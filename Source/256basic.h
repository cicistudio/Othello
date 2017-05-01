#include "dos.h"
#include "stdio.h"
#include "io.h"
#include "fcntl.h"

#define NO_SURFACE 1		/*缓冲形式:无缓冲页*/
#define SINGLE_SURFACE 0	/*缓冲形式:单缓冲页*/

#define TEXT_BIG_CURSOR 0	/*大文本光标(占整个字符)*/
#define TEXT_NORMAL_CURSOR 7	/*标准文本光标*/

char *malloc();		/*内存分配单元转化:字节型*/
unsigned int SurfaceMode;	/*记录缓冲形式*/

#include "256ems.h"

char far *VPoint=MK_FP(0xa000,0000);
unsigned int NowSurface=0,Vmode=0;
unsigned char lastVpage;

typedef
struct
{int left;
 int right;
 int top;
 int bottom;
}
RECT;

static RECT default_cut={0,639,0,479};
RECT screen_cut={0,639,0,479};/*屏幕剪切定义*/

void setdac()		/*设置抖动bmp格式色表，该色表是XNVIEW的256色抖动矩阵色表dacmap*/
{register int r,g,b,k=0;
 for(r=0;r<64;r+=9)
  for(g=0;g<64;g+=9)
   for(b=0;b<64;b+=21)
   {outportb(0x3c8,k);
    outportb(0x3c9,r);
    outportb(0x3c9,g);
    outportb(0x3c9,b);
    k++;
   }
}

void restoredac()	/*恢复EGA/VGA 16色色表*/
{int i=0,
 pattle16[48]=
 {0,0,0,	0,0,43,		0,42,0,		0,43,43,
  43,0,0,	43,0,43,	43,22,0,	43,43,43,
  22,22,22,	20,20,63,	0,63,0,		0,63,63,
  63,20,20,	63,20,63,	63,63,0,	63,63,63
 };
 char ega_colors[16]={0,1,2,3,4,5,20,7,56,57,58,59,60,61,62,63};
 for(i=0;i<16;i++)
 {outportb(0x3c8,ega_colors[i]);
  outportb(0x3c9,pattle16[i*3]);
  outportb(0x3c9,pattle16[i*3+1]);
  outportb(0x3c9,pattle16[i*3+2]);
 }
}

void setpalette(char far *PaletteData)/*设置系统调色板*/
{ struct REGPACK regs;
  regs.r_ax=0x1012;
  regs.r_bx=0;/*开始设置的颜色，一般为0，即从0号色开始获取*/
  regs.r_cx=256;/*count为要获取的颜色数目，一般为256或16*/
  regs.r_es=FP_SEG(PaletteData);
  regs.r_dx=FP_OFF(PaletteData);
  intr(0x10,&regs);
}

void getpalette(char far *PaletteData)/*获取系统调色版*/
{ struct REGPACK regs;
  regs.r_ax=0x1017;
  regs.r_bx=0;/*开始获取的颜色，一般为0，即从0号色开始获取*/
  regs.r_cx=256;/*count为要获取的颜色数目，一般为256或16*/
  regs.r_es=FP_SEG(PaletteData);
  regs.r_dx=FP_OFF(PaletteData);
  intr(0x10,&regs);
}

static int PIXEL_MODE=COPY_PUT;
void putpixel(register int x,register int y,register unsigned char color)
/*256 640*480写点函数，允许使用点模式，PEXEL_MODE设置见emsbytecopy处的宏定义，
  不同的是它的INVERT_PUT是对目标取反而不是对源取反
*/
{register unsigned char n,far *descpoint;
 register long temp=640l*y+x;
 register unsigned int nowVpage,nowEmap;
 if(x<screen_cut.left||x>screen_cut.right||y<screen_cut.top||y>screen_cut.bottom)return;
 if(SurfaceMode)
 {nowVpage=temp>>16;
  if(nowVpage!=lastVpage)
   {selectpage(nowVpage);
    lastVpage=nowVpage;
   }
  temp&=0xffff;
  descpoint=VPoint;
 }
 else
 {nowEmap=temp>>14;
  if(nowEmap!=lastEmap[0])emap(nowEmap,0);
  temp&=0x3fff;
  descpoint=EmsPoint;
 }
 switch(PIXEL_MODE)
 {case COPY_PUT		:*(descpoint+temp)=color;break;
  case INVERT_PUT	:*(descpoint+temp)=~*(descpoint+temp);break;	/*是对目标取反*/
  case OR_PUT		:*(descpoint+temp)=*(descpoint+temp)|color;break;
  case AND_PUT		:*(descpoint+temp)=*(descpoint+temp)&color;break;
  case XOR_PUT		:*(descpoint+temp)=*(descpoint+temp)^color;
 }
}

#define EMS_DATA_SEEK 1310720l	/*80页EMS数据缓冲区结束位置*/
#define LENGTH_HZK12 196272l	/*HZK12的数据总长度*/
#define LENGTH_HZK16 267616l	/*HZK16的数据总长度*/

static unsigned long BmpStackStart;	/*要加载BMP图像数据区起始指针，image.h用*/
static unsigned long BmpStackPos;	/*要加载BMP图像数据区工作指针，image.h用*/

#define DestroyAllImage BmpStackPos=BmpStackStart
/*释放所有由LoadImage和Initanimate分配的EMS图像资源*/

static unsigned long HZK12_DATA=0,HZK16_DATA=0;	/*HZK12与HZK16的EMS数据指针*/
unsigned char far *ROM16,far *ROM14,far *ROM8;/* 16*8、14*8及8*8 ASCII ROM字模指针*/

void LoadChinease()	/*加载中文字体文件到EMS，初始化BMP图像数据区起始指针*/
{unsigned int i;
 int HZK;
 BmpStackStart=EMS_DATA_SEEK;
 if((HZK=_open("fnt\\HZK12",1))!=-1)		/*试图加载12点阵汉字库*/
 {for(i=0;i<11;i++)
  {emap(80+i,0);
   _read(HZK,EmsPoint,16384);
  }
  emap(80+i,0);
  _read(HZK,EmsPoint,16048);
  HZK12_DATA+=EMS_DATA_SEEK;
  BmpStackStart+=LENGTH_HZK12;
  _close(HZK);
 }
 if((HZK=_open("fnt\\HZK16",1))!=-1)		/*试图加载16点阵汉字库*/
 {if(HZK12_DATA>0)
  {_read(HZK,EmsPoint+16048,336);
   for(i=0;i<16;i++)
   {emap(92+i,0);
    _read(HZK,EmsPoint,16384);
   }
   emap(92+i,0);
   _read(HZK,EmsPoint,5136);
   HZK16_DATA+=HZK12_DATA+LENGTH_HZK12;
  }
  else
  {for(i=0;i<16;i++)
   {emap(80+i,0);
    _read(HZK,EmsPoint,16384);
   }
   emap(80+i,0);
   _read(HZK,EmsPoint,5472);
   HZK16_DATA=EMS_DATA_SEEK;
  }
  BmpStackStart+=LENGTH_HZK16;
  _close(HZK);
 }
}

unsigned char far* get_ascii_rom(unsigned int reg_bx)
{struct REGPACK reg;
 reg.r_ax=0x1130;
 reg.r_bx=reg_bx;
 intr(0x10,&reg);
 return MK_FP(reg.r_es,reg.r_bp);		/*获得ROM字符集首址*/
}

void hide_text_cursor(void)	/*隐藏文本光标*/
{union REGS r;
 r.h.ah=1;
 r.h.ch=32;
 int86(0x10,&r,&r);
}

void show_text_cursor(char size)	/*(10-17):自定义文本光标)*/
{union REGS r;
 r.h.ah=1;
 r.h.cl=size;
 r.h.ch=7;
 int86(0x10,&r,&r);
}

unsigned char set_SVGA_mode(int vmode)
{union REGS r;
 r.x.ax=0x4f02;
 r.x.bx=vmode;
 int86(0x10,&r,&r);
 return(r.h.ah);
}

unsigned int get_SVGA_mode()
{union REGS r;
 r.x.ax=0x4f03;
 int86(0x10,&r,&r);
 return(r.x.bx);
}

void close256()	/*恢复文本模式*/
{selectpage(0);
 if(Vmode!=0)
 {set_SVGA_mode(Vmode);
  show_text_cursor(TEXT_NORMAL_CURSOR);
  restoredac();
 }
 efree();
}

void init256(char Surface_Mode)	/*初始化屏幕到640*480 256色模式*/
{ROM8=get_ascii_rom(0x0300);	/*获得ROM字符集首址*/
 ROM14=get_ascii_rom(0x0200);	/*获得ROM字符集首址*/
 ROM16=get_ascii_rom(0x0600);	/*获得ROM字符集首址*/

 SurfaceMode=Surface_Mode;
 initems();
 Vmode=get_SVGA_mode();
 hide_text_cursor();	/*隐藏文本光标，256色图形模式不兼容文本光标*/
 LoadChinease();
 DestroyAllImage;	/*复位BMP数据工作指针*/
 if(set_SVGA_mode(0x101))
 {printf("\nSorry, Your graphics driver does not supplied.\n");
  close256();
  exit(0);
 }
 setdac();
 selectpage(0);
}

void cls(unsigned char k)	/*清屏函数*/
{register unsigned int i,n;
 register char buffer[1024],*p=MK_FP(0xa000,0);
 for(i=0;i<1024;i++)buffer[i]=k;
 if(SurfaceMode)
 {for(n=0;n<5;n++)
  {selectpage(n);
   for(i=0;i<64;i++)
   memcpy(p+i*1024,buffer,1024);
  }
 }
 else
 {for(n=0;n<300;n++)
  {
  i=n/16;
  if(n%16==0)emap(i,0);
  memcpy(EmsPoint+n%16*1024l,buffer,1024);
  }
 }
}

unsigned char getpixel(register int x,register int y)	/*读取像素颜色函数*/
{register long temp=640l*y+x;
 register int nowEmap,n;
 if(SurfaceMode)
 {selectpage(temp>>16);
  temp&=0xffff;
  lastVpage=(temp>>16);
  return(peekb(0xa000,temp));
 }
 else
 {nowEmap=temp>>14;
  if(nowEmap!=lastEmap[0])emap(nowEmap,0);
  temp&=0x3fff;
  return(*(EmsPoint+temp));
 }
}

selectpage(register char page)	/*Video Bios 换页函数*/
{union REGS r;
 r.x.ax=0x4f05;
 r.x.bx=0;
 r.x.dx=page;	/*选择页面*/
 int86(0x10,&r,&r);
 lastVpage=page;
}

void vpost(void)	/*刷新页面*/
{register unsigned int i,j;
 if(SurfaceMode)return;/*是单缓冲页系统专用的*/
 {for(j=0;j<5;j++)
  {for(i=0;i<4;i++)
    emap(j*4+i,i);
   selectpage(j);
   memcpy(VPoint,EmsPoint,32768);
   memcpy(VPoint+32768,EmsPoint+32768,32768);
  }
 }
}

void byte_emstov(unsigned long desc,unsigned long src,char mode)
/*
  单字节的图像数据字节传输函数，desc(目标)和src(源)均为传输的EMS相对偏移
  mode含义如下
  mode>=0	:使用mode颜色掩码（过滤掉mode颜色）
  mode=COPY_PUT	:直接传输（也可以换OR_PUT等）
*/
{register unsigned int vpage=desc>>16,voffset=desc&0xffff,
		       emsmap=src>>14,emsoffset=src&0x3fff;
 register unsigned char c1,c2;

 if(lastEmap[0]!=emsmap)emap(emsmap,0);
 if(lastVpage!=vpage)selectpage(vpage);
 c1=*(VPoint+voffset);
 c2=*(EmsPoint+emsoffset);

 if(mode>=0)
 {if(c2!=mode)
   *(VPoint+voffset)=c2;
 }
 else
  switch(mode)
  {case COPY_PUT	:*(VPoint+voffset)=c2;break;
   case INVERT_PUT	:*(VPoint+voffset)=~c2;break;
   case OR_PUT		:*(VPoint+voffset)=c1|c2;break;
   case AND_PUT		:*(VPoint+voffset)=c1&c2;break;
   case XOR_PUT		:*(VPoint+voffset)=c1^c2;
  }
}

void MySelectpage1(unsigned int page,char mode)
{if(mode)	/*换Vpage*/
 {if(lastVpage!=page)selectpage(page);
 }
 else		/*换EMSpage*/
 {char n;
  for(n=0;n<4;n++)
   if(page*4+n!=lastEmap[n])
    emap(page*4+n,n);
 }
}

void scanline_copy(unsigned long desc,unsigned long src,unsigned int length,char mode)
/*
  单扫描线内容拷贝函数，desc与src均使用相对偏移，mode值意义如下：
  值	意义
  ---------------
  1	EMS->VRAM
  -1	VRAM->EMS
*/
{char pagetype1,pagetype2,far* descPoint,far* srcPoint;
 unsigned descpage=desc>>16,descoffset=desc&0xffff,
	  srcpage=src>>16,srcoffset=src&0xffff;
 if(mode==1)
 {descPoint=VPoint;srcPoint=EmsPoint;
  pagetype1=1;pagetype2=0;
 }
 else
 {descPoint=EmsPoint;srcPoint=VPoint;
  pagetype1=0;pagetype2=1;
 }
 MySelectpage1(descpage,pagetype1);MySelectpage1(srcpage,pagetype2);
 if((long)srcoffset+length<=65536l&&(long)descoffset+length<=65536l)
 {memcpy(descPoint+descoffset,srcPoint+srcoffset,length);
  return;
 }
 else
 {unsigned int passed_length;
  if(descoffset==srcoffset)
  {passed_length=65536l-descoffset;
   memcpy(descPoint+descoffset,srcPoint+srcoffset,passed_length);
   MySelectpage1(descpage+1,pagetype1);MySelectpage1(srcpage+1,pagetype2);
   memcpy(descPoint,srcPoint,length-passed_length);
  }
  else
  {while(length>0)
   {if((long)srcoffset+length<=65536l&&(long)descoffset+length<=65536l)
    {memcpy(descPoint+descoffset,srcPoint+srcoffset,length);
     break;
    }
    if(srcoffset>descoffset)
    {passed_length=65536l-srcoffset;
     memcpy(descPoint+descoffset,srcPoint+srcoffset,passed_length);
     srcpage++;
     MySelectpage1(srcpage,pagetype2);
     descoffset+=passed_length;
     srcoffset=0;
    }
    else
    {passed_length=65536l-descoffset;
     memcpy(descPoint+descoffset,srcPoint+srcoffset,passed_length);
     descpage++;
     MySelectpage1(descpage,pagetype1);
     srcoffset+=passed_length;
     descoffset=0;
    }
    length-=passed_length;
   }
  }
 }
}

void MemCopy256(unsigned long descoffset,char *mempos,unsigned int length,char mode)
/*
  常规内存与EMS或VRAM间的拷贝函数，不带屏幕剪切，
  mempos为常规内存指针，EMS或VRAM起始点偏移，mode含义如下：
  mode	数据移动方向
  ------------------------
  0	常规内存->EMS
  1	常规内存->VRAM
  2	EMS->常规内存
  3	VRAM->常规内存
*/
{unsigned int page=descoffset>>16,offset=descoffset&0xffff,part1;
 char far* descPoint;
 if(mode%2)descPoint=VPoint;
 else descPoint=EmsPoint;
 MySelectpage1(page,mode%2);
 if((long)offset+length<=65536l)
 {if(mode/2)memcpy(mempos,descPoint+offset,length);
  else memcpy(descPoint+offset,mempos,length);
  return;
 }
 else
 {part1=65536l-offset;
  if(mode/2)memcpy(mempos,descPoint+offset,part1);
  else memcpy(descPoint+offset,mempos,part1);
  MySelectpage1(page+1,mode%2);
  length-=part1;
  if(mode/2)memcpy(mempos+part1,descPoint,length);
  else memcpy(descPoint,mempos+part1,length);
 }
}

void screenline_copy(int x,int y,char *mempos,unsigned int length,char mode)
/*
  常规内存与绘图屏幕间的水平线拷贝函数，带屏幕剪切，
  mempos为常规内存指针，(x,y)为屏幕上水平数据线的左起始点，mode含义如下：
  mode	数据移动方向
  ------------------------
  0	常规内存->EMS屏幕
  1	常规内存->VRAM屏幕
  2	EMS屏幕->常规内存
  3	VRAM屏幕->常规内存
*/
{unsigned int scan_seek=0,scan_length;
 unsigned long descoffset;
 if(x+length<screen_cut.left||x>screen_cut.right||y<screen_cut.top||y>screen_cut.bottom)return;
 if(x<screen_cut.left)scan_seek=screen_cut.left-x;
 if(x+length>screen_cut.right)scan_length=screen_cut.right-scan_seek-x+1;
 else scan_length=length-scan_seek;
 descoffset=y*640l+x+scan_seek;
 MemCopy256(descoffset,mempos+scan_seek,scan_length,mode);
}

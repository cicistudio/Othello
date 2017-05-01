void LoadDAC(char *bmpfile)	/*以bmpfile文件的色表设置系统调色版*/
{unsigned char buffer[1024],dac[768]={0};
 int n,fp;
 if((fp=_open(bmpfile,1))==-1)return;	/*加载失败则返回*/
 _read(fp,&n,2);
 if(n!=19778)goto OUT;/*检查文件标志不是BMP则返回*/
 lseek(fp,28,SEEK_SET);
 _read(fp,&n,2);
 if(n!=8)goto OUT;/*文件不是256色位图则返回*/
 lseek(fp,54,SEEK_SET);
 _read(fp,buffer,1024);
 for(n=0;n<256;n++)
 {dac[n*3]=buffer[n*4+2]>>2;
  dac[n*3+1]=buffer[n*4+1]>>2;
  dac[n*3+2]=buffer[n*4]>>2;
 }
 setpalette(dac);
 OUT:
 close(fp);
}

typedef
struct
{int width;/*图像宽*/
 int height;/*图像高*/
 char type;/*区别位图类型，'B'为256色位图，'M'为2色掩码位图*/
 unsigned long ems_offset;/*EMS数据位置*/
}
Bmp256;/*256色BMP数据类型*/

Bmp256 LoadImage(char* datfile)
/*加载256色位图数据到EMS*/
{Bmp256 bmp={0};
 int fp,n,nowEmap,Eseek;
 long readdata;
 if((fp=_open(datfile,1))==-1)return(bmp);
 lseek(fp,0,SEEK_SET);
 _read(fp,&bmp.width,2);
 _read(fp,&bmp.height,2);
 readdata=(long)bmp.width*bmp.height;
 bmp.ems_offset=BmpStackPos;
 nowEmap=BmpStackPos/16384;
 bmp.type='B';
 Eseek=BmpStackPos%16384;
 BmpStackPos+=readdata;
 n=nowEmap%4;
 if(lastEmap[n]!=nowEmap)
  emap(nowEmap,n);
 if(readdata<16384-Eseek)
  _read(fp,EmsPoint+n*16384+Eseek,readdata);
 else
 {_read(fp,EmsPoint+n*16384+Eseek,16384-Eseek);
  readdata-=(16384-Eseek);
  while(1)
  {nowEmap++;
   n=nowEmap%4;
   emap(nowEmap,n);
   if(readdata>16384)
   {_read(fp,EmsPoint+n*16384,16384);
    readdata-=16384;
   }
   else
   {_read(fp,EmsPoint+n*16384,readdata);
    break;
   }
  }
 }
 _close(fp);
 return(bmp);
}

Bmp256 LoadBMP(char *bmpfile)
/*加载BMP图像数据到EMS*/
{int color_depth,n,k,length,fp;
 unsigned char *buffer;
 Bmp256 bmp={0};
 if((fp=_open(bmpfile,1))==-1)return(bmp);/*如果打开文件失败则图像大小为0，数据指向为0*/
 _read(fp,&n,2);/*读取数字签名*/
 if(n!=19778)goto OUT;/*若文件数字签名不是BM则为打开失败*/
 lseek(fp,28,SEEK_SET);
 _read(fp,&color_depth,2);/*检查色深*/
 if(!(color_depth==1||color_depth==8))goto OUT;/*若色深不对也为打开失败*/
 if(color_depth==8)bmp.type='B';else bmp.type='M';/*标识数据是位图还是掩码*/
 lseek(fp,18,SEEK_SET);
 _read(fp,&bmp.width,2);/*读取图片宽*/
 lseek(fp,2,SEEK_CUR);
 _read(fp,&bmp.height,2);/*读取图片高*/
 lseek(fp,0,SEEK_END);
 bmp.ems_offset=BmpStackPos;
 if(color_depth==1)length=bmp.width/8+(bmp.width%8!=0);
 else length=bmp.width;
 buffer=malloc(length);
 k=(length%4)?(4-length%4):0; /*宽度修正值*/
 for(n=0;n<bmp.height;n++)
 {lseek(fp,-k-length,SEEK_CUR);
  _read(fp,buffer,length);/*读取数据至buffer*/
  MemCopy256(BmpStackPos,buffer,length,0);/*buffer数据移至EMS*/
  BmpStackPos+=length;/*从EMS图像数据栈尾部开始添加数据*/
  lseek(fp,-length,SEEK_CUR);
 }
 OUT:
 close(fp);
 return(bmp);
}

void PutImage(int x,int y,Bmp256 bmp,int mode)
/*输出位图到以(x,y)为左上角顶点的区域，mode参数设置见emsbytecopy*/
{register int i,j;
 register long n=0;
 if(bmp.type!='B')return;	/*类型检测*/
 for(j=0;j<bmp.height;j++)
  for(i=0;i<bmp.width;i++,n++)
  {if(i+x<screen_cut.left||i+x>screen_cut.right||j+y<screen_cut.top||j+y>screen_cut.bottom)continue;
   if(SurfaceMode)	/*无缓冲页，直接输出到屏幕*/
    byte_emstov((j+y)*640l+i+x,bmp.ems_offset+n,mode);
   else			/*单缓冲页，输出到EMS缓冲页*/
    emsbytecopy((j+y)*640l+i+x,bmp.ems_offset+n,mode);
  }
}

void QPutImage(int x,int y,Bmp256 bmp)
/*高速显示位图函数，输出位图到以(x,y)为左上角顶点的区域，只能拷贝输出*/
{register int j,scan_seek=0,scan_length;
 if(bmp.type!='B')return;	/*类型检测*/
 if(x+bmp.width<screen_cut.left||x>screen_cut.right)return;
 if(x<screen_cut.left)scan_seek=screen_cut.left-x;
 if(x+bmp.width>screen_cut.right)scan_length=screen_cut.right-scan_seek-x+1;
 else scan_length=bmp.width-scan_seek;
 for(j=0;j<bmp.height;j++)
 {if(j+y<screen_cut.top||j+y>screen_cut.bottom)continue;
  if(SurfaceMode)	/*无缓冲页，直接输出到屏幕*/
   scanline_copy((j+y)*640l+x+scan_seek,bmp.ems_offset+(long)j*bmp.width+scan_seek,scan_length,1);
  else			/*单缓冲页，输出到EMS缓冲页*/
   emsblockcopy((j+y)*640l+x+scan_seek,bmp.ems_offset+(long)j*bmp.width+scan_seek,scan_length);
 }
}

void PutMask(int x,int y,Bmp256 bmp,unsigned char color)
/*输出二进制掩码位图bmp到以(x,y)为左上角的位置，颜色为color，也可以设置点模式PIXEL_MODE产生特殊效果*/
{register int i,j,k,w,fix,n,c;
 register unsigned long datapos=bmp.ems_offset;
 register unsigned int nowEmap;
 if(bmp.type!='M')return;	/*类型检测*/
 fix=bmp.width%8;
 w=bmp.width/8+(fix?1:0);
 for(j=0;j<bmp.height;j++)
  for(i=0;i<w;i++)
  {nowEmap=datapos>>14;
   if(nowEmap!=lastEmap[2])emap(nowEmap,2);
   c=*(EmsPoint+32768+(datapos&0x3fff));
   if((i==w-1)&&fix)n=fix;
   else n=8;
   for(k=0;k<n;k++)
    if(c&(0x80>>k))
     putpixel(x+i*8+k,y+j,color);
   datapos++;
  }
}

typedef
struct
{int x,y;			/*物体左上角屏幕坐标位置*/
 int width,height;		/*物体的宽、高*/
 unsigned char active;		/*是否激活(是否响应show_animate)*/
 unsigned char autoplaying;	/*是否每显示一次则自动增加内部计时器*/
 unsigned char nowplaying;	/*当前播放帧*/
 unsigned char framecount;	/*动画总帧数*/
 unsigned int timedelay;	/*每间隔帧间的延时(使用show_animate多少次则更换一帧)*/
 unsigned int timetick;		/*物体内部的show_animate计数器*/
 unsigned char maskcolor;	/*要设置为透明颜色*/
 Bmp256 bmp;			/*bmp图像数据*/
}
Animate256;			/*256色简单动画物体类型*/

void initanimate(Animate256 *animate,int startx,int starty,unsigned char framecount,unsigned int timedelay,unsigned char maskcolor,char *datfile)
/*初始化动画对象，参数依次为：动画对象、物体屏幕坐标(x,y)、总帧数、帧间隔延时、掩码颜色、数据文件*/
{animate->x=startx;animate->y=starty;
 animate->autoplaying=1;		/*启动内部计时器*/
 animate->nowplaying=0;		/*初始化时从第一帧开始播放*/
 animate->framecount=framecount;
 animate->timedelay=timedelay;
 animate->timetick=0;
 animate->active=1;		/*初始化时物体已激活(可以显示在屏幕)*/
 animate->maskcolor=maskcolor;	/*设置透明颜色*/
 animate->bmp=LoadBMP(datfile);
 animate->width=animate->bmp.width/framecount;
 animate->height=animate->bmp.height;
}

void showanimate(Animate256 *animate)	/*使用掩码(透明色)刷新动画物体到屏幕*/
{register int i,j,width=animate->bmp.width/animate->framecount;
 register long n=0;
 if(!animate->active|animate->bmp.type!='B')return;	/*未激活则不绘制图像和数据类型检测*/
 n+=(width*animate->nowplaying);
 for(j=0;j<animate->bmp.height;j++)
 {for(i=0;i<width;i++,n++)
  {if(i+animate->x<screen_cut.left||i+animate->x>screen_cut.right||
      j+animate->y<screen_cut.top||j+animate->y>screen_cut.bottom)continue;
   if(SurfaceMode)	/*无缓冲页，直接输出到屏幕*/
    byte_emstov((j+animate->y)*640l+i+animate->x,animate->bmp.ems_offset+n,animate->maskcolor);
   else			/*单缓冲页，输出到EMS缓冲页*/
    emsbytecopy((j+animate->y)*640l+i+animate->x,animate->bmp.ems_offset+n,animate->maskcolor);
  }
  n+=(width*(animate->framecount-1));
 }
 if(!animate->autoplaying)return;	/*未启动内部计数器则不计数*/
 if(animate->timetick==animate->timedelay-1)	/*未达到更帧换的时间则不更换帧*/
 {animate->nowplaying=(animate->nowplaying+1)%animate->framecount;animate->timetick=0;}
 else animate->timetick++;
}

void Qshowanimate(Animate256 *animate)
/*不使用掩码刷新物体到屏幕，速度较showanimate快*/
{register int j,scan_seek=0,scan_length,width=animate->bmp.width/animate->framecount;
 if(!animate->active|animate->bmp.type!='B')return;	/*未激活则不绘制图像和数据类型检测*/
 if(animate->x+width<screen_cut.left||animate->x>screen_cut.right)return;
 if(animate->x<screen_cut.left)scan_seek=screen_cut.left-animate->x;
 if(animate->x+width>screen_cut.right)scan_length=screen_cut.right-scan_seek-animate->x+1;
 else scan_length=width-scan_seek;
 for(j=0;j<animate->bmp.height;j++)
 {if(j+animate->y<screen_cut.top||j+animate->y>screen_cut.bottom)continue;
  if(SurfaceMode)	/*无缓冲页，直接输出到屏幕*/
   scanline_copy((j+animate->y)*640l+animate->x+scan_seek,animate->bmp.ems_offset+(long)j*animate->bmp.width+(long)width*(animate->nowplaying)+scan_seek,scan_length,1);
  else			/*单缓冲页，输出到EMS缓冲页*/
   emsblockcopy((j+animate->y)*640l+animate->x+scan_seek,animate->bmp.ems_offset+(long)j*animate->bmp.width+(long)width*(animate->nowplaying)+scan_seek,scan_length);
 }
 if(animate->timetick==animate->timedelay)	/*未达到更帧换的时间则不更换帧*/
 {animate->nowplaying=(animate->nowplaying+1)%animate->framecount;animate->timetick=0;}
 else animate->timetick++;
}

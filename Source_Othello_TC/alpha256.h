/******************************************/
/*               alpha256.h               */
/*                                        */
/*               alpha函数库              */
/*                                        */
/*            Cat Tom 8.29.2003           */
/******************************************/




/******************************************************************/
/*序号_RGB矩阵*/
static struct
{
 unsigned char r;
 unsigned char g;
 unsigned char b;
}pal[256];

/*RGB_序号矩阵*/
static unsigned char rgbmatrix[8][8][4];



/******************************************************************/
/*根据r,g,b值找匹配色号的宏*/
#define findbest(r,g,b) rgbmatrix[(r+4)/9][(g+4)/9][(b+10)/21]



/******************************************************************/
/*ALPHA初始化函数*/
void initalpha()
{unsigned char r,g,b,k=0;
 unsigned char rcounter,gcounter,bcounter;
 int index;
 for(r=0,rcounter=0;r<64;r+=9,rcounter++)
  for(g=0,gcounter=0;g<64;g+=9,gcounter++)
   for(b=0,bcounter=0;b<64;b+=21,bcounter++)
   {
    pal[k].r=r;
    pal[k].g=g;
    pal[k].b=b;/*给序号_RGB矩阵赋值*/

    rgbmatrix[rcounter][gcounter][bcounter]=k;/*给RGB_序号矩阵赋值*/

    k++;
   }
}


/*画ALPHA点的函数*/
void alphadot(int x,int y,register unsigned char color)
{register unsigned char n,far *descpoint;
 register long temp=640l*y+x;
 register unsigned int nowVpage,nowEmap;
 register unsigned char r,g,b,oldcolor;
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

 oldcolor=*(descpoint+temp);

 /*进行50%的ALPHA混合*/
 r = (pal[color].r+pal[oldcolor].r)>>1;
 g = (pal[color].g+pal[oldcolor].g)>>1;
 b = (pal[color].b+pal[oldcolor].b)>>1;

 *(descpoint+temp)=findbest(r,g,b);
}


/*画ALPHA线的函数*/
void alphaline(int x1,int y1,int x2,int y2,unsigned char color)
{int xdelta,ydelta,xstep,ystep,change;
 xdelta=x2-x1;
 ydelta=y2-y1;
 if(xdelta<0)
 {xdelta=-xdelta;                /*从右向左画线*/
  xstep=-1;
 }
 else xstep=1;                        /*从左向右画线*/
 if(ydelta<0)
 {ydelta=-ydelta;                /*从下向上画线*/
  ystep=-1;
 }
 else ystep=1;                        /*从上向下画线*/
 if (xdelta>ydelta)                /*x改变得比y快*/
 {change=xdelta>>1;
  while(x1!=x2)
  {alphadot(x1,y1,color);
   x1+=xstep;
   change+=ydelta;
   if(change>xdelta)
   {y1+=ystep;
    change-=xdelta;
 }}}
 else                                /*y改变得比x快*/
 {change=ydelta>>1;
  while(y1!=y2)
  {alphadot(x1,y1,color);
   y1+=ystep;
   change+=xdelta;
   if(change>ydelta)
   {x1+=xstep;
    change-=ydelta;
 }}}
 alphadot(x2,y2,color);
}


/*画ALPHA实心矩形的函数*/
void alphabar(int x,int y,unsigned int width,unsigned int height,unsigned char color)
{
 int i,j;
 for(i=y;i<y+height;i++)
   for(j=x;j<x+width;j++)
     alphadot(j,i,color);
}


/*ALPHA的掩码输出*/
void alphamask(int x,int y,Bmp256 bmp,unsigned char color)
{register int i,j,k,w,fix,n,c;
 register unsigned long datapos=bmp.ems_offset;
 register unsigned int nowEmap;
 if(bmp.type!='M')return;        /*类型检测*/
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
     alphadot(x+i*8+k,y+j,color);
   datapos++;
  }
}


/*内部函数,为ALPHA模式的内存-内存拷贝*/
void alphaemscopy(unsigned long desc,unsigned long src,unsigned char mask)
{register unsigned int descmap=desc>>14,descoffset=desc&0x3fff,
                       srcmap=src>>14,srcoffset=src&0x3fff;
 register unsigned char c1,c2,r,g,b;
 if(lastEmap[0]!=descmap)emap(descmap,0);
 if(lastEmap[1]!=srcmap)emap(srcmap,1);
 c1=*(EmsPoint+descoffset);
 c2=*(EmsPoint+16384+srcoffset);

 if(c2!=mask)
 {
  /*进行50%的ALPHA混合*/
  r = (pal[c1].r+pal[c2].r)>>1;
  g = (pal[c1].g+pal[c2].g)>>1;
  b = (pal[c1].b+pal[c2].b)>>1;

  *(EmsPoint+descoffset)=findbest(r,g,b);
 }
}


/*内部函数,ALPHA模式的内存-显存拷贝*/
void alphaemstov(unsigned long desc,unsigned long src,unsigned char mask)
{register unsigned int vpage=desc>>16,voffset=desc&0xffff,
                       emsmap=src>>14,emsoffset=src&0x3fff;
 register unsigned char c1,c2,r,g,b;

 if(lastEmap[0]!=emsmap)emap(emsmap,0);
 if(lastVpage!=vpage)selectpage(vpage);
 c1=*(VPoint+voffset);
 c2=*(EmsPoint+emsoffset);

 if(c2!=mask)
 {
  /*进行50%的ALPHA混合*/
  r = (pal[c1].r+pal[c2].r)>>1;
  g = (pal[c1].g+pal[c2].g)>>1;
  b = (pal[c1].b+pal[c2].b)>>1;

  *(VPoint+voffset)=findbest(r,g,b);
 }
}



/*输出ALPHA混合的位图*/
void alphaimage(int x,int y,Bmp256 bmp,int mask)
{register int i,j;
 register long n=0;
 if(bmp.type!='B')return;        /*类型检测*/
 for(j=0;j<bmp.height;j++)
  for(i=0;i<bmp.width;i++,n++)
  {if(i+x<screen_cut.left||i+x>screen_cut.right||j+y<screen_cut.top||j+y>screen_cut.bottom)continue;
   if(SurfaceMode)        /*无缓冲页，直接输出到屏幕*/
    alphaemstov((j+y)*640l+i+x,bmp.ems_offset+n,mask);
   else                        /*单缓冲页，输出到EMS缓冲页*/
    alphaemscopy((j+y)*640l+i+x,bmp.ems_offset+n,mask);
  }
}


/*显示子画面库中的ALPHA混合图象*/
void alphaputspr(int x,int y,int xx,int yy,Sprlib slib,int mask)
{register int i,j;
 register long offsety;

 /*类型检测,如源坐标错误则返回*/
 if(slib.image.type!='B'||xx<1||xx>slib.xx||yy<1||yy>slib.yy)return;

 offsety=(long)slib.image.width*slib.height*(yy-1)+slib.width*(xx-1);
 for(j=0;j<slib.height;j++,offsety+=slib.image.width)
  for(i=0;i<slib.width;i++)
  {if(i+x<screen_cut.left||i+x>screen_cut.right||j+y<screen_cut.top||j+y>screen_cut.bottom)continue;
   if(SurfaceMode)        /*无缓冲页，直接输出到屏幕*/
    alphaemstov((j+y)*640l+i+x,slib.image.ems_offset+offsety+i,mask);
   else                        /*单缓冲页，输出到EMS缓冲页*/
    alphaemscopy((j+y)*640l+i+x,slib.image.ems_offset+offsety+i,mask);
  }

}
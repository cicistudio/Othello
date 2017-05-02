/******************************************/
/*                slb256.h                */
/*                                        */
/*             子画面库函数库             */
/*                                        */
/*            Cat Tom 8.29.2003           */
/******************************************/




/******************************************************************/




/******************************************************************/
typedef struct
{
 int width;          /*子画面宽*/
 int height;         /*子画面高*/
 int xx;             /*横向子画面数*/
 int yy;             /*纵向子画面数*/
 Bmp256 image;       /*图象*/
}Sprlib;



/******************************************************************/
/*加载子画面库的函数*/
Sprlib loadsprlib(int width,int height,char *filename)
{

 Sprlib slib;

 /*加载bmp图象*/
 slib.image=LoadBMP(filename);

 slib.width=width;
 slib.height=height;

 /*若图象长宽和子画面长宽不能整除则结束*/
 if(slib.image.width%slib.width!=0||slib.image.height%slib.height!=0)exit(0);

 slib.xx=slib.image.width/slib.width;
 slib.yy=slib.image.height/slib.height;

 return slib;
}


/*显示子画面库中的图象*/
void putspr(int x,int y,int xx,int yy,Sprlib slib,int mode)
{register int i,j;
 register long offsety;

 /*类型检测,如源坐标错误则返回*/
 if(slib.image.type!='B'||xx<1||xx>slib.xx||yy<1||yy>slib.yy)return;

 offsety=(long)slib.image.width*slib.height*(yy-1)+slib.width*(xx-1);
 for(j=0;j<slib.height;j++,offsety+=slib.image.width)
  for(i=0;i<slib.width;i++)
  {if(i+x<screen_cut.left||i+x>screen_cut.right||j+y<screen_cut.top||j+y>screen_cut.bottom)continue;
   if(SurfaceMode)        /*无缓冲页，直接输出到屏幕*/
    byte_emstov((j+y)*640l+i+x,slib.image.ems_offset+offsety+i,mode);
   else                        /*单缓冲页，输出到EMS缓冲页*/
    emsbytecopy((j+y)*640l+i+x,slib.image.ems_offset+offsety+i,mode);
  }

}
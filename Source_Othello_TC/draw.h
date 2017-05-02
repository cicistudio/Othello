#define PI 3.1415926536	/*π常量*/

#define BLACK 0		/*黑色*/
#define WHITE 255	/*白色*/
#define RED 224		/*红色*/
#define GREEN 28	/*绿色*/
#define BLUE 3		/*蓝色*/
#define LIGHTGRAY 182	/*浅灰色*/
#define DARKGRAY 109	/*深灰色*/
#define YELLOW 252	/*黄色*/
#define DARKGREEN 12	/*深绿色*/
#define LIGHTBLUE 83	/*浅蓝色*/
#define CYAN 31		/*青色*/
#define PINK 234	/*粉红色*/
#define ORANGE 236	/*橙色*/
#define MAGENTA 227	/*紫色*/
#define BROWN 136	/*褐色*/

/*画矩形的宏*/
#define rectangle(x0,y0,x1,y1,color) line(x0,y0,x0,y1,color);line(x0,y0,x1,y0,color);line(x0,y1,x1,y1,color);line(x1,y1,x1,y0,color)

void line(int x1,int y1,int x2,int y2,unsigned char color)
/*通用的画线函数，用color颜色由(x1,y1)画到(x2,y2)*/
{int xdelta,ydelta,xstep,ystep,change;
 xdelta=x2-x1;
 ydelta=y2-y1;
 if(xdelta<0)
 {xdelta=-xdelta;		/*从右向左画线*/
  xstep=-1;
 }
 else xstep=1;			/*从左向右画线*/
 if(ydelta<0)
 {ydelta=-ydelta;		/*从下向上画线*/
  ystep=-1;
 }
 else ystep=1;			/*从上向下画线*/
 if (xdelta>ydelta)		/*x改变得比y快*/
 {change=xdelta>>1;
  while(x1!=x2)
  {putpixel(x1,y1,color);
   x1+=xstep;
   change+=ydelta;
   if(change>xdelta)
   {y1+=ystep;
    change-=xdelta;
 }}}
 else				/*y改变得比x快*/
 {change=ydelta>>1;
  while(y1!=y2)
  {putpixel(x1,y1,color);
   y1+=ystep;
   change+=xdelta;
   if(change>ydelta)
   {x1+=xstep;
    change-=ydelta;
 }}}
 putpixel(x2,y2,color);
}

void circle(int centrex,int centrey,int r,unsigned char color)
/*画圆函数，以(centrex,centrey)为中心画一半径为r的圆*/
{int x,y,delta,delta1,delta2,direction;
 x=0;y=r;
 delta=2*(1-r);
 while(y>=0)
 {putpixel(centrex+x,centrey+y,color);
  putpixel(centrex-x,centrey-y,color);
  putpixel(centrex+x,centrey-y,color);
  putpixel(centrex-x,centrey+y,color);
  if(delta<0)
  {delta1=2*(delta+y)-1;
   if(delta1<=0)direction=1;
   else direction=2;
  }
  else if(delta>0)
  {delta2=2*(delta-x)-1;
   if(delta2<=0)direction=2;
   else direction=3;
  }
  else direction=2;
  switch(direction)
  {case 1:x++;
	  delta+=2*x+1;
	  break;
   case 2:x++;
	  y--;
	  delta+=2*(x-y+1);
	  break;
   case 3:y--;
	  delta+=(-2*y+1);
	  break;
  }
 }
}

void ellipse(int x0,int y0,int a,int b,unsigned char color)
/*以(x0,y0)为中心、a和b分别为水平和垂直半轴画一椭圆*/
{int x,y;
 float d1,d2;
 x=0;y=b;
 d1=b*b+a*a*(-b+0.25);
 putpixel(x0+x,y0+y,color);
 putpixel(x0-x,y0-y,color);
 putpixel(x0-x,y0+y,color);
 putpixel(x0+x,y0-y,color);
 while((x+1f)*b*b<(y-0.5f)*a*a)
 {if(d1<0)
  {d1+=(2f*x+3)*b*b;
   x++;
  }
  else
  {d1+=(2f*x+3)*b*b+(-2f*y+2)*a*a;
   x++;y--;
  }
  putpixel(x0+x,y0+y,color);
  putpixel(x0-x,y0-y,color);
  putpixel(x0-x,y0+y,color);
  putpixel(x0+x,y0-y,color);
 }
 d2=(x+0.5f)*b+(y-1f)*a-a*b;
 while(y>0)
 {if(d2<0)
  {d2+=(2f*x+2)*b*b+(-2f*y+3)*a*a;
   x++;y--;
  }
  else
  {d2+=(-2f*y+3)*a*a;
   y--;
  }
  putpixel(x0+x,y0+y,color);
  putpixel(x0-x,y0-y,color);
  putpixel(x0-x,y0+y,color);
  putpixel(x0+x,y0-y,color);
 }
}

void bar(int x,int y,unsigned int width,unsigned int height,unsigned char color)
/*以(x,y)为左上角顶点画一宽width、高height的填充矩形*/
{unsigned int j;
 unsigned char *buffer=malloc(width);
 memset(buffer,color,width);
 for(j=0;j<height;j++)
 {if(SurfaceMode)screenline_copy(x,y+j,buffer,width,1);
  else screenline_copy(x,y+j,buffer,width,0);
  }
 free(buffer);
}

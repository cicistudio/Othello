#define PI 3.1415926536	/*�г���*/

#define BLACK 0		/*��ɫ*/
#define WHITE 255	/*��ɫ*/
#define RED 224		/*��ɫ*/
#define GREEN 28	/*��ɫ*/
#define BLUE 3		/*��ɫ*/
#define LIGHTGRAY 182	/*ǳ��ɫ*/
#define DARKGRAY 109	/*���ɫ*/
#define YELLOW 252	/*��ɫ*/
#define DARKGREEN 12	/*����ɫ*/
#define LIGHTBLUE 83	/*ǳ��ɫ*/
#define CYAN 31		/*��ɫ*/
#define PINK 234	/*�ۺ�ɫ*/
#define ORANGE 236	/*��ɫ*/
#define MAGENTA 227	/*��ɫ*/
#define BROWN 136	/*��ɫ*/

/*�����εĺ�*/
#define rectangle(x0,y0,x1,y1,color) line(x0,y0,x0,y1,color);line(x0,y0,x1,y0,color);line(x0,y1,x1,y1,color);line(x1,y1,x1,y0,color)

void line(int x1,int y1,int x2,int y2,unsigned char color)
/*ͨ�õĻ��ߺ�������color��ɫ��(x1,y1)����(x2,y2)*/
{int xdelta,ydelta,xstep,ystep,change;
 xdelta=x2-x1;
 ydelta=y2-y1;
 if(xdelta<0)
 {xdelta=-xdelta;		/*����������*/
  xstep=-1;
 }
 else xstep=1;			/*�������һ���*/
 if(ydelta<0)
 {ydelta=-ydelta;		/*�������ϻ���*/
  ystep=-1;
 }
 else ystep=1;			/*�������»���*/
 if (xdelta>ydelta)		/*x�ı�ñ�y��*/
 {change=xdelta>>1;
  while(x1!=x2)
  {putpixel(x1,y1,color);
   x1+=xstep;
   change+=ydelta;
   if(change>xdelta)
   {y1+=ystep;
    change-=xdelta;
 }}}
 else				/*y�ı�ñ�x��*/
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
/*��Բ��������(centrex,centrey)Ϊ���Ļ�һ�뾶Ϊr��Բ*/
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
/*��(x0,y0)Ϊ���ġ�a��b�ֱ�Ϊˮƽ�ʹ�ֱ���ửһ��Բ*/
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
/*��(x,y)Ϊ���ϽǶ��㻭һ��width����height��������*/
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
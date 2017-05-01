#define TX_NORMAL 12	/*普通字体*/
#define TX_BIG 16	/*大字体*/
#define TX_SMALL 8	/*小字体*/
char TEXT_SIZE=TX_NORMAL;	/*字体标志*/

char TEXT_DIRECTION=1;		/*排字标志，1为横排，0为竖排*/

#define SL_NONE 0	/*文字不倾斜*/
#define SL_LEFT 1	/*文字左倾*/
#define SL_RIGHT -1	/*文字右倾*/
char TEXT_SLANT=SL_NONE;	/*文字倾斜:不倾斜*/

void puts256(unsigned char *s,int x,int y,int color)
/*显示彩色汉字，把*s所指的字符串输出到(x,y)为左上定点的位置，现支持3种字体*/
{char text_flag,fix_length=0,th,tw,i,j,mat[32]={0},canput,text_h,slant;
 long position;
 unsigned char qh,wh,*p,far *ROM;
 unsigned long HZK_DATA=0;
 switch(TEXT_SIZE)		/*确定使用的ROM字符与相配的汉字库类型*/
 {case TX_NORMAL:ROM=ROM14;HZK_DATA=HZK12_DATA;text_h=14;break;
  case TX_BIG   :ROM=ROM16;HZK_DATA=HZK16_DATA;text_h=16;break;
  case TX_SMALL :ROM=ROM8;text_h=8;	/*该ROM字符无匹的配汉字类型*/
 }
 while(*s!=0)
 {if(*s>0xa0&&*(s+1)>0xa0)
  {if(HZK_DATA>0)		/*已加载相应HZK*/
   {tw=16;th=TEXT_SIZE;
    qh=*s-0xa0;
    wh=*(s+1)-0xa0;
    position=(94*(qh-1)+(wh-1))*2l*th;
    MemCopy256(HZK_DATA+position,mat,th*2,2);
   }
   else memset(mat,0,32);
   text_flag=1;			/*字体标志为汉字*/
  }
  else
  {tw=8;th=text_h;
   memcpy(mat,ROM+(*s)*text_h,text_h);
   text_flag=0;			/*字体标志为英文字母*/
  }
  slant=0;
  for(j=0;j<th;j++)
  {if(!(j%4))slant+=TEXT_SLANT;	/*控制文字的倾斜*/
   for(i=0;i<tw;i++)
   {if(text_flag)canput=((0x80>>i%8)&mat[2*j+i/8]);
    else canput=((mat[j]>>(7-i))&1);
    if(canput)
    {fix_length=(text_flag&&text_h==14);
     putpixel(i+x+fix_length+slant,y+j,color);
    }
   }
  }
  if(text_flag)
  {s+=2;
   if(TEXT_DIRECTION)x+=text_h+2;
   else y+=text_h+2;
  }
  else
  {s++;
   if(TEXT_DIRECTION)
   {if(TEXT_SIZE==TX_BIG)x+=9;
    else x+=8;
   }
   else y+=text_h+2;
  }
 }
}

void boxputs256(char *s,int x0,int y0,char texts_width,char texts_height,unsigned char color)
/*区域显示汉字的函数，显示*s所指字符串最多texts_heigth行，每行texts_width个汉字*/
{unsigned char workline[81]={0},flag,i,h,count=0;
 if(TEXT_DIRECTION==0)return;		/*暂时不支持汉字竖排*/
 switch(TEXT_SIZE)
 {case TX_NORMAL:h=20;break;
  case TX_BIG:h=24;break;
  case TX_SMALL:h=9;
 }
 while(1)
 {if(count+1>texts_height)return;	/*超出输出高则跳出*/
  memcpy(workline,s,texts_width);
  for(i=0;i<texts_width;i++)
   if(workline[texts_width-i-1]<128)break;
  if(i%2)	/*半汉字字符修正*/
  {s+=texts_width-1;
   workline[texts_width-1]=0;
  }
  else s+=texts_width;
  puts256(workline,x0,y0+count*h,color);
  count++;
  for(i=0;i<texts_width-1;i++)if(workline[i]==0)return;	/*为结束行则跳出*/
 }
}

unsigned char boxput_height(unsigned char *s,char texts_width)
/*预测用boxput256输出*s所指字符串占用行数(不限制行数时)*/
{char i,temp=0;
 while(1)
 {if(*s==0)return(temp);
  temp++;
  for(i=0;i<texts_width;i++)if(s[i]==0)return(temp);
  for(i=0;i<texts_width-1;i++)
   if(s[texts_width-i-1]<128)break;
  if(i%2)s+=texts_width-1;
  else s+=texts_width;
 }
}

int printf256(int x,int y,unsigned char color,char *format, ...)
/*格式化输出字符串，可变参数使用方式与printf相同，返回格式化后的字符串长度
  但有些控制位置的字符如"\n","\t"等无法正常显示，格式化后最长容纳255字节信息
  如使用 printf256(200,200,255,"%d+%d=%d",10,15,25);
  则在以屏幕点(200,200)为左上角输出255号色(白色)字符串"10+15=25"
*/
{char buffer[256];
 va_list argptr;
 int count;
 va_start(argptr,format);
 count=vsprintf(buffer,format,argptr);
 va_end(argptr);
 puts256(buffer,x,y,color);
 return(count);
}
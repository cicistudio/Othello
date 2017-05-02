#define TX_NORMAL 12	/*��ͨ����*/
#define TX_BIG 16	/*������*/
#define TX_SMALL 8	/*С����*/
char TEXT_SIZE=TX_NORMAL;	/*�����־*/

char TEXT_DIRECTION=1;		/*���ֱ�־��1Ϊ���ţ�0Ϊ����*/

#define SL_NONE 0	/*���ֲ���б*/
#define SL_LEFT 1	/*��������*/
#define SL_RIGHT -1	/*��������*/
char TEXT_SLANT=SL_NONE;	/*������б:����б*/

void puts256(unsigned char *s,int x,int y,int color)
/*��ʾ��ɫ���֣���*s��ָ���ַ��������(x,y)Ϊ���϶����λ�ã���֧��3������*/
{char text_flag,fix_length=0,th,tw,i,j,mat[32]={0},canput,text_h,slant;
 long position;
 unsigned char qh,wh,*p,far *ROM;
 unsigned long HZK_DATA=0;
 switch(TEXT_SIZE)		/*ȷ��ʹ�õ�ROM�ַ�������ĺ��ֿ�����*/
 {case TX_NORMAL:ROM=ROM14;HZK_DATA=HZK12_DATA;text_h=14;break;
  case TX_BIG   :ROM=ROM16;HZK_DATA=HZK16_DATA;text_h=16;break;
  case TX_SMALL :ROM=ROM8;text_h=8;	/*��ROM�ַ���ƥ���人������*/
 }
 while(*s!=0)
 {if(*s>0xa0&&*(s+1)>0xa0)
  {if(HZK_DATA>0)		/*�Ѽ�����ӦHZK*/
   {tw=16;th=TEXT_SIZE;
    qh=*s-0xa0;
    wh=*(s+1)-0xa0;
    position=(94*(qh-1)+(wh-1))*2l*th;
    MemCopy256(HZK_DATA+position,mat,th*2,2);
   }
   else memset(mat,0,32);
   text_flag=1;			/*�����־Ϊ����*/
  }
  else
  {tw=8;th=text_h;
   memcpy(mat,ROM+(*s)*text_h,text_h);
   text_flag=0;			/*�����־ΪӢ����ĸ*/
  }
  slant=0;
  for(j=0;j<th;j++)
  {if(!(j%4))slant+=TEXT_SLANT;	/*�������ֵ���б*/
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
/*������ʾ���ֵĺ�������ʾ*s��ָ�ַ������texts_heigth�У�ÿ��texts_width������*/
{unsigned char workline[81]={0},flag,i,h,count=0;
 if(TEXT_DIRECTION==0)return;		/*��ʱ��֧�ֺ�������*/
 switch(TEXT_SIZE)
 {case TX_NORMAL:h=20;break;
  case TX_BIG:h=24;break;
  case TX_SMALL:h=9;
 }
 while(1)
 {if(count+1>texts_height)return;	/*���������������*/
  memcpy(workline,s,texts_width);
  for(i=0;i<texts_width;i++)
   if(workline[texts_width-i-1]<128)break;
  if(i%2)	/*�뺺���ַ�����*/
  {s+=texts_width-1;
   workline[texts_width-1]=0;
  }
  else s+=texts_width;
  puts256(workline,x0,y0+count*h,color);
  count++;
  for(i=0;i<texts_width-1;i++)if(workline[i]==0)return;	/*Ϊ������������*/
 }
}

unsigned char boxput_height(unsigned char *s,char texts_width)
/*Ԥ����boxput256���*s��ָ�ַ���ռ������(����������ʱ)*/
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
/*��ʽ������ַ������ɱ����ʹ�÷�ʽ��printf��ͬ�����ظ�ʽ������ַ�������
  ����Щ����λ�õ��ַ���"\n","\t"���޷�������ʾ����ʽ���������255�ֽ���Ϣ
  ��ʹ�� printf256(200,200,255,"%d+%d=%d",10,15,25);
  ��������Ļ��(200,200)Ϊ���Ͻ����255��ɫ(��ɫ)�ַ���"10+15=25"
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
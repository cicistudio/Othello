void go_inout(int color,long timedelay,char w)
/*ͼ��ĵ����뵭����colorΪĿ����ɫ��w=0Ϊ���룬w=1Ϊ����*/
{register int n,k=0;
 register char target_rgb[256][3],turn_rgb[256][3],
 r,g,b;
 for(r=0;r<64;r+=9)	/*���ԭDACɫ��*/
  for(g=0;g<64;g+=9)
   for(b=0;b<64;b+=21)
   {target_rgb[k][0]=r;
    target_rgb[k][1]=g;
    target_rgb[k][2]=b;
    k++;
   }
 r=target_rgb[color][0];
 g=target_rgb[color][1];
 b=target_rgb[color][2];
 for(k=0;k<256;k++)		/*����򵭳�ɫ���*/
 {turn_rgb[k][0]=(r-target_rgb[k][0])/9;
  turn_rgb[k][1]=(g-target_rgb[k][1])/9;
  turn_rgb[k][2]=(b-target_rgb[k][2])/21;
  if(w)
  {turn_rgb[k][0]=-turn_rgb[k][0];
   turn_rgb[k][1]=-turn_rgb[k][1];
   turn_rgb[k][2]=-turn_rgb[k][2];
  }
 }
 if(w)
  for(k=0;k<256;k++)
  {target_rgb[k][0]=r;
   target_rgb[k][1]=g;
   target_rgb[k][2]=b;
  }
 for(n=1;n<19;n++)
 {for(k=0;k<256;k++)
  {if(n%6!=0)target_rgb[k][2]+=turn_rgb[k][2];
   else target_rgb[k][2]+=turn_rgb[k][2]*2;
   if(n%2!=0)
   {target_rgb[k][1]+=turn_rgb[k][1]/2;target_rgb[k][0]+=turn_rgb[k][0]/2;}
   else
   {target_rgb[k][1]+=(turn_rgb[k][1]-turn_rgb[k][1]/2);
    target_rgb[k][0]+=(turn_rgb[k][0]-turn_rgb[k][0]/2);
   }
   outportb(0x3c8,k);
   outportb(0x3c9,target_rgb[k][0]);
   outportb(0x3c9,target_rgb[k][1]);
   outportb(0x3c9,target_rgb[k][2]);
  }
  delay(timedelay);	/*��ʱ*/
 }
}

void PrintScreen(char *bmpfile)/*ȫ��ͼ�����ΪBMPͼ�񱣴�*/
{int n,fp;
 const unsigned char head[]={66,77,54,180,4,0,0,0,0,0,54,4,0,0,40,0,0,0,128,2,0,0,224,1,0,0,
 1,0,8,0,0,0,0,0,0,176,4,0,196,14,0,0,196,14,0,0,0,0,0,0,0,0,0,0};/*�����Ϣͷ*/
 unsigned char buffer[1024]={0},dac[768];
 if((fp=open(bmpfile,O_CREAT|O_WRONLY,0x0100|0x0080))==-1)return;
 _write(fp,head,sizeof(head));/*д640*480 256color BMP�ļ�ͷ*/
 getpalette(dac);
 for(n=255;n>=0;n--)
 {buffer[n*4]=dac[n*3+2]<<2;
  buffer[n*4+1]=dac[n*3+1]<<2;
  buffer[n*4+2]=dac[n*3]<<2;
 }
 _write(fp,buffer,1024);/*д��ǰϵͳ��ɫ��*/
 for(n=479;n>=0;n--)
 {MemCopy256(640l*n,buffer,640,2);/*ȡ��Ļ���ݵ�buffer*/
  _write(fp,buffer,640);/*дһɨ��������*/
 }
 _close(fp);
}
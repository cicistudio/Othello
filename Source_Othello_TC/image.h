void LoadDAC(char *bmpfile)	/*��bmpfile�ļ���ɫ������ϵͳ��ɫ��*/
{unsigned char buffer[1024],dac[768]={0};
 int n,fp;
 if((fp=_open(bmpfile,1))==-1)return;	/*����ʧ���򷵻�*/
 _read(fp,&n,2);
 if(n!=19778)goto OUT;/*����ļ���־����BMP�򷵻�*/
 lseek(fp,28,SEEK_SET);
 _read(fp,&n,2);
 if(n!=8)goto OUT;/*�ļ�����256ɫλͼ�򷵻�*/
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
{int width;/*ͼ���*/
 int height;/*ͼ���*/
 char type;/*����λͼ���ͣ�'B'Ϊ256ɫλͼ��'M'Ϊ2ɫ����λͼ*/
 unsigned long ems_offset;/*EMS����λ��*/
}
Bmp256;/*256ɫBMP��������*/

Bmp256 LoadImage(char* datfile)
/*����256ɫλͼ���ݵ�EMS*/
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
/*����BMPͼ�����ݵ�EMS*/
{int color_depth,n,k,length,fp;
 unsigned char *buffer;
 Bmp256 bmp={0};
 if((fp=_open(bmpfile,1))==-1)return(bmp);/*������ļ�ʧ����ͼ���СΪ0������ָ��Ϊ0*/
 _read(fp,&n,2);/*��ȡ����ǩ��*/
 if(n!=19778)goto OUT;/*���ļ�����ǩ������BM��Ϊ��ʧ��*/
 lseek(fp,28,SEEK_SET);
 _read(fp,&color_depth,2);/*���ɫ��*/
 if(!(color_depth==1||color_depth==8))goto OUT;/*��ɫ���ҲΪ��ʧ��*/
 if(color_depth==8)bmp.type='B';else bmp.type='M';/*��ʶ������λͼ��������*/
 lseek(fp,18,SEEK_SET);
 _read(fp,&bmp.width,2);/*��ȡͼƬ��*/
 lseek(fp,2,SEEK_CUR);
 _read(fp,&bmp.height,2);/*��ȡͼƬ��*/
 lseek(fp,0,SEEK_END);
 bmp.ems_offset=BmpStackPos;
 if(color_depth==1)length=bmp.width/8+(bmp.width%8!=0);
 else length=bmp.width;
 buffer=malloc(length);
 k=(length%4)?(4-length%4):0; /*�������ֵ*/
 for(n=0;n<bmp.height;n++)
 {lseek(fp,-k-length,SEEK_CUR);
  _read(fp,buffer,length);/*��ȡ������buffer*/
  MemCopy256(BmpStackPos,buffer,length,0);/*buffer��������EMS*/
  BmpStackPos+=length;/*��EMSͼ������ջβ����ʼ�������*/
  lseek(fp,-length,SEEK_CUR);
 }
 OUT:
 close(fp);
 return(bmp);
}

void PutImage(int x,int y,Bmp256 bmp,int mode)
/*���λͼ����(x,y)Ϊ���ϽǶ��������mode�������ü�emsbytecopy*/
{register int i,j;
 register long n=0;
 if(bmp.type!='B')return;	/*���ͼ��*/
 for(j=0;j<bmp.height;j++)
  for(i=0;i<bmp.width;i++,n++)
  {if(i+x<screen_cut.left||i+x>screen_cut.right||j+y<screen_cut.top||j+y>screen_cut.bottom)continue;
   if(SurfaceMode)	/*�޻���ҳ��ֱ���������Ļ*/
    byte_emstov((j+y)*640l+i+x,bmp.ems_offset+n,mode);
   else			/*������ҳ�������EMS����ҳ*/
    emsbytecopy((j+y)*640l+i+x,bmp.ems_offset+n,mode);
  }
}

void QPutImage(int x,int y,Bmp256 bmp)
/*������ʾλͼ���������λͼ����(x,y)Ϊ���ϽǶ��������ֻ�ܿ������*/
{register int j,scan_seek=0,scan_length;
 if(bmp.type!='B')return;	/*���ͼ��*/
 if(x+bmp.width<screen_cut.left||x>screen_cut.right)return;
 if(x<screen_cut.left)scan_seek=screen_cut.left-x;
 if(x+bmp.width>screen_cut.right)scan_length=screen_cut.right-scan_seek-x+1;
 else scan_length=bmp.width-scan_seek;
 for(j=0;j<bmp.height;j++)
 {if(j+y<screen_cut.top||j+y>screen_cut.bottom)continue;
  if(SurfaceMode)	/*�޻���ҳ��ֱ���������Ļ*/
   scanline_copy((j+y)*640l+x+scan_seek,bmp.ems_offset+(long)j*bmp.width+scan_seek,scan_length,1);
  else			/*������ҳ�������EMS����ҳ*/
   emsblockcopy((j+y)*640l+x+scan_seek,bmp.ems_offset+(long)j*bmp.width+scan_seek,scan_length);
 }
}

void PutMask(int x,int y,Bmp256 bmp,unsigned char color)
/*�������������λͼbmp����(x,y)Ϊ���Ͻǵ�λ�ã���ɫΪcolor��Ҳ�������õ�ģʽPIXEL_MODE��������Ч��*/
{register int i,j,k,w,fix,n,c;
 register unsigned long datapos=bmp.ems_offset;
 register unsigned int nowEmap;
 if(bmp.type!='M')return;	/*���ͼ��*/
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
{int x,y;			/*�������Ͻ���Ļ����λ��*/
 int width,height;		/*����Ŀ���*/
 unsigned char active;		/*�Ƿ񼤻�(�Ƿ���Ӧshow_animate)*/
 unsigned char autoplaying;	/*�Ƿ�ÿ��ʾһ�����Զ������ڲ���ʱ��*/
 unsigned char nowplaying;	/*��ǰ����֡*/
 unsigned char framecount;	/*������֡��*/
 unsigned int timedelay;	/*ÿ���֡�����ʱ(ʹ��show_animate���ٴ������һ֡)*/
 unsigned int timetick;		/*�����ڲ���show_animate������*/
 unsigned char maskcolor;	/*Ҫ����Ϊ͸����ɫ*/
 Bmp256 bmp;			/*bmpͼ������*/
}
Animate256;			/*256ɫ�򵥶�����������*/

void initanimate(Animate256 *animate,int startx,int starty,unsigned char framecount,unsigned int timedelay,unsigned char maskcolor,char *datfile)
/*��ʼ���������󣬲�������Ϊ����������������Ļ����(x,y)����֡����֡�����ʱ��������ɫ�������ļ�*/
{animate->x=startx;animate->y=starty;
 animate->autoplaying=1;		/*�����ڲ���ʱ��*/
 animate->nowplaying=0;		/*��ʼ��ʱ�ӵ�һ֡��ʼ����*/
 animate->framecount=framecount;
 animate->timedelay=timedelay;
 animate->timetick=0;
 animate->active=1;		/*��ʼ��ʱ�����Ѽ���(������ʾ����Ļ)*/
 animate->maskcolor=maskcolor;	/*����͸����ɫ*/
 animate->bmp=LoadBMP(datfile);
 animate->width=animate->bmp.width/framecount;
 animate->height=animate->bmp.height;
}

void showanimate(Animate256 *animate)	/*ʹ������(͸��ɫ)ˢ�¶������嵽��Ļ*/
{register int i,j,width=animate->bmp.width/animate->framecount;
 register long n=0;
 if(!animate->active|animate->bmp.type!='B')return;	/*δ�����򲻻���ͼ����������ͼ��*/
 n+=(width*animate->nowplaying);
 for(j=0;j<animate->bmp.height;j++)
 {for(i=0;i<width;i++,n++)
  {if(i+animate->x<screen_cut.left||i+animate->x>screen_cut.right||
      j+animate->y<screen_cut.top||j+animate->y>screen_cut.bottom)continue;
   if(SurfaceMode)	/*�޻���ҳ��ֱ���������Ļ*/
    byte_emstov((j+animate->y)*640l+i+animate->x,animate->bmp.ems_offset+n,animate->maskcolor);
   else			/*������ҳ�������EMS����ҳ*/
    emsbytecopy((j+animate->y)*640l+i+animate->x,animate->bmp.ems_offset+n,animate->maskcolor);
  }
  n+=(width*(animate->framecount-1));
 }
 if(!animate->autoplaying)return;	/*δ�����ڲ��������򲻼���*/
 if(animate->timetick==animate->timedelay-1)	/*δ�ﵽ��֡����ʱ���򲻸���֡*/
 {animate->nowplaying=(animate->nowplaying+1)%animate->framecount;animate->timetick=0;}
 else animate->timetick++;
}

void Qshowanimate(Animate256 *animate)
/*��ʹ������ˢ�����嵽��Ļ���ٶȽ�showanimate��*/
{register int j,scan_seek=0,scan_length,width=animate->bmp.width/animate->framecount;
 if(!animate->active|animate->bmp.type!='B')return;	/*δ�����򲻻���ͼ����������ͼ��*/
 if(animate->x+width<screen_cut.left||animate->x>screen_cut.right)return;
 if(animate->x<screen_cut.left)scan_seek=screen_cut.left-animate->x;
 if(animate->x+width>screen_cut.right)scan_length=screen_cut.right-scan_seek-animate->x+1;
 else scan_length=width-scan_seek;
 for(j=0;j<animate->bmp.height;j++)
 {if(j+animate->y<screen_cut.top||j+animate->y>screen_cut.bottom)continue;
  if(SurfaceMode)	/*�޻���ҳ��ֱ���������Ļ*/
   scanline_copy((j+animate->y)*640l+animate->x+scan_seek,animate->bmp.ems_offset+(long)j*animate->bmp.width+(long)width*(animate->nowplaying)+scan_seek,scan_length,1);
  else			/*������ҳ�������EMS����ҳ*/
   emsblockcopy((j+animate->y)*640l+animate->x+scan_seek,animate->bmp.ems_offset+(long)j*animate->bmp.width+(long)width*(animate->nowplaying)+scan_seek,scan_length);
 }
 if(animate->timetick==animate->timedelay)	/*δ�ﵽ��֡����ʱ���򲻸���֡*/
 {animate->nowplaying=(animate->nowplaying+1)%animate->framecount;animate->timetick=0;}
 else animate->timetick++;
}

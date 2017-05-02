char far *EmsPoint;
unsigned char emm_name[]="EMMXXXX0",emm_alloc=0,EMS_ERR=0;
unsigned int emm_handle;
unsigned int lastEmap[4];

err_table[]={03,04,15,15,15,6,10,7,7,8,11,15,12,13,14};

int ememavail(void)
/*����EMS�Ƿ����(EMM386.exe�Ѽ���)*/
{union REGS in,out;
 unsigned char far *emm;
 emm=(unsigned char far *)(0x67*4+2);
 emm=MK_FP(*((unsigned int *)emm),0xA);
 if(memcmp(emm_name,emm,8))
 {EMS_ERR=1;return(0);}
 in.h.ah=0x42;
 int86(0x67,&in,&out);
 if(out.h.ah)
 {err_rtn(out.h.ah);return(0);}
 if(out.x.dx)
 {EMS_ERR=0;return(out.x.dx);}
 else{EMS_ERR=2;return(0);}
}

err_rtn(unsigned char ah)
{if(!ah)
 {EMS_ERR=0;return;}
 EMS_ERR=err_table[ah&0x80];
}

char far *ealloc(unsigned int pages)
/*����EMSҳ����*/
{union REGS in,out;
 if(emm_alloc)
 {EMS_ERR=5;return(NULL);}
 in.h.ah=0x43;
 in.x.bx=pages;
 int86(0x67,&in,&out);
 if(out.h.ah)
 {err_rtn(out.h.ah);return(NULL);}
 emm_alloc=1;
 emm_handle=out.x.dx;
 in.h.ah=0x41;
 int86(0x67,&in,&out);
 if(out.h.ah)
 {err_rtn(out.h.ah);return(NULL);}
 EMS_ERR=0;
 return(MK_FP(out.x.bx,0x0));
}

int efree(void)
/*�ͷ�EMS*/
{union REGS in,out;
 if(!emm_alloc)
 {EMS_ERR=9;return(-1);}
 in.h.ah=0x45;
 in.x.dx=emm_handle;
 int86(0x67,&in,&out);
 if(out.h.ah)
 {err_rtn(out.h.ah);return(-1);}
 emm_alloc=0;
 EMS_ERR=0;
 return(0);
}

int emap(unsigned int pageno,unsigned char n)
/*ӳ��16kEMSҳ������ҳ��nΪ����ҳƫ��(ȡ0-3����4ҳ)*/
{union REGS in,out;
 if(!emm_alloc)
 {EMS_ERR=9;return(-1);}
 if(pageno==65535)return(0);
 in.h.ah=0x44;
 in.h.al=n;
 in.x.bx=pageno;
 in.x.dx=emm_handle;
 int86(0x67,&in,&out);
 if(out.h.ah)
 {err_rtn(out.h.ah);return(-1);}
 else
 {lastEmap[n]=pageno;
  return(0);
 }
}

void show_ems_error(void)/*��ʾEMS������Ϣ*/
{switch(EMS_ERR)
 {case 0 :puts("No error.");break;
  case 1 :puts("Expanded memory not installed.");break;
  case 2 :puts("No free expanded memory pages.");break;
  case 3 :puts("Software mal function.");break;
  case 4 :puts("Hardware mal function.");break;
  case 5 :puts("EMS memory already allocated by this process");break;
  case 6 :puts("No EMM handles free.");break;
  case 7 :puts("Insufficient EMS pages to fill request.");break;
  case 8 :puts("Attempt to allocated 0 pages.");break;
  case 9 :puts("EMS memory not available.");break;
  case 10:puts("'esave' called without subsequent 'erestore'.");break;
  case 11:puts("Logical page out of range allocated to process.");break;
  case 12:puts("No room in save area.");break;
  case 13:puts("'save' already called by process.");break;
  case 14:puts("'erestore' called without prior 'esave'.");break;
  case 15:puts("Unidentified error.");
 }
}

void initems(void)/*EMS��ʼ��*/
{int n;
 if(!ememavail())
 {show_ems_error();exit(0);}
 EmsPoint=ealloc(512);		/*����8M EMS�ڴ棬ealloc����ֵ���Ը���ϵͳ�ڴ�����Ϊ�������*/
 if(EMS_ERR)
 {show_ems_error();exit(0);}
 for(n=0;n<4;n++)
  emap(n,n);
}

#define COPY_PUT -1	/*ֱ�Ӵ���*/
#define INVERT_PUT -2	/*ȡ������*/
#define OR_PUT -3	/*��Ŀ�ꡰ�򡱲���*/
#define AND_PUT -4	/*��Ŀ�ꡰ�롱����*/
#define XOR_PUT -5	/*��Ŀ�ꡰ��򡱲���*/

void emsbytecopy(unsigned long desc,unsigned long src,int mode)
/*
  EMS���ͼ�������ֽڴ��亯����desc(Ŀ��)��src(Դ)��Ϊ�����EMS���ƫ��
  mode��������
  mode>=0	:ʹ��mode��ɫ���루���˵�mode��ɫ��
  mode=COPY_PUT	:ֱ�Ӵ��䣨Ҳ���Ի�OR_PUT�ȣ�
*/
{register unsigned int descmap=desc>>14,descoffset=desc&0x3fff,
		       srcmap=src>>14,srcoffset=src&0x3fff;
 register unsigned char c1,c2;
 if(lastEmap[0]!=descmap)emap(descmap,0);
 if(lastEmap[1]!=srcmap)emap(srcmap,1);
 c1=*(EmsPoint+descoffset);
 c2=*(EmsPoint+16384+srcoffset);
 if(mode>=0)
 {if(c2!=mode)
   *(EmsPoint+descoffset)=c2;
 }
 else
  switch(mode)
  {case COPY_PUT	:*(EmsPoint+descoffset)=c2;break;
   case INVERT_PUT	:*(EmsPoint+descoffset)=~c2;break;
   case OR_PUT		:*(EmsPoint+descoffset)=c1|c2;break;
   case AND_PUT		:*(EmsPoint+descoffset)=c1&c2;break;
   case XOR_PUT		:*(EmsPoint+descoffset)=c1^c2;
  }
}

void MyEmap1(unsigned int ems2map,char mode)
{if(mode)
 {if(ems2map*2!=lastEmap[2])emap(ems2map*2,2);
  if(ems2map*2+1!=lastEmap[3])emap(ems2map*2+1,3);
 }
 else
 {if(ems2map*2!=lastEmap[0])emap(ems2map*2,0);
  if(ems2map*2+1!=lastEmap[1])emap(ems2map*2+1,1);
 }
}

void emsblockcopy(unsigned long desc,unsigned long src,unsigned long length)
/*EMS�鿽�����亯����descΪ�����EMS���ƫ��*/
{unsigned int descoffset=desc&0x7fff,srcoffset=src&0x7fff;
 unsigned int desc2map=desc>>15,src2map=src>>15;
 MyEmap1(desc2map,0);MyEmap1(src2map,1);
 if(descoffset==srcoffset)	/*�������Դ��offset��ͬ�����*/
 {unsigned int headpart;
  headpart=32768-descoffset;
  if(headpart>=length)
  {memcpy(EmsPoint+descoffset,EmsPoint+32768+descoffset,length);return;}
  memcpy(EmsPoint+descoffset,EmsPoint+32768+descoffset,headpart);
  length-=headpart;
  desc2map++;src2map++;
  while(length>0)
  {MyEmap1(desc2map,0);MyEmap1(src2map,1);
   if(length<32768)
   {memcpy(EmsPoint,EmsPoint+32768,length);return;}
   memcpy(EmsPoint,EmsPoint+32768,32768);
   length-=32768;
   desc2map++;src2map++;
  }
 }
 else		/*�������Դ��offset��ͬ�����*/
 {unsigned int flag,passed_length;
  if(descoffset+length<=32768l&&srcoffset+length<=32768l)
  {memcpy(EmsPoint+descoffset,EmsPoint+32768+srcoffset,length);
   return;
  }
  if(descoffset>srcoffset)flag=1;	/*˵��Դoffsetʣ��ı�Ŀ��offset��*/
  else flag=0;
  while(length>0)
  {if(flag)passed_length=32768-descoffset;
   else passed_length=32768-srcoffset;
   if(length<passed_length)passed_length=length;
   memcpy(EmsPoint+descoffset,EmsPoint+32768+srcoffset,passed_length);
   if(flag)
   {srcoffset+=passed_length;
    descoffset=0;
    desc2map++;
    MyEmap1(desc2map,0);
   }
   else
   {descoffset+=passed_length;
    srcoffset=0;
    src2map++;
    MyEmap1(src2map,1);
   }
   length-=passed_length;
   flag=!flag;
  }
 }
}

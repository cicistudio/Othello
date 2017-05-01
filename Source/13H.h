# define  BYTE         unsigned char
# define  BOOL         BYTE
# define  WORD         unsigned int
# define  DWORD        unsigned long
# define  TRUE         1
# define  FALSE        !TRUE

/* BIOS 8*8 �����ֿ�Ķε�ַ��ƫ���� */
WORD FONT_SEG;
WORD FONT_OFF;

/* ��ʾ��̨�ҳ��ַ */
void far * Video;

/* ��ȡBIOS 8*8 �����ֿ�Ķε�ַ��ƫ���� */
void GetFontAdd()
{
  struct REGPACK regs;
  regs.r_bx=0x0300;
  regs.r_ax=0x1130;
  intr(0x10,&regs);
  FONT_SEG=regs.r_es;
  FONT_OFF=regs.r_bp;
}

/* ���̨�ҳд���� */
void Pset(int x,int y,BYTE color)
{
  if ((x>=0)&&(x<320)&&(y>=0)&&(y<200))
     *((BYTE far*)Video+y*320+x)=color;
}

/* �ȴ��������� */
void wait()
{
  _AX=0;
  geninterrupt(0x16);
}

/* ����VGA 13Hģʽ */
void setmode2()
{
  _AX=0x13;
  geninterrupt(0x10);
  GetFontAdd();
}

/* �����ı�ģʽ */
void closemode()
{
  _AX=0x3;
  geninterrupt(0x10);
}

/* ���õ�ɫ�� */
void setpal(int Color,BYTE r,BYTE g,BYTE b)
{
  outportb(0x3c8,Color);
  outportb(0x3c9,r);
  outportb(0x3c9,g);
  outportb(0x3c9,b);
}

/* ��Ļ��λ����������ַ���*/
void locate(int Line,int Col)
{
  _DH=Line;
  _DL=Col;
  _AH=2;
  _BX=0;
  geninterrupt(0x10);
}

/* �Ӽ��̻�������ֱ�Ӷ���ɨ���� */
BYTE ScanKey(void)
{
  int  start,end;
  WORD key=0;
  start=peek(0,0x41a);
  end=peek(0,0x41c);
  if (start==end) return(0);
  else
  {
    key=peek(0x40,start);
    start+=2;
    if (start==0x3e) start=0x1e;
    poke(0x40,0x1a,start);
    return(key/256);
  }
}


/* ˢ����Ļ */
void ReFresh(void)
{
  movedata(FP_SEG(Video),FP_OFF(Video),0xa000,0,64000);
}

/* ����ַ�����ʾ��̨�ҳ */
void OutChar(int x0,int y0,int ch,BYTE Color)
{
  int  x,y;
  BYTE c;
  for (y=0;y<8;y++)
  {
      c=peekb(FONT_SEG,FONT_OFF+ch*8+y);
      for (x=0;x<8;x++)
      {
          if (c&(1<<(7-x))) Pset(x+x0*8,y+y0*8,Color);
      }
  }
}

/* ����ַ�������ʾ��̨�ҳ */
void OutString(int x,int y,char *p,BYTE Color)
{
  while (*p)
  {
    OutChar(x++,y,*p++,Color);
    if (x==40)
    {
       x=0;
       y++;
    }
  }
}
/* �ڣ�X��Y������� */

void pset(int x,int y,BYTE color)
{
  pokeb(0xa000,y*320+x,color);
}

/* ȡ��X��Y������ɫ */
BYTE point(int x,int y)
{
  return peekb(0xa000,y*320+x);
}


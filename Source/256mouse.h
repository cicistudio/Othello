#define mbLeft 0
#define mbRight 1

char MouseOnShow=0;

typedef
struct
{char hotpoint_x;
 char hotpoint_y;
 unsigned char maskcolor;
 unsigned char mask[24][24];
} c_cursor;

static c_cursor DEFAULT_CURSOR=
{  0,  0,
  28,
  28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28,  0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28,  0,  0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28,  0,145,  0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28,  0,255,146,  0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28,  0,255,146,109,  0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28,  0,255,255,146,146,  0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28,  0,255,255,109,146,109,  0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28,  0,255,255,255,109,146,146,  0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28,  0,255,255,255,146,109,146,109,  0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28,  0,255,255,255,255,146,109,146,146,  0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28,  0,255,255,255,255,109,  0,  0,  0,  0,  0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28,  0,255,255,  0,255,255,  0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28,  0,255,  0, 28,  0,255,255,  0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28,  0,  0, 28, 28,  0,255,255,  0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28,  0, 28, 28, 28, 28,  0,255,255,  0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28, 28, 28, 28, 28, 28,  0,255,255,  0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28, 28, 28, 28, 28, 28, 28,  0,255,255,  0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28, 28, 28, 28, 28, 28, 28,  0,255,255,  0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28, 28, 28, 28, 28, 28, 28, 28,  0,  0, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
  28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
};

static c_cursor HAND_CURSOR=
{  6,  0,
  29,
  29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
  29, 29, 29, 29, 29, 29,  0,  0, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
  29, 29, 29, 29, 29,  0,255,255,  0, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
  29, 29, 29, 29, 29,  0,255,255,  0, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
  29, 29, 29, 29, 29,  0,255,255,  0, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
  29, 29, 29, 29, 29,  0,255,255,  0, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
  29, 29, 29, 29, 29,  0,255,255,  0,  0,  0, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
  29, 29, 29, 29, 29,  0,255,255,  0,255,255,  0,  0,  0, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
  29, 29, 29, 29, 29,  0,255,255,  0,255,255,  0,255,255,  0,  0, 29, 29, 29, 29, 29, 29, 29, 29,
  29, 29, 29, 29, 29,  0,255,255,  0,255,255,  0,255,255,  0,255,  0, 29, 29, 29, 29, 29, 29, 29,
  29,  0,  0,  0, 29,  0,255,255,  0,255,255,  0,255,255,  0,255,255,  0, 29, 29, 29, 29, 29, 29,
  29,  0,255,255,  0,  0,255,255,255,255,255,255,255,255,  0,255,255,  0, 29, 29, 29, 29, 29, 29,
  29,  0,255,255,255,  0,255,255,255,255,255,255,255,255,255,255,255,  0, 29, 29, 29, 29, 29, 29,
  29, 29,  0,255,255,  0,255,255,255,255,255,255,255,255,255,255,255,  0, 29, 29, 29, 29, 29, 29,
  29, 29, 29,  0,255,  0,255,255,255,255,255,255,255,255,255,255,255,  0, 29, 29, 29, 29, 29, 29,
  29, 29, 29,  0,255,255,255,255,255,255,255,255,255,255,255,255,255,  0, 29, 29, 29, 29, 29, 29,
  29, 29, 29, 29,  0,255,255,255,255,255,255,255,255,255,255,255,255,  0, 29, 29, 29, 29, 29, 29,
  29, 29, 29, 29,  0,255,255,255,255,255,255,255,255,255,255,255,  0, 29, 29, 29, 29, 29, 29, 29,
  29, 29, 29, 29, 29,  0,255,255,255,255,255,255,255,255,255,255,  0, 29, 29, 29, 29, 29, 29, 29,
  29, 29, 29, 29, 29,  0,255,255,255,255,255,255,255,255,255,255,  0, 29, 29, 29, 29, 29, 29, 29,
  29, 29, 29, 29, 29, 29,  0,255,255,255,255,255,255,255,255,  0, 29, 29, 29, 29, 29, 29, 29, 29,
  29, 29, 29, 29, 29, 29,  0,255,255,255,255,255,255,255,255,  0, 29, 29, 29, 29, 29, 29, 29, 29,
  29, 29, 29, 29, 29, 29,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 29, 29, 29, 29, 29, 29, 29, 29,
  29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
};

struct
{int x;
 int y;
 int getx;
 int gety;
 c_cursor cur;
 unsigned char buffer[24][24];
}mouse;

void getmousexy(void)	/* 取得鼠标位置 */
{union REGS r;
 r.x.ax=0x3;
 int86(0x33,&r,&r);
 mouse.getx=r.x.cx;
 mouse.gety=r.x.dx;
}

void setmousexy(int x,int y)	/* 设置鼠标位置 */
{union REGS r;
 r.x.ax=0x4;
 r.x.cx=x;
 r.x.dx=y;
 int86(0x33,&r,&r);
}

int getmkeyin(int key)		/* 取得鼠标按键按下信息 0左 1右 */
{union REGS r;
 r.x.ax=0x5;
 r.x.bx=key;
 int86(0x33,&r,&r);
 if(r.x.bx==1)return key;
 else return(key+1);
}

int getmkeyout(int key)		/* 取得鼠标按键抬起信息 0左 1右 */
{union REGS r;
 r.x.ax=0x6;
 r.x.bx=key;
 int86(0x33,&r,&r);
 if(r.x.bx==1) return key;
 else return(key+1);
}

void setmmove(int x1,int y1,int x2,int y2)  /*设置鼠标移动范围  */
{union REGS r;
 r.x.ax=0x7;
 r.x.cx=x1;
 r.x.dx=x2;
 int86(0x33,&r,&r);
 r.x.ax=0x8;
 r.x.cx=y1;
 r.x.dx=y2;
 int86(0x33,&r,&r);
}

void loadcursor(c_cursor cursor)
{if(MouseOnShow)return;
 mouse.cur.hotpoint_x=cursor.hotpoint_x;
 mouse.cur.hotpoint_y=cursor.hotpoint_y;
 mouse.cur.maskcolor=cursor.maskcolor;
 memcpy(mouse.cur.mask,cursor.mask,576);
}

int initmouse(void)       /*  初始化鼠标   */
{int n;
 union REGS r;
 r.x.ax=0x0;
 int86(0x33,&r,&r);
 if (r.x.ax!=0)
 {getmousexy();
  setmmove(0,0,639,479);
  mouse.x=mouse.getx;
  mouse.y=mouse.gety;
  loadcursor(DEFAULT_CURSOR);
  return 1;
 }
 else return 0;
}

void hidemouse(void)
{register int i,j;
 if(SurfaceMode==SINGLE_SURFACE)
 {for(j=0;j<24;j++)
   for(i=0;i<24;i++)
    putpixel(mouse.x+i-mouse.cur.hotpoint_x,mouse.y+j-mouse.cur.hotpoint_y,mouse.buffer[j][i]);/*恢复原图像*/
 }
 else ;
 MouseOnShow=0;
}

void showmouse(void)
{register int i,j;
 getmousexy();
 mouse.x=mouse.getx;
 mouse.y=mouse.gety;
 if(SurfaceMode==SINGLE_SURFACE)
 {for(j=0;j<24;j++)
   for(i=0;i<24;i++)
   {mouse.buffer[j][i]=getpixel(mouse.x+i-mouse.cur.hotpoint_x,mouse.y+j-mouse.cur.hotpoint_y);/*保存新图像*/
    if(mouse.cur.mask[j][i]!=mouse.cur.maskcolor)
     putpixel(mouse.x+i-mouse.cur.hotpoint_x,mouse.y+j-mouse.cur.hotpoint_y,mouse.cur.mask[j][i]);/*绘制鼠标*/
   }
 }
 else ;
 MouseOnShow=1;
}

void changecursor(c_cursor cursor)	/*更改鼠标光标形状*/
{hidemouse();
 loadcursor(cursor);
 showmouse();
}

void drawmouse(void)	/*绘制鼠标光标*/
{getmousexy();
 if(mouse.getx!=mouse.x||mouse.gety!=mouse.y)
 {register int i,j;
  if(SurfaceMode==SINGLE_SURFACE)
  {for(j=0;j<24;j++)
    for(i=0;i<24;i++)
     putpixel(mouse.x+i-mouse.cur.hotpoint_x,mouse.y+j-mouse.cur.hotpoint_y,mouse.buffer[j][i]);/*恢复原图像*/
  }
  else ;
  mouse.x=mouse.getx;
  mouse.y=mouse.gety;
  if(SurfaceMode==SINGLE_SURFACE)
  {for(j=0;j<24;j++)
    for(i=0;i<24;i++)
    {mouse.buffer[j][i]=getpixel(mouse.x+i-mouse.cur.hotpoint_x,mouse.y+j-mouse.cur.hotpoint_y);/*保存新图像*/
     if(mouse.cur.mask[j][i]!=mouse.cur.maskcolor)
      putpixel(mouse.x+i-mouse.cur.hotpoint_x,mouse.y+j-mouse.cur.hotpoint_y,mouse.cur.mask[j][i]);/*绘制鼠标*/
    }
  }
  else ;
 }
}
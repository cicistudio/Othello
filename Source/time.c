# define  MAXTIMER     10

/* 计时器结构 */
struct TM
{
  DWORD Interval;              /*      间隔       */
  DWORD LastTimer;             /* 上次时间发生时间*/
  BOOL  Enable;                /*      活动       */
  BOOL  Used;                  /*      可用       */
  void  (*Pointer)();          /*   事件远指针    */
};

struct TM tmTM[MAXTIMER+1];
int    TimerUsed=0;

/* 获取BIOS计数器数值 */
DWORD BiosTimer(void)
{
  DWORD BIOSTIMER=0;
  BIOSTIMER=peek(0x0,0x46e);
  BIOSTIMER<<=8;
  BIOSTIMER+=peek(0x0,0x46c);
  return (BIOSTIMER);
}

/* 时间事件（时钟系统核心） */
void TimerEvent()
{
  int   i;
  DWORD TimerDiff;

  for (i=1;i<=MAXTIMER;i++)
  {
      if (tmTM[i].Used&&tmTM[i].Enable)
      {
         TimerDiff=BiosTimer()-tmTM[i].LastTimer;
	 if (tmTM[i].Interval<=TimerDiff)
         {
            tmTM[i].Pointer();
            tmTM[i].LastTimer=BiosTimer();
         }
      }
  }
}

/* 创建一个时钟（成功返回时钟的句柄，否则返回NULL） */
int CreateTimer(DWORD Interval,void (*Pointer)())
{
  int i=0;
  if (TimerUsed==MAXTIMER) return NULL;

  while (tmTM[++i].Used);

  tmTM[i].Pointer=Pointer;
  tmTM[i].Interval=Interval;
  tmTM[i].Enable=TRUE;
  tmTM[i].Used=TRUE;
  tmTM[i].LastTimer=BiosTimer();

  TimerUsed++;
  return i;
}

/* 删除一个时钟 */
void KillTimer(int *TimerID)
{
  if (tmTM[*TimerID].Used)
  {
     TimerUsed--;
     tmTM[*TimerID].Used=FALSE;
  }
  *TimerID=0;
}

/* 删除所有时钟 */
void KillAllTimer()
{
  int i;
  for (i=0;i<=MAXTIMER;i++) tmTM[i].Used=FALSE;
  TimerUsed=0;
}
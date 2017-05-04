#include "256basic.h"
/*256色模式工作基本函数头文件*/
#include "256mouse.h"    
/*256色模式下鼠标支持的头文件*/
#include "image.h"    
/*位图图像类型、动画图像类型操作函数库*/
#include "puts256.h"    
/*256色文本操作函数库*/
#include "draw.h"    
/*256色图形绘图函数库*/
#include "do_image.h"    
/*256色图形系统特效函数库*/
#include "slb256.h"     
/*精灵库文件的操作函数库*/
#include "alpha256.h"   
/*ALPHA混合输出函数库*/


#include<dos.h>
#include "13H.h"
/* 300x200 图形显示模式*/
#include<time.h>
#include<stdio.h>
#include "time.c"
#include "alloc.h"
#include "stdlib.h"

#define UP 72 
#define DOWN 80 
#define LEFT 75 
#define RIGHT 77

void choosemode(void);
void gamemain_1(void);
/*人机大战*/
void gamemain_2(void);
/*人人大战*/
void gameend(void);
/*游戏结束*/
void gamemain_new(void);
/*游戏初始化*/
void gamemain_2_game(void);
/*游戏主菜单*/
void gamemain_2_help(void);
/*帮助主菜单*/
int computer_1(int,int);
int computer_1_1(int,int);
int comuter_2_0(int,int);
int computer_2(int,int);
int computer_2_1(int,int);
int computer_3(int,int);
int computer_4(int,int);
int computer_5(int,int);
int computer_6(int,int);
/*电脑智能*/
int changechess(int,int,int,int);
/*电脑翻子判断*/
int xx=0,yy=0 ;
/* 用于标记电脑刚下子的位置*/
int count_step ;
/*每走一步计算机就记一步用于判断游戏结束*/
/*整体算法不够简化，但是更易于维护和思维计算*/

/*最好将资源声明在外部，以便各函数模块都可以使用*/
Bmp256 back ;
Bmp256 askfirst,askend ;
Bmp256 game,help ;
Bmp256 black,white ;
int check=0 ;
/*用于鼠标的指向判断*/
int hei[10][10][2],bai[10][10][2],ren_yiput[10][10][2],cpu_yiput[10][10][2];
/*此数组用于存放已下子地址*/
int canput_hei[10][10][2],canput_bai[10][10][2];
/*此数组用于可放子的地址*/
int canput[10][10][2];
/*此数组用于合并后的可存放地址，电脑下子的地址。具体要存哪一个就要看主函数的判断*/

int flag_changechess=1 ;
/*用于判断人机大战时，电脑先走*/
int flag_whozhizi=1 ;
/*当flag_whozhizi为1时人执黑，否则人执白*/
int flag_cpuyixia=0 ;
/*用于标记电脑是否走子*/
int flag_show=0 ;
/*flag_show用于是否显示标记可填空处*/

BYTE PAL[256][3];
int Step=0 ;
int n=0 ;

/*程晨软件设置的内心表达*/


void choosemode(void)
{
    int i,j ;
    char is_on,key ;
    static char curtype=1,texts[3][16]=
    {
        /*虽然为空但和图片的位置是一直的！*/
        "        ","        ","  " 
    }
    ;
    
    do 
    {
        while(getmkeyin(mbRight)!=mbRight)
        {
            hidemouse();
            QPutImage(0,0,back);
            /*输出背景图*/
            QPutImage(240,150,askfirst);
            /*输出选择模式*/
            /*因为要加载新的鼠标光标图像只有mouse被隐藏后才能进行*/
            /*for(j=0;j<7;j++)
                                                        for(i=0;i<8;i++)       小图片动态显示
                                                        QPutImage(-bk_tc.width+a+i*bk_tc.width,-b+j*bk_tc.height,bk_tc);
                                                        a=(a+1)%bk_tc.width ;
                                                        b=(b+1)%bk_tc.height ; */
            /*TEXT_SIZE=TX_NORMAL ;  12点阵显示*/
            TEXT_SIZE=TX_BIG ;
            /*16点阵显示*/
            getmousexy();
            is_on=-1 ;
            for(i=0;i<2;i++)
            /*当鼠标到什么位置时就将字显时兰色，鼠标点击定位鼠标点击主要是此函数控制*/
            if(mouse.getx>=272&&mouse.getx<=345&&mouse.gety>=200+i*30&&mouse.gety<=216+i*30)
            {
                is_on=i ;
                puts256(texts[i],275,200+i*30,BLUE);
                /*显示要点击的汉字位置*/
                /* line(48,218+i*40,185,218+i*40,BLUE);  再下面画线，表示连接*/
            }
            else puts256(texts[i],275,200+i*30,0);
            
            /*判断差键鼠标点击主要是此函数控制*/
            if(mouse.getx>=357&&mouse.getx<=376&&mouse.gety>=152&&mouse.gety<=171)
            {
                is_on=2 ;
                puts256(texts[2],357,152,BLUE);
            }
            else puts256(texts[2],357,152,0);
            
            if(is_on>=0)
            {
                if(curtype)
                {
                    /* loadcursor(HAND_CURSOR);  */
                    /*加载鼠标光标：3D箭头*/
                    curtype=0 ;
                }
                if(getmkeyin(mbLeft)==mbLeft)
                /*点击鼠标响应代码*/
                switch(is_on)
                {
                    case 0 :
                    gamemain_1();
                    
                    break ;
                    case 1 :
                    gamemain_2();
                    
                    break ;
                    case 2 :
                    gameend();
                    /* show_6_3();  */
                }
            }
            else 
            if(!curtype)
            {
                /*loadcursor(DEFAULT_CURSOR);*/
                /*加载鼠标光标：手形光标*/
                curtype=1 ;
            }
            {
                char s[8];
                /*puts256("鼠标坐标：",330,430,0); */
                printf256(550,460,BLUE,"%4d,%4d",mouse.getx,mouse.gety);
                /*puts256("当前鼠标光标类型：",330,450,0);
                                                                            if(curtype)puts256("DEFAULT_CURSOR",490,450,BLUE);
                                                                            else puts256("HAND_CURSOR",490,450,BLUE); */
            }
            /*if(kbhit())
                                                        {
                                                            key=getch();
                                                            if(key==0)continue ;
                                                            if(key=='a'||key=='A')
                                                            {
                                                               show_6_1();
                                                                continue ;
                                                            }
                                                            if(key=='b'||key=='B')
                                                            {
                                                                show_6_2();
                                                                continue ;
                                                            }
                                                            if(key=='c'||key=='C')
                                                            {
                                                                show_6_3();
                                                                continue ;
                                                            }
                                                            break ;
                                                        } */
            
            showmouse();
            getmkeyin(mbLeft);
            /*取走鼠标缓冲*/
            vpost();
        }
        gameend();
    }
    while(1);
    /*虽然是死循环但是可以在退出函数中退出游戏*/
}


void gameend(void)
{
    int i,j ;
    char is_on,key ;
    static char curtype=1,texts[3][16]=
    {
        /*虽然为空但和图片的位置是一直的！*/
        "        ","        ","  " 
    }
    ;
    
    
    while(getmkeyin(mbRight)!=mbRight)
    {
        hidemouse();
        QPutImage(240,150,askend);
        /*输出选择模式*/
        TEXT_SIZE=TX_BIG ;
        /*16点阵显示*/
        getmousexy();
        is_on=-1 ;
        for(i=0;i<2;i++)
        if(mouse.getx>=272&&mouse.getx<=345&&mouse.gety>=200+i*30&&mouse.gety<=216+i*30)
        {
            is_on=i ;
            puts256(texts[i],275,200+i*30,BLUE);
            /*显示要点击的汉字位置*/
        }
        else puts256(texts[i],275,200+i*30,0);
        
        /*判断差键鼠标点击主要是此函数控制*/
        if(mouse.getx>=357&&mouse.getx<=376&&mouse.gety>=152&&mouse.gety<=171)
        {
            is_on=2 ;
            puts256(texts[2],357,152,BLUE);
        }
        else puts256(texts[2],357,152,0);
        
        if(is_on>=0)
        {
            if(curtype)
            {
                curtype=0 ;
            }
            if(getmkeyin(mbLeft)==mbLeft)
            /*点击鼠标响应代码*/
            switch(is_on)
            {
                case 0 :
                exit(0);
                /* 退出游戏*/
                break ;
                case 1 :
                return(0);
                /*返回游戏*/
                
                case 2 :
                return(0);
                
            }
        }
        else 
        if(!curtype)
        {
            curtype=1 ;
        }
        {
            char s[8];
            /* printf256(550,460,BLUE,"%4d,%4d",mouse.getx,mouse.gety); */
        }
        showmouse();
        getmkeyin(mbLeft);
        vpost();
    }
}




void gamemain_new(void)
{
    int a,b ;
    for(a=0;a<10;a++)
    for(b=0;b<10;b++)
    {
        bai[a][b][0]=0 ;
        hei[a][b][0]=0 ;
        
        ren_yiput[a][b][0]=0 ;
        cpu_yiput[a][b][0]=0 ;
        canput_hei[a][b][0]=0 ;
        canput_bai[a][b][0]=0 ;
        
    }
    bai[4][4][0]=1 ;
    bai[5][5][0]=1 ;
    hei[5][4][0]=1 ;
    hei[4][5][0]=1 ;
    /*数据初始化后再调入主游戏函数*/
    xx=0 ;
    yy=0 ;
    flag_changechess=1 ;
    count_step=0 ;
    flag_whozhizi=1 ;
    choosemode();
}

/*人机大战*/
void gamemain_1(void)
{
    int i,j,a,b,c,d ;
    int flag_heibai=1,flag_pass ;
    int hei_new[10][10][2],bai_new[10][10][2];
    int count_bai,count_hei,count_canput=1,count_canput_bai,count_canput_hei ;
    int count_1,count_2,count_3,count_4,count_5 ;
    int count_mouse_bai,count_mouse_hei ;
    /*主要用于游戏结束判断*/
    /*用于交替使用黑白子*/
    char is_on,key ;
    static char curtype=1,texts[3][16]=
    {
        /*虽然为空但和图片的位置是一直的！*/
        "   ","   ","   " 
    }
    ;
    
    flag_changechess=1 ;
    /*16点阵显示*/
    /*虽然是死循环，但是鼠标点叉后会退出游戏*/
    while(1)
    {
        hidemouse();
        QPutImage(0,0,back);
        /*输出背景图*/
        
        /*输出已标记棋子，及可下子的地方。*/
        for(a=1;a<9;a++)for(b=1;b<9;b++)
        {
            if(hei[a][b][0]==1)
            PutImage(a*41+5,b*40+64,black,28);
            if(bai[a][b][0]==1)
            PutImage(a*41+5,b*40+64,white,28);
            if(flag_show)
            {
                if(canput_hei[a][b][0]==1&&flag_heibai)
                puts256("X",a*41+5+10,b*40+64+10,BLACK);
                if(canput_bai[a][b][0]==1&&!flag_heibai)
                puts256("X",a*41+5+10,b*40+64+10,WHITE);
            }
        }
        
        if(xx&&yy)puts256("★",xx*41+10,yy*40+70,7);
        
        
        /*以下代码为输出黑白子的数量（势力范围）*/
        count_bai=0 ;
        count_hei=0 ;
        count_canput_bai=0 ;
        count_canput_hei=0 ;
        count_1=0 ;
        count_2=0 ;
        count_3=0 ;
        count_4=0 ;
        count_5=0 ;
        flag_pass=1 ;
        
        for(a=1;a<9;a++)
        for(b=1;b<9;b++)
        {
            if(bai[a][b][0]==1)
            count_bai++;
            if(hei[a][b][0]==1)
            count_hei++;
            if(canput_bai[a][b][0]==1)
            count_canput_bai++;
            if(canput_hei[a][b][0]==1)
            count_canput_hei++;
            canput[a][b][0]=0 ;
            /*电脑只需判断一次*/
        }
        printf256(522,168,250,"%d",count_hei);
        printf256(522,198,250,"%d",count_bai);
        if(flag_changechess)
        {
            TEXT_SIZE=TX_NORMAL ;
            puts256("按",436,385,250);
            puts256("键可以让电脑先走棋",460,385,250);
            TEXT_SIZE=TX_BIG ;
            puts256("c",452,383,250);
        }
        TEXT_SIZE=TX_BIG ;
        
        /*以下代码为准备带入电脑智能的准备工作（数据初始化）*/
        
        if(flag_whozhizi)
        for(a=1;a<9;a++)
        for(b=1;b<9;b++)
        {
            canput[a][b][0]=canput_bai[a][b][0];
            ren_yiput[a][b][0]=hei[a][b][0];
            cpu_yiput[a][b][0]=bai[a][b][0];
        }
        else 
        for(a=1;a<9;a++)
        for(b=1;b<9;b++)
        {
            canput[a][b][0]=canput_hei[a][b][0];
            ren_yiput[a][b][0]=bai[a][b][0];
            cpu_yiput[a][b][0]=hei[a][b][0];
        }
        
        
        
        if(canput[1][1][0])count_1++;
        if(canput[1][8][0])count_1++;
        if(canput[8][1][0])count_1++;
        if(canput[8][8][0])count_1++;
        
        for(a=3;a<=6;a++)
        {
            if(canput[a][1][0])count_2++;
            if(canput[1][a][0])count_2++;
            if(canput[8][a][0])count_2++;
            if(canput[a][8][0])count_2++;
            if(canput[a][3][0])count_3++;
            if(canput[a][6][0])count_3++;
            if(canput[3][a][0])count_3++;
            if(canput[6][a][0])count_3++;
            if(canput[a][2][0])count_4++;
            if(canput[a][7][0])count_4++;
            if(canput[2][a][0])count_4++;
            if(canput[7][a][0])count_4++;
        }
        
        if(canput[1][2][0])count_5++;
        if(canput[1][7][0])count_5++;
        if(canput[2][1][0])count_5++;
        if(canput[2][2][0])count_5++;
        if(canput[2][7][0])count_5++;
        if(canput[2][8][0])count_5++;
        if(canput[7][1][0])count_5++;
        if(canput[7][2][0])count_5++;
        if(canput[7][7][0])count_5++;
        if(canput[7][8][0])count_5++;
        if(canput[8][2][0])count_5++;
        if(canput[8][7][0])count_5++;
        
        /*    printf256(300,200,RED,"%d,%d,%d,%d,%d,%d,%d,%d",count_1,count_2,count_3,count_4,count_5,count_canput_bai,count_canput_hei,flag_changechess);   */
        flag_cpuyixia=0 ;
        if(count_1)
        flag_heibai=computer_1(flag_heibai,flag_whozhizi);
        else if(cpu_yiput[1][1][0]||cpu_yiput[1][8][0]||cpu_yiput[8][1][0]||cpu_yiput[8][8][0])
        flag_heibai=computer_1_1(flag_heibai,flag_whozhizi);
        if(count_2&&flag_cpuyixia==0)
        {
            flag_heibai=computer_2_0(flag_heibai,flag_whozhizi);     /*下子判断*/
            if(flag_cpuyixia==0)flag_heibai=computer_2(flag_heibai,flag_whozhizi);/*不下子判断*/
        }
        if(count_3&&flag_cpuyixia==0)
        flag_heibai=computer_3(flag_heibai,flag_whozhizi);
        if(count_4&&flag_cpuyixia==0)
        flag_heibai=computer_4(flag_heibai,flag_whozhizi);
        if(count_2&&flag_cpuyixia==0)
        flag_heibai=computer_2_1(flag_heibai,flag_whozhizi);
        if(count_5&&flag_cpuyixia==0)
        flag_heibai=computer_5(flag_heibai,flag_whozhizi);

       /* flag_heibai=computer_6(flag_heibai,flag_whozhizi); 后备加智能处理代码*/
        
        /*分区域计算可执行高性能代码。flag_changechess代入是要判断电脑应该填什么颜色的子*/
        
        /*用于判断游戏是否结束*/
        
        
        if(count_canput==0)
        {
            
            if(count_hei+count_bai==64)
            {
                if(count_hei>count_bai)
                {
                    puts256("黑棋赢了!按鼠标继续。",150,170,250);
                    vpost();
                    /*用于输出字*/
                    while(1)
                    {
                        if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                        gamemain_new();
                    }
                }
                else if(count_hei<count_bai)
                {
                    puts256("白棋赢了!按鼠标继续。",150,170,250);
                    vpost();
                    while(1)
                    {
                        if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                        gamemain_new();
                    }
                }
                else if(count_hei==count_bai)
                {
                    puts256("哈哈，你们打平了!按鼠标继续。",110,170,250);
                    vpost();
                    while(1)
                    {
                        if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                        gamemain_new();
                    }
                }
                
                
            }
            
            else 
            {
                if(count_canput_bai==0&&!flag_heibai)
                {
                    puts256("白棋这一步没有可下的地方了，按鼠标PASS!",100,190,250);
                    vpost();
                    while(flag_pass)
                    {
                        if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                        {
                            flag_heibai=(!flag_heibai);
                            flag_pass=0 ;
                            count_mouse_bai=count_step ;
                        }
                        
                    }
                }
                if(count_canput_hei==0&&flag_heibai)
                {
                    puts256("黑棋这一步没有可下的地方了，按鼠标PASS!",100,190,250);
                    vpost();
                    while(flag_pass)
                    {
                        if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                        {
                            flag_heibai=(!flag_heibai);
                            flag_pass=0 ;
                            count_mouse_hei=count_step ;
                        }
                    }
                }
                
                
                if(count_mouse_bai==count_mouse_hei)
                {
                    if(count_hei>count_bai)
                    {
                        puts256("黑棋赢了!按鼠标继续。",150,170,250);
                        vpost();
                        /*用于输出字*/
                        while(1)
                        {
                            if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                            gamemain_new();
                        }
                    }
                    else if(count_hei<count_bai)
                    {
                        puts256("白棋赢了!按鼠标继续。",150,170,250);
                        vpost();
                        while(1)
                        {
                            if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                            gamemain_new();
                        }
                    }
                    else if(count_hei==count_bai)
                    {
                        puts256("哈哈，你们打平了!按鼠标继续。",110,170,250);
                        vpost();
                        while(1)
                        {
                            if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                            gamemain_new();
                        }
                    }
                }
            }
        }
        count_canput=0 ;
        
        /*以下代码为清除canput数组虽然在高速循环中，但可下子标记还是会显示出来的，这种不显示停顿是很小的。*/
        
        if(!flag_heibai)
        for(a=0;a<10;a++)
        for(b=0;b<10;b++)
        {
            canput_hei[a][b][0]=0 ;
            
        }
        
        else 
        for(a=0;a<10;a++)
        for(b=0;b<10;b++)
        {
            canput_bai[a][b][0]=0 ;
            
        }
        
        /*初始化新数组程序*/
        for(a=0;a<9;a++)
        for(b=0;b<9;b++)
        {
            hei_new[a][b][0]=hei[a][b][0];
            bai_new[a][b][0]=bai[a][b][0];
        }
        
        
        /*PutImage(46,104,white,28);显示去除28色（这里为绿色）底图的图片*/
        
        /*以下代码为当按下C时改变下子的先后顺序*/
        if(kbhit())
        {
            key=getch();
            if(key=='c'||key=='C')
            if(flag_changechess)
            {
                flag_changechess=0 ;
                flag_whozhizi=0 ;
                
                
            }
            if(key=='s'||key=='S')
            flag_show=(!flag_show);
        }
        
        
        /*这段代码很不合理，可以和上面的循环放在一起使用，但是它的结构化更清晰，以下代码是将可以下黑子的地方标记到canput数组中*/
        if(flag_heibai)
        {
            for(a=1;a<9;a++)
            for(b=1;b<9;b++)
            {
                if(hei[a][b][0]==1)
                {
                    if(bai[a][b+1][0]==1)
                    for(i=b+1;i<9;i++)
                    {
                        if(hei[a][i][0]==1)break ;
                        /*如果遇到黑子就不在判断了*/
                        /* 如果为空就输入到可填数组*/
                        if(bai[a][i][0]==0&&hei[a][i][0]==0)
                        {
                            canput_hei[a][i][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(bai[a][b-1][0]==1)
                    for(i=b-1;i>0;i--)
                    {
                        if(hei[a][i][0]==1)break ;
                        if(bai[a][i][0]==0&&hei[a][i][0]==0)
                        {
                            canput_hei[a][i][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(bai[a+1][b][0]==1)
                    for(i=a+1;i<9;i++)
                    {
                        if(hei[i][b][0]==1)break ;
                        if(bai[i][b][0]==0&&hei[i][b][0]==0)
                        {
                            canput_hei[i][b][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(bai[a-1][b][0]==1)
                    for(i=a-1;i>0;i--)
                    {
                        if(hei[i][b][0]==1)break ;
                        if(bai[i][b][0]==0&&hei[i][b][0]==0)
                        {
                            canput_hei[i][b][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(bai[a+1][b+1][0]==1)
                    for(j=b+1,i=a+1;i<9;i++,j++)
                    {
                        if(j>8)break ;
                        if(hei[i][j][0]==1)break ;
                        if(bai[i][j][0]==0&&hei[i][j][0]==0)
                        {
                            canput_hei[i][j][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(bai[a-1][b-1][0]==1)
                    for(j=b-1,i=a-1;i>0;i--,j--)
                    {
                        if(j<1)break ;
                        if(hei[i][j][0]==1)break ;
                        if(bai[i][j][0]==0&&hei[i][j][0]==0)
                        {
                            canput_hei[i][j][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(bai[a-1][b+1][0]==1)
                    for(j=b+1,i=a-1;i>0;i--,j++)
                    {
                        if(j>8)break ;
                        if(hei[i][j][0]==1)break ;
                        if(bai[i][j][0]==0&&hei[i][j][0]==0)
                        {
                            canput_hei[i][j][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(bai[a+1][b-1][0]==1)
                    for(j=b-1,i=a+1;i<9;i++,j--)
                    {
                        if(j<1)break ;
                        if(hei[i][j][0]==1)break ;
                        if(bai[i][j][0]==0&&hei[i][j][0]==0)
                        {
                            canput_hei[i][j][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    
                    /*  以上代码为判断一个黑子周围是否有白色子。如果有那么继续判断其下一个子是否为空格，如果有那么即为可填子的地方。存放在可填子数组中。   */
                    
                }
                
                
            }
        }
        /*以下代码为判断白子可填处，和上面的原理相同但数据处理上相反*/
        else 
        {
            for(a=1;a<9;a++)
            for(b=1;b<9;b++)
            {
                if(bai[a][b][0]==1)
                {
                    if(hei[a][b+1][0]==1)
                    for(i=b+1;i<9;i++)
                    {
                        if(bai[a][i][0]==1)break ;
                        if(bai[a][i][0]==0&&hei[a][i][0]==0)
                        {
                            canput_bai[a][i][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(hei[a][b-1][0]==1)
                    for(i=b-1;i>0;i--)
                    {
                        if(bai[a][i][0]==1)break ;
                        if(bai[a][i][0]==0&&hei[a][i][0]==0)
                        {
                            canput_bai[a][i][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(hei[a+1][b][0]==1)
                    for(i=a+1;i<9;i++)
                    {
                        if(bai[i][b][0]==1)break ;
                        if(bai[i][b][0]==0&&hei[i][b][0]==0)
                        {
                            canput_bai[i][b][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(hei[a-1][b][0]==1)
                    for(i=a-1;i>0;i--)
                    {
                        if(bai[i][b][0]==1)break ;
                        if(bai[i][b][0]==0&&hei[i][b][0]==0)
                        {
                            canput_bai[i][b][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(hei[a+1][b+1][0]==1)
                    for(j=b+1,i=a+1;i<9;i++,j++)
                    {
                        if(j>8)break ;
                        if(bai[i][j][0]==1)break ;
                        if(bai[i][j][0]==0&&hei[i][j][0]==0)
                        {
                            canput_bai[i][j][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(hei[a-1][b-1][0]==1)
                    for(j=b-1,i=a-1;i>0;i--,j--)
                    {
                        if(j<1)break ;
                        if(bai[i][j][0]==1)break ;
                        if(bai[i][j][0]==0&&hei[i][j][0]==0)
                        {
                            canput_bai[i][j][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(hei[a-1][b+1][0]==1)
                    for(j=b+1,i=a-1;i>0;i--,j++)
                    {
                        if(j>8)break ;
                        if(bai[i][j][0]==1)break ;
                        if(bai[i][j][0]==0&&hei[i][j][0]==0)
                        {
                            canput_bai[i][j][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(hei[a+1][b-1][0]==1)
                    for(j=b-1,i=a+1;i<9;i++,j--)
                    {
                        if(j<1)break ;
                        if(bai[i][j][0]==1)break ;
                        if(bai[i][j][0]==0&&hei[i][j][0]==0)
                        {
                            canput_bai[i][j][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    
                    
                }
                
                
            }
        }
        
        
        getmousexy();
        is_on=-1 ;
        
        /*以下用于判断鼠标指向棋盘位置*/
        
        for(i=1;i<9;i++)
        for(j=1;j<9;j++)
        if(mouse.getx>=j*41&&mouse.getx<=j*41+34&&mouse.gety>=i*40+58&&mouse.gety<=i*40+58+34)
        {
            if(getmkeyin(mbLeft)==mbLeft)
            /*只能在指定位置（X标记处)放入棋子*/
            /*交替下黑白子*/
            if(canput_hei[j][i][0]==1||canput_bai[j][i][0]==1)if(!flag_heibai&&bai[j][i][0]!=1&&hei[j][i][0]!=1)
            {
                bai[j][i][0]=1 ;
                flag_changechess=0 ;
                if(!flag_whozhizi)flag_heibai=(!flag_heibai);
                
                
                /*以下代码为替换黑白子（人人对战）功能，由于如果把原数组附值后，后面的判断就会把修改后的数组判断进去。所以应该再使用新数组，最后将值代入原数组！*/
                if(hei[j+1][i][0]==1)
                for(a=j+1;a<9;a++)
                {
                    if(bai[a][i][0]==1)
                    {
                        for(c=j;c<=a;c++)
                        {
                            bai_new[c][i][0]=1 ;
                            hei_new[c][i][0]=0 ;
                        }
                        break ;
                    }
                    
                }
                
                if(hei[j][i-1][0]==1)
                for(b=i-1;b>0;b--)
                {
                    if(bai[j][b][0]==1)
                    {
                        for(c=i;c>=b;c--)
                        {
                            bai_new[j][c][0]=1 ;
                            hei_new[j][c][0]=0 ;
                        }
                        break ;
                    }
                    
                }
                
                if(hei[j][i+1][0]==1)
                for(b=i+1;b<9;b++)
                {
                    if(bai[j][b][0]==1)
                    {
                        for(c=i;c<=b;c++)
                        {
                            bai_new[j][c][0]=1 ;
                            hei_new[j][c][0]=0 ;
                        }
                        break ;
                    }
                    
                }
                
                if(hei[j-1][i][0]==1)
                for(a=j-1;a>0;a--)
                {
                    if(bai[a][i][0]==1)
                    {
                        
                        for(c=j;c>=a;c--)
                        {
                            bai_new[c][i][0]=1 ;
                            hei_new[c][i][0]=0 ;
                        }
                        break ;
                    }
                }
                
                /*这种算法和前面的判断可填空格不一样，优点是结构更清晰。更简单*/
                if(hei[j+1][i+1][0]==1)for(a=j+1,b=i+1,d=0;b<9;a++,b++,d++)
                {
                    if(a>8)break ;
                    if(bai[a][b][0]==1)
                    {
                        for(c=0;c<=d;c++)
                        {
                            bai_new[j+c][i+c][0]=1 ;
                            hei_new[j+c][i+c][0]=0 ;
                        }
                        break ;
                    }
                }
                
                if(hei[j-1][i-1][0]==1)
                for(a=j-1,b=i-1,d=0;b>0;a--,b--,d++)
                {
                    if(a<1)break ;
                    if(bai[a][b][0]==1)
                    
                    {
                        
                        for(c=0;c<=d;c++)
                        {
                            bai_new[j-c][i-c][0]=1 ;
                            hei_new[j-c][i-c][0]=0 ;
                        }
                        break ;
                    }
                }
                
                if(hei[j+1][i-1][0]==1)
                for(a=j+1,b=i-1,d=0;b>0;b--,a++,d++)
                {
                    if(a>8)break ;
                    if(bai[a][b][0]==1)
                    
                    {
                        
                        for(c=0;c<=d;c++)
                        {
                            bai_new[j+c][i-c][0]=1 ;
                            hei_new[j+c][i-c][0]=0 ;
                        }
                        break ;
                    }
                }
                
                if(hei[j-1][i+1][0]==1)
                for(a=j-1,b=i+1,d=0;b<9;b++,a--,d++)
                {
                    if(a<1)break ;
                    if(bai[a][b][0]==1)
                    {
                        for(c=0;c<=d;c++)
                        {
                            bai_new[j-c][i+c][0]=1 ;
                            hei_new[j-c][i+c][0]=0 ;
                        }
                        break ;
                    }
                }
                
                
            }
            
            
            else if(bai[j][i][0]!=1&&hei[j][i][0]!=1)
            {
                hei[j][i][0]=1 ;
                
                flag_changechess=0 ;
                if(flag_whozhizi)flag_heibai=(!flag_heibai);
                
                if(bai[j+1][i][0]==1)
                for(a=j+1;a<9;a++)
                {
                    if(hei[a][i][0]==1)
                    
                    {
                        for(c=j;c<=a;c++)
                        {
                            bai_new[c][i][0]=0 ;
                            hei_new[c][i][0]=1 ;
                        }
                        break ;
                    }
                }
                
                if(bai[j][i-1][0]==1)
                for(b=i-1;b>0;b--)
                {
                    if(hei[j][b][0]==1)
                    
                    {
                        for(c=i;c>=b;c--)
                        {
                            bai_new[j][c][0]=0 ;
                            hei_new[j][c][0]=1 ;
                        }
                        break ;
                    }
                }
                
                if(bai[j][i+1][0]==1)
                for(b=i+1;b<9;b++)
                {
                    if(hei[j][b][0]==1)
                    
                    {
                        for(c=i;c<=b;c++)
                        {
                            bai_new[j][c][0]=0 ;
                            hei_new[j][c][0]=1 ;
                        }
                        break ;
                    }
                }
                
                if(bai[j-1][i][0]==1)
                for(a=j-1;a>0;a--)
                {
                    if(hei[a][i][0]==1)
                    
                    {
                        for(c=j;c>=a;c--)
                        {
                            bai_new[c][i][0]=0 ;
                            hei_new[c][i][0]=1 ;
                        }
                        break ;
                    }
                }
                
                if(bai[j+1][i+1][0]==1)
                for(a=j+1,b=i+1,d=0;b<9;a++,b++,d++)
                {
                    if(a>8)break ;
                    if(hei[a][b][0]==1)
                    {
                        for(c=0;c<=d;c++)
                        {
                            bai_new[j+c][i+c][0]=0 ;
                            hei_new[j+c][i+c][0]=1 ;
                        }
                        break ;
                    }
                }
                
                if(bai[j-1][i-1][0]==1)
                for(a=j-1,b=i-1,d=0;b>0;a--,b--,d++)
                {
                    if(a<1)break ;
                    if(hei[a][b][0]==1)
                    
                    {
                        
                        for(c=0;c<=d;c++)
                        {
                            bai_new[j-c][i-c][0]=0 ;
                            hei_new[j-c][i-c][0]=1 ;
                        }
                        break ;
                    }
                }
                
                if(bai[j+1][i-1][0]==1)
                for(a=j+1,b=i-1,d=0;b>0;b--,a++,d++)
                {
                    if(a>8)break ;
                    if(hei[a][b][0]==1)
                    
                    {
                        
                        for(c=0;c<=d;c++)
                        {
                            bai_new[j+c][i-c][0]=0 ;
                            hei_new[j+c][i-c][0]=1 ;
                        }
                        break ;
                    }
                }
                
                if(bai[j-1][i+1][0]==1)
                for(a=j-1,b=i+1,d=0;b<9;b++,a--,d++)
                {
                    if(a<1)break ;
                    if(hei[a][b][0]==1)
                    {
                        for(c=0;c<=d;c++)
                        {
                            bai_new[j-c][i+c][0]=0 ;
                            hei_new[j-c][i+c][0]=1 ;
                        }
                        break ;
                    }
                }
                
                
            }
        }
        
        /*以下代码用于付值*/
        for(a=0;a<9;a++)
        for(b=0;b<9;b++)
        {
            hei[a][b][0]=hei_new[a][b][0];
            bai[a][b][0]=bai_new[a][b][0];
        }
        /*以下用于判断鼠标特殊位置（叉之类）*/
        /*判断差键鼠标点击主要是此函数控制*/
        if(mouse.getx>=12&&mouse.getx<=34&&mouse.gety>=31&&mouse.gety<=42)
        {
            is_on=0 ;
            puts256(texts[0],12,31,BLUE);
        }
        else puts256(texts[0],12,31,0);
        
        /*判断差键鼠标点击主要是此函数控制*/
        if(mouse.getx>=49&&mouse.getx<=72&&mouse.gety>=31&&mouse.gety<=42)
        {
            is_on=1 ;
            puts256(texts[1],49,31,BLUE);
        }
        else puts256(texts[1],49,31,0);
        
        /*判断差键鼠标点击主要是此函数控制*/
        if(mouse.getx>=616&&mouse.getx<=635&&mouse.gety>=3&&mouse.gety<=20)
        {
            is_on=2 ;
            puts256(texts[2],616,3,BLUE);
        }
        else puts256(texts[2],616,3,0);
        
        if(is_on>=0)
        {
            if(curtype)
            {
                curtype=0 ;
            }
            if(getmkeyin(mbLeft)==mbLeft)
            /*点击鼠标特殊位置响应代码*/
            switch(is_on)
            {
                case 0 :
                gamemain_2_game();
                break ;
                case 1 :
                gamemain_2_help();
                break ;
                case 2 :
                gameend();
                break ;
                
            }
        }
        else 
        if(!curtype)
        {
            curtype=1 ;
        }
        {
            char s[8];
            printf256(550,460,BLUE,"%4d,%4d",mouse.getx,mouse.gety);
        }
        
        
        
        
        showmouse();
        getmkeyin(mbLeft);
        vpost();
        
    }
}

/*人人大战*/
void gamemain_2(void)
{
    int i,j,a,b,c,d ;
    int flag_heibai=1,flag_pass,flag_show=0 ;
    int hei_new[10][10][2],bai_new[10][10][2];
    int count_bai,count_hei,count_canput=1,count_canput_bai,count_canput_hei ;
    int count_mouse_bai,count_mouse_hei ;
    /*用于交替使用黑白子*/
    char is_on,key ;
    static char curtype=1,texts[3][16]=
    {
        /*虽然为空但和图片的位置是一直的！*/
        "   ","   ","   " 
    }
    ;
    
    TEXT_SIZE=TX_BIG ;
    /*16点阵显示*/
    /*虽然是死循环，但是鼠标点叉后会退出游戏*/
    while(1)
    {
        hidemouse();
        QPutImage(0,0,back);
        /*输出背景图*/
        
        /*输出已标记棋子，及可下子的地方。*/
        for(a=1;a<9;a++)for(b=1;b<9;b++)
        {
            if(hei[a][b][0]==1)
            PutImage(a*41+5,b*40+64,black,28);
            if(bai[a][b][0]==1)
            PutImage(a*41+5,b*40+64,white,28);
            if(flag_show)
            {
                if(canput_hei[a][b][0]==1&&flag_heibai)
                puts256("X",a*41+5+10,b*40+64+10,BLACK);
                if(canput_bai[a][b][0]==1&&!flag_heibai)
                puts256("X",a*41+5+10,b*40+64+10,WHITE);
            }
        }
        /*以下代码为输出黑白子的数量（势力范围）*/
        count_bai=0 ;
        count_hei=0 ;
        count_canput_bai=0 ;
        count_canput_hei=0 ;
        flag_pass=1 ;
        
        for(a=1;a<9;a++)
        for(b=1;b<9;b++)
        {
            if(bai[a][b][0]==1)
            count_bai++;
            if(hei[a][b][0]==1)
            count_hei++;
            if(canput_bai[a][b][0]==1)
            count_canput_bai++;
            if(canput_hei[a][b][0]==1)
            count_canput_hei++;
        }
        printf256(522,168,250,"%d",count_hei);
        printf256(522,198,250,"%d",count_bai);
        
        /*用于判断游戏是否结束*/
        if(count_canput==0)
        {
            
            if(count_hei+count_bai==64)
            {
                if(count_hei>count_bai)
                {
                    puts256("黑棋赢了!",180,170,250);
                    vpost();
                    /*用于输出字*/
                    while(1)
                    {
                        if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                        gamemain_new();
                    }
                }
                else if(count_hei<count_bai)
                {
                    puts256("白棋赢了!",180,170,250);
                    vpost();
                    while(1)
                    {
                        if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                        gamemain_new();
                    }
                }
                else if(count_hei==count_bai)
                {
                    puts256("哈哈，你们打平了!",140,170,250);
                    vpost();
                    while(1)
                    {
                        if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                        gamemain_new();
                    }
                }
                
                
            }
            
            else 
            {
                if(count_canput_bai==0&&!flag_heibai)
                {
                    puts256("白棋这一步没有可下的地方了，按鼠标PASS!",100,190,250);
                    vpost();
                    while(flag_pass)
                    {
                        if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                        {
                            flag_heibai=(!flag_heibai);
                            flag_pass=0 ;
                            count_mouse_bai=count_step ;
                        }
                        
                    }
                }
                if(count_canput_hei==0&&flag_heibai)
                {
                    puts256("黑棋这一步没有可下的地方了，按鼠标PASS!",100,190,250);
                    vpost();
                    while(flag_pass)
                    {
                        if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                        {
                            flag_heibai=(!flag_heibai);
                            flag_pass=0 ;
                            count_mouse_hei=count_step ;
                        }
                    }
                }
                
                
                if(count_mouse_bai==count_mouse_hei)
                {
                    if(count_hei>count_bai)
                    {
                        puts256("黑棋赢了!",180,170,250);
                        vpost();
                        /*用于输出字*/
                        while(1)
                        {
                            if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                            gamemain_new();
                        }
                    }
                    else if(count_hei<count_bai)
                    {
                        puts256("白棋赢了!",180,170,250);
                        vpost();
                        while(1)
                        {
                            if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                            gamemain_new();
                        }
                    }
                    else if(count_hei==count_bai)
                    {
                        puts256("哈哈，你们打平了!",140,170,250);
                        vpost();
                        while(1)
                        {
                            if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                            gamemain_new();
                        }
                    }
                }
            }
        }
        
        
        count_canput=0 ;
        
        if(kbhit())
        {
            key=getch();
            if(key=='s'||key=='S')
            flag_show=(!flag_show);
            
        }
        /*以下代码为清除canput数组虽然在高速循环中，但可下子标记还是会显示出来的，这种不显示停顿是很小的。*/
        
        
        /*初始化新数组程序*/
        for(a=0;a<9;a++)
        for(b=0;b<9;b++)
        {
            hei_new[a][b][0]=hei[a][b][0];
            bai_new[a][b][0]=bai[a][b][0];
        }
        
        
        if(!flag_heibai)
        for(a=0;a<10;a++)
        for(b=0;b<10;b++)
        {
            canput_hei[a][b][0]=0 ;
            
        }
        
        else 
        for(a=0;a<10;a++)
        for(b=0;b<10;b++)
        {
            canput_bai[a][b][0]=0 ;
            
        }
        
        
        /*PutImage(46,104,white,28);显示去除28色（这里为绿色）底图的图片*/
        /*这段代码很不合理，可以和上面的循环放在一起使用，但是它的结构化更清晰，以下代码是将可以下黑子的地方标记到canput数组中*/
        if(flag_heibai)
        {
            for(a=1;a<9;a++)
            for(b=1;b<9;b++)
            {
                if(hei[a][b][0]==1)
                {
                    if(bai[a][b+1][0]==1)
                    for(i=b+1;i<9;i++)
                    {
                        if(hei[a][i][0]==1)break ;
                        /*如果遇到黑子就不在判断了*/
                        /* 如果为空就输入到可填数组*/
                        if(bai[a][i][0]==0&&hei[a][i][0]==0)
                        {
                            canput_hei[a][i][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(bai[a][b-1][0]==1)
                    for(i=b-1;i>0;i--)
                    {
                        if(hei[a][i][0]==1)break ;
                        if(bai[a][i][0]==0&&hei[a][i][0]==0)
                        {
                            canput_hei[a][i][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(bai[a+1][b][0]==1)
                    for(i=a+1;i<9;i++)
                    {
                        if(hei[i][b][0]==1)break ;
                        if(bai[i][b][0]==0&&hei[i][b][0]==0)
                        {
                            canput_hei[i][b][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(bai[a-1][b][0]==1)
                    for(i=a-1;i>0;i--)
                    {
                        if(hei[i][b][0]==1)break ;
                        if(bai[i][b][0]==0&&hei[i][b][0]==0)
                        {
                            canput_hei[i][b][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(bai[a+1][b+1][0]==1)
                    for(j=b+1,i=a+1;i<9;i++,j++)
                    {
                        if(j>8)break ;
                        if(hei[i][j][0]==1)break ;
                        if(bai[i][j][0]==0&&hei[i][j][0]==0)
                        {
                            canput_hei[i][j][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(bai[a-1][b-1][0]==1)
                    for(j=b-1,i=a-1;i>0;i--,j--)
                    {
                        if(j<1)break ;
                        if(hei[i][j][0]==1)break ;
                        if(bai[i][j][0]==0&&hei[i][j][0]==0)
                        {
                            canput_hei[i][j][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(bai[a-1][b+1][0]==1)
                    for(j=b+1,i=a-1;i>0;i--,j++)
                    {
                        if(j>8)break ;
                        if(hei[i][j][0]==1)break ;
                        if(bai[i][j][0]==0&&hei[i][j][0]==0)
                        {
                            canput_hei[i][j][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(bai[a+1][b-1][0]==1)
                    for(j=b-1,i=a+1;i<9;i++,j--)
                    {
                        if(j<1)break ;
                        if(hei[i][j][0]==1)break ;
                        if(bai[i][j][0]==0&&hei[i][j][0]==0)
                        {
                            canput_hei[i][j][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    
                    /*  以上代码为判断一个黑子周围是否有白色子。如果有那么继续判断其下一个子是否为空格，如果有那么即为可填子的地方。存放在可填子数组中。   */
                    
                }
                
                
            }
        }
        /*以下代码为判断白子可填处，和上面的原理相同但数据处理上相反*/
        else 
        {
            for(a=1;a<9;a++)
            for(b=1;b<9;b++)
            {
                if(bai[a][b][0]==1)
                {
                    if(hei[a][b+1][0]==1)
                    for(i=b+1;i<9;i++)
                    {
                        if(bai[a][i][0]==1)break ;
                        if(bai[a][i][0]==0&&hei[a][i][0]==0)
                        {
                            canput_bai[a][i][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(hei[a][b-1][0]==1)
                    for(i=b-1;i>0;i--)
                    {
                        if(bai[a][i][0]==1)break ;
                        if(bai[a][i][0]==0&&hei[a][i][0]==0)
                        {
                            canput_bai[a][i][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(hei[a+1][b][0]==1)
                    for(i=a+1;i<9;i++)
                    {
                        if(bai[i][b][0]==1)break ;
                        if(bai[i][b][0]==0&&hei[i][b][0]==0)
                        {
                            canput_bai[i][b][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(hei[a-1][b][0]==1)
                    for(i=a-1;i>0;i--)
                    {
                        if(bai[i][b][0]==1)break ;
                        if(bai[i][b][0]==0&&hei[i][b][0]==0)
                        {
                            canput_bai[i][b][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(hei[a+1][b+1][0]==1)
                    for(j=b+1,i=a+1;i<9;i++,j++)
                    {
                        if(j>8)break ;
                        if(bai[i][j][0]==1)break ;
                        if(bai[i][j][0]==0&&hei[i][j][0]==0)
                        {
                            canput_bai[i][j][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(hei[a-1][b-1][0]==1)
                    for(j=b-1,i=a-1;i>0;i--,j--)
                    {
                        if(j<1)break ;
                        if(bai[i][j][0]==1)break ;
                        if(bai[i][j][0]==0&&hei[i][j][0]==0)
                        {
                            canput_bai[i][j][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(hei[a-1][b+1][0]==1)
                    for(j=b+1,i=a-1;i>0;i--,j++)
                    {
                        if(j>8)break ;
                        if(bai[i][j][0]==1)break ;
                        if(bai[i][j][0]==0&&hei[i][j][0]==0)
                        {
                            canput_bai[i][j][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    if(hei[a+1][b-1][0]==1)
                    for(j=b-1,i=a+1;i<9;i++,j--)
                    {
                        if(j<1)break ;
                        if(bai[i][j][0]==1)break ;
                        if(bai[i][j][0]==0&&hei[i][j][0]==0)
                        {
                            canput_bai[i][j][0]=1 ;
                            count_canput++;
                            break ;
                        }
                    }
                    
                    
                }
                
                
            }
        }
        
        
        getmousexy();
        is_on=-1 ;
        
        /*以下用于判断鼠标指向棋盘位置*/
        
        for(i=1;i<9;i++)
        for(j=1;j<9;j++)
        if(mouse.getx>=j*41&&mouse.getx<=j*41+34&&mouse.gety>=i*40+58&&mouse.gety<=i*40+58+34)
        {
            if(getmkeyin(mbLeft)==mbLeft)
            /*只能在指定位置（X标记处)放入棋子*/
            /*交替下黑白子*/
            if(canput_hei[j][i][0]==1||canput_bai[j][i][0]==1)if(!flag_heibai&&bai[j][i][0]!=1&&hei[j][i][0]!=1)
            {
                bai[j][i][0]=1 ;
                
                flag_heibai=1 ;
                
                
                /*以下代码为替换黑白子（人人对战）功能，由于如果把原数组附值后，后面的判断就会把修改后的数组判断进去。所以应该再使用新数组，最后将值代入原数组！*/
                if(hei[j+1][i][0]==1)
                for(a=j+1;a<9;a++)
                {
                    if(bai[a][i][0]==1)
                    {
                        for(c=j;c<=a;c++)
                        {
                            bai_new[c][i][0]=1 ;
                            hei_new[c][i][0]=0 ;
                        }
                        break ;
                    }
                    
                }
                
                if(hei[j][i-1][0]==1)
                for(b=i-1;b>0;b--)
                {
                    if(bai[j][b][0]==1)
                    {
                        for(c=i;c>=b;c--)
                        {
                            bai_new[j][c][0]=1 ;
                            hei_new[j][c][0]=0 ;
                        }
                        break ;
                    }
                    
                }
                
                if(hei[j][i+1][0]==1)
                for(b=i+1;b<9;b++)
                {
                    if(bai[j][b][0]==1)
                    {
                        for(c=i;c<=b;c++)
                        {
                            bai_new[j][c][0]=1 ;
                            hei_new[j][c][0]=0 ;
                        }
                        break ;
                    }
                    
                }
                
                if(hei[j-1][i][0]==1)
                for(a=j-1;a>0;a--)
                {
                    if(bai[a][i][0]==1)
                    {
                        
                        for(c=j;c>=a;c--)
                        {
                            bai_new[c][i][0]=1 ;
                            hei_new[c][i][0]=0 ;
                        }
                        break ;
                    }
                }
                
                /*这种算法和前面的判断可填空格不一样，优点是结构更清晰。更简单*/
                if(hei[j+1][i+1][0]==1)for(a=j+1,b=i+1,d=0;b<9;a++,b++,d++)
                {
                    if(a>8)break ;
                    if(bai[a][b][0]==1)
                    {
                        for(c=0;c<=d;c++)
                        {
                            bai_new[j+c][i+c][0]=1 ;
                            hei_new[j+c][i+c][0]=0 ;
                        }
                        break ;
                    }
                }
                
                if(hei[j-1][i-1][0]==1)
                for(a=j-1,b=i-1,d=0;b>0;a--,b--,d++)
                {
                    if(a<1)break ;
                    if(bai[a][b][0]==1)
                    
                    {
                        
                        for(c=0;c<=d;c++)
                        {
                            bai_new[j-c][i-c][0]=1 ;
                            hei_new[j-c][i-c][0]=0 ;
                        }
                        break ;
                    }
                }
                
                if(hei[j+1][i-1][0]==1)
                for(a=j+1,b=i-1,d=0;b>0;b--,a++,d++)
                {
                    if(a>8)break ;
                    if(bai[a][b][0]==1)
                    
                    {
                        
                        for(c=0;c<=d;c++)
                        {
                            bai_new[j+c][i-c][0]=1 ;
                            hei_new[j+c][i-c][0]=0 ;
                        }
                        break ;
                    }
                }
                
                if(hei[j-1][i+1][0]==1)
                for(a=j-1,b=i+1,d=0;b<9;b++,a--,d++)
                {
                    if(a<1)break ;
                    if(bai[a][b][0]==1)
                    {
                        for(c=0;c<=d;c++)
                        {
                            bai_new[j-c][i+c][0]=1 ;
                            hei_new[j-c][i+c][0]=0 ;
                        }
                        break ;
                    }
                }
                
                
            }
            
            
            else if(bai[j][i][0]!=1&&hei[j][i][0]!=1)
            {
                hei[j][i][0]=1 ;
                flag_heibai=0 ;
                
                
                if(bai[j+1][i][0]==1)
                for(a=j+1;a<9;a++)
                {
                    if(hei[a][i][0]==1)
                    
                    {
                        for(c=j;c<=a;c++)
                        {
                            bai_new[c][i][0]=0 ;
                            hei_new[c][i][0]=1 ;
                        }
                        break ;
                    }
                }
                
                if(bai[j][i-1][0]==1)
                for(b=i-1;b>0;b--)
                {
                    if(hei[j][b][0]==1)
                    
                    {
                        for(c=i;c>=b;c--)
                        {
                            bai_new[j][c][0]=0 ;
                            hei_new[j][c][0]=1 ;
                        }
                        break ;
                    }
                }
                
                if(bai[j][i+1][0]==1)
                for(b=i+1;b<9;b++)
                {
                    if(hei[j][b][0]==1)
                    
                    {
                        for(c=i;c<=b;c++)
                        {
                            bai_new[j][c][0]=0 ;
                            hei_new[j][c][0]=1 ;
                        }
                        break ;
                    }
                }
                
                if(bai[j-1][i][0]==1)
                for(a=j-1;a>0;a--)
                {
                    if(hei[a][i][0]==1)
                    
                    {
                        for(c=j;c>=a;c--)
                        {
                            bai_new[c][i][0]=0 ;
                            hei_new[c][i][0]=1 ;
                        }
                        break ;
                    }
                }
                
                if(bai[j+1][i+1][0]==1)
                for(a=j+1,b=i+1,d=0;b<9;a++,b++,d++)
                {
                    if(a>8)break ;
                    if(hei[a][b][0]==1)
                    {
                        for(c=0;c<=d;c++)
                        {
                            bai_new[j+c][i+c][0]=0 ;
                            hei_new[j+c][i+c][0]=1 ;
                        }
                        break ;
                    }
                }
                
                if(bai[j-1][i-1][0]==1)
                for(a=j-1,b=i-1,d=0;b>0;a--,b--,d++)
                {
                    if(a<1)break ;
                    if(hei[a][b][0]==1)
                    
                    {
                        
                        for(c=0;c<=d;c++)
                        {
                            bai_new[j-c][i-c][0]=0 ;
                            hei_new[j-c][i-c][0]=1 ;
                        }
                        break ;
                    }
                }
                
                if(bai[j+1][i-1][0]==1)
                for(a=j+1,b=i-1,d=0;b>0;b--,a++,d++)
                {
                    if(a>8)break ;
                    if(hei[a][b][0]==1)
                    
                    {
                        
                        for(c=0;c<=d;c++)
                        {
                            bai_new[j+c][i-c][0]=0 ;
                            hei_new[j+c][i-c][0]=1 ;
                        }
                        break ;
                    }
                }
                
                if(bai[j-1][i+1][0]==1)
                for(a=j-1,b=i+1,d=0;b<9;b++,a--,d++)
                {
                    if(a<1)break ;
                    if(hei[a][b][0]==1)
                    {
                        for(c=0;c<=d;c++)
                        {
                            bai_new[j-c][i+c][0]=0 ;
                            hei_new[j-c][i+c][0]=1 ;
                        }
                        break ;
                    }
                }
                
                
            }
        }
        
        /*以下代码用于付值*/
        for(a=0;a<9;a++)
        for(b=0;b<9;b++)
        {
            hei[a][b][0]=hei_new[a][b][0];
            bai[a][b][0]=bai_new[a][b][0];
        }
        /*以下用于判断鼠标特殊位置（叉之类）*/
        /*判断差键鼠标点击主要是此函数控制*/
        if(mouse.getx>=12&&mouse.getx<=34&&mouse.gety>=31&&mouse.gety<=42)
        {
            is_on=0 ;
            puts256(texts[0],12,31,BLUE);
        }
        else puts256(texts[0],12,31,0);
        
        /*判断差键鼠标点击主要是此函数控制*/
        if(mouse.getx>=49&&mouse.getx<=72&&mouse.gety>=31&&mouse.gety<=42)
        {
            is_on=1 ;
            puts256(texts[1],49,31,BLUE);
        }
        else puts256(texts[1],49,31,0);
        
        /*判断差键鼠标点击主要是此函数控制*/
        if(mouse.getx>=616&&mouse.getx<=635&&mouse.gety>=3&&mouse.gety<=20)
        {
            is_on=2 ;
            puts256(texts[2],616,3,BLUE);
        }
        else puts256(texts[2],616,3,0);
        
        if(is_on>=0)
        {
            if(curtype)
            {
                curtype=0 ;
            }
            if(getmkeyin(mbLeft)==mbLeft)
            /*点击鼠标特殊位置响应代码*/
            switch(is_on)
            {
                case 0 :
                gamemain_2_game();
                break ;
                case 1 :
                gamemain_2_help();
                break ;
                case 2 :
                gameend();
                break ;
                
            }
        }
        else 
        if(!curtype)
        {
            curtype=1 ;
        }
        {
            char s[8];
            printf256(550,460,BLUE,"%4d,%4d",mouse.getx,mouse.gety);
        }
        
        
        
        
        showmouse();
        getmkeyin(mbLeft);
        vpost();
        
    }
}


void gamemain_2_game(void)
{
    int i,j ;
    char is_on,key ;
    static char curtype=1,texts[3][16]=
    {
        /*虽然为空但和图片的位置是一直的！*/
        "","","   " 
    }
    ;
    
    check=0 ;
    while(!check)
    {
        if(getmkeyin(mbRight)==mbRight)check=1 ;
        hidemouse();
        QPutImage(12,49,game);
        /*输出背景图*/
        TEXT_SIZE=TX_BIG ;
        /*16点阵显示*/
        getmousexy();
        is_on=-1 ;
        
        for(i=0;i<2;i++)
        if(mouse.getx>=22&&mouse.getx<=90&&mouse.gety>=51+i*25&&mouse.gety<=70+i*25)
        {
            is_on=i ;
            puts256(texts[i],22,51+i*25,BLUE);
            /*显示要点击的汉字位置*/
        }
        else puts256(texts[i],22,51+i*25,0);
        
        
        /*判断差键鼠标点击主要是此函数控制*/
        if(mouse.getx>=616&&mouse.getx<=635&&mouse.gety>=3&&mouse.gety<=20)
        {
            is_on=2 ;
            puts256(texts[2],616,3,BLUE);
        }
        else puts256(texts[2],616,3,0);
        
        if(is_on>=0)
        {
            if(curtype)
            {
                curtype=0 ;
            }
            if(getmkeyin(mbLeft)==mbLeft)
            /*点击鼠标响应代码*/
            switch(is_on)
            {
                case 0 :
                gamemain_new();
                break ;
                case 1 :
                check=1 ;
                /*用于鼠标点击退出*/
                gameend();
                break ;
                case 2 :
                check=1 ;
                gameend();
                break ;
            }
        }
        else 
        if(!curtype)
        {
            curtype=1 ;
        }
        {
            char s[8];
            printf256(550,460,BLUE,"%4d,%4d",mouse.getx,mouse.gety);
        }
        showmouse();
        getmkeyin(mbLeft);
        vpost();
    }
    return(0);
}

void gamemain_2_help(void)
{
    int i,j ;
    char is_on,key ;
    static char curtype=1,texts[3][16]=
    {
        /*虽然为空但和图片的位置是一直的！*/
        "","","   " 
    }
    ;
    
    check=0 ;
    while(!check)
    {
        if(getmkeyin(mbRight)==mbRight)check=1 ;
        hidemouse();
        QPutImage(34,49,help);
        /*输出背景图*/
        TEXT_SIZE=TX_BIG ;
        /*16点阵显示*/
        getmousexy();
        is_on=-1 ;
        
        for(i=0;i<2;i++)
        if(mouse.getx>=40&&mouse.getx<=118&&mouse.gety>=51+i*25&&mouse.gety<=70+i*25)
        {
            is_on=i ;
            puts256(texts[i],40,51+i*25,BLUE);
            /*显示要点击的汉字位置*/
        }
        else puts256(texts[i],40,51+i*25,0);
        
        /*判断差键鼠标点击主要是此函数控制*/
        if(mouse.getx>=616&&mouse.getx<=635&&mouse.gety>=3&&mouse.gety<=20)
        {
            is_on=2 ;
            puts256(texts[2],616,3,BLUE);
        }
        else puts256(texts[2],616,3,0);
        
        if(is_on>=0)
        {
            if(curtype)
            {
                curtype=0 ;
            }
            if(getmkeyin(mbLeft)==mbLeft)
            /*点击鼠标响应代码*/
            switch(is_on)
            {
                case 0 :
                puts256("    黑白棋又叫奥塞罗棋，是在规格为８Ｘ８的棋盘上进行的棋类游戏。",30,100,125);
                puts256("游戏开始时在棋盘中央预先放置4粒棋子（2黑2白）,然后双方轮流下子，",30,120,125);
                puts256("直到棋盘下满时，盘上棋子多的一方胜利。",30,140,125);
                puts256("规则：",30,160,224);
                puts256("1.吃子：无论是直线还是斜线方向，下子后若所下之子与己方棋子之间全",30,180,125);
                puts256("部是敌方棋子(不包含空格),则这些敌方棋子全部被吃掉，变成己方棋子。",30,200,125);
                puts256("2.下子：只能在可以吃子的位置下子，否则此处下子无效。",30,220,125);
                puts256("3.放弃下子：若无处可以下子,则自动放弃一次下子机会,由对方继续下子。",30,240,125);
                puts256("4.游戏结束：当棋盘下满,或双方都无子可下时游戏结束。子多的一方获胜。",30,260,125);
                puts256("策略和技巧：",30,280,224);
                puts256("尽量多的抢占边和角上的格子，因为它们中的棋子被对方吃掉的可能性较小。",30,300,125);
                puts256("游戏相关：",30,320,224);
                puts256("1. S键：打开/关闭 可下子位置提示。",30,340,125);
                puts256("2. C键：在人机大战时让电脑先走。",30,360,125);
                puts256("3. ★ 代表电脑的走子位置。",30,380,125);
                puts256("4. 当菜单被选择后，点击鼠标右键可以取消选择。",30,400,125);
                
                break ;
                case 1 :
                puts256("    你相信这是用Turbo C 2.0开发出来的游戏吗？我可以很肯定对你说：",26,100,125);
                puts256("不要不相信你的眼睛，这的确是一个事实！你可以到我的主页上下载到源代",26,120,125);
                puts256("码",26,140,125);
                puts256(" www.chengchen.net",78,140,253);
                puts256("  写此程序，我只是想告诉大家：编程是一件",250,140,125);
                puts256("愉快的事情，只要你肯动脑筋！",26,160,125);
                puts256("    近来一些人对我的C 语言能力提出了质疑，因为我在帮他们解决一些问",26,180,125);
                puts256("题时，不得不参考书籍！诚然，我的C 语言的确学的很差，很多库函数我都",26,200,125);
                puts256("不懂。但是，我认为学习一门语言关键在于如何去运用。而不是单纯的计算。",26,220,125);
                puts256("学习语言需要发散思维！这也是我为何喜欢机试而讨厌笔试的原因之一。笔",26,240,125);
                puts256("试时，我不得不按照题目的思维去思考，虽然我常有更简单的算法！苦想良",26,260,125);
                puts256("久，终于决定暂时放下手中的VC++的研究，而用TC2.0写个什么东东来，而且",26,280,125);
                puts256("我也缺少这么一个经典的DOS软件。于是《黑白风云》就诞生了！",26,300,125);
                puts256("    这是我最后一个DOS下的程序了，作为对DOS时代的美好回忆吧！既然是",26,320,125);
                puts256("最后一个DOS程序，我希望能展示一下TC的魅力。永恒、经典！！",26,340,125);
                puts256("    最后特别感谢李振东同学，因为当我的计算机被别人霸用时，他忍受着",26,360,125);
                puts256("郁闷的危险，提供了编程环境！他还参与了后期测试，还要感谢老友葛新春。",26,380,125);
                puts256("因为他对我曾经的研究成果的大力赞赏，极大地鼓舞了我的信心。还要感谢",26,400,125);
                puts256("老爸的经济支持。",26,420,125);
                puts256("程晨",434,425,224);
                puts256("于四川理工",469,425,125);
                puts256("2005年3月",460,445,125);
                break ;
                case 2 :
                check=1 ;
                gameend();
                break ;
            }
        }
        else 
        if(!curtype)
        {
            curtype=1 ;
        }
        {
            char s[8];
            printf256(550,460,BLUE,"%4d,%4d",mouse.getx,mouse.gety);
        }
        showmouse();
        getmkeyin(mbLeft);
        vpost();
    }
    return(0);
}


/*此函数将使电脑走子，将canput_bai[][][]和canput_hei[][][]合并为一个数组，带入此函数中。因此不管是白还是黑都走一个子，只带回坐标*/
/*带入一个已下子的数组（新建，全局变量）*/
/*1：判断可填部分是否为角，如果为角则闭下一子*/
/*2：判断边（观察，智能关键部分）*/
/*3：对于中间部分可以随机（可以扩充智能判断）*/
/*参数用于带入flag_heibai带回参数值*/
/*可用数组canput[][][]和*/
/*当flag_chess_change为1时人执黑*/
int computer_1(int flag_chess_heibai,int flag_chess_change)
{
    if(canput[1][1][0])
    flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,1,1);
    else if(canput[1][8][0])
    flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,1,8);
    else if(canput[8][1][0])
    flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,8,1);
    else if(canput[8][8][0])
    flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,8,8);
    /*   if(flag_chess_change)
           bai[a][b][0]=1
         else
           hei[a][b][0]=1
    */
    
    return(flag_chess_heibai);
}

int computer_1_1(int flag_chess_heibai,int flag_chess_change)
{
    int a,flag=1 ;
    
    if(cpu_yiput[1][1][0])
    for(a=2;a<=6;a++)
    {
        if(ren_yiput[a][1][0]&&canput[a+1][1][0]&&flag)
        {
            flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a+1,1);
            flag=0 ;
            break ;
        }
        if(ren_yiput[1][a][0]&&canput[1][a+1][0]&&flag)
        {
            flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,1,a+1);
            flag=0 ;
            break ;
        }
    }
    
    if(cpu_yiput[1][8][0]&&flag)
    for(a=2;a<=6;a++)
    if(ren_yiput[a][8][0]&&canput[a+1][8][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a+1,8);
        flag=0 ;
        break ;
    }
    
    if(cpu_yiput[1][8][0]&&flag)
    for(a=7;a>=3;a--)
    if(ren_yiput[1][a][0]&&canput[1][a-1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,1,a-1);
        flag=0 ;
        break ;
    }
    
    if(cpu_yiput[8][1][0]&&flag)
    for(a=7;a>=3;a--)
    if(ren_yiput[a][1][0]&&canput[a-1][1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a-1,1);
        flag=0 ;
        break ;
    }
    
    if(cpu_yiput[8][1][0]&&flag)
    for(a=2;a<=6;a++)
    if(ren_yiput[8][a][0]&&canput[8][a+1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,8,a+1);
        flag=0 ;
        break ;
    }
    
    if(cpu_yiput[8][8][0]&&flag)
    for(a=7;a>=3;a--)
    {
        if(ren_yiput[8][a][0]&&canput[8][a-1][0]&&flag)
        {
            flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,8,a-1);
            flag=0 ;
            break ;
        }
        if(ren_yiput[a][8][0]&&canput[a-1][8][0]&&flag)
        {
            flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a-1,8);
            flag=0 ;
            break ;
        }
    }
    return(flag_chess_heibai);
    
}

/*用于判断边应该下子的情况*/
int computer_2_0(int flag_chess_heibai,int flag_chess_change)
{
    int a,b,flag=1 ;
    
    if(flag)
    for(a=4;a<=7;a++)
    if(cpu_yiput[a][1][0]&&ren_yiput[a-1][1][0]&&canput[a-2][1][0]&&!ren_yiput[a-3][1][0]&&!ren_yiput[a+1][1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a-2,1);
        flag=0 ;
        break ;
    }
    
    if(flag)
    for(a=4;a<=7;a++)
    if(cpu_yiput[1][a][0]&&ren_yiput[1][a-1][0]&&canput[1][a-2][0]&&!ren_yiput[1][a-3][0]&&!ren_yiput[1][a+1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,1,a-2);
        flag=0 ;
        break ;
    }
    
    if(flag)
    for(a=4;a<=7;a++)
    if(cpu_yiput[8][a][0]&&ren_yiput[8][a-1][0]&&canput[8][a-2][0]&&!ren_yiput[8][a-3][0]&&!ren_yiput[8][a+1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,8,a-2);
        flag=0 ;
        break ;
    }
    
    if(flag)
    for(a=4;a<=7;a++)
    if(cpu_yiput[a][8][0]&&ren_yiput[a-1][8][0]&&canput[a-2][8][0]&&!ren_yiput[a-3][8][0]&&!ren_yiput[a+1][8][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a-2,8);
        flag=0 ;
        break ;
    }
    
    if(flag)
    for(a=2;a<=5;a++)
    if(cpu_yiput[a][1][0]&&ren_yiput[a+1][1][0]&&canput[a+2][1][0]&&!ren_yiput[a+3][1][0]&&!ren_yiput[a-1][1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a+2,1);
        flag=0 ;
        break ;
    }
    
    if(flag)
    for(a=2;a<=5;a++)
    if(cpu_yiput[1][a][0]&&ren_yiput[1][a+1][0]&&canput[1][a+2][0]&&!ren_yiput[1][a+3][0]&&!ren_yiput[1][a-1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,1,a+2);
        flag=0 ;
        break ;
    }
    
    if(flag)
    for(a=2;a<=5;a++)
    if(cpu_yiput[8][a][0]&&ren_yiput[8][a+1][0]&&canput[8][a+2][0]&&!ren_yiput[8][a+3][0]&&!ren_yiput[8][a-1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,8,a+2);
        flag=0 ;
        break ;
    }
    
    
    if(flag)
    for(a=2;a<=5;a++)
    if(cpu_yiput[a][8][0]&&ren_yiput[a+1][8][0]&&canput[a+2][8][0]&&!ren_yiput[a+3][8][0]&&!ren_yiput[a-1][8][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a+2,8);
        flag=0 ;
        break ;
    }
    
    
    if(flag)
    if(cpu_yiput[2][1][0]&&ren_yiput[3][1][0]&&ren_yiput[4][1][0]&&ren_yiput[5][1][0]&&ren_yiput[6][1][0]&&canput[7][1][0]&&!ren_yiput[1][1][0]&&!ren_yiput[1][1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,7,1);
        flag=0 ;
    }
    
    if(flag)
    if(cpu_yiput[2][8][0]&&ren_yiput[3][8][0]&&ren_yiput[4][8][0]&&ren_yiput[5][8][0]&&ren_yiput[6][8][0]&&canput[7][8][0]&&!ren_yiput[1][8][0]&&!ren_yiput[1][8][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,7,8);
        flag=0 ;
    }
    
    if(flag)
    if(cpu_yiput[1][2][0]&&ren_yiput[1][3][0]&&ren_yiput[1][4][0]&&ren_yiput[1][5][0]&&ren_yiput[1][6][0]&&canput[1][7][0]&&!ren_yiput[1][1][0]&&!ren_yiput[1][1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,1,7);
        flag=0 ;
    }
    
    if(flag)
    if(cpu_yiput[8][2][0]&&ren_yiput[8][3][0]&&ren_yiput[8][4][0]&&ren_yiput[8][5][0]&&ren_yiput[8][6][0]&&canput[8][7][0]&&!ren_yiput[8][1][0]&&!ren_yiput[8][1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,8,7);
        flag=0 ;
    }
    
    if(flag)
    if(cpu_yiput[7][1][0]&&ren_yiput[3][1][0]&&ren_yiput[4][1][0]&&ren_yiput[5][1][0]&&ren_yiput[6][1][0]&&canput[2][1][0]&&!ren_yiput[8][1][0]&&!ren_yiput[8][1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,2,1);
        flag=0 ;
    }
    
    if(flag)
    if(cpu_yiput[7][8][0]&&ren_yiput[3][8][0]&&ren_yiput[4][8][0]&&ren_yiput[5][8][0]&&ren_yiput[6][8][0]&&canput[2][8][0]&&!ren_yiput[8][8][0]&&!ren_yiput[8][8][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,2,8);
        flag=0 ;
    }
    
    if(flag)
    if(cpu_yiput[1][7][0]&&ren_yiput[1][3][0]&&ren_yiput[1][4][0]&&ren_yiput[1][5][0]&&ren_yiput[1][6][0]&&canput[1][2][0]&&!ren_yiput[1][8][0]&&!ren_yiput[1][8][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,1,2);
        flag=0 ;
    }
    
    if(flag)
    if(cpu_yiput[8][7][0]&&ren_yiput[8][3][0]&&ren_yiput[8][4][0]&&ren_yiput[8][5][0]&&ren_yiput[8][6][0]&&canput[8][2][0]&&!ren_yiput[8][8][0]&&!ren_yiput[8][8][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,8,2);
        flag=0 ;
    }
    
    if(flag)
    for(a=5;a<=7;a++)
    if(cpu_yiput[a][1][0]&&ren_yiput[a-1][1][0]&&ren_yiput[a-2][1][0]&&canput[a-3][1][0]&&!ren_yiput[a-4][1][0]&&!ren_yiput[a+1][1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a-3,1);
        flag=0 ;
        break ;
    }
    
    if(flag)
    for(a=5;a<=7;a++)
    if(cpu_yiput[a][8][0]&&ren_yiput[a-1][8][0]&&ren_yiput[a-2][8][0]&&canput[a-3][8][0]&&!ren_yiput[a-4][8][0]&&!ren_yiput[a+1][8][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a-3,8);
        flag=0 ;
        break ;
    }
    
    if(flag)
    for(a=5;a<=7;a++)
    if(cpu_yiput[1][a][0]&&ren_yiput[1][a-1][0]&&ren_yiput[1][a-2][0]&&canput[1][a-3][0]&&!ren_yiput[1][a-4][0]&&!ren_yiput[1][a+1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,1,a-3);
        flag=0 ;
        break ;
    }
    
    if(flag)
    for(a=5;a<=7;a++)
    if(cpu_yiput[8][a][0]&&ren_yiput[8][a-1][0]&&ren_yiput[8][a-2][0]&&canput[8][a-3][0]&&!ren_yiput[8][a-4][0]&&!ren_yiput[8][a+1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,8,a-3);
        flag=0 ;
        break ;
    }
    
    if(flag)
    for(a=2;a<=4;a++)
    if(cpu_yiput[a][1][0]&&ren_yiput[a+1][1][0]&&ren_yiput[a+2][1][0]&&canput[a+3][1][0]&&!ren_yiput[a+4][1][0]&&!ren_yiput[a-1][1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a+3,1);
        flag=0 ;
        break ;
    }
    
    if(flag)
    for(a=2;a<=4;a++)
    if(cpu_yiput[a][8][0]&&ren_yiput[a+1][8][0]&&ren_yiput[a+2][8][0]&&canput[a+3][8][0]&&!ren_yiput[a+4][8][0]&&!ren_yiput[a-1][8][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a+3,8);
        flag=0 ;
        break ;
    }
    
    if(flag)
    for(a=2;a<=4;a++)
    if(cpu_yiput[1][a][0]&&ren_yiput[1][a+1][0]&&ren_yiput[1][a+2][0]&&canput[1][a+3][0]&&!ren_yiput[1][a+4][0]&&!ren_yiput[1][a-1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,1,a+1);
        flag=0 ;
        break ;
    }
    
    
    if(flag)
    for(a=2;a<=4;a++)
    if(cpu_yiput[8][a][0]&&ren_yiput[8][a+1][0]&&ren_yiput[8][a+2][0]&&canput[8][a+3][0]&&!ren_yiput[8][a+4][0]&&!ren_yiput[8][a-1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,8,a+1);
        flag=0 ;
        break ;
    }
    
    
    if(flag)
    for(a=6;a<=7;a++)
    if(cpu_yiput[a][1][0]&&ren_yiput[a-1][1][0]&&ren_yiput[a-2][1][0]&&ren_yiput[a-3][1][0]&&canput[a-4][1][0]&&!ren_yiput[a-5][1][0]&&!ren_yiput[a+1][1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a-4,1);
        flag=0 ;
        break ;
    }
    
    if(flag)
    for(a=6;a<=7;a++)
    if(cpu_yiput[a][8][0]&&ren_yiput[a-1][8][0]&&ren_yiput[a-2][8][0]&&ren_yiput[a-3][8][0]&&canput[a-4][8][0]&&!ren_yiput[a-5][8][0]&&!ren_yiput[a+1][8][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a-4,8);
        flag=0 ;
        break ;
    }
    
    if(flag)
    for(a=6;a<=7;a++)
    if(cpu_yiput[1][a][0]&&ren_yiput[1][a-1][0]&&ren_yiput[1][a-2][0]&&ren_yiput[1][a-3][0]&&canput[1][a-4][0]&&!ren_yiput[1][a-5][0]&&!ren_yiput[1][a+1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,1,a-4);
        flag=0 ;
        break ;
    }
    
    if(flag)
    for(a=6;a<=7;a++)
    if(cpu_yiput[8][a][0]&&ren_yiput[8][a-1][0]&&ren_yiput[8][a-2][0]&&ren_yiput[8][a-3][0]&&canput[8][a-4][0]&&!ren_yiput[8][a-5][0]&&!ren_yiput[8][a+1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,8,a-4);
        flag=0 ;
        break ;
    }
    
    if(flag)
    for(a=2;a<=3;a++)
    if(cpu_yiput[a][1][0]&&ren_yiput[a+1][1][0]&&ren_yiput[a+2][1][0]&&ren_yiput[a+3][1][0]&&canput[a+4][1][0]&&!ren_yiput[a+5][1][0]&&!ren_yiput[a-1][1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a+4,1);
        flag=0 ;
        break ;
    }
    
    if(flag)
    for(a=2;a<=3;a++)
    if(cpu_yiput[a][8][0]&&ren_yiput[a+1][8][0]&&ren_yiput[a+2][8][0]&&ren_yiput[a+3][8][0]&&canput[a+4][8][0]&&!ren_yiput[a+5][8][0]&&!ren_yiput[a-1][8][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a+4,8);
        flag=0 ;
        break ;
    }
    
    if(flag)
    for(a=2;a<=3;a++)
    if(cpu_yiput[1][a][0]&&ren_yiput[1][a+1][0]&&ren_yiput[1][a+2][0]&&ren_yiput[1][a+3][0]&&canput[1][a+4][0]&&!ren_yiput[1][a+5][0]&&!ren_yiput[1][a-1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,1,a+4);
        flag=0 ;
        break ;
    }
    
    if(flag)
    for(a=2;a<=3;a++)
    if(cpu_yiput[8][a][0]&&ren_yiput[8][a+1][0]&&ren_yiput[8][a+2][0]&&ren_yiput[8][a+3][0]&&canput[8][a+4][0]&&!ren_yiput[8][a+5][0]&&!ren_yiput[8][a-1][0])
    {
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,8,a+4);
        flag=0 ;
        break ;
    }
    
    
    return(flag_chess_heibai);
}


int computer_2(int flag_chess_heibai,int flag_chess_change)
{
    int a,b,rnd=0,m=0,n=0 ;
    int temp[10][10][2],canput_new[10][2];
    
    for(a=0;a<10;a++)
    for(b=0;b<10;b++)
    temp[a][b][0]=canput[a][b][0];
    
    for(a=0;a<10;a++)
    for(b=0;b<2;b++)
    canput_new[a][b]=0 ;
    
    
    for(a=4;a<=5;a++)
    {
        if(cpu_yiput[a][1][0]&&ren_yiput[a-1][1][0]&&ren_yiput[a+1][1][0]&&canput[a-2][1][0]&&canput[a+2][1][0])
        {
            temp[a-2][1][0]=0 ;
            temp[a+2][1][0]=0 ;
        }
        /*将可下子部分标记为不可下子以后再在随机下，最后恢复调用原随机计算   */
        if(cpu_yiput[a][8][0]&&ren_yiput[a-1][8][0]&&ren_yiput[a+1][8][0]&&canput[a-2][8][0]&&canput[a+2][8][0])
        {
            temp[a-2][8][0]=0 ;
            temp[a+2][8][0]=0 ;
        }
        if(cpu_yiput[1][a][0]&&ren_yiput[1][a-1][0]&&ren_yiput[1][a+1][0]&&canput[1][a-2][0]&&canput[1][a+2][0])
        {
            temp[1][a-2][0]=0 ;
            temp[1][a+2][0]=0 ;
        }
        if(cpu_yiput[8][a][0]&&ren_yiput[8][a-1][0]&&ren_yiput[8][a+1][0]&&canput[8][a-2][0]&&canput[8][a+2][0])
        {
            temp[8][a-2][0]=0 ;
            temp[8][a+2][0]=0 ;
        }
    }
    
    for(a=5;a<=7;a++)
    {
        if(cpu_yiput[a][1][0]&&ren_yiput[a-1][1][0]&&ren_yiput[a-3][1][0]&&canput[a-2][1][0])
        temp[a-2][1][0]=0 ;
        if(cpu_yiput[a][8][0]&&ren_yiput[a-1][8][0]&&ren_yiput[a-3][8][0]&&canput[a-2][8][0])
        temp[a-2][8][0]=0 ;
        if(cpu_yiput[1][a][0]&&ren_yiput[1][a-1][0]&&ren_yiput[1][a-3][0]&&canput[1][a-2][0])
        temp[1][a-2][0]=0 ;
        if(cpu_yiput[8][a][0]&&ren_yiput[8][a-1][0]&&ren_yiput[8][a-3][0]&&canput[8][a-2][0])
        temp[8][a-2][0]=0 ;
    }
    
    for(a=2;a<=4;a++)
    {
        if(cpu_yiput[a][1][0]&&ren_yiput[a+1][1][0]&&ren_yiput[a+3][1][0]&&canput[a+2][1][0])
        temp[a+2][1][0]=0 ;
        if(cpu_yiput[a][8][0]&&ren_yiput[a+1][8][0]&&ren_yiput[a+3][8][0]&&canput[a+2][8][0])
        temp[a+2][8][0]=0 ;
        if(cpu_yiput[1][a][0]&&ren_yiput[1][a+1][0]&&ren_yiput[1][a+3][0]&&canput[1][a+2][0])
        temp[1][a+2][0]=0 ;
        if(cpu_yiput[8][a][0]&&ren_yiput[8][a+1][0]&&ren_yiput[8][a+3][0]&&canput[8][a+2][0])
        temp[8][a+2][0]=0 ;
    }
    
    for(a=2;a<=5;a++)
    {
        if(ren_yiput[a][1][0]&&canput[a+1][1][0]&&!ren_yiput[a+2][1][0])
        temp[a+1][1][0]=0;
        if(ren_yiput[a][8][0]&&canput[a+1][8][0]&&!ren_yiput[a+2][8][0])
        temp[a+1][8][0]=0;
        if(ren_yiput[1][a][0]&&canput[1][a+1][0]&&!ren_yiput[1][a+2][0])
        temp[1][a+1][0]=0;
        if(ren_yiput[8][a][0]&&canput[8][a+1][0]&&!ren_yiput[8][a+2][0])
        temp[8][a+1][0]=0;

     }

    for(a=4;a<=7;a++)
    {
      if(ren_yiput[a][1][0]&&canput[a-1][1][0]&&!ren_yiput[a-2][1][0])
        temp[a-1][1][0]=0;
      if(ren_yiput[a][8][0]&&canput[a-1][8][0]&&!ren_yiput[a-2][8][0])
        temp[a-1][8][0]=0;
      if(ren_yiput[1][a][0]&&canput[1][a-1][0]&&!ren_yiput[1][a-2][0])
        temp[1][a-1][0]=0;
      if(ren_yiput[8][a][0]&&canput[8][a-1][0]&&!ren_yiput[8][a-2][0])
        temp[8][a-1][0]=0;
    }


    for(a=3;a<=6;a++)
    {
       if(temp[a][1][0])n++;
       if(temp[1][a][0])n++;
       if(temp[8][a][0])n++;
       if(temp[a][8][0])n++;

    }

    if(n)
    {
        for(a=3;a<=6;a++)
        {
            if(temp[a][1][0])
            {
                canput_new[m][0]=a ;
                canput_new[m][1]=1 ;
                m++;
            }
            if(temp[1][a][0])
            {
                canput_new[m][0]=1 ;
                canput_new[m][1]=a ;
                m++;
            }
            if(temp[8][a][0])
            {
                canput_new[m][0]=8 ;
                canput_new[m][1]=a ;
                m++;
            }
            if(temp[a][8][0])
            {
                canput_new[m][0]=a ;
                canput_new[m][1]=8 ;
                m++;
            }
            
        }
        rnd=((unsigned)biostime(0,0)+rand())%(m);
        /*产生0-m的随机数,注意这里的canput_new数组[m][0]记载的是横坐标。[m][1]是纵坐标*/
        flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,canput_new[rnd][0],canput_new[rnd][1]);

    }
    
    
    /*   if(flag)
           { flag_chess_heibai=computer_3(flag_chess_heibai,flag_chess_change);
             flag=0;
            }
    
             if(flag)
           { flag_chess_heibai=computer_4(flag_chess_heibai,flag_chess_change);
             flag=0;
            }
        */
    
    
    /*   if(flag)
    
            flag_chess_heibai=computer_5(flag_chess_heibai,flag_chess_change);
    
        */
    
    /*
           for(a=3;a<=6;a++)
               {
                 if(canput[a][1][0])  {flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a,1) ;break;}
                 else if(canput[1][a][0]) { flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,1,a) ;break;}
                 else if(canput[8][a][0])  {  flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,8,a) ; break;}
                 else if(canput[a][8][0]) { flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a,8) ; break;}
    
               }  */
return(flag_chess_heibai);
}

int computer_2_1(int flag_chess_heibai,int flag_chess_change)
{
    int a,b,rnd=0,m=0 ;
    int canput_new[10][2];
    
    for(a=0;a<10;a++)
    for(b=0;b<2;b++)
    canput_new[a][b]=0 ;
    
    for(a=3;a<=6;a++)
    {
        if(canput[a][1][0])
        {
            canput_new[m][0]=a ;
            canput_new[m][1]=1 ;
            m++;
        }
        if(canput[1][a][0])
        {
            canput_new[m][0]=1 ;
            canput_new[m][1]=a ;
            m++;
        }
        if(canput[8][a][0])
        {
            canput_new[m][0]=8 ;
            canput_new[m][1]=a ;
            m++;
        }
        if(canput[a][8][0])
        {
            canput_new[m][0]=a ;
            canput_new[m][1]=8 ;
            m++;
        }
        
    }
    rnd=((unsigned)biostime(0,0)+rand())%(m);
    /* 产生0-m的随机数 */
    flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,canput_new[rnd][0],canput_new[rnd][1]);
    
    return(flag_chess_heibai);
}


int computer_3(int flag_chess_heibai,int flag_chess_change)
{
    int a,b,rnd=0,m=0 ;
    int canput_new[10][2];
    
    for(a=0;a<10;a++)
    for(b=0;b<2;b++)
    canput_new[a][b]=0 ;
    
    for(a=3;a<=6;a++)
    {
        if(canput[a][3][0])
        {
            canput_new[m][0]=a ;
            canput_new[m][1]=3 ;
            m++;
        }
        if(canput[3][a][0])
        {
            canput_new[m][0]=3 ;
            canput_new[m][1]=a ;
            m++;
        }
        if(canput[6][a][0])
        {
            canput_new[m][0]=6 ;
            canput_new[m][1]=a ;
            m++;
        }
        if(canput[a][6][0])
        {
            canput_new[m][0]=a ;
            canput_new[m][1]=6 ;
            m++;
        }
        
    }
    rnd=((unsigned)biostime(0,0)+rand())%(m);
    /*产生0-m的随机数*/
    flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,canput_new[rnd][0],canput_new[rnd][1]);
    
    
    
    /* int a,b;
          for(a=3;a<=6;a++)
               {
                 if(canput[a][3][0])  {flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a,3) ;break;}
                 else if(canput[3][a][0]) { flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,3,a) ;break;}
                 else if(canput[6][a][0])  {  flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,6,a) ; break;}
                 else if(canput[a][6][0]) { flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a,6) ; break;}
               }
        */
    return(flag_chess_heibai);
}

int computer_4(int flag_chess_heibai,int flag_chess_change)
{
    int a,b,rnd=0,m=0 ;
    int canput_new[10][2];
    
    for(a=0;a<10;a++)
    for(b=0;b<2;b++)
    canput_new[a][b]=0 ;
    
    for(a=3;a<=6;a++)
    {
        if(canput[a][2][0])
        {
            canput_new[m][0]=a ;
            canput_new[m][1]=2 ;
            m++;
        }
        if(canput[2][a][0])
        {
            canput_new[m][0]=2 ;
            canput_new[m][1]=a ;
            m++;
        }
        if(canput[7][a][0])
        {
            canput_new[m][0]=7 ;
            canput_new[m][1]=a ;
            m++;
        }
        if(canput[a][7][0])
        {
            canput_new[m][0]=a ;
            canput_new[m][1]=7 ;
            m++;
        }
        
    }
    rnd=((unsigned)biostime(0,0)+rand())%(m);
    /*产生0-m的随机数*/
    flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,canput_new[rnd][0],canput_new[rnd][1]);
    /*
       int a,b;
        for(a=3;a<=6;a++)
               {
                 if(canput[a][2][0])  {flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a,2) ;break;}
                 else if(canput[2][a][0]) { flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,2,a) ;break;}
                 else if(canput[7][a][0])  {  flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,7,a) ; break;}
                 else if(canput[a][7][0]) { flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,a,7) ; break;}
               }
        */
    return(flag_chess_heibai);
}

int computer_5(int flag_chess_heibai,int flag_chess_change)
{
    int a,b,rnd=0,m=0 ;
    int canput_new[10][2];
    
    for(a=0;a<10;a++)
    for(b=0;b<2;b++)
    canput_new[a][b]=0 ;
    
    if(canput[1][2][0])
    {
        canput_new[m][0]=1 ;
        canput_new[m][1]=2 ;
        m++;
    }
    if(canput[1][7][0])
    {
        canput_new[m][0]=1 ;
        canput_new[m][1]=7 ;
        m++;
    }
    if(canput[2][1][0])
    {
        canput_new[m][0]=2 ;
        canput_new[m][1]=1 ;
        m++;
    }
    if(canput[2][2][0])
    {
        canput_new[m][0]=2 ;
        canput_new[m][1]=2 ;
        m++;
    }
    if(canput[2][7][0])
    {
        canput_new[m][0]=2 ;
        canput_new[m][1]=7 ;
        m++;
    }
    if(canput[2][8][0])
    {
        canput_new[m][0]=2 ;
        canput_new[m][1]=8 ;
        m++;
    }
    if(canput[7][1][0])
    {
        canput_new[m][0]=7 ;
        canput_new[m][1]=1 ;
        m++;
    }
    if(canput[7][2][0])
    {
        canput_new[m][0]=7 ;
        canput_new[m][1]=2 ;
        m++;
    }
    if(canput[7][7][0])
    {
        canput_new[m][0]=7 ;
        canput_new[m][1]=7 ;
        m++;
    }
    if(canput[7][8][0])
    {
        canput_new[m][0]=7 ;
        canput_new[m][1]=8 ;
        m++;
    }
    if(canput[8][7][0])
    {
        canput_new[m][0]=8 ;
        canput_new[m][1]=7 ;
        m++;
    }
    if(canput[8][2][0])
    {
        canput_new[m][0]=8 ;
        canput_new[m][1]=2 ;
        m++;
    }
    
    rnd=((unsigned)biostime(0,0)+rand())%(m);
    /*产生0-m的随机数*/
    flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,canput_new[rnd][0],canput_new[rnd][1]);
    
    
    /*
               if (canput[1][2][0])flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,1,2)        ;
               else if (canput[1][7][0])flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,1,7)   ;
               else if (canput[2][1][0])flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,2,1)   ;
               else if (canput[2][2][0])flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,2,2)   ;
               else if (canput[2][7][0])flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,2,7)   ;
               else if (canput[2][8][0])flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,2,8)   ;
               else if (canput[7][1][0])flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,7,1)   ;
               else if (canput[7][2][0])flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,7,2)   ;
               else if (canput[7][7][0])flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,7,7)   ;
               else if (canput[7][8][0])flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,7,8)   ;
               else if (canput[8][2][0])flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,8,2)   ;
               else if (canput[8][7][0])flag_chess_heibai=changechess(flag_chess_heibai,flag_chess_change,8,7)   ;
               */
    return(flag_chess_heibai);
}

int computer_6(int flag_chess_heibai,int flag_chess_change)
{
    
    
    return(flag_chess_heibai);
}

/*这个函数用于电脑翻子,有人可能会问为什么前面的不直接带此函数，那是因为我那时还没有想到，代码我又懒得去改。*/
/*j,i用于计算机放子的坐标*/
int changechess(int flag_chess_heibai2,int flag_chess_change2,int j,int i)
{
    int a,b,c,d ;
    int hei_new[10][10][2],bai_new[10][10][2];
    xx=j ;
    yy=i ;
    /*用于标记电脑刚下子的位置*/
    for(a=0;a<9;a++)
    for(b=0;b<9;b++)
    {
        hei_new[a][b][0]=hei[a][b][0];
        bai_new[a][b][0]=bai[a][b][0];
    }
    
    
    if(flag_chess_change2)
    {
        bai[j][i][0]=1 ;
        /*以下代码为替换黑白子功能，由于如果把原数组附值后，后面的判断就会把修改后的数组判断进去。所以应该再使用新数组，最后将值代入原数组！*/
        
        if(hei[j+1][i][0]==1)
        for(a=j+1;a<9;a++)
        {
            if(bai[a][i][0]==1)
            {
                for(c=j;c<=a;c++)
                {
                    bai_new[c][i][0]=1 ;
                    hei_new[c][i][0]=0 ;
                }
                break ;
            }
            
        }
        
        if(hei[j][i-1][0]==1)
        for(b=i-1;b>0;b--)
        {
            if(bai[j][b][0]==1)
            {
                for(c=i;c>=b;c--)
                {
                    bai_new[j][c][0]=1 ;
                    hei_new[j][c][0]=0 ;
                }
                break ;
            }
            
        }
        
        if(hei[j][i+1][0]==1)
        for(b=i+1;b<9;b++)
        {
            if(bai[j][b][0]==1)
            {
                for(c=i;c<=b;c++)
                {
                    bai_new[j][c][0]=1 ;
                    hei_new[j][c][0]=0 ;
                }
                break ;
            }
            
        }
        
        if(hei[j-1][i][0]==1)
        for(a=j-1;a>0;a--)
        {
            if(bai[a][i][0]==1)
            {
                
                for(c=j;c>=a;c--)
                {
                    bai_new[c][i][0]=1 ;
                    hei_new[c][i][0]=0 ;
                }
                break ;
            }
        }
        
        /*这种算法和前面的判断可填空格不一样，优点是结构更清晰。更简单*/
        if(hei[j+1][i+1][0]==1)for(a=j+1,b=i+1,d=0;b<9;a++,b++,d++)
        {
            if(a>8)break ;
            if(bai[a][b][0]==1)
            {
                for(c=0;c<=d;c++)
                {
                    bai_new[j+c][i+c][0]=1 ;
                    hei_new[j+c][i+c][0]=0 ;
                }
                break ;
            }
        }
        
        if(hei[j-1][i-1][0]==1)
        for(a=j-1,b=i-1,d=0;b>0;a--,b--,d++)
        {
            if(a<1)break ;
            if(bai[a][b][0]==1)
            
            {
                
                for(c=0;c<=d;c++)
                {
                    bai_new[j-c][i-c][0]=1 ;
                    hei_new[j-c][i-c][0]=0 ;
                }
                break ;
            }
        }
        
        if(hei[j+1][i-1][0]==1)
        for(a=j+1,b=i-1,d=0;b>0;b--,a++,d++)
        {
            if(a>8)break ;
            if(bai[a][b][0]==1)
            
            {
                
                for(c=0;c<=d;c++)
                {
                    bai_new[j+c][i-c][0]=1 ;
                    hei_new[j+c][i-c][0]=0 ;
                }
                break ;
            }
        }
        
        if(hei[j-1][i+1][0]==1)
        for(a=j-1,b=i+1,d=0;b<9;b++,a--,d++)
        {
            if(a<1)break ;
            if(bai[a][b][0]==1)
            {
                for(c=0;c<=d;c++)
                {
                    bai_new[j-c][i+c][0]=1 ;
                    hei_new[j-c][i+c][0]=0 ;
                }
                break ;
            }
        }
        
        
    }
    
    
    else 
    {
        hei[j][i][0]=1 ;
        if(bai[j+1][i][0]==1)
        for(a=j+1;a<9;a++)
        {
            if(hei[a][i][0]==1)
            
            {
                for(c=j;c<=a;c++)
                {
                    bai_new[c][i][0]=0 ;
                    hei_new[c][i][0]=1 ;
                }
                break ;
            }
        }
        
        if(bai[j][i-1][0]==1)
        for(b=i-1;b>0;b--)
        {
            if(hei[j][b][0]==1)
            
            {
                for(c=i;c>=b;c--)
                {
                    bai_new[j][c][0]=0 ;
                    hei_new[j][c][0]=1 ;
                }
                break ;
            }
        }
        
        if(bai[j][i+1][0]==1)
        for(b=i+1;b<9;b++)
        {
            if(hei[j][b][0]==1)
            
            {
                for(c=i;c<=b;c++)
                {
                    bai_new[j][c][0]=0 ;
                    hei_new[j][c][0]=1 ;
                }
                break ;
            }
        }
        
        if(bai[j-1][i][0]==1)
        for(a=j-1;a>0;a--)
        {
            if(hei[a][i][0]==1)
            
            {
                for(c=j;c>=a;c--)
                {
                    bai_new[c][i][0]=0 ;
                    hei_new[c][i][0]=1 ;
                }
                break ;
            }
        }
        
        if(bai[j+1][i+1][0]==1)
        for(a=j+1,b=i+1,d=0;b<9;a++,b++,d++)
        {
            if(a>8)break ;
            if(hei[a][b][0]==1)
            {
                for(c=0;c<=d;c++)
                {
                    bai_new[j+c][i+c][0]=0 ;
                    hei_new[j+c][i+c][0]=1 ;
                }
                break ;
            }
        }
        
        if(bai[j-1][i-1][0]==1)
        for(a=j-1,b=i-1,d=0;b>0;a--,b--,d++)
        {
            if(a<1)break ;
            if(hei[a][b][0]==1)
            
            {
                
                for(c=0;c<=d;c++)
                {
                    bai_new[j-c][i-c][0]=0 ;
                    hei_new[j-c][i-c][0]=1 ;
                }
                break ;
            }
        }
        
        if(bai[j+1][i-1][0]==1)
        for(a=j+1,b=i-1,d=0;b>0;b--,a++,d++)
        {
            if(a>8)break ;
            if(hei[a][b][0]==1)
            
            {
                
                for(c=0;c<=d;c++)
                {
                    bai_new[j+c][i-c][0]=0 ;
                    hei_new[j+c][i-c][0]=1 ;
                }
                break ;
            }
        }
        
        if(bai[j-1][i+1][0]==1)
        for(a=j-1,b=i+1,d=0;b<9;b++,a--,d++)
        {
            if(a<1)break ;
            if(hei[a][b][0]==1)
            {
                for(c=0;c<=d;c++)
                {
                    bai_new[j-c][i+c][0]=0 ;
                    hei_new[j-c][i+c][0]=1 ;
                }
                break ;
            }
        }
        
        
    }
    /*以下代码用于付值*/
    for(a=0;a<9;a++)
    for(b=0;b<9;b++)
    {
        hei[a][b][0]=hei_new[a][b][0];
        bai[a][b][0]=bai_new[a][b][0];
    }
    count_step++;
    flag_chess_heibai2=(!flag_chess_heibai2);
    flag_cpuyixia=1 ;
    /*只要有翻子就说明电脑下子了*/
    return(flag_chess_heibai2);
}




/*调色板渐入*/
void StepIn()
{
    int i ;
    for(i=0;i<256;i++)setpal(i,PAL[i][0]*Step/64,PAL[i][1]*Step/64,PAL[i][2]*Step/64);
    Step++;
    if(Step>64)KillAllTimer();
}
/* 调色板渐出 */
void StepOut()
{
    int i ;
    for(i=0;i<256;i++)setpal(i,PAL[i][0]*Step/64,PAL[i][1]*Step/64,PAL[i][2]*Step/64);
    Step--;
    if(Step<1)KillAllTimer();
}
/*将图形调入内存*/
void ClearScreen()
{
    int x,y ;

    for(y=0;y<=200;y++)for(x=0;x<=320;x++)Pset(x,y,n);

}
/*调入开始画面*/
void Logo()
{
    FILE*bmp ;
    int i,r,g,b,x,y ;
    setmode2();
    sleep(2);
    bmp=fopen("skin\\logo.bmp","rb");
    fseek(bmp,54,SEEK_SET);
    for(i=0;i<256;i++)
    {
        PAL[i][2]=fgetc(bmp)>>2 ;
        PAL[i][1]=fgetc(bmp)>>2 ;
        PAL[i][0]=fgetc(bmp)>>2 ;
        fgetc(bmp);
        setpal(i,0,0,0);
    }
    for(y=0;y<200;y++)
    for(x=0;x<320;x++)pokeb(0xa000,y*320+x,fgetc(bmp));
    fclose(bmp);
    CreateTimer(1,StepIn);
    while(ScanKey()!=1&&TimerUsed)TimerEvent();
    Step=64 ;
    StepIn();
    CreateTimer(1,StepOut);
    while(ScanKey()!=1&&TimerUsed)TimerEvent();
    Step=0 ;
    StepOut();
    setpal(0,64,64,64);
}

/*显示火焰特效*/
void movie()
{
    int x,y,c ;
    for(x=1;x<=32;x++)
    {
        setpal(x,x*2-1,0,0);
        setpal(x+32,63,x*2-1,0);
        setpal(x+64,63,63,x*2-1);
        setpal(x+96,63,63,63);
    }
    showchn();
    while(ScanKey()!=28) /*1是ESC键，57是空格键，28是回车键*/
    {
        /*
                                          for (i=0;i<16;i++)
                                                   for (j=0;j<16;j++)
                                                   pset(random(300)+j,random(150)+i,random(256));
                                                                                      */
        for(x=0;x<320;x+=2)
        {
            for(y=1;y<=202;y+=2)
            {
                c=(point(x,y)+point(x+2,y)+point(x,y+2)+point(x+2,y+2))>>2 ;
                if(c--)
                {
                    poke(0xa000,(y-2)*320+x,(c<<8)+c);
                    poke(0xa000,(y-1)*320+x,(c<<8)+c);
                }
            }
            y-=2 ;
            pset(x,y,random(320));
            showchn();
        }
    }
}

void drawmat(char *mat,int matsize,int x,int y,int color)
/*依次：字模指针、点阵大小、起始坐标(x,y)、颜色*/
{
  int i, j, k, n;
  n = (matsize - 1) / 8 + 1;
  for(j = 0; j < matsize; j++)
    for(i = 0; i < n; i++)
      for(k = 0;k < 8; k++)
        if(mat[j * n + i] & (0x80 >> k))  /*测试为1的位则显示*/
          pset(x + i * 8 + k, y + j, color);
}


showchn()
{
    char hei48H[]=
    {
        /* 以下是 '黑' 的 48点阵华文行楷 字模，288 byte */
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0xFF,0x80,0x00,0x00,0x00,
        0x1F,0xFF,0xC0,0x00,0x00,0x00,0x7F,0xFF,
        0xE0,0x00,0x00,0x00,0xFF,0x01,0xF0,0x00,
        0x00,0x11,0xFF,0xB9,0xF0,0x00,0x00,0x1F,
        0x0F,0xFD,0xF0,0x00,0x00,0x0E,0x07,0x9F,
        0xE0,0x00,0x00,0x07,0x07,0xBF,0xE0,0x00,
        0x00,0x07,0x7F,0xBF,0xC0,0x00,0x00,0x07,
        0x7F,0xFF,0xC0,0x00,0x00,0x07,0x7B,0xE7,
        0x80,0x00,0x00,0x07,0x7B,0xDF,0x80,0x00,
        0x00,0x03,0x37,0xFF,0x00,0x00,0x00,0x03,
        0x1F,0xFE,0x00,0x00,0x00,0x03,0xFF,0xF8,
        0x00,0x00,0x00,0x01,0xFF,0xC0,0x00,0x00,
        0x00,0x00,0xFF,0x80,0x00,0x00,0x00,0x00,
        0x0F,0xF0,0x00,0x00,0x00,0x00,0xFF,0xF8,
        0x00,0x00,0x00,0x01,0xFF,0xF0,0x00,0x00,
        0x00,0x01,0xFF,0xC0,0x00,0x00,0x00,0x00,
        0xFF,0xE0,0x00,0x00,0x00,0x00,0x1F,0xFC,
        0x00,0x00,0x00,0x00,0x3F,0xFE,0x00,0x00,
        0x00,0x01,0xFF,0xFE,0x00,0x00,0x00,0x03,
        0xFF,0xFE,0x00,0x00,0x00,0x03,0xFC,0x00,
        0x00,0x00,0x00,0x01,0xE0,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0xFF,0xFC,0x00,0x01,0x8F,0xFF,0xFC,
        0x0E,0x00,0x01,0xFF,0xDF,0xF0,0x0F,0x00,
        0x03,0xFE,0x0F,0xC0,0xFF,0x00,0x03,0xF8,
        0x00,0x03,0xFF,0x00,0x01,0xE0,0x00,0x00,
        0x7F,0x00,0x01,0xC0,0x00,0x00,0x02,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    }
    ;
    char bai48H[]=
    {
        /* 以下是 '白' 的 48点阵华文行楷 字模，288 byte */
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,
        0x00,0x00,0x00,0x00,0x1F,0x00,0x00,0x00,
        0x00,0x00,0x1F,0x80,0x00,0x00,0x00,0x00,
        0x1F,0xC0,0x00,0x00,0x00,0x00,0x3F,0xC0,
        0x00,0x00,0x00,0x00,0x3F,0x80,0x00,0x00,
        0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00,
        0x7E,0x00,0x00,0x00,0x00,0x00,0xFC,0x00,
        0x00,0x00,0x00,0x00,0xF8,0x3F,0x80,0x00,
        0x00,0x01,0xF3,0xFF,0xF0,0x00,0x00,0x03,
        0xEF,0xFF,0xF8,0x00,0x00,0x1F,0xFF,0xFF,
        0xFC,0x00,0x00,0x1F,0x7F,0xF0,0x7E,0x00,
        0x00,0x1C,0x7F,0x80,0x7E,0x00,0x00,0x1E,
        0x82,0x00,0x7E,0x00,0x00,0x1F,0x00,0x00,
        0x7E,0x00,0x00,0x1F,0x01,0xF0,0x7E,0x00,
        0x00,0x1E,0x1F,0xF8,0x7C,0x00,0x00,0x0F,
        0x7F,0xFC,0x7C,0x00,0x00,0x0F,0x7F,0xF8,
        0xFC,0x00,0x00,0x0F,0x3F,0xF0,0xFC,0x00,
        0x00,0x0F,0x1F,0x80,0xFC,0x00,0x00,0x0F,
        0x10,0x00,0xF8,0x00,0x00,0x0F,0x00,0x01,
        0xF8,0x00,0x00,0x0F,0x00,0x01,0xF8,0x00,
        0x00,0x07,0x03,0xF1,0xF8,0x00,0x00,0x07,
        0xFF,0xF9,0xF0,0x00,0x00,0x07,0xFF,0xFF,
        0xF0,0x00,0x00,0x03,0xFF,0xFF,0xF0,0x00,
        0x00,0x03,0xFC,0x0F,0xE0,0x00,0x00,0x01,
        0xE0,0x07,0xE0,0x00,0x00,0x00,0x80,0x07,
        0xC0,0x00,0x00,0x00,0x00,0x03,0x80,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    }
    ;
    char feng48H[]=
    {
        /* 以下是 '风' 的 48点阵华文行楷 字模，288 byte */
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0xFF,
        0x80,0x00,0x00,0x00,0x03,0xFF,0xC0,0x00,
        0x00,0x00,0x07,0xE3,0xC0,0x00,0x00,0x00,
        0x1F,0xC7,0xE0,0x00,0x00,0x00,0x3F,0x87,
        0xC0,0x00,0x00,0x00,0xFF,0x07,0x80,0x00,
        0x00,0x41,0xFC,0x07,0x80,0x00,0x00,0x7B,
        0xF8,0x07,0x80,0x00,0x00,0x3F,0x00,0x07,
        0x80,0x00,0x00,0x3E,0x1F,0x87,0x00,0x00,
        0x00,0x3E,0x0F,0xCF,0x00,0x00,0x00,0x3C,
        0x0F,0xCF,0x00,0x00,0x00,0x3C,0x0F,0x8F,
        0x00,0x00,0x00,0x38,0x0F,0x8E,0x00,0x00,
        0x00,0x38,0x1F,0x8E,0x00,0x00,0x00,0x38,
        0x1F,0x0E,0x00,0x00,0x00,0x3F,0xDF,0x0E,
        0x00,0x00,0x00,0x3F,0xFF,0x0E,0x00,0x00,
        0x00,0x3F,0xFF,0x0E,0x00,0x00,0x00,0x38,
        0xFF,0x8F,0x00,0x00,0x00,0x38,0xFF,0xCE,
        0xC0,0x00,0x00,0x38,0xFF,0xCE,0x60,0x00,
        0x00,0x38,0xFF,0xEE,0x30,0x00,0x00,0x79,
        0xFF,0xEE,0x18,0x00,0x00,0x79,0xFB,0xEE,
        0x0C,0x00,0x00,0x7F,0xF1,0xEF,0x06,0x00,
        0x00,0x77,0xE0,0xE7,0x07,0x00,0x01,0xF7,
        0xC0,0x27,0x03,0x80,0x01,0xF3,0x80,0x07,
        0x81,0xC0,0x01,0xF0,0x00,0x07,0x81,0xE0,
        0x01,0xE0,0x00,0x03,0xE1,0xF0,0x01,0xC0,
        0x00,0x01,0xFF,0xFC,0x01,0x80,0x00,0x01,
        0xFF,0xFC,0x00,0x00,0x00,0x00,0x7F,0xFC,
        0x00,0x00,0x00,0x00,0x0F,0xF0,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    }
    ;
    char yun48H[]=
    {
        /* 以下是 '云' 的 48点阵华文行楷 字模，288 byte */
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,
        0x00,0x00,0x00,0x00,0x00,0x7E,0x00,0x00,
        0x00,0x00,0x3F,0xFF,0x00,0x00,0x00,0x00,
        0x1F,0xFF,0x80,0x00,0x00,0x00,0x1F,0xFF,
        0x80,0x00,0x00,0x00,0x0F,0xFF,0x00,0x00,
        0x00,0x00,0x07,0xFE,0x00,0x00,0x00,0x00,
        0x07,0xF8,0x00,0x00,0x00,0x00,0x03,0xF0,
        0x00,0x00,0x00,0x00,0x07,0xE0,0x00,0x00,
        0x00,0x00,0x0F,0x80,0x00,0x00,0x00,0x00,
        0x1F,0x00,0x78,0x00,0x00,0x00,0x3C,0x1F,
        0xFC,0x00,0x00,0x00,0xF0,0xFF,0xFC,0x00,
        0x00,0x01,0xCF,0xFF,0xFE,0x00,0x00,0x07,
        0x3F,0xFF,0xFC,0x00,0x00,0x1D,0xFF,0xFF,
        0xF0,0x00,0x00,0x67,0xFF,0xFF,0x80,0x00,
        0x01,0xBF,0xFF,0xFE,0x00,0x00,0x03,0xFF,
        0xF3,0xF8,0x00,0x00,0x03,0xFF,0x87,0xF0,
        0x00,0x00,0x01,0xFE,0x0F,0xCC,0x00,0x00,
        0x00,0xF8,0x3F,0x8F,0x00,0x00,0x00,0x00,
        0x7E,0x0F,0xC0,0x00,0x00,0x00,0xFC,0x1F,
        0xE0,0x00,0x00,0x03,0xFB,0xFF,0xE0,0x00,
        0x00,0x03,0xFF,0xFF,0xF0,0x00,0x00,0x07,
        0xFF,0xFF,0xF0,0x00,0x00,0x07,0xFF,0xE3,
        0xF0,0x00,0x00,0x07,0xFF,0x01,0xF8,0x00,
        0x00,0x03,0xFC,0x01,0xF8,0x00,0x00,0x03,
        0xF0,0x00,0xF8,0x00,0x00,0x01,0xE0,0x00,
        0xF0,0x00,0x00,0x01,0xC0,0x00,0x70,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    }
    ;
    char cheng12S[]=
    {
        /* 以下是 '程' 的 12点阵宋体 字模，24 byte */
        0x37,0xC0,0xE4,0x40,0x24,0x40,0xF7,0xC0,
        0x20,0x00,0x6F,0xE0,0x71,0x00,0xA7,0xC0,
        0xA1,0x00,0x21,0x00,0x2F,0xE0,0x00,0x00,
    }
    ;
    char xu12S[]=
    {
        /* 以下是 '序' 的 12点阵宋体 字模，24 byte */
        0x04,0x00,0x7F,0xE0,0x40,0x00,0x5F,0x80,
        0x45,0x00,0x42,0x00,0x7F,0xE0,0x42,0x40,
        0x42,0x00,0x82,0x00,0x8E,0x00,0x00,0x00,
    }
    ;
    
    char she12S[]=
    {
        /* 以下是 '设' 的 12点阵宋体 字模，24 byte */
        0x47,0x80,0x24,0x80,0x04,0x80,0x04,0xE0,
        0xE8,0x00,0x37,0xC0,0x24,0x40,0x22,0x80,
        0x31,0x00,0x22,0x80,0x1C,0x60,0x00,0x00,
    }
    ;
    
    char ji12S[]=
    {
        /* 以下是 '计' 的 12点阵宋体 字模，24 byte */
        0x41,0x00,0x21,0x00,0x01,0x00,0x01,0x00,
        0xCF,0xE0,0x41,0x00,0x41,0x00,0x41,0x00,
        0x51,0x00,0x61,0x00,0x41,0x00,0x00,0x00,
    }
    ;
    char m12S[]=
    {
        /* 以下是 '：' 的 12点阵宋体 字模，24 byte */
        0x00,0x00,0x00,0x00,0x0C,0x00,0x0C,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x00,
        0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    }
    ;
    
    char chen12S[]=
    {
        /* 以下是 '晨' 的 12点阵宋体 字模，24 byte */
        0x3F,0xC0,0x20,0x40,0x3F,0xC0,0x20,0x40,
        0x7F,0xE0,0x40,0x00,0x7F,0xE0,0x54,0x40,
        0x52,0x80,0x55,0x00,0x98,0xE0,0x00,0x00,
    }
    ;
    /*显示开场汉字信息*/
    drawmat(hei48H,48,70,40,20);
    drawmat(bai48H,48,110,40,20);
    drawmat(feng48H,48,150,40,20);
    drawmat(yun48H,48,190,40,20);
    drawmat(cheng12S,12,150,85,15);
    drawmat(xu12S,12,165,85,15);
    drawmat(she12S,12,180,85,15);
    drawmat(ji12S,12,195,85,15);
    drawmat(m12S,12,210,85,15);
    drawmat(cheng12S,12,225,85,15);
    drawmat(chen12S,12,240,85,15);
}
/*
main()
{
    Video=farmalloc(64000);
    if(Video==NULL)
    {
        printf("Not enough Memory!\n");
        exit(0);
    }
    Logo();
    setmode();

    movie();
    wait();
    closemode();
    farfree(Video);

}   */





main()
{
    char key ;
    
    Logo();
    setmode2();
    movie();
    closemode();
    init256(SINGLE_SURFACE);
    /*初始化屏幕缓冲为单缓冲页结构，该语句必须写在最前面*/
    initmouse();
    /*初始化256色鼠标*/
    initalpha();
    /*初始化颜色匹配矩阵*/
    
    /*开始加载各项资源，注意：该图像资源除了用DestroyAllImage释放所有资源外(复位BMP加载指针)，没有提供其他方式进行释放*/
    /*因此，保证资源只被加载一次*/
    back=LoadBMP("skin\\back.bmp");
    askfirst=LoadBMP("skin\\askfirst.bmp");
    askend=LoadBMP("skin\\askend.bmp");
    game=LoadBMP("skin\\game.bmp");
    help=LoadBMP("skin\\help.bmp");
    black=LoadBMP("skin\\black.bmp");
    white=LoadBMP("skin\\white.bmp");
    START :
    cls(0);
    gamemain_new();
    close256();
}

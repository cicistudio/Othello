#include "256basic.h"
/*256ɫģʽ������������ͷ�ļ�*/
#include "256mouse.h"    
/*256ɫģʽ�����֧�ֵ�ͷ�ļ�*/
#include "image.h"    
/*λͼͼ�����͡�����ͼ�����Ͳ���������*/
#include "puts256.h"    
/*256ɫ�ı�����������*/
#include "draw.h"    
/*256ɫͼ�λ�ͼ������*/
#include "do_image.h"    
/*256ɫͼ��ϵͳ��Ч������*/
#include "slb256.h"     
/*������ļ��Ĳ���������*/
#include "alpha256.h"   
/*ALPHA������������*/


#include<dos.h>
#include "13H.h"
/* 300x200 ͼ����ʾģʽ*/
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
/*�˻���ս*/
void gamemain_2(void);
/*���˴�ս*/
void gameend(void);
/*��Ϸ����*/
void gamemain_new(void);
/*��Ϸ��ʼ��*/
void gamemain_2_game(void);
/*��Ϸ���˵�*/
void gamemain_2_help(void);
/*�������˵�*/
int computer_1(int,int);
int computer_1_1(int,int);
int comuter_2_0(int,int);
int computer_2(int,int);
int computer_2_1(int,int);
int computer_3(int,int);
int computer_4(int,int);
int computer_5(int,int);
int computer_6(int,int);
/*��������*/
int changechess(int,int,int,int);
/*���Է����ж�*/
int xx=0,yy=0 ;
/* ���ڱ�ǵ��Ը����ӵ�λ��*/
int count_step ;
/*ÿ��һ��������ͼ�һ�������ж���Ϸ����*/
/*�����㷨�����򻯣����Ǹ�����ά����˼ά����*/

/*��ý���Դ�������ⲿ���Ա������ģ�鶼����ʹ��*/
Bmp256 back ;
Bmp256 askfirst,askend ;
Bmp256 game,help ;
Bmp256 black,white ;
int check=0 ;
/*��������ָ���ж�*/
int hei[10][10][2],bai[10][10][2],ren_yiput[10][10][2],cpu_yiput[10][10][2];
/*���������ڴ�������ӵ�ַ*/
int canput_hei[10][10][2],canput_bai[10][10][2];
/*���������ڿɷ��ӵĵ�ַ*/
int canput[10][10][2];
/*���������ںϲ���Ŀɴ�ŵ�ַ���������ӵĵ�ַ������Ҫ����һ����Ҫ�����������ж�*/

int flag_changechess=1 ;
/*�����ж��˻���սʱ����������*/
int flag_whozhizi=1 ;
/*��flag_whozhiziΪ1ʱ��ִ�ڣ�������ִ��*/
int flag_cpuyixia=0 ;
/*���ڱ�ǵ����Ƿ�����*/
int flag_show=0 ;
/*flag_show�����Ƿ���ʾ��ǿ���մ�*/

BYTE PAL[256][3];
int Step=0 ;
int n=0 ;

/*�̳�������õ����ı��*/


void choosemode(void)
{
    int i,j ;
    char is_on,key ;
    static char curtype=1,texts[3][16]=
    {
        /*��ȻΪ�յ���ͼƬ��λ����һֱ�ģ�*/
        "        ","        ","  " 
    }
    ;
    
    do 
    {
        while(getmkeyin(mbRight)!=mbRight)
        {
            hidemouse();
            QPutImage(0,0,back);
            /*�������ͼ*/
            QPutImage(240,150,askfirst);
            /*���ѡ��ģʽ*/
            /*��ΪҪ�����µ������ͼ��ֻ��mouse�����غ���ܽ���*/
            /*for(j=0;j<7;j++)
                                                        for(i=0;i<8;i++)       СͼƬ��̬��ʾ
                                                        QPutImage(-bk_tc.width+a+i*bk_tc.width,-b+j*bk_tc.height,bk_tc);
                                                        a=(a+1)%bk_tc.width ;
                                                        b=(b+1)%bk_tc.height ; */
            /*TEXT_SIZE=TX_NORMAL ;  12������ʾ*/
            TEXT_SIZE=TX_BIG ;
            /*16������ʾ*/
            getmousexy();
            is_on=-1 ;
            for(i=0;i<2;i++)
            /*����굽ʲôλ��ʱ�ͽ�����ʱ��ɫ���������λ�������Ҫ�Ǵ˺�������*/
            if(mouse.getx>=272&&mouse.getx<=345&&mouse.gety>=200+i*30&&mouse.gety<=216+i*30)
            {
                is_on=i ;
                puts256(texts[i],275,200+i*30,BLUE);
                /*��ʾҪ����ĺ���λ��*/
                /* line(48,218+i*40,185,218+i*40,BLUE);  �����滭�ߣ���ʾ����*/
            }
            else puts256(texts[i],275,200+i*30,0);
            
            /*�жϲ���������Ҫ�Ǵ˺�������*/
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
                    /*��������꣺3D��ͷ*/
                    curtype=0 ;
                }
                if(getmkeyin(mbLeft)==mbLeft)
                /*��������Ӧ����*/
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
                /*��������꣺���ι��*/
                curtype=1 ;
            }
            {
                char s[8];
                /*puts256("������꣺",330,430,0); */
                printf256(550,460,BLUE,"%4d,%4d",mouse.getx,mouse.gety);
                /*puts256("��ǰ��������ͣ�",330,450,0);
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
            /*ȡ����껺��*/
            vpost();
        }
        gameend();
    }
    while(1);
    /*��Ȼ����ѭ�����ǿ������˳��������˳���Ϸ*/
}


void gameend(void)
{
    int i,j ;
    char is_on,key ;
    static char curtype=1,texts[3][16]=
    {
        /*��ȻΪ�յ���ͼƬ��λ����һֱ�ģ�*/
        "        ","        ","  " 
    }
    ;
    
    
    while(getmkeyin(mbRight)!=mbRight)
    {
        hidemouse();
        QPutImage(240,150,askend);
        /*���ѡ��ģʽ*/
        TEXT_SIZE=TX_BIG ;
        /*16������ʾ*/
        getmousexy();
        is_on=-1 ;
        for(i=0;i<2;i++)
        if(mouse.getx>=272&&mouse.getx<=345&&mouse.gety>=200+i*30&&mouse.gety<=216+i*30)
        {
            is_on=i ;
            puts256(texts[i],275,200+i*30,BLUE);
            /*��ʾҪ����ĺ���λ��*/
        }
        else puts256(texts[i],275,200+i*30,0);
        
        /*�жϲ���������Ҫ�Ǵ˺�������*/
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
            /*��������Ӧ����*/
            switch(is_on)
            {
                case 0 :
                exit(0);
                /* �˳���Ϸ*/
                break ;
                case 1 :
                return(0);
                /*������Ϸ*/
                
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
    /*���ݳ�ʼ�����ٵ�������Ϸ����*/
    xx=0 ;
    yy=0 ;
    flag_changechess=1 ;
    count_step=0 ;
    flag_whozhizi=1 ;
    choosemode();
}

/*�˻���ս*/
void gamemain_1(void)
{
    int i,j,a,b,c,d ;
    int flag_heibai=1,flag_pass ;
    int hei_new[10][10][2],bai_new[10][10][2];
    int count_bai,count_hei,count_canput=1,count_canput_bai,count_canput_hei ;
    int count_1,count_2,count_3,count_4,count_5 ;
    int count_mouse_bai,count_mouse_hei ;
    /*��Ҫ������Ϸ�����ж�*/
    /*���ڽ���ʹ�úڰ���*/
    char is_on,key ;
    static char curtype=1,texts[3][16]=
    {
        /*��ȻΪ�յ���ͼƬ��λ����һֱ�ģ�*/
        "   ","   ","   " 
    }
    ;
    
    flag_changechess=1 ;
    /*16������ʾ*/
    /*��Ȼ����ѭ����������������˳���Ϸ*/
    while(1)
    {
        hidemouse();
        QPutImage(0,0,back);
        /*�������ͼ*/
        
        /*����ѱ�����ӣ��������ӵĵط���*/
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
        
        if(xx&&yy)puts256("��",xx*41+10,yy*40+70,7);
        
        
        /*���´���Ϊ����ڰ��ӵ�������������Χ��*/
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
            /*����ֻ���ж�һ��*/
        }
        printf256(522,168,250,"%d",count_hei);
        printf256(522,198,250,"%d",count_bai);
        if(flag_changechess)
        {
            TEXT_SIZE=TX_NORMAL ;
            puts256("��",436,385,250);
            puts256("�������õ���������",460,385,250);
            TEXT_SIZE=TX_BIG ;
            puts256("c",452,383,250);
        }
        TEXT_SIZE=TX_BIG ;
        
        /*���´���Ϊ׼������������ܵ�׼�����������ݳ�ʼ����*/
        
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
            flag_heibai=computer_2_0(flag_heibai,flag_whozhizi);     /*�����ж�*/
            if(flag_cpuyixia==0)flag_heibai=computer_2(flag_heibai,flag_whozhizi);/*�������ж�*/
        }
        if(count_3&&flag_cpuyixia==0)
        flag_heibai=computer_3(flag_heibai,flag_whozhizi);
        if(count_4&&flag_cpuyixia==0)
        flag_heibai=computer_4(flag_heibai,flag_whozhizi);
        if(count_2&&flag_cpuyixia==0)
        flag_heibai=computer_2_1(flag_heibai,flag_whozhizi);
        if(count_5&&flag_cpuyixia==0)
        flag_heibai=computer_5(flag_heibai,flag_whozhizi);

       /* flag_heibai=computer_6(flag_heibai,flag_whozhizi); �󱸼����ܴ������*/
        
        /*����������ִ�и����ܴ��롣flag_changechess������Ҫ�жϵ���Ӧ����ʲô��ɫ����*/
        
        /*�����ж���Ϸ�Ƿ����*/
        
        
        if(count_canput==0)
        {
            
            if(count_hei+count_bai==64)
            {
                if(count_hei>count_bai)
                {
                    puts256("����Ӯ��!����������",150,170,250);
                    vpost();
                    /*���������*/
                    while(1)
                    {
                        if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                        gamemain_new();
                    }
                }
                else if(count_hei<count_bai)
                {
                    puts256("����Ӯ��!����������",150,170,250);
                    vpost();
                    while(1)
                    {
                        if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                        gamemain_new();
                    }
                }
                else if(count_hei==count_bai)
                {
                    puts256("���������Ǵ�ƽ��!����������",110,170,250);
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
                    puts256("������һ��û�п��µĵط��ˣ������PASS!",100,190,250);
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
                    puts256("������һ��û�п��µĵط��ˣ������PASS!",100,190,250);
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
                        puts256("����Ӯ��!����������",150,170,250);
                        vpost();
                        /*���������*/
                        while(1)
                        {
                            if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                            gamemain_new();
                        }
                    }
                    else if(count_hei<count_bai)
                    {
                        puts256("����Ӯ��!����������",150,170,250);
                        vpost();
                        while(1)
                        {
                            if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                            gamemain_new();
                        }
                    }
                    else if(count_hei==count_bai)
                    {
                        puts256("���������Ǵ�ƽ��!����������",110,170,250);
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
        
        /*���´���Ϊ���canput������Ȼ�ڸ���ѭ���У��������ӱ�ǻ��ǻ���ʾ�����ģ����ֲ���ʾͣ���Ǻ�С�ġ�*/
        
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
        
        /*��ʼ�����������*/
        for(a=0;a<9;a++)
        for(b=0;b<9;b++)
        {
            hei_new[a][b][0]=hei[a][b][0];
            bai_new[a][b][0]=bai[a][b][0];
        }
        
        
        /*PutImage(46,104,white,28);��ʾȥ��28ɫ������Ϊ��ɫ����ͼ��ͼƬ*/
        
        /*���´���Ϊ������Cʱ�ı����ӵ��Ⱥ�˳��*/
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
        
        
        /*��δ���ܲ��������Ժ������ѭ������һ��ʹ�ã��������Ľṹ�������������´����ǽ������º��ӵĵط���ǵ�canput������*/
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
                        /*����������ӾͲ����ж���*/
                        /* ���Ϊ�վ����뵽��������*/
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
                    
                    /*  ���ϴ���Ϊ�ж�һ��������Χ�Ƿ��а�ɫ�ӡ��������ô�����ж�����һ�����Ƿ�Ϊ�ո��������ô��Ϊ�����ӵĵط�������ڿ����������С�   */
                    
                }
                
                
            }
        }
        /*���´���Ϊ�жϰ��ӿ�����������ԭ����ͬ�����ݴ������෴*/
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
        
        /*���������ж����ָ������λ��*/
        
        for(i=1;i<9;i++)
        for(j=1;j<9;j++)
        if(mouse.getx>=j*41&&mouse.getx<=j*41+34&&mouse.gety>=i*40+58&&mouse.gety<=i*40+58+34)
        {
            if(getmkeyin(mbLeft)==mbLeft)
            /*ֻ����ָ��λ�ã�X��Ǵ�)��������*/
            /*�����ºڰ���*/
            if(canput_hei[j][i][0]==1||canput_bai[j][i][0]==1)if(!flag_heibai&&bai[j][i][0]!=1&&hei[j][i][0]!=1)
            {
                bai[j][i][0]=1 ;
                flag_changechess=0 ;
                if(!flag_whozhizi)flag_heibai=(!flag_heibai);
                
                
                /*���´���Ϊ�滻�ڰ��ӣ����˶�ս�����ܣ����������ԭ���鸽ֵ�󣬺�����жϾͻ���޸ĺ�������жϽ�ȥ������Ӧ����ʹ�������飬���ֵ����ԭ���飡*/
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
                
                /*�����㷨��ǰ����жϿ���ո�һ�����ŵ��ǽṹ������������*/
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
        
        /*���´������ڸ�ֵ*/
        for(a=0;a<9;a++)
        for(b=0;b<9;b++)
        {
            hei[a][b][0]=hei_new[a][b][0];
            bai[a][b][0]=bai_new[a][b][0];
        }
        /*���������ж��������λ�ã���֮�ࣩ*/
        /*�жϲ���������Ҫ�Ǵ˺�������*/
        if(mouse.getx>=12&&mouse.getx<=34&&mouse.gety>=31&&mouse.gety<=42)
        {
            is_on=0 ;
            puts256(texts[0],12,31,BLUE);
        }
        else puts256(texts[0],12,31,0);
        
        /*�жϲ���������Ҫ�Ǵ˺�������*/
        if(mouse.getx>=49&&mouse.getx<=72&&mouse.gety>=31&&mouse.gety<=42)
        {
            is_on=1 ;
            puts256(texts[1],49,31,BLUE);
        }
        else puts256(texts[1],49,31,0);
        
        /*�жϲ���������Ҫ�Ǵ˺�������*/
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
            /*����������λ����Ӧ����*/
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

/*���˴�ս*/
void gamemain_2(void)
{
    int i,j,a,b,c,d ;
    int flag_heibai=1,flag_pass,flag_show=0 ;
    int hei_new[10][10][2],bai_new[10][10][2];
    int count_bai,count_hei,count_canput=1,count_canput_bai,count_canput_hei ;
    int count_mouse_bai,count_mouse_hei ;
    /*���ڽ���ʹ�úڰ���*/
    char is_on,key ;
    static char curtype=1,texts[3][16]=
    {
        /*��ȻΪ�յ���ͼƬ��λ����һֱ�ģ�*/
        "   ","   ","   " 
    }
    ;
    
    TEXT_SIZE=TX_BIG ;
    /*16������ʾ*/
    /*��Ȼ����ѭ����������������˳���Ϸ*/
    while(1)
    {
        hidemouse();
        QPutImage(0,0,back);
        /*�������ͼ*/
        
        /*����ѱ�����ӣ��������ӵĵط���*/
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
        /*���´���Ϊ����ڰ��ӵ�������������Χ��*/
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
        
        /*�����ж���Ϸ�Ƿ����*/
        if(count_canput==0)
        {
            
            if(count_hei+count_bai==64)
            {
                if(count_hei>count_bai)
                {
                    puts256("����Ӯ��!",180,170,250);
                    vpost();
                    /*���������*/
                    while(1)
                    {
                        if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                        gamemain_new();
                    }
                }
                else if(count_hei<count_bai)
                {
                    puts256("����Ӯ��!",180,170,250);
                    vpost();
                    while(1)
                    {
                        if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                        gamemain_new();
                    }
                }
                else if(count_hei==count_bai)
                {
                    puts256("���������Ǵ�ƽ��!",140,170,250);
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
                    puts256("������һ��û�п��µĵط��ˣ������PASS!",100,190,250);
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
                    puts256("������һ��û�п��µĵط��ˣ������PASS!",100,190,250);
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
                        puts256("����Ӯ��!",180,170,250);
                        vpost();
                        /*���������*/
                        while(1)
                        {
                            if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                            gamemain_new();
                        }
                    }
                    else if(count_hei<count_bai)
                    {
                        puts256("����Ӯ��!",180,170,250);
                        vpost();
                        while(1)
                        {
                            if(getmkeyin(mbLeft)==mbLeft||getmkeyin(mbRight)==mbRight)
                            gamemain_new();
                        }
                    }
                    else if(count_hei==count_bai)
                    {
                        puts256("���������Ǵ�ƽ��!",140,170,250);
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
        /*���´���Ϊ���canput������Ȼ�ڸ���ѭ���У��������ӱ�ǻ��ǻ���ʾ�����ģ����ֲ���ʾͣ���Ǻ�С�ġ�*/
        
        
        /*��ʼ�����������*/
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
        
        
        /*PutImage(46,104,white,28);��ʾȥ��28ɫ������Ϊ��ɫ����ͼ��ͼƬ*/
        /*��δ���ܲ��������Ժ������ѭ������һ��ʹ�ã��������Ľṹ�������������´����ǽ������º��ӵĵط���ǵ�canput������*/
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
                        /*����������ӾͲ����ж���*/
                        /* ���Ϊ�վ����뵽��������*/
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
                    
                    /*  ���ϴ���Ϊ�ж�һ��������Χ�Ƿ��а�ɫ�ӡ��������ô�����ж�����һ�����Ƿ�Ϊ�ո��������ô��Ϊ�����ӵĵط�������ڿ����������С�   */
                    
                }
                
                
            }
        }
        /*���´���Ϊ�жϰ��ӿ�����������ԭ����ͬ�����ݴ������෴*/
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
        
        /*���������ж����ָ������λ��*/
        
        for(i=1;i<9;i++)
        for(j=1;j<9;j++)
        if(mouse.getx>=j*41&&mouse.getx<=j*41+34&&mouse.gety>=i*40+58&&mouse.gety<=i*40+58+34)
        {
            if(getmkeyin(mbLeft)==mbLeft)
            /*ֻ����ָ��λ�ã�X��Ǵ�)��������*/
            /*�����ºڰ���*/
            if(canput_hei[j][i][0]==1||canput_bai[j][i][0]==1)if(!flag_heibai&&bai[j][i][0]!=1&&hei[j][i][0]!=1)
            {
                bai[j][i][0]=1 ;
                
                flag_heibai=1 ;
                
                
                /*���´���Ϊ�滻�ڰ��ӣ����˶�ս�����ܣ����������ԭ���鸽ֵ�󣬺�����жϾͻ���޸ĺ�������жϽ�ȥ������Ӧ����ʹ�������飬���ֵ����ԭ���飡*/
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
                
                /*�����㷨��ǰ����жϿ���ո�һ�����ŵ��ǽṹ������������*/
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
        
        /*���´������ڸ�ֵ*/
        for(a=0;a<9;a++)
        for(b=0;b<9;b++)
        {
            hei[a][b][0]=hei_new[a][b][0];
            bai[a][b][0]=bai_new[a][b][0];
        }
        /*���������ж��������λ�ã���֮�ࣩ*/
        /*�жϲ���������Ҫ�Ǵ˺�������*/
        if(mouse.getx>=12&&mouse.getx<=34&&mouse.gety>=31&&mouse.gety<=42)
        {
            is_on=0 ;
            puts256(texts[0],12,31,BLUE);
        }
        else puts256(texts[0],12,31,0);
        
        /*�жϲ���������Ҫ�Ǵ˺�������*/
        if(mouse.getx>=49&&mouse.getx<=72&&mouse.gety>=31&&mouse.gety<=42)
        {
            is_on=1 ;
            puts256(texts[1],49,31,BLUE);
        }
        else puts256(texts[1],49,31,0);
        
        /*�жϲ���������Ҫ�Ǵ˺�������*/
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
            /*����������λ����Ӧ����*/
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
        /*��ȻΪ�յ���ͼƬ��λ����һֱ�ģ�*/
        "","","   " 
    }
    ;
    
    check=0 ;
    while(!check)
    {
        if(getmkeyin(mbRight)==mbRight)check=1 ;
        hidemouse();
        QPutImage(12,49,game);
        /*�������ͼ*/
        TEXT_SIZE=TX_BIG ;
        /*16������ʾ*/
        getmousexy();
        is_on=-1 ;
        
        for(i=0;i<2;i++)
        if(mouse.getx>=22&&mouse.getx<=90&&mouse.gety>=51+i*25&&mouse.gety<=70+i*25)
        {
            is_on=i ;
            puts256(texts[i],22,51+i*25,BLUE);
            /*��ʾҪ����ĺ���λ��*/
        }
        else puts256(texts[i],22,51+i*25,0);
        
        
        /*�жϲ���������Ҫ�Ǵ˺�������*/
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
            /*��������Ӧ����*/
            switch(is_on)
            {
                case 0 :
                gamemain_new();
                break ;
                case 1 :
                check=1 ;
                /*����������˳�*/
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
        /*��ȻΪ�յ���ͼƬ��λ����һֱ�ģ�*/
        "","","   " 
    }
    ;
    
    check=0 ;
    while(!check)
    {
        if(getmkeyin(mbRight)==mbRight)check=1 ;
        hidemouse();
        QPutImage(34,49,help);
        /*�������ͼ*/
        TEXT_SIZE=TX_BIG ;
        /*16������ʾ*/
        getmousexy();
        is_on=-1 ;
        
        for(i=0;i<2;i++)
        if(mouse.getx>=40&&mouse.getx<=118&&mouse.gety>=51+i*25&&mouse.gety<=70+i*25)
        {
            is_on=i ;
            puts256(texts[i],40,51+i*25,BLUE);
            /*��ʾҪ����ĺ���λ��*/
        }
        else puts256(texts[i],40,51+i*25,0);
        
        /*�жϲ���������Ҫ�Ǵ˺�������*/
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
            /*��������Ӧ����*/
            switch(is_on)
            {
                case 0 :
                puts256("    �ڰ����ֽа������壬���ڹ��Ϊ���أ��������Ͻ��е�������Ϸ��",30,100,125);
                puts256("��Ϸ��ʼʱ����������Ԥ�ȷ���4�����ӣ�2��2�ף�,Ȼ��˫���������ӣ�",30,120,125);
                puts256("ֱ����������ʱ���������Ӷ��һ��ʤ����",30,140,125);
                puts256("����",30,160,224);
                puts256("1.���ӣ�������ֱ�߻���б�߷������Ӻ�������֮���뼺������֮��ȫ",30,180,125);
                puts256("���ǵз�����(�������ո�),����Щ�з�����ȫ�����Ե�����ɼ������ӡ�",30,200,125);
                puts256("2.���ӣ�ֻ���ڿ��Գ��ӵ�λ�����ӣ�����˴�������Ч��",30,220,125);
                puts256("3.�������ӣ����޴���������,���Զ�����һ�����ӻ���,�ɶԷ��������ӡ�",30,240,125);
                puts256("4.��Ϸ����������������,��˫�������ӿ���ʱ��Ϸ�������Ӷ��һ����ʤ��",30,260,125);
                puts256("���Ժͼ��ɣ�",30,280,224);
                puts256("���������ռ�ߺͽ��ϵĸ��ӣ���Ϊ�����е����ӱ��Է��Ե��Ŀ����Խ�С��",30,300,125);
                puts256("��Ϸ��أ�",30,320,224);
                puts256("1. S������/�ر� ������λ����ʾ��",30,340,125);
                puts256("2. C�������˻���սʱ�õ������ߡ�",30,360,125);
                puts256("3. �� ������Ե�����λ�á�",30,380,125);
                puts256("4. ���˵���ѡ��󣬵������Ҽ�����ȡ��ѡ��",30,400,125);
                
                break ;
                case 1 :
                puts256("    ������������Turbo C 2.0������������Ϸ���ҿ��Ժܿ϶�����˵��",26,100,125);
                puts256("��Ҫ����������۾������ȷ��һ����ʵ������Ե��ҵ���ҳ�����ص�Դ��",26,120,125);
                puts256("��",26,140,125);
                puts256(" www.chengchen.net",78,140,253);
                puts256("  д�˳�����ֻ������ߴ�ң������һ��",250,140,125);
                puts256("�������飬ֻҪ��϶��Խ",26,160,125);
                puts256("    ����һЩ�˶��ҵ�C ����������������ɣ���Ϊ���ڰ����ǽ��һЩ��",26,180,125);
                puts256("��ʱ�����ò��ο��鼮����Ȼ���ҵ�C ���Ե�ȷѧ�ĺܲ�ܶ�⺯���Ҷ�",26,200,125);
                puts256("���������ǣ�����Ϊѧϰһ�����Թؼ��������ȥ���á������ǵ����ļ��㡣",26,220,125);
                puts256("ѧϰ������Ҫ��ɢ˼ά����Ҳ����Ϊ��ϲ�����Զ�������Ե�ԭ��֮һ����",26,240,125);
                puts256("��ʱ���Ҳ��ò�������Ŀ��˼άȥ˼������Ȼ�ҳ��и��򵥵��㷨��������",26,260,125);
                puts256("�ã����ھ�����ʱ�������е�VC++���о�������TC2.0д��ʲô������������",26,280,125);
                puts256("��Ҳȱ����ôһ�������DOS��������ǡ��ڰ׷��ơ��͵����ˣ�",26,300,125);
                puts256("    ���������һ��DOS�µĳ����ˣ���Ϊ��DOSʱ�������û���ɣ���Ȼ��",26,320,125);
                puts256("���һ��DOS������ϣ����չʾһ��TC�����������㡢���䣡��",26,340,125);
                puts256("    ����ر��л����ͬѧ����Ϊ���ҵļ���������˰���ʱ����������",26,360,125);
                puts256("���Ƶ�Σ�գ��ṩ�˱�̻��������������˺��ڲ��ԣ���Ҫ��л���Ѹ��´���",26,380,125);
                puts256("��Ϊ�������������о��ɹ��Ĵ������ͣ�����ع������ҵ����ġ���Ҫ��л",26,400,125);
                puts256("�ϰֵľ���֧�֡�",26,420,125);
                puts256("�̳�",434,425,224);
                puts256("���Ĵ���",469,425,125);
                puts256("2005��3��",460,445,125);
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


/*�˺�����ʹ�������ӣ���canput_bai[][][]��canput_hei[][][]�ϲ�Ϊһ�����飬����˺����С���˲����ǰ׻��Ǻڶ���һ���ӣ�ֻ��������*/
/*����һ�������ӵ����飨�½���ȫ�ֱ�����*/
/*1���жϿ�����Ƿ�Ϊ�ǣ����Ϊ�������һ��*/
/*2���жϱߣ��۲죬���ܹؼ����֣�*/
/*3�������м䲿�ֿ���������������������жϣ�*/
/*�������ڴ���flag_heibai���ز���ֵ*/
/*��������canput[][][]��*/
/*��flag_chess_changeΪ1ʱ��ִ��*/
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

/*�����жϱ�Ӧ�����ӵ����*/
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
        /*�������Ӳ��ֱ��Ϊ���������Ժ���������£����ָ�����ԭ�������   */
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
        /*����0-m�������,ע�������canput_new����[m][0]���ص��Ǻ����ꡣ[m][1]��������*/
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
    /* ����0-m������� */
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
    /*����0-m�������*/
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
    /*����0-m�������*/
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
    /*����0-m�������*/
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

/*����������ڵ��Է���,���˿��ܻ���Ϊʲôǰ��Ĳ�ֱ�Ӵ��˺�����������Ϊ����ʱ��û���뵽��������������ȥ�ġ�*/
/*j,i���ڼ�������ӵ�����*/
int changechess(int flag_chess_heibai2,int flag_chess_change2,int j,int i)
{
    int a,b,c,d ;
    int hei_new[10][10][2],bai_new[10][10][2];
    xx=j ;
    yy=i ;
    /*���ڱ�ǵ��Ը����ӵ�λ��*/
    for(a=0;a<9;a++)
    for(b=0;b<9;b++)
    {
        hei_new[a][b][0]=hei[a][b][0];
        bai_new[a][b][0]=bai[a][b][0];
    }
    
    
    if(flag_chess_change2)
    {
        bai[j][i][0]=1 ;
        /*���´���Ϊ�滻�ڰ��ӹ��ܣ����������ԭ���鸽ֵ�󣬺�����жϾͻ���޸ĺ�������жϽ�ȥ������Ӧ����ʹ�������飬���ֵ����ԭ���飡*/
        
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
        
        /*�����㷨��ǰ����жϿ���ո�һ�����ŵ��ǽṹ������������*/
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
    /*���´������ڸ�ֵ*/
    for(a=0;a<9;a++)
    for(b=0;b<9;b++)
    {
        hei[a][b][0]=hei_new[a][b][0];
        bai[a][b][0]=bai_new[a][b][0];
    }
    count_step++;
    flag_chess_heibai2=(!flag_chess_heibai2);
    flag_cpuyixia=1 ;
    /*ֻҪ�з��Ӿ�˵������������*/
    return(flag_chess_heibai2);
}




/*��ɫ�彥��*/
void StepIn()
{
    int i ;
    for(i=0;i<256;i++)setpal(i,PAL[i][0]*Step/64,PAL[i][1]*Step/64,PAL[i][2]*Step/64);
    Step++;
    if(Step>64)KillAllTimer();
}
/* ��ɫ�彥�� */
void StepOut()
{
    int i ;
    for(i=0;i<256;i++)setpal(i,PAL[i][0]*Step/64,PAL[i][1]*Step/64,PAL[i][2]*Step/64);
    Step--;
    if(Step<1)KillAllTimer();
}
/*��ͼ�ε����ڴ�*/
void ClearScreen()
{
    int x,y ;

    for(y=0;y<=200;y++)for(x=0;x<=320;x++)Pset(x,y,n);

}
/*���뿪ʼ����*/
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

/*��ʾ������Ч*/
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
    while(ScanKey()!=28) /*1��ESC����57�ǿո����28�ǻس���*/
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
/*���Σ���ģָ�롢�����С����ʼ����(x,y)����ɫ*/
{
  int i, j, k, n;
  n = (matsize - 1) / 8 + 1;
  for(j = 0; j < matsize; j++)
    for(i = 0; i < n; i++)
      for(k = 0;k < 8; k++)
        if(mat[j * n + i] & (0x80 >> k))  /*����Ϊ1��λ����ʾ*/
          pset(x + i * 8 + k, y + j, color);
}


showchn()
{
    char hei48H[]=
    {
        /* ������ '��' �� 48�������п� ��ģ��288 byte */
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
        /* ������ '��' �� 48�������п� ��ģ��288 byte */
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
        /* ������ '��' �� 48�������п� ��ģ��288 byte */
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
        /* ������ '��' �� 48�������п� ��ģ��288 byte */
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
        /* ������ '��' �� 12�������� ��ģ��24 byte */
        0x37,0xC0,0xE4,0x40,0x24,0x40,0xF7,0xC0,
        0x20,0x00,0x6F,0xE0,0x71,0x00,0xA7,0xC0,
        0xA1,0x00,0x21,0x00,0x2F,0xE0,0x00,0x00,
    }
    ;
    char xu12S[]=
    {
        /* ������ '��' �� 12�������� ��ģ��24 byte */
        0x04,0x00,0x7F,0xE0,0x40,0x00,0x5F,0x80,
        0x45,0x00,0x42,0x00,0x7F,0xE0,0x42,0x40,
        0x42,0x00,0x82,0x00,0x8E,0x00,0x00,0x00,
    }
    ;
    
    char she12S[]=
    {
        /* ������ '��' �� 12�������� ��ģ��24 byte */
        0x47,0x80,0x24,0x80,0x04,0x80,0x04,0xE0,
        0xE8,0x00,0x37,0xC0,0x24,0x40,0x22,0x80,
        0x31,0x00,0x22,0x80,0x1C,0x60,0x00,0x00,
    }
    ;
    
    char ji12S[]=
    {
        /* ������ '��' �� 12�������� ��ģ��24 byte */
        0x41,0x00,0x21,0x00,0x01,0x00,0x01,0x00,
        0xCF,0xE0,0x41,0x00,0x41,0x00,0x41,0x00,
        0x51,0x00,0x61,0x00,0x41,0x00,0x00,0x00,
    }
    ;
    char m12S[]=
    {
        /* ������ '��' �� 12�������� ��ģ��24 byte */
        0x00,0x00,0x00,0x00,0x0C,0x00,0x0C,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x00,
        0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    }
    ;
    
    char chen12S[]=
    {
        /* ������ '��' �� 12�������� ��ģ��24 byte */
        0x3F,0xC0,0x20,0x40,0x3F,0xC0,0x20,0x40,
        0x7F,0xE0,0x40,0x00,0x7F,0xE0,0x54,0x40,
        0x52,0x80,0x55,0x00,0x98,0xE0,0x00,0x00,
    }
    ;
    /*��ʾ����������Ϣ*/
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
    /*��ʼ����Ļ����Ϊ������ҳ�ṹ����������д����ǰ��*/
    initmouse();
    /*��ʼ��256ɫ���*/
    initalpha();
    /*��ʼ����ɫƥ�����*/
    
    /*��ʼ���ظ�����Դ��ע�⣺��ͼ����Դ������DestroyAllImage�ͷ�������Դ��(��λBMP����ָ��)��û���ṩ������ʽ�����ͷ�*/
    /*��ˣ���֤��Դֻ������һ��*/
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

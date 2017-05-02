#include "all256.h"

#define UP 72 
#define DOWN 80 
#define LEFT 75 
#define RIGHT 77 
/*��������*/
void show_1(void);
void show_2(void);
void show_2_12(char use_screen_cut);
void show_2_3(void);
void show_2_4(void);
void show_2_5(void);
void show_2_6(void);
void show_3(void);
void show_3_1(void);
void show_3_2(void);
void show_3_3(void);
void show_4(void);
void show_5(void);
void show_6(void);
void get_rand(unsigned char n[],unsigned char max);
void show_6_1(void);
void show_6_2(void);
void show_6_3(void);
void show_7(void);
void show_8(void);

/*��ý���Դ�������ⲿ���Ա������ģ�鶼����ʹ��*/
/*һ��ͼƬ����*/
Bmp256 candle,title,mars,earth ;
Bmp256 fbb,model,snow,bmw ;
Bmp256 ymhd,deskmap,say,satellite,yue,testmask,textmask,bkgdmask ;
Bmp256 text1,text2,text3,text4,bk_tc ;
Bmp256 title_qh,leafs,lxr,leafs2,birdl,birdr,stick ;
Bmp256 island ;
/*���ͼƬ����*/
Animate256 universe,frame,arrow ;
Animate256 mary,bqla,bqlb,bowwave,aniearth ;
Animate256 angell,angelr ;
/*����ȡͼƬ����*/
Sprlib dialog ;
Sprlib tianshi ;
Sprlib yaka ;

main()
{
    char key,arrowystep=1 ;
    
    init256(SINGLE_SURFACE);
    /*��ʼ����Ļ����Ϊ������ҳ�ṹ����������д����ǰ��*/
    initmouse();
    /*��ʼ��256ɫ���*/
    initalpha();
    /*��ʼ����ɫƥ�����*/
    
    /*��ʼ���ظ�����Դ��ע�⣺��ͼ����Դ������DestroyAllImage�ͷ�������Դ��(��λBMP����ָ��)��û���ṩ������ʽ�����ͷ�*/
    /*��ˣ���֤��Դֻ������һ��*/
    candle=LoadBMP("��̨.bmp");
    title=LoadBMP("title0.bmp");
    mars=LoadBMP("065.bmp");
    earth=LoadBMP("earth.bmp");
    
    fbb=LoadBMP("fbb.bmp");
    model=LoadBMP("model.bmp");
    snow=LoadBMP("ѩԭ.bmp");
    bmw=LoadBMP("bmw.bmp");
    
    ymhd=LoadBMP("ymhd.bmp");
    deskmap=LoadBMP("��ֽ.bmp");
    say=LoadBMP("say.bmp");
    satellite=LoadBMP("��������.bmp");
    yue=LoadBMP("yue.bmp");
    testmask=LoadBMP("testmask.bmp");
    textmask=LoadBMP("textmask.bmp");
    bkgdmask=LoadBMP("bkgdmask.bmp");
    
    text1=LoadBMP("text1.bmp");
    text2=LoadBMP("text2.bmp");
    text3=LoadBMP("text3.bmp");
    text4=LoadBMP("text4.bmp");
    bk_tc=LoadBMP("bk_tc.bmp");
    
    title_qh=LoadBMP("title_qh.bmp");
    leafs=LoadBMP("leafs.bmp");
    lxr=LoadBMP("lxr.bmp");
    
    leafs2=LoadBMP("leafs2.bmp");
    birdl=LoadBMP("bird����.bmp");
    birdr=LoadBMP("bird����.bmp");
    
    stick=LoadBMP("stick.bmp");
    
    island=LoadBMP("island.bmp");
    /*��̬��ʾͼ*/
    initanimate(&universe,130,360,5,4,0,"��������.bmp");
    initanimate(&frame,530+12,300-35,4,6,0,"��������.bmp");
    initanimate(&arrow,240,153+(arrowystep-1)*30,5,5,28,"��ͷ����.bmp");
    
    initanimate(&mary,30,30,4,3,28,"����.bmp");
    initanimate(&bqla,100,300,6,5,28,"������A.bmp");
    initanimate(&bqlb,100,300,6,3,28,"������B.bmp");
    initanimate(&bowwave,190,280,5,2,28,"������.bmp");
    initanimate(&aniearth,320,100,15,4,0,"��������.bmp");
    
    initanimate(&angell,410,140,6,5,28,"��ʹL.bmp");
    initanimate(&angelr,110,140,6,5,28,"��ʹR.bmp");
    
    dialog=loadsprlib(32,32,"dialog.bmp");
    tianshi=loadsprlib(89,70,"��ʹL.bmp");
    yaka=loadsprlib(32,32,"yaka.bmp");
    
    START :
    cls(0);
    PutImage(530,300,candle,28); /*��ʾͼƬ*/
    QPutImage(25,20,title);
    QPutImage(25,225,earth);
    TEXT_SIZE=TX_NORMAL ;
    puts256("��For Turbo C 2 �汾:2.3��",200,85,219);
    puts256("ʹ�á�����ѡ�񣬻س�ȷ����Ҳ���԰���Ӧ���ּ�",180,440,YELLOW);
    TEXT_SIZE=TX_BIG ;
    puts256("1. λͼ������ʾ.",295,165,239);
    puts256("2. ͼ���׼������ʾ.",295,165+30,31);
    puts256("3. ͼ����Ч������ʾ.",295,165+30*2,156);
    puts256("4. ���ֲ�����ʾ.",295,165+30*3,246);
    puts256("5. ��ͼ��������ʾ.",295,165+30*4,254);
    puts256("6. 256ɫͼ��ϵͳ�ۺ���ʾ.",295,165+30*5,251);
    puts256("7. XNVIEW 256ɫ����ɫ��.",295,165+30*6,122);
    puts256("8. ALPHA�����ͼ�ؿ�ĵ���.",295,165+30*7,147);
    puts256("9. �˳���ʾ����(ESC).",295,165+30*8,255);
    while(1)
    {
        if(kbhit())
        {
            key=getch();
            if(key==0)
            {
                key=getch();
                /*���������*/
                if(key==UP&&arrowystep>1)
                {
                    bar(arrow.x,arrow.y,arrow.width,arrow.height,0);
                    arrow.nowplaying=0 ;
                    arrowystep--;
                    arrow.y-=30 ;
                }
                /*���������*/
                if(key==DOWN&&arrowystep<9)
                {
                    bar(arrow.x,arrow.y,arrow.width,arrow.height,0);
                    arrow.nowplaying=0 ;
                    arrowystep++;
                    arrow.y+=30 ;
                }
            }
            /*�س���*/
            if(key==13)switch(arrowystep)
            {
                case 1 :
                key='1' ;
                break ;
                case 2 :
                key='2' ;
                break ;
                case 3 :
                key='3' ;
                break ;
                case 4 :
                key='4' ;
                break ;
                case 5 :
                key='5' ;
                break ;
                case 6 :
                key='6' ;
                break ;
                case 7 :
                key='7' ;
                break ;
                case 8 :
                key='8' ;
                break ;
                case 9 :
                key=27 ;
            }
            switch(key)
            {
                case '1' :
                show_1();
                goto START ;
                case '2' :
                show_2();
                goto START ;
                case '3' :
                show_3();
                goto START ;
                case '4' :
                show_4();
                goto START ;
                case '5' :
                show_5();
                goto START ;
                case '6' :
                show_6();
                goto START ;
                case '7' :
                show_7();
                goto START ;
                case '8' :
                show_8();
                goto START ;
                case '9' :
                key=27 ;
            }
            if(key==27)break ;
            /*ESC��*/
        }
        Qshowanimate(&universe);
        /*���ƶ�������������*/
        Qshowanimate(&frame);
        /*���ƶ���������*/
        Qshowanimate(&arrow);
        /*���ƶ�������ͷ*/
        vpost();
        /*���»��棬������ҳϵͳר��*/
    }
    close256();
}

void show_1(void)   /*λͼ������ʾ.*/
{
    cls(239);
    rectangle(4,4,150+5,234+5,255);
    TEXT_SIZE=TX_NORMAL ;
    puts256("�����256ɫBMPλͼ(fbb.bmp)",160,50,0);
    puts256("�Դ�������ʽ���256ɫBMPλͼ(model.bmp)��",160,70,0);
    puts256("�������������������ʽ������������Ի�úܺõ�Ч��",30,250,0);
    puts256("��ͼ���ε�254����ɫ(����)��",210,120,0);
    puts256("����ͼ���ε�28����ɫ(����)",210,140,0);
    boxputs256("����INVERT_PUTģʽ����Ч����",350,340,20,2,0);
    QPutImage(5,5,fbb);
    PutImage(480,35,model,254);
    PutImage(170,165,bmw,28);
    rectangle(30,270,30+301,270+201,255);
    QPutImage(31,271,snow);
    PutImage(120,370,bmw,28);
    PutImage(370,385,bmw,INVERT_PUT);
    vpost();
    getch();
}

void show_2(void)    /*ͼ���׼������ʾ.*/
{
    char key,arrowypos=1,ymhdxpos=0 ;
    START2 :
    cls(31);
    TEXT_SIZE=TX_NORMAL ;
    puts256("�����µ�256ɫͼ��ϵͳ�У�EMS�ڴ漼������Ļ���м��������˸�ϵͳ",65,315,229);
    puts256("�����Ĳ����͸�ǿ��Ĺ���",80,330,229);
    puts256("��λͼ����EMS����ʾ��ʹ����ͼ���Ϊ�Ӹ��ٵ��ڴ��ж�ȡ",80,360,0);
    puts256("ʹ�û���EMS�ĵ�����ҳ�ṹ����ʹһ��ͼ����Ƶ��ٶ�Ҳ���������",80,385,0);
    puts256("Ļ��˸",80,400,0);
    puts256("��������Ļ���м�����ʹ���������ͼ�񲿷���ʾ��ķǳ���",80,425,0);
    
    puts256("��չ���ͼ�����������ʾ��ʹ�á�����������ESC���˳�",105,140,DARKGREEN);
    puts256("��. ֱ��ʹ��QPutImage��ͼ�����",180,165,DARKGREEN);
    puts256("��. ������Ļ���к��ͼ�����",180,190,DARKGREEN);
    puts256("��. ֧����Ļ���е�λͼ���",180,215,DARKGREEN);
    puts256("��. ʹ�ü򵥶�������Animate256",180,240,DARKGREEN);
    puts256("��. ʹ��2ɫ�����ļ�",180,265,DARKGREEN);
    puts256("��. �ö�ɫ��������ʾ�Զ���ɫ��λͼ",180,290,DARKGREEN);
    while(1)
    {
        bar(0,5,640,ymhd.height,31);
        bar(145,165,24,273-135,31);
        for(key=0;key<8;key++)
        PutImage(key*100+ymhdxpos-100,5,ymhd,28);
        if(kbhit())
        {
            key=getch();
            if(key==0)
            {
                key=getch();
                if(key==UP&&arrowypos>1)arrowypos--;
                if(key==DOWN&&arrowypos<6)arrowypos++;
            }
            if(key==13)
            switch(arrowypos)
            {
                case 1 :
                show_2_12(0);
                goto START2 ;
                case 2 :
                show_2_12(1);
                goto START2 ;
                case 3 :
                show_2_3();
                goto START2 ;
                case 4 :
                show_2_4();
                goto START2 ;
                case 5 :
                show_2_5();
                goto START2 ;
                case 6 :
                show_2_6();
                goto START2 ;
            }
            if(key==27)break ;
        }
        puts256(">>>",145,165+(arrowypos-1)*25,RED);
        ymhdxpos=(ymhdxpos+1)%100 ;
        vpost();
    }
}

void show_2_12(char use_screen_cut)
{
    int i ;
    if(use_screen_cut)
    {
        cls(0);
        puts256("�������ڼ������...",220,25,255);
        screen_cut.left=50 ;
        screen_cut.right=639-50 ;
        screen_cut.top=50 ;
        screen_cut.bottom=479-50 ;
    }
    for(i=0;i<160&&!kbhit();i++)
    {
        QPutImage(-i,0,deskmap);
        vpost();
    }
    for(i=0;i<120&&!kbhit();i++)
    {
        QPutImage(-159,-i,deskmap);
        vpost();
    }
    for(i=0;i<160&&!kbhit();i++)
    {
        QPutImage(i-159,-119,deskmap);
        vpost();
    }
    for(i=0;i<120&&!kbhit();i++)
    {
        QPutImage(0,i-119,deskmap);
        vpost();
    }
    getch();
    if(use_screen_cut)
    {
        screen_cut.left=0 ;
        screen_cut.right=639 ;
        screen_cut.top=0 ;
        screen_cut.bottom=479 ;
    }
}

void show_2_3(void)
{
    cls(0);
    QPutImage(-20,-5,mars);
    QPutImage(400,-30,mars);
    QPutImage(470,340,mars);
    QPutImage(-40,380,mars);
    PutImage(648-say.width,488-say.height,say,28);
    QPutImage(150,150,satellite);
    puts256("��ʹ����Ļ���к�һ�п�Խ��Ļ�߽�Ĳ�������ü�",100,350,255);
    puts256("�����������Զ��ü�������Ļ�߽�Ĳ���",115,370,255);
    vpost();
    getch();
}

void show_2_4(void)
{
    int changebql=0 ;
    bqlb.nowplaying=0 ;
    /*��λ��ǰ����֡*/
    bqla.nowplaying=0 ;
    bowwave.nowplaying=0 ;
    while(!kbhit())
    {
        cls(0);
        Qshowanimate(&aniearth);
        /*��֧������Ķ������ţ������ٶȽϿ�*/
        boxputs256("���2.0�汾�Ժ󣬸�ϵͳ��ʼ֧�ֶ������У����ڸ�ϵͳ�ĸ��ٶȺ�֧��ʹ�õ�����ҳ������˸߷ֱ����µ����ж��������ϸо�������",50,220,70,2,255);
        showanimate(&mary);
        if(changebql<18)showanimate(&bqlb);
        else showanimate(&bqla);
        if(changebql==12)
        {
            bowwave.x=190 ;
        }
        if(changebql>12)
        {
            showanimate(&bowwave);
            bowwave.x+=6 ;
        }
        changebql=(changebql+1)%58 ;
        vpost();
    }
    getch();
}

void show_2_5(void)
{
    QPutImage(0,0,deskmap);
    PutMask(270,165,testmask,WHITE);
    PIXEL_MODE=INVERT_PUT ;
    /*���õ�ģʽΪȡ��*/
    PutMask(270,280,testmask,WHITE);
    PIXEL_MODE=COPY_PUT ;
    /*���õ�ģʽΪ����*/
    
    PutMask(20,10,textmask,RED);
    PutMask(220,60,textmask,GREEN);
    PutMask(40,110,textmask,YELLOW);
    PutMask(30,200,bkgdmask,218);
    
    boxputs256("����2.1�汾��ּ�����һ���µ�������������������ʽ���÷�ʽ������2ɫ��BMPλͼΪ����������������ֻ�ͼ�Ρ�������Լ�˴洢�ռ䣬���ҿ���ʹ�ö�����ɫ���߼����ʵ�ģʽ������ͼ�Ρ�",
    30+20,200+20,22,10,DARKGREEN);
    vpost();
    getch();
}

void show_2_6(void)
{
    LoadDAC("yue.bmp");
    QPutImage(0,0,yue);
    vpost();
    getch();
    cls(31);
    vpost();
    setdac();
}

void show_3(void)
{
    char key ;
    static angelpos=1 ;
    int angelcount=0 ;
    Animate256 angel1,angel2,angel3,angel4,angel5 ;
    angel1=angell ;
    /*�������͵���һ���÷���ֱ�ӽ����ѷ����ͼ����Դ*/
    angel1.x=0 ;
    angel1.y=350 ;
    angel1.nowplaying=1 ;
    /*����tempangel�ĵ�ǰ֡*/
    angel1.timedelay=6 ;
    /*��ʱ6֡*/
    angel2=angel1 ;
    angel2.nowplaying=2 ;
    angel3=angel1 ;
    angel3.nowplaying=3 ;
    angel4=angel1 ;
    angel4.nowplaying=4 ;
    angel5=angel1 ;
    angel5.nowplaying=5 ;
    START3 :
    cls(156);
    TEXT_SIZE=TX_BIG ;
    puts256("ʹ�á�����ѡ�񣬻س�ȷ����ESC���˳�",150,120,0);
    puts256("��ͼ����ƽ�̡�",230,180,BROWN);
    puts256("��ȫ��ͼ��ĵ��뵭����",205,180+40,BROWN);
    puts256("��ȫ��Ļͼ�񿽱���",223,180+80,BROWN);
    TEXT_SIZE=TX_NORMAL ;
    while(1)
    {
        bar(angell.x,angell.y,angell.width,angell.height,156);
        bar(angelr.x,angelr.y,angelr.width,angelr.height,156);
        puts256("������������������������",208,195+(angelpos-1)*40,156);
        if(kbhit())
        {
            key=getch();
            if(key==0)
            {
                key=getch();
                if(key==UP&&angelpos>1)
                {
                    angelpos--;
                    angell.y=140+(angelpos-1)*40 ;
                    angelr.y=140+(angelpos-1)*40 ;
                }
                if(key==DOWN&&angelpos<3)
                {
                    angelpos++;
                    angell.y=140+(angelpos-1)*40 ;
                    angelr.y=140+(angelpos-1)*40 ;
                }
            }
            if(key==13)
            switch(angelpos)
            {
                case 1 :
                show_3_1();
                goto START3 ;
                case 2 :
                show_3_2();
                goto START3 ;
                case 3 :
                show_3_3();
                goto START3 ;
            }
            if(key==27)break ;
        }
        puts256("������������������������",208,195+(angelpos-1)*40,RED);
        showanimate(&angell);
        showanimate(&angelr);
        bar(0,350,640,80,156);
        angel1.x=0-angelcount ;
        angel2.x=156-angelcount ;
        angel3.x=156*2-angelcount ;
        angel4.x=156*3-angelcount ;
        angel5.x=156*4-angelcount ;
        showanimate(&angel1);
        showanimate(&angel2);
        showanimate(&angel3);
        showanimate(&angel4);
        showanimate(&angel5);
        if(angelcount==155)
        {
            angelcount=0 ;
            /*��ʹ����ʱ�غ�λ�ñ������һ֡*/
            angel1.nowplaying=(angel1.nowplaying+1)%angel1.framecount ;
            angel2.nowplaying=(angel2.nowplaying+1)%angel2.framecount ;
            angel3.nowplaying=(angel3.nowplaying+1)%angel3.framecount ;
            angel4.nowplaying=(angel4.nowplaying+1)%angel4.framecount ;
            angel5.nowplaying=(angel5.nowplaying+1)%angel5.framecount ;
        }
        else angelcount++;
        vpost();
    }
}

void show_3_1(void)
{
    int i=0,j=0,a=0,b=0,c=0,d=0 ;
    Animate256 tempmary=mary ;
    tempmary.timedelay=2 ;
    while(!kbhit())
    {
        for(j=0;j<7;j++)
        for(i=0;i<8;i++)
        QPutImage(i*bk_tc.width-a,j*bk_tc.height-b,bk_tc);
        rectangle(399,49,601,201,0);
        screen_cut.left=400 ;
        screen_cut.right=600 ;
        screen_cut.top=50 ;
        screen_cut.bottom=200 ;
        tempmary.autoplaying=0 ;
        /*�ر�tempmary���Զ�����*/
        for(j=0;j<3;j++)
        for(i=0;i<5;i++)
        {
            tempmary.x=400+c+(i-1)*tempmary.width ;
            tempmary.y=50-d+j*tempmary.height ;
            showanimate(&tempmary);
        }
        tempmary.autoplaying=1 ;
        /*��tempmary���Զ�����*/
        showanimate(&tempmary);
        /*�ò�����Ҫ��Ϊ������һ���ڲ�����*/
        a=(a+1)%bk_tc.width ;
        b=(b+1)%bk_tc.height ;
        c=(c+1)%mary.width ;
        d=(d+1)%mary.height ;
        screen_cut=default_cut ;
        PutImage(30,230,ymhd,28);
        puts256("��ʾ��ͼ��ǰ���ȵ�����Ļ���� screen_cut ��ֵ��",30,100,RED);
        puts256("ʹ�ú�Ҫ�ǵ���screen_cut=default_cut�ָ�Ĭ",30,115,RED);
        puts256("����Ļ����Ŷ��",30,130,RED);
        puts256("�������Ļ���е�ʹ�ã��������ѭ����ʵ��ͼ���ƽ�̣�",140,250,0);
        puts256("���ڸ�ϵͳ�ĸ��ٶȣ���ʹ��̬������ƽ��ͼ��Ҳ����",155,265,0);
        puts256("�ﵽ�ܺõ�Ч���������������ö���ͼ��ȥƽ�̡�",155,280,0);
        vpost();
    }
    getch();
}

void show_3_2(void)
{
    int w,h ;
    char i=0 ;
    Bmp256*texts[4];
    texts[0]=&text1 ;
    texts[1]=&text2 ;
    texts[2]=&text3 ;
    texts[3]=&text4 ;
    do 
    {
        go_inout(0,5000,0);
        cls(0);
        PutMask((640-texts[i]->width)/2,(480-texts[i]->height)/2,*texts[i],WHITE);
        vpost();
        bar((640-texts[i]->width)/2,(480-texts[i]->height)/2,texts[i]->width,texts[i]->height,0);
        go_inout(0,5000,1);
        delay(50000);
        i=(i+1)%4 ;
    }
    while(!kbhit());
    while(kbhit())getch();
}

void show_3_3(void)
{
    QPutImage(-30,-20,deskmap);
    PutImage(40,40,angelr.bmp,28);
    /*��angelr��bmpͼ����Դ��ʾ����Ļ*/
    bar(60,140,270,55,DARKGRAY);
    rectangle(55,135,335,200,DARKGRAY);
    bar(50,150,270,55,190);
    rectangle(45,145,325,210,190);
    boxputs256("��ǰͼ���Ѿ�������printscr.bmp�ļ��У������ֱ��˫����",65,160,30,5,0);
    vpost();
    PrintScreen("printscr.bmp");
    getch();
}

void show_4(void)
{
    char*s0="��ӭʹ�ã�����ɫͼ��ϵͳ��",
    *s1="Welcome Using 256 Colors System!",
    *text="�����ı�����ʾ:�ַ��������޶�����Ĵ�С���Զ�����" ;
    cls(246);
    TEXT_SIZE=TX_NORMAL ;
    puts256("�ѱ�ͼ��ϵͳ�ṩ��������ɹ�ʹ��",140,330,6);
    puts256("���Ƿֱ�Ϊ��",156,345,6);
    puts256("TEXT_SIZE�� Ӣ�Ĵ�С �����Ĵ�С ����Ҫ���ֿ�",140,368,6);
    puts256("��������������������������������������������",140,380,6);
    puts256("NORMAL        14*8      12*12       hzk12",140,390,6);
    puts256("BIG           16*8      16*16       hzk16",140,405,6);
    puts256("SMALL         8*8       <��>         <��>",140,420,6);
    puts256("��ʹ�ú��֣������ǵĳ������������Ⱥ�����ƹ��",124,445,229);
    rectangle(75,15,420+144,270+44,0);
    bar(80,20,480,290,0);
    puts256("TEXT_SIZE=NORMAL:",95,34,233);
    puts256(s0,95,52,252);
    puts256(s1,95,70,28);
    TEXT_SIZE=TX_BIG ;
    puts256("TEXT_SIZE=BIG:",95,95,233);
    puts256(s0,95,115,252);
    puts256(s1,95,135,28);
    TEXT_SIZE=TX_SMALL ;
    puts256("TEXT_SIZE=SMALL:",95,165,233);
    puts256(s1,95,175,28);
    TEXT_SIZE=TX_BIG ;
    puts256("�� �� �� �� �� �� �� �� �� �� �� �� ��",95,280,119);
    TEXT_DIRECTION=0 ;
    puts256("��������...",505,40,255);
    puts256("���������������",525,40,223);
    TEXT_DIRECTION=1 ;
    boxputs256(text,90,200,18,3,223);
    TEXT_SIZE=TX_NORMAL ;
    boxputs256(text,280,200,27,2,223);
    TEXT_SIZE=TX_BIG ;
    printf256(280,250,ORANGE,"%s��24*35+359=%d","��ʽ�����",24*35+359);
    TEXT_SLANT=SL_LEFT ;
    puts256("������б",395,65,159);
    TEXT_SLANT=SL_RIGHT ;
    puts256("������б",395,65+50,159);
    TEXT_SLANT=SL_NONE ;
    TEXT_SIZE=TX_NORMAL ;
    puts256("TEXT_SLANT=SL_LEFT",340,65-15,WHITE);
    puts256("TEXT_SLANT=SL_RIGTH",340,65+35,WHITE);
    vpost();
    getch();
}

void show_5(void)
{
    int i ;
    cls(254);
    TEXT_SIZE=TX_NORMAL ;
    
    circle(140,140,50,RED);
    puts256("��Բ��ʾ",115,135,0);
    ellipse(340,300,100,25,BROWN);
    puts256("����Բ",320,292,0);
    
    for(i=0;i<8;i++)
    {
        rectangle(400+i*10,100+i*10,500-i*10,200-i*10,0);
    }
    line(400,100,500,200,0);
    line(400,200,500,100,0);
    puts256("�û�ͼ����(line,rectangle)���Ƶ�ͼ�Ρ�",200,210,0);
    
    bar(100,250,110,100,5);
    bar(105,255,100,80,255);
    rectangle(105,337,205,347,255);
    bar(110,340,10,5,233);
    bar(155-10,250-10,20,10,0);
    line(155,250,155-50,250-50,0);
    line(155,250,155+50,250-50,0);
    TEXT_SIZE=TX_BIG ;
    puts256("�ԣ� �ӣţ�",107,270,229);
    puts256("��ӭ�տ�",120,300,145);
    TEXT_SIZE=TX_NORMAL ;
    puts256("���û�ͼ����(bar,line,rectangle)���Ƶĵ��ӻ�",130,360,0);
    
    boxputs256("��ϵͳ��ͼ������draw.h�ṩ��һЩ�����Ļ�ͼ���������Ի���һЩ�򵥵�ͼ��",100,400,50,2,0);
    vpost();
    getch();
}

void show_6(void)
{
    int i,j,a=0,b=0 ;
    char is_on,key ;
    static char curtype=1,texts[3][16]=
    {
        "A. ͼ���л���ʾ","B. �ɿض�����ʾ","C. һ��������Ϸ" 
    }
    ;
    while(getmkeyin(mbRight)!=mbRight)
    {
        hidemouse();
        /*��ΪҪ�����µ������ͼ��ֻ��mouse�����غ���ܽ���*/
        for(j=0;j<7;j++)
        for(i=0;i<8;i++)
        QPutImage(-bk_tc.width+a+i*bk_tc.width,-b+j*bk_tc.height,bk_tc);
        a=(a+1)%bk_tc.width ;
        b=(b+1)%bk_tc.height ;
        TEXT_SIZE=TX_NORMAL ;
        rectangle(200,220,600,395,110);
        puts256("�������ۺ�ʹ��256ɫͼ��ϵͳ����ʱ��Ѥ�ö�",222,230,0);
        puts256("�ʵĻ���Ͳ����ˣ���ᾪ̾��ʹ�򵥵�TCҲ�ܻ�",222,230+15,0);
        puts256("������˾�ϸ�Ļ��档�����֤���˱�̵�һ��",222,230+15*2,0);
        puts256("�������Ǿ��ǣ�������������ֻ���벻����",222,230+15*3,0);
        puts256("ʹ�ø�ͼ��ϵͳ��������׹���������",222,300,0);
        puts256("�� Xnview(�������ɶ�����ʽ256ɫBMPλͼ)",222,300+15,0);
        puts256("�� PhotoShop(���������������BMPλͼ)",222,300+15*2,0);
        puts256("С����:Դ���������Windows�������ü��±��༭",222,355,163);
        puts256("Ȼ����TC����File��Load������:*.txt���ɴ򿪡�",222,370,163);
        TEXT_SIZE=TX_BIG ;
        puts256("256ɫͼ��ϵͳ�ۺ���ʾ",30,160,RED);
        puts256("��ǰ�Ļ���֧�����...",250,50,MAGENTA);
        puts256("������꣬������ʲô���...",250,70,MAGENTA);
        puts256("ʹ���������������Ӧ��ĸ����ʾ��Ŀ...",250,90,MAGENTA);
        puts256("�����������һ���귵��������...",250,110,MAGENTA);
        
        getmousexy();
        is_on=-1 ;
        for(i=0;i<3;i++)
        if(mouse.getx>=50&&mouse.getx<=185&&mouse.gety>=200+i*40&&mouse.gety<=216+i*40)
        {
            is_on=i ;
            puts256(texts[i],50,200+i*40,BLUE);
            line(48,218+i*40,185,218+i*40,BLUE);
        }
        else puts256(texts[i],50,200+i*40,0);
        if(is_on>=0)
        {
            if(curtype)
            {
                loadcursor(HAND_CURSOR);
                /*��������꣺3D��ͷ*/
                curtype=0 ;
            }
            if(getmkeyin(mbLeft)==mbLeft)
            /*��������Ӧ����*/
            switch(is_on)
            {
                case 0 :
                show_6_1();
                break ;
                case 1 :
                show_6_2();
                break ;
                case 2 :
                show_6_3();
                getch();
            }
        }
        else 
        if(!curtype)
        {
            loadcursor(DEFAULT_CURSOR);
            /*��������꣺���ι��*/
            curtype=1 ;
        }
        {
            char s[8];
            puts256("��ǰ������꣺",330,430,0);
            printf256(448,430,BLUE,"%4d,%4d",mouse.getx,mouse.gety);
            puts256("��ǰ��������ͣ�",330,450,0);
            if(curtype)puts256("DEFAULT_CURSOR",490,450,BLUE);
            else puts256("HAND_CURSOR",490,450,BLUE);
        }
        if(kbhit())
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
        }
        showmouse();
        getmkeyin(mbLeft);
        /*ȡ����껺��*/
        vpost();
    }
}

/*����������ظ�����max<=255*/
void get_rand(unsigned char n[],unsigned char max)
{
    unsigned char temp[256],m ;
    int i,j ;
    for(i=0;i<max;i++)temp[i]=i ;
    for(i=0;i<max;i++)
    {
        m=((unsigned)biostime(0,0)+rand())%(max-i);
        n[i]=temp[m];
        for(j=0;j<max-m;j++)
        temp[m+j]=temp[m+j+1];
    }
}

void show_6_1(void)
{
    int i,j ;
    char key,s[4][15]=
    {
        "A. �ƶ�ʽ�л�","B. ����ʽ�л�","C.��Ҷ��ʽ�л�","D. չ��ʽ�л�" 
    }
    ;
    for(j=0;j<9;j++)
    for(i=0;i<12;i++)
    QPutImage(i*leafs.width,j*leafs.height,leafs);
    PutMask(180,20,title_qh,0);
    for(i=0;i<4;i++)puts256(s[i],23+i*(fbb.width+8),300,BROWN);
    puts256("����Ӧ��ĸ������ͼ���л���ESC���˳�",150,330,RED);
    TEXT_SIZE=TX_NORMAL ;
    boxputs256("��������ʾ4����Ч����������ש��������ã���256ɫͼ��ϵͳ�����Կ����ǳ���������л�Ч�������߿����Լ�ȥ�о�",70,380,60,2,0);
    for(i=0;i<4;i++)
    {
        QPutImage(i*(fbb.width+8)+8,60,fbb);
        rectangle(i*(fbb.width+8)+7,59,i*(fbb.width+8)+8+fbb.width,fbb.height+60,GREEN);
    }
    vpost();
    while(1)
    if(kbhit())
    {
        key=getch();
        if(key==27)break ;
        switch(key)
        {
            case 'a' :
            /*�л�Ч��1*/
            case 'A' :
            {
                screen_cut.left=8 ;
                screen_cut.right=7+fbb.width ;
                screen_cut.top=60 ;
                screen_cut.bottom=59+fbb.height ;
                for(i=0;i<fbb.height;i++)
                {
                    QPutImage(8,60-lxr.height+i,lxr);
                    QPutImage(8,60+i,fbb);
                    vpost();
                }
                sleep(1);
                for(i=0;i<fbb.height;i++)
                {
                    screen_cut.top=60 ;
                    screen_cut.bottom=60+i ;
                    QPutImage(8,59,fbb);
                    screen_cut.top=60+i ;
                    screen_cut.bottom=59+fbb.height ;
                    QPutImage(8,59,lxr);
                    vpost();
                }
                break ;
            }
            case 'b' :
            /*�л�Ч��2*/
            case 'B' :
            {
                unsigned char show[235];
                get_rand(show,fbb.width);
                screen_cut.top=60 ;
                screen_cut.bottom=59+fbb.height ;
                for(i=0;i<fbb.width;i++)
                {
                    screen_cut.left=16+lxr.width+show[i];
                    screen_cut.right=16+lxr.width+show[i];
                    QPutImage(lxr.width+16,60,lxr);
                    vpost();
                }
                sleep(1);
                get_rand(show,fbb.height);
                screen_cut.left=16+fbb.width ;
                screen_cut.right=15+fbb.width*2 ;
                for(i=0;i<fbb.height;i++)
                {
                    screen_cut.top=60+show[i];
                    screen_cut.bottom=60+show[i];
                    QPutImage(fbb.width+16,60,fbb);
                    vpost();
                }
                break ;
            }
            case 'c' :
            /*�л�Ч��3*/
            case 'C' :
            {
                screen_cut.left=fbb.width*2+24 ;
                screen_cut.right=fbb.width*3+24 ;
                for(j=0;j<lxr.height/10;j++)
                {
                    for(i=0;i<=10;i++)
                    {
                        screen_cut.top=60+i*(lxr.height/10);
                        screen_cut.bottom=60+i*(lxr.height/10)+j ;
                        QPutImage(lxr.width*2+24,60,lxr);
                    }
                    delay(1000);
                    vpost();
                }
                sleep(1);
                screen_cut.top=60 ;
                screen_cut.bottom=59+fbb.height ;
                for(j=0;j<lxr.width/7;j++)
                {
                    for(i=0;i<=7;i++)
                    {
                        screen_cut.left=fbb.width*2+24+i*(fbb.width/7);
                        screen_cut.right=fbb.width*2+24+i*(fbb.width/7)+j ;
                        QPutImage(fbb.width*2+24,60,fbb);
                    }
                    delay(1000);
                    vpost();
                }
                break ;
            }
            case 'd' :
            /*�л�Ч��4*/
            case 'D' :
            {
                int centre_x=fbb.width*3+32+fbb.width/2,
                centre_y=60+fbb.height/2 ;
                for(i=0;i<=lxr.height/2;i++)
                {
                    screen_cut.left=centre_x-i ;
                    screen_cut.right=centre_x+i ;
                    screen_cut.top=centre_y-i ;
                    screen_cut.bottom=centre_y+i ;
                    QPutImage(lxr.width*3+32,60,lxr);
                    vpost();
                }
                sleep(1);
                for(i=0;i<=fbb.height;i++)
                {
                    screen_cut.left=centre_x-i ;
                    screen_cut.right=centre_x+i ;
                    screen_cut.top=centre_y-i ;
                    screen_cut.bottom=centre_y+i ;
                    QPutImage(fbb.width*3+32,60,fbb);
                    vpost();
                }
                break ;
            }
        }
        while(kbhit())getch();
    }
    screen_cut=default_cut ;
}

void show_6_2(void)
{
    int i,j ;
    char k=0,key,direction=1 ;
    Animate256 bird ;
    initanimate(&bird,100,100,4,2,28,"");
    bird.bmp=birdr ;
    /*Animate.bmpҲ����ֱ�Ӹ�ֵ�ѷ�����Դ��Bmp256*/
    bird.width=bird.bmp.width/bird.framecount ;
    /*���������Ļ�һЩAnimate��Ա��Ҫ����*/
    bird.height=bird.bmp.height/bird.framecount ;
    while(1)
    {
        for(j=0;j<7;j++)
        for(i=0;i<9;i++)
        QPutImage(i*81-k,j*81-k,leafs2);
        k=(k+1)%81 ;
        PutImage(640-say.width,480-say.height,say,28);
        bar(350,200,170,120,255);
        rectangle(347,197,523,323,168);
        line(523,323,550,338,168);
        TEXT_SIZE=TX_NORMAL ;
        boxputs256("���ʾ�����µ�256ɫͼ�������ɵĿɿض�����������Ļ�ϵ���һֻ�ܼ��̷�������ƵĶ������������ɰ���(ESC���˳�)",355,203,20,7,204);
        if(kbhit())
        {
            key=getch();
            if(key==0)
            {
                key=getch();
                if(key==UP)
                if(bird.y>=-bird.height/2)bird.y-=3 ;
                if(key==DOWN)
                if(bird.y<=479-bird.height/2)bird.y+=3 ;
                if(key==LEFT)
                {
                    if(direction==1)
                    {
                        bird.bmp=birdl ;
                        direction=-1 ;
                    }
                    else 
                    if(bird.x>=-bird.width/2)bird.x-=3 ;
                }
                if(key==RIGHT)
                {
                    if(direction==-1)
                    {
                        bird.bmp=birdr ;
                        direction=1 ;
                    }
                    else 
                    if(bird.x<=639-bird.width/2)bird.x+=3 ;
                }
                while(kbhit())getch();
            }
            if(key==27)break ;
        }
        showanimate(&bird);
        vpost();
    }
}

void next_direction(float xpos,float ypos,float*xspeed,float*yspeed,int stickx,char map[])
{
    int x,y ;
    if(xpos<0||xpos+11>639)*xspeed=-*xspeed ;
    if(ypos<0||ypos>490)*yspeed=-*yspeed ;
    if(ypos==449&&xpos+5>stickx&&xpos+5<stickx+stick.width)
    {
        *xspeed=*xspeed+(xpos-stickx-24)/60 ;
        if(*xspeed<-0.9)*xspeed=-0.9 ;
        if(*xspeed>0.9)*xspeed=0.9 ;
        *yspeed=-*yspeed ;
    }
    y=(ypos+5.5)/16 ;
    if(*xspeed<0)x=(xpos-1)/32 ;
    if(*xspeed>0)x=(xpos+11)/32 ;
    if(*xspeed!=0&&y<20&&map[y*20+x])
    {
        *xspeed=-*xspeed ;
        bar(x*32,y*16,32,16,0);
        map[y*20+x]=0 ;
    }
    x=(xpos+5.5)/32 ;
    if(*yspeed<0)y=(ypos-1)/16 ;
    if(*yspeed>0)y=(ypos+11)/16 ;
    if(*yspeed!=0&&y<20&&map[y*20+x])
    {
        *yspeed=-*yspeed ;
        bar(x*32,y*16,32,16,0);
        map[y*20+x]=0 ;
    }
}

void show_6_3(void)
{
    int i,j,stickx=380 ;
    float xspeed=0,yspeed=1,xpos=400,ypos=400 ;
    char key,map[20][20]=
    {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,229,229,229,0,0,175,175,175,0,0,0,0,0,255,255,255,255,0,0,
        0,0,229,0,0,175,0,0,0,175,0,0,0,255,0,255,255,0,255,0,
        0,0,229,0,0,175,0,0,0,0,0,0,255,0,255,0,0,255,0,255,
        0,0,229,0,0,175,0,0,0,0,0,0,255,0,255,0,0,0,0,255,
        0,0,229,0,0,175,0,0,0,175,0,0,255,0,255,0,0,255,0,255,
        0,0,229,0,0,0,175,175,175,0,0,0,0,255,0,255,255,0,255,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,0,0,
        0,0,127,127,0,0,252,252,252,0,0,79,79,0,0,0,0,0,0,0,
        0,127,0,0,127,0,252,0,0,0,79,0,0,0,0,0,0,0,0,0,
        0,0,0,127,0,0,252,252,0,0,79,79,79,0,0,0,0,0,0,0,
        0,0,127,0,0,0,0,0,252,0,79,0,0,79,0,0,0,0,0,0,
        0,127,0,0,127,0,0,0,252,0,79,0,0,79,0,0,0,0,0,0,
        0,127,127,127,127,0,252,252,0,0,0,79,79,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,28,0,0,0,0,0,28,0,0,0,0,0,0,0,
        0,0,0,0,0,28,0,28,0,0,0,28,0,28,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,28,0,0,0,28,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,28,28,28,0,0,0,0,0,0,0,0,0,
    }
    ,
    ball[11][11]=
    {
        0,0,0,182,219,182,219,182,0,0,0,
        0,0,182,219,219,255,218,182,146,0,0,
        0,182,219,219,255,218,255,218,182,146,0,
        219,182,219,255,255,255,255,219,182,146,218,
        183,182,255,219,255,255,255,218,219,146,182,
        182,219,218,255,255,255,219,219,182,182,146,
        182,146,219,218,255,218,255,218,183,145,146,
        182,146,182,219,219,219,218,219,146,110,182,
        0,109,146,146,183,182,182,145,146,109,0,
        0,0,109,146,146,146,109,110,109,0,0,
        0,0,0,146,146,109,146,146,0,0,0,
    }
    ,
    text[50]="���������ʼ�����������Ƶ��壬��Ϸ�а�ESC���˳�" ;
    cls(0);
    for(j=0;j<20;j++)
    for(i=0;i<20;i++)
    if(map[i][j])
    {
        bar(j*32,i*16,31,16,map[i][j]);
        rectangle(j*32,i*16,j*32+31,i*16+15,255);
    }
    puts256(text,150,400,250);
    QPutImage(stickx,460,stick);
    vpost();
    getch();
    SurfaceMode=NO_SURFACE ;
    /*Ϊ�˱���vpost���ٶ��ӳ٣��ڻ�ͼ�����ߵ�����£�ǿ��ʹ���޻���ҳ����ģʽ���ٻ�ͼ*/
    puts256(text,150,400,0);
    while(1)
    {
        next_direction(xpos,ypos,&xspeed,&yspeed,stickx,map);
        for(j=0;j<11;j++)
        for(i=0;i<11;i++)
        if(ball[i][j])
        putpixel(xpos+0.5+i,ypos+0.5+j,BLACK);
        xpos+=xspeed ;
        ypos+=yspeed ;
        for(j=0;j<11;j++)
        for(i=0;i<11;i++)
        if(ball[i][j])
        putpixel(xpos+0.5+i,ypos+0.5+j,ball[i][j]);
        QPutImage(stickx,460,stick);
        if(kbhit())
        {
            key=getch();
            if(key==0)
            {
                key=getch();
                if(key==LEFT)stickx-=3 ;
                if(key==RIGHT)stickx+=3 ;
            }
            if(key==27)break ;
        }
        delay(300);
    }
    SurfaceMode=SINGLE_SURFACE ;
    /*�ָ�������ҳ����ģʽ*/
}

void show_7(void)
{
    int color ;
    char value[4]=
    {
        0 
    }
    ;
    cls(0);
    for(color=0;color<256;color++)
    {
        bar(40*(color%16),30*(color/16),27,14,color);
        itoa(color,value,10);
        puts256(value,40*(color%16)+2,30*(color/16)+14,255);
    }
    vpost();
    getch();
}

void dialogbox(int x,int y,int width,int height)
{
    int i ;
    putspr(x,y,1,1,dialog,MAGENTA);
    putspr(x+width*32-32,y,3,1,dialog,MAGENTA);
    putspr(x,y+height*32-32,1,3,dialog,MAGENTA);
    putspr(x+width*32-32,y+height*32-32,3,3,dialog,MAGENTA);
    for(i=1;i<width-1;i++)
    putspr(x+32*i,y,2,1,dialog,MAGENTA);
    for(i=1;i<height-1;i++)
    putspr(x,y+32*i,1,2,dialog,MAGENTA);
    for(i=1;i<height-1;i++)
    putspr(x+32*width-32,y+32*i,3,2,dialog,MAGENTA);
    for(i=1;i<width-1;i++)
    putspr(x+32*i,y+32*height-32,2,3,dialog,MAGENTA);
    
    alphabar(x+31,y+32,32*width-62,32*height-63,BLUE);
}

void clearkeybuffer()
{
    while(kbhit())getch();
}

void show_8(void)
{
    int i=1 ;
    
    QPutImage(0,0,island);
    
    dialogbox(95,300,14,5);
    boxputs256("������ALPHA�㷨���ӻ���⻭������͸���Ի���,��RPG�в��Ǻ�������?",135,340,41,10,YELLOW);
    
    TEXT_SIZE=TX_NORMAL ;
    alphaimage(50,30,bmw,28);
    boxputs256("<-������alphaimage������ʾ��͸��256ɫλͼ",350,50,20,20,BLUE);
    
    alphamask(250,150,textmask,WHITE);
    boxputs256("������alphamask������ʾ��͸����ɫ����λͼ->",50,150,20,20,PINK);
    
    alphaputspr(90,250,2,2,yaka,MAGENTA);
    boxputs256("<-alphaputspr������ʾ��͸���ӻ���,�������ӻ�����ļ�yaka.bmp��",150,250,40,20,RED);
    
    vpost();
    getch();
    clearkeybuffer();
    
    cls(0);
    
    TEXT_SIZE=TX_BIG ;
    QPutImage(0,0,yaka.image);
    dialogbox(95,300,14,5);
    boxputs256("�����ǿ��۵��ӻ����.��������Ҫ�ѵ�һ�У������еĺ���ץ����.�����RPG�ĵ�ͼ������˵�ǳ���Ҫ.",135,340,41,10,YELLOW);
    vpost();
    getch();
    clearkeybuffer();
    
    cls(0);
    putspr(45,60,6,1,yaka,MAGENTA);
    dialogbox(95,300,14,5);
    boxputs256("��,����ץ������,�����ӻ����,�Ժ����Ǳ���Ϸʱ�Ϳ��԰Ѵ����ӻ������һ��BMPͼ����,��Դ������Ҳ�ʹ����ˣ�              ���亯������:Cat Tom",135,337,41,10,YELLOW);
    vpost();
    ;
    getch();
    clearkeybuffer();
    
    
}
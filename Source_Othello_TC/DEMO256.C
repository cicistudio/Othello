#include "all256.h"

#define UP 72 
#define DOWN 80 
#define LEFT 75 
#define RIGHT 77 
/*函数声明*/
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

/*最好将资源声明在外部，以便各函数模块都可以使用*/
/*一般图片定义*/
Bmp256 candle,title,mars,earth ;
Bmp256 fbb,model,snow,bmw ;
Bmp256 ymhd,deskmap,say,satellite,yue,testmask,textmask,bkgdmask ;
Bmp256 text1,text2,text3,text4,bk_tc ;
Bmp256 title_qh,leafs,lxr,leafs2,birdl,birdr,stick ;
Bmp256 island ;
/*多幅图片定义*/
Animate256 universe,frame,arrow ;
Animate256 mary,bqla,bqlb,bowwave,aniearth ;
Animate256 angell,angelr ;
/*可提取图片定义*/
Sprlib dialog ;
Sprlib tianshi ;
Sprlib yaka ;

main()
{
    char key,arrowystep=1 ;
    
    init256(SINGLE_SURFACE);
    /*初始化屏幕缓冲为单缓冲页结构，该语句必须写在最前面*/
    initmouse();
    /*初始化256色鼠标*/
    initalpha();
    /*初始化颜色匹配矩阵*/
    
    /*开始加载各项资源，注意：该图像资源除了用DestroyAllImage释放所有资源外(复位BMP加载指针)，没有提供其他方式进行释放*/
    /*因此，保证资源只被加载一次*/
    candle=LoadBMP("烛台.bmp");
    title=LoadBMP("title0.bmp");
    mars=LoadBMP("065.bmp");
    earth=LoadBMP("earth.bmp");
    
    fbb=LoadBMP("fbb.bmp");
    model=LoadBMP("model.bmp");
    snow=LoadBMP("雪原.bmp");
    bmw=LoadBMP("bmw.bmp");
    
    ymhd=LoadBMP("ymhd.bmp");
    deskmap=LoadBMP("壁纸.bmp");
    say=LoadBMP("say.bmp");
    satellite=LoadBMP("人造卫星.bmp");
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
    birdl=LoadBMP("bird向左.bmp");
    birdr=LoadBMP("bird向右.bmp");
    
    stick=LoadBMP("stick.bmp");
    
    island=LoadBMP("island.bmp");
    /*动态显示图*/
    initanimate(&universe,130,360,5,4,0,"宇宙序列.bmp");
    initanimate(&frame,530+12,300-35,4,6,0,"火焰序列.bmp");
    initanimate(&arrow,240,153+(arrowystep-1)*30,5,5,28,"箭头序列.bmp");
    
    initanimate(&mary,30,30,4,3,28,"玛莉.bmp");
    initanimate(&bqla,100,300,6,5,28,"版奇良A.bmp");
    initanimate(&bqlb,100,300,6,3,28,"版奇良B.bmp");
    initanimate(&bowwave,190,280,5,2,28,"气功炮.bmp");
    initanimate(&aniearth,320,100,15,4,0,"地球序列.bmp");
    
    initanimate(&angell,410,140,6,5,28,"天使L.bmp");
    initanimate(&angelr,110,140,6,5,28,"天使R.bmp");
    
    dialog=loadsprlib(32,32,"dialog.bmp");
    tianshi=loadsprlib(89,70,"天使L.bmp");
    yaka=loadsprlib(32,32,"yaka.bmp");
    
    START :
    cls(0);
    PutImage(530,300,candle,28); /*显示图片*/
    QPutImage(25,20,title);
    QPutImage(25,225,earth);
    TEXT_SIZE=TX_NORMAL ;
    puts256("〖For Turbo C 2 版本:2.3〗",200,85,219);
    puts256("使用↑↓键选择，回车确定，也可以按相应数字键",180,440,YELLOW);
    TEXT_SIZE=TX_BIG ;
    puts256("1. 位图函数演示.",295,165,239);
    puts256("2. 图像标准操作演示.",295,165+30,31);
    puts256("3. 图像特效操作演示.",295,165+30*2,156);
    puts256("4. 文字操作演示.",295,165+30*3,246);
    puts256("5. 绘图函数库演示.",295,165+30*4,254);
    puts256("6. 256色图形系统综合演示.",295,165+30*5,251);
    puts256("7. XNVIEW 256色抖动色表.",295,165+30*6,122);
    puts256("8. ALPHA混合与图素库的调用.",295,165+30*7,147);
    puts256("9. 退出演示程序(ESC).",295,165+30*8,255);
    while(1)
    {
        if(kbhit())
        {
            key=getch();
            if(key==0)
            {
                key=getch();
                /*方向键：上*/
                if(key==UP&&arrowystep>1)
                {
                    bar(arrow.x,arrow.y,arrow.width,arrow.height,0);
                    arrow.nowplaying=0 ;
                    arrowystep--;
                    arrow.y-=30 ;
                }
                /*方向键：下*/
                if(key==DOWN&&arrowystep<9)
                {
                    bar(arrow.x,arrow.y,arrow.width,arrow.height,0);
                    arrow.nowplaying=0 ;
                    arrowystep++;
                    arrow.y+=30 ;
                }
            }
            /*回车键*/
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
            /*ESC键*/
        }
        Qshowanimate(&universe);
        /*绘制动画：宇宙旋涡*/
        Qshowanimate(&frame);
        /*绘制动画：火焰*/
        Qshowanimate(&arrow);
        /*绘制动画：箭头*/
        vpost();
        /*更新画面，单缓冲页系统专用*/
    }
    close256();
}

void show_1(void)   /*位图函数演示.*/
{
    cls(239);
    rectangle(4,4,150+5,234+5,255);
    TEXT_SIZE=TX_NORMAL ;
    puts256("←输出256色BMP位图(fbb.bmp)",160,50,0);
    puts256("以带掩码形式输出256色BMP位图(model.bmp)→",160,70,0);
    puts256("↓合理利用两种输出方式叠加输出，可以获得很好的效果",30,250,0);
    puts256("该图屏蔽掉254号颜色(淡黄)→",210,120,0);
    puts256("↓该图屏蔽掉28号颜色(淡绿)",210,140,0);
    boxputs256("采用INVERT_PUT模式绘制效果↓",350,340,20,2,0);
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

void show_2(void)    /*图像标准操作演示.*/
{
    char key,arrowypos=1,ymhdxpos=0 ;
    START2 :
    cls(31);
    TEXT_SIZE=TX_NORMAL ;
    puts256("★在新的256色图形系统中，EMS内存技术和屏幕剪切技术赋予了该系统",65,315,229);
    puts256("更简便的操作和更强大的功能",80,330,229);
    puts256("将位图读入EMS再显示，使绘制图像变为从高速的内存中读取",80,360,0);
    puts256("使用基于EMS的单缓冲页结构，即使一屏图像绘制得再多也不会造成屏",80,385,0);
    puts256("幕闪烁",80,400,0);
    puts256("采用了屏幕剪切技术，使滚屏浏览和图像部分显示变的非常简单",80,425,0);
    
    puts256("扩展后的图像基本操作演示，使用↑↓键流览，ESC键退出",105,140,DARKGREEN);
    puts256("Ⅰ. 直接使用QPutImage的图像滚屏",180,165,DARKGREEN);
    puts256("Ⅱ. 调整屏幕剪切后的图像滚屏",180,190,DARKGREEN);
    puts256("Ⅲ. 支持屏幕剪切的位图输出",180,215,DARKGREEN);
    puts256("Ⅳ. 使用简单动画类型Animate256",180,240,DARKGREEN);
    puts256("Ⅴ. 使用2色掩码文件",180,265,DARKGREEN);
    puts256("Ⅵ. 用读色表函数显示自定义色表位图",180,290,DARKGREEN);
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
        puts256("现在正在剪切输出...",220,25,255);
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
    puts256("★使用屏幕剪切后，一切跨越屏幕边界的操作将变得简",100,350,255);
    puts256("单，函数将自动裁剪超过屏幕边界的部分",115,370,255);
    vpost();
    getch();
}

void show_2_4(void)
{
    int changebql=0 ;
    bqlb.nowplaying=0 ;
    /*复位当前播放帧*/
    bqla.nowplaying=0 ;
    bowwave.nowplaying=0 ;
    while(!kbhit())
    {
        cls(0);
        Qshowanimate(&aniearth);
        /*不支持掩码的动画播放，但是速度较快*/
        boxputs256("★从2.0版本以后，该系统开始支持动画序列，由于该系统的高速度和支持使用单缓冲页，在如此高分辨率下的序列动画表现上感觉还不错",50,220,70,2,255);
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
    /*设置点模式为取反*/
    PutMask(270,280,testmask,WHITE);
    PIXEL_MODE=COPY_PUT ;
    /*设置点模式为正常*/
    
    PutMask(20,10,textmask,RED);
    PutMask(220,60,textmask,GREEN);
    PutMask(40,110,textmask,YELLOW);
    PutMask(30,200,bkgdmask,218);
    
    boxputs256("★在2.1版本里，又加入了一种新的输出方法：掩码输出方式。该方式允许以2色的BMP位图为工作掩码来输出文字或图形。不仅节约了存储空间，而且可以使用多种颜色和逻辑画笔的模式来绘制图形。",
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
    /*动画类型的另一种用法：直接借用已分配的图像资源*/
    angel1.x=0 ;
    angel1.y=350 ;
    angel1.nowplaying=1 ;
    /*调整tempangel的当前帧*/
    angel1.timedelay=6 ;
    /*延时6帧*/
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
    puts256("使用↑↓键选择，回车确定，ESC键退出",150,120,0);
    puts256("◎图像块的平铺◎",230,180,BROWN);
    puts256("◎全屏图像的淡入淡出◎",205,180+40,BROWN);
    puts256("◎全屏幕图像拷贝◎",223,180+80,BROWN);
    TEXT_SIZE=TX_NORMAL ;
    while(1)
    {
        bar(angell.x,angell.y,angell.width,angell.height,156);
        bar(angelr.x,angelr.y,angelr.width,angelr.height,156);
        puts256("━━━━━━━━━━━━",208,195+(angelpos-1)*40,156);
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
        puts256("━━━━━━━━━━━━",208,195+(angelpos-1)*40,RED);
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
            /*天使飞行时重合位置必须后移一帧*/
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
        /*关闭tempmary的自动播放*/
        for(j=0;j<3;j++)
        for(i=0;i<5;i++)
        {
            tempmary.x=400+c+(i-1)*tempmary.width ;
            tempmary.y=50-d+j*tempmary.height ;
            showanimate(&tempmary);
        }
        tempmary.autoplaying=1 ;
        /*打开tempmary的自动播放*/
        showanimate(&tempmary);
        /*该播放主要是为了增加一次内部计数*/
        a=(a+1)%bk_tc.width ;
        b=(b+1)%bk_tc.height ;
        c=(c+1)%mary.width ;
        d=(d+1)%mary.height ;
        screen_cut=default_cut ;
        PutImage(30,230,ymhd,28);
        puts256("显示该图像前，先调整屏幕剪切 screen_cut 的值→",30,100,RED);
        puts256("使用后，要记得用screen_cut=default_cut恢复默",30,115,RED);
        puts256("认屏幕剪切哦！",30,130,RED);
        puts256("★配合屏幕剪切的使用，你可以用循环来实现图像的平铺，",140,250,0);
        puts256("由于该系统的高速度，即使动态地生成平铺图像，也可以",155,265,0);
        puts256("达到很好的效果，你甚至可以拿动画图像去平铺。",155,280,0);
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
    /*将angelr的bmp图像资源显示在屏幕*/
    bar(60,140,270,55,DARKGRAY);
    rectangle(55,135,335,200,DARKGRAY);
    bar(50,150,270,55,190);
    rectangle(45,145,325,210,190);
    boxputs256("当前图象已经保存在printscr.bmp文件中，你可以直接双击打开",65,160,30,5,0);
    vpost();
    PrintScreen("printscr.bmp");
    getch();
}

void show_4(void)
{
    char*s0="欢迎使用２５６色图形系统！",
    *s1="Welcome Using 256 Colors System!",
    *text="区域文本的显示:字符将随着限定区域的大小而自动换行" ;
    cls(246);
    TEXT_SIZE=TX_NORMAL ;
    puts256("⊙本图形系统提供３种字体可供使用",140,330,6);
    puts256("它们分别为：",156,345,6);
    puts256("TEXT_SIZE　 英文大小 　中文大小 　需要汉字库",140,368,6);
    puts256("──────────────────────",140,380,6);
    puts256("NORMAL        14*8      12*12       hzk12",140,390,6);
    puts256("BIG           16*8      16*16       hzk16",140,405,6);
    puts256("SMALL         8*8       <无>         <无>",140,420,6);
    puts256("◆使用汉字，让我们的程序更有利与在群众中推广◆",124,445,229);
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
    puts256("♀ ☆ ★ ○ ● ◎ ◇ ◆ □ ■ △ ▲ ♂",95,280,119);
    TEXT_DIRECTION=0 ;
    puts256("文字竖排...",505,40,255);
    puts256("ⅠⅡⅢⅣⅤⅥⅦⅧⅨ",525,40,223);
    TEXT_DIRECTION=1 ;
    boxputs256(text,90,200,18,3,223);
    TEXT_SIZE=TX_NORMAL ;
    boxputs256(text,280,200,27,2,223);
    TEXT_SIZE=TX_BIG ;
    printf256(280,250,ORANGE,"%s：24*35+359=%d","格式化输出",24*35+359);
    TEXT_SLANT=SL_LEFT ;
    puts256("文字左斜",395,65,159);
    TEXT_SLANT=SL_RIGHT ;
    puts256("文字右斜",395,65+50,159);
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
    puts256("画圆演示",115,135,0);
    ellipse(340,300,100,25,BROWN);
    puts256("画椭圆",320,292,0);
    
    for(i=0;i<8;i++)
    {
        rectangle(400+i*10,100+i*10,500-i*10,200-i*10,0);
    }
    line(400,100,500,200,0);
    line(400,200,500,100,0);
    puts256("用绘图函数(line,rectangle)绘制的图形↑",200,210,0);
    
    bar(100,250,110,100,5);
    bar(105,255,100,80,255);
    rectangle(105,337,205,347,255);
    bar(110,340,10,5,233);
    bar(155-10,250-10,20,10,0);
    line(155,250,155-50,250-50,0);
    line(155,250,155+50,250-50,0);
    TEXT_SIZE=TX_BIG ;
    puts256("ＴＶ ＳＥＴ",107,270,229);
    puts256("欢迎收看",120,300,145);
    TEXT_SIZE=TX_NORMAL ;
    puts256("↑用绘图函数(bar,line,rectangle)绘制的电视机",130,360,0);
    
    boxputs256("该系统绘图函数库draw.h提供了一些基本的绘图函数，可以绘制一些简单的图形",100,400,50,2,0);
    vpost();
    getch();
}

void show_6(void)
{
    int i,j,a=0,b=0 ;
    char is_on,key ;
    static char curtype=1,texts[3][16]=
    {
        "A. 图像切换演示","B. 可控动画演示","C. 一个弹球游戏" 
    }
    ;
    while(getmkeyin(mbRight)!=mbRight)
    {
        hidemouse();
        /*因为要加载新的鼠标光标图像只有mouse被隐藏后才能进行*/
        for(j=0;j<7;j++)
        for(i=0;i<8;i++)
        QPutImage(-bk_tc.width+a+i*bk_tc.width,-b+j*bk_tc.height,bk_tc);
        a=(a+1)%bk_tc.width ;
        b=(b+1)%bk_tc.height ;
        TEXT_SIZE=TX_NORMAL ;
        rectangle(200,220,600,395,110);
        puts256("当灵活的综合使用256色图形系统函数时，绚烂多",222,230,0);
        puts256("彩的画面就产生了，你会惊叹即使简单的TC也能画",222,230+15,0);
        puts256("画出如此精细的画面。在这里，证明了编程的一个",222,230+15*2,0);
        puts256("真理，那就是：不怕做不到，只怕想不到。",222,230+15*3,0);
        puts256("使用该图形系统建议的配套工具软件：",222,300,0);
        puts256("⒈ Xnview(用于生成抖动格式256色BMP位图)",222,300+15,0);
        puts256("⒉ PhotoShop(用于制作带掩码的BMP位图)",222,300+15*2,0);
        puts256("小技巧:源代码可以在Windows环境下用记事本编辑",222,355,163);
        puts256("然后在TC下用File→Load，输入:*.txt即可打开。",222,370,163);
        TEXT_SIZE=TX_BIG ;
        puts256("256色图形系统综合演示",30,160,RED);
        puts256("当前的画面支持鼠标...",250,50,MAGENTA);
        puts256("动动鼠标，看看有什么结果...",250,70,MAGENTA);
        puts256("使用鼠标左键点击或按相应字母键演示项目...",250,90,MAGENTA);
        puts256("按其它键或右击鼠标返回主画面...",250,110,MAGENTA);
        
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
                /*加载鼠标光标：3D箭头*/
                curtype=0 ;
            }
            if(getmkeyin(mbLeft)==mbLeft)
            /*点击鼠标响应代码*/
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
            /*加载鼠标光标：手形光标*/
            curtype=1 ;
        }
        {
            char s[8];
            puts256("当前鼠标坐标：",330,430,0);
            printf256(448,430,BLUE,"%4d,%4d",mouse.getx,mouse.gety);
            puts256("当前鼠标光标类型：",330,450,0);
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
        /*取走鼠标缓冲*/
        vpost();
    }
}

/*生成随机不重复数组max<=255*/
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
        "A. 移动式切换","B. 拉线式切换","C.百叶窗式切换","D. 展开式切换" 
    }
    ;
    for(j=0;j<9;j++)
    for(i=0;i<12;i++)
    QPutImage(i*leafs.width,j*leafs.height,leafs);
    PutMask(180,20,title_qh,0);
    for(i=0;i<4;i++)puts256(s[i],23+i*(fbb.width+8),300,BROWN);
    puts256("按相应字母键启动图像切换，ESC键退出",150,330,RED);
    TEXT_SIZE=TX_NORMAL ;
    boxputs256("★这里演示4个简单效果，仅做抛砖引玉的作用，用256色图形系统还可以开发非常多的其它切换效果，读者可以自己去研究",70,380,60,2,0);
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
            /*切换效果1*/
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
            /*切换效果2*/
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
            /*切换效果3*/
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
            /*切换效果4*/
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
    /*Animate.bmp也可以直接赋值已分配资源的Bmp256*/
    bird.width=bird.bmp.width/bird.framecount ;
    /*不过这样的话一些Animate成员还要设置*/
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
        boxputs256("这个示例用新的256色图像函数生成的可控动画，现在屏幕上的是一只受键盘方向键控制的动画宠物鸟，它可爱吗？(ESC键退出)",355,203,20,7,204);
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
    text[50]="按任意键开始，←→键控制档板，游戏中按ESC键退出" ;
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
    /*为了避免vpost的速度延迟，在绘图量不高的情况下，强行使用无缓冲页绘制模式加速绘图*/
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
    /*恢复单缓冲页绘制模式*/
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
    boxputs256("这是用ALPHA算法和子画面库画出来的透明对话框,在RPG中不是很有用吗?",135,340,41,10,YELLOW);
    
    TEXT_SIZE=TX_NORMAL ;
    alphaimage(50,30,bmw,28);
    boxputs256("<-这是用alphaimage函数显示的透明256色位图",350,50,20,20,BLUE);
    
    alphamask(250,150,textmask,WHITE);
    boxputs256("这是用alphamask函数显示的透明单色掩码位图->",50,150,20,20,PINK);
    
    alphaputspr(90,250,2,2,yaka,MAGENTA);
    boxputs256("<-alphaputspr函数显示的透明子画面,它来自子画面库文件yaka.bmp。",150,250,40,20,RED);
    
    vpost();
    getch();
    clearkeybuffer();
    
    cls(0);
    
    TEXT_SIZE=TX_BIG ;
    QPutImage(0,0,yaka.image);
    dialogbox(95,300,14,5);
    boxputs256("这是亚卡港的子画面库.我们现在要把第一行，第六列的海星抓出来.这对于RPG的地图处理来说非常重要.",135,340,41,10,YELLOW);
    vpost();
    getch();
    clearkeybuffer();
    
    cls(0);
    putspr(45,60,6,1,yaka,MAGENTA);
    dialogbox(95,300,14,5);
    boxputs256("瞧,它被抓出来了,有了子画面库,以后我们编游戏时就可以把大量子画面放在一张BMP图象中,资源的整理也就大大简化了！              扩充函数作者:Cat Tom",135,337,41,10,YELLOW);
    vpost();
    ;
    getch();
    clearkeybuffer();
    
    
}

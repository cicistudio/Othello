/******************************************/
/*                slb256.h                */
/*                                        */
/*             �ӻ���⺯����             */
/*                                        */
/*            Cat Tom 8.29.2003           */
/******************************************/




/******************************************************************/




/******************************************************************/
typedef struct
{
 int width;          /*�ӻ����*/
 int height;         /*�ӻ����*/
 int xx;             /*�����ӻ�����*/
 int yy;             /*�����ӻ�����*/
 Bmp256 image;       /*ͼ��*/
}Sprlib;



/******************************************************************/
/*�����ӻ����ĺ���*/
Sprlib loadsprlib(int width,int height,char *filename)
{

 Sprlib slib;

 /*����bmpͼ��*/
 slib.image=LoadBMP(filename);

 slib.width=width;
 slib.height=height;

 /*��ͼ�󳤿���ӻ��泤�������������*/
 if(slib.image.width%slib.width!=0||slib.image.height%slib.height!=0)exit(0);

 slib.xx=slib.image.width/slib.width;
 slib.yy=slib.image.height/slib.height;

 return slib;
}


/*��ʾ�ӻ�����е�ͼ��*/
void putspr(int x,int y,int xx,int yy,Sprlib slib,int mode)
{register int i,j;
 register long offsety;

 /*���ͼ��,��Դ��������򷵻�*/
 if(slib.image.type!='B'||xx<1||xx>slib.xx||yy<1||yy>slib.yy)return;

 offsety=(long)slib.image.width*slib.height*(yy-1)+slib.width*(xx-1);
 for(j=0;j<slib.height;j++,offsety+=slib.image.width)
  for(i=0;i<slib.width;i++)
  {if(i+x<screen_cut.left||i+x>screen_cut.right||j+y<screen_cut.top||j+y>screen_cut.bottom)continue;
   if(SurfaceMode)        /*�޻���ҳ��ֱ���������Ļ*/
    byte_emstov((j+y)*640l+i+x,slib.image.ems_offset+offsety+i,mode);
   else                        /*������ҳ�������EMS����ҳ*/
    emsbytecopy((j+y)*640l+i+x,slib.image.ems_offset+offsety+i,mode);
  }

}
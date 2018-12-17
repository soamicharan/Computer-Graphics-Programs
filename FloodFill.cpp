 #include<graphics.h>
#include<stdio.h>
#include<conio.h>
int boundry_col,fill_col,ox,oy;
void FFManger(int xm,int ym,int i,int j);
void FFLU(int x,int y,int i,int j);
void FFRD(int x,int y,int i,int j);
void FFRU(int x,int y,int i,int j);
void FFLD(int x,int y,int i,int j);
int main()
{
    initwindow(400,400);
    circle(200,200,200);
   // rectangle(2,2,700,700);
  //ellipse(400,400,0,360,400,3);
  //int arr[]={100,100,150,150,100,150,100,100};
    //drawpoly(4,arr);
    int xe,ye;
    printf("enter X co-ordinate inside shape -> ");
    scanf("%d",&xe);
    printf("Enter Y co-ordinate inside shape -> ");
    scanf("%d",&ye);
    printf("Enter boundry color-> ");
    scanf("%d",&boundry_col);
    printf("Enter fill color-> ");
    scanf("%d",&fill_col);
    FFManger(xe,ye,1,0);
    FFManger(xe,ye,0,1);
    printf("Done");
    getch();
}
void FFManger(int xm,int ym,int i, int j)
{
    ox=xm;
    oy=ym;
    if(i==1) ym++;
    else xm--;
    FFLD(xm,ym,i,j);
    while(getpixel(xm,ym)!=boundry_col)
    {
        if(i==1) ym++;
        else xm--;
        FFLD(xm,ym,i,j);
    }
    xm=ox;
    ym=oy+1;
    while(getpixel(xm,ym)!=boundry_col)
    {
        if(i==1) ym--;
        else xm--;
        FFLU(xm,ym,i,j);
    }
    xm=ox+1;
    ym=oy-1;
    while(getpixel(xm,ym)!=boundry_col)
    {
        if(i==1) ym++;
        else xm++;
        FFRD(xm,ym,i,j);

    }
    xm=ox+1;
    ym=oy;
    while(getpixel(xm,ym)!=boundry_col)
    {
        if(i==1) ym--;
        else xm++;
        FFRU(xm,ym,i,j);
    }

}
void FFLU(int x,int y,int i,int j)
{
    if(x<0)
        return;
    int cur_col=getpixel(x,y);
    int c1=getpixel(x-1,y-1),c2=getpixel(x-1,y),c3=getpixel(x,y-1);
    if(boundry_col!=cur_col)
    {
        if(c1!=boundry_col&&c2!=boundry_col&&c3!=boundry_col){
        if(cur_col!=fill_col)
            putpixel(x,y,fill_col);
        FFLU(x-i,y-j,i,j);
        }
    }
    else return;
}
void FFRD(int x,int y,int i,int j)
{
    int cur_col=getpixel(x,y);
    int c1=getpixel(x+1,y+1),c2=getpixel(x+1,y),c3=getpixel(x,y+1);
    if(boundry_col!=cur_col)
    {
        if(c1!=boundry_col&&c2!=boundry_col&&c3!=boundry_col){
        if(cur_col!=fill_col)
            putpixel(x,y,fill_col);
        FFRD(x+i,y+j,i,j);
        }
    }
    else return;
}
void FFRU(int x,int y,int i,int j)
{
    int cur_col=getpixel(x,y);
    int c1=getpixel(x+1,y-1),c2=getpixel(x+1,y),c3=getpixel(x,y-1);
    if(boundry_col!=cur_col)
    {
        if(c1!=boundry_col&&c2!=boundry_col&&c3!=boundry_col){
        if(cur_col!=fill_col)
            putpixel(x,y,fill_col);
        FFRU(x+i,y-j,i,j);
        }
    }
    else return;
}
void FFLD(int x,int y,int i,int j)
{
    int cur_col=getpixel(x,y);
    int c1=getpixel(x-1,y+1),c2=getpixel(x-1,y),c3=getpixel(x,y+1);
    if(boundry_col!=cur_col)
    {
        if(c1!=boundry_col&&c2!=boundry_col&&c3!=boundry_col){
       if(cur_col!=fill_col)
            putpixel(x,y,fill_col);
        FFLD(x-i,y+j,i,j);
        }
    }
    else return;
}

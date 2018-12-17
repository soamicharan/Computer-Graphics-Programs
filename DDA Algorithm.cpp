#include<graphics.h>
#include<stdio.h>
#include<conio.h>
int main()
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm,"");
    float x1,y1,x2,y2;
    int x=0,y=0;
    printf("Enter co-ordinates one end of line\nx -> ");
    scanf("%f",&x1);
    printf("y -> ");
    scanf("%f",&y1);
    printf("Enter co-ordinates second end of line\nx -> ");
    scanf("%f",&x2);
    printf("y -> ");
    scanf("%f",&y2);
    if(x1==x2 || y1==y2)
    {
        printf("DDA algorithm implementation is not possible");
        return 0;
    }
    float m = (y2-y1)/(x2-x1);
    if(abs(m)<=1)
    {
        for(int i =(int)x1;i<=(int)x2;i++)
        {
            y1+=m;
            putpixel(i,(int)(y1+0.5),2);
        }
    }
    if(abs(m)>1)
    {
        for(int i =(int)y1;i<=(int)y2;i++)
        {
            x1+=1/m;
            putpixel(i,(int)(x1+0.5),3);
        }
    }
    getch();
}

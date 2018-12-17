#include<stdio.h>
#include<graphics.h>
#include<conio.h>
int main()
{
    int gm = DETECT,gd;

    int x1,y1,x2,y2,col;
    printf("Enter Start co-ordinates of line.\nx -> ");
    scanf("%d",&x1);
    printf("y -> ");
    scanf("%d",&y1);
    printf("Enter end co-ordinates of line.\nx -> ");
    scanf("%d",&x2);
    printf("y -> ");
    scanf("%d",&y2);
    printf("Enter color number -> ");
    scanf("%d",&col);
    initgraph(&gm,&gd,"");
    int m = (y2-y1)/(x2-x1);
    int dx=x2-x1,dy=y2-y1;
    putpixel(x1,y1,col);
    if (m<1)
    {
        int P=2*dy-dx;
        for(int i=0;i<dx-1;i++)
        {
            if(P<0)
            {
                putpixel(++x1,y1,col);
                P=P+2*dy;
            }
            else
            {
                putpixel(++x1,++y1,col);
                P=P+2*dy-2*dx;
            }
        }
    }
    else
    {
        int P=2*dx-dy;
        for(int i=0;i<dy-1;i++)
        {
            if(P<0)
            {
                putpixel(x1,++y1,col);
                P=P+2*dx;
            }
            else
            {
                putpixel(++x1,++y1,col);
                P=P+2*dx-2*dy;
            }
        }
    }
    getch();
    closegraph();
}

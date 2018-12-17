#include<stdio.h>
#include<graphics.h>
int main()
{
    initwindow(500,500);
    int xc,yc,rad;
    printf("Enter center co-ordinates of circle.\n");
    scanf("%d%d",&xc,&yc);
    printf("Enter radius.\n");
    scanf("%d",&rad);
    putpixel(xc,yc+rad,15);
    int p0=(5/4)-rad;
    int x=0,y=rad;
    while(x<y)
    {
        if(p0<0)
        {
            x++;
            p0=p0+2*x+1;
        }
        else
        {
            x++;
            y--;
            p0=p0+2*x+1-2*y;
        }
        putpixel(x+xc,y+yc,15);
        putpixel(-x+xc,y+yc,15);
        putpixel(x+xc,-y+yc,15);
        putpixel(-x+xc,-y+yc,15);
        putpixel(y+xc,x+yc,15);
        putpixel(-y+xc,x+yc,15);
        putpixel(y+xc,-x+yc,15);
        putpixel(-y+xc,-x+yc,15);
    }
    getch();
}

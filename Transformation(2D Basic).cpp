#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>
float bufmat[20][3];
float tempmat[20][3];
float trans[][3]={{1,0,0},{0,1,0},{0,0,1}};
int np,boundry_col,fill_col,ox,oy;
void Transformation(float *mat1,int r1,int c1,float *mat2,int r2,int c2)
{
   float temp;
   for(int i=0;i<r1;i++)
   {
       for(int j=0;j<c2;j++)
       {
           temp=0;
           for(int k=0;k<c1;k++)
           {
              temp+=*((mat1+i*c1)+k)**((mat2+k*c2)+j);
           }
           bufmat[i][j]=temp;
       }
   }
}
void copy_matrix(int r,int c)
{
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            tempmat[i][j]=bufmat[i][j];
}
void Rotate(int xr,int yr,double theta,float *in_mat)
{
        trans[2][0]=-xr;trans[2][1]=-yr;
        Transformation(in_mat,np,3,&trans[0][0],3,3);
        copy_matrix(np,3);
        trans[2][0]=0;trans[2][1]=0;
        trans[0][0]=cos(theta*(3.14/180));trans[0][1]=sin(theta*(3.14/180));
        trans[1][0]=-sin(theta*(3.14/180));trans[1][1]=cos(theta*(3.14/180));
        Transformation(&tempmat[0][0],np,3,&trans[0][0],3,3);
        copy_matrix(np,3);
        trans[2][0]=xr;trans[2][1]=yr;
        trans[0][0]=1;trans[0][1]=0;
        trans[1][0]=0;trans[1][1]=1;
        Transformation(&tempmat[0][0],np,3,&trans[0][0],3,3);
        copy_matrix(np,3);
}
void Scale(float sc,float *in_mat)
{
        trans[1][1]=sc;
        trans[0][0]=sc;
        Transformation(in_mat,np,3,&trans[0][0],3,3);
        copy_matrix(np,3);
}
void Transition(int x,int y,float *in_mat)
{
        trans[2][0]=x;
        trans[2][1]=y;
        Transformation(in_mat,np,3,&trans[0][0],3,3);
        copy_matrix(np,3);
}
void Reflect(int x1,int y1,int x2,int y2,double theta,float *in_mat)
{
        trans[2][0]=-x1;trans[2][1]=-y1;
        Transformation(in_mat,np,3,&trans[0][0],3,3);
        copy_matrix(np,3);
        trans[2][0]=0;trans[2][1]=0;
        trans[0][0]=cos(theta);trans[0][1]=-sin(theta);
        trans[1][0]=sin(theta);trans[1][1]=cos(theta);
        Transformation(&tempmat[0][0],np,3,&trans[0][0],3,3);
        copy_matrix(np,3);
        trans[0][0]=1;trans[0][1]=0;
        trans[1][0]=0;trans[1][1]=-1;
        Transformation(&tempmat[0][0],np,3,&trans[0][0],3,3);
        copy_matrix(np,3);
        trans[0][0]=cos(theta);trans[0][1]=sin(theta);
        trans[1][0]=-sin(theta);trans[1][1]=cos(theta);
        Transformation(&tempmat[0][0],np,3,&trans[0][0],3,3);
        copy_matrix(np,3);
        trans[0][0]=1;trans[0][1]=0;
        trans[1][0]=0;trans[1][1]=1;
        trans[2][0]=x1;trans[2][1]=y1;
        Transformation(&tempmat[0][0],np,3,&trans[0][0],3,3);
        copy_matrix(np,3);
}

void FFLU(int x,int y,int i,int j)
{
    if(x<0)
        return;
    int cur_col=getpixel(x,y);int c1=getpixel(x-1,y-1),c2=getpixel(x-1,y),c3=getpixel(x,y-1);
    if(boundry_col!=cur_col){if(c1!=boundry_col&&c2!=boundry_col&&c3!=boundry_col){if(cur_col!=fill_col){putpixel(x,y,fill_col);}FFLU(x-i,y-j,i,j);}}
    else return;
}
void FFRD(int x,int y,int i,int j)
{
    int cur_col=getpixel(x,y);int c1=getpixel(x+1,y+1),c2=getpixel(x+1,y),c3=getpixel(x,y+1);
    if(boundry_col!=cur_col){if(c1!=boundry_col&&c2!=boundry_col&&c3!=boundry_col){if(cur_col!=fill_col){putpixel(x,y,fill_col);}FFRD(x+i,y+j,i,j);}}
    else return;
}
void FFRU(int x,int y,int i,int j)
{
    int cur_col=getpixel(x,y);int c1=getpixel(x+1,y-1),c2=getpixel(x+1,y),c3=getpixel(x,y-1);
    if(boundry_col!=cur_col){if(c1!=boundry_col&&c2!=boundry_col&&c3!=boundry_col){if(cur_col!=fill_col){putpixel(x,y,fill_col);}FFRU(x+i,y-j,i,j);}}
    else return;
}
void FFLD(int x,int y,int i,int j)
{
    int cur_col=getpixel(x,y);int c1=getpixel(x-1,y+1),c2=getpixel(x-1,y),c3=getpixel(x,y+1);
    if(boundry_col!=cur_col){if(c1!=boundry_col&&c2!=boundry_col&&c3!=boundry_col){if(cur_col!=fill_col){putpixel(x,y,fill_col);}FFLD(x-i,y+j,i,j);}}
    else return;
}
void FFManger(int xm,int ym,int i, int j)
{
    ox=xm;oy=ym;
    if(i==1) ym++;else xm--;
    FFLD(xm,ym,i,j);
    while(getpixel(xm,ym)!=boundry_col){if(i==1) ym++;else xm--;FFLD(xm,ym,i,j);}
    xm=ox;ym=oy+1;
    while(getpixel(xm,ym)!=boundry_col){if(i==1) ym--;else xm--;FFLU(xm,ym,i,j);}
    xm=ox+1;ym=oy-1;
    while(getpixel(xm,ym)!=boundry_col){if(i==1) ym++;else xm++;FFRD(xm,ym,i,j);}
    xm=ox+1;ym=oy;
    while(getpixel(xm,ym)!=boundry_col){if(i==1) ym--;else xm++;FFRU(xm,ym,i,j);}
}
int main()
{
int ch1,ch2,rd,stang,endang;
initwindow(500,500);
while(true){
    printf("Press\n1 - Point\n2 - Line\n3 - Rectangle\n4 - Circle\n5 - Ellipse\n6 - Arc\n7 - Polygon\n");
    scanf("%d",&ch1);
    if(ch1==1)
        np=1;
    else if(ch1==2||ch1==3||ch1==4||ch1==6)
        np=2;
    else if(ch1==5)
        np=3;
    else
    {
        printf("Enter no. of Points -> ");
        scanf("%d",&np);
    }
    float in_mat[np][3];
    if(ch1==4||ch1==6)
    {
        printf("Enter Center co-ordinates\n");
        scanf("%f",&in_mat[0][0]);
        scanf("%f",&in_mat[0][1]);
        printf("Enter Radius -> ");
        scanf("%d",&rd);
        if(ch1==6)
        {
            printf("Enter Start angle -> ");
            scanf("%d",&stang);
            printf("Enter End angle -> ");
            scanf("%d",&endang);
        }
        in_mat[1][0]=in_mat[0][0]+rd;
        in_mat[1][1]=in_mat[0][1];
    }
    else if(ch1==5)
    {
        int xrd,yrd;
        printf("Enter Center co-ordinates\n");
        scanf("%f",&in_mat[0][0]);
        scanf("%f",&in_mat[0][1]);
        printf("Enter X-axis Radius -> ");
        scanf("%d",&xrd);
        printf("Enter Y-axis Radius -> ");
        scanf("%d",&yrd);
        printf("Enter Start angle -> ");
        scanf("%d",&stang);
        printf("Enter End angle -> ");
        scanf("%d",&endang);
        in_mat[1][0]=in_mat[0][0]+xrd;
        in_mat[1][1]=in_mat[0][1];
        in_mat[2][0]=in_mat[0][0];
        in_mat[2][1]=in_mat[0][1]+yrd;
    }
    else
    {
        printf("Enter points\n");
        for(int i=0;i<np;i++)
        {
           for(int j=0;j<3;j++)
            {
                if(j==2)
                    in_mat[i][j]=1;
                else
                    scanf("%f",&in_mat[i][j]);
            }
        }
    }
    printf("Press\n1 - Rotation\n2 - Scaling\n3 - Transition\n4 - Reflection\n5 - Floodfill\n6 - Custom Transformation\n");
    scanf("%d",&ch2);

    if(ch2==1)
    {
        printf("Enter Degree of rotation(with sign) -> ");
        int xr,yr;
        double theta;
        scanf("%lf",&theta);
        printf("Enter a point about rotation\nx -> ");
        scanf("%d",&xr);
        printf("y -> ");
        scanf("%d",&yr);
        Rotate(xr,yr,theta,&in_mat[0][0]);

    }
    else if(ch2==2)
    {
        printf("Enter scaling factor -> ");
        float sc;
        scanf("%f",&sc);
        Scale(sc,&in_mat[0][0]);
    }
    else if(ch2==3)
    {
        int x,y;
        printf("Enter Transition factors.In X-axis -> ");
        scanf("%d",&x);
        printf("In Y-axis -> ");
        scanf("%d",&y);
        Transition(x,y,&in_mat[0][0]);
    }
    else if(ch2==4)
    {
        int x1,y1,x2,y2;
        printf("Enter two points of line reflection about\n");
        scanf("%d",&x1);scanf("%d",&y1);
        scanf("%d",&x2);scanf("%d",&y2);
        float theta=90*(3.14/180);
        if(x1!=x2)
                theta=atan((y2-y1)/(x2-x1))*(180/3.14);
        Reflect(x1,y1,x2,y2,theta,&in_mat[0][0]);
    }
    else if(ch2==6)
    {
        printf("Enter 3X3 Transformation matrix row wise\n");
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                scanf("%f",&trans[i][j]);
        Transformation(&in_mat[0][0],np,3,&trans[0][0],3,3);
        copy_matrix(np,3);
    }

    if(ch1==1)
    {
        putpixel(in_mat[0][0],in_mat[0][1],1);
        putpixel(tempmat[0][0],tempmat[0][1],4);
    }
    else if(ch1==2)
    {
        setcolor(1);
        line(in_mat[0][0],in_mat[0][1],in_mat[1][0],in_mat[1][1]);
        setcolor(4);
        line(tempmat[0][0],tempmat[0][1],tempmat[1][0],tempmat[1][1]);
    }
    else if(ch1==3)
    {
        setcolor(1);
        rectangle(in_mat[0][0],in_mat[0][1],in_mat[1][0],in_mat[1][1]);
        setcolor(4);
        rectangle(tempmat[0][0],tempmat[0][1],tempmat[1][0],tempmat[1][1]);
    }
    else if(ch1==4)
    {
        setcolor(1);
        circle(in_mat[0][0],in_mat[0][1],rd);
        setcolor(4);
        int mod_rd=rd;
        if(ch2==2)
            mod_rd=tempmat[1][0]-tempmat[0][0];
        circle(tempmat[0][0],tempmat[0][1],mod_rd);
    }
    else if(ch1==5)
    {
        setcolor(1);
        ellipse(in_mat[0][0],in_mat[0][1],stang,endang,in_mat[1][0]-in_mat[0][0],in_mat[2][1]-in_mat[0][1]);
        setcolor(4);
        ellipse(tempmat[0][0],tempmat[0][1],stang,endang,tempmat[1][0]-tempmat[0][0],tempmat[2][1]-tempmat[0][1]);
    }
    else if(ch1==6)
    {
        setcolor(1);
        arc(in_mat[0][0],in_mat[0][1],stang,endang,rd);
        setcolor(4);
        int mod_rd=rd;
        if(ch2==2)
            mod_rd=tempmat[1][0]-tempmat[0][0];
        arc(tempmat[0][0],tempmat[0][1],stang,endang,mod_rd);
    }
    else if(ch1==7)
    {
        int arr[np*2];
        int c=0;
        for(int i=0;i<np;i++)
            for(int j=0;j<2;j++)
                arr[c++]=in_mat[i][j];
        setcolor(1);
        drawpoly(np,arr);
        c=0;
        for(int i=0;i<np;i++)
            for(int j=0;j<2;j++)
                arr[c++]=tempmat[i][j];
        setcolor(4);
        drawpoly(np,arr);
    }
     if(ch2==5)
    {
        int xe,ye;
        printf("enter X co-ordinate inside shape -> ");
        scanf("%d",&xe);
        printf("Enter Y co-ordinate inside shape ->");
        scanf("%d",&ye);
        printf("Enter boundry color-> ");
        scanf("%d",&boundry_col);
        printf("Enter fill color-> ");
        scanf("%d",&fill_col);
        FFManger(xe,ye,1,0);
        FFManger(xe,ye,0,1);
    }
}
    getch();
}

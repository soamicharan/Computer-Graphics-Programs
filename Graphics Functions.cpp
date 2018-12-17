#include<graphics.h>
#include<stdio.h>
#include<math.h>
#include<conio.h>
float bufmat[20][3];
float tempmat[20][3];
float trans[][3]={{1,0,0},{0,1,0},{0,0,1}};
int np,cc=15;
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
void trans_manager(int p[],int rot,int sca,int tra,int refl,int man)
{
    float in_mat[np][3];
    int c=0;
    for(int i=0;i<np;i++)
        {
           for(int j=0;j<3;j++)
            {
                if(j==2)
                    in_mat[i][j]=1;
                else
                    in_mat[i][j]=p[c++];
            }
        }
    if(rot==1)
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
        for(int i=0;i<np;i++)
            for(int j=0;j<3;j++)
                in_mat[i][j]=tempmat[i][j];

    }
    if(sca==1)
    {
        printf("Enter scaling factor -> ");
        float sc;
        scanf("%f",&sc);
        Scale(sc,&in_mat[0][0]);
        for(int i=0;i<np;i++)
            for(int j=0;j<3;j++)
                in_mat[i][j]=tempmat[i][j];
    }
    if(tra==1)
    {
        int x,y;
        printf("Enter Transition factors.In X-axis -> ");
        scanf("%d",&x);
        printf("In Y-axis -> ");
        scanf("%d",&y);
        Transition(x,y,&in_mat[0][0]);
        for(int i=0;i<np;i++)
            for(int j=0;j<3;j++)
                in_mat[i][j]=tempmat[i][j];
    }
    if(refl==1)
    {
        int x1,y1,x2,y2;
        printf("Enter two points of line reflection about\n");
        scanf("%d",&x1);scanf("%d",&y1);
        scanf("%d",&x2);scanf("%d",&y2);
        float theta=90*(3.14/180);
        if(x1!=x2)
                theta=atan((y2-y1)/(x2-x1))*(180/3.14);
        Reflect(x1,y1,x2,y2,theta,&in_mat[0][0]);
        for(int i=0;i<np;i++)
            for(int j=0;j<3;j++)
                in_mat[i][j]=tempmat[i][j];
    }
    else if(man==1)
    {
        printf("Enter 3X3 Transformation matrix row wise\n");
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                scanf("%f",&trans[i][j]);
        Transformation(&in_mat[0][0],np,3,&trans[0][0],3,3);
        copy_matrix(np,3);
        for(int i=0;i<np;i++)
            for(int j=0;j<3;j++)
                in_mat[i][j]=tempmat[i][j];
    }

}
int main()
{
    int gd = DETECT, gm;
    printf("Press\n1  -> Create new graph\n2  -> Set fill style\n3  -> Set color\n4  -> Line\n5  -> Circle\n6  -> Rectangle\n");
    printf("7  -> Ellipse\n8  -> Polygon\n9  -> Arc\n10 -> Sector\n11 -> Print a Text\n12 -> Get Pixel Color\n13 -> Get Co-ordinates\n");
    printf("14 -> Put a Pixel\n15 -> Flood Fill\n16 -> Print Color Numbers\n17-> Transformation\n");
    int choice;
    while(true)
    {
        int is_trans=0,rot=0,sca=0,tra=0,refl=0,man=0;
        scanf("%d",&choice);
        if(choice==17)
        {
            printf("press 1 for yes or 0 for no.\n");
            is_trans=1;
            printf("Rotation ? -> ");scanf("%d",&rot);
            printf("Scaling ? -> ");scanf("%d",&sca);
            printf("Translation ? -> ");scanf("%d",&tra);
            printf("Reflection ? -> ");scanf("%d",&refl);
            printf("Custom Transformation ? -> ");scanf("%d",&man);
            printf("Choose a shape to continue\n");
            scanf("%d",&choice);
        }
        if(choice==1)
        {
            int w,h;
            printf("Enter size of graph.\nWidth -> ");
            scanf("%d",&w);
            printf("Height -> ");scanf("%d",&h);
            initwindow(w,h);
        }
        else if(choice==2)
        {
            printf("Choose Style\n1 -> EMPTY_FILL\n2 -> SOLID_FILL\n3 -> LINE_FILL\n4 -> LTSLASH_FILL\n");
            printf("5 -> SLASH_FILL\n6 -> BKSLASH_FILL\n7 -> LTBKSLASH_FILL\n8 -> HATCH_FILL\n9 -> XHATCH_FILL\n");
            printf("10 -> INTERLEAVE_FILL\n11 -> WIDE_DOT_FILL\n12 -> CLOSE_DOT_FILL\n13 -> USER_FILL\n");
            int c;
            scanf("%d",&c);
            int col;
            printf("Enter Color No.\n");
            scanf("%d",&col);
            switch(c)
            {
                case 1:{setfillstyle(EMPTY_FILL,col);break;}
                case 2:{setfillstyle(SOLID_FILL,col);break;}
                case 3:{setfillstyle(LINE_FILL,col);break;}
                case 4:{setfillstyle(LTSLASH_FILL,col);break;}
                case 5:{setfillstyle(SLASH_FILL,col);break;}
                case 6:{setfillstyle(BKSLASH_FILL,col);break;}
                case 7:{setfillstyle(LTBKSLASH_FILL,col);break;}
                case 8:{setfillstyle(HATCH_FILL,col);break;}
                case 9:{setfillstyle(XHATCH_FILL,col);break;}
                case 10:{setfillstyle(INTERLEAVE_FILL,col);break;}
                case 11:{setfillstyle(WIDE_DOT_FILL,col);break;}
                case 12:{setfillstyle(CLOSE_DOT_FILL,col);break;}
                case 13:{setfillstyle(USER_FILL,col);break;}
                default:{printf("Wrong Choice");break;}
            }
        }
        else if(choice==3)
        {
            printf("Enter Color No. -> ");
            int col;
            scanf("%d",&col);
            setcolor(col);
            cc=col;
        }
        else if(choice==4)
        {
            int x1,y1,x2,y2;
            /*printf("Enter Start Point Co-ordinates.\nx -> ");scanf("%d",&x1);
            printf("y -> ");scanf("%d",&y1);
            printf("Enter End Point Co-ordinates.\nx ->");scanf("%d",&x2);
            printf("y -> ");scanf("%d",&y2);*/
            printf("Click at end points\n");
            while(!ismouseclick(WM_LBUTTONDOWN)){}
            getmouseclick(WM_LBUTTONDOWN,x1,y1);
            while(!ismouseclick(WM_LBUTTONDOWN)){}
            getmouseclick(WM_LBUTTONDOWN,x2,y2);
            line(x1,y1,x2,y2);
            if(is_trans==1)
            {
                int p[]={x1,y1,x2,y2};
                np=2;
                trans_manager(p,rot,sca,tra,refl,man);
                setcolor(4);
                line(tempmat[0][0],tempmat[0][1],tempmat[1][0],tempmat[1][1]);
                setcolor(cc);
            }
        }
        else if(choice==5)
        {
            int x,y,rad,x1,y1;
            /*printf("Enter Co-ordinates of center of circle.\nx -> ");
            scanf("%d",&x);
            printf("y -> ");scanf("%d",&y);
            printf("Enter Radius.\n");scanf("%d",&rad);*/
            printf("Click for Center of circle\n");
            while(!ismouseclick(WM_LBUTTONDOWN)){}
            getmouseclick(WM_LBUTTONDOWN,x,y);

            printf("Click for radius of circle\n");
            while(!ismouseclick(WM_LBUTTONDOWN)){}
            getmouseclick(WM_LBUTTONDOWN,x1,y1);

            rad=sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
            circle(x,y,(int)rad);
            if(is_trans==1)
            {
                int p[]={x,y,x1,y1};
                np=2;
                trans_manager(p,rot,sca,tra,refl,man);
                setcolor(4);
            int mod_rd=rad;
            if(sca==1)
                mod_rd=tempmat[1][0]-tempmat[0][0];
            circle(tempmat[0][0],tempmat[0][1],mod_rd);
            setcolor(cc);
            }
        }
        else if(choice==6)
        {
            int x1,y1,x2,y2;
            /*printf("Enter Left Top Co-ordinates.\nx -> ");scanf("%d",&x1);
            printf("y -> ");scanf("%d",&y1);
            printf("Enter Right Bottom Co-ordinates.\nx ->");scanf("%d",&x2);
            printf("y -> ");scanf("%d",&y2);*/
            printf("Click for Left top Corner\n");
            while(!ismouseclick(WM_LBUTTONDOWN)){}
            getmouseclick(WM_LBUTTONDOWN,x1,y1);

            printf("Click for Right Bottom corner\n");
            while(!ismouseclick(WM_LBUTTONDOWN)){}
            getmouseclick(WM_LBUTTONDOWN,x2,y2);
            rectangle(x1,y1,x2,y2);
            if(is_trans==1)
            {
                int p[]={x1,y1,x2,y2};
                np=2;
                trans_manager(p,rot,sca,tra,refl,man);
                setcolor(4);
                rectangle(tempmat[0][0],tempmat[0][1],tempmat[1][0],tempmat[1][1]);
                setcolor(cc);
            }
        }
        else if(choice==7)
        {
            int x,y,st,en,xrad,yrad,x1,y1,x2,y2;
            printf("Click for Center of ellipse\n");
            while(!ismouseclick(WM_LBUTTONDOWN)){}
            getmouseclick(WM_LBUTTONDOWN,x,y);

            printf("Click for X-Axis radius of ellipse\n");
            while(!ismouseclick(WM_LBUTTONDOWN)){}
            getmouseclick(WM_LBUTTONDOWN,x1,y1);
            printf("Click for Y-Axis radius of ellipse\n");
            while(!ismouseclick(WM_LBUTTONDOWN)){}
            getmouseclick(WM_LBUTTONDOWN,x2,y2);
            /*printf("Enter Center Co-ordinates\nx -> ");scanf("%d",&x);
            printf("y -> ");scanf("%d",&y);*/
            printf("Enter start angle of ellipse -> ");scanf("%d",&st);
            printf("Enter end angle of ellipse -> ");scanf("%d",&en);
            /*printf("Enter X-Axis radius -> ");scanf("%d",&xrad);
            printf("Enter Y-Axis radius -> ");scanf("%d",&yrad);*/
            xrad=sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
            yrad=sqrt((x-x2)*(x-x2)+(y-y2)*(y-y2));
            ellipse(x,y,st,en,xrad,yrad);
            if(is_trans==1)
            {
                int p[]={x,y,x+xrad,y,x,y+yrad};
                np=3;
                trans_manager(p,rot,sca,tra,refl,man);
                setcolor(4);
                ellipse(tempmat[0][0],tempmat[0][1],st,en,tempmat[1][0]-tempmat[0][0],tempmat[2][1]-tempmat[0][1]);
                setcolor(cc);
            }
        }
        else if(choice==8)
        {
            int n;
            printf("Enter No. of points -> ");scanf("%d",&n);
            int points[2*n];
            printf("Click Points\n");
            int coun=0;
            for(int i=0;i<2*n;i+=2)
            {
                coun++;
                /*printf("x%d ->",(coun));scanf("%d",&points[i]);
                printf("y%d ->",(coun));scanf("%d",&points[i+1]);*/
                while(!ismouseclick(WM_LBUTTONDOWN)){}
                getmouseclick(WM_LBUTTONDOWN,points[i],points[i+1]);
            }
            printf("1 -> Hollow Polygon\n2 -> Filled Polygon\n");
            int c;scanf("%d",&c);
            if(c==1)
                drawpoly(n,points);
            else if(c==2)
                fillpoly(n,points);
            if(is_trans==1)
            {
                np=n;
                trans_manager(points,rot,sca,tra,refl,man);
                int arr[np*2];
                int c=0;
                for(int i=0;i<np;i++)
                    for(int j=0;j<2;j++)
                        arr[c++]=tempmat[i][j];
                setcolor(4);
                drawpoly(np,arr);
                setcolor(cc);
            }
        }
        else if(choice==9)
        {
            int x,y,st,en,rad,x1,y1;
            /*printf("Enter Center Co-ordinates\nx -> ");scanf("%d",&x);
            printf("y -> ");scanf("%d",&y);*/
            printf("Click for center of arc\n");
            while(!ismouseclick(WM_LBUTTONDOWN)){}
            getmouseclick(WM_LBUTTONDOWN,x,y);
            printf("Click for radius of arc\n");
            while(!ismouseclick(WM_LBUTTONDOWN)){}
            getmouseclick(WM_LBUTTONDOWN,x1,y1);
            printf("Enter start angle of arc -> ");scanf("%d",&st);
            printf("Enter end angle of arc -> ");scanf("%d",&en);
            rad=sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
            arc(x,y,st,en,rad);
            if(is_trans==1)
            {
                int p[]={x,y,x1,y1};
                np=2;
                trans_manager(p,rot,sca,tra,refl,man);
                setcolor(4);
                int mod_rd=rad;
                if(sca==1)
                    mod_rd=tempmat[1][0]-tempmat[0][0];
                arc(tempmat[0][0],tempmat[0][1],st,en,mod_rd);
                setcolor(cc);
            }
        }
        else if(choice==10)
        {
            int x,y,st,en,xrad,yrad,x1,y1,x2,y2;
            printf("Click for center of sector\n");
            while(!ismouseclick(WM_LBUTTONDOWN)){}
            getmouseclick(WM_LBUTTONDOWN,x,y);
            printf("Click for X-Axis radius of arc\n");
            while(!ismouseclick(WM_LBUTTONDOWN)){}
            getmouseclick(WM_LBUTTONDOWN,x1,y1);
            printf("Click for Y-Axis radius of arc\n");
            while(!ismouseclick(WM_LBUTTONDOWN)){}
            getmouseclick(WM_LBUTTONDOWN,x2,y2);
            /*printf("Enter Center Co-ordinates\nx -> ");scanf("%d",&x);
            printf("y -> ");scanf("%d",&y);*/
            printf("Enter start angle of sector -> ");scanf("%d",&st);
            printf("Enter end angle of sector -> ");scanf("%d",&en);
            /*printf("Enter X-Axis radius -> ");scanf("%d",&xrad);
            printf("Enter Y-Axis radius -> ");scanf("%d",&yrad);*/
            xrad=sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
            yrad=sqrt((x-x2)*(x-x2)+(y-y2)*(y-y2));
            sector(x,y,st,en,xrad,yrad);
            if(is_trans==1)
            {
                int p[]={x,y,x+xrad,y,x,y+yrad};
                np=3;
                trans_manager(p,rot,sca,tra,refl,man);
                setcolor(4);
                ellipse(tempmat[0][0],tempmat[0][1],st,en,tempmat[1][0]-tempmat[0][0],tempmat[2][1]-tempmat[0][1]);
                setcolor(cc);
            }
        }
        else if(choice==11)
        {
            char text[50];
            printf("Enter Text to print -> ");scanf("%s",&text);
            int x,y;
            printf("Click a point for print text\n");
            while(!ismouseclick(WM_LBUTTONDOWN)){}
            getmouseclick(WM_LBUTTONDOWN,x,y);
            outtextxy(x,y,text);
        }
        else if(choice==12)
        {
            int x,y;
            printf("Click a point to get pixel color\n");
            while(!ismouseclick(WM_LBUTTONDOWN)){}
            getmouseclick(WM_LBUTTONDOWN,x,y);
            printf("Color at (%d,%d) = %d\n",x,y,getpixel(x,y));
        }
        else if(choice==13)
        {
            printf("Current position of Co-ordinates = (%d,%d)\n",getx(),gety());
        }
        else if(choice==14)
        {
            int x,y,col;
            printf("Click a point to put a pixel\n");
            while(!ismouseclick(WM_LBUTTONDOWN)){}
            getmouseclick(WM_LBUTTONDOWN,x,y);
            printf("Enter Pixel Color No. -> ");scanf("%d",&col);
            putpixel(x,y,col);
        }
        else if(choice==15)
        {
            int x,y,col;
            printf("Click a point inside a shape\n");
            while(!ismouseclick(WM_LBUTTONDOWN)){}
            getmouseclick(WM_LBUTTONDOWN,x,y);
            printf("Enter Boundry Color No. -> ");scanf("%d",&col);
            floodfill(x,y,col);
        }
        else if(choice==16)
        {
            printf("0 - BLACK\n1 - BLUE\n2 - GREEN\n3 - CYAN\n");
            printf("4 - RED\n5 - MAGENTA\n6 - BROWN\n7 - LIGHTGRAY\n");
            printf("8 - DARKGRAY\n9 - LIGHTBLUE\n10 - LIGHTGREEN\n");
            printf("11 - LIGHTCYAN\n12 - LIGHTRED\n13 - LIGHTMAGENTA\n14 - YELLOW\n15 - WHITE\n");
        }
    }
}

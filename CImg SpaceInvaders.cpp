#include <iostream>
#define _fileno(F) ((F)->_file)
#include <ctime>
#include <vector>
#include "CImg.h"
#include <string>
#include <cmath>
using namespace std;
using namespace cimg_library;

int X0=950;
int Y0=1800;
int speed_alien=1;
float speed_spaceship=10.5;
int delay_shot=300;
int speed_bonus=3;
int bshot=0;
int score=0;
double valiens_shot=10;
int speed_shot=15;
int vie=1;
int gd=0;
int l=0;

struct bonus
{
    int x,y;
};
struct alien
{
    int x,y;
};


struct shot
{
    int x,y;

};
struct etoile
{
    int x,y;
};
struct double_shot
{
    double x,y,vx,vy;
};
vector<alien> aliens;
vector<shot> shots;
vector<double_shot> aliens_shot;
vector<etoile> stars;
vector<bonus> bonus_spaceship;
vector<bonus> bonus_shot;

int dif=3;
int main()
{
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<dif; j++)
        {
            alien a;
            a.x=110+180*i;
            a.y=20+180*j;
            aliens.push_back(a);
        }
    }
    for(int f=0; f<=50; f++)
    {
        etoile e;
        e.x=rand()%2000;
        e.y=rand()%2000;
        stars.push_back(e);
    }

    CImg <unsigned char> game(2000,2000,1,3,0);
    unsigned char orange[3] {255,127,0};
    unsigned char green[3] {0,255,0};
    unsigned char red[3] {255,0,0};
    unsigned char white[3] {255,255,255};
    unsigned char black[3] {0,0,0};
    unsigned char blue[3] {69,111,255};
    CImgDisplay disp(game,"Space Invaders");
    CImg<unsigned char> arc;
    arc=game;
    while(not disp.is_key())
    {
        disp.wait(5);
        game.draw_rectangle(200,700,350,720,white);
        game.draw_rectangle(200,700,210,900,white);
        game.draw_rectangle(350,700,340,900,white);
        game.draw_rectangle(200,900,350,920,white);

        game.draw_rectangle(450,700,600,720,white);
        game.draw_rectangle(450,700,460,900,white);
        game.draw_rectangle(600,700,590,900,white);
        game.draw_rectangle(450,900,600,920,white);

        game.draw_triangle(330,730,330,880,230,800,white);
        game.draw_triangle(470,730,470,880,580,800,white);
        game.draw_text(1000,750,("MOVE SPACESHIP"),white,black,1,100);
        game.draw_text(100,200,("SPACE INVADERS"),green,black,1,200);
        game.draw_circle(270,600,30,blue);
        game.draw_circle(530,600,30,red);
        game.draw_text(262,582,("F"),white,blue,1,40);
        game.draw_text(520,582,("S"),white,red,1,40);
        game.draw_text(1000,570,("BONUSES (FIRE/SPEED)"),white,black,1,100);
        game.draw_rectangle(200,1000,600,1020,white);
        game.draw_rectangle(200,1000,210,1175,white);
        game.draw_rectangle(600,1000,610,1175,white);
        game.draw_rectangle(200,1175,610,1195,white);
        game.draw_text(280,1050,("SPACE"),white,black,1,100);
        game.draw_text(1000,1050,("SHOOT"),white,black,1,100);
        game.draw_text(400,1500,("PRESS ANY KEY TO START"),red,black,1,100);
        game.draw_text(1200,1800,("Axel PATRON"),blue,black,1,50);
        game.display(disp);
    }

    while(not disp.is_closed())
    {
        disp.wait(2);


        if (disp.is_keyARROWLEFT())
            if (X0>0)
                X0-=speed_spaceship;
        if(disp.is_keyARROWRIGHT())
            if (X0<1900)
                X0+=speed_spaceship;
        if(disp.is_keySPACE())
        {
            if(bshot==0)
            {
                shot t;
                t.x=X0+50;
                t.y=Y0-100;
                if (shots.size()>=1)
                {
                    if (shots[shots.size()-1].y<Y0-delay_shot)
                        shots.push_back(t);
                }
                else
                    shots.push_back(t);
            }
            if (bshot==1)
            {
                shot t1,t2;
                t1.x=X0+20;
                t1.y=Y0-100;
                t2.x=X0+80;
                t2.y=Y0-100;
                if (shots.size()>=1)
                {
                    if (shots[shots.size()-1].y<Y0-delay_shot)
                    {
                        shots.push_back(t1);
                        shots.push_back(t2);
                    }
                }
                else
                {
                    shots.push_back(t1);
                    shots.push_back(t2);
                }

            }
            if (bshot==2)
            {
                shot t1,t2,t3;
                t1.x=X0+10;
                t1.y=Y0-100;
                t2.x=X0+50;
                t2.y=Y0-100;
                t3.x=X0+90;
                t3.y=Y0-100;

                if (shots.size()>=1)
                {
                    if (shots[shots.size()-1].y<Y0-delay_shot)
                    {
                        shots.push_back(t1);
                        shots.push_back(t2);
                        shots.push_back(t3);
                    }
                }
                else
                {
                    shots.push_back(t1);
                    shots.push_back(t2);
                    shots.push_back(t3);
                }

            }
        }
        for(alien& a : aliens)
        {
            int test=rand()%5000;
            if(test==0)
            {
                double_shot t;
                t.x=a.x+45;
                t.y=a.y+115;
                t.vx=((-25)+(rand()%50))/(25/sqrt(50));
                t.vy=sqrt(valiens_shot*valiens_shot-t.vx*t.vx);
                aliens_shot.push_back(t);
            }

        }

        for(int t=0; t<shots.size(); t++)
        {
            shots[t].y-=speed_shot;
            if(shots[t].y<-200)
                shots.erase(shots.begin()+t);
        }

        for(int t=0; t<aliens_shot.size(); t++)
        {
            if(aliens_shot[t].y>2200)
                aliens_shot.erase(aliens_shot.begin()+t);
        }
        l++;
        if(l==80)
        {
            if(gd==0)
            {
                gd=1;
                l=0;
            }
            else
            {
                gd=0;
                l=0;
            }

        }
        if(vie!=0)
        {
            for (alien& a : aliens)
            {
                a.y+=speed_alien;
                if(gd==0)
                    a.x+=1;
                if(gd==1)
                    a.x-=1;
            }
        }

        for (bonus& b : bonus_spaceship)
            b.y+=speed_bonus;

        for (bonus& b : bonus_shot)
            b.y+=speed_bonus;

        for(double_shot& t : aliens_shot)
        {
            t.x+=t.vx;
            t.y+=t.vy;
            if(t.x<0 or t.x>2000)
                t.vx=-t.vx;

        }

        game=arc;
        game.draw_rectangle(X0,Y0,X0+100,Y0-10,white);
        game.draw_rectangle(X0+15,Y0-10,X0+85,Y0-20,white);
        game.draw_rectangle(X0+45,Y0-120,X0+55,Y0+20,white);
        game.draw_rectangle(X0+30,Y0,X0+70,Y0+10,white);
        game.draw_rectangle(X0,Y0,X0+5,Y0-35,white);
        game.draw_rectangle(X0+100,Y0,X0+95,Y0-35,white);
        game.draw_rectangle(X0,Y0-35,X0+5,Y0-60,red);
        game.draw_rectangle(X0+100,Y0-35,X0+95,Y0-60,red);
        game.draw_rectangle(X0+40,Y0,X0+60,Y0-100,white);
        game.draw_rectangle(X0+20,Y0-10,X0+80,Y0-40,white);
        game.draw_rectangle(X0+30,Y0-40,X0+70,Y0-80,white);
        game.draw_rectangle(X0+20,Y0-10,X0+25,Y0-65,white);
        game.draw_rectangle(X0+80,Y0-10,X0+75,Y0-65,white);
        game.draw_rectangle(X0+20,Y0-65,X0+25,Y0-90,red);
        game.draw_rectangle(X0+80,Y0-65,X0+75,Y0-90,red);
        game.draw_rectangle(X0+20,Y0-20,X0+25,Y0-30,blue);
        game.draw_rectangle(X0+25,Y0-30,X0+30,Y0-40,blue);
        game.draw_rectangle(X0+80,Y0-20,X0+75,Y0-30,blue);
        game.draw_rectangle(X0+75,Y0-30,X0+70,Y0-40,blue);
        game.draw_rectangle(X0+42,Y0-20,X0+47,Y0-40,red);
        game.draw_rectangle(X0+47,Y0-30,X0+53,Y0-50,red);
        game.draw_rectangle(X0+53,Y0-20,X0+58,Y0-40,red);





        for(int bt=0; bt<bonus_shot.size(); bt++)
            if(bonus_shot[bt].x+20>X0 && bonus_shot[bt].x-20<X0+100 && bonus_shot[bt].y+20>Y0-120 && bonus_shot[bt].y-20<Y0)
            {
                bshot++;
                bonus_shot.erase(bonus_shot.begin()+bt);
            }

        for(int bt=0; bt<bonus_spaceship.size(); bt++)
            if(bonus_spaceship[bt].x+20>X0 && bonus_spaceship[bt].x-20<X0+100 && bonus_spaceship[bt].y+20>Y0-120 && bonus_spaceship[bt].y-20<Y0)
            {
                speed_spaceship+=5;
                bonus_spaceship.erase(bonus_spaceship.begin()+bt);
            }
        for(etoile& e : stars)
        {
            game.draw_circle(e.x,e.y,3,white);
            e.y+=speed_alien;
            if(e.y>2000)
                e.y-=2020;
        }
        if(dif==9)
        {
            game.draw_text(800,200,("YOU WON"),white,black,1,100);
            game.draw_text(750,400,("PRESS R TO RESTART"),red,black,1,100);
            speed_alien=0;
            speed_spaceship=0;
            delay_shot=3000000;
        }
        if (dif==3)
            game.draw_text(0,0,("LEVEL 1"),white,black,1,50);
        if (dif==4)
            game.draw_text(0,0,("LEVEL 2"),white,black,1,50);
        if (dif==5)
            game.draw_text(0,0,("LEVEL 3"),white,black,1,50);
        if (dif==6)
            game.draw_text(0,0,("LEVEL 4"),white,black,1,50);
        if (dif==7)
            game.draw_text(0,0,("LEVEL 5"),white,black,1,50);
        if (dif==8)
            game.draw_text(0,0,("LEVEL 6"),white,black,1,50);
        game.draw_text(1920,0,to_string(score).c_str(),white,black,1,50);
        game.draw_text(1775,0,("SCORE:"),white,black,1,50);
        for (bonus& b : bonus_shot)
        {
            b.y+=speed_bonus;
            game.draw_circle(b.x,b.y,20,blue);
            game.draw_text(b.x-7,b.y-10,("F"),white,blue,1,25);
        }
        for (bonus& b : bonus_spaceship)
        {
            b.y+=speed_bonus;
            game.draw_circle(b.x,b.y,20,red);
            game.draw_text(b.x-7,b.y-10,("S"),white,red,1,25);
        }
        if(dif<9)
        {
            for(alien& a : aliens)
            {
                game.draw_rectangle(a.x,a.y,a.x+90,a.y+90,green);
                game.draw_rectangle(a.x,a.y+90,a.x+10,a.y+120,green);
                game.draw_rectangle(a.x+20,a.y+90,a.x+30,a.y+120,green);
                game.draw_rectangle(a.x+40,a.y+60,a.x+50,a.y+120,green);
                game.draw_rectangle(a.x+60,a.y+60,a.x+70,a.y+120,green);
                game.draw_rectangle(a.x+80,a.y+60,a.x+90,a.y+120,green);
                game.draw_circle(a.x+30,a.y+35,8,black);
                game.draw_circle(a.x+60,a.y+35,8,black);
                game.draw_rectangle(a.x+20,a.y+70,a.x+30,a.y+80,black);
                game.draw_rectangle(a.x+30,a.y+70,a.x+60,a.y+60,black);
                game.draw_rectangle(a.x+60,a.y+70,a.x+70,a.y+80,black);
                if(a.y+120>Y0-120)
                {
                    vie=0;
                }
            }
            for(int t=0; t<shots.size(); t++)
                for(int a=0; a<aliens.size(); a++)
                    if(shots[t].x-5>aliens[a].x && shots[t].x-5<aliens[a].x+90 && shots[t].y-50>aliens[a].y && shots[t].y-50 <aliens[a].y+90 || shots[t].x+5>aliens[a].x && shots[t].x+5<aliens[a].x+90 && shots[t].y-50>aliens[a].y && shots[t].y-50 <aliens[a].y+90)
                    {

                            game.draw_rectangle(aliens[a].x,aliens[a].y,aliens[a].x+90,aliens[a].y+90,red);
                            game.draw_rectangle(aliens[a].x,aliens[a].y+90,aliens[a].x+10,aliens[a].y+120,red);
                            game.draw_rectangle(aliens[a].x+20,aliens[a].y+90,aliens[a].x+30,aliens[a].y+120,red);
                            game.draw_rectangle(aliens[a].x+40,aliens[a].y+60,aliens[a].x+50,aliens[a].y+120,red);
                            game.draw_rectangle(aliens[a].x+60,aliens[a].y+60,aliens[a].x+70,aliens[a].y+120,red);
                            game.draw_rectangle(aliens[a].x+80,aliens[a].y+60,aliens[a].x+90,aliens[a].y+120,red);
                            game.draw_circle(aliens[a].x+30,aliens[a].y+35,8,black);
                            game.draw_circle(aliens[a].x+60,aliens[a].y+35,8,black);
                            game.draw_rectangle(aliens[a].x+20,aliens[a].y+70,aliens[a].x+30,aliens[a].y+80,black);
                            game.draw_rectangle(aliens[a].x+30,aliens[a].y+70,aliens[a].x+60,aliens[a].y+60,black);
                            game.draw_rectangle(aliens[a].x+60,aliens[a].y+70,aliens[a].x+70,aliens[a].y+80,black);

                        aliens.erase(aliens.begin()+a);
                        shots.erase(shots.begin()+t);
                        score++;
                    }

            for(double_shot& t :aliens_shot)
            {
                if(t.x>X0 && t.x<X0+120 && t.y>Y0-90 && t.y<Y0)
                    vie=0;
            }
            if(vie==0)
            {
                aliens_shot.clear();
                game.draw_text(750,200,("YOU LOSE"),white,black,1,100);
                game.draw_text(750,400,("PRESS R TO RESTART"),red,black,1,100);
                speed_alien=0;
                speed_spaceship=0;
                delay_shot=100000;
            }

        }

        for(double_shot& t : aliens_shot)
        {
            game.draw_circle(t.x,t.y,8,red);
        }

        for(shot& t : shots)
        {
            game.draw_rectangle(t.x-5,t.y,t.x+5,t.y-50,white);
            game.draw_triangle(t.x-5,t.y-50,t.x,t.y-55,t.x+5,t.y-50,white);
        }
        if (aliens.size()==0)
        {
            shots.clear();
            dif=dif+1;
            if (dif==5 || dif==7)
            {
                bonus b;
                b.x=15+rand()%1970;
                b.y=0-rand()%2000;
                bonus_shot.push_back(b);
            }

            if (dif==4 || dif==6)
            {
                bonus b;
                b.x=15+rand()%1970;
                b.y=0-rand()%2000;
                bonus_spaceship.push_back(b);
            }

            for(int i=0; i<10; i++)
            {
                for(int j=0; j<dif; j++)
                {
                    alien a;
                    a.x=110+180*i;
                    a.y=20+180*j;
                    aliens.push_back(a);
                }
            }
        };

        if(disp.is_keyR())
        {
            vie=1;
            X0=950;
            Y0=1800;
            speed_alien=1;
            speed_spaceship=10;
            delay_shot=300;
            dif=3;
            aliens.clear();
            shots.clear();
            score=0;
            for(int i=0; i<11; i++)
            {
                for(int j=0; j<dif; j++)
                {
                    alien a;
                    a.x=110+180*i;
                    a.y=20+180*j;
                    aliens.push_back(a);
                }
            }
        }

        disp.display(game);
    }
}

#include "bomb.h"
#include"bullet.h"
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Enemy
{
public:
    Sprite Asprite;
    Texture tex;
    virtual void attack() =0;
    float x,y;
    
    float timer;
    float speed;
    bool dropped;
    char identifier;
    bomb * Bomb;
    bool working;
    virtual void collisionDetection(bullet *btr, int level, int&  score)=0;
    virtual void movement()=0;
    void workingOnBombOff()
    {
        this->Bomb->working=0;
        this->working=1;
    }
    void adjustDiamond(Enemy*e[])//adjusting the array into a diamond shape
    {
        e[0]->Asprite.setPosition(10 , 3 * 77 + 10);
        e[1]->Asprite.setPosition(10 + 60, 2 * 77 +10);
        e[2]->Asprite.setPosition(10 + 60*2, 1*77 + 10);
        e[3]->Asprite.setPosition(10 + 60*3, 0*77 + 10);
        e[4]->Asprite.setPosition(10 + 60*4, 1*77 + 10);
        e[5]->Asprite.setPosition(10 + 60*5, 2*77 + 10);
        e[6]->Asprite.setPosition(10 + 60*6, 3*77 + 10); //halfway point
        e[7]->Asprite.setPosition(10 + 60*1, 4*77 + 10);
        e[8]->Asprite.setPosition(10 + 60*2, 5*77 + 10);
        e[9]->Asprite.setPosition(10 + 60*3, 6*77 + 10);
        e[10]->Asprite.setPosition(10 + 60*4, 5*77 + 10);
        e[11]->Asprite.setPosition(10 + 60*5, 4*77 + 10);
        e[12]->Asprite.setPosition(10 + 60*6, 3*77 + 10);        
        for(int i=0; i<13;i++)
        {
            e[i]->working=1;
        }

    }
    bool diamondHorizontal(bool &dir,Enemy*e[])//seeing if its going out of bounds and pushing it back
    {
        if(e[0]->Asprite.getPosition().x  <=0)
            return true;
        if(e[12]->Asprite.getPosition().x  >=700)
            return true;

        return false;        
    }
    bool diamondVertical(bool &dir,Enemy*e[])//seeing if its going out of bounds and pushing it back
    {
        if(e[3]->Asprite.getPosition().y  <=0)
            return true;
        if(e[9]->Asprite.getPosition().y  >=600)
            return true;



        return false;
    }

    void diamonndMovement(bool &hU, bool &hR, Enemy*e[])//moving the shape as a whole
    {
        if(diamondHorizontal(hR, e))
        {hR= !hR;}
        if(hR)
        {
            for(int i=0; i<13;i++)
            {
                e[i]->Asprite.move(0.05*speed,0);
            }
        }
        else
        {
            for(int i=0; i<13;i++)
            {
                e[i]->Asprite.move(-0.05*speed,0);
            }
        }
        


        if(diamondVertical(hU, e))
        {hU = !hU;}
        if(!hU)
        {
            for(int i=0; i<13;i++)
            {
                e[i]->Asprite.move(0,0.05*speed);
            }
        }
        else
        {
            for(int i=0; i<13;i++)
            {
                e[i]->Asprite.move(0,-0.05*speed);
            }
        }
        


    }
    void triangleAdjust(Enemy *e[])
    {
        for (int i = 0; i < 3; i++)
        {
            e[i]->Asprite.setPosition(100 + i * 66, 80);
            if (i != 0)
                e[i + 3]->Asprite.setPosition(100 + i * 66, 80 + i * 77);
        }

        e[3]->Asprite.setPosition(100+3*66,80+3*77); // overlapped one
        for (int i = 7; i < 11; i++)
        {
            e[i]->Asprite.setPosition(100 + (i - 4) * 66, 80);
            e[i + 3]->Asprite.setPosition(100 + (i - 4) * 66,80 + (10-i) * 77);
        }
        e[6]->working=0;
    }
    void activeAction(float t, Enemy*e[], bullet *btr, int level, int &score)
    {
        for (int i = 0; i < 13; i++) // Cycling through all Enemies
        {
            e[i]->timer += t;                    // changing timer
            e[i]->attack();                         // Calling attack function for every enemy
            e[i]->Bomb->fall(e[i]->identifier); // Making bomb fall, enemy type passed as argument to adjust bomb speed
            e[i]->collisionDetection(btr, level,score);     // Seeing if any bullets collide with the enemies            
        }
    }
    void CrossAdjustment(Enemy*e[])//adjusting into a cross shape
    {
        for(int i=0;i<3;i++) //the first diagonal
        {
            e[i]->Asprite.setPosition(100 + i * 66, 50 + i*77);
            e[i]->working=1;
            e[i]->Bomb->working=0;
            
        }
        for(int i=3; i<6;i++)//second diagonal
        {
            e[i]->Asprite.setPosition(100 + i*66 -3*66 , (50 + 5*77) - i*77 );
            e[i]->working=1;
            e[i]->Bomb->working=0;
        }
        e[4]->working=0;//getting rid of the overlooping one        

    }
    bool crossVerticalBorder(bool &cU, Enemy *e[])
    {
        if(e[2]->Asprite.getPosition().y <150)
        {
            return true;
        }
        if(e[0]->Asprite.getPosition().y>250)
        {
            return true;
        }
        return false;
    }
    bool crossHorizontalBorder(bool &cD,Enemy *e[])
    {
         if(e[0]->Asprite.getPosition().x <50)
        {
            return true;
        }
        if(e[0]->Asprite.getPosition().x>450)
        {
            return true;
        }
        return false;
    }
    void crossMovement(bool &cU,bool &cR,Enemy *e[])
    {
        
        if(crossVerticalBorder(cU,e))
        {
            cU = !cU; 
        }
        if(!cU)
        {
            for(int i=0; i<6;i++)
            {
                e[i]->Asprite.move(0,0.05*speed);
            }
        }
        else
        {
            for(int i=0; i<6;i++)
            {
                e[i]->Asprite.move(0,-0.05*speed);
            }
        }
        if(crossHorizontalBorder(cR,e))
        {
            cR = !cU; 
        }
        if(!cR)
        {
            for(int i=0; i<6;i++)
            {
                e[i]->Asprite.move(0.05*speed,0);
            }
        }
        else
        {
            for(int i=0; i<6;i++)
            {
                e[i]->Asprite.move(-0.05*speed,0);
            }
        }


    }
    bool borderCheck(bool &dir, Enemy*e[])
    {
        if(e[0]->Asprite.getPosition().x <= 50)
        {  
            return true;
        }
        else if(e[12]->Asprite.getPosition().x >= 670)
        {
            return true;
        }
        return false;
    }
    void triangleMovement(bool &dir, Enemy*e[])
    {
        bool border = borderCheck(dir,e);
        if(border)
        {
            if(dir ==0)
            {
                e[0]->Asprite.move(0.25*speed,0);
            }
            else
            {
                e[12]->Asprite.move(-0.25*speed,0);
            }
            dir = !dir;
        }
        if(dir ==0 and !border)
        {
            for(int i=0; i<13;i++)
            {
                e[i]->Asprite.move(-0.15*speed,0);
            }
            return;
        }
        else if (dir==1 and !border)
        {
            for(int i=0; i<13;i++)
            {
                e[i]->Asprite.move(0.15*speed,0);
            }
            return;
        }
    
        
    }    
    

};


class Invader :public Enemy
{
public:
    int x,y;
    virtual void attack(){};
    virtual void collisionDetection(bullet *btr){};
    virtual void movement(){};
};  

class Alpha :public Invader
{
public:
    int x,y;
    int dir;
    

    Alpha(int x=10,int y=10)
    {
        this->speed=1;
        this->tex.loadFromFile("img/enemy_2.png");
        this->Asprite.setTexture(this->tex);
        Asprite.setPosition(x,y);
        dir =1;
        this->timer=0;
        Bomb = new bomb();
        working =1;
        bool dropped=0;
        timer = rand()%5;
        identifier ='A';


    }

    virtual void attack()
    {
        if(timer<5)
        {return;}
        Bomb->sprite.setPosition(Asprite.getPosition().x,Asprite.getPosition().y);
        Bomb->working=1;
        timer =0;
    }

    void movement()
    {
        if(!working)
        {
            return;
        }
        this->x= this->Asprite.getPosition().x;
        this->y = this->Asprite.getPosition().y;
        
        if(dir<3){
            if(x<=600 && y<= 200 )
            {
                dir =1;
            }
            else if(x<=680 && y>= 200)
            {
                dir =2;
            }
        }
        else if(dir==3)
        {
            
            if(x>=660 && y >= 40)
            {
               
                
                Asprite.move(0,-0.2*speed);
                return;
             
            }
            if(y<=40)
            {
                dir =4;
            }

            

        }
        else if(dir==4){
            Asprite.move(-0.2*speed,0);
            if(x<40)
            {
                dir =1;
            }
        }
        
        
        if(dir ==1)
        {
            Asprite.move(0,0.2*speed);
            return;
        }
        if(dir ==2)
        {
            Asprite.move(0.2*speed,0);

            //return;
        }
        if(x>=680 && y>=200)
        {
            dir =3;
            
        }

        
    }
    void collisionDetection(bullet *btr, int level, int & score)
    {
        if(!working)
        {
            return;
        }

        for(int i=0; i<10; i++)
        {
            if(!btr[i].working)
            {
                continue;
            }
            if((btr[i].sprite.getPosition().x+22 >= Asprite.getPosition().x) && (btr[i].sprite.getPosition().x <= Asprite.getPosition().x + 60 ) )
            {
                if((btr[i].sprite.getPosition().y+22 >= Asprite.getPosition().y) && (btr[i].sprite.getPosition().y <= (Asprite.getPosition().y + 77)))
                {
                    working =0;
                    btr[i].working =0;
                    score += 10* level;

                } 
            }

        }



    }



};

class Beta :public Invader
{
public:
    int x,y;
    int dir;
    
    Beta(int x=10,int y=10)
    {
        this->speed=1;
        this->tex.loadFromFile("img/enemy_1.png");
        this->Asprite.setTexture(this->tex);
        Asprite.setPosition(x,y);
        dir =1;
        this->timer=0;
        working =1;
        Bomb = new bomb();
        timer = rand()%3;
        identifier ='B';
    }
    virtual void attack()
    {
        if(timer<3)
        {return;}
        Bomb->sprite.setPosition(Asprite.getPosition().x,Asprite.getPosition().y);
        Bomb->working=1;
        timer =0;
    }
    void movement()
    {
        if(!working)
        {
            return;
        }
        this->x= this->Asprite.getPosition().x;
        this->y = this->Asprite.getPosition().y;
        
        
        if(dir<3){
            if(x<=600 && y<= 200 )
            {
                dir =1;
            }
            else if(x<=680 && y>= 200)
            {
                dir =2;
            }
        }
        else if(dir==3)
        {
            
            if(x>=660 && y >= 40)
            {
                
                Asprite.move(0,-0.2*speed);
                return;
             
            }
            if(y<=40)
            {
                dir =4;
            }
            
            

        }
        else if(dir==4){
            
            Asprite.move(-0.2*speed,0);
            if(x<40)
            {
                dir =1;
            }



        }
        
        
        if(dir ==1)
        {
            Asprite.move(0,0.2*speed);
            return;
        }
        if(dir ==2)
        {
            Asprite.move(0.2*speed,0);

            //return;
        }
        if(x>=680 && y>=200)
        {
            dir =3;
           
        }

        
    }

    void collisionDetection(bullet *btr, int level,int &score)
    {
        if(!working)
        {
            return;
        }

        for(int i=0; i<10; i++)
        {
            if(!btr[i].working)
            {
                continue;
            }
            if((btr[i].sprite.getPosition().x+22 >= Asprite.getPosition().x) && (btr[i].sprite.getPosition().x <= Asprite.getPosition().x + 60 ) )
            {
                if((btr[i].sprite.getPosition().y+22 >= Asprite.getPosition().y) && (btr[i].sprite.getPosition().y <= (Asprite.getPosition().y + 77)))
                {
                    working =0;
                    btr[i].working =0;
                    score+=20*level;

                } 
            }

        }



    }





};

class Gamma :public Invader
{
public:
    int x,y;
    int dir;
    Gamma(int x=10,int y=10)
    {
        this->speed=1;
        this->tex.loadFromFile("img/enemy_3.png");
        
        this->Asprite.setTexture(this->tex);
        if(x!=40*16)
            Asprite.setPosition(x,y); //x<=680 && y>= 200
        else{
                working =0;
        }

        this->timer =0;
        dir =3;
        timer = rand()%2;
        working =1;
        Bomb = new bomb();
        identifier ='C';
    }
    void movement()
    {
        if(!working)
        {
            return;
        }
        this->x= this->Asprite.getPosition().x;
        this->y = this->Asprite.getPosition().y;
        
        if(dir<3){
            if(x<=600 && y<= 200 )
            {
                dir =1;
            }
            else if(x<=680 && y>= 200)
            {
                dir =2;
            }
        }
        else if(dir==3)
        {
            
            if(x>=660 && y >= 40)
            {
                
                Asprite.move(0,-0.2*speed);
                return;
             
            }
            if(y<=40)
            {
                dir =4;
            }
            
            

        }
        else if(dir==4){
            
            Asprite.move(-0.2*speed,0);
            if(x<40)
            {
                dir =1;
            }



        }
        
        
        if(dir ==1)
        {
            Asprite.move(0,0.2*speed);
            return;
        }
        if(dir ==2)
        {
            Asprite.move(0.2*speed,0);

            //return;
        }
        if(x>=680 && y>=200)
        {
            dir =3;
           
        }

        
    }
    void collisionDetection(bullet *btr,int level, int& score)
    {
        if(!working)
        {
            return;
        }

        for(int i=0; i<10; i++)
        {
            if(!btr[i].working)
            {
                continue;
            }
            if((btr[i].sprite.getPosition().x+22 >= Asprite.getPosition().x) && (btr[i].sprite.getPosition().x <= Asprite.getPosition().x + 60 ) )
            {
                if((btr[i].sprite.getPosition().y+22 >= Asprite.getPosition().y) && (btr[i].sprite.getPosition().y <= (Asprite.getPosition().y + 77)))
                {
                    working =0;
                    btr[i].working =0;
                    score+=30*level;

                } 
            }

        }



    }
    virtual void attack()
    {
        if(timer<2)
        {return;}
        Bomb->sprite.setPosition(Asprite.getPosition().x,Asprite.getPosition().y);
        Bomb->working=1;
        timer =0;
        
    }




};



class Dragon: public Enemy
{
public:
    Sprite Dir;
    Texture frontT;
    Texture leftT;
    Texture rightT;
    Texture Laser;
    Texture LaserLeft;
    Texture LaserRight;
    int pos;

    

    Gamma * Gptr[4];
    Dragon()
    {
        this->speed=1;
        this->tex.loadFromFile("img/dragon.png");
        this->Asprite.setTexture(tex);
        Asprite.setPosition(250,100);
        this->working=0;
        Asprite.setScale(1.3,1.4);
        for(int i=0; i<4;i++)
        {
            if(i==1 || i==2)
                Gptr[i] = new Gamma(260*i, 80);
            else if(i==0)
                Gptr[i] = new Gamma(0,80);
            else     
                Gptr[i] = new Gamma(260*i-86, 80);
        }
        frontT.loadFromFile("img/PNG/Parts/cockpitYellow_4.png");
        leftT.loadFromFile("img/PNG/Parts/cockpitYellow_41.png");
        rightT.loadFromFile("img/PNG/Parts/cockpitYellow_42.png");
        Laser.loadFromFile("img/PNG/Lasers/laserBlue01.png");
        LaserLeft.loadFromFile("img/image(3).png");
        LaserRight.loadFromFile("img/image(2).png");
        pos=0;
        

    }
    
    Gamma* getGptr(int i){return Gptr[i];}

    void attack()//dragon attack
    {
        if(!working)
        {
            return;
        }
        if(timer>6)
        {
            timer=0;
            Dir.setScale(1,1);
        }
        for(int i =0; i<4;i++)//making Dragons pet Gammas attack player
        {
            
            Gptr[i]->attack();
            
            Gptr[i]->Bomb->fall('D');//Setting really fast speed for the bomb

        }
        
        if(timer >3)
        {
            if(pos ==1)
            {
                Dir.setTexture(LaserLeft);
                Dir.setPosition(240,Dir.getPosition().y);
                Dir.setScale(1,1);
            }
            else if(pos==2)
            {
                Dir.setTexture(LaserRight);
                Dir.setScale(1,1);
                
            }
            else if(pos ==3)
            {
                Dir.setTexture(Laser);
                Dir.setScale(1,1);
            }
        }
    }
    void pointeradjust(float x)
    {
        if(!working)
        {
            return;
        }
        if(timer>=2)
        {
            return;
        }
        if(x <260)
        {
            Dir.setTexture(leftT);
            pos =1;
        }
        else if(x>260*2)
        {
            Dir.setTexture(rightT);
            pos=2;
        }
        else
        {
            Dir.setTexture(frontT);
            pos=3;
        }
    }
    bool hit(float x)
    {
        if(!working)
        {
            return false;
        }
        if(timer<=3)
        {
            return false;
        }
        else
        {
            if(x<260 && pos ==1)
                return true;
            if(x>260*2 && pos ==2)
                return true;
            else if(pos==3 and x>260 and x<260*2)
            {
                return true;
            }
        }
        return false;
    }
    virtual void collisionDetection(bullet *btr, int level, int& score){}
    virtual void movement(){}
};

class Monster: public Enemy
{
public: 
    Texture laserT;
    Sprite LaserS;
    Monster()
    {
        this->speed=1;
        this->timer=0;
        this->tex.loadFromFile("img/monster1.png");
        this->Asprite.setTexture(tex);
        this->Asprite.setScale(0.7,0.7);//665 * 665 to 465 * 465
        this->Asprite.setPosition(100,20);
        this->working=0;
        this->laserT.loadFromFile("img/PNG/Lasers/laserRed14.png");//13*57
        this->LaserS.setTexture(laserT);


    } 
    void attack()
    {
        if(!working)
        {
            return;
        }
        if(timer<2)
        {
            return;
        }
        else
        {
            LaserS.setPosition(Asprite.getPosition().x-30+232,20+365);
            LaserS.setScale(5,7); //13*5
        }

    }
    void hit(float a, bool &f)
    {
        if(!working)
        {
            return;
        }
        if(f==1 or timer<2)
        {
            return;
        }
        if(a>Asprite.getPosition().x+232.0-13*2.5 and a<Asprite.getPosition().x+232+13*2.5)//seeing if laser hits player
        {
            f=1;
            
        }
    }
    void followPlayer(float a)
    {
        if(!working)
        {return;}
        if(a>Asprite.getPosition().x+232)
            Asprite.move(0.05*speed,0);
        if(a<Asprite.getPosition().x +232)
            Asprite.move(-0.05*speed,0);    
    }
    bool hitMonster(float x, float y)
    {
        if(!working)
        {
            return false;
        }
        //77 * 80 for the spaceship
        //465 for the monster

        if(x+77 >=this->Asprite.getPosition().x and x <= this->Asprite.getPosition().x +465)//seeing if x values align for a hit
        {
            if(y+80 >=this->Asprite.getPosition().y and y<= this->Asprite.getPosition().y+465)
            {
                return true;
            }
        }
        return false;



    }

    virtual void collisionDetection(bullet *btr, int level, int & score){}
    virtual void movement(){}

};





// class 
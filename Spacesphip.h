#include <SFML/Graphics.hpp>
#include<string.h>
//#include "bullet.h"
#include "Enemy.h"
#include "addons.h"
using namespace sf;


class Spacesphip{

public:
	Texture tex;
	Sprite sprite;
	Sprite life;
	Texture ltex;
	int tilt;
	float speed=0.1;
	float x,y;
	bullet * b_ptr;
	int lives;
	//int idx;


	Spacesphip(std::string png_path)
	{
		ltex.loadFromFile("img/PNG/UI/playerLife2_orange.png");
		life.setTexture(ltex);
		life.setPosition(0,0);
		tex.loadFromFile(png_path); //103 * 107
		sprite.setTexture(tex);
		x=340;y=700;
		sprite.setPosition(x,y);
		sprite.setScale(0.75,0.75); // 77 * 80
		b_ptr = new bullet[10];
		for(int i =0; i<10; i++)
		{
			b_ptr[i] = bullet();
		}
		this->lives=3;
		//idx =1;
	}
	
	void fire() //firing bullet for the first time
	{
		for(int i =0; i<10; i++)
		{
			if(b_ptr[i].working == 0 )
			{
				b_ptr[i].shoot_tilt = tilt;
				b_ptr[i].working =1;
				b_ptr[i].sprite.setPosition(x+36, y-40);
					
				break;
			}

		}
			
	}
	void moveBullet() //checking if bullet is in condition to move and moving 
	{

		for(int i =0; i<10; i++)
		{
			b_ptr[i].checkCollision();
		}

		
		for(int i =0; i<10; i++)
		{
			if(b_ptr[i].working == 1)
			{
				if(b_ptr[i].shoot_tilt ==0)
				{

					b_ptr[i].sprite.move(0, -0.5);

				}
				else if(b_ptr[i].shoot_tilt ==1)
				{
					b_ptr[i].sprite.move(-0.35,-0.35);
				}
				else if(b_ptr[i].shoot_tilt == 2)
				{

					b_ptr[i].sprite.move(0.35,-0.35);
				}

			}
		}
	}
	
	void move(std::string s)//moving the spaceship
	{
		float delta_x=0,delta_y=0;

		int tilt =0;
		if(s=="l")
		{
			//move the player left
			delta_x=-1.5 ;
			if(this->sprite.getPosition().x <= 0 )
			{
				float temp;
				temp = sprite.getPosition().y;

				sprite.setPosition(690,temp);

			}
		
		}	
		else if(s=="r")
		{
			//move the player right
			delta_x=1.5;
			if(this->sprite.getPosition().x >= 700 )
			{
				float temp;
				temp = sprite.getPosition().y;

				sprite.setPosition(0,temp);

			}
		}	
		if(s=="u")
			delta_y=-1.5;
		else if(s=="d")
			delta_y=1.5;
			
	

		delta_x*=speed;
		delta_y*=speed;

		sprite.move(delta_x, delta_y);
		
		this->x =  sprite.getPosition().x; //extracting the x and y values of the ship at the given time
		this->y =  sprite.getPosition().y;

	}

	void tilts(int orient)//tilting spaceship as needed
	{
		this->tilt=orient;
		if(this->tilt==1)
		{
			tex.loadFromFile("img/mor1.png");
			sprite.setTexture(tex);

		}
		else if(this->tilt==2)
		{
			tex.loadFromFile("img/mor2.png");
			sprite.setTexture(tex);

		}
		
	}

	void collision(Enemy * eptr)//checking spaceship collision with enemies or bombs
	{

			if(!eptr->working)
			{
				return;
			}
			else if((eptr->Asprite.getPosition().x +60 >=  sprite.getPosition().x) && (eptr->Asprite.getPosition().x  <=  sprite.getPosition().x +77) )
            {
                if((eptr->Asprite.getPosition().y + 77 >= sprite.getPosition().y) && ( eptr->Asprite.getPosition().y<= (sprite.getPosition().y +80)))
                {
					eptr->working=0;
                    this->lives=0;
					return;
                } 
            }

			if(!eptr->Bomb->working)
			{
				return;
			}
			else if((eptr->Bomb->sprite.getPosition().x +31 >=  sprite.getPosition().x) && (eptr->Bomb->sprite.getPosition().x  <=  sprite.getPosition().x +77) )
            {
                if((eptr->Bomb->sprite.getPosition().y +31  >=  sprite.getPosition().y) && (eptr->Bomb->sprite.getPosition().y<= (sprite.getPosition().y +80)))
                {
					eptr->Bomb->working=0;
                    this->lives-=1;
                } 
            }
	}
	

};

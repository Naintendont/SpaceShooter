#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace sf;
using namespace std;


class Addons
{
public:
    Sprite AddonSprite;
    Texture AddonTex;
    bool working;
    float timer;
    virtual void fall()=0;


};

class powerUP:public Addons
{

};

class lives:public Addons
{
public:
    lives()
    {
        AddonTex.loadFromFile("img/PNG/UI/playerLife1_red.png");
        AddonSprite.setTexture(AddonTex);
        this->timer=0;
        working =0;
        

    }
    void fall()
    {
        if(!working)
        {
            return;
        }
        else
        {
            if(AddonSprite.getPosition().y >= 740)
            {
                working =0;
            }
            else
            {
                AddonSprite.move(0,0.05);
            }
        }
    }
    void appear()
    {
        if(!working)
        {
            working =1;
            AddonSprite.setPosition(300, 0);
        }
        
    }
};
class Danger:public Addons
{

};
class Fire:public Addons
{


};

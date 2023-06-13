#include <SFML/Graphics.hpp>
#include<string.h>
using namespace sf;
using namespace std;

class bullet
{
public:
    Texture btex;
    Sprite sprite;
    float x,y;
    bool working;
    int shoot_tilt;

    bullet()
    {
        this->y=700;
        this->x=340;
        working =0;
        shoot_tilt =0;
        

        

    }

    void checkCollision()
    {
        if(sprite.getPosition().y <= 0){
            this->working=0;
            return;
        }
        if(sprite.getPosition().x <= 0){
            this->working =0;
            return;
        }
        if(sprite.getPosition().x>=740){
            this->working =0;
            return;
        }
    }
    

};
#include <SFML/Graphics.hpp>
#include<string.h>

using namespace sf;
using namespace std;

class bomb
{
public:
    Sprite sprite;
    Texture tex;
    bool working;
    int x,y;
    bomb(string png="img/enemy_laser.png", bool t=0)
    {

        tex.loadFromFile(png);
        sprite.setTexture(tex);

        x=0;
        y=0;
        working = t;

    }
    void fall(char x)
    {
        
        if(!working)
            return;
        //sprite.setPosition(x,y);
        this->x = sprite.getPosition().x;
        this->y = sprite.getPosition().y;


        if(this->y>= 780)
        {
            working =0;
            return;
        }
        if(working)
        {sprite.move(0,+0.15 * (x - 'A' + 1));}
        
    }

};
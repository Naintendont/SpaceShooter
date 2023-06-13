

#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;

class Menu{
public:
    Sprite menu;
    Texture Mtexture;
    Font MFont;
    Text MText[5];
//add menu attributes here
    Menu()
    {
    //constructors body
        Mtexture.loadFromFile("bg.png");
        menu.setTexture(Mtexture);
        //menu.setScale(0.406,0.7222);

        if(!MFont.loadFromFile("img/Berlin.ttf"))
            cout<<"Font Failure !";

        for(int i=0; i<5; i++)
        {
            MText[i].setFont(this->MFont);
            MText[i].setFillColor(Color::White);
            MText[i].setCharacterSize(50);
            MText[i].setPosition(50, 100*(i+1));
        }
        MText[0].setString("Press G to Start Game");
        MText[1].setString("Press R to Restart");
        MText[2].setString("Press Escape to Exit");
        MText[3].setString("Press P to pause the game");
        MText[4].setString("Press Q to unpause the game");
        // Start
        


    }

};

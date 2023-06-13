
#include <SFML/Graphics.hpp>
// #include <SFML/Audio.hpp>
#include <string.h>
#include <cstdlib>
#include "menu.h"
#include <time.h>
#include <iostream>
// #include "Enemy.h"
using namespace std;
#include "Spacesphip.h"
// #inlcude ""
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{
public:
    Sprite background; // Game background sprite
    Texture bg_texture;
    Spacesphip *p; // player
    int level;
    int shape;
    bool generation;
    Enemy *e_ptr[13];
    Dragon *dragP;
    Monster *monsP;
    Texture *tex1;
    Addons *Add_ptr[4];
    bool triangle_dir;
    int score;
    Text TScore;
    Font TFont;
    string SScore;
    
    // add other game attributes

    Game()
    {
        p = new Spacesphip("img/player_ship.png");
        bg_texture.loadFromFile("img/background.jpg");
        background.setTexture(bg_texture);
        background.setScale(2, 1.5);
        this->level = 1;
        this->shape = 1;
        triangle_dir=0;
        score=0;
        this->generation = 0;
        srand(time(0)); // now rand() will generate random values on every program run
        if(!TFont.loadFromFile("img/Berlin.ttf"))
            cout<<"Font Failure !";
        TScore.setFont(TFont);    
        TScore.setFillColor(Color::White);
        TScore.setCharacterSize(25);
        TScore.setPosition(500, 20);

        dragP = new Dragon;
        monsP = new Monster;
        // E2[1] = new Dragon;

        Add_ptr[0]= new lives();

        for (int i = 0; i < 6; i++) // Polymorphism
        {
            e_ptr[i] = new Alpha((50 * i), 20);
            e_ptr[i]->working = 1;
            e_ptr[i]->speed = 1;
            e_ptr[i]->Asprite.setTexture(e_ptr[i]->tex);
            e_ptr[i]->Asprite.setScale(0.5, 0.5); // 120 * 154 into 60 * 77
        }

        for (int i = 6; i < 10; i++)
        {
            e_ptr[i] = new Beta((40 * i), 100);
            e_ptr[i]->working = 1;
            e_ptr[i]->speed = 1;
            e_ptr[i]->Asprite.setTexture(e_ptr[i]->tex);
            e_ptr[i]->Asprite.setScale(0.5, 0.5); // 124 * 106 into 62 * 53
        }

        for (int i = 10; i < 13; i++)
        {
            e_ptr[i] = new Gamma((40 * i), 20);
            e_ptr[i]->working = 1;
            e_ptr[i]->speed = 1;
            e_ptr[i]->Asprite.setTexture(e_ptr[i]->tex);
            e_ptr[i]->Asprite.setScale(0.4, 0.4); // 173 * 132 into 86  * 66
        }
        tex1 = new Texture;
        tex1->loadFromFile("img/enemy_3.png");
    }
    void start_game()
    {

        RenderWindow window(VideoMode(780, 780), title);
        Clock clock;
        float timer = 0;
        float time_delay = 0.15;
        float time_for_monster = 45, monster_timer = 0;
        float time_for_dragon = 55, dragon_timer = 0;
        float time_from_fire = 1;
        bool leftUpDown = 0, rightUpDown = 0, livedDone=0, DangerDone=0, FireDone=0, PowerupDone=0;
        int AlphaGone = 0;
        bool monsterDone = 0, dragonDone = 0, shifted = 0, crossUp=0, crossRight =0,monsterhit=0,hitregistered=0, heartUp=0, heartR=0;
        bool temp[13] = {};

        Event e2;
        Menu m;
        while (!(Keyboard::isKeyPressed(Keyboard::G)))
        {
            {
                window.draw(m.menu);
                for (int i = 0; i < 5; i++) // loading all three texts
                    window.draw(m.MText[i]);

                window.display();
            }
        }

        while (window.isOpen())
        {
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;
            monster_timer += time;

            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                    window.close();          // close the game
            }
            if (Keyboard::isKeyPressed(Keyboard::P))
            {
                while (!Keyboard::isKeyPressed(Keyboard::Q))
                {
                    window.draw(m.menu); // Drawing menu elemnts and looping for the text
                    for (int i = 0; i < 5; i++)
                    {
                        window.draw(m.MText[i]);
                        window.draw(TScore);
                    }
                    window.display();
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            { // If left key is pressed
                window.close();
            } // Player will move to left

            if (Keyboard::isKeyPressed(Keyboard::Left)) // If left key is pressed
            {
                p->move("l");
                if (Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::Down))) // if left and up or left and down are pressed
                {
                    leftUpDown = 1;
                }

            } // Player will move to left
            if (Keyboard::isKeyPressed(Keyboard::R))
            {
                window.close();
                Game r;
                r.start_game();
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
            {
                p->move("r");                                                                         // player will move to right
                if (Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::Down))) // if right and up or rioght and down pressed
                {
                    rightUpDown = 1;
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Up)) // If up key is pressed
            {                           
                if(p->sprite.getPosition().x>=600 and p->sprite.getPosition().y <= 100)
                {
                    p->sprite.setPosition(20,700);
                }
                else if(p->sprite.getPosition().x<=100 and p->sprite.getPosition().y <= 100)
                {
                    p->sprite.setPosition(700,700);
                }
                else if (p->sprite.getPosition().y > 0)                                 // player will move upwwardds
                {
                    p->move("u");
                }
                else // wrapping back up if it goes out of lower bounds
                {
                    
                    p->sprite.setPosition(p->sprite.getPosition().x, 701);
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
            {
                if(p->sprite.getPosition().x >= 600 and p->sprite.getPosition().y >= 600 )
                {
                    p->sprite.setPosition(20,20);
                }
                else if(p->sprite.getPosition().x <= 100 and p->sprite.getPosition().y >= 600)
                {
                    p->sprite.setPosition(590,110);
                }
                else if (p->sprite.getPosition().y < 700)
                {
                    p->move("d");
                }    // player will move downwards
                else // wrapping back down if player goes too far down
                {
                    p->sprite.setPosition(p->sprite.getPosition().x, 0);
                }
            }

            if (leftUpDown) // if left and up or down pressed
            {
                p->tilts(1); // rotating left
                leftUpDown = 0;
            }
            else if (rightUpDown) // if right and up or down pressed
            {
                p->tilts(2); // rotating right
                rightUpDown = 0;
            }
            else // setting default textures back
            {
                p->tex.loadFromFile("img/player_ship.png");
                p->sprite.setTexture(p->tex);
                p->tilt = 0;
            }

            ////////////////////////////////////////////////
            /////  Call your functions here            ////
            //////////////////////////////////////////////
            time_from_fire += time;
            monster_timer += time;
            dragon_timer += time;

            if (Keyboard::isKeyPressed(Keyboard::Space)) // Spacebar check
            {
                if (time_from_fire > time_delay) // Setting a time delay for spacebar
                {
                    p->fire();          // fire a bullet
                    time_from_fire = 0; // reset timer
                }
            }
            p->moveBullet(); // moving bullets

            Texture tex2;
            tex2.loadFromFile("img/PNG/Lasers/laserBlue10.png"); // loading up texture for bullets

            for (int i = 0; i < 10; i++)
            { // setting textures for all bullets

                p->b_ptr[i].sprite.setTexture(tex2);
                p->b_ptr[i].sprite.setScale(0.6, 0.6);
            }

            //level=2;

            if(level==1)//splitting game into levels and shapes
            {
                if (AlphaGone < 3 and (dragon_timer < time_for_dragon or dragonDone) and (monster_timer<time_for_monster or monsterDone)) 
                { // seeing atleast one is on screen
                    if (AlphaGone == 0)
                    {
                        e_ptr[0]->activeAction(time,e_ptr,p->b_ptr, level, score); //passing time, bullets and enemy array for handling all funcitons
                        for(int i=0; i<13;i++)
                        {
                            e_ptr[i]->movement();                       // Calling movement for every enemy
                            p->collision(e_ptr[i]); // seeing if spaceship collides with any enemy or enemy bomb
                        }
    
                        for (int i = 0; i < 13; i++) // loop to see if all enemies have been destroyed
                        {
                            AlphaGone = 1;
                            if (e_ptr[i]->working)
                            {
                                AlphaGone = 0;
                                break;
                            }
                        }
                    }
                    else if (AlphaGone == 1 and this->shape == 1)
                    {
                        for (int i = 0; i < 13; i++)
                        {
                            e_ptr[i]->workingOnBombOff();//bomb turned off, working turned on
                        }
                        e_ptr[0]->triangleAdjust(e_ptr);//all enemies adjusted into a triangle
                        
                        shape = 2; //triangle here
                        AlphaGone = 1;
                    }
                    else if (AlphaGone == 1 and shape ==2)
                    {
                        e_ptr[0]->triangleMovement(triangle_dir,e_ptr);//making tirangle move
                        e_ptr[0]->activeAction(time,e_ptr,p->b_ptr, level, score); //passing time, bullets and enemy array for handling all funcitons
                        for(int i=0; i<13;i++)
                        {
                            p->collision(e_ptr[i]); // seeing if spaceship collides with any enemy or enemy bomb
                        }
                        int idx=0;
                        for (int i = 0; i < 13; i++) // loop to see if all enemies have been destroyed
                        {
                            
                            if (e_ptr[i]->working) //counting how many are remianing
                            {
                                
                                
                                idx++;
                            }
    
                        }
                        
                        if(!idx) //if none remaining, move to next stage
                        {
                            
                            AlphaGone=2;
                            
                        }
                        
                        
                    }
                    else if(AlphaGone==2)
                    {
                        
                        
                        if(shape ==2)//if previous shape hasnt been reset yet
                        {
                            
                            for(int i=0; i<13;i++)
                                e_ptr[i]->working=0;
                            
                            e_ptr[0]->CrossAdjustment(e_ptr);
                            shape=3;
                            
                        }
                        else if(shape ==3) //remember, shape 2 in constructpr
                        {
    
                            e_ptr[0]->crossMovement(crossUp, crossRight, e_ptr);
                            e_ptr[0]->activeAction(time,e_ptr,p->b_ptr, level,score);
                            for(int i=0; i<13;i++)
                            {
                                p->collision(e_ptr[i]); // seeing if spaceship collides with any enemy or enemy bomb
                            }
                            int idx=0;
                            for (int i = 0; i < 13; i++) // loop to see if all enemies have been destroyed
                            {
                            
                                if (e_ptr[i]->working) //counting how many are remianing
                                {
                                    idx++;
                                }   
    
                            }
                            //cout << idx <<endl;
                            if(!idx) //if none remaining, move to next stage
                            {
                                AlphaGone=3;
                                shape=4;
                                
                                if(!monsterDone)
                                {
                                    monster_timer += time_for_monster;
                                }
                                else if(!dragonDone)
                                {
                                    dragon_timer += time_for_dragon;
                                }
                                else
                                {
                                    cout << "next level"<<endl;
                                    level=2;
                                }                        
                            }
                        }
    
                    }    
    
                }
                else
                {
                    
                    if (!monsterDone and time_for_monster < monster_timer) // calling monster
                    {
                         if (!shifted) // saving state
                        {
                            for (int i = 0; i < 13; i++) // saving if working into a temporary array
                            {
                                temp[i] = e_ptr[i]->working;
                                e_ptr[i]->working = 0;
                            }
                            shifted = true;
                        }
                        
                        monsP->working=1;                                   //turning the monster on
                        monsP->timer += time;                               //adding timer
                        monsP->attack();                                    //attacking with laser
                        monsP->followPlayer(p->sprite.getPosition().x);     //adjusting according to player
                        monsP->hit(p->sprite.getPosition().x,monsterhit);   //hitting player based on x coordinates
                        if(!hitregistered and monsterhit)                   //taking one life down since laser doesnt immediatley kill
                        {
                            hitregistered=1;
                            p->lives-=1;
                        }
                        if(monsP->hitMonster(p->sprite.getPosition().x, p->sprite.getPosition().y))//passing ship x and y and seeing if collision takes place
                        {
                            p->lives =0;
                        }
                        if(monsP->timer>5)
                        {
                            monsP->working=0;
                            monsterDone=1;
                            monsP->timer=0;
                            if(!dragonDone)
                            {
                                dragon_timer+=time_for_dragon;
                            }
                            for (int i = 0; i < 13; i++) // restoring funtional states back into enemy
                            {
                                e_ptr[i]->working = temp[i];
                            }
                            monsterhit=0;
                            shifted=false;
                            score += 40* level;
                        }
                        if(dragonDone and monsterDone and shape ==4) //shifting to next level
                        {
                            cout <<"Level 1 done"<<endl;;
                            level=2;
        
                        }
    
                    }
                    if (!dragonDone and time_for_dragon < dragon_timer) // calling dragon
                    {
                        if (!shifted) // saving state
                        {
                            for (int i = 0; i < 13; i++) // saving if working into a temporary array
                            {
                                temp[i] = e_ptr[i]->working;
                                e_ptr[i]->working = 0;
                            }
                            shifted = true;
                        }
                        dragP->timer += time;                            // adjusting timer for bombs
                        dragP->working = 1;                              // turning dragon sprite on for display and other functionality
                        dragP->attack();                                 // calling attack for the dragon
                        dragP->pointeradjust(p->sprite.getPosition().x); // take aim at user
                        for (int i = 0; i < 4; i++)                      // checking collision for each of the dragon's pet Gammas
                        {
                            Enemy *temp = dragP->getGptr(i);
    
                            temp->timer += time;
    
                            p->collision(temp);
                        }
                        if (dragP->hit(p->sprite.getPosition().x)) //seeing if user gets hit by laser blast
                        {
                            p->lives = 0;
                        }
                        if (dragP->pos != 1)
                            dragP->Dir.setPosition(250 + 146, 336 + 90); //Adjusting position because one of the images is unaligned by default
                        if (dragP->timer > 3)
                            dragP->Dir.setScale(5, 5);
                        if (dragP->timer > 5)
                        {
                            dragP->working = 0;
                            dragonDone = 1;
                            for (int i = 0; i < 13; i++) // restoring funtional states back into enemy
                            {
                                e_ptr[i]->working = temp[i];
                            }
                            dragon_timer = 0;
                            shifted=false;
                            score+=40*level;
                        }
                        if(dragonDone and monsterDone and shape ==4) //shifting to next level
                        {
                            cout <<"Level 1 done"<<endl;;
                            level=2;
                            dragon_timer=0;
                            monster_timer=0;
                            dragonDone=0;
                            monsterDone=0;

                        }
                    }
                    
    
                }
                



            }
            else if(level==2)
            {
                if (shape<5)
                {
                    e_ptr[0]->adjustDiamond(e_ptr);
                    shape=5;
                }
                e_ptr[0]->diamonndMovement(heartUp, heartR, e_ptr);
                for(int i=0; i<13;i++)
                {
                    e_ptr[i]->speed=1.5;
                }
                e_ptr[0]->activeAction(time,e_ptr,p->b_ptr, level,score);
                for(int i=0; i<13;i++)
                {
                    p->collision(e_ptr[i]); // seeing if spaceship collides with any enemy or enemy bomb
                }
                int idx=0;
                for (int i = 0; i < 13; i++) // loop to see if all enemies have been destroyed
                {
                
                    if (e_ptr[i]->working) //counting how many are remianing
                    {
                        idx++;
                    }   

                }
                if(!idx)
                {
                    shape=6;
                    if(!monsterDone)
                    {
                        monster_timer += time_for_monster;
                    }
                    else if(!dragonDone)
                    {
                        dragon_timer += time_for_dragon;
                    }
                    else
                    {
                        cout << "level2 done" <<endl;
                        level=3;
                        shape=0;
                    }
                }
                if (!dragonDone and time_for_dragon < dragon_timer) // calling dragon
                {
                    if (!shifted) // saving state
                    {
                        for (int i = 0; i < 13; i++) // saving if working into a temporary array
                        {
                            temp[i] = e_ptr[i]->working;
                            e_ptr[i]->working = 0;
                        }
                        shifted = true;
                    }
                    dragP->timer += time;                            // adjusting timer for bombs
                    dragP->working = 1;                              // turning dragon sprite on for display and other functionality
                    dragP->attack();                                 // calling attack for the dragon
                    dragP->pointeradjust(p->sprite.getPosition().x); // take aim at user
                    for (int i = 0; i < 4; i++)                      // checking collision for each of the dragon's pet Gammas
                    {
                        Enemy *temp = dragP->getGptr(i);

                        temp->timer += time;

                        p->collision(temp);
                    }
                    if (dragP->hit(p->sprite.getPosition().x)) //seeing if user gets hit by laser blast
                    {
                        p->lives = 0;
                    }
                    if (dragP->pos != 1)
                        dragP->Dir.setPosition(250 + 146, 336 + 90); //Adjusting position because one of the images is unaligned by default
                    if (dragP->timer > 3)
                        dragP->Dir.setScale(5, 5);
                    if (dragP->timer > 5)
                    {
                        dragP->working = 0;
                        dragonDone = 1;
                        for (int i = 0; i < 13; i++) // restoring funtional states back into enemy
                        {
                            e_ptr[i]->working = temp[i];
                        }
                        dragon_timer = 0;
                        shifted=false;
                        score+=40*level;
                    }
                    if(dragonDone and monsterDone and shape ==4) //shifting to next level
                    {
                        cout <<"Level 2 done"<<endl;;
                        level=3;
                        shape=0;
                        dragon_timer=0;
                        monster_timer=0;
                        dragonDone=0;
                        monsterDone=0;

                    }
                }
                if (!monsterDone and time_for_monster < monster_timer) // calling monster
                {
                        if (!shifted) // saving state
                    {
                        for (int i = 0; i < 13; i++) // saving if working into a temporary array
                        {
                            temp[i] = e_ptr[i]->working;
                            e_ptr[i]->working = 0;
                        }
                        shifted = true;
                    }
                    
                    monsP->working=1;                                   //turning the monster on
                    monsP->timer += time;                               //adding timer
                    monsP->attack();                                    //attacking with laser
                    monsP->followPlayer(p->sprite.getPosition().x);     //adjusting according to player
                    monsP->hit(p->sprite.getPosition().x,monsterhit);   //hitting player based on x coordinates
                    if(!hitregistered and monsterhit)                   //taking one life down since laser doesnt immediatley kill
                    {
                        hitregistered=1;
                        p->lives-=1;
                    }
                    if(monsP->hitMonster(p->sprite.getPosition().x, p->sprite.getPosition().y))//passing ship x and y and seeing if collision takes place
                    {
                        p->lives =0;
                    }
                    if(monsP->timer>5)
                    {
                        monsP->working=0;
                        monsterDone=1;
                        monsP->timer=0;
                        if(!dragonDone)
                        {
                            dragon_timer+=time_for_dragon;
                        }
                        for (int i = 0; i < 13; i++) // restoring funtional states back into enemy
                        {
                            e_ptr[i]->working = temp[i];
                        }
                        monsterhit=0;
                        shifted=false;
                        score += 40* level;
                    }
                    if(dragonDone and monsterDone and shape ==4) //shifting to next level
                    {
                        cout <<"Level 2 done"<<endl;;
                        level=3;
                        shape=0;
    
                    }

                    }
                //e_ptr[0]->diamonndMovement(heartUp,heartR,e_ptr);



            }
            



            // cout << p->lives <<endl;
            if(p->lives == 0)
            {
                Texture tover;
                Sprite sover;
                tover.loadFromFile("img/over.jpg");
                sover.setTexture(tover);
                float timer2=0;
                window.clear();
                clock.restart();
                window.draw(sover);
                window.display();
                while(timer2<3)
                {
                    timer2 = clock.getElapsedTime().asSeconds();
                }
                window.close();
            }

            window.clear(Color::Black); // clears the screen
            window.draw(background);    // setting background
            window.draw(p->sprite);     // setting player on screen

            for (int i = 0; i < 13; i++) // cycling through all bullets and aplhas
            {

                if (i < 10)
                {
                    if (p->b_ptr[i].working)
                    {
                        window.draw(p->b_ptr[i].sprite); // displaying active bullets
                    }
                }
                if (e_ptr[i]->working) // If enemy not shot
                {
                    if (e_ptr[i]->Bomb->working) // if bomb is in the game
                    {
                        window.draw(e_ptr[i]->Bomb->sprite);//draw bomb
                    }
                    window.draw(e_ptr[i]->Asprite); // drawing enemy
                }
            }






            if(Add_ptr[0]->working)
            {
                window.draw(Add_ptr[0]->AddonSprite);
            }
            if (dragP->working) // if Dragon is actively used
            {
                window.draw(dragP->Dir);
                for (int i = 0; i < 4; i++)//iterating through bombs and sprites of dragons pet gammas
                {
                    Enemy *temp = dragP->getGptr(i);
                    temp->Asprite.setTexture(temp->tex);
                    temp->Asprite.setScale(0.4, 0.4);
                    window.draw(temp->Asprite);
                    if (temp->Bomb->working)
                        window.draw(temp->Bomb->sprite);
                }
                window.draw(dragP->Asprite); // draw dragon
            }
            if(monsP->working)
            {
                window.draw(monsP->Asprite);
                window.draw(monsP->LaserS);
            }
            for (int i = 0; i < p->lives; i++) // displaying number of lives in the left hand corner
            {
                window.draw(p->life); // drawing life and changing coordinates of it after
                p->life.move(77, 0);
            }
            p->life.setPosition(0, 0); // Resetting p.life
            SScore = to_string(score);
            SScore = "Score is  " + SScore;
            //cout <<SScore <<endl;
            TScore.setString(SScore);
            window.draw(TScore);

            // cout<< "Y = " << p->sprite.getPosition().y <<  " x = " << p->sprite.getPosition().x <<endl; //displaying ship x and y
            window.display(); // Displying all the sprites
        }
    }
};


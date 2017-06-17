#pragma once

#include "SFML\Graphics.hpp"
#include "Box2D\Box2D.h"

class Player
{
public:
    Player(); //Constructor
  

    void SetSprite(sf::Sprite&);

    //PLAYER MOVEMENT FUNCTIONS
    void moveUp();
    void StandStill();
    void moveRight();
    void moveLeft();
    void Animate();
    void setCollisionBox(b2World& world);
    void applyPhysics(b2World& world);

    //ACCESSOR FUNCTIONS
    sf::Sprite getSprite() const;

    sf::View GetView() const;

    void CheckView();

private:
    sf::Sprite sprite; //Declare Player Sprite
    sf::Vector2i source; //Declare Source (Sprite Sheet Crop)
    enum _Direction { Down, Left, Right, Up }; //Declare Direction Enumeration

    sf::Vector2f position;
    sf::View view;

    int numFootContacts;
                                               //ANIMATION DATA
    float speed; //Player Speed
    sf::Clock animClock; //Player Animation Clock
    sf::Time animTime; //Player Animation Time
};

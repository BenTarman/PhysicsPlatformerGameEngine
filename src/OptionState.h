#pragma once

#include "GameState.h"
#include "SFML\Graphics.hpp"

class OptionState: public GameState
{
private:

    sf::View gameView;
    sf::View guiView;

    

public:

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

   OptionState(Game* game);



};
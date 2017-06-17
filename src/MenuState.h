#ifndef GAME_STATE_START_HPP
#define GAME_STATE_START_HPP

#include <SFML/Graphics.hpp>

#include "GameState.h"

class MenuState : public GameState
{
private:

    sf::View view;

   

   

    void loadgame();
    void loadOptions();

public:

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

    MenuState(Game* game);
};

#endif /* GAME_STATE_START_HPP */
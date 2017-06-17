#ifndef GAME_STATE_EDITOR_HPP
#define GAME_STATE_EDITOR_HPP

#include <SFML/Graphics.hpp>

#include "gameState.h"
#include "player.h"
#include "TileMap.h"


class GameStateEditor : public GameState
{
private:

    sf::View gameView;
    sf::View guiView;

    sf::RectangleShape shape;


    Player homura;
    
    TileMap map;

    sf::Texture BoxTexture;
    sf::Sprite Sprite;

    void PauseGame();

    int counter;

public:
    void bar(b2World& world);
    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

    GameStateEditor(Game* game);
};

#endif /* GAME_STATE_EDITOR_HPP */
#ifndef GAME_HPP
#define GAME_HPP

#include <stack>
#include <vector>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "FontManager.h"
#include <memory>

class GameState;

class Game
{
public:


    bool isSpriteClicked(sf::Text sprite);
   

    sf::RenderWindow window;


    TextureManager texmgr;

    //main menu text
    FontManager playGame;
    FontManager options;
    FontManager quitGame;

    //options text
    FontManager resizeWindow;
    FontManager fullScreen;
    FontManager windowedScreen;




    sf::Sprite homuraSheet;
    sf::Sprite background;
    sf::Sprite dude;

   
    int counter;

    void pushState(std::shared_ptr<GameState> states);

    std::shared_ptr<GameState> currentState();

    //void changeState(GameState* state);
 

    void gameLoop();

    Game();
 

private:

    std::vector<std::shared_ptr<GameState>> states;

    void loadTextures();
    void loadFonts();


};

#endif /* GAME_HPP */
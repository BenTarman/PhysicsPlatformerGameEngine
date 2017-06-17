#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


#include "game.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "FontManager.h"

#include "Box2D\Box2D.h"


void Game::loadTextures()
{

    try
    {
        texmgr.loadTexture("background", "UBW.png");
        background.setTexture(this->texmgr.getRef("background"));
       
        texmgr.loadTexture("dude", "homuraSheet.png");
        dude.setTexture(texmgr.getRef("dude"));
        
       
    }
    catch (const std::exception&)
    {

    }

}

void Game::loadFonts()
{
    //main menu stuff
    playGame.SetParameters("Play Game", "arial", 900.0, 250.0);
    options.SetParameters("Options", "arial", 900.0, 300.0);
    quitGame.SetParameters("Quit Game", "arial", 900.0, 350.0);


    //option menu stuff
    resizeWindow.SetParameters("RESIZE WINDOW", "arial", 800.0, 250.0);
    fullScreen.SetParameters("Full Screen", "arial", 900.0, 300.0);
    windowedScreen.SetParameters("Windowed", "arial", 900.0, 350.0);

  
}

void Game::pushState(std::shared_ptr<GameState> state)
{
    states.push_back(std::shared_ptr<GameState>(state));

}




std::shared_ptr<GameState> Game::currentState()
{
    if (this->states.empty()) return nullptr;
    return states.back();


}

/*

void Game::changeState(GameState* state)
{
    if (!this->states.empty())
        popState();
    pushState(state);

    return;
}*/





void Game::gameLoop()
{
    sf::Clock clock;


    while (this->window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();
        if (currentState() == nullptr) continue;
        currentState()->handleInput();
        currentState()->update(dt);
        this->window.clear();
        currentState()->draw(dt);

        this->window.display();

       
    }
}

Game::Game()
{
    loadTextures();

    loadFonts();

    window.create(sf::VideoMode(1920, 1080), "Sick Game");
    


    /*sf::Vector2f targetSize(1280.0f, 720.0f);

    background.setScale(
        targetSize.x / background.getLocalBounds().width,
        targetSize.y / background.getLocalBounds().height);*/


    this->window.setFramerateLimit(60);


    
}





bool Game::isSpriteClicked(sf::Text sprite) {

    sf::IntRect rect(sprite.getPosition().x, sprite.getPosition().y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

    //If mouse position is in the rectangle do whatever
    if (rect.contains(sf::Mouse::getPosition(window))) {

        return true;
    }

    //Otherwise, don't do anything
    return false;
}
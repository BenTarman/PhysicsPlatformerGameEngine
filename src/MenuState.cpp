#include "MenuState.h"
#include <SFML/Graphics.hpp>

#include <iostream>

#include "OptionState.h"
#include "FontManager.h"
#include"gameState.h"
#include "PlayState.h"
#include "MenuState.h"

void MenuState::draw(const float dt)
{
   

   //set kawaii girl in background
    game->window.draw(game->background);


    //draw menu shit
    game->window.draw(game->playGame.GetText());
    game->window.draw(game->options.GetText());
    game->window.draw(game->quitGame.GetText());


}

void MenuState::update(const float dt)
{

}

void MenuState::handleInput()
{
    sf::Event event;

 
    while (game->window.pollEvent(event))
    {
        switch (event.type)
        {


            /* Close the window */
        case sf::Event::Closed:
            game->window.close();
            break;

       
      

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                game->window.close();
            else if (event.key.code == sf::Keyboard::Return)
                loadgame();
            break;

        case sf::Event::MouseMoved:
            if (game->isSpriteClicked(game->playGame.GetText()))
                game->playGame.SetColor(sf::Color::Red);
            else
                game->playGame.SetColor(sf::Color::White);

            if (game->isSpriteClicked(game->options.GetText()))
                game->options.SetColor(sf::Color::Red);
            else
                game->options.SetColor(sf::Color::White);

            if (game->isSpriteClicked(game->quitGame.GetText()))
                game->quitGame.SetColor(sf::Color::Red);
            else
                game->quitGame.SetColor(sf::Color::White);

            break;

        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (game->isSpriteClicked(game->playGame.GetText()))
                    loadgame();
                if (game->isSpriteClicked(game->options.GetText()))
                    loadOptions();
             
                if (game->isSpriteClicked(game->quitGame.GetText()))
                    game->window.close();


            }


            break;


        }
    }

    return;
}



MenuState::MenuState(Game* game)
{
    this->game = game;
   /* sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    view.setSize(pos);
    pos *= 0.5f;
    view.setCenter(pos);
*/

}

void MenuState::loadgame()
{

    game->pushState(std::shared_ptr<GameState>(new GameStateEditor(game)));

}



void MenuState::loadOptions()
{
    game->pushState(std::shared_ptr<GameState>(new OptionState(game)));


}



#include "MenuState.h"
#include "OptionState.h"


void OptionState::draw(const float dt)
{
   
    game->window.draw(game->resizeWindow.GetText());
    game->window.draw(game->fullScreen.GetText());
    game->window.draw(game->windowedScreen.GetText());


}

void OptionState::update(const float dt)
{


}


void OptionState::handleInput()
{
    sf::Event event;

    while (this->game->window.pollEvent(event))
    {
        switch (event.type)
        {
            /* Close the window */
        case sf::Event::Closed:

            game->window.close();
            break;

            //pause game
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                game->pushState(std::shared_ptr<GameState>(new MenuState(game)));
            break;

        case sf::Event::MouseMoved:
            if (game->isSpriteClicked(game->fullScreen.GetText()))
                game->fullScreen.SetColor(sf::Color::Red);
            else
                game->fullScreen.SetColor(sf::Color::White);

            if (game->isSpriteClicked(game->windowedScreen.GetText()))
                game->windowedScreen.SetColor(sf::Color::Red);
            else
                game->windowedScreen.SetColor(sf::Color::White);

       

            break;

        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (game->isSpriteClicked(game->fullScreen.GetText()))
                {
                    game->window.create(sf::VideoMode(1280, 720), "Sick Game", sf::Style::Fullscreen);
                }

                if (game->isSpriteClicked(game->windowedScreen.GetText()))
                {
                    game->window.create(sf::VideoMode(1280, 720), "Sick Game");
                }
                

               


            }


            break;




        }
    }



}







OptionState::OptionState(Game* game)
{
    this->game = game;
}


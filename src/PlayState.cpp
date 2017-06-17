#include "PlayState.h"
#include "MenuState.h"
#include <iostream>


#include "player.h"
#include <SFML/Graphics.hpp>
#include "Box2D\Box2D.h"
#include "GameState.h"

#include <iostream>

b2Vec2 gravity(0, -10.f);
b2World world(gravity);



void GameStateEditor::draw(const float dt)
{
  
    map.drawStuff(game->window);
  
  

    return;
}
void GameStateEditor::update(const float dt)
{

    map.UpdateStuff(world);
   
    //bar(world);


    //homura.setCollisionBox(world);
    //homura.applyPhysics(world);



    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //Move Right
    //    homura.moveRight();

    //else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //Move Left
    //    homura.moveLeft();
    //else
    //    homura.StandStill();

    //homura.CheckView();
    //

    //for (b2Body* BodyIterator = world.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
    //{
    //    if (BodyIterator->GetType() == b2_staticBody)
    //    {



    //        
    //        shape.setOrigin(500.f / 2, 200.f / 2);
    //        shape.setPosition(30 * BodyIterator->GetPosition().x, 30 * BodyIterator->GetPosition().y);
    //        shape.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);




    //        std::cout << BodyIterator->GetPosition().y << std::endl;



    //    }

    //}
   

}

void GameStateEditor::handleInput()
{
    sf::Event event;

    
    world.Step(1 / 60.f, 8, 3);
    

    while (this->game->window.pollEvent(event))
    {
        switch (event.type)
        {
            /* Close the window */
        case sf::Event::Closed:
            this->game->window.close();
            break;

            //pause game
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                game->pushState(std::shared_ptr<GameState>(new MenuState(game)));
            break;



            /*Resize the window */
        case sf::Event::Resized:

            gameView.setSize(event.size.width, event.size.height);
            guiView.setSize(event.size.width, event.size.height);
            this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0), this->guiView));
            this->game->background.setScale(
                float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
                float(event.size.height) / float(this->game->background.getTexture()->getSize().y));
            break;

        default: break;
        }
    }

  
}


GameStateEditor::GameStateEditor(Game* game)
{

    this->game = game;

    homura.SetSprite(game->dude);
  

    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->guiView.setSize(pos);
    this->gameView.setSize(pos);
    pos *= 0.5f;

    this->guiView.setCenter(pos);
    this->gameView.setCenter(pos);

 
    map.SetMap("test");

    map.GetMap(world);

    shape.setSize(sf::Vector2f(500, 200));
    shape.setFillColor(sf::Color::Green);

    


}

void GameStateEditor::PauseGame()
{


}





void GameStateEditor::bar(b2World& world)
{
    static bool wasExecuted = false;
    if (wasExecuted)
        return;

    wasExecuted = true;



    double SCALE = 30.0;

    BoxTexture.loadFromFile("box.png");



    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(300 / SCALE, 800 / SCALE);
    BodyDef.type = b2_staticBody;
    b2Body* Body = world.CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((500.f / 2) / SCALE, (200.f / 2) / SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 1.f;
    FixtureDef.friction = 0.7f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
}
#include "SFML\Graphics.hpp"
#include <iostream>
#include "player.h"
#include "ContactListener.h"
#include "Box2D\Box2D.h"

Player::Player() //Constructor
{
    numFootContacts = 0;

    position = sf::Vector2f(0, 0);


    view.reset(sf::FloatRect(0, 0, 800, 600));

    view.setViewport(sf::FloatRect(0, 0, 1.0, 1.0));

}


void Player::SetSprite(sf::Sprite& sprite)
{
    //PLAYER SPRITE
    this->sprite = sprite;


    sf::Vector2i source(1, Down); //Default Sprite Sheet Crop
    sprite.setTextureRect(sf::IntRect(300, 0, 90, 133)); //Crop Sprite Sheet (Default Crop)

    animTime = sf::milliseconds(80); //Animation Speed
    speed = 2.5;

   

}


void Player::CheckView()
{
    position.x = sprite.getPosition().x + 16 - (1920 * 0.5);
    position.y = sprite.getPosition().y + 16 - (1080 * 0.5);


    if (position.x < 0)
        position.x = 0;
    if (position.y < 0)
        position.y = 0;

    view.reset(sf::FloatRect(position.x, position.y, 1920, 1080));

}

sf::View Player::GetView() const
{
    return view;
}


void Player::setCollisionBox(b2World& world)
{

    static bool wasExecuted = false;
    if (wasExecuted)
        return;

    wasExecuted = true;

    double SCALE = 30.0;




    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(100 / SCALE, 100 / SCALE);
    BodyDef.type = b2_dynamicBody;
    BodyDef.fixedRotation = true;

    b2Body* boxBody = world.CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((52.0f / 2) / SCALE, (106.0f / 2) / SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 1.f;
    FixtureDef.shape = &Shape;
    boxBody->CreateFixture(&FixtureDef);

    // add foot sensor fixture
    b2Fixture*  footSensorFixture;
    b2PolygonShape footSensorBox;
    b2FixtureDef FootSensorFixtureDef;

    footSensorBox.SetAsBox((20.f / 2) / SCALE, (110.f / 2) / SCALE);
    FootSensorFixtureDef.isSensor = true;
    FootSensorFixtureDef.shape = &footSensorBox;
    footSensorFixture = boxBody->CreateFixture(&FootSensorFixtureDef);
    footSensorFixture->SetUserData((void*)3);
}


//ACCESSOR FUNCTIONS
sf::Sprite Player::getSprite() const //Player Sprite
{
    return sprite;
}

//PLAYER MOVEMENT
void Player::moveUp()
{

    
}

void Player::StandStill()
{
    sprite.setTextureRect(sf::IntRect(source.x * 98, 13, 98, 138));
    Animate();
 

}

void Player::moveRight()
{




    sprite.setTextureRect(sf::IntRect(source.x * 108, 138, 73, 130)); //Crop Sprite Sheet

    Animate();
}


void Player::moveLeft()
{

  
    sprite.setTextureRect(sf::IntRect(source.x * 108, 260, 73, 138)); //Crop Sprite Sheet

    Animate();

}

void Player::Animate()
{
    if (animClock.getElapsedTime() > animTime)
    {


        //Animation
        source.x++;
        if (source.x > 7)
        {
            source.x = 0;
        }
        animClock.restart();

    }

}


void Player::applyPhysics(b2World& world)
{

    for (b2Body* BodyIterator = world.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
    {
        if (BodyIterator->GetType() == b2_dynamicBody)
        {

            int num = 0;

            sprite.setOrigin(52.f / 2, 106.f / 2);
            sprite.setPosition(30 * BodyIterator->GetPosition().x, 30 * BodyIterator->GetPosition().y);
            sprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);



            MyContactListener contact;




            b2Vec2 vel = BodyIterator->GetLinearVelocity();
            float desiredVel = 0;


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                desiredVel = -5;

                float velChange = desiredVel - vel.x;
                float force = BodyIterator->GetMass() * velChange / (1 / 60.0); //f = mv/t
                BodyIterator->ApplyForce(b2Vec2(force, 0), BodyIterator->GetWorldCenter(), true);

            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                desiredVel = 5;

                float velChange = desiredVel - vel.x;
                float force = BodyIterator->GetMass() * velChange / (1 / 60.0); //f = mv/t
                BodyIterator->ApplyForce(b2Vec2(force, 0), BodyIterator->GetWorldCenter(), true);

            }

            

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                num++;
                if (num < 1)
                    break;


                float impulse = BodyIterator->GetMass() * -5;
                BodyIterator->ApplyLinearImpulse(b2Vec2(0, impulse), BodyIterator->GetWorldCenter(), true);
                num--;
                num--;
            }

            float changeInVelocity = desiredVel - BodyIterator->GetLinearVelocity().x;
            float mass = BodyIterator->GetMass();
            float impulse = mass * changeInVelocity;

            BodyIterator->ApplyLinearImpulse(b2Vec2(impulse, 0.f), BodyIterator->GetWorldCenter(),true);


        }


    }
}
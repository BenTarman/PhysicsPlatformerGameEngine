#include "game.h"
#include "MenuState.h"
#include <memory>

#include "SFML/Graphics.hpp"

#include <iostream>
int main()
{
    Game game;


    game.pushState(std::shared_ptr<GameState>(new MenuState(&game)));

    game.gameLoop();




    return 0;
}

//
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/Graphics.hpp>
//
//#include <tmx/MapLoader.h>
//#include <tmx/tmx2box2d.h>
//
//#include <tmx/DebugShape.h>
//
//#include <Box2D/Collision/Shapes/b2PolygonShape.h>
//#include <Box2D/Collision/Shapes/b2CircleShape.h>
//
//#include "ContactListener.h"
//#include <memory>
//
////NOTE ADD THIS NEXT TIME U WORK ON TO THE "PLAYER"
//
//
//
//
//
//
//int main()
//{
//    sf::RenderWindow renderWindow(sf::VideoMode(1280u, 640u), "TMX Loader - Box2D Body Creation Example");
//    renderWindow.setVerticalSyncEnabled(true);
//    renderWindow.setFramerateLimit(60);
//    //create map loader and load map
//    tmx::MapLoader ml("maps/");
//    ml.Load("test.tmx");
//
//    //create a box2D world
//    b2Vec2 gravity(0, -20);
//    b2World world(gravity);
//
//   
//
//    //parse map objects
//    std::vector<std::unique_ptr<sf::Shape>> debugBoxes;
//    std::vector<DebugShape> debugShapes;
//    std::vector<DebugShape> players;
//    std::map<b2Body*, sf::CircleShape> dynamicShapes; //we can use raw pointers because box2D manages its own memory
//
//   
//
//
//    std::map<b2Body*, sf::RectangleShape> player; //we can use raw pointers because box2D manages its own memory
//    
//    b2Body* b;
//
// 
//
//
//    b2Fixture* footSensorFixture;
//    b2PolygonShape footSensorBox;
//    b2FixtureDef FootSensorFixtureDef;
//
//
//
//
//
//
//
//    
//
//    const std::vector<tmx::MapLayer>& layers = ml.GetLayers();
//    for (const auto& l : layers)
//    {
//        if (l.name == "Static") //static bodies which make up the map geometry
//        {
//            for (const auto& o : l.objects)
//            {
//                //receive a pointer to the newly created body
//                b2Body* b = tmx::BodyCreator::Add(o, world);
//
//                b->SetGravityScale(10);
//
//                //iterate over body info to create some visual debugging shapes to help visualise
//                debugBoxes.push_back(std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape(sf::Vector2f(6.f, 6.f))));
//                sf::Vector2f pos = tmx::BoxToSfVec(b->GetPosition());
//                debugBoxes.back()->setPosition(pos);
//                debugBoxes.back()->setOrigin(3.f, 3.f);
//
//                for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
//                {
//                    b2Shape::Type shapeType = f->GetType();
//                    f->SetFriction(2.0);
//                    
//                    if (shapeType == b2Shape::e_polygon)
//                    {
//                        DebugShape ds;
//                        ds.setPosition(pos);
//                        b2PolygonShape* ps = (b2PolygonShape*)f->GetShape();
//
//                        int count = ps->GetVertexCount();
//                        for (int i = 0; i < count; i++)
//                            // ds.AddVertex(sf::Vertex(tmx::BoxToSfVec(ps->GetVertex(i)), sf::Color::Green));
//
//                         //ds.AddVertex(sf::Vertex(tmx::BoxToSfVec(ps->GetVertex(0)), sf::Color::Green));
//                            debugShapes.push_back(ds);
//                    }
//
//                }
//            }
//        }
//        else if (l.name == "Dynamic")
//        {
//            for (const auto& o : l.objects)
//            {
//                //this time keep a copy of the pointer so we can update the dynamic objects
//                //with their information. Don't forget to create a dynamic body
//                b = tmx::BodyCreator::Add(o, world, b2BodyType::b2_dynamicBody);
//                //b->GetFixtureList()->SetRestitution(0.99f); //set some properties of the body
//                                                            //we assume for this example all dynamic objects are circular. Other shapes also work
//                                                            //but you need to impliment your own drawing for them.
//
//                for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
//                {
//                    f->SetFriction(0.0);
//                    f->SetDensity(1.f);
//                }
//                footSensorBox.SetAsBox(20 / 2 / 30.0, 22 / 2 / 30.0);
//
//                FootSensorFixtureDef.isSensor = true;
//                FootSensorFixtureDef.shape = &footSensorBox;
//                footSensorFixture = b->CreateFixture(&FootSensorFixtureDef);
//                footSensorFixture->SetUserData((void*)3);
//                FootSensorFixtureDef.friction = 0.0f;
//
//
//                b2PolygonShape* cs = static_cast<b2PolygonShape*>(b->GetFixtureList()->GetShape());
//
//
//                sf::RectangleShape c(sf::Vector2f(50, 50));
//
//                c.setOrigin(sf::Vector2f(25, 25));
//
//
//                player.insert(std::pair<b2Body*, sf::RectangleShape>(b, c));
//
//
//            }
//
//
//        }
//
//
//    }
//
//    MyContactListener contact;
//
//    world.SetContactListener(&contact);
//    //-----------------------------------//
//    sf::Clock clock;
//    while (renderWindow.isOpen())
//    {
//        //poll input
//        sf::Event event;
//        while (renderWindow.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                renderWindow.close();
//        }
//
//        //update
//        world.Step(clock.restart().asSeconds(), 6, 3);
//        for (auto& ds : dynamicShapes)
//        {
//            //move the circle shape based on physics sim using conversion functions for units
//            ds.second.setPosition(tmx::BoxToSfVec(ds.first->GetPosition()));
//        }
//        for (auto& ds : player)
//        {
//            //move the circle shape based on physics sim using conversion functions for units
//            ds.second.setPosition(tmx::BoxToSfVec(ds.first->GetPosition()));
//
//
//            b2Vec2 vel = b->GetLinearVelocity();
//            float desiredVel = 0;
//
//            
//
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
//            {
//                desiredVel = -5;
//
//                float velChange = desiredVel - vel.x;
//                float force = b->GetMass() * velChange / (1 / 60.0); //f = mv/t
//                b->ApplyForce(b2Vec2(force, 0), b->GetWorldCenter(), true);
//
//            }
//            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
//            {
//                desiredVel = 5;
//
//                float velChange = desiredVel - vel.x;
//                float force = b->GetMass() * velChange / (1 / 60.0); //f = mv/t
//                b->ApplyForce(b2Vec2(force, 0), b->GetWorldCenter(), true);
//
//            }
//            std::cout << contact.blTouching << std::endl;
//
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//            {
//               
//              
//                if (contact.blTouching == true)
//                {
//
//                    b->ApplyLinearImpulse(b2Vec2(0.5, 0.8), b->GetWorldCenter(), true);
//                    b->SetLinearDamping(1.5);
//                    
//
//                }
//
//                
//
//
//
//            }
//
//
//            float changeInVelocity = desiredVel - b->GetLinearVelocity().x;
//            float mass = b->GetMass();
//            float impulse = mass * changeInVelocity;
//
//            b->ApplyLinearImpulse(b2Vec2(impulse, 0.f), b->GetWorldCenter(), true);
//
//
//        }
//
//        
//
//
//
//        //draw
//        renderWindow.clear();
//        renderWindow.draw(ml);
//        for (const auto& s : debugBoxes)
//            renderWindow.draw(*s);
//        for (const auto& s : debugShapes)
//            renderWindow.draw(s);
//        for (auto& ds : dynamicShapes)
//            renderWindow.draw(ds.second);
//        for (auto& ds : player)
//            renderWindow.draw(ds.second);
//        
//
//        renderWindow.display();
//    }
//
//    return 0;
//}
#pragma once
#include "Box2D\Box2D.h"


class MyContactListener : public b2ContactListener
{
public:
    bool blTouching;

    void BeginContact(b2Contact* contact)
    {
        //check if fixture A was a ball
        void* bodyUserData = contact->GetFixtureA()->GetUserData();
        if ((int)bodyUserData == 3)
        {
            blTouching = true;
        }
        //check if fixture B was a ball
        bodyUserData = contact->GetFixtureB()->GetUserData();
        if ((int)bodyUserData == 3)
        {
            blTouching = true;
        }
    }

    void EndContact(b2Contact* contact)
    {
        //check if fixture A was a ball
        void* bodyUserData = contact->GetFixtureA()->GetUserData();
        if ((int)bodyUserData == 3)
        {
            blTouching = false;
        }
        //check if fixture B was a ball
        bodyUserData = contact->GetFixtureB()->GetUserData();

        if ((int)bodyUserData == 3)
        {
            blTouching = false;
        }
    }
};

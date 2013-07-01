//---------------------------------------------------------------------------


#pragma hdrstop

#include "customWalls.h"
BrickWall::BrickWall(GameManager * gm, FastBitmap *c)
{
        state = 0;
        type  = TYPE_BRICK_WALL;
        team  = TEAM_BRICK_WALL;
        context = c;
        manager = gm;
        hp=maxhp=100;
        
        SpriteFabric * sf = SpriteFabric::getInstance();
        sprite = sf->SFM_CURRENT("brickwall",c);
}
BrickWall::~BrickWall()
{
        delete sprite;
}
void BrickWall::processMessage(IMessage * msg)
{
        switch (msg->type)
        {
        case MSG_COLLISION:
                if (msg->super->type&TYPE_BULLETS)
                {
                        Bullet * b = (Bullet*)msg->super;
                        hp -=b->getDmg(this);
                        if (hp<=0)
                                manager->sendMessage(IMessage::createDestroyMeMessage(this));
                }
                break;
        default:
                break;
        }
        delete msg;
}
void BrickWall::update(uint t)
{
        if (hp<100)
                sprite->setAnimation("dmg10%");
        if (hp<70)
                sprite->setAnimation("dmg30%");
        if (hp<50)
                sprite->setAnimation("dmg50%");
        if (hp<30)
                sprite->setAnimation("dmg70%");
        if (hp<10)
                sprite->setAnimation("dmg90%");
        sprite->update();
}
//---------------------------------------------------------------------------

ConcreteWall::ConcreteWall(GameManager * mgr, FastBitmap * ct)
{
        state = 0;
        type = TYPE_CONCRETE_WALL_LVL1;
        team = TEAM_PEACEFUL;
        manager = mgr;
        context = ct;
        maxhp=hp = 100;
        typeResist = RESIST_TYPE_NORMAL;
        valueResist = 95;
        
        SpriteFabric * sf = SpriteFabric::getInstance();
        sprite = sf->SFM_CURRENT("concretewall1",context);
}
ConcreteWall::~ConcreteWall()
{
        delete sprite;
}
void ConcreteWall::processMessage(IMessage * msg)
{
        switch (msg->type)
        {
        case MSG_COLLISION:
                if (msg->super->type&TYPE_BULLETS)
                {
                        Bullet * b = (Bullet*)msg->super;
                        hp -=b->getDmg(this,typeResist, valueResist);
                        if (hp<=0)
                                manager->sendMessage(IMessage::createDestroyMeMessage(this));
                }
                break;
        default:
                break;
        }
        delete msg;
}
void ConcreteWall::update(uint t)
{
        if (hp<100)
                sprite->setAnimation("dmg20%");
        if (hp<60)
                sprite->setAnimation("dmg40%");
        if (hp<40)
                sprite->setAnimation("dmg60%");
        if (hp<20)
                sprite->setAnimation("dmg80%");
        sprite->update();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

#pragma package(smart_init)

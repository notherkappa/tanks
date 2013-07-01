//---------------------------------------------------------------------------


#pragma hdrstop

#include "gameobjects.h"
PlayerTank::PlayerTank(GameManager* mgr, FastBitmap * c)
{
        state = PLAYERTANK_STATE_STILL;
        type  = TYPE_PLAYER_TANK;
        team  = TEAM_PLAYER_TANK;
        context = c;
        manager = mgr;
        speed = 100;
        attackCoolDown = 1000;
        hp=maxhp=100;
        typeResist = valueResist = 0;
        lasttimeAttack = 0;
        memset(arrowsPressed,0,4);
        lasttimeUpdated = ::GetTickCount();

        SpriteFabric * sf = SpriteFabric::getInstance();
        sprite = sf->SFM_CURRENT("tank_babyboy",c);
        moveRequested=false;

        UserStats * us = UserStats::getInstance();
        us->hp = hp;
        us->maxhp=maxhp;
}

PlayerTank::~PlayerTank()
{
        delete sprite;
}

void PlayerTank::keyUpdate(uint spKey)
{
        updateArrowPressed(spKey);
        bool isKeyDown = spKey&KEY_DOWN?true:false;
        byte key = spKey&0xFF;
        switch (key)
        {
        case VK_UP:
                if ((!isKeyDown)&& ((state&0xFF00)!=PLAYERTANK_STATE_ON_ICE))
                        state = (state&0xFF00)| someArrowPressed()?findNextArrowState(state):PLAYERTANK_STATE_STILL;
                else if ((state&0xFF00)!=PLAYERTANK_STATE_ON_ICE && isKeyDown)
                        state = (state&0xFF00)|PLAYERTANK_STATE_GO_UP;
                break;
        case VK_LEFT:
                if ((!isKeyDown)&& ((state&0xFF00)!=PLAYERTANK_STATE_ON_ICE))
                        state = (state&0xFF00)| someArrowPressed()?findNextArrowState(state):PLAYERTANK_STATE_STILL;
                else if ((state&0xFF00)!=PLAYERTANK_STATE_ON_ICE && isKeyDown)
                        state = (state&0xFF00)|PLAYERTANK_STATE_GO_LEFT;
                break;
        case VK_RIGHT:
                if ((!isKeyDown)&& ((state&0xFF00)!=PLAYERTANK_STATE_ON_ICE))
                        state = (state&0xFF00)| someArrowPressed()?findNextArrowState(state):PLAYERTANK_STATE_STILL;
                else if ((state&0xFF00)!=PLAYERTANK_STATE_ON_ICE && isKeyDown)
                        state = (state&0xFF00)|PLAYERTANK_STATE_GO_RIGHT;
                break;
        case VK_DOWN:
                if ((!isKeyDown)&& ((state&0xFF00)!=PLAYERTANK_STATE_ON_ICE))
                        state = (state&0xFF00)| someArrowPressed()?findNextArrowState(state):PLAYERTANK_STATE_STILL;
                else if ((state&0xFF00)!=PLAYERTANK_STATE_ON_ICE && isKeyDown)
                        state = (state&0xFF00)|PLAYERTANK_STATE_GO_DOWN;
                break;
        case VK_SPACE:
                if (isKeyDown)
                        shoot();
                break;
        }
}


void PlayerTank::update(uint t)
{
        uint timel = t - lasttimeUpdated;
        if (state == PLAYERTANK_STATE_STILL)
                sprite->animate = false;
        else
                sprite->animate = true;
        if (state == PLAYERTANK_STATE_GO_UP && sprite->getCurrentAnimationName()!="go_up")
                sprite->setAnimation("go_up");
        else if (state == PLAYERTANK_STATE_GO_RIGHT && sprite->getCurrentAnimationName()!="go_right")
                sprite->setAnimation("go_right");
        else if (state == PLAYERTANK_STATE_GO_DOWN && sprite->getCurrentAnimationName()!="go_bottom")
                sprite->setAnimation("go_bottom");
        else if (state == PLAYERTANK_STATE_GO_LEFT && sprite->getCurrentAnimationName()!="go_left")
                sprite->setAnimation("go_left");
        sprite->update();

        TDoubleRect r = sprite->getDoubleRect();

        if (state == PLAYERTANK_STATE_GO_UP)
                r.top -= speed*timel/1000;
        if (state == PLAYERTANK_STATE_GO_RIGHT)
                r.left += speed*timel/1000;
        if (state == PLAYERTANK_STATE_GO_DOWN)
                r.top += speed*timel/1000;
        if (state == PLAYERTANK_STATE_GO_LEFT)
                r.left -= speed*timel/1000;

        manager->sendMessage(IMessage::createMoveRequestMessage(this,r.left,r.top));
        moveRequested = true;
        lasttimeUpdated = ::GetTickCount();
}
bool PlayerTank::someArrowPressed()
{
        for (int i=0; i<4; i++)
                if (arrowsPressed[i])
                        return true;
        return false;
}
int PlayerTank::findNextArrowState(int currentState)
{
        for (int i=0; i<4; i++)
                if (arrowsPressed[i])
                        return i+1;
        return currentState;
}
void PlayerTank::updateArrowPressed(int spKey)
{
        bool isKeyDown = spKey&KEY_DOWN?true:false;
        byte key = spKey&0xFF;

        switch (key)
        {
        case VK_UP:
                arrowsPressed[0] = isKeyDown;
                break;
        case VK_LEFT:
                arrowsPressed[1] = isKeyDown;
                break;
        case VK_RIGHT:
                arrowsPressed[2] = isKeyDown;
                break;
        case VK_DOWN:
                arrowsPressed[3] = isKeyDown;
                break;
        }
}


void PlayerTank::processMessage(IMessage * msg)
{
        switch (msg->type)
        {
        case MSG_MOVE_REQUEST:
                sprite->setPosition(msg->left,msg->top);
                break;
        case MSG_COLLISION:
                if (msg->super->type&TYPE_BULLETS)
                {
                        if(msg->super->team == team)
                        {
                                if (moveRequested)
                                {
                                        sprite->setPosition(msg->left,msg->top);
                                        moveRequested=false;
                                }
                        }
                        else if (msg->super->team != TEAM_PEACEFUL)
                        {
                                Bullet * b = (Bullet*)msg->super;
                                hp-=b->getDmg(this,typeResist,valueResist);
                                UserStats *us = UserStats::getInstance();
                                us->hp = hp<0?0:hp;
                                if (hp<0)
                                {
                                        manager->sendMessage(IMessage::createHideMeMessage(this, false,false,true));
                                        state = PLAYERTANK_STATE_DEAD;
                                }
                        }
                }

                break;

        default:
                break;
        }
        delete msg;
}
void PlayerTank::shoot()
{
        if (::GetTickCount()-lasttimeAttack>attackCoolDown)
        {
                Bullet * b = new Bullet(manager,sprite->getContext(),this, 8, 20, 250);
                manager->sendMessage(b->getSelfAddMessage());
                lasttimeAttack = ::GetTickCount();

        }
}
//---------------------------------------------------------------------------
Bullet::Bullet(GameManager * mgr, FastBitmap * c, GameObject * owner, int mindmg, int maxdmg, int sp)
{
        manager = mgr;
        context = c;
        state = owner->sprite->getCurrentAnimationID()+1;
        team = owner->team;
        type = TYPE_BULLET;

        dmg = mindmg+random(maxdmg-mindmg+1);
        speed=sp;
        lasttimeUpdated = ::GetTickCount();
        
        SpriteFabric * sf = SpriteFabric::getInstance();
        sprite = sf->SFM_CURRENT("bullet",context);

        TRect r = owner->sprite->getRect();
        int l=r.left,t=r.top;
        String ownerCurrentAnimation = owner->sprite->getCurrentAnimationName();
        if (ownerCurrentAnimation == "go_up" || ownerCurrentAnimation == "still")
        {
                l = r.Width()/2+r.left - sprite->getRect().Width()/2;
                t = r.top - sprite->getRect().Height()/2;
        }
        else if (ownerCurrentAnimation == "go_left")
        {
                l = r.left - sprite->getRect().Width()/2;
                t = r.Height()/2+r.top - sprite->getRect().Height()/2;
        }
        else if (ownerCurrentAnimation == "go_bottom")
        {
                l = r.Width()/2+r.left - sprite->getRect().Width()/2;
                t = r.bottom + sprite->getRect().Height()/2;
        }
        else if (ownerCurrentAnimation == "go_right")
        {
                l = r.right + sprite->getRect().Width()/2;
                t = r.Height()/2+r.top - sprite->getRect().Height()/2;
        }
        sprite->setPosition(l,t);

}
Bullet::~Bullet()
{
        delete sprite;
}
void Bullet::processMessage(IMessage * msg)
{
        switch(msg->type)
        {
        case MSG_COLLISION:
                if (msg->super->type&TYPE_WALL)
                {
                        state = BULLET_STATE_DEAD;
                        manager->sendMessage(IMessage::createHideMeMessage(this,false,false,true));
                }
                if (msg->super->type&TYPE_TANK)
                {
                        if (msg->super->team !=team)
                        {
                                state = BULLET_STATE_DEAD;
                                manager->sendMessage(IMessage::createHideMeMessage(this,false,false,true));
                        }
                }
                break;
        default:
                break;
        }
        delete msg;
}
int Bullet::getDmg(GameObject * sender, uint typeResist, uint valueResist)
{
        if (typeResist)
                return dmg*(100-valueResist)/100;
        else
                return dmg;
}
void Bullet::update(uint t)
{
        double timel = t-lasttimeUpdated;
        TDoubleRect r;
        switch (state)
        {
        case BULLET_STATE_MOVE_UP:
                r = sprite->getDoubleRect();
                sprite->setPosition(r.left,r.top-(timel*double(speed)/1000.));
                break;
        case BULLET_STATE_MOVE_LEFT:
                r = sprite->getDoubleRect();
                sprite->setPosition(r.left-(timel*double(speed)/1000.),r.top);
                if (sprite->getCurrentAnimationName()!="go_left")
                        sprite->setAnimation("go_left");
                break;
        case BULLET_STATE_MOVE_RIGHT:
                r = sprite->getDoubleRect();
                sprite->setPosition(r.left+(timel*double(speed)/1000.),r.top);
                if (sprite->getCurrentAnimationName()!="go_right")
                        sprite->setAnimation("go_right");
                break;
        case BULLET_STATE_MOVE_DOWN:
                r = sprite->getDoubleRect();
                sprite->setPosition(r.left,r.top+(timel*double(speed)/1000.));
                if (sprite->getCurrentAnimationName()!="go_bottom")
                        sprite->setAnimation("go_bottom");
                break;
        case BULLET_STATE_DEAD:
                if (sprite->getCurrentAnimationName()!="death")
                        sprite->setAnimation("death");
                if (sprite->isLastFrameInAnimation())
                        manager->sendMessage(IMessage::createDestroyMeMessage(this));
        default:
                break;
        }
        if (r.top<-1000 || r.left<-1000 || r.top>2000 || r.left>2000)
        {
                state = BULLET_STATE_DEAD;
                manager->sendMessage(IMessage::createHideMeMessage(this,false,true,true));
        }
        sprite->update();
        lasttimeUpdated = ::GetTickCount();
}
//---------------------------------------------------------------------------

#pragma package(smart_init)

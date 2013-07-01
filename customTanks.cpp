//---------------------------------------------------------------------------


#pragma hdrstop

#include "customTanks.h"
//---------------------------------------------------------------------------
CustomPlayerTank::CustomPlayerTank(GameManager *mgr, FastBitmap *c, String profileFilename) : PlayerTank(mgr,c)
{
        Defines profile;
        profile.Load("userdata\\"+profileFilename);
        delete sprite;
        sprite = SpriteFabric::newSprite(profile.Get("sprite"),context);
        attackCoolDown = StrToInt(profile.Get("as"));
        speed = StrToInt(profile.Get("speed"));
        dmgmin = StrToInt(profile.Get("dmgmin"));
        dmgmax = StrToInt(profile.Get("dmgmax"));
        bulletSpeed = StrToInt(profile.Get("bulletspeed"));
        bulletType = StrToInt(profile.Get("bullettype"));
        maxhp = hp = StrToInt(profile.Get("maxhp"));
        typeResist = StrToInt(profile.Get("typeresist"));
        valueResist = StrToInt(profile.Get("valueresist"));
        pen[0] = StrToInt(profile.Get("concretepen"));
        pen[1] = StrToInt(profile.Get("brickpen"));
        pen[2] = StrToInt(profile.Get("tankpen"));
}
CustomPlayerTank::~CustomPlayerTank()
{
        delete sprite;
}
void CustomPlayerTank::shoot()
{
        if (::GetTickCount()-lasttimeAttack>attackCoolDown)
        {
                Bullet *b;
                switch (bulletType)
                {
                default:
                case TYPE_BULLET:
                        b = new Bullet(manager,sprite->getContext(),this, dmgmin, dmgmax, bulletSpeed);
                        manager->sendMessage(b->getSelfAddMessage());
                        lasttimeAttack = ::GetTickCount();
                        break;
                case TYPE_ANTICONCRETE_BULLET:
                        b = new AntiConcreteBullet(manager, sprite->getContext(), this, dmgmin, dmgmax, bulletSpeed, pen[0]);
                        manager->sendMessage(b->getSelfAddMessage());
                        lasttimeAttack = ::GetTickCount();
                        break;
                }
        }
}
//---------------------------------------------------------------------------
AIRandomMoveTank::AIRandomMoveTank(GameManager *mgr, FastBitmap *c, String profile)
: CustomPlayerTank(mgr,c,profile)
{
        Defines d;
        d.Load("userdata\\"+profile);
        int cnt=0;
        movingValues[0]=StrToInt(d.Get("mv_u")); cnt+=movingValues[0];
        movingValues[1]=StrToInt(d.Get("mv_l")); cnt+=movingValues[1];
        movingValues[2]=StrToInt(d.Get("mv_r")); cnt+=movingValues[2];
        movingValues[3]=StrToInt(d.Get("mv_d")); cnt+=movingValues[3];
        movingValuesSum = cnt;
        lasttimeChangedMove = 0;
        changeTime = StrToInt(d.Get("mv_t"));
        ccTime = random(changeTime)+changeTime/2;
        scoreForKill = StrToInt(d.Get("score"));
        team = TEAM_AI;
        type = TYPE_AI_TANK;
}
void AIRandomMoveTank::processMessage(IMessage * msg)
{
        switch (msg->type)
        {
        case MSG_MOVE_REQUEST:
                sprite->setPosition(msg->left,msg->top);
                break;
        case MSG_COLLISION:

                if (msg->super->type&TYPE_WALL)
                {
                        if (msg->super->type != TYPE_BRICK_WALL || random(100)>95)
                        {
                                state = changeMove();
                                lasttimeChangedMove = ::GetTickCount();
                        }
                }
                else if (msg->super->type&TYPE_BULLETS)
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
                                if (hp<0)
                                {
                                        manager->sendMessage(IMessage::createHideMeMessage(this, false,false,true));
                                        UserStats * us = UserStats::getInstance();
                                        us->scores+=scoreForKill* (state==AIRM_STATE_DEAD?0:1);
                                        state = AIRM_STATE_DEAD;
                                }
                        }
                }
                else if (msg->super->type&TYPE_TANK && msg->super->team == TEAM_AI)
                {
                        if (moveRequested)
                        {
                                sprite->setPosition(msg->left,msg->top);
                                moveRequested=false;
                        }
                }
                break;
        default:
                break;
        }
        delete msg;
}

int AIRandomMoveTank::changeMove()
{
        int r = random(movingValuesSum);
        if (r<movingValues[0])
                return AIRM_STATE_GO_UP;
        if (r<movingValues[0]+movingValues[1])
                return AIRM_STATE_GO_LEFT;
        if (r<movingValues[0]+movingValues[1]+movingValues[2])
                return AIRM_STATE_GO_RIGHT;
        else
                return AIRM_STATE_GO_DOWN;
}
void AIRandomMoveTank::update(uint t)
{
        double timel = t - lasttimeUpdated;

        if (::GetTickCount()-lasttimeChangedMove>ccTime && state != AIRM_STATE_DEAD)
        {
                state = changeMove();
                lasttimeChangedMove = ::GetTickCount();
                ccTime = random(changeTime)+changeTime/2;
        }


        if ((state&0xFF) == AIRM_STATE_GO_UP && sprite->getCurrentAnimationName()!="go_up")
                sprite->setAnimation("go_up");
        else if ((state&0xFF) == AIRM_STATE_GO_RIGHT && sprite->getCurrentAnimationName()!="go_right")
                sprite->setAnimation("go_right");
        else if ((state&0xFF) == AIRM_STATE_GO_DOWN && sprite->getCurrentAnimationName()!="go_bottom")
                sprite->setAnimation("go_bottom");
        else if ((state&0xFF) == AIRM_STATE_GO_LEFT && sprite->getCurrentAnimationName()!="go_left")
                sprite->setAnimation("go_left");
        else if ((state&0xFF) == AIRM_STATE_DEAD && sprite->getCurrentAnimationName()!="death")
                sprite->setAnimation("death");
        sprite->update();

        if ((state&0xFF)==AIRM_STATE_DEAD && sprite->isLastFrameInAnimation())
        {
                manager->sendMessage(IMessage::createDestroyMeMessage(this));
                return;
        }
        TDoubleRect r = sprite->getDoubleRect();
        if (r.left<0)
                r.left=0;
        if (r.top<0)
                r.top=0;
        if (r.right>768)
                r.left-=r.right-768;
        if (r.bottom>512)
                r.top-=r.bottom-512;
        sprite->setPosition(r.left,r.top);


        if ((state&0xFF) == AIRM_STATE_GO_UP)
                r.top -= double(speed)*timel/1000.;
        if ((state&0xFF) == AIRM_STATE_GO_RIGHT)
                r.left += double(speed)*timel/1000.;
        if ((state&0xFF) == AIRM_STATE_GO_DOWN)
                r.top += double(speed)*timel/1000.;
        if ((state&0xFF) == AIRM_STATE_GO_LEFT)
                r.left -= double(speed)*timel/1000.;

        manager->sendMessage(IMessage::createMoveRequestMessage(this,r.left,r.top));
        shoot();
        moveRequested = true;
        lasttimeUpdated = ::GetTickCount();
}

//---------------------------------------------------------------------------

#pragma package(smart_init)

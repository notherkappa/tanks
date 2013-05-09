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
                default:
                        break;
                }
        }
}

//---------------------------------------------------------------------------

#pragma package(smart_init)

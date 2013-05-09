//---------------------------------------------------------------------------


#pragma hdrstop

#include "customBullets.h"

AntiConcreteBullet::AntiConcreteBullet(GameManager * mgr, FastBitmap * c, GameObject * owner,
                                       int mindmg, int maxdmg, int speed, int concreteResistPenetration)
                                       :Bullet(mgr, c,owner, mindmg,maxdmg,speed)
{
        delete sprite;
        sprite = SpriteFabric::newSprite("anticoncretebullet",context);

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
        concretePen = concreteResistPenetration;
}
AntiConcreteBullet::~AntiConcreteBullet()
{
        delete sprite;
}
int AntiConcreteBullet::getDmg(GameObject * sender, uint typeResist, uint valueResist)
{
        if (sender->type == TYPE_CONCRETE_WALL_LVL1 && typeResist == RESIST_TYPE_NORMAL)
                valueResist-=concretePen;
        return typeResist?dmg*(100-valueResist)/100:dmg;
}


//---------------------------------------------------------------------------

#pragma package(smart_init)

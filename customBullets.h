//---------------------------------------------------------------------------

#ifndef customBulletsH
#define customBulletsH
#include "gameobjects.h"
#include "objectDefines.h"



class AntiConcreteBullet : public Bullet
{
public:
        AntiConcreteBullet(){;}
        virtual ~AntiConcreteBullet();
        AntiConcreteBullet(GameManager * mgr, FastBitmap * c, GameObject * owner, int mindmg, int maxdmg, int speed, int concreteResistPenetration=30);
        virtual int getDmg(GameObject * sender, uint typeResist=0, uint valueResist=0);
protected:
        int concretePen;

};

//---------------------------------------------------------------------------
#endif

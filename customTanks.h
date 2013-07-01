//---------------------------------------------------------------------------

#ifndef customTanksH
#define customTanksH

#include "gameobjects.h"
#include "customBullets.h"
#include "objectDefines.h"
class CustomPlayerTank : public PlayerTank
{
public:
        CustomPlayerTank(){;}
        virtual ~CustomPlayerTank();
        CustomPlayerTank(GameManager *mgr, FastBitmap *c, String profile);

        virtual void shoot();
protected:
        int dmgmin, dmgmax, bulletSpeed, bulletType;
        int pen[3];
};
class AIRandomMoveTank : public CustomPlayerTank
{
public:
        AIRandomMoveTank(){;}
        virtual ~AIRandomMoveTank(){delete sprite;}
        AIRandomMoveTank(GameManager *mgr, FastBitmap *c, String profile);
        virtual void keyUpdate(uint spKey){;}
        virtual void processMessage(IMessage * msg);
        virtual void update(uint t);
protected:
        int changeMove();
        int movingValues[4];
        int movingValuesSum;

        uint lasttimeChangedMove;
        uint changeTime, ccTime, cAttackSpeed;
        int scoreForKill;


};
//---------------------------------------------------------------------------
#endif

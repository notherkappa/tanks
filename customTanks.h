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
        ~CustomPlayerTank();
        CustomPlayerTank(GameManager *mgr, FastBitmap *c, String profile);

        void shoot();
protected:
        int dmgmin, dmgmax, bulletSpeed, bulletType;
        int pen[3];


};
//---------------------------------------------------------------------------
#endif

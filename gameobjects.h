//---------------------------------------------------------------------------

#ifndef gameobjectsH
#define gameobjectsH

#include "gamesystem.h"
#include "objectDefines.h"





class Bullet : public GameObject
{
public:
        Bullet(){;}
        Bullet(GameManager * mgr, FastBitmap * c, GameObject * owner, int mindmg, int maxdmg, int speed);
        virtual ~Bullet();
        virtual void keyUpdate(uint spKey){;}
        virtual void processMessage(IMessage * msg);
        virtual void update(uint t);
        virtual int getDmg(GameObject * sender, uint typeResist=0, uint valueResist=0);
protected:
        int dmg;
        int speed;
        int lasttimeUpdated;
};

class PlayerTank : public GameObject
{
public:
        PlayerTank(){;}
        PlayerTank(GameManager* mgr, FastBitmap * c);
        virtual ~PlayerTank();

        virtual void keyUpdate(uint spKey);
        virtual void processMessage(IMessage * msg);
        virtual void update(uint t);
        virtual void shoot();
protected:

        bool someArrowPressed();
        void updateArrowPressed(int spKey);
        int  findNextArrowState(int currentState);


        uint speed;
        uint attackCoolDown;
        uint lasttimeAttack;
        uint lasttimeUpdated;
        bool moveRequested;

        int hp, maxhp;
        int typeResist, valueResist;

        bool arrowsPressed[4];
};



//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#ifndef customWallsH
#define customWallsH
#include "gameobjects.h"
#include "objectDefines.h"

class BrickWall : public GameObject
{
public:
        BrickWall(){;}
        BrickWall(GameManager * mgr, FastBitmap *c);
        ~BrickWall();

        void keyUpdate(uint spKey){;}
        void processMessage(IMessage * msg);
        void update(uint t);
protected:
        int hp;
        int maxhp;
};

class ConcreteWall : public GameObject
{
public:
        ConcreteWall(){;}
        ConcreteWall(GameManager * mgr, FastBitmap *c);
        ~ConcreteWall();

        void keyUpdate(uint spKey){;}
        void processMessage(IMessage * msg);
        void update(uint t);
protected:
        int hp;
        int maxhp;
        int typeResist, valueResist;
};

class BoundWall : public GameObject
{
public:
        BoundWall(){type = TYPE_BOUND_WALL;}
        ~BoundWall(){;}
        void keyUpdate(uint spKey){;}
        void processMessage(IMessage * msg){;}
        void update(uint t){;}
        IMessage * getSelfAddMessage(){return IMessage::createAddMeMessage(this,false,false,false);}
protected:

};
//---------------------------------------------------------------------------
#endif

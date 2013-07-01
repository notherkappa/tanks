//---------------------------------------------------------------------------

#ifndef gamesystemH
#define gamesystemH
#include <queue>
#include "logic.h"
#include "rendersystem.h"
#include "stats.h"
#include "objectDefines.h"


#define MSG_MOVE_REQUEST        0x1
#define MSG_STATS_INCREASE      0x2
#define MSG_SHOW_MESSAGE        0x3
#define MSG_DESTROY_ME          0x4
#define MSG_GAMEOVER            0x5
#define MSG_BROADCAST           0x6
#define MSG_ADD                 0x7
#define MSG_ADD_ME              0x8
#define MSG_HIDE_ME             0x9
#define MSG_KILL_ME             0xA

#define MSG_COLLISION           0x101
#define MSG_DIE                 0x102
#define MSG_FREE                0x0


#define MSG_ADD_ME_ALL          MSG_ADD_ME | MSG_ML | MSG_RL | MSG_CL
#define MSG_HIDE_ME_ALL         MSG_HIDE_ME| MSG_ML | MSG_RL | MSG_CL

#define MSG_ML                  0x200
#define MSG_RL                  0x400
#define MSG_CL                  0x800
#define IS_MSG_ADD_ME(message)  ((message & 0xFF)==MSG_ADD_ME)
#define IS_MSG_HIDE_ME(message) ((message & 0xFF)==MSG_HIDE_ME)



#define TEAM_PLAYER             0x1
#define TEAM_AI                 0x2
#define TEAM_HOSTILE            0x3     //Enemy for everybody. Everybody are enemies for him.
#define TEAM_TEAMLESS           0x4     //Enemy for AI. Everybody are neutral for him.
#define TEAM_NEUTRAL            0x5     //Not enemy for all. Theres enemy for him, till they attack.
#define TEAM_PEACEFUL           0x6     //Not enemy for all. Theres no enemy for him in any case

#define TEAM_CUSTOM             0x100   //Custom team.


class GameObject;
class GameManager;
struct IMessage;

struct IMessage
{
        static IMessage* createFreeMessage();
        static IMessage* createMoveRequestMessage(GameObject * s, double l, double t);
        static IMessage* createStatsIncreaseMessage(uint value);
        static IMessage* createShowMessageMessage(String message);
        static IMessage* createDestroyMeMessage(GameObject *s);
        static IMessage* createGameoverMessage();
        static IMessage* createBroadcastMessage(IMessage* message);
        static IMessage* createAddMessage(GameObject * sp);
        static IMessage* createAddMeMessage(GameObject * s, bool messageList=true, bool renderList=true, bool collisionList=true);
        static IMessage* createHideMeMessage(GameObject *s, bool messageList=true, bool renderList=true, bool collisionList=true);
        static IMessage* createCollisionMessage(GameObject * sp, int l, int t);
        static IMessage* createDieMessage();

        uint type;

        GameObject * sender;
        GameObject * super;

        IMessage * broadcast;

        double left, top;

        uint value;
        double dValue;

        String msg;
};

class GameManager
{
public:
        GameManager();
        ~GameManager();

        void setRenderManager(RenderManager * rm);
        RenderManager* getRenderManager(){return renderManager;}
        void sendMessage(IMessage * m);

        void testCollisions();
        void update();
        void processMessages();
        void render();
        void clear();

        void launchGameCycle();
private:
        std::queue<IMessage*>   messageQueue;
        std::list<GameObject*>  listenersList;
        std::list<GameObject*>  collisionList;
        RenderManager * renderManager;
        KeyUpdateProducer keyUpdater;
};


class GameObject: public KeyListener
{
public:
        GameObject(){;}
        ~GameObject(){;}
        Sprite * sprite;
        GameManager * manager;
        FastBitmap * context;
        uint type, team;
        uint state;

        virtual void processMessage(IMessage *msg)=0;
        virtual void update (uint t)=0;
        virtual void render () {;}
        virtual IMessage * getSelfAddMessage(){return IMessage::createAddMeMessage(this);}
};

class SilentObject : public GameObject
{
public:
        SilentObject(){;}
        ~SilentObject(){;}

        virtual void processMessage(IMessage *msg){;}
        virtual void update (uint t){;}
        virtual void render () {;}
        virtual void keyUpdate(uint t) {;}
        virtual IMessage * getSelfAddMessage(){return IMessage::createAddMeMessage(this,false,false,false);}
};

//---------------------------------------------------------------------------
#endif

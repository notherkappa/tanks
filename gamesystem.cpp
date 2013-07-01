//---------------------------------------------------------------------------


#pragma hdrstop

#include "gamesystem.h"

IMessage* IMessage::createFreeMessage()
{
        IMessage *m = new IMessage();
        m->type = MSG_FREE;
        return m;
}
IMessage* IMessage::createMoveRequestMessage(GameObject * s, double l, double t)
{
        IMessage *m = new IMessage();
        m->type = MSG_MOVE_REQUEST;
        m->sender = s;
        m->left = l;
        m->top = t;
        return m;
}
IMessage* IMessage::createStatsIncreaseMessage(uint value)
{
        IMessage *m = new IMessage();
        m->type = MSG_STATS_INCREASE;
        m->value = value;
        return m;
}
IMessage* IMessage::createShowMessageMessage(String message)
{
        IMessage *m = new IMessage();
        m->type = MSG_SHOW_MESSAGE;
        m->msg = message;
        return m;
}
IMessage* IMessage::createDestroyMeMessage(GameObject *s)
{
        IMessage *m = new IMessage();
        m->type = MSG_DESTROY_ME;
        m->sender = s;
        return m;
}
IMessage* IMessage::createGameoverMessage()
{
        IMessage *m = new IMessage();
        m->type = MSG_GAMEOVER;
        return m;
}
IMessage* IMessage::createBroadcastMessage(IMessage* message)
{
        IMessage *m = new IMessage();
        m->type = MSG_BROADCAST;
        m->broadcast = message;
        return m;
}
IMessage* IMessage::createAddMessage(GameObject * sp)
{
        IMessage *m = new IMessage();
        m->type = MSG_ADD;
        m->super = sp;
        return m;
}
IMessage* IMessage::createAddMeMessage(GameObject * s, bool messageList, bool renderList, bool collisionList)
{
        IMessage *m = new IMessage();
        m->type = MSG_ADD_ME | (messageList ? MSG_ML:0) | (renderList ? MSG_RL:0) | (collisionList ? MSG_CL:0);
        m->sender = s;
        return m;
}
IMessage* IMessage::createHideMeMessage(GameObject * s, bool messageList, bool renderList, bool collisionList)
{
        IMessage *m = new IMessage();
        m->type = MSG_HIDE_ME | (messageList ? MSG_ML:0) | (renderList ? MSG_RL:0) | (collisionList ? MSG_CL:0);
        m->sender = s;
        return m;
}

IMessage* IMessage::createCollisionMessage(GameObject * sp, int l, int t)
{
        IMessage *m = new IMessage();
        m->type = MSG_COLLISION;
        m->super = sp;
        m->left = l;
        m->top = t;
        return m;
}
IMessage* IMessage::createDieMessage()
{
        IMessage *m = new IMessage();
        m->type = MSG_DIE;
        return m;
}
//---------------------------------------------------------------------------
GameManager::GameManager()
{
        renderManager = 0;
}
GameManager::~GameManager()
{
        ;
}
void GameManager::setRenderManager(RenderManager * rm)
{
        renderManager = rm;
}
void GameManager::sendMessage(IMessage * m)
{
        messageQueue.push(m);
}
void GameManager::testCollisions()
{
        for (std::list<GameObject*>::iterator i=collisionList.begin(); i!=collisionList.end(); i++)
                for (std::list<GameObject*>::iterator j=i; j!=collisionList.end(); j++)
                {
                        if (i==j)
                                continue;
                        if ((*i)->sprite->isSpriteCollision((*j)->sprite))
                        {
                                (*i)->processMessage(IMessage::createCollisionMessage(*j, (*i)->sprite->getRect().left,(*i)->sprite->getRect().top));
                                (*j)->processMessage(IMessage::createCollisionMessage(*i,(*j)->sprite->getRect().left,(*j)->sprite->getRect().top));
                        }
                }
}
void GameManager::update()
{
        keyUpdater.update();
        for (std::list<GameObject*>::iterator i=listenersList.begin(); i!=listenersList.end(); i++)
                (*i)->update(::GetTickCount());

}
void GameManager::processMessages()
{
        while(!messageQueue.empty())
        {
                IMessage * msg = messageQueue.front();
                UserStats * us;

                TRect senderRect;
                bool isCollision=false;

                switch (msg->type)
                {
                case MSG_MOVE_REQUEST:
                        senderRect = convertRect(msg->sender->sprite->getRect());
                        senderRect.left = msg->left;
                        senderRect.top = msg->top;
                        isCollision=false;
                        for (std::list<GameObject*>::iterator i=collisionList.begin(); i!=collisionList.end(); i++)
                                if ((*i)!=msg->sender && rectCollision(convertRect((*i)->sprite->getRect()), senderRect))
                                {
                                        msg->sender->processMessage(IMessage::createCollisionMessage(*i,msg->left,msg->top));
                                        isCollision = true;
                                        break;
                                }
                        if (!isCollision)
                        {
                                if (senderRect.left<0 || senderRect.left>(768-senderRect.right) || senderRect.top<0 || senderRect.top>(512-senderRect.bottom))
                                {
                                        SilentObject boundWall;
                                        boundWall.type = TYPE_BOUND_WALL;
                                        msg->sender->processMessage(IMessage::createCollisionMessage(&boundWall,msg->left,msg->top));
                                }
                                else
                                        msg->sender->processMessage(IMessage::createMoveRequestMessage(0,msg->left,msg->top));
                        }
                        break;
                case MSG_DESTROY_ME:
                        listenersList.remove(msg->sender);
                        renderManager->remove(msg->sender->sprite);
                        keyUpdater.removeListener(msg->sender);
                        collisionList.remove(msg->sender);
                        delete msg->sender;
                        break;
                case MSG_BROADCAST:
                        for (std::list<GameObject*>::iterator i=listenersList.begin(); i!=listenersList.end(); i++)
                                (*i)->processMessage(msg->broadcast);
                        break;
                case MSG_ADD:
                        sendMessage(msg->super->getSelfAddMessage());
                        break;
                case MSG_ADD_ME_ALL:
                case MSG_ADD_ME | MSG_ML:
                case MSG_ADD_ME | MSG_RL:
                case MSG_ADD_ME | MSG_CL:
                case MSG_ADD_ME | MSG_ML | MSG_RL:
                case MSG_ADD_ME | MSG_ML | MSG_CL:
                case MSG_ADD_ME | MSG_RL | MSG_CL:
                        if (msg->type & MSG_ML)
                        {
                                listenersList.push_back(msg->sender);
                                keyUpdater.addListener(msg->sender);
                        }
                        if (msg->type & MSG_RL)
                                renderManager->add(msg->sender->sprite);
                        if (msg->type & MSG_CL)
                                collisionList.push_back(msg->sender);
                        break;
                case MSG_HIDE_ME_ALL:
                case MSG_HIDE_ME | MSG_ML:
                case MSG_HIDE_ME | MSG_RL:
                case MSG_HIDE_ME | MSG_CL:
                case MSG_HIDE_ME | MSG_ML | MSG_RL:
                case MSG_HIDE_ME | MSG_ML | MSG_CL:
                case MSG_HIDE_ME | MSG_RL | MSG_CL:
                        if (msg->type & MSG_ML)
                        {
                                listenersList.remove(msg->sender);
                                keyUpdater.removeListener(msg->sender);
                        }
                        if (msg->type & MSG_RL)
                                renderManager->remove(msg->sender->sprite);
                        if (msg->type & MSG_CL)
                                collisionList.remove(msg->sender);
                        break;
                case MSG_STATS_INCREASE:
                        us = UserStats::getInstance();
                        us->scores+=msg->value;
                        break;
                case MSG_GAMEOVER:
                        us = UserStats::getInstance();
                        us->gameOver=true;
                        break;
                }
                messageQueue.pop();
                delete msg;
        }
}
void GameManager::render()
{
        renderManager->render();
}

void GameManager::launchGameCycle()
{
        testCollisions();
        update();
        processMessages();
        render();
}
void GameManager::clear()
{
        while(!messageQueue.empty()) messageQueue.pop();
        listenersList.clear();
        collisionList.clear();
        keyUpdater.clear();
}

//---------------------------------------------------------------------------

#pragma package(smart_init)

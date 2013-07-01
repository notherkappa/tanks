//---------------------------------------------------------------------------


#pragma hdrstop

#include "map.h"
void GameMap::addObject(String name, int id, int left, int top)
{
        map.AddToList("objects",name);
        map.Set("objects."+name+".id",IntToStr(id));
        map.Set("objects."+name+".left",IntToStr(left));
        map.Set("objects."+name+".top",IntToStr(top));
}
void GameMap::removeObject(TRect point)
{
        TRect r;
        TStringList * l = map.GetList("objects");
        for (int i=0; i<l->Count; i++)
        {
                String name = l->Strings[i];
                r.left = StrToInt(map.Get("objects."+name+".left"));
                r.top  = StrToInt(map.Get("objects."+name+".top"));
                r.right = r.left+32;
                r.bottom = r.top +32;
                if (rectCollision(convertRect(r),convertRect(point)))
                        map.RemoveFromList("objects",l->Strings[i]);
        }
        delete l;
}
void GameMap::generateObjects(GameManager *gm, FastBitmap* c)
{
        TStringList * l = map.GetList("objects");
        TStringList * sp = map.GetList("sprites");
        if (sp!=0)
                for (int i=0; i<sp->Count; i++)
                {
                        Sprite * sprite = new Sprite();
                        sprite->loadFromFile("sprites\\"+map.Get("sprites."+sp->Strings[i]+".sprite"));
                        sprite->setPosition(StrToInt(map.Get("sprites."+sp->Strings[i]+".left")),StrToInt(map.Get("sprites."+sp->Strings[i]+".top")));
                        if (map.IsDefined("sprites."+sp->Strings[i]+".animation"))
                        {
                                sprite->setAnimation(map.Get("sprites."+sp->Strings[i]+".animation"));
                                sprite->update();
                        }
                        if (map.IsDefined("sprites."+sp->Strings[i]+".dontanimate"))
                                sprite->animate=false;
                        sprite->setContext(c);
                        gm->getRenderManager()->add(sprite);
                }
        for (int i=0; i<l->Count; i++)
        {
                String name = l->Strings[i];
                int id = StrToInt(map.Get("objects."+name+".id"));
                GameObject * toCreate=0;
                switch (id)
                {
                case TYPE_BRICK_WALL:
                        toCreate = new BrickWall(gm,c);
                        toCreate->sprite->setPosition(StrToInt(map.Get("objects."+name+".left")),
                                                      StrToInt(map.Get("objects."+name+".top")));
                        gm->sendMessage(toCreate->getSelfAddMessage());
                        break;
                case TYPE_CONCRETE_WALL_LVL1:
                        toCreate = new ConcreteWall(gm,c);
                        toCreate->sprite->setPosition(StrToInt(map.Get("objects."+name+".left")),
                                                      StrToInt(map.Get("objects."+name+".top")));
                        gm->sendMessage(toCreate->getSelfAddMessage());
                        break;
                case TYPE_PLAYER_TANK:
                        toCreate= new CustomPlayerTank(gm,c,"usertank.sav");
                        toCreate->sprite->setPosition(StrToInt(map.Get("objects."+name+".left")),
                                                      StrToInt(map.Get("objects."+name+".top")));
                        gm->sendMessage(toCreate->getSelfAddMessage());
                        break;
                case AITANK_RANDOM_MOVE:
                        toCreate= new AIRandomMoveTank(gm,c,"airmtank.cfg");
                        toCreate->sprite->setPosition(StrToInt(map.Get("objects."+name+".left")),
                                                      StrToInt(map.Get("objects."+name+".top")));
                        gm->sendMessage(toCreate->getSelfAddMessage());
                        break;

                default:
                        break;
                }
        }
        delete l;

}


//---------------------------------------------------------------------------

#pragma package(smart_init)

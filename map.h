//---------------------------------------------------------------------------

#ifndef mapH
#define mapH
#include "objectDefines.h"
#include "customWalls.h"
#include "customTanks.h"
#include "customBullets.h"
#include "gamesystem.h"
#include "rendersystem.h"

class GameMap
{
public:
        GameMap(){map.SetList("objects", new TStringList());}
        ~GameMap(){;}
        GameMap(String filename){map.Load(filename);}

        void load(String filename){map.Load(filename);}
        void save(String filename, String levelName){if (levelName!="") map.Set("name",levelName);map.Save(filename);}
        void addObject(String objectname, int id, int left, int top);
        void removeObject(TRect point);
        void generateObjects(GameManager *gm, FastBitmap* c);
        String getLevelName(){return map.Get("name");}
        String getRespawnLeft(){return StrToInt("respawnPlayer1.left");}
        String getRespawnTop() {return StrToInt("respawnPlayer1.top" );}

        
        Defines map;
private:

};
//---------------------------------------------------------------------------
#endif

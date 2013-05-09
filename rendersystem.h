//---------------------------------------------------------------------------

#ifndef rendersystemH
#define rendersystemH
#include <vcl.h>
#include <Classes.hpp>
#include <list>
#include "fastbitmap.h"
#include "defines.h"

#define RM_NORMAL       0
#define RM_ALPHA_MASK   1
#define RM_OVERLAY      2

#define SPRITE_SIGNATURE 0xB0BAAEEB

#define ZB_LOWEST       0
#define ZB_BACK         1
#define ZB_BOTTOM       16
#define ZB_BEHIND       256
#define ZB_NORMAL       4096
#define ZB_UPPER        32368
#define ZB_TOP          65536
#define ZB_INTERFACE    1048576
#define ZB_ERROR        16777215


class RenderObject
{
public:
        RenderObject();
        ~RenderObject();

        void assign(FastBitmap * fb);
        void assign(PBMP b);
        void assign(String file);
        void setRenderMode(uint Mode, uint clr=0);
        void setContext(FastBitmap * context);
        void setPosition(int left, int top);

        void init(FastBitmap * pic, FastBitmap *context);
        void init(PBMP pic,         FastBitmap *context);
        void init(String filename,  FastBitmap *context);
        void init(FastBitmap * pic, PBMP context);
        void init(PBMP pic,         PBMP context);
        void init(String filename,  PBMP context);

        void applyAlphaMask(FastBitmap * mask);
        void applyAlphaMask(PBMP mask);
        void applyAlphaMask(String filename);

        void render();
        void render(FastBitmap * extContext);
        void render(PBMP extContext);
        void render(TCanvas * extContext);
        uint getMode(){return mode;}
        uint getColor(){return color;}
private:
        uint mode, color;
        bool selfMadeContext;
        FastBitmap * picture;
        FastBitmap * context;
        int left, top;

};

struct AnimationDescriptor
{
        AnimationDescriptor()
        {
                name="";
                firstFrame=lastFrame=0;
                animationTime=50;
        }
        AnimationDescriptor(AnimationDescriptor & c)
        {
                name=c.name;
                firstFrame=c.firstFrame;
                lastFrame = c.lastFrame;
                animationTime = c.animationTime;
        }
        AnimationDescriptor(String _name, uint ff, uint lf, uint t)
        {
                name = _name;
                firstFrame = ff;
                lastFrame = lf;
                animationTime = t;
        }
        ~AnimationDescriptor(){;}
        String name;
        uint firstFrame;
        uint lastFrame;
        uint animationTime;
};

class Sprite
{
public:
        friend class SpriteFabric;
        Sprite();
        ~Sprite();

        void loadFromFile(String filename);

        void setRenderMode(uint mode, uint color);
        void setContext(FastBitmap * c);
        FastBitmap * getContext();
        void addAnimation(String name, uint firstFrame, uint lastFrame, uint frameRate);
        void setAnimation(String name);
        void setAnimation(uint id);
        String getCurrentAnimationName();
        int getCurrentAnimationID();
        int getAnimationID(String name);
        bool isLastFrameInAnimation();


        bool update();
        void render();

        bool attach(String filename);
        void flush();

        TRect getRect();
        TDoubleRect getDoubleRect();
        void setPosition(double left, double top);

        bool isSpriteCollision(Sprite * s);
        bool isCursorCollision(int curX, int curY);

        bool operator<(Sprite &s) {return z<s.z;}
        uint getAnimationCount() {return animationCount;}
        uint getFramesCount() {return frCount;}

        uint z, id;
        bool allowAttachment;
        bool animate;
        AnimationDescriptor * animations;

private:

        void applyEffects(Defines &defs, String effectsList, uint mode, uint color);
        FastBitmap * frames;
        RenderObject picture;
        FastBitmap * context;

        uint currentAnimation;
        uint animationCount;
        uint currentFrame;
        uint lastTimeUpdated;
        uint frCount;
        int width, height;
        double left, top;
};

class SpriteFabric
{
        SpriteFabric(){;}
        ~SpriteFabric(){;}
        static TStringList * decomp(String c, char delimeter);

public:
        static void scan();
        static Sprite * newSprite(String composition, FastBitmap * context);
        static Sprite * copySprite(Sprite * src);
        static Sprite * newInstanceOf(Sprite * src);

};

class RenderManager
{
public:
        RenderManager(){id=0; context=0; output=0;}
        ~RenderManager(){;}

        void setContext(FastBitmap * ct, TCanvas* out, uint width, uint height, uint color);
        uint add(Sprite * s);
        void remove(uint id);
        void remove(Sprite *s);
        uint render();
        uint getColor(){return c;}
private:
        uint getId();
        uint id;
        std::list<Sprite*> sprites;

        FastBitmap * context;
        TCanvas * output;
        uint w,h,c;
};



//---------------------------------------------------------------------------
#endif

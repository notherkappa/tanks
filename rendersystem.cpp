//---------------------------------------------------------------------------


#pragma hdrstop

#include "rendersystem.h"
RenderObject::RenderObject()
{
        mode = RM_NORMAL;
        selfMadeContext = false;
        context = 0;
        picture = 0;
        left=top=0;
}
RenderObject::~RenderObject()
{
        if (selfMadeContext && context)
                delete context;
}
void RenderObject::assign(FastBitmap * fb)
{
        picture=fb;
}
void RenderObject::assign(PBMP bmp)
{
        picture = new FastBitmap();
        picture->init(bmp);
        selfMadeContext = true;
}
void RenderObject::assign(String file)
{
        PBMP b = new BMP();
        b->LoadFromFile(file);
        picture = new FastBitmap();
        picture->init(b);
}
void RenderObject::setRenderMode(uint m, uint clr)
{
        mode=m;
        color=clr;
}
void RenderObject::setContext(FastBitmap *c)
{
        if (selfMadeContext && context)
                delete context;
        context = c;
        selfMadeContext = false;
}
void RenderObject::setPosition(int l, int t)
{
        left = l;
        top = t;
}
void RenderObject::init(FastBitmap * pic, FastBitmap *c)
{
        picture = pic;
        selfMadeContext = false;
        context = c;
}
void RenderObject::init(PBMP pic, FastBitmap *c)
{
        if (selfMadeContext && context)
                delete context;
        picture = new FastBitmap();
        picture->init(pic);
        context = c;
        selfMadeContext = false;
}
void RenderObject::init(String filename,  FastBitmap *c)
{
        if (selfMadeContext && context)
                delete context;
        PBMP b = new BMP();
        b->LoadFromFile(filename);
        picture = new FastBitmap();
        picture->init(b);
        context=c;
}
void RenderObject::init(FastBitmap * pic, PBMP c)
{
        if (selfMadeContext && context)
                delete context;
        context = new FastBitmap();
        context->init(c);
        selfMadeContext = true;
        picture = pic;
}
void RenderObject::init(PBMP pic, PBMP c)
{
        if (selfMadeContext && context)
                delete context;
        context = new FastBitmap();
        context->init(c);
        selfMadeContext = true;
        picture = new FastBitmap();
        picture->init(pic);
}
void RenderObject::init(String filename,  PBMP c)
{
        if (selfMadeContext && context)
                delete context;
        context = new FastBitmap();
        context->init(c);
        selfMadeContext = true;

        PBMP p = new BMP();
        p->LoadFromFile(filename);
        picture = new FastBitmap();
        picture->init(p);
}
void RenderObject::applyAlphaMask(FastBitmap * mask)
{
        if (picture == 0)
                return;
        for (int i=0; i<picture->b->Width; i++)
                for (int j=0; j<picture->b->Height; j++)
                {
                        uint m = mask->getPixel(i,j);
                        uint pp = picture->getPixel(i,j);
                        picture->setPixel(i,j,
                                        ((m&0xFF)*(pp&0xFF)/255) |
                                        (((((m&0xFF00)>>8)*((pp&0xFF00)>>8)/255))<<8) |
                                        (((((m&0xFF0000)>>16)*((pp&0xFF0000)>>16)/255))<<16));

                }
}
void RenderObject::applyAlphaMask(PBMP pmask)
{
        if (picture == 0)
                return;
        FastBitmap * mask = new FastBitmap();
        mask->init(pmask);
        for (int i=0; i<picture->b->Width; i++)
                for (int j=0; j<picture->b->Height; j++)
                {
                        uint m = mask->getPixel(i,j);
                        uint pp = picture->getPixel(i,j);
                        picture->setPixel(i,j,
                                        ((m&0xFF)*(pp&0xFF)/255) |
                                        (((((m&0xFF00)>>8)*((pp&0xFF00)>>8)/255))<<8) |
                                        (((((m&0xFF0000)>>16)*((pp&0xFF0000)>>16)/255))<<16));
                }
}
void RenderObject::applyAlphaMask(String filename)
{
        if (picture == 0)
                return;
        PBMP pmask = new BMP();
        pmask->LoadFromFile(filename);
        FastBitmap * mask = new FastBitmap();
        mask->init(pmask);
        for (int i=0; i<picture->b->Width; i++)
                for (int j=0; j<picture->b->Height; j++)
                {
                        uint m = mask->getPixel(i,j);
                        uint pp = picture->getPixel(i,j);
                        picture->setPixel(i,j,
                                        ((m&0xFF)*(pp&0xFF)/255) |
                                        (((((m&0xFF00)>>8)*((pp&0xFF00)>>8)/255))<<8) |
                                        (((((m&0xFF0000)>>16)*((pp&0xFF0000)>>16)/255))<<16));
                }
}
void RenderObject::render()
{
        switch (mode)
        {
        case RM_NORMAL:
        default:
                context->b->Canvas->CopyRect(
                        Rect(left,top,left+picture->b->Width, top+picture->b->Height),
                        picture->b->Canvas,
                        Rect(0,0,picture->b->Width, picture->b->Height));
                break;
        case RM_ALPHA_MASK:
                for (int i=0; i<picture->b->Width; i++)
                        for (int j=0; j<picture->b->Height; j++)
                                if (picture->getPixel(i,j) !=color && (i+left)>=0 && (j+top)>=0 && (i+left<context->b->Width) && (j+top<context->b->Height))
                                        context->setPixel(i+left,j+top,picture->getPixel(i,j));
                break;
        case RM_OVERLAY:
                for (int i=0; i<picture->b->Width; i++)
                        for (int j=0; j<picture->b->Height; j++)
                                if (context->getPixel(i,j) ==color && (i-left)>=0 && (j-top)>=0 && (i+left<context->b->Width) && (j+top<context->b->Height))
                                        context->setPixel(i+left,j+top,picture->getPixel(i,j));
                break;
        }
}
void RenderObject::render(FastBitmap * extContext)
{
        switch (mode)
        {
        case RM_NORMAL:
        default:
                extContext->b->Canvas->CopyRect(
                        Rect(left,top,left+picture->b->Width, top+picture->b->Height),
                        picture->b->Canvas,
                        Rect(0,0,picture->b->Width, picture->b->Height));
                break;
        case RM_ALPHA_MASK:
                for (int i=0; i<picture->b->Width; i++)
                        for (int j=0; j<picture->b->Height; j++)
                                if (picture->getPixel(i,j) !=color && (i+left)>=0 && (j+top)>=0 && (i+left<extContext->b->Width) && (j+top<extContext->b->Height))
                                        extContext->setPixel(i+left,j+top,picture->getPixel(i,j));
                break;
        case RM_OVERLAY:
                for (int i=0; i<picture->b->Width; i++)
                        for (int j=0; j<picture->b->Height; j++)
                                if (extContext->getPixel(i,j) ==color && (i+left)>=0 && (j+top)>=0 && (i+left<extContext->b->Width) && (j+top<extContext->b->Height))
                                        extContext->setPixel(i+left,j+top,picture->getPixel(i,j));
                break;
        }
}
void RenderObject::render(PBMP extContext)
{
        extContext->Canvas->CopyRect(
                Rect(left,top,left+picture->b->Width, top+picture->b->Height),
                picture->b->Canvas,
                Rect(0,0,picture->b->Width, picture->b->Height));
}
void RenderObject::render(TCanvas* extContext)
{
        extContext->CopyRect(
                Rect(left,top,left+picture->b->Width, top+picture->b->Height),
                picture->b->Canvas,
                Rect(0,0,picture->b->Width, picture->b->Height));
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
Sprite::Sprite()
{
        frames = 0;
        context = 0;
        animations = new AnimationDescriptor[64];
        currentAnimation = 0;
        animationCount = 0;
        currentFrame = 0;
        lastTimeUpdated = 0;
        z = ZB_NORMAL;
        width=height=left=top=id=0;
        animate = true;
}
Sprite::~Sprite()
{
        flush();
        delete [] animations;
}
void Sprite::setRenderMode(uint mode, uint color)
{
        picture.setRenderMode(mode,color);
}
void Sprite::setContext(FastBitmap * c)
{
        context = c;
        picture.setContext(c);
}
FastBitmap * Sprite::getContext()
{
        return context;
}
void Sprite::addAnimation(String name, uint firstFrame, uint lastFrame, uint frameRate)
{
        if (animationCount<64)
        {
                animations[animationCount].name=name;
                animations[animationCount].firstFrame=firstFrame;
                animations[animationCount].lastFrame=lastFrame;
                animations[animationCount].animationTime=frameRate;
                animationCount++;
        }
}
void Sprite::setAnimation(String name)
{
        for (uint i=0; i<animationCount; i++)
                if (animations[i].name == name)
                {
                        currentAnimation = i;
                        lastTimeUpdated = 0;
                }

}
void Sprite::setAnimation(uint id)
{
        currentAnimation = id;
}
String Sprite::getCurrentAnimationName()
{
        return animations[currentAnimation].name;
}

int Sprite::getCurrentAnimationID()
{
        return currentAnimation;
}
int Sprite::getAnimationID(String name)
{
        for (uint i=0; i<animationCount;i++)
                if (animations[i].name==name)
                        return i;
        return -1;
}
bool Sprite::isLastFrameInAnimation()
{
        return currentFrame == animations[currentAnimation].lastFrame;
}
bool Sprite::update()
{
        if(!animate)
                return false;
        if (lastTimeUpdated == 0)
        {
                lastTimeUpdated = ::GetTickCount();
                currentFrame = animations[currentAnimation].firstFrame;
                return true;
        }
        uint timeLapsed = ::GetTickCount() - lastTimeUpdated;
        if (timeLapsed>animations[currentAnimation].animationTime)
        {
                if (currentFrame >= animations[currentAnimation].lastFrame)
                        currentFrame = animations[currentAnimation].firstFrame;
                else
                        currentFrame++;
                lastTimeUpdated = ::GetTickCount();
                return true;
        }
        return false;
}
void Sprite::render()
{
        picture.assign(&frames[currentFrame]);
        picture.render();
}
TRect Sprite::getRect()
{
        TRect r;
        r.left = left;
        r.top = top;
        r.right = left+width;
        r.bottom = top+height;
        return r;
}
TDoubleRect Sprite::getDoubleRect()
{
        TDoubleRect r;
        r.left = left;
        r.top = top;
        r.right = left+width;
        r.bottom = top+height;
        return r;
}
void Sprite::setPosition(double l, double t)
{
        left = l;
        top = t;
        picture.setPosition(left,top);
}
bool Sprite::isSpriteCollision(Sprite * s)
{
        TRect sr = s->getRect();
        TRect r = getRect();
        return rectCollision(convertRect(sr),convertRect(r));
}
bool Sprite::isCursorCollision(int curX, int curY)
{
        TRect r = getRect();
        return valueInRange(curX,r.left,r.right) && valueInRange(curY,r.top,r.bottom);
}

void Sprite::loadFromFile(String filename)
{
        Defines d;
        d.Load(filename);
        if (!(d.IsDefined("defines") && d.IsDefined("spriteconfig")))
                return;
        if (d.Get("type")=="attachment")
                return;

        String prefix = d.IsDefined("registername") ?
                        ("sprites\\res\\"+d.Get("registername")+".sprite\\") :
                        String("");
        int w = StrToInt(d.Get("w"));
        int h = StrToInt(d.Get("h"));


        PBMP allFrames = new BMP();
        allFrames->LoadFromFile(prefix+d.Get("spritesrc"));
        int framesCount = allFrames->Width/w;
        PBMP * bmpFrames = new PBMP[framesCount];
        frames = new FastBitmap[framesCount];
        frCount = framesCount;
        for (int i=0; i<framesCount; i++)
        {
                bmpFrames[i] = new BMP();
                bmpFrames[i]->Width  = w;
                bmpFrames[i]->Height = h;
                bmpFrames[i]->Canvas->CopyRect(Rect(0,0,w,h),
                                               allFrames->Canvas,
                                               Rect(w*i,0,w*i+w,h));
                frames[i].init(bmpFrames[i]);
        }
        delete allFrames;

        z = StrToInt(d.Get("z"));
        width=w;
        height=h;

        String modeString = d.Get("mode");
        int iMode=0;
        if (modeString == "alpha")
                iMode = RM_ALPHA_MASK;
        else if (modeString == "overlay")
                iMode = RM_OVERLAY;

        picture.setRenderMode(iMode,StrToInt(d.Get("color")));

        TStringList * aList = d.GetList("animationlist");
        for (int i=0; i<aList->Count; i++)
        {
                String name = aList->Strings[i];
                int ff = StrToInt(d.Get("animations."+name+".firstFrame"));
                int lf = StrToInt(d.Get("animations."+name+".lastFrame"));
                int at = StrToInt(d.Get("animations."+name+".animationTime"));
                this->addAnimation(name,ff,lf,at);
        }
        delete aList;

        allowAttachment = true;
}

bool Sprite::attach(String filename)
{
        Defines d;
        d.Load(filename);
        if (!(d.IsDefined("defines") && d.IsDefined("spriteconfig")))
                return false;
        if (d.Get("type")!="attachment")
                return false;


         String prefix = d.IsDefined("registername") ?
                        ("sprites\\res\\"+d.Get("registername")+".sprite\\") :
                        String("");

        int w = StrToInt(d.Get("w"));
        int h = StrToInt(d.Get("h"));
        int c = StrToInt(d.Get("color"));

        String modeString = d.Get("mode");
        int m=0;
        if (modeString == "alpha")
                m = RM_ALPHA_MASK;
        else if (modeString == "overlay")
                m = RM_OVERLAY;


        if (!d.IsDefined("nofx"))
                applyEffects(d,"prefx",m,c);

        if (d.IsDefined("spritesrc"))
        {
                PBMP allFrames = new BMP();
                allFrames->LoadFromFile(prefix+d.Get("spritesrc"));
                int framesCount = allFrames->Width/w;
                PBMP * bmpFrames = new PBMP[framesCount];
                FastBitmap * attachFrames = new FastBitmap[framesCount];
                RenderObject pic;
                pic.setRenderMode(m,c);
                for (int i=0; i<framesCount; i++)
                {
                        bmpFrames[i] = new BMP();
                        bmpFrames[i]->Width  = w;
                        bmpFrames[i]->Height = h;
                        bmpFrames[i]->Canvas->CopyRect(Rect(0,0,w,h),
                                                       allFrames->Canvas,
                                                       Rect(w*i,0,w*i+w,h));
                        attachFrames[i].init(bmpFrames[i]);
                        pic.init(&attachFrames[i],&frames[i]);
                        pic.render();
                }
                delete [] attachFrames;
                delete [] bmpFrames;
                delete allFrames;
        }
        if (!d.IsDefined("nofx"))
                applyEffects(d,"postfx",m,c);
        return true;
}

void Sprite::applyEffects(Defines &d, String effectsList, uint m, uint c)
{
        TStringList * fx = d.GetList(effectsList);
        for (int i=0; i<fx->Count; i++)
        {
                String name = fx->Strings[i];
                String op = d.Get(effectsList+"."+name+".id");
                if (op == "crp")
                {
                        uint changeColor = StrToInt(d.Get(effectsList+"."+name+".replace"));
                        uint replaceColor= StrToInt(d.Get(effectsList+"."+name+".with"));
                        for (uint i=0; i<frCount; i++)
                                frames[i].replaceColor(changeColor,replaceColor, m!=RM_NORMAL, c);
                }
                else if (op == "mul")
                {
                        uint mulValue = StrToInt(d.Get(effectsList+"."+name+".value"));
                        for (uint i=0; i<frCount; i++)
                                frames[i].multiply(mulValue,m!=RM_NORMAL,c);
                }
                else if (op == "add")
                {
                        uint addValue = StrToInt(d.Get(effectsList+"."+name+".value"));
                        for (uint i=0; i<frCount; i++)
                                frames[i].addValue(addValue,m!=RM_NORMAL,c);
                }
                else if (op == "col")
                {
                        uint cValue = StrToInt(d.Get(effectsList+"."+name+".center"));
                        uint dValue = StrToInt(d.Get(effectsList+"."+name+".degree"));
                        for (uint i=0; i<frCount; i++)
                                frames[i].transformContrastLowerTo(cValue, dValue, m !=RM_NORMAL, c);
                }
                else if (op == "coh")
                {
                        uint cValue = StrToInt(d.Get(effectsList+"."+name+".center"));
                        uint dValue = StrToInt(d.Get(effectsList+"."+name+".degree"));
                        for (uint i=0; i<frCount; i++)
                                frames[i].transformContrastHigherTo(cValue, dValue, m !=RM_NORMAL, c);
                }
                else if (op == "inv")
                        for (uint i=0; i<frCount; i++)
                                frames[i].invert(m!=RM_NORMAL,c);
                else if (op == "alp")
                {
                        uint aColor = StrToInt(d.Get(effectsList+"."+name+".color"));
                        uint opacity = StrToInt(d.Get(effectsList+"."+name+".opacity"));
                        for (uint i=0; i<frCount; i++)
                                frames[i].alphaColor(aColor,opacity,m!=RM_NORMAL,c);
                }
        }
}

void Sprite::flush()
{
        for (uint i=0; i<frCount; i++)
                delete frames[i].b;
        delete [] frames;
}

//---------------------------------------------------------------------------
void SpriteFabric::scan()
{
        TStringList * bat = new TStringList();
        bat->Add("dir /b sprites\\*.sprite>sprites\\last_fabric_scan.list");
        bat->SaveToFile("fabricScan.bat");
        ShellExecute(0,"open", "fabricScan.bat",0,0,SW_HIDE);
        Sleep(uint(600));
        bat->LoadFromFile("sprites\\last_fabric_scan.list");
        Defines spDefines, fbDefines;
        for (int i=0; i<bat->Count; i++)
        {
                spDefines.Load("sprites\\"+bat->Strings[i]);
                if (spDefines.IsDefined("registername"))
                        fbDefines.Set(spDefines.Get("registername"), "sprites\\"+bat->Strings[i]);
        }
        fbDefines.Save("sprites\\fbDefines.fabric");
        DeleteFile("fabricScan.bat");
        DeleteFile("sprites\\last_fabric_scan.list");
        delete bat;
}
TStringList * SpriteFabric::decomp(String c, char d)
{
        char *srcString = c.c_str();
        char *tmpString = new char [c.Length()];
        TStringList * words = new TStringList();
        int index=0, tIndex=0;
        memset(tmpString,0,c.Length());
        for (; index<c.Length(); index++)
        {
                if (srcString[index]==d)
                        if (index==0)
                        {
                                delete[] tmpString;
                                delete words;
                                return 0;
                        }
                        else
                        {
                                words->Add(tmpString);
                                memset(tmpString,0,c.Length());
                                tIndex=0;
                        }
                else
                {
                        tmpString[tIndex]=srcString[index];
                        tIndex++;
                }
        }
        if (tIndex!=0)
                words->Add(tmpString);
        delete [] tmpString;
        return words;
}

Sprite * SpriteFabric::newSprite(String comp, FastBitmap * context)
{
        TStringList * parts=new TStringList();
        parts->Delimiter= '+';
        parts->DelimitedText = comp;
        if (parts == 0)
                return 0;
        Sprite *s = new Sprite();
        s->setContext(context);
        if (!FileExists("sprites\\fbDefines.fabric"))
                scan();
        Defines d;
        d.Load("sprites\\fbDefines.fabric");
        s->loadFromFile(d.Get(parts->Strings[0]));
        for (int i=1; i<parts->Count; i++)
                s->attach(d.Get(parts->Strings[i]));
        delete parts;
        return s;
}
Sprite * SpriteFabric::copySprite(Sprite * src)
{
        Sprite *s = new Sprite();
        s->setContext(src->context);
        for (uint i=0; i<src->animationCount; i++)
                s->addAnimation(src->animations[i].name,
                                src->animations[i].firstFrame,
                                src->animations[i].lastFrame,
                                src->animations[i].animationTime);
        TRect sr = src->getRect();
        int w = sr.right-sr.left;
        int h = sr.bottom-sr.top;
        PBMP * bmpframes = new PBMP[src->frCount];
        s->frames = new FastBitmap[src->frCount];
        for (uint i=0; i<src->frCount; i++)
        {
                bmpframes[i] = new BMP();
                bmpframes[i]->Width = w;
                bmpframes[i]->Height = h;
                bmpframes[i]->Canvas->CopyRect(Rect(0,0,w,h),
                                               src->frames[i].b->Canvas,
                                               Rect(0,0,w,h));
                s->frames[i].init(bmpframes[i]);
        }
        s->setAnimation(src->getCurrentAnimationName());
        s->setPosition(sr.left,sr.top);
        s->setRenderMode(src->picture.getMode(),src->picture.getColor());
        s->currentAnimation = src->currentAnimation;
        s->currentFrame = src->currentFrame;
        s->lastTimeUpdated = src->lastTimeUpdated;
        s->animate = src->animate;
        s->z = src->z;
        s->allowAttachment = src->allowAttachment;
        s->frCount = src->frCount;
        s->width = w;
        s->height = h;
        return s;
}
Sprite * SpriteFabric::newInstanceOf(Sprite * src)
{
        Sprite *s = new Sprite();
        s->setContext(src->context);
        for (uint i=0; i<src->animationCount; i++)
                s->addAnimation(src->animations[i].name,
                                src->animations[i].firstFrame,
                                src->animations[i].lastFrame,
                                src->animations[i].animationTime);
        TRect sr = src->getRect();
        int w = sr.right-sr.left;
        int h = sr.bottom-sr.top;
        PBMP * bmpframes = new PBMP[src->frCount];
        s->frames = new FastBitmap[src->frCount];
        for (uint i=0; i<src->frCount; i++)
        {
                bmpframes[i] = new BMP();
                bmpframes[i]->Width = w;
                bmpframes[i]->Height = h;
                bmpframes[i]->Canvas->CopyRect(Rect(0,0,w,h),
                                               src->frames[i].b->Canvas,
                                               Rect(0,0,w,h));
                s->frames[i].init(bmpframes[i]);
        }
        s->setAnimation(0);
        s->setRenderMode(src->picture.getMode(),src->picture.getColor());
        s->z = src->z;
        s->frCount = src->frCount;
        s->width = w;
        s->height = h;
        return s;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
uint RenderManager::add(Sprite * s)
{
        sprites.push_back(s);
        sprites.sort();
        sprites.reverse();
        s->id = getId();
        return s->id;
}
void RenderManager::remove(uint id)
{
        std::list<Sprite*>::iterator i = sprites.begin();
        for (; i!=sprites.end(); ++i)
                if ((*i)->id == id)
                        sprites.remove(*i);
}
void RenderManager::remove(Sprite *s)
{
        sprites.remove(s);
}
uint RenderManager::render()
{
        uint startTime = ::GetTickCount();
        if (context)
                context->b->Canvas->FillRect(Rect(0,0,w,h));
        for (std::list<Sprite*>::iterator i = sprites.begin(); i!=sprites.end(); ++i)
        {
                (*i)->update();
                (*i)->render();
        }
        if (output && context)
                output->CopyRect(Rect(0,0,w,h), context->b->Canvas, Rect(0,0,w,h));
        return ::GetTickCount()-startTime;
}
uint RenderManager::getId()
{
        id++;
        return id;
}
void RenderManager::setContext(FastBitmap * ct, TCanvas* out, uint width, uint height, uint color)
{
        context = ct;
        output = out;
        w=width;
        h=height;
        c=color;
        context->b->Canvas->Brush->Color = c;
}
//---------------------------------------------------------------------------

#pragma package(smart_init)

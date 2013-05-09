//---------------------------------------------------------------------------

#ifndef fastbitmapH
#define fastbitmapH
#include <vcl.h>
#include <graphics.hpp>
#include "logic.h"
#define PBMP Graphics::TBitmap *
#define BMP  Graphics::TBitmap
#define PIXEL(i) rgb24pixel::fromInt(i)
#define PIXELRGB(r,g,b) rgb24pixel::fromRGB(r, g, b)
struct rgb24pixel
{
        byte b,g,r;
        uint toInt() {return (b<<16)|(g<<8)|r;}
        void setFromInt(uint c){r = c&0xFF; g = (c&0xFF00)>>8; b = (c&0xFF0000)>>16;}
        static rgb24pixel fromInt (uint c);
        static rgb24pixel fromRGB (byte r, byte g, byte b);
};
class FastBitmap
{
public:
        FastBitmap();
        FastBitmap(PBMP src);
        ~FastBitmap();
        void init(PBMP src);
        uint getPixel(uint left, uint top);
        void setPixel(uint left, uint top, uint pixel);

        //effects
        void replaceColor(uint toChange, uint destColor, bool useExceptColor=false, uint exceptColor=0);
        void multiply(uint mulValue, bool useExceptColor=false, uint exceptColor=0, uint delValue=1024);
        void addValue(int addValue, bool useExceptColor=false, uint exceptColor=0);
        void transformContrastLowerTo(uint centerValue, uint degree, bool useExceptColor=false, uint exceptColor=0);
        void transformContrastHigherTo(uint centerValue, uint degree, bool useExceptColor=false, uint exceptColor=0);
        void invert(uint useExceptColor=false, uint exceptColor=0);
        void alphaColor(uint color, uint opacity, bool useExceptColor=false, uint exceptColor=0);


        //
        PBMP b;
private:
        rgb24pixel ** pixels;
};

//---------------------------------------------------------------------------
#endif

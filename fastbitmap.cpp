//---------------------------------------------------------------------------


#pragma hdrstop

#include "fastbitmap.h"
rgb24pixel rgb24pixel::fromInt (uint c)
{
        rgb24pixel r;
        r.r = c&0xFF;
        r.g = (c&0xFF00)>>8;
        r.b = (c&0xFF0000)>>16;
        return r;
}
rgb24pixel rgb24pixel::fromRGB (byte r, byte g, byte b)
{
        rgb24pixel res;
        res.r=r;
        res.g=g;
        res.b=b;
        return res;
}
FastBitmap::FastBitmap()
{
        b = 0;
        pixels = 0;
}
FastBitmap::FastBitmap(PBMP src)
{
        b=0;
        pixels = 0;
        init(src);
}
FastBitmap::~FastBitmap()
{
        if (pixels)
                delete[]pixels;
}
void FastBitmap::init(PBMP src)
{
        src->PixelFormat = pf24bit;
        b = src;
        if (pixels)
                delete[]pixels;
        pixels = new rgb24pixel*[b->Height];
        for (int i=0; i<b->Height; i++)
                pixels[i] = (rgb24pixel*)b->ScanLine[i];
}
uint FastBitmap::getPixel(uint left, uint top)
{
        if (!pixels)
                return -1;
        else
                return pixels[top][left].toInt();
}
void FastBitmap::setPixel(uint left, uint top, uint c)
{
        if (!pixels)
                return;
        pixels[top][left] = rgb24pixel::fromInt(c);
}
void FastBitmap::replaceColor(uint toChange, uint destColor, bool useExceptColor, uint exceptColor)
{
        for (int i=0; i<b->Width; i++)
                for (int j=0; j<b->Height; j++)
                        if ((pixels[j][i].toInt() == toChange) && ((pixels[j][i].toInt() != exceptColor) || (!useExceptColor)))
                                pixels[j][i] = rgb24pixel::fromInt(destColor);
}
void FastBitmap::multiply(uint mulValue, bool useExceptColor, uint exceptColor, uint delValue)
{
        for (int i=0; i<b->Width; i++)
                for (int j=0; j<b->Height; j++)
                        if (!useExceptColor || (pixels[j][i].toInt() != exceptColor))
                        {
                                pixels[j][i].b = pixels[j][i].b*mulValue/delValue;
                                pixels[j][i].g = pixels[j][i].g*mulValue/delValue;
                                pixels[j][i].r = pixels[j][i].r*mulValue/delValue;
                        }
}
void FastBitmap::addValue(int addValue, bool useExceptColor, uint exceptColor)
{
        for (int i=0; i<b->Width; i++)
                for (int j=0; j<b->Height; j++)
                        if (!useExceptColor || (pixels[j][i].toInt() != exceptColor))
                        {
                                pixels[j][i].b = pixels[j][i].b+addValue;
                                pixels[j][i].g = pixels[j][i].g+addValue;
                                pixels[j][i].r = pixels[j][i].r+addValue;
                        }
}
void FastBitmap::transformContrastLowerTo(uint centerValue, uint degree, bool useExceptColor, uint exceptColor)
{
        rgb24pixel center = rgb24pixel::fromInt(centerValue);
        for (int i=0; i<b->Width; i++)
                for (int j=0; j<b->Height; j++)
                        if (!useExceptColor || (pixels[j][i].toInt() != exceptColor))
                        {
                                pixels[j][i].b += (center.b-pixels[j][j].b)*degree/255;
                                pixels[j][i].g += (center.g-pixels[j][j].g)*degree/255;
                                pixels[j][i].r += (center.r-pixels[j][j].r)*degree/255;
                        }
}
void FastBitmap::transformContrastHigherTo(uint centerValue, uint degree, bool useExceptColor, uint exceptColor)
{
        rgb24pixel center = rgb24pixel::fromInt(centerValue);
        for (int i=0; i<b->Width; i++)
                for (int j=0; j<b->Height; j++)
                        if (!useExceptColor || (pixels[j][i].toInt() != exceptColor))
                        {
                                pixels[j][i].b += (255-abs(center.b-pixels[j][j].b))*degree/255;
                                pixels[j][i].g += (255-abs(center.g-pixels[j][j].g))*degree/255;
                                pixels[j][i].r += (255-abs(center.r-pixels[j][j].r))*degree/255;
                        }
}
void FastBitmap::invert(uint useExceptColor, uint exceptColor)
{
        for (int i=0; i<b->Width; i++)
                for (int j=0; j<b->Height; j++)
                        if (!useExceptColor || (pixels[j][i].toInt() != exceptColor))
                        {
                                pixels[j][i].b = 255-pixels[j][i].b;
                                pixels[j][i].g = 255-pixels[j][i].g;
                                pixels[j][i].r = 255-pixels[j][i].r;
                        }
}
void FastBitmap::alphaColor(uint color, uint opacity, bool useExceptColor, uint exceptColor)
{
        rgb24pixel p = rgb24pixel::fromInt(color);
        for (int i=0; i<b->Width; i++)
                for (int j=0; j<b->Height; j++)
                        if (!useExceptColor || (pixels[j][i].toInt() != exceptColor))
                        {
                                pixels[j][i].b = (p.b - pixels[j][i].b)*opacity/255 + pixels[j][i].b;
                                pixels[j][i].g = (p.g - pixels[j][i].g)*opacity/255 + pixels[j][i].g;
                                pixels[j][i].r = (p.r - pixels[j][i].r)*opacity/255 + pixels[j][i].r;
                        }
}



//---------------------------------------------------------------------------

#pragma package(smart_init)

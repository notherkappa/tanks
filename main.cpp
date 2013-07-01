//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int SIZE__L = 800, SIZE__T = 400;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
        SIZE__L = ClientWidth;
        SIZE__T = ClientHeight;
        b = new Graphics::TBitmap();
        b->Width = SIZE__L;
        b->Height = SIZE__T;
        fb.init(b);
        mode = 0;
        renderTestMode = false;

        PBMP ct = new BMP();
        ct->Width = 768;
        ct->Height = 512;
        ct->Canvas->Brush->Color = clBtnFace;
        ct->Canvas->FillRect(Rect(0,0,ClientWidth,ClientHeight));
        FastBitmap * fbC = new FastBitmap();
        fbC->init(ct);
        this->ts.ct=fbC;
        ts.s.setContext(ts.ct);


}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
        x=X;y=Y;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyPress(TObject *Sender, char &Key)
{
        if (Key == 'T')
        {
                renderTestMode = 1-renderTestMode;
                return;
        }
        else if (Key == 'E')
        {
                Form2->ShowModal();
        }
        else if (Key == 'R')
        {
                initGame();
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RenderTest(TCanvas * output, uint mode)
{
        GTimer->Enabled=false;
        static uint st,t;
        st= (Tag==0)?::GetTickCount():st;
        t = Tag==0?::GetTickCount():t;
        Caption ="TIME: "+ IntToStr(::GetTickCount()-t)+". FPS: "+FloatToStr(double(Tag)*1000/double((::GetTickCount()+1-st))).SetLength(5)+". TAG: "+Tag;
        TPoint p;
        for (int i=0; i<SIZE__L;i++)
        for (int j=0; j<SIZE__T;j++)
        {
                uint tmp;
                switch (mode)
                {
                case 0:
                default:
                        fb.setPixel(i,j, (i+j)*2+Tag);
                        break;
                case 1:
                        fb.setPixel(i,j,i*j-Tag);
                        break;
                case 2:
                        fb.setPixel(i,j,i*j+(i-1)*(j+SIZE__L)+Tag*i);
                        break;
                case 3:
                        fb.setPixel(i,j,(i-j)*j+(i+x)*(j-y)+2*(Tag%1000)*(y-j)-8*Tag);
                        break;
                case 4:
                        fb.setPixel(i,j,(i-j)*j+i*(i-j-1)+i*(j-i+1)+Tag*Tag + 0xFFFFFF/((x-i)==0?x-i+1:x-i)+ 0xFFFFFF/((y-i)==0?y-i+1:y-i));
                        break;
                case 5:
                        fb.setPixel(i,j,fb.getPixel(SIZE__L-i-1,SIZE__T-j-1)*i*j+Tag*i*j);
                        break;
                case 6:
                        fb.setPixel(i,j,double(fb.getPixel(SIZE__L-i-1,SIZE__T-j-1))*double(i-SIZE__L)/double(x));
                        break;
                case 7:
                        fb.setPixel(i,j, i*j<<random(16)+ i+j-(i%(j+1))*j*(j+255)/(Tag+1)+i*(Tag*Tag+i-255)+j);
                case 8:
                        fb.setPixel(i,j,double(fb.getPixel(SIZE__L-i-1,SIZE__T-j-1))*(0.1019-double(i-SIZE__L)/double(SIZE__L))
                                                                                    *(1.1617-double(j-SIZE__T)/double(SIZE__T)));
                        break;
                case 9:
                        fb.setPixel(i,j,double(fb.getPixel(SIZE__L-i-1,SIZE__T-j-1))*(0.5-double(i-SIZE__L)/double(SIZE__L))
                                                                                    *(0.5-double(j-SIZE__T)/double(SIZE__T))
                                                                                    *double(double(Tag%75)/66+0.65));
                        break;
                case 10:
                        tmp = random (2)+1;
                        fb.setPixel(i,j,(((fb.getPixel(x,y)&0xFF)+tmp*(Tag%4)+fb.getPixel(i,j)*Tag&0xFF)/2)|
                                        ((((fb.getPixel(x,y)&0xFF00)+tmp*(Tag%8)+fb.getPixel(i,j)*Tag&0xFF00)/3))|
                                        ((((fb.getPixel(x,y)&0xFF0000)+/*(tmp*Tag%16)*/+i*(j+y)+(x+Tag/1024)*y+fb.getPixel(i,j)&0xFF0000)/4)));
                        break;
                case 11:
                        tmp = random (2)+1;
                        fb.setPixel(i,j,(((fb.getPixel(x,y)&0xFF)+tmp*(Tag%4)-fb.getPixel(i,j)&0xFF)/2)|
                                        ((((fb.getPixel(x,y)&0xFF00)+tmp*(Tag%8)+fb.getPixel(i,j)*Tag&0xFF00)/3))|
                                        ((((fb.getPixel(x,y)&0xFF0000)+(tmp*Tag%16)+(i-x+y)*(j+y)+(x+Tag/1024)*y+fb.getPixel(i,j)&0xFF0000)/4)));
                        break;

                }
        }
        Canvas->CopyRect(Rect(0,0,SIZE__L,SIZE__T),b->Canvas,Rect(0,0,SIZE__L,SIZE__T));
        Tag++;
        t = ::GetTickCount();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::RenderTestTimerrTimer(TObject *Sender)
{
        static count;
        static m=0;
        if (renderTestMode)
        {
                RenderTest(Canvas, m);
                if (count>=50)
                {
                        m+=1;
                        count=0;
                        if (m == 12)
                        {
                                renderTestMode = false;
                                ShowMessage("RENDER TEST IS OVER");
                                GTimer->Enabled=true;
                        }
                        m%=12;
                }
                else
                        count++;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        spriteTest();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::spriteTest()
{
        uint ttt=::GetTickCount();
        ts.ct->b->Canvas->FillRect(Rect(0,0,ClientWidth,ClientHeight));
        ts.s.update();
        ts.s.render();
        Canvas->CopyRect(Rect(0,0,ClientWidth,ClientHeight),ts.ct->b->Canvas,
                              Rect(0,0,ClientWidth,ClientHeight));
        Caption=IntToStr(::GetTickCount()-ttt);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
        spriteTest();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::GTimerTimer(TObject *Sender)
{
        gt.gm->launchGameCycle();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormActivate(TObject *Sender)
{
        if (GTimer->Tag == 0)
        {
                initGame();
                GTimer->Tag=1;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        DeleteFile("sprites\\fbDefines.fabric");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        UserStats * us = UserStats::getInstance();
        us->scores++;
        us->print(Label2,Label3,Label1,Label4, ProgressBar1, Label5);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::initGame()
{
        gt.rm = new RenderManager();
        gt.rm->setContext(ts.ct,Canvas,SIZE__L, SIZE__T, clGray);
        gt.gm = new GameManager();
        gt.gm->setRenderManager(gt.rm);

        SpriteFabric * sf = SpriteFabric::getInstance();
        Defines globalConfig;
        globalConfig.Load("userdata\\global.cfg");
        TStringList * cachedSprites = globalConfig.GetList("cachedsprites");
        for (int i=0; i<cachedSprites->Count; i++)
                sf->addSpriteToCache(cachedSprites->Strings[i]);

        gt.map.load("maps\\temp.map");
        gt.map.generateObjects(gt.gm,ts.ct);
        UserStats * us = UserStats::getInstance();
        us->levelName = gt.map.getLevelName();
        us->livesCount=3;
        us->print(Label2,Label3,Label1,Label4,ProgressBar1, Label5);
        GTimer->Enabled=true;
        Timer2->Enabled=true;
        delete cachedSprites;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
        UserStats * us = UserStats::getInstance();
        if (us->hp<=0)
        {
                us->livesCount--;
                if (us->livesCount<0)
                {
                        us->gameOver=true;
                        GTimer->Enabled = false;
                        Timer2->Enabled = false;
                        ShowMessage("Game Over.");
                }
                else
                        us->hp=100;
        }
        
        us->print(Label2,Label3,Label1,Label4, ProgressBar1, Label5);

}
//---------------------------------------------------------------------------


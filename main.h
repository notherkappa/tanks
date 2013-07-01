//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "gamesystem.h"
#include "customTanks.h"
#include "customWalls.h"
#include "customBullets.h"
#include "defines.h"
#include "mapCreator.h"
#include "stats.h"
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TTimer *RenderTestTimerr;
        TTimer *Timer1;
        TTimer *GTimer;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TTimer *Timer2;
        TProgressBar *ProgressBar1;
        TLabel *Label5;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall FormKeyPress(TObject *Sender, char &Key);
        void __fastcall RenderTestTimerrTimer(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall GTimerTimer(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void __fastcall RenderTest(TCanvas * output, uint mode);
        void __fastcall spriteTest();
        void __fastcall initGame();

        bool renderTestMode;
        PBMP b;
        FastBitmap fb;
        uint x, y;
        uint mode;

        struct TestSprite
        {
                Sprite s;
                FastBitmap * ct;
        } ts;

        struct GameCycleTest
        {
                RenderManager * rm;
                GameManager * gm;
                GameMap map;
        } gt;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#ifndef mapCreatorH
#define mapCreatorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <list>
#include "objectdefines.h"
#include "customWalls.h"
#include "customBullets.h"
#include "customTanks.h"
#include "defines.h"
#include "gamesystem.h"
#include "logic.h"
#include "map.h"
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall GroupBox1Click(TObject *Sender);
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall FormClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm2(TComponent* Owner);

        void __fastcall buildEditorInterface();
        void __fastcall PaletteClick(TObject *Sender);

        int pickedItem;
        GameMap map;
        std::list<PBMP>palette;
        int cLeft, cTop;
        PBMP context;
        PBMP cursorContext;
        PBMP paletteItem;

};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif

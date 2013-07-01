//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mapCreator.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::buildEditorInterface()
{
        Defines d;
        d.Load("maps\\mapeditor.cfg");
        TStringList * objects = d.GetList("objects");
        for (int i=0; i<objects->Count; i++)
        {
                PBMP bmpImg = new BMP();
                TImage * img = new TImage(this);
                img->Parent = GroupBox1;
                Defines sp;

                sp.Load("sprites\\"+d.Get("objects."+objects->Strings[i]+".sprite"));

                String filespr ="sprites\\res\\"+sp.Get("registername")+".sprite\\"+sp.Get("spritesrc");
                img->Picture->LoadFromFile(filespr);
                bmpImg->LoadFromFile(filespr);
                img->Tag = i+1;
                img->Left = (i%4)*32+4;
                img->Top = (i/4)*32+16;
                img->Width=StrToInt(sp.Get("w"));
                img->Height=StrToInt(sp.Get("h"));
                bmpImg->Width=StrToInt(sp.Get("w"));
                bmpImg->Height=StrToInt(sp.Get("h"));
                img->OnClick = PaletteClick;
                palette.push_back(bmpImg);
                context = new BMP();
                context->Canvas->Brush->Color=clSilver;
                context->Width = ClientWidth;
                context->Height = ClientHeight;
                context->Canvas->FillRect(Rect(0,0,ClientWidth,ClientHeight));

                cursorContext = new BMP();
                cursorContext->Width = ClientWidth;
                cursorContext->Height = ClientHeight;

                paletteItem = new BMP();
                paletteItem->Width = 32;
                paletteItem->Height = 32;


                DoubleBuffered=true;
                GameMap * gm = new GameMap();
                map = *gm;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormActivate(TObject *Sender)
{
        buildEditorInterface();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::PaletteClick(TObject *Sender)
{
        pickedItem = ((TImage*)Sender)->Tag;
        int ii=0;
        for (std::list<PBMP>::iterator i=palette.begin(); i!=palette.end();i++,ii++)
                if (ii==pickedItem-1)
                {
                        paletteItem->Canvas->Brush->Color=clSilver;
                        paletteItem->Canvas->FillRect(Rect(0,0,32,32));
                        paletteItem->Canvas->CopyRect(Rect(0,0,32,32), (*i)->Canvas, Rect(0,0,32,32));
                }

}
//---------------------------------------------------------------------------
void __fastcall TForm2::GroupBox1Click(TObject *Sender)
{
        pickedItem=0;
        paletteItem->Canvas->Brush->Color=clSilver;
        paletteItem->Canvas->FillRect(Rect(0,0,32,32));
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
        cursorContext->Canvas->CopyRect(Rect(0,0,ClientWidth,ClientHeight),context->Canvas,Rect(0,0,ClientWidth,ClientHeight));
        int posX = (X-paletteItem->Width/2+16)/32*32;
        int posY = (Y-paletteItem->Height/2+16)/32*32;
        cursorContext->Canvas->CopyRect(Rect(posX,posY,posX+32,posY+32), paletteItem->Canvas, Rect(0,0,32,32));
        Canvas->CopyRect(Rect(0,0,ClientWidth,ClientHeight),cursorContext->Canvas,Rect(0,0,ClientWidth,ClientHeight));
        cLeft = posX;
        cTop  = posY;
}
//---------------------------------------------------------------------------


void __fastcall TForm2::FormClick(TObject *Sender)
{
        if (pickedItem!=0)
        {
                Defines ed;
                ed.Load("maps\\mapeditor.cfg");
                TStringList * l = ed.GetList("objects");
                map.addObject(l->Strings[pickedItem-1]+":"+IntToStr(::GetTickCount())+":"+IntToStr(random(0xFFFFFF)), StrToInt(ed.Get("objects."+l->Strings[pickedItem-1]+".id")),cLeft,cTop);
                int ii=0;
                for (std::list<PBMP>::iterator i=palette.begin(); i!=palette.end();i++,ii++)
                        if (ii==pickedItem-1)
                                context->Canvas->CopyRect(Rect(cLeft,cTop,cLeft+32, cTop+32),(*i)->Canvas,Rect(0,0,32,32));
                delete l;
                map.save("maps\\temp.map", " 1");
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Button1Click(TObject *Sender)
{
        Form1->GTimer->Enabled=false;
        if (OpenDialog1->Execute())
        {
                SetCurrentDir(ExtractFilePath(Application->ExeName));
                LabeledEdit1->Text = StringReplace(ExtractFileName(OpenDialog1->FileName),
                                                   ".sprite","",TReplaceFlags()<<rfIgnoreCase<<rfReplaceAll);
                TStringList * l = map.map.GetList("sprites");
                if (l==0)
                        map.map.SetList("sprites",new TStringList());
                String name = LabeledEdit1->Text+IntToStr(::GetTickCount())+IntToStr(random(0xffffff));
                map.map.AddToList("sprites",name );
                map.map.Set("sprites."+name+".left", LabeledEdit2->Text);
                map.map.Set("sprites."+name+".top", LabeledEdit3->Text);
                map.map.Set("sprites."+name+".sprite", LabeledEdit1->Text+".sprite");
                map.map.Set("sprites."+name+".animation", LabeledEdit4->Text);
                if (!CheckBox1->Checked)
                        map.map.Define("sprites."+name+".dontanimate");
                ListBox1->Items->Add(LabeledEdit1->Text);
                map.save("maps\\temp.map", " 1");
        }
        Form1->GTimer->Enabled=true;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *tlo;
        TMainMenu *MainMenu1;
        TMenuItem *Opcje1;
        TMenuItem *Opis1;
        TMenuItem *Zapiszgre1;
        TMenuItem *N1;
        TMenuItem *Zakocz1;
        TMenuItem *Pomoc1;
        TMenuItem *Informacje1;
        TMenuItem *Oprogramie1;
        TMenuItem *Autor1;
        TLabel *namePlayer1;
        TLabel *score;
        TLabel *namePlayer2;
        TShape *ball;
        TShape *p1;
        TShape *p2;
        TTimer *up1;
        TTimer *down1;
        TTimer *up2;
        TTimer *down2;
        void __fastcall up1Timer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall down1Timer(TObject *Sender);
        void __fastcall up2Timer(TObject *Sender);
        void __fastcall down2Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

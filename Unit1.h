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
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

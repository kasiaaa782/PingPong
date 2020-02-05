//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------





/*
void __fastcall TForm1::lewoTimer(TObject *Sender)
{
     if(paddle->Left > 10 ) paddle->Left -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::prawoTimer(TObject *Sender)
{
     if(paddle->Left + paddle->Width < tlo->Width - 10 ) paddle->Left += 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     if(Key == VK_LEFT) lewo->Enabled = true;
     if(Key == VK_RIGHT) prawo->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     if(Key == VK_LEFT) lewo->Enabled = false;
     if(Key == VK_RIGHT) prawo->Enabled = false;

*/

void __fastcall TForm1::up1Timer(TObject *Sender)
{
    if(p1->Top > 60 ) p1->Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::down1Timer(TObject *Sender)
{
    if(p1->Top + p1->Height < tlo->Height - 10 ) p1->Top += 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::up2Timer(TObject *Sender)
{
    if(p2->Top > 60 ) p2->Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::down2Timer(TObject *Sender)
{
   if(p2->Top + p2->Height < tlo->Height - 10 ) p2->Top += 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key == 'A') up1->Enabled = true;
    if(Key == 'Z') down1->Enabled = true;
    if(Key == VK_UP) up2->Enabled = true;
    if(Key == VK_DOWN) down2->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key == 'A') up1->Enabled = false;
    if(Key == 'Z') down1->Enabled = false;
    if(Key == VK_UP) up2->Enabled = false;
    if(Key == VK_DOWN) down2->Enabled = false;
}
//---------------------------------------------------------------------------





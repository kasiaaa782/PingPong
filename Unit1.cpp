//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int x = -4;
int y = -4;
int player1 = 0;
int player2 = 0;
int round = 0;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::up1Timer(TObject *Sender)
{
    if(p1->Top > 60 ) p1->Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::down1Timer(TObject *Sender)
{
    if(p1->Top + p1->Height < table->Height - 10 ) p1->Top += 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::up2Timer(TObject *Sender)
{
    if(p2->Top > 60 ) p2->Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::down2Timer(TObject *Sender)
{
   if(p2->Top + p2->Height < table->Height - 10 ) p2->Top += 10;
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

void __fastcall TForm1::ballTTimer(TObject *Sender)
{
      ball->Left += x;
      ball->Top += y;

      //odbij od gornej sciany
      if(ball->Top <= table->Top+41) y = -y;
      //odbij od dolnej sciany
      if(ball->Top + ball->Height >= table->Top+table->Height) y = -y;

      //rozgrywka
      if ( ball->Top > p1->Top-ball->Height/2 &&
           ball->Top < p1->Top+p1->Height &&
           ball->Left <= p1->Left+p1->Width){
               if(ball->Top > p1->Top+40 && ball->Top+ball->Height < p1->Top+p1->Height-40){
                   x = 1.5*x;
                   y = 1.5*y;
               }
               sndPlaySound("snd/pilka.wav", SND_ASYNC);
               x = -x;
           }
      else if ( ball->Top > p2->Top-ball->Height/2 &&
                ball->Top < p2->Top+p2->Height &&
                ball->Left+ball->Width >= p2->Left ){
                   if(ball->Top > p2->Top+40 && ball->Top+ball->Height < p1->Top+p1->Height-40){
                      x = 1.5*x;
                      y = 1.5*y;
                   }
                   sndPlaySound("snd/pilka.wav", SND_ASYNC);
                   x = -x;
               }
      else if(ball->Left < p1->Left){
          sndPlaySound("snd/przegrana.wav", SND_ASYNC);
          player2++;
          ballT->Enabled = false;
          ball->Visible = false;
          Label1->Caption = "Punkt dla gracza 2 !";
          Label1->Visible = true;
          Button1->Visible = true;
      } else if (ball->Left+ball->Width > p2->Left+p2->Width) {
          sndPlaySound("snd/przegrana.wav", SND_ASYNC);
          player1++;
          ballT->Enabled = false;
          ball->Visible = false;
          Label1->Caption = "Punkt dla gracza 1 !";
          Label1->Visible = true;
          Button1->Visible = true;
      }
}
//---------------------------------------------------------------------------


  /*

        //blokowanie ruchow paletki
        Form1->OnKeyDown = FormKeyUp;
  */

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int x = -4;
int y = -4;
int player1 = 0;
int player2 = 0;
int round = 1;
int refNumber = 0;
AnsiString r, rNb, pr1, pr2;

void showGameDescription(){
     ShowMessage(
       "Witaj w grze PingPong! \n \n"
       "Lewy gracz steruje wciskaj¹c klawisze A oraz Z. \n"
       "Prawy gracz steruje wciskaj¹c strza³ki do góry i w dó³. \n \n"
       "Dla urozmaicenia zabawy: \n"
       "Kiedy odbijesz pi³kê na œrodku paletki, wówczas zmienisz jej k¹t odbicia i przyœpieszy. \n"
       "Im d³u¿ej odbijasz, tym pi³ka szybciej przemieszcza siê. \n"
       "Rozgrywka trwa 10 rund. \n \n"
       "Mi³ej zabawy! "
     );
}

void startGame(){
     Form1->Label1->Visible = false;
     Form1->newGame->Visible = false;
     Form1->nextRound->Visible = false;
     Form1->ballT->Enabled = true;
     Form1->ball->Visible = true;
}

void stopGame(AnsiString rr, AnsiString rrNb){
     Form1->Label2->Caption = "Iloœæ odbiæ: "+rrNb;
     Form1->Label3->Caption = "Runda "+rr;
     Form1->Label1->Visible = true;
     Form1->nextRound->Visible = true;
}

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
      r = IntToStr(round);
      rNb = IntToStr(refNumber);

      //zmiana kierunku pi³ki
      if(round%2 == 0 ){
         ball->Left -= x;
         ball->Top -= y;
      } else {
         ball->Left += x;
         ball->Top += y;
      }

      //odbij od gornej sciany
      if(ball->Top <= table->Top+41) y = -y;
      //odbij od dolnej sciany
      if(ball->Top + ball->Height >= table->Top+table->Height) y = -y;

      //rozgrywka
      if ( ball->Top > p1->Top-ball->Height/2 &&
           ball->Top < p1->Top+p1->Height &&
           ball->Left <= p1->Left+p1->Width){
               if(ball->Top > p1->Top+40 && ball->Top+ball->Height < p1->Top+p1->Height-40){
                   x = 1.4*x;
                   y = 1.4*y;
               }
               x = 1.1*x;
               y = 1.1*y;
               sndPlaySound("snd/pilka.wav", SND_ASYNC);
               x = -x;
               refNumber++;
           }
      else if ( ball->Top > p2->Top-ball->Height/2 &&
                ball->Top < p2->Top+p2->Height &&
                ball->Left+ball->Width >= p2->Left ){
                   if(ball->Top > p2->Top+40 && ball->Top+ball->Height < p1->Top+p1->Height-40){
                      x = 1.4*x;
                      y = 1.4*y;
                   }
                   x = 1.1*x;
                   y = 1.1*y;
                   sndPlaySound("snd/pilka.wav", SND_ASYNC);
                   x = -x;
                   refNumber++;
               }
      else if(ball->Left < p1->Left){
          sndPlaySound("snd/przegrana.wav", SND_ASYNC);
          player2++;
          pr1 = IntToStr(player1);
          pr2 = IntToStr(player2);
          score->Caption = "Wynik "+pr1+":"+pr2;
          if(round < 10) {
            Label1->Caption = "Punkt dla gracza 2!    >";
            stopGame(r, rNb);
          } else {
            nextRound->Visible = false;
            if(player1 > player2){
               Label1->Caption = "Brawo! Zwyciê¿a gracz 1!";
            } else {
              Label1->Caption = "Brawo! Zwyciê¿a gracz 2!";
            }
            Label1->Visible = true;
          }
          newGame->Visible = true;
          ballT->Enabled = false;
          ball->Visible = false;
          //blokowanie ruchow paletki
          Form1->OnKeyDown = FormKeyUp;

      } else if (ball->Left+ball->Width > p2->Left+p2->Width) {
          sndPlaySound("snd/przegrana.wav", SND_ASYNC);
          player1++;
          pr1 = IntToStr(player1);
          pr2 = IntToStr(player2);
          score->Caption = "Wynik "+pr1+":"+pr2;
          if(round < 10) {
            Label1->Caption = "<   Punkt dla gracza 1 !";
            stopGame(r, rNb);
          } else {
            nextRound->Visible = false;
            if(player1 > player2){
               Label1->Caption = "Brawo! Zwyciê¿a gracz 1!";
            } else {
              Label1->Caption = "Brawo! Zwyciê¿a gracz 2!";
            }
            Label1->Visible = true;
          }

          newGame->Visible = true;
          ballT->Enabled = false;
          ball->Visible = false;
          //blokowanie ruchow paletki
          Form1->OnKeyDown = FormKeyUp;
      }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::newGameClick(TObject *Sender)
{
     refNumber = 0;
     round = 1;
     r = IntToStr(round);

     p1->Top = 200;
     p2->Top = 200;
     player1 = 0;
     player2 = 0;
     ball->Left = 496;
     ball->Top = 240;
     x=-4;
     y=-4;
     Label2->Caption = "Iloœæ odbiæ";
     Label3->Caption = "Runda "+r;
     score->Caption = "Wynik";
     startGame();

     //odblokowanie ruchow paletki
     Form1->OnKeyDown = FormKeyDown;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::nextRoundClick(TObject *Sender)
{
     round++;
     r = IntToStr(round);
     refNumber = 0;
     p1->Top = 200;
     p2->Top = 200;
     ball->Left = 496;
     ball->Top = 240;
     x=-4;
     y=-4;
     Label2->Caption = "Iloœæ odbiæ";
     Label3->Caption = "Runda "+r;
     startGame();
     //odblokowanie ruchow paletki
     Form1->OnKeyDown = FormKeyDown;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Oprogramie1Click(TObject *Sender)
{
     Form2->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Autor1Click(TObject *Sender)
{
    ShellExecute(NULL, "open", "https://www.linkedin.com/in/katarzyna-niemiec-a99a62142/", NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N1Click(TObject *Sender)
{
     Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
     showGameDescription();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Opis1Click(TObject *Sender)
{
     showGameDescription();
}
//---------------------------------------------------------------------------




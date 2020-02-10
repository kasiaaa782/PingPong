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
 
int x = 8;
int y = 8;
// szybkosc pilki
int xFast = 16;
int xSlow = 11;

int player1 = 0;
int player2 = 0;
int bounceCounts = 0;
int bounceFasterCounts = 0;
int fasterMoveAfterXBounce = 1;
int acceleration = 1;   //przyspieszenie
int round = 1;
int initialBallInterval = 18;
int maxBounceCounts = 0;
int firstStart = 1;

AnsiString r, bC, pr1, pr2;

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
     Form1->Label4->Visible = false;
}

void stopGame(AnsiString rr, AnsiString rbC){
     Form1->Label2->Caption = "Iloœæ odbiæ: "+rbC;
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
      bC = IntToStr(bounceCounts);

      ball->Left += x;
      ball->Top += y;

      //odbij od gornej sciany
      if(ball->Top <= table->Top+41) y = -y;
      //odbij od dolnej sciany
      if(ball->Top + ball->Height >= table->Top+table->Height) y = -y;

      //odbicie od lewej paletki
      if ( (ball->Top+ball->Height >= p1->Top) &&
           (ball->Top <= p1->Top + p1->Height) &&
           (ball->Left <= p1->Left+p1->Width) ){
            if(x<0){
               bounceCounts++;
               sndPlaySound("snd/pilka.wav", SND_ASYNC);
               int quarterPaddle = p1->Height / 4; // 1/4 wysokosci paletki
              // jesli pilka uderzyla posrodku paletki +/-25% jej wysokosci to odbijajac
              // zmieniam jej kat przesuwania sie
               if(  (ball->Top > p1->Top + quarterPaddle) &&
                    (ball->Top+ball->Height <= p1->Top+p1->Height-quarterPaddle) )
                   x = xFast;
               else
                   x = xSlow;
               if( bounceFasterCounts >= fasterMoveAfterXBounce){
                  bounceFasterCounts = 0;
                  if (ballT->Interval - acceleration > 0)
                      ballT->Interval -= acceleration;
               }
               else
                  bounceFasterCounts++;
            }
       }
       //odbicie od prawej paletki
      else if ( (ball->Top+ball->Height >= p2->Top) &&
                (ball->Top <= p2->Top+p2->Height) &&
                (ball->Left + ball->Width >= p2->Left) ){
                if(x>0){
                   bounceCounts++;
                   sndPlaySound("snd/pilka.wav", SND_ASYNC);
                   int quarterPaddle = p2->Height / 4; // 1/4 wysokosci paletki
                 // jesli pilka uderzyla posrodku paletki +/-25% jej wysokosci to odbijajac
                 // zmieniam jej kat przesuwania sie
                   if( (ball->Top >= p2->Top + quarterPaddle) &&
                       (ball->Top+ball->Height <= p2->Top+p2->Height-quarterPaddle))
                      x = -xFast;
                   else
                      x = -xSlow;
                   if(bounceFasterCounts >= fasterMoveAfterXBounce){
                      bounceFasterCounts = 0;
                      if (ballT->Interval - acceleration > 0)
                          ballT->Interval -= acceleration;
                   }
                   else
                      bounceFasterCounts++;
                }
      }
      //przegrana po lewej stronie, punkt dla gracza 2 - prawego
      else if(ball->Left <= p1->Left){
          sndPlaySound("snd/przegrana.wav", SND_ASYNC);
          player2++;
          pr1 = IntToStr(player1);
          pr2 = IntToStr(player2);
          score->Caption = "Wynik "+pr1+":"+pr2;
          if(round < 10) {
            Label1->Caption = "Punkt dla gracza 2!    >";
            stopGame(r, bC);
            if(bounceCounts > maxBounceCounts){
                maxBounceCounts = bounceCounts;
            }
          } else {
            nextRound->Visible = false;
            if(player1 > player2){
               Label1->Caption = "Brawo! Zwyciê¿a gracz 1!";
               Label4->Caption = "Najwiêksza iloœæ odbiæ: " + IntToStr(maxBounceCounts);
               Label4->Visible = true;
            } else {
              Label1->Caption = "Brawo! Zwyciê¿a gracz 2!";
              Label4->Caption = "Najwiêksza iloœæ odbiæ: " + IntToStr(maxBounceCounts);
              Label4->Visible = true;
            }
            Label1->Visible = true;
          }
          newGame->Visible = true;
          ballT->Enabled = false;
          ball->Visible = false;
          //blokowanie ruchow paletki
          Form1->OnKeyDown = FormKeyUp;

      }
      //przegrana po prawej stronie, punkt dla gracza 1 - lewego
      else if (ball->Left > p2->Left) {
          sndPlaySound("snd/przegrana.wav", SND_ASYNC);
          player1++;
          pr1 = IntToStr(player1);
          pr2 = IntToStr(player2);
          score->Caption = "Wynik "+pr1+":"+pr2;
          if(round < 10) {
            Label1->Caption = "<   Punkt dla gracza 1 !";
            stopGame(r, bC);
            if(bounceCounts > maxBounceCounts){
                maxBounceCounts = bounceCounts;
            }
          } else {
            nextRound->Visible = false;
            if(player1 > player2){
               Label1->Caption = "Brawo! Zwyciê¿a gracz 1!";
               Label4->Caption = "Najwiêksza iloœæ odbiæ: " + IntToStr(maxBounceCounts);
               Label4->Visible = true;
            } else {
              Label1->Caption = "Brawo! Zwyciê¿a gracz 2!";
              Label4->Caption = "Najwiêksza iloœæ odbiæ: " + IntToStr(maxBounceCounts);
              Label4->Visible = true;
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
     if (firstStart == 1)
     {
        firstStart = 0;
        bounceCounts = 0;
        bounceFasterCounts = 0;
        round = 1;
        r = IntToStr(round);
        p1->Top = 200;
        p2->Top = 200;
        player1 = 0;
        player2 = 0;
        ball->Left = 496;
        ball->Top = 240;
        if (x < 0)
           x = xSlow;
        else
           x = -xSlow;

        Label2->Caption = "Iloœæ odbiæ";
        Label3->Caption = "Runda "+r;
        score->Caption = "Wynik";
        startGame();
        ballT->Interval = initialBallInterval;
     }
     else {
        if (Application->MessageBox("Czy na pewno chcesz zacz¹æ od nowa?","PotwierdŸ",
        MB_YESNO | MB_ICONQUESTION) == IDYES) {
            firstStart = 0;
            bounceCounts = 0;
            bounceFasterCounts = 0;
            round = 1;
            r = IntToStr(round);
            p1->Top = 200;
            p2->Top = 200;
            player1 = 0;
            player2 = 0;
            ball->Left = 496;
            ball->Top = 240;
            if (x < 0)
               x = xSlow;
            else
               x = -xSlow;

            Label2->Caption = "Iloœæ odbiæ";
            Label3->Caption = "Runda "+r;
            score->Caption = "Wynik";
            startGame();
            ballT->Interval = initialBallInterval;
            //odblokowanie ruchow paletki
            Form1->OnKeyDown = FormKeyDown;
        }
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::nextRoundClick(TObject *Sender)
{
     round++;
     r = IntToStr(round);
     bounceCounts = 0;
     bounceFasterCounts = 0;
     p1->Top = 200;
     p2->Top = 200;
     ball->Left = 496;
     ball->Top = 240;
     if (x < 0)
        x = xSlow;
     else
        x = -xSlow;
     Label2->Caption = "Iloœæ odbiæ";
     Label3->Caption = "Runda "+r;
     startGame();
     ballT->Interval = initialBallInterval;
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




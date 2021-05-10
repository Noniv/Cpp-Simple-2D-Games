//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1* Form1;
//UWAGA: obiekty oraz funkcje zdefiniowane s� w pliku nag��wkowym
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	gameMode = 0;
	game = false;
	BallSpeedx = 0;
	BallSpeedy = 0;
	point = 0;
	hardiness = 0;
	randomNumber = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonOnePlayerClick(TObject* Sender)
{
	gameMode = 1;                                 //ustawienie trybu dla 1 gracza
	ButtonHard->Visible = true;					  //pokazanie przycisk�w poziomu trudno�ci
	ButtonEasy->Visible = true;
	ButtonOnePlayer->Visible = false;             //usuni�cie zb�dnych przycisk�w
	ButtonTwoPlayers->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonTwoPlayersClick(TObject* Sender)
{
	gameMode = 2;                                 //ustawienie trybu dla 2 graczy
	ButtonOnePlayer->Visible = false;             //usuni�cie zb�dnych przycisk�w
	ButtonTwoPlayers->Visible = false;
	ButtonHard->Visible = true;					  //pokazanie przycisk�w poziomu trudno�ci
	ButtonEasy->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonEasyClick(TObject* Sender)
{
	ButtonHard->Visible = false;						//usuni�cie zb�dnych przycisk�w
	ButtonEasy->Visible = false;
	hardiness = 1;										//ustawienie poziomu trudno�ci
	if (gameMode == 1)
	{
		StringMain->Caption = "Sterowanie:";				//zmiana napisu na "sterowanie"
		StringW->Visible = true;                           //pokazanie sterowania dla jednego gracza
		StringS->Visible = true;
	}
	else if (gameMode == 2)
	{
		StringMain->Caption = "Sterowanie:";				//zmiana napisu na "sterowanie"
		StringW->Visible = true;                          //pokazanie sterowania dla dw�ch graczy
		StringS->Visible = true;
		StringUpper->Visible = true;
		StringDown->Visible = true;
	}
	ButtonPlay->Visible = true;                        //stworzenie przycisku do gry
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonHardClick(TObject* Sender)
{
	ButtonHard->Visible = false;				//usuni�cie zb�dnych przycisk�w
	ButtonEasy->Visible = false;
	hardiness = 2;										//ustawienie poziomu trudno�ci
	if (gameMode == 1)
	{
		StringMain->Caption = "Sterowanie:";				//zmiana napisu na "sterowanie"
		StringW->Visible = true;                           //pokazanie sterowania dla jednego gracza
		StringS->Visible = true;
	}
	else if (gameMode == 2)
	{
		StringMain->Caption = "Sterowanie:";				//zmiana napisu na "sterowanie"
		StringW->Visible = true;                          //pokazanie sterowania dla dw�ch graczy
		StringS->Visible = true;
		StringUpper->Visible = true;
		StringDown->Visible = true;
	}
	ButtonPlay->Visible = true;                        //stworzenie przycisku do gry
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonPlayClick(TObject* Sender)
{
	ButtonPlay->Visible = false;						 //usuni�cie przycisku do gry
	StringMain->Visible = false;						//usuni�cie g��wnego napisu
	if (gameMode == 1)                                   //usuni�cie informacji o sterowaniu
	{
		StringW->Visible = false;
		StringS->Visible = false;
	}
	else
	{
		StringW->Visible = false;
		StringS->Visible = false;
		StringUpper->Visible = false;
		StringDown->Visible = false;
	}
	game = true;										//rozpocz�cie gry
	BallSpeedx = -6;									//ustawienie pr�dko�ci pocz�tkowej pi�ki
	BallSpeedy = -6;
}
//---------------------------------------------------------------------------
randomize();								//rozpocz�cie generowania liczb losowych
void __fastcall TForm1::TimerBallTimer(TObject* Sender)
{
	if (game == true)
	{
		if (gameMode == 1)
			computerMove();		//ruch komputera
		if (hardiness == 2)
			reversePoint();			//obsluga czerwonego punktu
		ballMove();			//ruch pilki
		if (Ball->Left < Background->Left + 5) 			//sprawdzenie, czy pi�ka wysz�a poza pole gry (lewo)
		{
			point = 2;              //zakonczenie gry i przyznanie punktu prawemu graczowi
			endGame();
		}
		else if (Ball->Left + Ball->Width > Background->Width - 5)	//sprawdzenie, czy pi�ka wysz�a poza pole gry (prawo)
		{
			point = 1;
			endGame();             //zakonczenie gry i przyznanie punktu lewemu graczowi
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TimerLeftPaddleUpTimer(TObject* Sender)
{
	if (PaddleLeft->Top > 30)		//sprawdzenie czy paletka nie jest za daleko
		PaddleLeft->Top -= 8;		//przesuni�cie lewej paletki do g�ry
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TimerLeftPaddleDownTimer(TObject* Sender)
{
	if (PaddleLeft->Top + PaddleLeft->Height < Background->Height - 30)		//sprawdzenie czy paletka nie jest za daleko
		PaddleLeft->Top += 8;		//przesuni�cie lewej paletki w d�
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TimerRightPaddleUpTimer(TObject* Sender)
{
	if (PaddleRight->Top > 30)			//sprawdzenie czy paletka nie jest za daleko
		PaddleRight->Top -= 8;			//przesuni�cie prawej paletki do g�ry
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TimerRightPaddleDownTimer(TObject* Sender)
{
	if (PaddleRight->Top + PaddleRight->Height < Background->Height - 30)	//sprawdzenie czy paletka nie jest za daleko
		PaddleRight->Top += 8;			//przesuni�cie prawej paletki w d�
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject* Sender, WORD& Key, TShiftState Shift)
{
	if (Key == VK_UP && gameMode == 2)			//strza�ka do g�ry
		TimerRightPaddleUp->Enabled = true;
	if (Key == VK_DOWN && gameMode == 2)		//strza�ka w d�
		TimerRightPaddleDown->Enabled = true;
	if (Key == 'W')								//W
		TimerLeftPaddleUp->Enabled = true;
	if (Key == 'S')								//S
		TimerLeftPaddleDown->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject* Sender, WORD& Key, TShiftState Shift)
{
	if (Key == VK_UP && gameMode == 2)			//strza�ka do g�ry
		TimerRightPaddleUp->Enabled = false;
	if (Key == VK_DOWN && gameMode == 2)		//strza�ka w d�
		TimerRightPaddleDown->Enabled = false;
	if (Key == 'W')								//W
		TimerLeftPaddleUp->Enabled = false;
	if (Key == 'S')								//S
		TimerLeftPaddleDown->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonRestartClick(TObject* Sender)
{
	StringMain->Visible = false;		//usuni�cie g��wnego napisu
	ButtonRestart->Visible = false;		//usuni�cie zb�dnych przycisk�w
	ButtonMenu->Visible = false;
	Ball->Left = 496;					//przywr�cenie pi�ki i ustawienie jej na warto�ci pocz�tkowej
	Ball->Top = 264;
	Ball->Visible = true;
	game = true;						//rozpocz�cie gry
	point = 0;							//zresetowanie warto�ci zmiennej point
	if (random(2) == 0)                //wprawienie pi�ki w ruch
	{
		BallSpeedx = -6;
		BallSpeedy = -6;
	}
	else
	{
		BallSpeedx = 6;
		BallSpeedy = 6;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonMenuClick(TObject* Sender)
{
	ButtonMenu->Visible = false;             //usuniecie zbednych przyciskow
	ButtonRestart->Visible = false;
	StringMain->Caption = "Wybierz tryb gry: ";         //zmiana napisu
	ButtonOnePlayer->Visible = true;               //pokazanie przyciskow wyboru gry
	ButtonTwoPlayers->Visible = true;
	Ball->Left = 496;					//przywr�cenie pi�ki i ustawienie jej na warto�ci pocz�tkowej
	Ball->Top = 264;
	Ball->Visible = true;
}
//---------------------------------------------------------------------------
void TForm1::computerMove()
{
	if ((PaddleRight->Top + PaddleRight->Height / 2 > Ball->Top + Ball->Height / 2 + 5) &&		//dla hardiness 1
		(PaddleRight->Top > 30) && hardiness == 1)
		PaddleRight->Top -= 7;
	else if ((PaddleRight->Top + PaddleRight->Height / 2 < Ball->Top + Ball->Height / 2 - 5) &&
		(PaddleRight->Top + PaddleRight->Height < Background->Height - 30) && hardiness == 1)
		PaddleRight->Top += 7;
	else if ((PaddleRight->Top + PaddleRight->Height / 2 > Ball->Top + Ball->Height / 2 + 6) &&    //dla hardiness 2
		(PaddleRight->Top > 30) && hardiness == 2)
		PaddleRight->Top -= 9;
	else if ((PaddleRight->Top + PaddleRight->Height / 2 < Ball->Top + Ball->Height / 2 - 6) &&
		(PaddleRight->Top + PaddleRight->Height < Background->Height - 30) && hardiness == 2)
		PaddleRight->Top += 9;
}
//---------------------------------------------------------------------------
void TForm1::ballMove()
{
	Ball->Left += BallSpeedx;		//zmiana wsp�rz�dnej x pilki
	Ball->Top += BallSpeedy;		//zmiana wsp�rz�dnej y pilki
	if ((Ball->Top <= 0) || (Ball->Top + Ball->Height >= Background->Height))	//odbicie pi�ki od do�u i g�ry
	{
		sndPlaySound("snd/sound.wav", SND_ASYNC);		//dzwiek odbicia
		BallSpeedy = -BallSpeedy;					//odbicie pilki
	}
	else if ((Ball->Top + Ball->Height > PaddleLeft->Top) &&			//warunek kolizji z lew� paletk�
		(Ball->Top < PaddleLeft->Top + PaddleLeft->Height) &&
		(Ball->Left < PaddleLeft->Left + PaddleLeft->Width + 15) &&
		(Ball->Left > PaddleLeft->Left + PaddleLeft->Width - 20))
	{
		sndPlaySound("snd/sound.wav", SND_ASYNC);		//dzwiek odbicia
		if (BallSpeedx < 0 && BallSpeedx > -20)				//odbicie pi�ki i zwi�kszenie jej szybko�ci je�li jest mniejsza od 20
			BallSpeedx = -BallSpeedx + 1;
		else if (BallSpeedx < 0)
			BallSpeedx = -BallSpeedx;
		randomNumber = random(3);							//losowa zmiana szybko�ci w kierunku pionowym
		if ((randomNumber == 0 || randomNumber == 1) && BallSpeedy > 0 &&
			BallSpeedy < 15)
			BallSpeedy += random(3);
		else if ((randomNumber == 2 || randomNumber == 3) && BallSpeedy < 0 &&
			BallSpeedy > -15)
			BallSpeedy -= random(3);
	}
	else if ((Ball->Top + Ball->Height > PaddleRight->Top) &&		//warunek kolizji z praw� paletk�
		(Ball->Top < PaddleRight->Top + PaddleRight->Height) &&
		(Ball->Left + Ball->Width > PaddleRight->Left - 15) &&
		(Ball->Left + Ball->Width < PaddleRight->Left + 20))
	{
		sndPlaySound("snd/sound.wav", SND_ASYNC);	//dzwiek odbicia
		if (BallSpeedx > 0 && BallSpeedx < 20)			//odbicie pi�ki i zwi�kszenie jej szybko�ci je�li jest mniejsza od 20
			BallSpeedx = -BallSpeedx - 1;
		else if (BallSpeedx > 0)
			BallSpeedx = -BallSpeedx;
		randomNumber = random(4);						//losowa zmiana szybko�ci w kierunku pionowym
		if (randomNumber == 1 || randomNumber == 2)
			BallSpeedy += randomNumber;
		else
			BallSpeedy -= randomNumber;
	}
}
//---------------------------------------------------------------------------
void TForm1::endGame()
{
	game = false;				//wylaczenie gry
	Ball->Visible = false;		//usuniecie pilki
	if (point == 1)				//pokazanie zwyciezcy
		StringMain->Caption = "Wygrywa gracz lewy!";
	else if (point == 2)
		StringMain->Caption = "Wygrywa gracz prawy!";
	else if (point == 0)
		StringMain->Caption = "Remis!";
	StringMain->Visible = true;
	ButtonRestart->Visible = true;		//pokazanie przycisku restartu
	ButtonMenu->Visible = true;
	ReversePoint->Visible = false;          //usuniecie punktu utrudniajcego gre
}
//---------------------------------------------------------------------------
void TForm1::reversePoint()
{
	if (random(10) == 1 && (BallSpeedx > 18 || BallSpeedx < -18) && ReversePoint->Visible == false)      //warunek powstania punktu
	{
		ReversePoint->Left = 500 + random(60);                         //powstanie punktu z losowymi wspo�rzednymi
		ReversePoint->Top = 75 + random(450);
		ReversePoint->Visible = true;
	}
	else if ((ReversePoint->Visible == true) && (ReversePoint->Left > Ball->Left - 30) &&                   //sprawdzenie czy punkt ju� istnieje i czy nastapilo zderzenie z nim
		(ReversePoint->Left + ReversePoint->Width < Ball->Left + Ball->Width + 30) &&
		(ReversePoint->Top > Ball->Top - 30) &&
		(ReversePoint->Top + ReversePoint->Height < Ball->Top + Ball->Height + 30))
	{
		ReversePoint->Visible = false;          //usuniecie punktu i odbicie pilki
		BallSpeedx = -BallSpeedx;
		sndPlaySound("snd/sound2.wav", SND_ASYNC);   //odegranie dzwieku
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject* Sender, TCloseAction& Action)
{
	gameMode = 0;
	game = false;
	BallSpeedx = 0;
	BallSpeedy = 0;
	point = 0;
	hardiness = 0;
	randomNumber = 0;
	Ball->Left = 496;
	Ball->Top = 264;
	StringMain->Caption = "Wybierz tryb gry:";
	ButtonEasy->Visible = false;
	ButtonHard->Visible = false;
	ButtonMenu->Visible = false;
	ButtonPlay->Visible = false;
	ButtonRestart->Visible = false;
	ReversePoint->Visible = false;
	StringDown->Visible = false;
	StringS->Visible = false;
	StringUpper->Visible = false;
	StringW->Visible = false;
	TimerLeftPaddleDown->Enabled = false;
	TimerLeftPaddleUp->Enabled = false;
	TimerRightPaddleDown->Enabled = false;
	TimerRightPaddleUp->Enabled = false;
	StringMain->Visible = true;
	ButtonOnePlayer->Visible = true;
	ButtonTwoPlayers->Visible = true;
	Ball->Visible = true;
}
//---------------------------------------------------------------------------

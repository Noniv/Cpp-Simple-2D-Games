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
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TImage* Ball;           //pi³ka
	TImage* PaddleLeft;     //lewa paletka
	TImage* PaddleRight;    //prawa paletka
	TShape* Background;     //t³o
	TLabel* StringMain;     //g³ówny napis na górze
	TImage* ButtonOnePlayer;    //przycisk trybu dla 1 gracza
	TImage* ButtonTwoPlayers;   //przycisk trybu dla 2 graczy
	TLabel* StringW;        //napis W
	TLabel* StringS;        //napis S
	TLabel* StringUpper;    //napis strza³ka w górê
	TLabel* StringDown;     //napis strza³ka w dó³
	TImage* ButtonPlay;     //przycisk gry
	TTimer* TimerBall;      //g³ówny timer odpowiadaj¹cy za grê
	TTimer* TimerLeftPaddleUp;  //timer odpowiadaj¹cy za ruch lewej paletki w górê
	TTimer* TimerLeftPaddleDown; //timer odpowiadaj¹cy za ruch lewej paletki w dó³
	TTimer* TimerRightPaddleUp;     //timer odpowiadaj¹cy za ruch prawej paletki w górê
	TTimer* TimerRightPaddleDown;   //timer odpowiadaj¹cy za ruch prawej paletki w dó³
	TImage* ButtonRestart;      //przycisk ponownej gry
	TImage* ButtonEasy;     //przycisk trybu ³atwego
	TImage* ButtonHard;	//przycisk trybu trudnego
	TShape* ReversePoint;	//czerwony punkt utrudniaj¹cy grê od pewnego momentu w trybie trudnym
	TImage* ButtonMenu;     //przycisk powrotu do menu
	void __fastcall ButtonOnePlayerClick(TObject* Sender);	//funkcja obs³uguj¹ca zdarzenie wciœniêcia przycisku gry 1-osobowej
	void __fastcall ButtonTwoPlayersClick(TObject* Sender);	//funkcja obs³uguj¹ca zdarzenie wciœniêcia przycisku gry 2-osobowej
	void __fastcall ButtonPlayClick(TObject* Sender);	//funkcja obs³uguj¹ca zdarzenie wciœniêcia przycisku rozpoczynaj¹cego grê
	void __fastcall TimerBallTimer(TObject* Sender);	//funkcja g³ówna gry, wywo³uj¹ca siê co 15ms
	void __fastcall TimerLeftPaddleUpTimer(TObject* Sender);	//funkcja wykonuj¹ca siê przy naciœniêciu W
	void __fastcall TimerLeftPaddleDownTimer(TObject* Sender);	//funkcja wykonuj¹ca siê przy naciœniêciu S
	void __fastcall TimerRightPaddleUpTimer(TObject* Sender);	//funkcja wykonuj¹ca siê przy naciœniêciu strza³ki do góry
	void __fastcall TimerRightPaddleDownTimer(TObject* Sender);	//funkcja wykonuj¹ca siê przy naciœniêciu strza³ki w dó³
	void __fastcall FormKeyDown(TObject* Sender, WORD& Key, TShiftState Shift);	//funkcja obs³uguj¹ca wciœniêcie przycisku, uruchomienie timerów
	void __fastcall FormKeyUp(TObject* Sender, WORD& Key, TShiftState Shift);	//funkcja obs³uguj¹ca opuszczenie przycisku, zatrzymanie timerów
	void __fastcall ButtonRestartClick(TObject* Sender);	//funkcja obs³uguj¹ca zdarzenie wciœniêcia przycisku restartuj¹cego grê
	void __fastcall ButtonEasyClick(TObject* Sender);	//funkcja obs³uguj¹ca zdarzenie wciœniêcia przycisku trybu ³atwego
	void __fastcall ButtonHardClick(TObject* Sender);	//funkcja obs³uguj¹ca zdarzenie wciœniêcia przycisku trybu trudnego
	void __fastcall ButtonMenuClick(TObject* Sender);
	void __fastcall FormClose(TObject* Sender, TCloseAction& Action);	//funkcja obs³uguj¹ca zdarzenie wciœniêcia przycisku powrotu do menu
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);	//funkcja wywo³ywana przy tworzeniu okna gry
	bool game;			//zmienna przechowuj¹ca czy u¿ytkownik aktualnie gra
	int gameMode;			//zmienna przechowuje informacjê o tym, który tryb (dla 1 lub 2 graczy) zosta³ wybrany
	int BallSpeedx;			//zmienna odpowiadaj¹ca za szybkoœæ pi³ki w kierunku poziomym
	int BallSpeedy;			//zmienna odpowiadaj¹ca za szybkoœæ pi³ki w kierunku pionowym
	int point;				//zmienna przechowuje informacjê o tym, kto ostatnio odbi³ - 1 czy 2 gracz
	int hardiness;			//zmienna przechowuje poziom hardinessi
	int randomNumber;		        //zmienna zmieniaj¹ca szybkoœæ kuli w kierunku pionowym
	void endGame();		//funkcja zatrzymuje grê
	void computerMove();	//funkcja obs³uguje grê komputera
	void ballMove();	//funkcja obs³uguje ruch pi³ki
	void reversePoint();	//funkcja odpowiadaj¹ca za dodatkowy czerwony punkt utrudniaj¹cy d³u¿sz¹ grê
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1* Form1;
//---------------------------------------------------------------------------
#endif

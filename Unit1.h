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
	TImage* Ball;           //pi�ka
	TImage* PaddleLeft;     //lewa paletka
	TImage* PaddleRight;    //prawa paletka
	TShape* Background;     //t�o
	TLabel* StringMain;     //g��wny napis na g�rze
	TImage* ButtonOnePlayer;    //przycisk trybu dla 1 gracza
	TImage* ButtonTwoPlayers;   //przycisk trybu dla 2 graczy
	TLabel* StringW;        //napis W
	TLabel* StringS;        //napis S
	TLabel* StringUpper;    //napis strza�ka w g�r�
	TLabel* StringDown;     //napis strza�ka w d�
	TImage* ButtonPlay;     //przycisk gry
	TTimer* TimerBall;      //g��wny timer odpowiadaj�cy za gr�
	TTimer* TimerLeftPaddleUp;  //timer odpowiadaj�cy za ruch lewej paletki w g�r�
	TTimer* TimerLeftPaddleDown; //timer odpowiadaj�cy za ruch lewej paletki w d�
	TTimer* TimerRightPaddleUp;     //timer odpowiadaj�cy za ruch prawej paletki w g�r�
	TTimer* TimerRightPaddleDown;   //timer odpowiadaj�cy za ruch prawej paletki w d�
	TImage* ButtonRestart;      //przycisk ponownej gry
	TImage* ButtonEasy;     //przycisk trybu �atwego
	TImage* ButtonHard;	//przycisk trybu trudnego
	TShape* ReversePoint;	//czerwony punkt utrudniaj�cy gr� od pewnego momentu w trybie trudnym
	TImage* ButtonMenu;     //przycisk powrotu do menu
	void __fastcall ButtonOnePlayerClick(TObject* Sender);	//funkcja obs�uguj�ca zdarzenie wci�ni�cia przycisku gry 1-osobowej
	void __fastcall ButtonTwoPlayersClick(TObject* Sender);	//funkcja obs�uguj�ca zdarzenie wci�ni�cia przycisku gry 2-osobowej
	void __fastcall ButtonPlayClick(TObject* Sender);	//funkcja obs�uguj�ca zdarzenie wci�ni�cia przycisku rozpoczynaj�cego gr�
	void __fastcall TimerBallTimer(TObject* Sender);	//funkcja g��wna gry, wywo�uj�ca si� co 15ms
	void __fastcall TimerLeftPaddleUpTimer(TObject* Sender);	//funkcja wykonuj�ca si� przy naci�ni�ciu W
	void __fastcall TimerLeftPaddleDownTimer(TObject* Sender);	//funkcja wykonuj�ca si� przy naci�ni�ciu S
	void __fastcall TimerRightPaddleUpTimer(TObject* Sender);	//funkcja wykonuj�ca si� przy naci�ni�ciu strza�ki do g�ry
	void __fastcall TimerRightPaddleDownTimer(TObject* Sender);	//funkcja wykonuj�ca si� przy naci�ni�ciu strza�ki w d�
	void __fastcall FormKeyDown(TObject* Sender, WORD& Key, TShiftState Shift);	//funkcja obs�uguj�ca wci�ni�cie przycisku, uruchomienie timer�w
	void __fastcall FormKeyUp(TObject* Sender, WORD& Key, TShiftState Shift);	//funkcja obs�uguj�ca opuszczenie przycisku, zatrzymanie timer�w
	void __fastcall ButtonRestartClick(TObject* Sender);	//funkcja obs�uguj�ca zdarzenie wci�ni�cia przycisku restartuj�cego gr�
	void __fastcall ButtonEasyClick(TObject* Sender);	//funkcja obs�uguj�ca zdarzenie wci�ni�cia przycisku trybu �atwego
	void __fastcall ButtonHardClick(TObject* Sender);	//funkcja obs�uguj�ca zdarzenie wci�ni�cia przycisku trybu trudnego
	void __fastcall ButtonMenuClick(TObject* Sender);
	void __fastcall FormClose(TObject* Sender, TCloseAction& Action);	//funkcja obs�uguj�ca zdarzenie wci�ni�cia przycisku powrotu do menu
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);	//funkcja wywo�ywana przy tworzeniu okna gry
	bool game;			//zmienna przechowuj�ca czy u�ytkownik aktualnie gra
	int gameMode;			//zmienna przechowuje informacj� o tym, kt�ry tryb (dla 1 lub 2 graczy) zosta� wybrany
	int BallSpeedx;			//zmienna odpowiadaj�ca za szybko�� pi�ki w kierunku poziomym
	int BallSpeedy;			//zmienna odpowiadaj�ca za szybko�� pi�ki w kierunku pionowym
	int point;				//zmienna przechowuje informacj� o tym, kto ostatnio odbi� - 1 czy 2 gracz
	int hardiness;			//zmienna przechowuje poziom hardinessi
	int randomNumber;		        //zmienna zmieniaj�ca szybko�� kuli w kierunku pionowym
	void endGame();		//funkcja zatrzymuje gr�
	void computerMove();	//funkcja obs�uguje gr� komputera
	void ballMove();	//funkcja obs�uguje ruch pi�ki
	void reversePoint();	//funkcja odpowiadaj�ca za dodatkowy czerwony punkt utrudniaj�cy d�u�sz� gr�
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1* Form1;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------
#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <string.h>
#include "Score.h"
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TShape* Background;
	TImage* ButtonPlay;
	TTimer* TimerBeforeSequence;
	TTimer* TimerSequence;
	TLabel* StringMain;
	TImage* ButtonRestart;
	TImage* ButtonScores;
	TLabel* StringScores;
	TImage* ButtonOK;
	TLabel* StringNick;
	TEdit* EditNick;
	TImage* ButtonNickOK;
	void __fastcall ButtonPlayClick(TObject* Sender);
	void __fastcall TimerSequenceTimer(TObject* Sender);
	void __fastcall TimerBeforeSequenceTimer(TObject* Sender);
	void __fastcall ButtonRestartClick(TObject* Sender);
	void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
	void __fastcall ButtonScoresClick(TObject* Sender);
	void __fastcall ButtonOKClick(TObject* Sender);
	void __fastcall ButtonNickOKClick(TObject* Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
	__fastcall ~TForm3();
	int order[100];
	int orderIterator;
	int points;
	std::string nick;
	TImage* tmp;
	TImage* block[9];
	Score* score;
	void __fastcall BlockClick(TObject* Sender);
	void activateBlock(int blockNumber);
	void endGame();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3* Form3;
//---------------------------------------------------------------------------
#endif

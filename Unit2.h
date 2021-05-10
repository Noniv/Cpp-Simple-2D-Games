//---------------------------------------------------------------------------
#ifndef Unit2H
#define Unit2H
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
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TShape* Background;
	TImage* Paddle;
	TImage* Ball;
	TTimer* TimerBall;
	TTimer* TimerRight;
	TTimer* TimerLeft;
	TImage* ButtonPlay;
	TImage* ButtonRestart;
	TLabel* StringMain;
	TImage* BallSpeedPoint;
	TTimer* TimerBallSpeedPointEnd;
	TImage* PaddleSpeedPoint;
	TTimer* TimerPaddleSpeedPointEnd;
	TTimer* TimerHyperBallPointEnd;
	TTimer* TimerPaddleWidthDownPointEnd;
	TTimer* TimerPaddleWidthUpPointEnd;
	TImage* HyperBallPoint;
	TImage* PaddleWidthDownPoint;
	TImage* PaddleWidthUpPoint;
	TImage* aKey;
	TImage* dKey;
	TImage* ButtonScores;
	TLabel* StringScores;
	TImage* ButtonOK;
	TImage* ButtonNextLevel;
	TLabel* StringNick;
	TEdit* EditNick;
	TImage* ButtonNickOK;
	void __fastcall TimerBallTimer(TObject* Sender);
	void __fastcall TimerRightTimer(TObject* Sender);
	void __fastcall TimerLeftTimer(TObject* Sender);
	void __fastcall FormKeyDown(TObject* Sender, WORD& Key,
		TShiftState Shift);
	void __fastcall FormKeyUp(TObject* Sender, WORD& Key,
		TShiftState Shift);
	void __fastcall ButtonPlayClick(TObject* Sender);
	void __fastcall ButtonRestartClick(TObject* Sender);
	void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
	void __fastcall TimerBallSpeedPointEndTimer(TObject* Sender);
	void __fastcall TimerPaddleSpeedPointEndTimer(TObject* Sender);
	void __fastcall TimerPaddleWidthDownPointEndTimer(TObject* Sender);
	void __fastcall TimerPaddleWidthUpPointEndTimer(TObject* Sender);
	void __fastcall TimerHyperBallPointEndTimer(TObject* Sender);
	void __fastcall ButtonScoresClick(TObject* Sender);
	void __fastcall ButtonOKClick(TObject* Sender);
	void __fastcall ButtonNextLevelClick(TObject* Sender);
	void __fastcall ButtonNickOKClick(TObject* Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
	__fastcall ~TForm2();
	int ballSpeedx;
	int ballSpeedy;
	int hardiness;
	int hardinessx;
	int paddleCollisionTicks;
	int maxPaddleCollisionTicks;
	int points;
	int prevPoints;
	int blockHitCount[60];
	int paddleSpeed;
	int collisionsIterator;
	bool blocksTrue[60];
	bool game;
	bool isHyperBall;
	bool isPaddleSpeedPoint;
	bool isBallSpeedPoint;
	bool isPaddleWidthUpPoint;
	bool isPaddleWidthDownPoint;
	bool isHyperBallPoint;
	bool isPaddleWidthUpPointPicked;
	bool wasHyperBallPicked;
	std::string nick;
	TImage* Block[60];
	TImage* lastBlock;
	Score* score;
	bool collision(TImage* Object1, TImage* Object2);
	void colorAllBlocks();
	void ballMove();
	void blockCollisionControl();
	void endGame();
	void hardinessControl();
	void bonusCreateControl(TImage* Block);
	void ballSpeedPointCreate(TImage* Block);
	void ballSpeedPointCollision();
	void hyperBallPointCreate(TImage* Block);
	void hyperBallPointCollision();
	void paddleSpeedPointCreate(TImage* Block);
	void paddleSpeedPointCollision();
	void paddleWidthDownPointCreate(TImage* Block);
	void paddleWidthDownPointCollision();
	void paddleWidthUpPointCreate(TImage* Block);
	void paddleWidthUpPointCollision();
	void setDefaultValues();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2* Form2;
//---------------------------------------------------------------------------
#endif

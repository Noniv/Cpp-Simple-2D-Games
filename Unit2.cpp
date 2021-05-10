//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>
#pragma hdrstop
#include "mmsystem.h"
#include "Unit2.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2* Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
	score = new Score();
	score->setCurrentGame("Arkanoid");
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Block[i * 10 + j] = new TImage(this);
			Block[i * 10 + j]->Parent = this;
			Block[i * 10 + j]->Visible = false;
			Block[i * 10 + j]->Height = 20;
			Block[i * 10 + j]->Width = 50;
			Block[i * 10 + j]->Left = 20 + 75 * j;
			Block[i * 10 + j]->Top = 53 + 70 * i;
		}
	}
	setDefaultValues();
	colorAllBlocks();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::TimerBallTimer(TObject* Sender)
{
	if (game == true)
	{
		ballMove();
		blockCollisionControl();
		endGame();
		hardinessControl();
		ballSpeedPointCollision();
		hyperBallPointCollision();
		paddleSpeedPointCollision();
		paddleWidthDownPointCollision();
		paddleWidthUpPointCollision();
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::TimerRightTimer(TObject* Sender)
{
	if ((Paddle->Left + Paddle->Width < Background->Width - 15 && isPaddleWidthUpPointPicked == false) ||
		(Paddle->Left + Paddle->Width < Background->Width + 45 && isPaddleWidthUpPointPicked == true))
		Paddle->Left += paddleSpeed;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::TimerLeftTimer(TObject* Sender)
{
	if ((Paddle->Left > 15 && isPaddleWidthUpPointPicked == false) ||
		(Paddle->Left > -45 && isPaddleWidthUpPointPicked == true))
		Paddle->Left -= paddleSpeed;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormKeyDown(TObject* Sender, WORD& Key,
	TShiftState Shift)
{
	if (Key == 'A')
		TimerLeft->Enabled = true;
	if (Key == 'D')
		TimerRight->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormKeyUp(TObject* Sender, WORD& Key,
	TShiftState Shift)
{
	if (Key == 'A')
		TimerLeft->Enabled = false;
	if (Key == 'D')
		TimerRight->Enabled = false;
}
//---------------------------------------------------------------------------
void TForm2::ballMove()
{
	Ball->Top += ballSpeedy;
	Ball->Left += ballSpeedx;
	if ((Ball->Top + Ball->Height > Paddle->Top - 5) &&
		(Ball->Left < Paddle->Left + Paddle->Width) &&
		(Ball->Left + Ball->Width > Paddle->Left) &&
		(Ball->Top + Ball->Height < Paddle->Top + Paddle->Width + 15) &&
		(ballSpeedy > 0))
	{
		paddleCollisionTicks++;
		lastBlock = NULL;
		ballSpeedy = -ballSpeedy;
		sndPlaySound("snd/sound.wav", SND_ASYNC);
	}
	else if ((Ball->Left <= 5 && ballSpeedx < 0) ||
		(Ball->Left + Ball->Width >= Background->Width - 5 && ballSpeedx > 0))
	{
		ballSpeedx = -ballSpeedx;
		lastBlock = NULL;
	}
	else if ((Ball->Top < 0) && (ballSpeedy < 0))
	{
		ballSpeedy = -ballSpeedy;
		lastBlock = NULL;
	}
}
//---------------------------------------------------------------------------
void TForm2::blockCollisionControl()
{
	for (int i = 0; i < 60; i++)
		if ((blocksTrue[i] == true) &&
			collision(Ball, Block[i]) &&
			(lastBlock != Block[i]))
		{
			blockHitCount[i]--;
			switch (blockHitCount[i])
			{
			case 1:
				Block[i]->Picture->LoadFromFile("img/block5.bmp");
				break;
			case 2:
				Block[i]->Picture->LoadFromFile("img/block4.bmp");
				break;
			case 3:
				Block[i]->Picture->LoadFromFile("img/block3.bmp");
				break;
			case 4:
				Block[i]->Picture->LoadFromFile("img/block2.bmp");
				break;
			case 5:
				Block[i]->Picture->LoadFromFile("img/block1.bmp");
				break;
			}
			if (isHyperBall == false)
			{
				collisionsIterator++;
				if (collisionsIterator > 4)
				{
					bonusCreateControl(Block[i]);
					collisionsIterator = 0;
				}
				ballSpeedy = -ballSpeedy;
				lastBlock = Block[i];
				sndPlaySound("snd/sound2.wav", SND_ASYNC);
			}
			else if (isHyperBall == true)
				blockHitCount[i] = 0;
			if (blockHitCount[i] <= 0)
			{
				Block[i]->Visible = false;
				blocksTrue[i] = false;
				points++;
			}
		}
}
//---------------------------------------------------------------------------
void TForm2::endGame()
{
	if ((Ball->Top + Ball->Width >= Background->Height) || points >= 60)
	{
		game = false;
		ballSpeedx = 0;
		ballSpeedy = 0;
		Ball->Visible = false;
		if (points >= 60)
		{
			StringMain->Visible = true;
			StringMain->Caption = "Wygrana! Twoje punkty: " + IntToStr(prevPoints + points);
			ButtonNextLevel->Visible = true;
			ButtonScores->Visible = false;
		}
		else
		{
			ButtonRestart->Visible = true;
			ButtonScores->Visible = true;
			StringMain->Visible = true;
			if (points + prevPoints > 0)
				StringMain->Caption = "Przegrana! Twoje punkty: " + IntToStr(prevPoints + points);
			StringNick->Caption = "Aby zapisaæ wynik, podaj nick (max 3 znaki): ";
			StringNick->BringToFront();
			EditNick->BringToFront();
			ButtonNickOK->BringToFront();
			StringNick->Visible = true;
			EditNick->Visible = true;
			ButtonNickOK->Visible = true;
		}
		TimerBallSpeedPointEnd->Enabled = false;
		TimerHyperBallPointEnd->Enabled = false;
		TimerPaddleSpeedPointEnd->Enabled = false;
		TimerPaddleWidthDownPointEnd->Enabled = false;
		TimerPaddleWidthUpPointEnd->Enabled = false;
		BallSpeedPoint->Visible = false;
		PaddleWidthDownPoint->Visible = false;
		PaddleWidthUpPoint->Visible = false;
		HyperBallPoint->Visible = false;
		PaddleSpeedPoint->Visible = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ButtonPlayClick(TObject* Sender)
{
	ButtonPlay->Visible = false;
	ButtonScores->Visible = false;
	aKey->Visible = false;
	dKey->Visible = false;
	prevPoints = 0;
	game = true;
	colorAllBlocks();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ButtonRestartClick(TObject* Sender)
{
	ButtonRestart->Visible = false;
	ButtonScores->Visible = false;
	StringMain->Visible = false;
	setDefaultValues();
	prevPoints = 0;
	game = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormClose(TObject* Sender, TCloseAction& Action)
{
	setDefaultValues();
	ButtonPlay->Visible = true;
	ButtonScores->Visible = true;
	aKey->Visible = true;
	dKey->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::TimerBallSpeedPointEndTimer(TObject* Sender)
{
	if (ballSpeedy > 0)
	{
		ballSpeedy -= 3;
		if (ballSpeedx > 3)
			ballSpeedx -= 3;
		else if (ballSpeedx < -3)
			ballSpeedx += 3;
	}
	else if (ballSpeedy < 0)
	{
		ballSpeedy += 3;
		if (ballSpeedx > 3)
			ballSpeedx -= 3;
		else if (ballSpeedx < -3)
			ballSpeedx += 3;
	}
	TimerBallSpeedPointEnd->Enabled = false;
	isBallSpeedPoint = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::TimerPaddleSpeedPointEndTimer(TObject* Sender)
{
	paddleSpeed -= 3;
	isPaddleSpeedPoint = false;
	Paddle->Picture->LoadFromFile("img/paddle.bmp");
	TimerPaddleSpeedPointEnd->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::TimerPaddleWidthDownPointEndTimer(TObject* Sender)
{
	Paddle->Width = 120;
	Paddle->Left -= 30;
	TimerPaddleWidthDownPointEnd->Enabled = false;
	isPaddleWidthDownPoint = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::TimerPaddleWidthUpPointEndTimer(TObject* Sender)
{
	Paddle->Width = 120;
	Paddle->Left += 60;
	TimerPaddleWidthUpPointEnd->Enabled = false;
	isPaddleWidthUpPoint = false;
	isPaddleWidthUpPointPicked = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::TimerHyperBallPointEndTimer(TObject* Sender)
{
	sndPlaySound("snd/hyperball.wav", SND_ASYNC);
	if (paddleCollisionTicks >= maxPaddleCollisionTicks)
	{
		isHyperBall = false;
		Ball->Picture->LoadFromFile("img/ball.bmp");
		Ball->Width = 17;
		Ball->Height = 17;
		TimerHyperBallPointEnd->Enabled = false;
		isHyperBallPoint = false;
	}
}
//---------------------------------------------------------------------------
void TForm2::hardinessControl()
{
	hardiness++;
	hardinessx++;
	if (hardiness > 2500)
	{
		if (ballSpeedy > 0)
			ballSpeedy++;
		else if (ballSpeedy < 0)
			ballSpeedy--;
		hardiness = 0;
	}
	if (hardinessx > 3750)
	{
		if (ballSpeedx > 0)
			ballSpeedx++;
		else if (ballSpeedx < 0)
			ballSpeedx--;
		hardinessx = 0;
	}
}
//---------------------------------------------------------------------------
void TForm2::bonusCreateControl(TImage* Block)
{
	int tmp = random(5);
	switch (tmp)
	{
	case 0:
		ballSpeedPointCreate(Block);
		break;
	case 1:
		hyperBallPointCreate(Block);
		break;
	case 2:
		paddleSpeedPointCreate(Block);
		break;
	case 3:
		paddleWidthDownPointCreate(Block);
		break;
	case 4:
		paddleWidthUpPointCreate(Block);
		break;
	}
}
//---------------------------------------------------------------------------
void TForm2::ballSpeedPointCreate(TImage* Block)
{
	if (isBallSpeedPoint == false)
	{
		BallSpeedPoint->Left = Block->Left + Block->Width / 2;
		BallSpeedPoint->Top = Block->Top + Block->Height;
		BallSpeedPoint->Visible = true;
		isBallSpeedPoint = true;
	}
}
//---------------------------------------------------------------------------
void TForm2::ballSpeedPointCollision()
{
	if (isBallSpeedPoint == true)
		BallSpeedPoint->Top += 2;
	if (collision(Paddle, BallSpeedPoint) && isBallSpeedPoint == true && BallSpeedPoint->Visible == true)
	{
		BallSpeedPoint->Visible = false;
		if (ballSpeedy > 0 && ballSpeedx > 0)
		{
			ballSpeedy += 3;
			ballSpeedx += 3;
		}
		else if (ballSpeedy > 0 && ballSpeedx < 0)
		{
			ballSpeedy += 3;
			ballSpeedx -= 3;
		}
		else if (ballSpeedy < 0 && ballSpeedx > 0)
		{
			ballSpeedy -= 3;
			ballSpeedx += 3;
		}
		else if (ballSpeedy < 0 && ballSpeedx < 0)
		{
			ballSpeedy -= 3;
			ballSpeedx -= 3;
		}
		TimerBallSpeedPointEnd->Enabled = true;
	}
	else if (BallSpeedPoint->Top > Background->Height && BallSpeedPoint->Visible == true)
	{
		BallSpeedPoint->Visible = false;
		isBallSpeedPoint = false;
	}
	else if (isBallSpeedPoint == false)
		BallSpeedPoint->Visible == false;
}
//---------------------------------------------------------------------------
bool TForm2::collision(TImage* Object1, TImage* Object2)
{
	if (Object1->Left + Object1->Width > Object2->Left &&
		Object1->Left < Object2->Left + Object2->Width &&
		Object1->Top + Object1->Height > Object2->Top &&
		Object1->Top < Object2->Top + Object2->Height)
		return true;
	else
		return false;
}
//---------------------------------------------------------------------------
void TForm2::colorAllBlocks()
{
	for (int i = 0; i < 60; i++)
	{
		switch (blockHitCount[i])
		{
		case 1:
			Block[i]->Picture->LoadFromFile("img/block5.bmp");
			break;
		case 2:
			Block[i]->Picture->LoadFromFile("img/block4.bmp");
			break;
		case 3:
			Block[i]->Picture->LoadFromFile("img/block3.bmp");
			break;
		case 4:
			Block[i]->Picture->LoadFromFile("img/block2.bmp");
			break;
		case 5:
			Block[i]->Picture->LoadFromFile("img/block1.bmp");
			break;
		case 6:
			Block[i]->Picture->LoadFromFile("img/block.bmp");
			break;
		}
	}
}
//---------------------------------------------------------------------------
void TForm2::hyperBallPointCreate(TImage* Block)
{
	if (isHyperBallPoint == false && wasHyperBallPicked == false && random(5) == 0)
	{
		HyperBallPoint->Left = Block->Left + Block->Width / 2;
		HyperBallPoint->Top = Block->Top + Block->Height;
		HyperBallPoint->Visible = true;
		isHyperBallPoint = true;
	}
}
//---------------------------------------------------------------------------
void TForm2::hyperBallPointCollision()
{
	if (isHyperBallPoint == true)
		HyperBallPoint->Top += 2;
	if (collision(Paddle, HyperBallPoint) && isHyperBallPoint == true && HyperBallPoint->Visible == true)
	{
		paddleCollisionTicks = 0;
		wasHyperBallPicked = true;
		if (ballSpeedy > 0)
			maxPaddleCollisionTicks = 2;
		else if (ballSpeedy < 0)
			maxPaddleCollisionTicks = 1;
		HyperBallPoint->Visible = false;
		isHyperBall = true;
		Ball->Picture->LoadFromFile("img/hyperball.bmp");
		Ball->Width = 34;
		Ball->Height = 34;
		TimerHyperBallPointEnd->Enabled = true;
	}
	else if (HyperBallPoint->Top > Background->Height && HyperBallPoint->Visible == true)
	{
		HyperBallPoint->Visible = false;
		isHyperBallPoint = false;
	}
	else if (isHyperBallPoint == false)
		HyperBallPoint->Visible == false;
}
//---------------------------------------------------------------------------
void TForm2::paddleSpeedPointCreate(TImage* Block)
{
	if (isPaddleSpeedPoint == false)
	{
		PaddleSpeedPoint->Left = Block->Left + Block->Width / 2;
		PaddleSpeedPoint->Top = Block->Top + Block->Height;
		PaddleSpeedPoint->Visible = true;
		isPaddleSpeedPoint = true;
	}
}
//---------------------------------------------------------------------------
void TForm2::paddleSpeedPointCollision()
{
	if (isPaddleSpeedPoint == true)
		PaddleSpeedPoint->Top += 2;
	if (collision(Paddle, PaddleSpeedPoint) && isPaddleSpeedPoint == true && PaddleSpeedPoint->Visible == true)
	{
		Paddle->Picture->LoadFromFile("img/paddleHyper.bmp");
		paddleSpeed += 3;
		PaddleSpeedPoint->Visible = false;
		TimerPaddleSpeedPointEnd->Enabled = true;
	}
	else if (PaddleSpeedPoint->Top > Background->Height && PaddleSpeedPoint->Visible == true)
	{
		PaddleSpeedPoint->Visible = false;
		isPaddleSpeedPoint = false;
	}
	else if (isPaddleSpeedPoint == false)
		PaddleSpeedPoint->Visible == false;
}
//---------------------------------------------------------------------------
void TForm2::paddleWidthDownPointCreate(TImage* Block)
{
	if (isPaddleWidthDownPoint == false && isPaddleWidthUpPoint == false)
	{
		PaddleWidthDownPoint->Left = Block->Left + Block->Width / 2;
		PaddleWidthDownPoint->Top = Block->Top + Block->Height;
		PaddleWidthDownPoint->Visible = true;
		isPaddleWidthDownPoint = true;
	}
}
//---------------------------------------------------------------------------
void TForm2::paddleWidthDownPointCollision()
{
	if (isPaddleWidthDownPoint == true)
		PaddleWidthDownPoint->Top += 2;
	if (collision(Paddle, PaddleWidthDownPoint) && isPaddleWidthDownPoint == true && PaddleWidthDownPoint->Visible == true)
	{
		PaddleWidthDownPoint->Visible = false;
		Paddle->Width = 60;
		Paddle->Left += 30;
		TimerPaddleWidthDownPointEnd->Enabled = true;
	}
	else if (PaddleWidthDownPoint->Top > Background->Height && PaddleWidthDownPoint->Visible == true)
	{
		PaddleWidthDownPoint->Visible = false;
		isPaddleWidthDownPoint = false;
	}
	else if (isPaddleWidthDownPoint == false)
		PaddleWidthDownPoint->Visible == false;
}
//---------------------------------------------------------------------------
void TForm2::paddleWidthUpPointCreate(TImage* Block)
{
	if (isPaddleWidthUpPoint == false && isPaddleWidthDownPoint == false)
	{
		PaddleWidthUpPoint->Left = Block->Left + Block->Width / 2;
		PaddleWidthUpPoint->Top = Block->Top + Block->Height;
		PaddleWidthUpPoint->Visible = true;
		isPaddleWidthUpPoint = true;
	}
}
//---------------------------------------------------------------------------
void TForm2::paddleWidthUpPointCollision()
{
	if (isPaddleWidthUpPoint == true)
		PaddleWidthUpPoint->Top += 2;
	if (collision(Paddle, PaddleWidthUpPoint) && isPaddleWidthUpPoint == true && PaddleWidthUpPoint->Visible == true)
	{
		PaddleWidthUpPoint->Visible = false;
		Paddle->Width = 240;
		Paddle->Left -= 60;
		isPaddleWidthUpPointPicked = true;
		TimerPaddleWidthUpPointEnd->Enabled = true;
	}
	else if (PaddleWidthUpPoint->Top > Background->Height && PaddleWidthUpPoint->Visible == true)
	{
		PaddleWidthUpPoint->Visible = false;
		isPaddleWidthUpPoint = false;
	}
	else if (isPaddleWidthUpPoint == false)
		PaddleWidthUpPoint->Visible == false;
}
//---------------------------------------------------------------------------
void TForm2::setDefaultValues()
{
	Ball->Width = 17;
	Ball->Height = 17;
	Ball->Left = 272 + random(50);
	Ball->Top = 550;
	Ball->Picture->LoadFromFile("img/ball.bmp");
	Ball->Visible = true;
	ballSpeedx = -4;
	ballSpeedy = -4;
	Paddle->Left = 320;
	Paddle->Width = 120;
	paddleSpeed = 8;
	Paddle->Picture->LoadFromFile("img/paddle.bmp");
	BallSpeedPoint->Visible = false;
	PaddleWidthDownPoint->Visible = false;
	PaddleWidthUpPoint->Visible = false;
	HyperBallPoint->Visible = false;
	PaddleSpeedPoint->Visible = false;
	isPaddleSpeedPoint = false;
	isBallSpeedPoint = false;
	isPaddleWidthUpPoint = false;
	isPaddleWidthDownPoint = false;
	isHyperBallPoint = false;
	isPaddleWidthUpPointPicked = false;
	isHyperBall = false;
	game = false;
	points = 0;
	hardiness = 0;
	hardinessx = 0;
	lastBlock = NULL;
	paddleCollisionTicks = 0;
	collisionsIterator = 0;
	maxPaddleCollisionTicks = 0;
	nick = "";
	wasHyperBallPicked = false;
	ButtonRestart->Visible = false;
	ButtonNextLevel->Visible = false;
	ButtonOK->Visible = false;
	StringMain->Visible = false;
	StringScores->Visible = false;
	StringNick->Visible = false;
	EditNick->Visible = false;
	ButtonNickOK->Visible = false;
	for (int i = 0; i < 60; i++)
	{
		blockHitCount[59 - i] = i / 10 + 1;
		Block[i]->Visible = true;
		blocksTrue[i] = true;
	}
	colorAllBlocks();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ButtonScoresClick(TObject* Sender)
{
	if (points > 0)
	{
		ButtonRestart->Visible = false;
		StringMain->Visible = false;
		EditNick->Visible = false;
	}
	else
		ButtonPlay->Visible = false;
	ButtonScores->Visible = false;
	ButtonOK->Visible = true;
	StringScores->Visible = true;
	StringScores->BringToFront();
	StringScores->Caption = score->load().c_str();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ButtonOKClick(TObject* Sender)
{
	if (points > 0 || prevPoints > 0)
	{
		ButtonRestart->Visible = true;
		StringMain->Visible = true;
		EditNick->Visible = true;
	}
	else
		ButtonPlay->Visible = true;
	ButtonScores->Visible = true;
	ButtonOK->Visible = false;
	StringScores->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ButtonNextLevelClick(TObject* Sender)
{
	prevPoints += points;
	ButtonNextLevel->Visible = false;
	setDefaultValues();
	for (int i = 0; i < 60; i++)
		blockHitCount[i] = random(6) + 1;
	colorAllBlocks();
	game = true;
}
//---------------------------------------------------------------------------
__fastcall TForm2::~TForm2()
{
	for (int i = 0; i < 60; i++)
		delete Block[i];
	delete score;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ButtonNickOKClick(TObject* Sender)
{
	nick = EditNick->Text.c_str();
	if (nick == "" || nick.length() > 3)
		return;
	score->save(points + prevPoints, nick);
	score->normalise();
	ButtonNickOK->Visible = false;
	EditNick->Visible = false;
	StringNick->Caption = "Zapisano!";
}
//---------------------------------------------------------------------------

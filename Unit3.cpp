//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3* Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
	score = new Score;
	score->setCurrentGame("SimonSays");
	orderIterator = 0;
	points = 1;
	tmp = NULL;
	randomize();
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			block[3 * i + j] = new TImage(this);
			block[3 * i + j]->Parent = this;
			block[3 * i + j]->Picture->LoadFromFile("img/soundBlockWhite.bmp");
			block[3 * i + j]->Left = j * 100 + 50;
			block[3 * i + j]->Top = i * 100 + 50;
			block[3 * i + j]->OnClick = BlockClick;
			block[3 * i + j]->Cursor = crHandPoint;
			block[3 * i + j]->Enabled = false;
		}
	for (int i = 0; i < 100; i++)
		order[i] = random(9);
}
//---------------------------------------------------------------------------
void __fastcall TForm3::ButtonPlayClick(TObject* Sender)
{
	ButtonPlay->Visible = false;
	TimerSequence->Enabled = true;
	StringMain->Caption = "Zapamiêtaj sekwencjê";
	StringMain->Visible = true;
	ButtonScores->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::BlockClick(TObject* Sender)
{
	for (int i = 0; i < 9; i++)
	{
		if (Sender == block[i])
		{
			activateBlock(i);
			if (i == order[orderIterator] && orderIterator < points - 1)
				orderIterator++;
			else if (i == order[orderIterator] && orderIterator == points - 1)
			{
				points++;
				orderIterator = 0;
				tmp = block[i];
				TimerBeforeSequence->Enabled = true;
				for (int j = 0; j < 9; j++)
					block[j]->Enabled = false;
			}
			else if (i != order[orderIterator])
			{
				tmp = block[i];
				endGame();
			}
		}
	}
}
//---------------------------------------------------------------------------
void TForm3::activateBlock(int blockNumber)
{
	switch (blockNumber)
	{
	case 0: sndPlaySound("snd/block0.wav", SND_ASYNC); break;
	case 1: sndPlaySound("snd/block1.wav", SND_ASYNC); break;
	case 2: sndPlaySound("snd/block2.wav", SND_ASYNC); break;
	case 3: sndPlaySound("snd/block3.wav", SND_ASYNC); break;
	case 4: sndPlaySound("snd/block4.wav", SND_ASYNC); break;
	case 5: sndPlaySound("snd/block5.wav", SND_ASYNC); break;
	case 6: sndPlaySound("snd/block6.wav", SND_ASYNC); break;
	case 7: sndPlaySound("snd/block7.wav", SND_ASYNC); break;
	case 8: sndPlaySound("snd/block8.wav", SND_ASYNC); break;
	}
	block[blockNumber]->Picture->LoadFromFile("img/soundBlockBlue.bmp");
	for (int i = 0; i < 9; i++)
		if (i != blockNumber)
			block[i]->Picture->LoadFromFile("img/soundBlockWhite.bmp");
}
//---------------------------------------------------------------------------
void __fastcall TForm3::TimerSequenceTimer(TObject* Sender)
{
	StringMain->Caption = "Zapamiêtaj sekwencjê";
	if (orderIterator < points)
	{
		activateBlock(order[orderIterator]);
		orderIterator++;
	}
	else
	{
		block[order[orderIterator - 1]]->Picture->LoadFromFile("img/soundBlockWhite.bmp");
		orderIterator = 0;
		TimerSequence->Enabled = false;
		for (int i = 0; i < 9; i++)
			block[i]->Enabled = true;
		StringMain->Caption = "Powtórz sekwencjê";
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm3::TimerBeforeSequenceTimer(TObject* Sender)
{
	tmp->Picture->LoadFromFile("img/soundBlockWhite.bmp");
	StringMain->Caption = "Dobrze!";
	TimerSequence->Enabled = true;
	TimerBeforeSequence->Enabled = false;
}
//---------------------------------------------------------------------------
void TForm3::endGame()
{
	tmp->Picture->LoadFromFile("img/soundBlockRed.bmp");
	StringMain->Caption = "Twój wynik: " + IntToStr(points - 1);
	orderIterator = 0;
	for (int i = 0; i < 100; i++)
		order[i] = random(9);
	ButtonRestart->Visible = true;
	ButtonScores->Visible = true;
	for (int i = 0; i < 9; i++)
		block[i]->Enabled = false;
	if (points < 2)
		return;
	StringNick->Caption = "Aby zapisaæ wynik, podaj nick (max 3 znaki): ";
	StringNick->BringToFront();
	EditNick->BringToFront();
	ButtonNickOK->BringToFront();
	StringNick->Visible = true;
	EditNick->Visible = true;
	ButtonNickOK->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::ButtonRestartClick(TObject* Sender)
{
	points = 1;
	ButtonRestart->Visible = false;
	tmp->Picture->LoadFromFile("img/soundBlockWhite.bmp");
	TimerSequence->Enabled = true;
	StringMain->Caption = "Zapamiêtaj sekwencjê";
	ButtonScores->Visible = false;
	StringNick->Visible = false;
	EditNick->Visible = false;
	ButtonNickOK->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::FormClose(TObject* Sender, TCloseAction& Action)
{
	TimerSequence->Enabled = false;
	for (int i = 0; i < 9; i++)
		block[i]->Picture->LoadFromFile("img/soundBlockWhite.bmp");
	TimerSequence->Enabled = false;
	StringMain->Visible = false;
	points = 1;
	orderIterator = 0;
	for (int i = 0; i < 100; i++)
		order[i] = random(9);
	ButtonPlay->Visible = true;
	ButtonRestart->Visible = false;
	ButtonScores->Visible = true;
	StringScores->Visible = false;
	ButtonOK->Visible = false;
	StringNick->Visible = false;
	EditNick->Visible = false;
	ButtonNickOK->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::ButtonScoresClick(TObject* Sender)
{
	if (points > 0)
		EditNick->Visible = false;
	StringScores->Visible = true;
	StringScores->BringToFront();
	StringScores->Caption = score->load().c_str();
	ButtonScores->Visible = false;
	ButtonOK->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::ButtonOKClick(TObject* Sender)
{
	StringScores->Visible = false;
	ButtonScores->Visible = true;
	ButtonOK->Visible = false;
}
//---------------------------------------------------------------------------
__fastcall TForm3::~TForm3()
{
	for (int i = 0; i < 9; i++)
		delete block[i];
	delete score;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::ButtonNickOKClick(TObject* Sender)
{
	nick = EditNick->Text.c_str();
	if (nick == "" || nick.length() > 3)
		return;
	score->save(points - 1, nick);
	score->normalise();
	ButtonNickOK->Visible = false;
	EditNick->Visible = false;
	StringNick->Caption = "Zapisano!";
}
//---------------------------------------------------------------------------

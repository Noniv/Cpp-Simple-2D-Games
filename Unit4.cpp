//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4* Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm4::ButtonSimonSaysClick(TObject* Sender)
{
	Form3->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::ButtonPongClick(TObject* Sender)
{
	Form1->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm4::ButtonArkanoidClick(TObject* Sender)
{
	Form2->ShowModal();
}
//---------------------------------------------------------------------------

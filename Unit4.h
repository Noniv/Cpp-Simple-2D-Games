//---------------------------------------------------------------------------
#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
	TShape* Background;
	TImage* ButtonArkanoid;
	TImage* ButtonPong;
	TImage* ButtonSimonSays;
	TImage* ImageSimonSays;
	TImage* ImagePong;
	TImage* ImageArkanoid;
	void __fastcall ButtonSimonSaysClick(TObject* Sender);
	void __fastcall ButtonPongClick(TObject* Sender);
	void __fastcall ButtonArkanoidClick(TObject* Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4* Form4;
//---------------------------------------------------------------------------
#endif

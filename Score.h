//---------------------------------------------------------------------------
#ifndef ScoreH
#define ScoreH
//---------------------------------------------------------------------------
#include <algorithm>
#include <fstream>
#include <string>
struct scoreStruct;

class Score
{
	std::string currentGame;
public:
	void setCurrentGame(std::string game);
	void save(int points, std::string nick);
	void normalise();
	void sortScores(scoreStruct array[], int size);
	std::string load();
	std::string getFileName();
};
//---------------------------------------------------------------------------
#endif

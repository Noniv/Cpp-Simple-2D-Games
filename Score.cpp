//---------------------------------------------------------------------------
#pragma hdrstop
#include "Score.h"
#include <time.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)

struct scoreStruct
{
	std::string nick;
	int points;
};


void Score::save(int points, std::string nick)
{
	std::fstream file;
	file.open(getFileName().c_str(), std::ios::out | std::ios::app);
	if (file.good() == false)
		return;
	file << points << std::endl;
	file << nick << std::endl;
	file.close();
}
//---------------------------------------------------------------------------
std::string Score::load()
{
	std::fstream file;
	file.open(getFileName().c_str(), std::ios::in);
	if (file.good() == false)
		return "";
	scoreStruct scoreLine[11];
	for (int i = 0; i < 11; i++)
	{
		scoreLine[i].points = 0;
		scoreLine[i].nick = "";
	}
	int lineNumber = 0;
	std::string line;
	std::string score = "";
	while (getline(file, line) && lineNumber < 22)
	{
		if (lineNumber % 2 == 0)
			scoreLine[lineNumber / 2].points = std::atoi(line.c_str());

		else if (lineNumber % 2 == 1)
			scoreLine[lineNumber / 2].nick = line;

		lineNumber++;
	}
	for (int i = 0; i < 10; i++)
	{
		char tmp1[10];
		char tmp2[10];
		std::itoa(i + 1, tmp1, 10);
		std::itoa(scoreLine[i].points, tmp2, 10);
		if (scoreLine[i].points == 0)
			tmp2[0] = 0;
		if (currentGame == "Arkanoid")
			score = score + tmp1 + ".\t" + scoreLine[i].nick + "\t\t" + tmp2 + "\n";
		else
			score = score + tmp1 + ".\t" + scoreLine[i].nick + "\t" + tmp2 + "\n";
	}
	file.close();
	return score;
}
//---------------------------------------------------------------------------
void Score::normalise()
{
	std::fstream file;
	file.open(getFileName().c_str(), std::ios::in);
	if (file.good() == false)
		return;
	scoreStruct scoreLine[11];
	for (int i = 0; i < 11; i++)
	{
		scoreLine[i].points = 0;
		scoreLine[i].nick = "";
	}
	int lineNumber = 0;
	std::string line;
	while (std::getline(file, line) && lineNumber < 22)
	{
		if (lineNumber % 2 == 0)
			scoreLine[lineNumber / 2].points = std::atoi(line.c_str());
		else if (lineNumber % 2 == 1)
			scoreLine[lineNumber / 2].nick = line;
		lineNumber++;
	}
	file.close();

	sortScores(scoreLine, 11);

	std::ofstream file2(getFileName().c_str());
	if (file2.good() == false)
		return;
	for (int i = 0; i < 10; i++)
	{
		file2 << scoreLine[i].points << std::endl;
		file2 << scoreLine[i].nick << std::endl;
	}
	file2.close();
}
//---------------------------------------------------------------------------
void Score::setCurrentGame(std::string game)
{
	currentGame = game;
}
//---------------------------------------------------------------------------
std::string Score::getFileName()
{
	std::string fileName = currentGame;
	fileName = "scr/" + fileName + "Scores.txt";
	return fileName;
}
//---------------------------------------------------------------------------
void Score::sortScores(scoreStruct array[], int size)
{
	bool swapped;

	do
	{
		swapped = false;
		for (int i = 0; i < size - 1; i++)
		{
			if (array[i].points < array[i + 1].points)
			{
				std::swap(array[i], array[i + 1]);
				swapped = true;
			}
		}
	} while (swapped == true);
}

#ifndef _GAME_
#define _GAME_

#include "Board.h"
#include "Pieces.h"
#include "IO.h"
#include <time.h>


// Время в миллисекундах, которое фигура остается на поле перед тем, как опустится на 1 блок
#define WAIT_TIME 700

class Game
{
public:
	// Конструктор класса Game
	Game(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight);

	void DrawScene ();
	void CreateNewPiece ();

	//Позиция, тип и тип вращения фигуры
	int mPosX, mPosY;	
	int mPiece, mRotation;

private:
	//объявление переменных для 1) Высоты экрана 2) позиции нового блока 3) типа блока и типа вращения
	int mScreenHeight;			
	int mNextPosX, mNextPosY;	
	int mNextPiece, mNextRotation;

	// Указатели для взаимодействия с полем, фигурами и вводом
	Board *mBoard;
	Pieces *mPieces;
	IO *mIO;

	int GetRand (int pA, int pB);
	void InitGame();
	void DrawPiece (int pX, int pY, int pPiece, int pRotation);
	void DrawBoard ();
};

#endif

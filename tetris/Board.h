#ifndef _BOARD_
#define _BOARD_


#include "Pieces.h"


// Определяем константы для размеров и параметров игрового поля
#define BOARD_LINE_WIDTH 6         // Ширина каждой из двух линий, которые ограничивают игровое поле
#define BLOCK_SIZE 16             // Ширина и высота каждого блока фигуры
#define BOARD_POSITION 110        // Центр игрового поля от левого края экрана
#define BOARD_WIDTH 10            // Ширина игрового поля в блоках
#define BOARD_HEIGHT 20           // Высота игрового поля в блоках
#define MIN_VERTICAL_MARGIN 20    // Мин вертикальный отступ от границы игрового поля
#define MIN_HORIZONTAL_MARGIN 20 // Мин горизонтальный отступ от границы игрового поля
#define PIECE_BLOCKS 5            // Число горизонтальных и вертикальных блоков в матрице фигуры


class Board
{
public:

	Board						(Pieces *pPieces, int pScreenHeight);

	int GetXPosInPixels			(int pPos);
	int GetYPosInPixels			(int pPos);
	bool IsFreeBlock			(int pX, int pY);
	bool IsPossibleMovement		(int pX, int pY, int pPiece, int pRotation);
	void StorePiece				(int pX, int pY, int pPiece, int pRotation);
	void DeletePossibleLines	();
	bool IsGameOver				();

private:
	enum { POS_FREE, POS_FILLED };			// POS_FREE - блок типа 0(ничего нет); POS_FILLED - блок типа 1 или 2(там что то есть)
	int mBoard [BOARD_WIDTH][BOARD_HEIGHT];	//массив, который хранит значения свободных\занятых блоков
	Pieces *mPieces;
	int mScreenHeight;

	void InitBoard();
	void DeleteLine (int pY);
};

#endif

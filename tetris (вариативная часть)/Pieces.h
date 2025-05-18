#ifndef _PIECES_
#define _PIECES_


class Pieces //Класс для работы с фигурами
{
public:

	int GetBlockType		(int pPiece, int pRotation, int pX, int pY);//тип блока с информацией о положении и повороте
	int GetXInitialPosition (int pPiece, int pRotation);//начальная позиция по оси x
	int GetYInitialPosition (int pPiece, int pRotation);//начальная позиция по оси y
};
#endif

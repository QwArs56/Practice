#include "Board.h"

// Иницилизация 
Board::Board (Pieces *pPieces, int pScreenHeight)
{
	mScreenHeight = pScreenHeight;
	mPieces = pPieces;

	InitBoard();
}


void Board::InitBoard()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
		for (int j = 0; j < BOARD_HEIGHT; j++)
			mBoard[i][j] = POS_FREE;
}

void Board::StorePiece (int pX, int pY, int pPiece, int pRotation)
{
	// Store each block of the piece into the board
	for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++)
		{	
			// Store only the blocks of the piece that are not holes
			if (mPieces->GetBlockType (pPiece, pRotation, j2, i2) != 0)		
				mBoard[i1][j1] = POS_FILLED;	
		}
	}
}



bool Board::IsGameOver()
{
	//игра кончается когда первая линия(сверху) имеет блок типа 1 или 2
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		if (mBoard[i][0] == POS_FILLED) return true;
	}

	return false;
}



void Board::DeleteLine (int pY)
{
	//сдвиг линий вниз(что еще имеют пропуски)
	for (int j = pY; j > 0; j--)
	{
		for (int i = 0; i < BOARD_WIDTH; i++)
		{
			mBoard[i][j] = mBoard[i][j-1];
		}
	}	
}

//удаление заполненных линий
void Board::DeletePossibleLines ()
{
	for (int j = 0; j < BOARD_HEIGHT; j++)
	{
		int i = 0;
		while (i < BOARD_WIDTH)
		{
			if (mBoard[i][j] != POS_FILLED) break;
			i++;
		}

		if (i == BOARD_WIDTH) DeleteLine (j);
	}
}



bool Board::IsFreeBlock (int pX, int pY)
{
	if (mBoard [pX][pY] == POS_FREE) return true; else return false;
}


// Возвращает горизонт. позицию блока в пикселях для указанной позиции на поле
int Board::GetXPosInPixels (int pPos)
{
	return  ( ( BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) ) + (pPos * BLOCK_SIZE) );
}

// Возвращает верт. позицию блока в пикселях для указанной позиции на поле
int Board::GetYPosInPixels (int pPos)
{
	return ( (mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (pPos * BLOCK_SIZE) );
}


/* 
Проверяет, можно ли разместить фигуру в указанной позиции без столкновений(c другими фигурами, со стенами)
Возвращает true, если движение возможно, false - невозможно.
*/
bool Board::IsPossibleMovement (int pX, int pY, int pPiece, int pRotation)
{
	for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++)
		{
			// Проверка, находится ли фигура за пределами поля
			if (i1 < 0 ||
				i1 > BOARD_WIDTH - 1 ||
				j1 > BOARD_HEIGHT - 1)
			{
				// Если блок фигуры выходит за пределы поля и он не пустой, возвращаем false
				if (mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0)
					return 0;
			}

			// Проверка, не столкнулась ли фигура с уже размещенными блоками
			if (j1 >= 0)
			{
				// Если блок фигуры не пустой и не свободен, возвращаем false
				if ((mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0) &&
					(!IsFreeBlock(i1, j1)))
					return false;
			}
		}
	}
	return true;
}
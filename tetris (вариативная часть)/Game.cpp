#include <windows.h>
#include "Game.h"


Game::Game(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight) 
{
	mScreenHeight = pScreenHeight;

	// ѕолучаем указатели на другие классы
	mBoard = pBoard;
	mPieces = pPieces;
	mIO = pIO;

	InitGame ();
}



int Game::GetRand (int pA, int pB)
{
	return rand () % (pB - pA + 1) + pA;
}


void Game::InitGame()
{
	srand ((unsigned int) time(NULL));

	//ѕараметры первой падающей фигуры
	mPiece			= GetRand (0, 6);
	mRotation		= GetRand (0, 3);
	mPosX 			= (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition (mPiece, mRotation);
	mPosY 			= mPieces->GetYInitialPosition (mPiece, mRotation);

	//следующей фигуры
	mNextPiece 		= GetRand (0, 6);
	mNextRotation 	= GetRand (0, 3);
	mNextPosX 		= BOARD_WIDTH + 5;
	mNextPosY 		= 5;	
}


//генератор тетромины
void Game::CreateNewPiece()
{
	//параметры нового падающего блока
	mPiece			= mNextPiece;
	mRotation		= mNextRotation;
	mPosX 			= (BOARD_WIDTH / 2) + mPieces->GetXInitialPosition (mPiece, mRotation);
	mPosY 			= mPieces->GetYInitialPosition (mPiece, mRotation);

	//«адаем случайно тип и позицию вращени€
	mNextPiece 		= GetRand (0, 6);
	mNextRotation 	= GetRand (0, 3);
}



const color pieceColors[7] = {RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE};

void Game::DrawPiece(int pX, int pY, int pPiece, int pRotation)
{
	// ¬ыбираем цвет фигуры по типу
	color mColor = pieceColors[pPiece];

	// ѕолучаем позицию фигуры на экране
	int mPixelsX = mBoard->GetXPosInPixels(pX);
	int mPixelsY = mBoard->GetYPosInPixels(pY);

	// –исуем каждый блок фигуры
	for (int i = 0; i < PIECE_BLOCKS; i++)
	{
		for (int j = 0; j < PIECE_BLOCKS; j++)
		{
			// ѕроверка, есть ли блок в этом месте (1 или 2)
			if (mPieces->GetBlockType(pPiece, pRotation, j, i) != 0)
			{
				mIO->DrawRectangle(
					mPixelsX + i * BLOCK_SIZE,
					mPixelsY + j * BLOCK_SIZE,
					(mPixelsX + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
					(mPixelsY + j * BLOCK_SIZE) + BLOCK_SIZE - 1,
					mColor
				);
			}
		}
	}
}

void Game::DrawBoard ()
{
	//ѕарамерты границ пол€
	int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
	int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
	int mY = mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT);
	

	//–исование этих границ в виде пр€моугольников
	mIO->DrawRectangle (mX1 - BOARD_LINE_WIDTH, mY, mX1, mScreenHeight - 1, BLUE);
	mIO->DrawRectangle (mX2, mY, mX2 + BOARD_LINE_WIDTH, mScreenHeight - 1, BLUE);
	

	// ќтрисовка уже упавших блоков
	mX1 += 1;
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{	
			//проверка типа блока, тип больше 0 - отрисовать
			if (!mBoard->IsFreeBlock(i, j))	
				mIO->DrawRectangle (	mX1 + i * BLOCK_SIZE, 
										mY + j * BLOCK_SIZE, 
										(mX1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1, 
										(mY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, 
										RED);
		}
	}	
}


//отрисовка экрана(поле, падающий кусок, следующий кусок)
void Game::DrawScene ()
{
	DrawBoard ();												
	DrawPiece (mPosX, mPosY, mPiece, mRotation);				
	DrawPiece (mNextPosX, mNextPosY, mNextPiece, mNextRotation);
}

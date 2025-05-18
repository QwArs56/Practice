#include "Game.h"            // Подключение заголовочного файла с объявлениями классов и функций для игры
#include <windows.h>

// Главная функция для Windows-приложения, точка входа программы
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	
	IO mIO; // Создание объекта для работы с графикой (отображение на экране), используется SDL
	int mScreenHeight = mIO.GetScreenHeight();// Получение высоты экрана

	Pieces mPieces;// Создание объекта для работы с тетромино (фигуры)
	Board mBoard(&mPieces, mScreenHeight);// Создание объекта для игрового поля
	Game mGame(&mBoard, &mPieces, &mIO, mScreenHeight);
	unsigned long mTime1 = SDL_GetTicks();

	// Пока не нажата клавиша ESC
	while (!mIO.IsKeyDown(SDLK_ESCAPE))
	{
		//Отображение на экране
		//Очищение экрана, рисование сцены, обновление сцены на следующем кадре
		mIO.ClearScreen();
		mGame.DrawScene();
		mIO.UpdateScreen();     

		//Обработка ввода
		// Получаем код нажатой клавиши
		int mKey = mIO.Pollkey();

		switch (mKey)
		{
		//Правая клавиша
		case (SDLK_RIGHT):
		{
			// Проверка, можно ли переместить фигуру вправо
			if (mBoard.IsPossibleMovement(mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
				mGame.mPosX++;
			break;
		}

		//Левая клавиша
		case (SDLK_LEFT):
		{
			// Проверяем, можно ли переместить фигуру влево
			if (mBoard.IsPossibleMovement(mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
				mGame.mPosX--;
			break;
		}

		//Клавиша вниз
		case (SDLK_DOWN):
		{
			// Проверяем, можно ли переместить фигуру вниз
			if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
				mGame.mPosY++;
			break;
		}

		// Если нажата клавиша "X" (быстрое падение фигуры)
		case (SDLK_x):
		{
			// Проверяем, можно ли перемещать фигуру до самого низа
			while (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation)) {
				mGame.mPosY++;  // Опускаем фигуру до первого препятствия
			}

			// Сохраняем фигуру в игровом поле
			mBoard.StorePiece(mGame.mPosX, mGame.mPosY - 1, mGame.mPiece, mGame.mRotation);

			
			mBoard.DeletePossibleLines();// Удаляем заполненые линии

			if (mBoard.IsGameOver())
			{
				mIO.Getkey();  // Ожидаем нажатие клавиши
				exit(0);
			}

			// Создаем новую фигуру
			mGame.CreateNewPiece();
			break;
		}

		// Если нажата клавиша "Z" (поворот фигуры)
		case (SDLK_z):
		{
			// Проверяем, можно ли повернуть фигуру
			if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation + 1) % 4))
				mGame.mRotation = (mGame.mRotation + 1) % 4;//Поварачиваем фигуру(меняем ее состояние)
			break;
		}
		}

		//Вертикальное движение

		// Получаем текущее время для отслеживания интервала
		unsigned long mTime2 = SDL_GetTicks();

		// Если прошло достаточно времени (по таймеру)
		if ((mTime2 - mTime1) > WAIT_TIME)
		{
			// Проверяем, можно ли переместить фигуру вниз
			if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
			{
				mGame.mPosY++;
			}
			else
			{
				// Сохраняем фигуру в игровом поле
				mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);
				mBoard.DeletePossibleLines();

				if (mBoard.IsGameOver())
				{
					mIO.Getkey();  
					exit(0);
				}

				mGame.CreateNewPiece();
			}

			
			mTime1 = SDL_GetTicks(); // Обновляем время для следующего движения
		}
	}
	return 0;
}
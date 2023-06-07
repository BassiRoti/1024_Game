#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <iomanip>
using namespace std;

const int ROWS = 4;
const int COLS = 4;

void initializeBoard(int board[][COLS]);      // initialize board with first two boxes
void generateRandomNumber(int board[][COLS]); // generate random number at random position on the board
void printBoard(int board[][COLS]);

bool moveUp(int board[][COLS]);
bool moveUpReArrange(int board[][COLS]);

bool moveDown(int board[][COLS]);
bool moveDownReArrange(int board[][COLS]);

bool moveRight(int board[][COLS]);
bool moveRightReArrange(int board[][COLS]);

bool moveLeft(int board[][COLS]);
bool moveLeftReArrange(int board[][COLS]);


bool isGoalReach(int board[][COLS]);  // check if any of the box has value 1024
bool isGameOver(int board[][COLS]); // check if every index is filled and not two consecutive numbers are same

int main(int argc, char** argv) {

	int board[ROWS][COLS] = { 0 };
	srand(time(0));

	initializeBoard(board);
	system("color 3D");
	printBoard(board);

	char inputCommand;

	while (!isGoalReach(board) && !isGameOver(board)) {

		inputCommand = _getch();

		cout << "Input Command: " << inputCommand << endl;

		switch (inputCommand) {

		case 'u': {
			bool isBoardChange = moveUp(board);
			if (isBoardChange) {
				generateRandomNumber(board);
			}

			break;
		}
		case 'd': {
			bool isBoardChange = moveDown(board);
			if (isBoardChange) {
				generateRandomNumber(board);
			}

			break;
		}
		case 'l': {
			bool isBoardChange = moveLeft(board);
			if (isBoardChange) {
				generateRandomNumber(board);
			}

			break;
		}
		case 'r': {

			bool isBoardChange = moveRight(board);
			if (isBoardChange) {
				generateRandomNumber(board);
			}

			break;
		}
		}
		system("cls");
		printBoard(board);
	}

	if (isGoalReach(board)) {

		cout << "Congratulations!!! You win/n";
	}
	else {
		cout << "Game OVER !!!\n";
	}
	system("pause");
	return 0;
}


void printBoard(int board[ROWS][COLS]) {

	char upLeft = (char)201;
	char upRight = (char)187;
	char horizontal = (char)205;
	char downLeft = (char)200;
	char downRight = (char)188;
	char plusShape = (char)206;
	char down = (char)203;
	char up = (char)202;
	char left = (char)204;
	char right = (char)185;
	char vertical = (char)186;

	cout << upLeft;
	for (int i = 0; i < ROWS - 1; i++) {
		cout << horizontal << horizontal << horizontal << horizontal << horizontal << horizontal << horizontal << down;
	}
	cout << horizontal << horizontal << horizontal << horizontal << horizontal << horizontal << horizontal << upRight << endl;
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j <= ROWS; j++)
			cout << vertical << "\t";
		cout << endl;
		for (int k = 0; k < COLS; k++) {
			if (board[i][k] != 0) {
				cout << vertical << setw(4) << board[i][k] << setw(4);
			}
			else {
				cout << vertical << setw(4) << " " << setw(4);
			}

		}
		cout << vertical;
		cout << endl;

		if (i != ROWS - 1) {
			for (int l = 0; l <= ROWS; l++)
				cout << vertical << "\t";
			cout << endl << left;
			for (int m = 0; m < ROWS - 1; m++) {
				cout << horizontal << horizontal << horizontal << horizontal << horizontal << horizontal << horizontal << plusShape;
			}
			cout << horizontal << horizontal << horizontal << horizontal << horizontal << horizontal << horizontal << right << endl;
		}
	}
	for (int i = 0; i <= ROWS; i++) {
		cout << vertical << "\t";
	}
	cout << endl << downLeft;
	for (int i = 0; i < ROWS - 1; i++) {
		cout << horizontal << horizontal << horizontal << horizontal << horizontal << horizontal << horizontal << up;
	}
	cout << horizontal << horizontal << horizontal << horizontal << horizontal << horizontal << horizontal << downRight << endl;

}

void generateRandomNumber(int board[ROWS][COLS]) {

	while (true) {

		int row = rand() % ROWS;
		int col = rand() % COLS;

		if (board[row][col] == 0) {
			board[row][col] = rand() % 2 + 1;
			break;
		}
	}
}
void initializeBoard(int board[ROWS][COLS]) {

	generateRandomNumber(board);
	generateRandomNumber(board);
}

bool moveUp(int board[][COLS]) {

	bool isBoardChanged = false, isBoardChangedDuringReArrange = false;
	bool boardStateChanged = false;
	isBoardChangedDuringReArrange = moveUpReArrange(board);

	for (int j = 0; j < COLS; j++) {

		for (int i = 0; i < ROWS - 1; i++) {
			if (board[i][j] == board[i + 1][j] && board[i][j] != 0) {
				board[i][j] = board[i][j] * 2;
				board[i + 1][j] = 0;
				isBoardChanged = true;
			}
		}
	}
	if (isBoardChanged) {
		moveUpReArrange(board);
	}
	boardStateChanged = isBoardChanged || isBoardChangedDuringReArrange;

	return boardStateChanged;
}

bool moveUpReArrange(int board[][COLS]) {

	// "i,j" represent indexes of first iterator
	//      * first iterator find non zero element which will be moved up
	// "l,m" represent indexes of second iterator
	//      * Second iterator find the location of box [where the non-zero element (identified by first iterator) will be moved / copied]
	int l = 0;
	bool isBoardChanged = false;

	for (int j = 0, m = 0; j < COLS; j++, m++) {

		l = 0;
		for (int i = 0; i < ROWS; i++) {

			if (board[i][j] != 0 && i != 0) { // find first non zero number in a column to move it up (Do not move up if it is already in top row "i.e. i=0")

				if (board[l][m] != 0) {
					l++;
				}

				if (i != l) {

					board[l][m] = board[i][j];
					board[i][j] = 0;
					isBoardChanged = true;
				}
			}
		}
	}
	return isBoardChanged;
}

bool moveDown(int board[][COLS]) {

	bool isBoardChanged = false, isBoardChangedDuringReArrange = false;
	bool boardStateChanged = false;
	isBoardChangedDuringReArrange = moveDownReArrange(board);

	for (int j = 0; j < COLS; j++) {

		for (int i = ROWS - 1; i >= 0; i--) {
			if (board[i][j] == board[i - 1][j] && board[i][j] != 0) {
				board[i][j] = board[i][j] * 2;
				board[i - 1][j] = 0;
				isBoardChanged = true;
			}
		}
	}
	if (isBoardChanged) {
		moveDownReArrange(board);
	}
	boardStateChanged = isBoardChanged || isBoardChangedDuringReArrange;

	return boardStateChanged;
}

bool moveDownReArrange(int board[][COLS]) {

	int l;
	bool isBoardChanged = false;

	for (int j = 0, m = 0; j < COLS; j++, m++) {

		l = ROWS - 1;
		for (int i = ROWS - 1; i >= 0; i--) {

			if (board[i][j] != 0 && i != (ROWS - 1)) { // find first non zero number in a column to move it up (Do not move up if it is already in top row "i.e. i=0")

				if (board[l][m] != 0) {
					l--;
				}

				if (i != l) {

					board[l][m] = board[i][j];
					board[i][j] = 0;
					isBoardChanged = true;
				}
			}
		}
	}
	return isBoardChanged;
}

bool moveRight(int board[][COLS]) {

	bool isBoardChanged = false, isBoardChangedDuringReArrange = false;
	bool boardStateChanged = false;
	isBoardChangedDuringReArrange = moveRightReArrange(board);

	for (int i = 0; i < ROWS; i++) {

		for (int j = COLS - 1; j >= 0; j--) {
			if (board[i][j] == board[i][j - 1] && board[i][j] != 0) {
				board[i][j] = board[i][j] * 2;
				board[i][j - 1] = 0;
				isBoardChanged = true;
			}
		}
	}
	if (isBoardChanged) {
		moveRightReArrange(board);
	}
	boardStateChanged = isBoardChanged || isBoardChangedDuringReArrange;

	return boardStateChanged;
}

bool moveRightReArrange(int board[][COLS]) {


	bool isBoardChanged = false;

	for (int i = 0, l = 0; i < ROWS; i++, l++) {

		int m = COLS - 1;
		for (int j = COLS - 1; j >= 0; j--) {

			if (board[i][j] != 0 && j != COLS - 1) {

				if (board[l][m] != 0) {
					m--;
				}

				if (j != m) {

					board[l][m] = board[i][j];
					board[i][j] = 0;
					isBoardChanged = true;
				}
			}
		}
	}
	return isBoardChanged;
}

bool moveLeft(int board[][COLS]) {

	bool isBoardChanged = false, isBoardChangedDuringReArrange = false;
	bool boardStateChanged = false;
	isBoardChangedDuringReArrange = moveLeftReArrange(board);

	for (int i = 0; i < ROWS; i++) {

		for (int j = 0; j < COLS - 1; j++) {
			if (board[i][j] == board[i][j + 1] && board[i][j] != 0) {
				board[i][j] = board[i][j] * 2;
				board[i][j + 1] = 0;
				isBoardChanged = true;
			}
		}
	}
	if (isBoardChanged) {
		moveLeftReArrange(board);
	}
	boardStateChanged = isBoardChanged || isBoardChangedDuringReArrange;

	return boardStateChanged;
}

bool moveLeftReArrange(int board[][COLS]) {


	bool isBoardChanged = false;

	for (int i = 0, l = 0; i < ROWS; i++, l++) {

		int m = 0;
		for (int j = 0; j < COLS; j++) {

			if (board[i][j] != 0 && j != 0) {

				if (board[l][m] != 0) {
					m++;
				}

				if (j != m) {

					board[l][m] = board[i][j];
					board[i][j] = 0;
					isBoardChanged = true;
				}
			}
		}
	}
	return isBoardChanged;
}

bool isGoalReach(int board[][COLS]) {

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {

			if (board[i][j] == 1024) {
				return true; // this function return true when any of the cell / box reaches value 1024
			}
		}
	}
	return false;
}

bool isGameOver(int board[][COLS]) {

	// check if every index is filled and not two consecutive numbers are same
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {

			if (board[i][j] == 0) {
				return false;
			}
		}
	}

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS - 1; j++) {

			if (board[i][j] == board[i][j + 1]) {
				return false;
			}
		}
	}

	for (int j = 0; j < COLS; j++) {
		for (int i = 0; i < ROWS - 1; i++) {

			if (board[i][j] == board[i + 1][j]) {
				return false;
			}
		}
	}

	return true;
}

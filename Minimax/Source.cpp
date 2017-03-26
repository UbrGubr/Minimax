#include<iostream>
#include<string>
#include<stdlib.h>

const int PAWN = 100;
const int BISH = 305;
const int KNIGHT = 300;
const int ROOK = 500;
const int KING = 2000;

const int pawn = -100;
const int bish = -305;
const int knight = -300;
const int rook = -500;
const int king = -2000;

int board[8][6];

const int startup[8][6] = {
	0, 0, 0, 0, king, 0,
	knight, bish, rook, rook, bish, knight,
	0, 0, 0, pawn, 0, 0,
	0, 0, pawn, 0, 0, 0,
	0, 0, 0, 0, KNIGHT, 0,
	0, 0, PAWN, PAWN, 0, 0,
	KNIGHT, BISH, ROOK, ROOK, BISH, 0,
	0, KING, 0, 0, 0, 0,
};

void SetupBoard(void)
{
	int i, j;
	for (i = 0; i<8; i++)
	{
		for (j = 0; j<6; j++)
		{
			board[i][j] = startup[i][j];
		}
	}
}

void PrintBoard(void)
{
	using namespace std;

	int col, row;
	string piece;

	for (col=7; col>=0; col--)
	{
		cout << endl << col + 1 << "  ";
		for (row=0; row<6; row++)
		{
			switch(board[col][row])
			{
				case 0:
					piece = "-";
					break;
				case PAWN:
					piece = "P";
					break;
				case KNIGHT:
					piece = "N";
					break;
				case BISH:
					piece = "B";
					break;
				case ROOK:
					piece = "R";
					break;
				case KING:
					piece = "K";
					break;
				case pawn:
					piece = "p";
					break;
				case knight:
					piece = "n";
					break;
				case bish:
					piece = "b";
					break;
				case rook:
					piece = "r";
					break;
				case king:
					piece = "k";
					break;
			}
			cout << piece << " ";
		}
	}
	cout << endl << endl << "   A B C D E F" << endl << endl;
}

bool ValidateMove(int colSource, int rowSource, int colDest, int rowDest)
{
	using namespace std;
	
	cout << "colSource=" << colSource << " rowSource=" << rowSource << " colDest=" << colDest << " rowDest=" << rowDest << endl;

	// check if destination position is the same as source
	if ((rowSource == rowDest) && (colSource == colDest))
	{
		cout << "Illegal: Start and End positions cannot be the same" << endl;
		return false;
	}
	

	bool valid = false;
	int xDelta = colDest - colSource;
	int yDelta = rowDest - rowSource;

	switch (board[rowSource][colSource])
	{

		case 0:
			cout << "Illegal: There is no game piece in the source location" << endl;
			break;
		case bish:
			cout << "Moving bish" << endl;
			if(abs(xDelta) == abs(yDelta)) // moving diagonally, legal
			{
				if (xDelta > 0 && yDelta > 0) // moving forward-right, legal
				{
					if (board[rowSource+1][colSource+1] < 0) // check if the next piece is friendly, illegal
					{
						cout << "   Illegal: The next position in your desired move is friendly" << endl;
						return false;
					}
					cout << "   moving bishop forward-right" << endl;
					/*
					for (; rowSource<rowDest && colSource<colDest; rowSource++, colSource++)
					{
						if (board[rowSource+1][colSource+1] != 0) // encountered another game piece
						{
							if (isupper(board[rowSource][colSource])) // opponent piece
							{
								// take the piece, move our piece to this position
							}
							else // our own piece
							{
								// move our piece to previous position
							}
						}
					}
					*/
					valid = true;
				}
				else if (xDelta < 0 && yDelta > 0) // moving forward-left
				{
					if (board[rowSource+1][colSource-1] < 0) // check if the next piece is friendly, illegal
					{
						cout << "   Illegal: The next position in your desired move is friendly" << endl;
						return false;
					}
					cout << "   moving bishop forward-left" << endl;
					valid = true;
				}
			}
			break;
		case BISH:
			cout << "Moving BISH" << endl;
			if (abs(xDelta) == abs(yDelta))
			{
				if ((xDelta < 0 && yDelta < 0) || (xDelta > 0 && yDelta < 0)) // moving forward
				{
					cout << "   ...moving forward" << endl;
					valid = true;
				}
			}
			break;
	}

	return valid;
}

int main(void)
{
	using namespace std;

	string response;
	bool human_moves_first = true;

	while ((response.substr(0,1) != "y") && (response.substr(0,1) != "n")) 
	{
		cout << "Would you like to make the first move? (y/n):";
		getline(cin, response);
	}
	if (response.substr(0, 1) == "n") { human_moves_first = false; }

	SetupBoard();
	PrintBoard();
	
	while(1){
		cout << "Enter move:";
		getline(cin, response);

		if(response.substr(0, 1) >= "A" && response.substr(0, 1) <= "F"
			&& response.substr(1, 1) >= "1" && response.substr(1, 1) <= "8"
			&& response.substr(2, 1) >= "A" && response.substr(2, 1) <= "F"
			&& response.substr(3, 1) >= "1" && response.substr(3, 1) <= "8")
		{
			int rowSource, colSource, rowDest, colDest;
			colSource = response[0] - 'A';
			rowSource = response[1] - '1';
			colDest = response[2] - 'A';
			rowDest = response[3] - '1';

			if (ValidateMove(colSource, rowSource, colDest, rowDest))
			{
				board[rowDest][colDest] = board[rowSource][colSource];
				board[rowSource][colSource] = 0;
			}
			else
			{
				cout << "Illegal move detected: " << colSource << rowSource << " -> " << colDest << rowDest << endl;
			}
			//board[d][c] = board[b][a];
			//board[b][a] = 0;
		}
		else
		{
			cout << endl << "Illegal: the move is outside of the game bounds" << endl << endl;
		}
		PrintBoard();
	}
}
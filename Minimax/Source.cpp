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
	0, 0, 0, 0, 0, 0,
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
			cout << "Moving player's bishop..." << endl;
			if(abs(xDelta) == abs(yDelta)) // Player moving diagonally, legal
			{
				if (xDelta > 0 && yDelta > 0) //Player moving forward-right, legal
				{
					if (board[rowSource + 1][colSource + 1] < 0) // if the next piece in our move is friendly, illegal
					{
						cout << "   Illegal: The next position in your desired move is friendly" << endl;
						return false;
					}
					cout << "   ...moving forward-right" << endl;

					bool keep_moving = true;
					int rowCurr = rowSource;
					int colCurr = colSource;
					for (; rowCurr<rowDest && colCurr<colDest && keep_moving; rowCurr++, colCurr++)
					{
						if(board[rowCurr + 1][colCurr + 1] < 0) // encountered friendly game piece, stop here
						{
							keep_moving = false;
							cout << "   ...next position holds a friendly piece, stopping here";
						}
						else if(board[rowCurr + 1][colCurr + 1] > 0) // encountered enemy piece in next position, make move and then stop
						{
							board[rowCurr + 1][colCurr + 1] = board[rowCurr][colCurr];
							board[rowCurr][colCurr] = 0;
							keep_moving = false;
							cout << "   ...captured an enemy piece at " << rowCurr+1 << colCurr+1 << endl;
						}
						else // next space is empty, make move and keep going
						{
							board[rowCurr + 1][colCurr + 1] = board[rowCurr][colCurr];
							board[rowCurr][colCurr] = 0;
							keep_moving = true;
						}
					}

					valid = true;
				}
				else if (xDelta < 0 && yDelta > 0) // Player moving forward-left, legal
				{
					if (board[rowSource - 1][colSource + 1] < 0) // if the next piece in our move is friendly, illegal
					{
						cout << "   Illegal: The next position in your desired move is friendly" << endl;
						return false;
					}
					cout << "   ...moving forward-left" << endl;

					bool keep_moving = true;
					int rowCurr = rowSource;
					int colCurr = colSource;
					for (; rowCurr<rowDest && colCurr>colDest && keep_moving; rowCurr++, colCurr--)
					{
						if (board[rowCurr + 1][colCurr - 1] < 0) // encountered friendly game piece, stop here
						{
							keep_moving = false;
							cout << "   ...next position holds a friendly piece, stopping here";
						}
						else if (board[rowCurr + 1][colCurr - 1] > 0) // encountered enemy piece in next position, make move and then stop
						{
							board[rowCurr + 1][colCurr - 1] = board[rowCurr][colCurr];
							board[rowCurr][colCurr] = 0;
							keep_moving = false;
							cout << "   ...captured an enemy piece at " << rowCurr+1 << colCurr-1 << endl;
						}
						else // next space is empty, make move and keep going
						{
							board[rowCurr + 1][colCurr - 1] = board[rowCurr][colCurr];
							board[rowCurr][colCurr] = 0;
							keep_moving = true;
						}
					}

					valid = true;
				}
			}
			break;
		case BISH:
			cout << "Moving computer's bishop..." << endl;
			if (abs(xDelta) == abs(yDelta))	// Computer is moving diagonally, legal
			{
				if (xDelta < 0 && yDelta < 0) // Computer moving forward-right, legal
				{
					if (board[rowSource - 1][colSource - 1] > 0) // if the next piece in our move is friendly, illegal
					{
						cout << "   Illegal: The next position in your desired move is friendly" << endl;
						return false;
					}

					cout << "   ...moving forward-right" << endl;

					bool keep_moving = true;
					int rowCurr = rowSource;
					int colCurr = colSource;
					for (; rowCurr>rowDest && colCurr>colDest && keep_moving; rowCurr--, colCurr--)
					{
						if (board[rowCurr - 1][colCurr - 1] > 0) // encountered friendly game piece, stop here
						{
							keep_moving = false;
							cout << "   ...next position holds a friendly piece, stopping here";
						}
						else if (board[rowCurr - 1][colCurr - 1] < 0) // encountered enemy piece in next position, make move and then stop
						{
							board[rowCurr - 1][colCurr - 1] = board[rowCurr][colCurr];
							board[rowCurr][colCurr] = 0;
							keep_moving = false;
							cout << "   ...captured an enemy piece at " << rowCurr - 1 << colCurr - 1 << endl;
						}
						else // next space is empty, make move and keep going
						{
							board[rowCurr - 1][colCurr - 1] = board[rowCurr][colCurr];
							board[rowCurr][colCurr] = 0;
							keep_moving = true;
						}
					}
					valid = true;
				}
				else if (xDelta > 0 && yDelta < 0)
				{
					if (board[rowSource - 1][colSource + 1] > 0) // if the next piece in our move is friendly, illegal
					{
						cout << "   Illegal: The next position in your desired move is friendly" << endl;
						return false;
					}

					cout << "   ...moving forward-left" << endl;

					bool keep_moving = true;
					int rowCurr = rowSource;
					int colCurr = colSource;
					for (; rowCurr > rowDest && colCurr < colDest && keep_moving; rowCurr--, colCurr++)
					{
						if (board[rowCurr - 1][colCurr + 1] > 0) // encountered friendly game piece, stop here
						{
							keep_moving = false;
							cout << "   ...next position holds a friendly piece, stopping here";
						}
						else if (board[rowCurr - 1][colCurr + 1] < 0) // encountered enemy piece in next position, make move and then stop
						{
							board[rowCurr - 1][colCurr + 1] = board[rowCurr][colCurr];
							board[rowCurr][colCurr] = 0;
							keep_moving = false;
							cout << "   ...captured an enemy piece at " << rowCurr - 1 << colCurr + 1 << endl;
						}
						else // next space is empty, make move and keep going
						{
							board[rowCurr - 1][colCurr + 1] = board[rowCurr][colCurr];
							board[rowCurr][colCurr] = 0;
							keep_moving = true;
						}
					}
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
				//board[rowDest][colDest] = board[rowSource][colSource];
				//board[rowSource][colSource] = 0;
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
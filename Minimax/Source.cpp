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

	int a, b;
	string piece;

	for (a=7; a>=0; a--)
	{
		cout << endl << a + 1 << "  ";
		for (b=0; b<6; b++)
		{
			switch(board[a][b])
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
			int a, b, c, d;
			a = response[0] - 'A';
			b = response[1] - '1';
			c = response[2] - 'A';
			d = response[3] - '1';

			board[d][c] = board[b][a];
			board[b][a] = 0;
			PrintBoard();

		}
	}
}
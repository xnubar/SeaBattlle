#include <iostream>
#include <time.h>
#include <conio.h>
using namespace std;

const int row = 10;
const int col = 10;
int board[row][col];
int board_comp[row][col];


struct Person {
	char name[100];
	char surname[100];
};


struct SHIPS {
	char name[100];
	int length;
	int count;
};


void PersonalData(Person*player) {
	getchar();
	cout << "Enter your name: ";
	cin.getline(player[0].name, 100);
	cout << "Enter your surname: ";
	cin.getline(player[0].surname, 100);
	cout << "\n\n\t********************************************************" << endl;
	cout << "\t\t WELCOME TO SEA BATTLE, " << player[0].name << " " << player[0].surname << "!" << endl;
	cout << " \t\t\t\tGOOD LUCK!" << endl;
	cout << "\t********************************************************" << endl;
	cout << endl;
}


void ship_info(SHIPS *ship) {
	strcpy_s(ship[0].name, "battleship"); ship[0].length = 1; ship[0].count = 4;
	strcpy_s(ship[1].name, "cruiser"); ship[1].length = 2; ship[1].count = 3;
	strcpy_s(ship[2].name, "destroyer"); ship[2].length = 3; ship[2].count = 2;
	strcpy_s(ship[3].name, "submarine"); ship[3].length = 4; ship[3].count = 1;
}


void print_player_board(Person* player) {
	cout << "\n\n\n\n\t\t<<<<<" << player[0].name << " " << player[0].surname << "'S BOARD>>>>>>\n\t ______________________________________________\n\n\t\t\tX\n\n";

	cout << "\t    0 1 2 3 4 5 6 7 8 9" << endl;
	cout << "\t   ---------------------\n";
	for (int y = 0; y < col; y++) {
		if (y == 5)
			cout << "Y";
		if (y < 10)
			cout << "\t " << y << " ";
		else
			cout << " " << y << " ";
		cout << "|";
		for (int x = 0; x < row; x++)
		{
			if (board[x][y] == 0)
				cout << ' ';
			else if (board[x][y]>-10&&board[x][y]<=-1)
				cout << 'X';
			else if (board[x][y] > 0 && board[x][y] < 11)
				cout << char(219);
			else if (board[x][y] == -100)
				cout << '.';
			cout << '|';
		}
		cout << endl;
	}
	cout << "\t   ---------------------\n\n\n";
}


void print_comp_board() {
	cout << "\n\n\n\n\t\t <<<<<COMPUTER'S BOARD>>>>>\n\t ______________________________________________\n\n\t\t\tX\n\n";
	cout << "\t    0 1 2 3 4 5 6 7 8 9" << endl;
	cout << "\t   ---------------------\n";
	for (int y = 0; y < col; y++) {
		if (y == 5)
			cout << "Y";
		if (y < 10)
			cout << "\t " << y << " ";
		else
			cout << " " << y << " ";
		cout << "|";
		for (int x = 0; x < row; x++) {
			if (board_comp[x][y] >= 0 && board_comp[x][y] < 11)
				cout << ' ';
			else if (board_comp[x][y] == -100)
				cout << '.';
			else if (board_comp[x][y]>-10&&board_comp[x][y]<=-1)
				cout << 'X';
			cout << '|';
		}
		cout << endl;
	}
	cout << "\t   ---------------------\n\n\n";
}


void set_coord_space_B(int count, int field[10][10]) {
	int x, y;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (field[i][j] == count) {
				x = i;
				y = j;
				if (x - 1 >= 0 && y - 1 >= 0 && field[x - 1][y - 1] == 0)
					field[x - 1][y - 1] = -100;
				if (y - 1 >= 0 && field[x][y - 1] == 0)
					field[x][y - 1] = -100;
				if (x + 1 <= 9 && y - 1 >= 0 && field[x + 1][y - 1] == 0)
					field[x + 1][y - 1] = -100;
				if (x + 1 <= 9 && field[x + 1][y] == 0)
					field[x + 1][y] = -100;
				if (x + 1 <= 9 && y + 1 <= 9 && field[x + 1][y + 1] == 0)
					field[x + 1][y + 1] = -100;
				if (y + 1 <= 9 && field[x][y + 1] == 0)
					field[x][y + 1] = -100;
				if (x - 1 >= 0 && y + 1 <= 9 && field[x - 1][y + 1] == 0)
					field[x - 1][y + 1] = -100;
				if (x - 1 >= 0 && field[x - 1][y] == 0)
					field[x - 1][y] = -100;
			}
		}
	}
}


void deleteNegatives() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (board_comp[i][j] < 0)
				board_comp[i][j] = 0;
		}
	}
}


void set_ships_player(int board[10][10], SHIPS*ship, Person *player) {
	int x;
	int y;
	int count = 1;
	int shipcol;
	int shiprow;
	char coords;
	int k;
	for (int i = 0; i < 4; i++) {
		k = 1;
		while (k <= ship[i].count) {
			system("cls");
			print_player_board(player);
			cout << k << "." << ship[i].name << " -> x:"; cin >> x;
			cout << k << "." << ship[i].name << " -> y:"; cin >> y;
			cout << "<H/V?>: "; cin >> coords;
			if ((coords == 'H' || coords == 'h') && x + ship[i].length <= 10 && board[x][y] == 0) {
				for (shiprow = 0; shiprow < ship[i].length; shiprow++) {
					board[x + shiprow][y] = count;
					set_coord_space_B(count, board);
				}
				system("cls");
				print_player_board(player);
				k++;
				count++;
			}
			else if ((coords == 'V' || coords == 'v') && y + ship[i].length <= 10 && board[x][y] == 0) {
				for (shipcol = 0; shipcol < ship[i].length; shipcol++) {
					board[x][y + shipcol] = count;
					set_coord_space_B(count, board);

				}
				system("cls");
				print_player_board(player);
				k++;
				count++;
			}
			else if ((y + ship[i].count <= 10 || x + ship[i].count <= 10) || board[x][y] != 0)
				cout << "Enter coordinates correctly!: \n";
		}
	}
	system("cls");
	print_player_board(player);
}


void set_ships_comp(SHIPS *ship) {
	srand(time(0));
	int count_ship = 10;
	int z = 1;
	int comp_x;
	int comp_y;
	int comp_ship_col;
	int comp_ship_row;
	int comp_h;
	for (int i = 3; i >= 0; i--) {
		z = 1;
		while (z <= ship[i].count) {
			comp_h = rand() % 2;
			comp_x = rand() % 10;
			comp_y = rand() % 10;
			if (comp_h == 1 && comp_x + ship[i].length < 10 && board_comp[comp_x][comp_y] == 0 && board_comp[comp_x + ship[i].length - 1][comp_y] == 0) {
				for (comp_ship_row = 0; comp_ship_row < ship[i].length; comp_ship_row++) {
					board_comp[comp_x + comp_ship_row][comp_y] = count_ship;
					set_coord_space_B(count_ship, board_comp);
				}
				count_ship--;
				z++;
			}
			else if (comp_h == 0 && comp_y + ship[i].length < 10 && board_comp[comp_x][comp_y] == 0 && board_comp[comp_x][comp_y + ship[i].length - 1] == 0) {
				for (comp_ship_col = 0; comp_ship_col < ship[i].length; comp_ship_col++) {
					board_comp[comp_x][comp_y + comp_ship_col] = count_ship;
					set_coord_space_B(count_ship, board_comp);
				}
				count_ship--;
				z++;
			}
		}
	}
	deleteNegatives();
	print_comp_board();
}


void player_board_initial(Person* player, int board[10][10]) {
	cout << "\n\n\n\n\t\t<<<<<" << player[0].name << " " << player[0].surname << "'S BOARD>>>>>>\n\t ______________________________________________\n\n\t\t\tX\n\n";

	cout << "\t    0 1 2 3 4 5 6 7 8 9" << endl;
	cout << "\t   ---------------------\n";
	for (int y = 0; y < col; y++) {
		if (y == 5)
			cout << "Y";
		if (y < 10)
			cout << "\t " << y << " ";
		else
			cout << " " << y << " ";
		cout << "|";
		for (int x = 0; x < row; x++) {
			board[x][y] = 0;
			if (board[x][y] == 0)
			{
				cout << ' ';
			}
			cout << '|';
		}
		cout << endl;
	}
	cout << "\t   ---------------------\n\n\n";
}


void comp_board_initial() {
	cout << "\n\n\n\n\t\t <<<<<COMPUTER'S BOARD>>>>>\n\t______________________________________________\n\n\t\t\tX\n\n";
	cout << "\t    0 1 2 3 4 5 6 7 8 9" << endl;
	cout << "\t   ---------------------\n";
	for (int comp_y = 0; comp_y < col; comp_y++) {
		if (comp_y == 5)
			cout << "Y";
		if (comp_y < 10)
			cout << "\t " << comp_y << " ";
		else
			cout << " " << comp_y << " ";
		cout << "|";
		for (int comp_x = 0; comp_x < row; comp_x++) {
			board_comp[comp_x][comp_y] = 0;
			if (board_comp[comp_x][comp_y] == 0)
				cout << ' ';
			cout << '|';
		}
		cout << endl;
	}
	cout << "\t   ---------------------\n\n\n";
}


void hit_comp(Person *player, SHIPS *ship) {
	srand(time(0));
	int sth = 1;
	int score_player =0;
	int ship_number;
	int score_comp =0;
	int turn_toplay;
	int hit_comp_x;
	int hit_comp_y;
	int hit_player_x;
	int hit_player_y;
	int destroyed = 0;
	cout << "Who will start first? <Player-1/Computer-0>: ";
	cin >> turn_toplay;
	int score = 0;
	while (score_comp < 21 && score_player < 21) {
		if (turn_toplay % 2 != 0) {
			cout << "player: " << score_player << endl;
			cout << "comp: " << score_player<<endl;
			cout << "Player's turn.\n";
			print_comp_board();
			do
			{
				cout << "Computer_X: "; cin >> hit_comp_x;
				cout << "Computer_Y: "; cin >> hit_comp_y;
			} while (board_comp[hit_comp_x][hit_comp_y] < 0);
			if (board_comp[hit_comp_x][hit_comp_y] > 0) {
				ship_number = board_comp[hit_comp_x][hit_comp_y];
				board_comp[hit_comp_x][hit_comp_y] = -ship_number;
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						if (board_comp[i][j] == ship_number)
							destroyed++;
					}
				}
				if (destroyed == 0)
					set_coord_space_B(-ship_number, board_comp);
				score_player++;
			}
			else
			{
				board_comp[hit_comp_x][hit_comp_y] = -100;
				cout << "It's missed.\n";
			}
			system("cls");
			print_comp_board();
		}
		else {
			cout << "Computer's turn.\n";
			print_player_board(player);
			do {
				hit_player_x = rand() % 10;
				hit_player_y = rand() % 10;
			} while (board[hit_player_x][hit_player_y]<0);
			if (board[hit_player_x][hit_player_y] > 0) {
				ship_number = board[hit_player_x][hit_player_y];
				board[hit_player_x][hit_player_y] = -ship_number;
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						if (board[i][j] == ship_number)
							destroyed++;
					}
				}
				if (destroyed == 0)
					set_coord_space_B(-ship_number, board);
				score_comp++;
			}
			else {
				board[hit_player_x][hit_player_y] = -100;
				cout << "It's missed.\n";
			}
			system("cls");
			print_player_board(player);
		}
		turn_toplay++;
		destroyed = 0;
	}
	print_player_board(player);
	print_comp_board();
	if (score_comp > score_player)
		cout << "COMPUTER IS WINNER!!!\n";
	else if (score_player > score_comp)
		cout << player[0].name << " " << player[0].surname << " IS WINNER!!!\n";
}


void main() {
	int x = 0;
	int y = 0;
	Person *player = new Person[0];
	SHIPS *ship = new SHIPS[4];
	ship_info(ship);
	char start;
	cout << "Do you wanna start to the game? <Y/N>: ";
	while (true) {
		cin >> start;
		switch (start) {
		case 'Y':
		case'y':PersonalData(player);
			player_board_initial(player, board);
			comp_board_initial();
			set_ships_player(board, ship, player);
			set_ships_comp(ship);
			hit_comp(player, ship); break;
		case'N':
		case 'n': cout << "\t\t\tGOODBYE!" << endl; exit(0); break;
		default: cout << "Make your choice correctly!\nEnter your your choice again: "; break;
		}
	}
}
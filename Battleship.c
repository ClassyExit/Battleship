/****************************************************************************
> Name: Alex
> Date: 10/21/19
> Assignment: Battleship - PA6

> Description: This program simulates a game of battleship against an A.I.
			The game is completly text-based. The objective is to sink your oppenents
			ships before they sink yours! First player to achieve destroying their
			opponents ships, wins! You have 5 ships - a carrier, battleship,
			cruiser, submarine, and destoyer. Each have a pre-defined length.
			The game alternates with turns between the two players each time
			asking for coordinates to launch an attack. All data is outputted to
			a log file which can be accessed after the game is over.

***************************************************************************/

#include "PA6.h"


/****************************************************************************
	Function: welcome_screen()
	Date Created : 10/23/2019
	Date Last Modified :
	Description : Displays the rules for Battleship.
	Input parameters : N/A
	Returns : N/A
	Preconditions : N/A
	Postconditions : Displays the rules to the screen.
***************************************************************************/
void welcome_screen(void)
{
	char userInput[20];
	do {
		system("cls");
		puts("******************************Welcome to Battleship******************************");
		puts("> This is a two-player game: Player1 is you and player2 is an A.I.");
		puts("> The rules of Battleship are as follows:");
		puts("1) Initially, you will place your ships. You will have an option of placing manually or automatically.");
		puts("1.2) There are a total of 5 ships with each ship a specific length shown in parentheses:");
		puts(" Carrier (5), Battleship (4), Cruiser (3), Submarine(3), Destroyer (2).");
		puts("2) You may only place ships vertically or horizontally. Ships can not be stacked upon one another.");
		puts("3) A ship must remain inside the 10x10 grid. You can not have a part of the ship outside the bounds of the grid.");
		puts("4) Once the game starts, you may not change the positions of your ships.");
		puts("5) Each player will take turns inputting coordinates where you would like to hit. You many only launch one hit per turn.");
		puts("6) If a hit is successful, the grid will contain an '*' that shows you made a hit. Otherwise, if you miss, the grid will display a 'm' for miss.");
		puts("7) The player that first sinks the opponents ships is the winner!\n");

		puts("Press Enter to continue");
		fgets(userInput, 20, stdin);

	} while (userInput[0] != '\n');
	system("cls");
}

/****************************************************************************
	Function: initialize_game_board()
	Date Created : 10/23/19
	Date Last Modified :
	Description : This modifies the 10x10 grid (board) so that all components of
				the struct are modified accordingly
	Input parameters : The board array
	Returns : The updates board array
	Preconditions : Must initialize the players board
	Postconditions : Initializes the board based on the struct
***************************************************************************/
char initialize_game_board(Cell board[ROWS][COLUMNS])
{
	int i = 0, j = 0;
	char a = 40;

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLUMNS; j++)
		{
			board[i][j].symbol = '-'; //initializes symbol to - of each cell on board
			board[i][j].occupied = 0; //sets occupied to 0
			board[i][j].hidden = '~'; //sets hidden to '~'
			board[i][j].hidden_occupied = 0; 
			
		}
	}

	return board;
}


/****************************************************************************
	Function: print_board()
	Date Created : 11/3/19
	Date Last Modified :
	Description : Prints the gameboard 
	Input parameters : Board which you want printed
	Returns : n/a
	Preconditions : Must have a board initialized
	Postconditions : Prints board to the screen
***************************************************************************/
void print_board(Cell board[ROWS][COLUMNS])
{
	int i = 0, j = 0;
	printf("    0  1  2  3  4  5  6  7  8  9 ");
	printf("\n");
	for (i = 0; i < ROWS; i++)
	{
		printf(" %d ", i);

		for (j = 0; j < COLUMNS; j++)
		{
			printf(" %c ", board[i][j].symbol);
		}
		printf("\n");
	}

}


/****************************************************************************
	Function: print_hidden_board()
	Date Created : 11/3/19
	Date Last Modified :
	Description : prints a 'hidden' board where all cells are displayed as
				'~'. This function is used when attacking the other players 
				board to avoid seeing where the opponents ship are.
	Input parameters : Board
	Returns : void
	Preconditions : 
	Postconditions : Prints the board to the screen
***************************************************************************/
void print_hidden_board(Cell board[ROWS][COLUMNS])
{
	int i = 0, j = 0;
	printf("    0  1  2  3  4  5  6  7  8  9 ");
	printf("\n");
	for (i = 0; i < ROWS; i++)
	{
		printf(" %d ", i);

		for (j = 0; j < COLUMNS; j++)
		{
			printf(" %c ", board[i][j].hidden);
		}
		printf("\n");
	}
}


/****************************************************************************
	Function: determine_who_starts()
	Date Created : 10/30/19
	Date Last Modified :
	Description : Outputs a random number between 1-2 to determine who gets to
				start the game. 1 = player 1, 2 = AI.
	Input parameters : n/a
	Returns : int value between 1-2
	Preconditions : n/a
	Postconditions : prints out a message to screen saying who goes first. Additionally
					returns the int value of random choice.
***************************************************************************/
int determine_who_starts(void)
{
	int random = 0;

	random = rand() % 2 + 1;
	puts("At random selection:");
	if (random == 1) //User goes 1st
	{
		puts("Player 1 goes first!");
	}
	else if (random == 2) //A.I. goes 1st
	{
		puts("The A.I. goes first");
	}

	return random;
}

/****************************************************************************
	Function: proceed()
	Date Created : 10/29/19
	Date Last Modified :
	Description : Basic function used to continue the game by inputting any key
				to continue the game before a clear screen is performed.
	Input parameters : n/a
	Returns : n/a
	Preconditions : n/a
	Postconditions : Prints out a message asking user to press any key to continue.
***************************************************************************/
void proceed(void)
{
	/*char temp[100] = "";

	puts("\nPress any key to continue");
	fgets(temp, 1, stdin);*/
	//do {
		puts("\nPress any key to continue");
		getch();

	//} while (getch() == '\n');
}

/****************************************************************************
	Function: manually_place_ships()
	Date Created : 10/29/19
	Date Last Modified :
	Description : This function performs the manuall ship placement onto the board.
				The function asks the user for a certain amount of coordinates
				until the desired ship length is met. In addition, it performs 
				an error check to determine if the inputs are valid. 
	Input parameters : gameboard, int ship size, char ship_symbol, ship_name_str,
				practice_board. 
	Returns : n/a
	Preconditions : must have all the input available and set.
	Postconditions : updates the gameboard based on ship placements
***************************************************************************/
void manually_place_ships(Cell gameboard[ROWS][COLUMNS], int ship_size, char ship_symbol, char str_ship_name[], Cell practice_board[ROWS][COLUMNS])
{
	//Variables
	int valid = 0; //Error checking variable 
	int row[5] = { 0 }, col[5] = { 0 }; //Stores coordinates
	int i = 0, j = 0; //loop variables
	int error_count = 0;
	char userInput[] = { '\0' };

	//printf("Input %d coordinates for the %s:\n", ship_size, str_ship_name);

	while (valid != 1)
	{

		for (i = 0; i < ship_size; i++) //coordinates entered by user
		{
			system("cls");
			printf("Input %d coordinates for the %s:\n", ship_size, str_ship_name);
			print_board(practice_board);
			printf("Input %d coordinates (row, column) for the %s.\n", ship_size, str_ship_name);
			scanf("%d %d", &row[i], &col[i]);
			practice_board[row[i]][col[i]].symbol = ship_symbol;
		}
	
		//system("cls");
		print_board(practice_board);

		//check if positions on gameboard are open (valid)
		for (i = 0; i < ship_size; i++)
		{
			if (gameboard[row[i]][col[i]].occupied != 0)
			{
				//puts("You cannot stack ships on top of one another!");
				error_count++;
				//printf("Error count = %d\n", error_count);
			}
		}

		//check bounds
		for (i = 0; i < ship_size; i++)
		{
			if (row[i] > 10 || row[i] < 0) //check top & bottom bounds
			{
				//puts("Must place ships within bounds!");
				error_count++;
				//printf("Error count = %d\n", error_count);
			}
			if (col[i] > 10 || col[i] < 0) //checks left and right bounds
			{
				//puts("Must place ships within bounds!");
				error_count++;
				//printf("Error count = %d\n", error_count);
			}
			
		}

		//check for diagonal placement
		if ((row[0] != row[ship_size -1]) && (col[0] != col[ship_size -1]))
		{
			//puts("Can not place ships diagonally!");
			error_count++;
			//printf("Error count = %d\n", error_count);
		}
		
		//check for continuous placement
		if ((row[ship_size - 1] - row[0] == ship_size-1) || (col[ship_size - 1] - col[0] == ship_size -1))
		{
			
		}
		else
		{
			error_count++;
		}

		if (error_count == 0)
		{
			valid = 1;
			puts("All your ships have been successfully placed!");

			for (i = 0; i < ship_size; i++)
			{
				gameboard[row[i]][col[i]].symbol = ship_symbol;
				gameboard[row[i]][col[i]].occupied = 1;
			}
			//print_board(gameboard);
		}
		else
		{
			puts("Invalid placement, please try again.");
			valid = 0;
			error_count = 0;
			for (i = 0; i < ship_size; i++)
			{
				practice_board[row[i]][col[i]].symbol = gameboard[row[i]][col[i]].symbol;
			}
			do {
				puts("Press any key to redeploy your ship.");
				getch();
			
			} while (getch() == '\n');
		}
	}
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLUMNS; j++)
		{
			gameboard[i][j].hidden = '~';
		}
	}
	proceed();
	system("cls");
}


/****************************************************************************
	Function: automatically_place_ships()
	Date Created : 11/2/19
	Date Last Modified :
	Description : This function places ships automatically based on their length.
				The functions initially picks a random coordinates and adds the
				length either horizontally or vertically. It is executed in a 
				while loop until a valid placement is found with no overlap.
	Input parameters : gameboard, int ship_size, char ship_symbol
	Returns : n/a
	Preconditions : must initialize gameboard, have ship size, and a symbol to 
					represent the ship on the board.
	Postconditions : Updates the board with the ships
***************************************************************************/
void automatically_place_ships(Cell gameboard[ROWS][COLUMNS], int ship_size, char ship_symbol)
{
	int random_direction = 0; // Used to determine direction -> 1: Horizontal, 2: Vertical
	int error_count= 0; //counts errors
	int row[5] = { 0 }, col[5] = { 0 };
	int i = 0, j = 0;
	int valid = 0;
	int runs = 0;

	random_direction = rand() % 2 + 1; //determines random number between 1 and 2.
	//random_direction = 1;

	if (random_direction == 1) //horizontal placement
	{
		while (valid == 0)
		{
			error_count = 0;
			runs++;
			//Random coordinate to place intial ship
			row[0] = rand() % COLUMNS; //row
			col[0] = rand() % (COLUMNS - ship_size); //column 
			//printf("Row[%d] = %d, Col[%d] = %d\n", 0, row[0], 0, col[0]);
			
			//Add length to ship
			for (i = 1; i < ship_size; i++) //starts at i = 1 since we already have the 0 index
			{
				row[i] = row[0]; //row not changing
				col[i] = col[i - 1] + 1; //column increments by one each time from the 0 index, continuously	
			}

			//check for overlapping (valid placements on board)
			for (i = 0; i < ship_size; i++)
			{

				if (gameboard[row[i]][col[i]].occupied != 0)
				{
					//spot already taken;
					error_count++; //adds one to error
				}
			}

			if (error_count == 0) //if no errors then place ships on board
			{
				valid = 1;
				//no errors; can place ships on board
				for (i = 0; i < ship_size; i++)
				{
					gameboard[row[i]][col[i]].symbol = ship_symbol;
					gameboard[row[i]][col[i]].occupied = 1;
				}
			}
			else
			{
				//has overlaps 
				valid = 0; //not valid - has to reloop
			}
		}
		//once spots are valid -> print to gameboard
		for (i = 0; i < ship_size; i++)
		{
			gameboard[row[i]][col[i]].occupied = 1;
			gameboard[row[i]][col[i]].symbol = ship_symbol;

		}
	}
	else if (random_direction == 2) //vertical placement
	{
		while (valid == 0)
		{
			error_count = 0;
			runs++;
			//Random coordinate to place intial ship
			row[0] = rand() % (ROWS - ship_size); //row
			col[0] = rand() % ROWS; //column 
			//printf("Row[%d] = %d, Col[%d] = %d\n", 0, row[0], 0, col[0]);

			//Add length to ship
			for (i = 1; i < ship_size; i++) //starts at i = 1 since we already have the 0 index
			{
				row[i] = row[i - 1] + 1; //row changing
				col[i] = col[0]; //col not changing 
			}

			//check for overlapping (valid placements on board)
			for (i = 0; i < ship_size; i++)
			{
				if (gameboard[row[i]][col[i]].occupied != 0)
				{
					//spot already taken;
					error_count++; //adds one to error
				}
			}

			if (error_count == 0)
			{
				valid = 1;
				//no errors; can place ships on board
				for (i = 0; i < ship_size; i++)
				{
					gameboard[row[i]][col[i]].symbol = ship_symbol;
					gameboard[row[i]][col[i]].occupied = 1;
				}
			}
			else
			{
				//has overlaps 
				valid = 0; //not valid - has to reloop
			}
		}
		
		//once spots are valid -> print to gameboard
		for (i = 0; i < ship_size; i++)
		{
			gameboard[row[i]][col[i]].occupied = 1;
			gameboard[row[i]][col[i]].symbol = ship_symbol;

		}
	}
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLUMNS; j++)
		{
			gameboard[i][j].hidden = '~';
		}
	}
}


/****************************************************************************
	Function: rand_num()
	Date Created : 11/2/19
	Date Last Modified :
	Description : Returns a random value between 1-2.
	Input parameters : n/a
	Returns : int 
	Preconditions : n/a
	Postconditions : n/a
***************************************************************************/
int rand_num(void)
{
	int random = 0;

	random = rand() % 2 + 1;

	return random;
}

/****************************************************************************
	Function: check_shot()
	Date Created : 11/3/19
	Date Last Modified : 
	Description : This function checks coordinates to the shot inputted by
				the user. If it is a hit, it updates the ship_size by minusing
				1 to the total ship length (doesn't alter the actual ship_size). 
				Once the ship length is 0, then it means the ship sunk. 
	Input parameters : gameboard, row_coord, col_coord, player_ship_size array
	Returns : the result of the shot -> 1 = hit, 0 = miss.
	Preconditions : n/a
	Postconditions : n/a
***************************************************************************/
int check_shot(Cell gameboard[ROWS][COLUMNS], int row_coordinate, int col_coordinate, int playerships_array[])
{
	int result = 0;

	if (gameboard[row_coordinate][col_coordinate].symbol == 'c')
	{
		result = 1; //hit
		playerships_array[0]--; //minuses one from total length of ship. Once 0, means ship sunk.
	}
	else if (gameboard[row_coordinate][col_coordinate].symbol == 'b')
	{
		result = 1; //hit
		playerships_array[1]--;
	}
	else if (gameboard[row_coordinate][col_coordinate].symbol == 'r')
	{
		result = 1; //hit
		playerships_array[2]--;
	}
	else if (gameboard[row_coordinate][col_coordinate].symbol == 's')
	{
		result = 1; //hit
		playerships_array[3]--;
	}
	else if (gameboard[row_coordinate][col_coordinate].symbol == 'd')
	{
		result = 1; //hit
		playerships_array[4]--;
	}
	else
	{
		result = 0; //miss
	}

	return result;
}

/****************************************************************************
	Function: is_winner()
	Date Created : 11/3/19
	Date Last Modified :
	Description : determines if there is a winner by checking the hits that were
				successful. Additionally, prints out the winner to the file. 
	Input parameters : Stats struct of player1, AI, and output file. 
	Returns : returns 1 if p1 win, returns 2 if AI wins, else 0 if no winner yet.
	Preconditions : Must have a file to output to. 
	Postconditions : Prints out to the file. Returns if any winners.
***************************************************************************/
int is_winner(Stats player1, Stats AI, FILE *output_file)
{
	if (player1.hit == 17)
	{
		//player 1 wins
		puts("Player 1 wins!");
		fprintf(output_file, "Player 1 wins!\n");
		return 1;
	}
	else if (AI.hit == 17)
	{
		//AI wins
		puts("The AI wins!");
		fprintf(output_file, "The AI wins!\n");
		return 2;
	}
	else
	{
		//no winner yet
		return 0;
	}
}

/****************************************************************************
	Function: update_board()
	Date Created : 11/3/19
	Date Last Modified :
	Description : Updates the gameboard based on the coordinates inputted by the user.
	Input parameters : gameboard, check_shot, row_coord, col_coord.
	Returns : n/a
	Preconditions : Must call check_shot before. 
	Postconditions : Updates the gameboard.
***************************************************************************/
void update_board(Cell gameboard[ROWS][COLUMNS], int result_check_shot, int row_coordinate, int col_coordinate)
{
	if (result_check_shot == 1) //hit
	{
		gameboard[row_coordinate][col_coordinate].hidden = '*';
		gameboard[row_coordinate][col_coordinate].hidden_occupied = 1;
	}
	else //miss
	{
		gameboard[row_coordinate][col_coordinate].hidden = 'm';
		gameboard[row_coordinate][col_coordinate].hidden_occupied = 1;
	}
}

/****************************************************************************
	Function: output_current_move()
	Date Created : 11/3/19
	Date Last Modified :
	Description : Outputs to the output file the coordinates of the players turn and
				whether it was a hit or miss. Additionally, if a ship is sunk, 
				it prints to the output file. 
	Input parameters : output file, result_check_shot, result_ship_sunk, row_coord
					col_coord, player_name_str.
	Returns : prints to the output file
	Preconditions : Must get result of check_shot, result of check_if_ship_sunk
	Postconditions : n/a
***************************************************************************/
void output_current_move(FILE *output_file, int result_check_shot, int result_ship_sunk, int row_coordinate, int col_coordinate, char player[])
{
	//coordinates selected
	//hit or miss
	//ship sunk or not
	char miss[] = "miss", hit[] = "hit", carrier[] = "carrier", battleship[] = "battleship", sub[] = "submarine", destroyer[] = "destroyer", cruiser[] = "cruiser";

	fprintf(output_file, " %s chose %d, %d\n", player, row_coordinate, col_coordinate); //prints coordinates
	if (result_check_shot == 1) //hit
	{
		fprintf(output_file, "%d, %d is a %s!\n", row_coordinate, col_coordinate, hit); //prints if hit
	}
	else //miss
	{
		fprintf(output_file, "%d, %d is a %s!\n", row_coordinate, col_coordinate, miss); //prints if miss
	}


	if (result_ship_sunk == 1) //carrier sunk
	{
		fprintf(output_file, "%s %s has been sunk!\n", player, carrier);
	}
	else if (result_ship_sunk == 2) //battleship sunk
	{
		fprintf(output_file, "%s %s has been sunk!\n", player, battleship);
	}
	else if (result_ship_sunk == 3) //cruiser sunk
	{
		fprintf(output_file, "%s %s has been sunk!\n", player, cruiser);
	}
	else if (result_ship_sunk == 4) //sub sunk
	{
		fprintf(output_file, "%s %s has been sunk!\n", player, sub);
	}
	else if (result_ship_sunk == 5) //destroyer sunk
	{
		fprintf(output_file, "%s %s has been sunk!\n", player, destroyer);
	}

}


/****************************************************************************
	Function: AI_random_coords()
	Date Created : 11/3/19
	Date Last Modified :
	Description : This function gets AI coords and checks if the coords
				are valid or not. Repeats until valid. 
	Input parameters : AI coords[], gameboard 
	Returns : n/a
	Preconditions : n/a
	Postconditions : n/a
***************************************************************************/
void AI_random_coords(int AI_coords[], Cell user_gameboard[ROWS][COLUMNS])
{
	int valid = 0;
	
	while (valid != 1)
	{
		AI_coords[0] = rand() % 10; //row
		AI_coords[1] = rand() % 10;	//col

		//check if already used. 
		if (user_gameboard[AI_coords[0]][AI_coords[1]].hidden == '~')
		{
			//not used
			valid = 1;
		}
		else
		{
			//repeat
			valid = 0;
		}
	}
	printf("The AI striked %d, %d\n", AI_coords[0], AI_coords[1]);
	
}

/****************************************************************************
	Function: check_if_ship_sunk()
	Date Created : 11/3/19
	Date Last Modified :
	Description : This function checks if a ship sinks. 
	Input parameters : player_ship size+array, player_name_str
	Returns : result of ship. If 1 = carrier sunk, 2 = battleship sunk, etc. 
				0 = miss.
	Preconditions : n/a
	Postconditions : n/a
***************************************************************************/
int check_if_ship_sunk(int player_ship_arr[], char playername[])
{
	int result = 0;
	if (player_ship_arr[0] == 0) //carrier sunk
	{
		result = 0; //carrier code
		player_ship_arr[0] = -1; //update array to -1 to remove ship from list of choices in the future
		printf("%s's carrier has sunk!\n", playername);
	}
	else if (player_ship_arr[1] == 0) //battleship sunk
	{
		result = 1;
		player_ship_arr[1] = -1;
		printf("%s's battleship has sunk!\n", playername);
	}
	else if (player_ship_arr[2] == 0) //cruiser sunk
	{
		result = 2;
		player_ship_arr[2] = -1;
		printf("%s's cruiser has sunk!\n", playername);
	}
	else if (player_ship_arr[3] == 0) //sub sunk
	{
		result = 3;
		player_ship_arr[3] = -1;
		printf("%s's submarine has sunk!\n", playername);
	}
	else if (player_ship_arr[4] == 0) //destroyer sunk
	{
		result = 4;
		player_ship_arr[4] = -1;
		printf("%s's destroyer has sunk!\n", playername);
	}
	else
	{
		result = -1;
	}

	return result;
}

/****************************************************************************
	Function: print_shot()
	Date Created : 11/3/19
	Date Last Modified :
	Description : prints the result of the shot to the screen. 
	Input parameters : gameboard, row_coord, col_coord.
	Returns : n/a
	Preconditions : n/a
	Postconditions : n/a
***************************************************************************/
void print_shot(Cell gameboard[ROWS][COLUMNS], int row_coord, int col_coord)
{
	if (gameboard[row_coord][col_coord].occupied != 0)
	{
		printf("\n %d, %d is a hit!\n", row_coord, col_coord);
	}
	else
	{
		printf("\n %d, %d is a miss!\n", row_coord, col_coord);
	}
}

/****************************************************************************
	Function: print_shot()
	Date Created : 11/3/19
	Date Last Modified :
	Description : prints the result of the shot by the AI to the screen.
	Input parameters : gameboard, row_coord, col_coord.
	Returns : n/a
	Preconditions : n/a
	Postconditions : n/a
***************************************************************************/
void print_shot_AI(Cell gameboard[ROWS][COLUMNS], int row_coord, int col_coord)
{
	if (gameboard[row_coord][col_coord].symbol != '-')
	{
	printf("\n %d, %d is a hit!\n", row_coord, col_coord);
	}
	else
	{
		printf("\n %d, %d is a miss!\n", row_coord, col_coord);
	}
}

/****************************************************************************
	Function: output_stats()
	Date Created : 11/4/19
	Date Last Modified :
	Description : This function outputs the stats of each player to the output
				file. The stats include the total shots, missed shots, hit
				shots, hit/miss ratio, and whether the player lost or not.			
	Input parameters : output_file, struct of player and AI Stats, and the 
					result of win_loss.
	Returns : outputs to file.
	Preconditions : must call is_winner before to get result.
	Postconditions : n/a
***************************************************************************/
void output_stats(FILE *output_file, Stats player, Stats AI, int win_lose)
{
	double AI_hit_miss = 0, user_hit_miss = 0;

	AI_hit_miss = ((double) AI.hit / (double) AI.total) * 100;
	user_hit_miss = ( (double) player.hit / (double) player.total) * 100;

	fprintf(output_file, "\nGame Stats\n");
	//P1 stats
	fprintf(output_file, "Player 1 Statistics:\n");
	fprintf(output_file, "Total shots = %d\n", player.total); //prints total shots of player 1
	fprintf(output_file, "Missed shots = %d\n", player.miss);	//prints total missed shots
	fprintf(output_file, "Hit shots = %d\n", player.hit);	//prints total hit shots
	fprintf(output_file, "Hit/Miss percent ratio is %.2lf\n", user_hit_miss); //hit ratio (hits/miss
	if (win_lose == 1)	//won or lost
	{
		fprintf(output_file, "Player 1 won!");
	}
	else
	{
		fprintf(output_file, "Player 1 lost!");
	}

	fprintf(output_file, "\nAI Statistics:\n");
	fprintf(output_file, "Total shots = %d\n", AI.total); 
	fprintf(output_file, "Missed shots = %d\n", AI.miss);
	fprintf(output_file, "Hit shots = %d\n", AI.hit);
	fprintf(output_file, "Hit/Miss percent ratio is  %.2lf\n", AI_hit_miss);
	if (win_lose == 2)	//won or lost
	{
		fprintf(output_file, "The AI won!");
	}
	else
	{
		fprintf(output_file, "The AI lost!");
	}

	fprintf(output_file, "\n**END OF GAME**\n");
}

/****************************************************************************
	Function: print_battleship()
	Date Created : 11/4/19
	Date Last Modified :
	Description : This function prints out a big 'Battleship' on the start 
				screen. 
	Input parameters : n/a
	Returns : n/a
	Preconditions : n/a
	Postconditions : n/a
****************************************************************************/
void print_battleship(void)
{
	puts("");
	puts("");
	puts("");
	puts("");
	puts("\033[1;31m"); //changes color to red
	puts("			XXXXX   XXXX  XXXXXX XXXXXX XX     XXXXXX  XXXXX XX  XX XX XXXXX");
	puts("			XX  XX XX  XX   XX     XX   XX     XX     XX     XX  XX XX XX  XX");
	puts("			XXXXX  XX  XX   XX     XX   XX     XXXX    XXXX  XXXXXX XX XXXXX");
	puts("			XX  XX XXXXXX   XX     XX   XX     XX         XX XX  XX XX XX");
	puts("			XXXXX  XX  XX   XX     XX   XXXXXX XXXXXX XXXXX  XX  XX XX XX");
	puts("\033[0m"); //resets color back to normal

	puts("");
	puts("");
	puts("");


	puts("					   Press any key to play!");
	printf(">");

}

/****************************************************************************
> Name: Alex Genriech
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


int main(void)
{
	srand(time(NULL));

	FILE* outfile = NULL;
	outfile = fopen("battleship.log", "w");

	srand(time(NULL));
	//Structs
	Cell gameboard1[ROWS][COLUMNS] = { {0, '\0', '\0', 0} }; //Player 1 board
	Cell gameboard2[ROWS][COLUMNS] = { {0, '\0', '\0', 0} }; //A.I. board
	Cell practice_board1[ROWS][COLUMNS] = { {0, '\0', '\0', 0} }; 
	Stats player1 = { 0, 0, 0 }; //player stats
	Stats AI = { 0, 0, 0 }; //AI stats

	//Ship names
	char ship_carrier[] = "Carrier", ship_battleship[] = "Battleship", ship_Cruiser[] = "Cruiser",
		ship_submarine[] = "Submarine", ship_destroyer[] = "Destroyer";
	//Ship symbols
	char carrier_symbol = 'c', battleship_symbol = 'b', cruiser_symbol = 'r', submarine_symbol = 's', destroyer_symbol = 'd';
	//Ship sizes
	int carrier_length = 5, battleship_length = 4, cruiser_length = 3, submarine_length = 3, destroyer_length = 2;
	//Ship lengths
	int player1_ships[5] = { 5, 4, 3, 3, 2 }, AI_ships[5] = { 5, 4, 3, 3, 2 }; //carrier, battleship, cruiser, submarine, destroyer
	//player names
	char user[10] = "Player 1", AI_player[10] = "A.I.";
	//variables
	char decision = '\0';
	int AI_coords[2] = { 0, 0 }, user_coords[2] = { 0,0 }; //Stores players coordinates
	int start = 0; //Determines who starts
	int win = 0;

	print_battleship();
	getch();

	//Initializing boards
	initialize_game_board(gameboard1); //Initialize User board
	initialize_game_board(gameboard1); //Initialize A.I. board
	initialize_game_board(practice_board1); //used to display ship when placing manually
	

	//GAMEPLAY
	welcome_screen();

	do {
		system("cls");
		puts("Would you like your ships placed manually or automatically? [m] for manual, [a] for automatic.");
		scanf(" %c", &decision);
	} while (decision != 'm' && decision != 'a');

	if (decision == 'm') //manual placement of ship
	{
		manually_place_ships(gameboard1, carrier_length, carrier_symbol, ship_carrier, practice_board1);
		manually_place_ships(gameboard1, battleship_length, battleship_symbol, ship_battleship, practice_board1);
		manually_place_ships(gameboard1, cruiser_length, cruiser_symbol, ship_Cruiser, practice_board1);
		manually_place_ships(gameboard1, submarine_length, submarine_symbol, ship_submarine, practice_board1);
		manually_place_ships(gameboard1, destroyer_length, destroyer_symbol, ship_destroyer, practice_board1);
		puts("Your ships have been placed successfully!");
	}
	else if (decision == 'a') //automatic placement of ships
	{
		automatically_place_ships(gameboard1, carrier_length, carrier_symbol);
		
		automatically_place_ships(gameboard1, battleship_length, battleship_symbol);
		
		automatically_place_ships(gameboard1, cruiser_length, cruiser_symbol);
		
		automatically_place_ships(gameboard1, submarine_length, submarine_symbol); 
		
		automatically_place_ships(gameboard1, destroyer_length, destroyer_symbol);

		puts("Your ships have been placed successfully! Your board has been displayed below:");
		print_board(gameboard1);
	}
	
	proceed();
	system("cls");

	//places AI shipes automatically
	automatically_place_ships(gameboard2, carrier_length, carrier_symbol);
	automatically_place_ships(gameboard2, battleship_length, battleship_symbol);
	automatically_place_ships(gameboard2, cruiser_length, cruiser_symbol);
	automatically_place_ships(gameboard2, submarine_length, submarine_symbol);
	automatically_place_ships(gameboard2, destroyer_length, destroyer_symbol);
	puts("The A.I. has placed their ships randomly.");
	//print_board(gameboard2); //prints AI gameboard

	proceed();
	system("cls");

	//printf("%c\n", gameboard2[0][0].symbol);
	//printf("%c\n", gameboard2[0][0].hidden);
	//print_board(gameboard2);

	start = determine_who_starts(); //picks who starts first

	proceed();

	if (start == 1) //player 1 goes first
	{
		while (win == 0) //gameplay
		{
			int cont = 0, chk_shot = 0, chk_ship_sink = 0;

			int i = 0, j = 0;
			//player 1 turn

			//asks for input of coordinates to strike
			//do {
			while (cont != 1)
			{
				system("cls");
				print_hidden_board(gameboard2); //prints hidden version of AI board so user can place targets
				puts("Enter one coordinate (row, col) which you would like to strike.");
				printf(">");
				scanf("%d %d", &user_coords[0], &user_coords[1]);
				
				if (gameboard2[user_coords[0]][user_coords[1]].hidden_occupied == 1)
				{
					cont = 0;
					puts("Coordinates are already used or invalid, please try new coordinates.");

					puts("Press any key to re-enter a new coordinate.");
					getch();
				}
				else if (user_coords[0] > 10 || user_coords[0] < 0)
				{
					puts("Coordinate must be within the grid!");
					cont = 0;
					puts("Press any key to re-enter a new coordinate.");
					getch();
				}
				else if (user_coords[1] > 10 || user_coords[1] < 0)
				{
					puts("Coordinate must be within the grid!");
					cont = 0;
					puts("Press any key to re-enter a new coordinate.");
					getch();
				}
				else
				{
					cont = 1; //valid
				}
			} 
			
			system("cls");
			//check the shot
			chk_shot = check_shot(gameboard2, user_coords[0], user_coords[1], AI_ships);
			//update board
			update_board(gameboard2, chk_shot, user_coords[0], user_coords[1]);
			//print board
			print_hidden_board(gameboard2);
			//print result of shot 
			print_shot(gameboard2, user_coords[0], user_coords[1]);
			//check if ship sunk
			chk_ship_sink = check_if_ship_sunk(AI_ships, AI_player);
			//output to file
			output_current_move(outfile, chk_shot, chk_ship_sink, user_coords[0], user_coords[1], AI_player);

			//update player stats
			if (chk_shot == 0)//miss
			{
				player1.miss++;
				player1.total++;
			}
			else if (chk_shot == 1) //hit
			{
				player1.hit++;
				player1.total++;
			}
			//printf("\nPlayer 1 hits = %d, AI hits = %d\n", player1.hit, AI.hit);
			proceed();
			system("cls");
			win = is_winner(player1, AI, outfile); //checks if any winner


			//AI turn
			AI_random_coords(AI_coords, gameboard1);

			//check shot
			chk_shot = check_shot(gameboard1, AI_coords[0], AI_coords[1], player1_ships);
			//update board
			update_board(gameboard1, chk_shot, AI_coords[0], AI_coords[1]);
			//print board
			print_hidden_board(gameboard1);
			//print result of shot 
			print_shot_AI(gameboard1, AI_coords[0], AI_coords[1]);
			//check if ship sunk
			chk_ship_sink = check_if_ship_sunk(player1_ships, user);
			//output to file
			output_current_move(outfile, chk_shot, chk_ship_sink, AI_coords[0], AI_coords[1], user);
			//update AI stats
			if (chk_shot == 0)
			{
				AI.miss++;
				AI.total++;
			}
			else if (chk_shot == 1)
			{
				AI.hit++;
				AI.total++;
			}

			//printf("\nPlayer 1 hits = %d, AI hits = %d\n", player1.hit, AI.hit);
			proceed();

			system("cls");

			win = is_winner(player1, AI, outfile); //checks if any winner
		}
	}
	else if (start == 2) //AI goes first
	{
		
		while (win == 0) //gameplay
		{
			int cont = 0, chk_shot = 0, chk_ship_sink = 0;
			system("cls");
			//AI turn
			AI_random_coords(AI_coords, gameboard1);

			//check shot
			chk_shot = check_shot(gameboard1, AI_coords[0], AI_coords[1], player1_ships);
			//update board
			update_board(gameboard1, chk_shot, AI_coords[0], AI_coords[1]);
			//print board
			print_hidden_board(gameboard1);
			//print result of shot 
			print_shot_AI(gameboard1, AI_coords[0], AI_coords[1]);
			//check if ship sunk
			chk_ship_sink = check_if_ship_sunk(player1_ships, user);
			//output to file
			output_current_move(outfile, chk_shot, chk_ship_sink, AI_coords[0], AI_coords[1], user);
			//update AI stats
			if (chk_shot == 0)
			{
				AI.miss++;
				AI.total++;
			}
			else if (chk_shot == 1)
			{
				AI.hit++;
				AI.total++;
			}

			//printf("\nPlayer 1 hits = %d, AI hits = %d\n", player1.hit, AI.hit);
			proceed();

			system("cls");

			win = is_winner(player1, AI, outfile); //checks if any winner


			//player 1 turn

			//asks for input of coordinates to strike
			while (cont != 1)
			{
				system("cls");
				print_hidden_board(gameboard2); //prints hidden version of AI board so user can place targets
				puts("Enter one coordinate (row, col) which you would like to strike.");
				printf(">");
				scanf("%d %d", &user_coords[0], &user_coords[1]);
				
				if (gameboard2[user_coords[0]][user_coords[1]].hidden_occupied == 1)
				{
					cont = 0;
					puts("Coordinates are already used or invalid, please try new coordinates.");

					puts("Press any key to re-enter a new coordinate.");
					getch();
				}
				else if (user_coords[0] > 10 || user_coords[0] < 0)
				{
					puts("Coordinate must be within the grid!");
					cont = 0;
					puts("Press any key to re-enter a new coordinate.");
					getch();
				}
				else if (user_coords[1] > 10 || user_coords[1] < 0)
				{
					puts("Coordinate must be within the grid!");
					cont = 0;
					puts("Press any key to re-enter a new coordinate.");
					getch();
				}
				else
				{
					cont = 1; //valid
				}
			}

			system("cls");
			//check the shot
			chk_shot = check_shot(gameboard2, user_coords[0], user_coords[1], AI_ships);
			//update board
			update_board(gameboard2, chk_shot, user_coords[0], user_coords[1]);
			//print board
			print_hidden_board(gameboard2);
			//print result of shot 
			print_shot(gameboard2, user_coords[0], user_coords[1]);
			//check if ship sunk
			chk_ship_sink = check_if_ship_sunk(AI_ships, AI_player);
			//output to file
			output_current_move(outfile, chk_shot, chk_ship_sink, user_coords[0], user_coords[1], AI_player);

			//update player stats
			if (chk_shot == 0)//miss
			{
				player1.miss++;
				player1.total++;
			}
			else if (chk_shot == 1) //hit
			{
				player1.hit++;
				player1.total++;
			}
			//printf("\nPlayer 1 hits = %d, AI hits = %d\n", player1.hit, AI.hit);
			proceed();
			system("cls");
			//win: 1 = player 1 wins, 2 = AI wins
			win = is_winner(player1, AI, outfile); //checks if any winner 
			
		}
	}

	//print game stats
	output_stats(outfile, player1, AI, win);
	puts("Game Statistics have been successfully outputted to logfile.");
	//closes file
	fclose(outfile);

	return 0;
}

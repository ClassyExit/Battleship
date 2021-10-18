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

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
 

#define ROWS 10
#define COLUMNS 10

typedef struct stats
{
	int hit;
	int miss;
	int total;

}Stats;


typedef struct cell
{
	int occupied; //1 is occupied, 0 is not.
	char symbol;
	char hidden;
	int hidden_occupied;

}Cell;



//Function declarations

void welcome_screen(void);

char initialize_game_board(Cell board[ROWS][COLUMNS]);

void print_board(Cell board[ROWS][COLUMNS]);

void print_hidden_board(Cell board[ROWS][COLUMNS]);

int determine_who_starts(void);

void manually_place_ships(Cell gameboard[ROWS][COLUMNS], int ship_size, char ship_symbol, char str_ship_name[], Cell practice_board[ROWS][COLUMNS]);

int rand_num(void);

void automatically_place_ships(Cell gameboard[ROWS][COLUMNS], int ship_size, char ship_symbol);

void update_board(Cell gameboard[ROWS][COLUMNS], int result_check_shot, int row_coordinate, int col_coordinate);

int is_winner(Stats player1, Stats AI, FILE* output_file);

void output_stats(FILE* output_file, Stats player, Stats AI, int win_lose);

void proceed(void);

int check_shot(Cell gameboard[ROWS][COLUMNS], int row_coordinate, int col_coordinate, int playerships_array[]);

void output_current_move(FILE* output_file, int result_check_shot, int result_ship_sunk, int row_coordinate, int col_coordinate, char player[]);

int check_if_ship_sunk(int player_ship_arr[], char playername[]);

void AI_random_coords(int AI_coords[], Cell user_gameboard[ROWS][COLUMNS]);

void print_shot(Cell gameboard[ROWS][COLUMNS], int row_coord, int col_coord);

void print_shot_AI(Cell gameboard[ROWS][COLUMNS], int row_coord, int col_coord);

void print_battleship(void);

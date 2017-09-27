#include "PlayGame_UserInterface.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


static void GUI_Interface()
{
	int i;
	for(i = 0; i < 50; ++i)
	{
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");	
		printf("\t\t\t\t\t\t\t \033[01;3%dm Welcome To Game Of Life \n\n", 1 + ( rand()% 6) );
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");	
		usleep(100000);		
		fflush(stdout);
	}
}

static void StartPlayGUI()
{
	
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");		
	printf("\t\t\t\t\t\t\t\t\x1b[31mS\x1b[35mt\x1b[32ma\x1b[33mr\x1b[36mt\x1b[32ms \x1b[35mp\x1b[33ml\x1b[31ma\x1b[35m\x1b[36my\n");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");		
	printf(ANSI_COLOR_RESET);	
	
	fflush(stdout);

}


int main()
{

	GameOfLife* newGame;
	
	int rows;
	int columns;
	int threads;
	int generation;
	int equal;

	GUI_Interface();


	printf(ANSI_COLOR_RESET);	
	printf("\n\n");
	printf("\t\t\t\t\t\t\t\tEnter rows:  ");
	scanf("%d", &rows);
	fflush(stdout);
	
	printf("\t\t\t\t\t\t\t\tEnter columns:  ");
	scanf("%d", &columns);
	fflush(stdout);
	
	printf("\t\t\t\t\t\t\t\tEnter number of threads:  ");
	scanf("%d", &threads);
	fflush(stdout);
	
	printf("\t\t\t\t\t\t\t\tEnter number of cycle:  ");
	scanf("%d", &generation);
	fflush(stdout);
	
	printf("\t\t\t\t\tEnter 1 to stop if the cells stop moving Ziro To continue by generation ");
	scanf("%d", &equal);
	printf("\n\n");
	fflush(stdout);


	newGame = CreateNewGame(rows, columns, threads, generation, NULL, equal);
	StartPlayGUI();
	RunNewGame(newGame); 
	
	return 0;
}






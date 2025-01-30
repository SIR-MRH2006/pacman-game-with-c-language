// https://www.geeksforgeeks.org/pacman-game-in-c/

// Pacman Game in C language 
#include <conio.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

// All the elements to be used 
// Declared here 
#define WIDTH 40 
#define HEIGHT 20 
#define PACMAN 'C' 
#define WALL '#' 
#define FOOD '.' 
#define EMPTY ' ' 
#define DEMON 'X' 
#define ENEMY 'E' 
#define PERESENT '$' 

// Global Variables are 
// Declared here 
int res = 0; 
int score = 0; 
int pacman_x, pacman_y; 
int food = 0; 
int curr = 0; 

typedef struct{
	char type;
} varOfCell;

void initialize(varOfCell cells[WIDTH][HEIGHT]){
	// Putting Walls as boundary in the Game 
	for (int i = 0; i < HEIGHT; i++) { 
		for (int j = 0; j < WIDTH; j++) { 
			if (i == 0 || j == (WIDTH - 1) || j == 0 || i == (HEIGHT - 1)){ 
				cells[i][j].type = '#';
			}
			else{
				cells[i][j].type = '.';
			}
		} 
	}

	// Putting Walls inside the Game 
	int count = 50; 
	while (count != 0) { 
		int i = (rand() % (HEIGHT + 1)); 
		int j = (rand() % (WIDTH + 1)); 

		if (cells[i][j].type != WALL && cells[i][j].type != PACMAN) { 
			cells[i][j].type = WALL;
			count--; 
		} 
	} 

	int val = 5; 
	while (val--) { 
		int row = (rand() % (HEIGHT + 1)); 
		for (int j = 3; j < WIDTH - 3; j++) { 
			if (cells[row][j].type != WALL && cells[row][j].type != PACMAN){ 
				cells[row][j].type = WALL; 
			} 
		} 
	} 

	// Putting Demons in the Game 
	count = 10; 
	while (count != 0) { 
		int i = (rand() % (HEIGHT + 1)); 
		int j = (rand() % (WIDTH + 1)); 

		if (cells[i][j].type != WALL && cells[i][j].type != PACMAN) { 
			cells[i][j].type = DEMON; 
			count--; 
		} 
	} 

	// Cursor at Center 
	pacman_x = WIDTH / 2; 
	pacman_y = HEIGHT / 2; 
	cells[pacman_y][pacman_x].type = PACMAN; 

	// Points Placed 
	for (int i = 0; i < HEIGHT; i++) { 
		for (int j = 0; j < WIDTH; j++) { 
			if (i % 2 == 0 && j % 2 == 0 && cells[i][j].type != WALL && cells[i][j].type != DEMON && cells[i][j].type != PACMAN){ 
				cells[i][j].type = FOOD; 
				food++; 
			} 
		} 
	} 
} 

void draw(varOfCell cells[WIDTH][HEIGHT]) { 
	// Clear screen 
	system("cls");

	// Drawing All the elements in the screen 
	for (int i = 0; i < HEIGHT; i++) { 
		for (int j = 0; j < WIDTH; j++) { 
			printf("%c", cells[i][j].type); 
		} 
		printf("\n"); 
	} 
	printf("Score: %d\n", score); 
} 

// Function enables to move the Cursor 
void move(int move_x, int move_y,varOfCell cells[WIDTH][HEIGHT]) { 
	int x = pacman_x + move_x; 
	int y = pacman_y + move_y; 

	if (cells[y][x].type != WALL) { 
		if (cells[y][x].type == FOOD) { 
			score++; 
			food--; 
			curr++; 
			if (food == 0) { 
				res = 2; 
				return; 
			} 
		} 
		else if (cells[y][x].type == DEMON) { 
			res = 1; 
		} 

		cells[pacman_y][pacman_x].type = EMPTY; 
		pacman_x = x; 
		pacman_y = y; 
		cells[pacman_y][pacman_x].type = PACMAN; 
	} 
} 

// Main Function 
int main(){ 
	varOfCell cells[WIDTH][HEIGHT];
	initialize(cells); 
	char ch;
	food -= 35; 
	int totalFood = food; 
	// Instructions to Play 
	printf(" Use buttons for w(up), a(left) , d(right) and "
		"s(down)\nAlso, Press q for quit\n"); 

	printf("Enter Y to continue: \n"); 

	ch = getch(); 
	if (ch != 'Y' && ch != 'y') { 
		printf("Exit Game! "); 
		return 1; 
	} 

	while(1){ 
		draw(cells); 
		printf("Total Food count: %d\n", totalFood); 
		printf("Total Food eaten: %d\n", curr); 
		if (res == 1) { 
			// Clear screen 
			system("cls"); 
			printf("Game Over! Dead by Demon\n Your Score: ""%d\n",score); 
			return 1; 
		} 

		if (res == 2) { 
			// Clear screen 
			system("cls"); 
			printf("You Win! \n Your Score: %d\n", score); 
			return 1; 
		} 

		// Taking the Input from the user 
		ch = getch(); 

		// Moving According to the 
		// input character 
		switch (ch) { 
		case 'w': 
			move(0, -1,cells); 
			break; 
		case 's': 
			move(0, 1,cells); 
			break; 
		case 'a': 
			move(-1, 0,cells); 
			break; 
		case 'd': 
			move(1, 0,cells); 
			break; 
		case 'q': 
			printf("Game Over! Your Score: %d\n", score); 
			return 0; 
		} 
	} 

	return 0; 
}


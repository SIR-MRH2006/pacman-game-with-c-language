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
int score = 0;         //امتیاز بازی (غذاهای خورده شده)
int pacman_x, pacman_y;  // مختصات پک من
int enemy_x, enemy_y;  // مختصات پک من
int enemy_x2, enemy_y2;  // مختصات پک من
int food = 0;  //تعداد غذاهای موجود در بازی
int curr = 0;    //تعداد غذاهای خورده شده
int countOfPresent = 0;
int isdouble = 0;
int totalFood;

typedef struct{
	char type;
} varOfCell;

void initialize(varOfCell cells[HEIGHT][WIDTH]){
	// Putting Walls as boundary in the Game 
	for (int i = 0; i < HEIGHT; i++) { 
		for (int j = 0; j < WIDTH; j++) { 
			if (i == 0 || j == WIDTH-1 || j == 0 || i == HEIGHT-1){ 
				cells[i][j].type = WALL;
			}
			else{
				cells[i][j].type = EMPTY;
			}
		} 
	}
	int val = 5; 
	while (val--) { 
		int row = (rand() % (HEIGHT + 1)); 
		for (int j = 7; j < WIDTH - 3; j++) { 
			if (cells[row][j].type == EMPTY){ 
				cells[row][j].type = WALL; 
			} 
		} 
	}
	// Putting Walls inside the Game 
	int count = 40; 
	while (count != 0) { 
		int i = (rand() % (HEIGHT + 1)); 
		int j = (rand() % (WIDTH + 1)); 

		if (cells[i][j].type == EMPTY &&
		 	cells[i+1][j+1].type == EMPTY &&
			cells[i+1][j].type == EMPTY &&
		  	cells[i+1][j-1].type == EMPTY &&
		    cells[i-1][j-1].type == EMPTY &&
			cells[i-1][j].type == EMPTY &&
			cells[i-1][j+1].type == EMPTY &&
			cells[i][j+1].type == EMPTY &&
			cells[i][j-1].type == EMPTY){ 
			cells[i][j].type = WALL;
			count--; 
		} 
	}  
	// Putting present in the Game 
	count = 3; 
	while (count != 0) { 
		int i = (rand() % (HEIGHT + 1)); 
		int j = (rand() % (WIDTH + 1)); 
		if (cells[i][j].type == EMPTY){ 
			cells[i][j].type = PERESENT; 
			count--; 
		} 
	} 
	// Putting Demons in the Game 
	count = 10; 
	while (count != 0) { 
		int i = (rand() % (HEIGHT + 1)); 
		int j = (rand() % (WIDTH + 1)); 

		if (cells[i][j].type == EMPTY){ 
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
			if (i % 2 == 0 && j % 2 == 0 && cells[i][j].type == EMPTY){ 
				cells[i][j].type = FOOD; 
				food++; 
			} 
		} 
	} 
	//
	count = 1; 
	while (count != 0) { 
		int i = (rand() % (HEIGHT+1)); 
		int j = (rand() % (WIDTH+1)); 

		if (cells[i][j].type == EMPTY) { 
			cells[i][j].type = ENEMY;
			enemy_x = j;
			enemy_y = i;
			count--; 
		} 
	} 
	count = 1; 
	while (count != 0) { 
		int i = (rand() % (HEIGHT+1)); 
		int j = (rand() % (WIDTH+1)); 

		if (cells[i][j].type == EMPTY) { 
			cells[i][j].type = ENEMY;
			enemy_x2 = j;
			enemy_y2 = i;
			count--; 
		} 
	} 
} 




void draw(varOfCell cells[HEIGHT][WIDTH]) { 
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
	totalFood = food;
	printf("Total Food count: %d\n", totalFood); 
	printf("Total Food eaten: %d\n", curr); 
} 

// ADD TO FILE
void addToFile(varOfCell cells[HEIGHT][WIDTH],FILE *ptrToFile){
	//------------------------------------open-FILE
	ptrToFile = fopen("pacman.txt","wb");
	fwrite(&pacman_x,sizeof(int),1,ptrToFile);
	fwrite(&pacman_y,sizeof(int),1,ptrToFile);
	fwrite(&score,sizeof(int),1,ptrToFile);
	fwrite(&food,sizeof(int),1,ptrToFile);
	fwrite(&curr,sizeof(int),1,ptrToFile);
	fwrite(cells,sizeof(varOfCell),800,ptrToFile);
	fclose(ptrToFile);
	// Close a FILE---------------------------------
}

// Function enables to move the Cursor 
int move(int move_x, int move_y,varOfCell cells[HEIGHT][WIDTH],FILE *ptrToFile){
	int x = pacman_x + move_x; 
	int y = pacman_y + move_y; 

	if (cells[y][x].type != WALL){ 
		if (cells[y][x].type == FOOD){ 
			if(isdouble == 1 && countOfPresent != 0){
				score = score+2;
				food--;
				curr++;
				countOfPresent--;
				if(food == 0 || score == 80){ 
					res = 2; 
				}
			}else{
				score++;
				food--; 
				curr++; 
				if (food == 0 || score == 80){ 
					res = 2;
				}
			}
		}else if (cells[y][x].type == DEMON){ 
			res = 1; 
		}else if (cells[y][x].type == PERESENT){ 
			countOfPresent = 10;
			isdouble = 1;
		}else if (cells[y][x].type == ENEMY){ 
			res = 1; 
		}

		cells[pacman_y][pacman_x].type = EMPTY; 
		pacman_x = x; 
		pacman_y = y; 
		cells[pacman_y][pacman_x].type = PACMAN; 
	} 

	addToFile(cells,ptrToFile);

} 

void moveEnemy1(varOfCell cells[HEIGHT][WIDTH]){
	printf("enter moveEnemy");
	if(pacman_x<enemy_x && cells[enemy_y][enemy_x-1].type != WALL && cells[enemy_y][enemy_x-1].type != ENEMY){
		cells[enemy_y][enemy_x].type = EMPTY;
		enemy_x -= 1;
		cells[enemy_y][enemy_x].type = ENEMY;
	}else if(pacman_x > enemy_x && cells[enemy_y][enemy_x+1].type != WALL && cells[enemy_y][enemy_x+1].type != ENEMY){
		cells[enemy_y][enemy_x].type = EMPTY;
		enemy_x += 1;
		cells[enemy_y][enemy_x].type = ENEMY;
	}else if(pacman_y<enemy_y && cells[enemy_y-1][enemy_x].type != WALL && cells[enemy_y-1][enemy_x].type != ENEMY){
		cells[enemy_y][enemy_x].type = EMPTY;
		enemy_y -= 1;
		cells[enemy_y][enemy_x].type = ENEMY;
	}else if(pacman_y > enemy_y && cells[enemy_y+1][enemy_x].type != WALL  && cells[enemy_y+1][enemy_x].type != ENEMY){
		cells[enemy_y][enemy_x].type = EMPTY;
		enemy_y += 1;
		cells[enemy_y][enemy_x].type = ENEMY;
	}
	draw(cells);
}

void moveEnemy2(varOfCell cells[HEIGHT][WIDTH]){
	if(pacman_x<enemy_x2 && cells[enemy_y2][enemy_x2-1].type != WALL && cells[enemy_y2][enemy_x2-1].type != ENEMY){
		cells[enemy_y2][enemy_x2].type = EMPTY;
		enemy_x2 -= 1;
		cells[enemy_y2][enemy_x2].type = ENEMY;
	}else if(pacman_x > enemy_x2 && cells[enemy_y2][enemy_x2+1].type != WALL && cells[enemy_y2][enemy_x2+1].type != ENEMY){
		cells[enemy_y2][enemy_x2].type = EMPTY;
		enemy_x2 += 1;
		cells[enemy_y2][enemy_x2].type = ENEMY;
	}else if(pacman_y<enemy_y2 && cells[enemy_y2-1][enemy_x2].type != WALL && cells[enemy_y2-1][enemy_x2].type != ENEMY){
		cells[enemy_y2][enemy_x2].type = EMPTY;
		enemy_y2 -= 1;
		cells[enemy_y2][enemy_x2].type = ENEMY;
	}else if(pacman_y > enemy_y2 && cells[enemy_y2+1][enemy_x2].type != WALL && cells[enemy_y2+1][enemy_x2].type != ENEMY){
		cells[enemy_y2][enemy_x2].type = EMPTY;
		enemy_y2 += 1;
		cells[enemy_y2][enemy_x2].type = ENEMY;
	}
	draw(cells);
}


int response(varOfCell cells[HEIGHT][WIDTH],FILE *ptrToFile){
	char ch;
	food -= 60;  
	// Instructions to Play 
	printf(" Use buttons for w(up), a(left) , d(right) and ""s(down)\nAlso, Press q for quit\n"); 
	printf("Enter Y to continue: \n"); 

	ch = getch(); 
	if (ch != 'Y' && ch != 'y') { 
		printf("Exit Game! "); 
		return 1; 
	} 


	while(1){
		draw(cells); 
		if (res == 1){ 
			system("cls"); 
			printf("Game Over! Dead by Demon\n Your Score: ""%d\n",score); 
			return 1; 
		}else if (res == 2){ 
			system("cls"); 
			printf("You Win! \n Your Score: %d\n", score); 
			return 1; 
		} 

		moveEnemy1(cells);
		if(pacman_x == enemy_x && pacman_y == enemy_y){
			printf("GMAEOVER");
			exit(0);
		}

		moveEnemy2(cells);
		if(pacman_x == enemy_x2 && pacman_y == enemy_y2){
			printf("GMAEOVER");
			exit(0);
		}

		ch = getch(); 
		switch (ch) { 
		case 'w': 
			move(0, -1,cells,ptrToFile); 
			break; 
		case 's': 
			move(0, 1,cells,ptrToFile); 
			break; 
		case 'a': 
			move(-1, 0,cells,ptrToFile); 
			break; 
		case 'd': 
			move(1, 0,cells,ptrToFile);
			break; 
		case 'q': 
			printf("Game Over! Your Score: %d\n", score); 
			printf("GAME OVER");
			return 0; 
		} 
	}
}

// ================================START==================================== {{MAIN_FUNCTION}} ===============================================//
int main(){ 
	varOfCell cells[HEIGHT][WIDTH];

	int tim = time(NULL);
	//-------------------------------give info from a {FILE}------------------------
	//------------------------------------open-FILE
	FILE *ptrToFile = fopen("pacman.txt","rb");
	int isEmpty = -1;
	if(ptrToFile == NULL){
		printf("we have a problem in open the file \n");
		return 0;
	}else{
		fseek(ptrToFile,0,SEEK_END);
		long size = ftell(ptrToFile);
		if(size == 0){
			isEmpty = 0;
		}else{
			fseek(ptrToFile,0,SEEK_SET);
			fread(&pacman_x,sizeof(int),1,ptrToFile);
			fread(&pacman_y,sizeof(int),1,ptrToFile);
			fread(&score,sizeof(int),1,ptrToFile);
			fread(&food,sizeof(int),1,ptrToFile);
			fread(&curr,sizeof(int),1,ptrToFile);
			fread(cells,sizeof(varOfCell),800,ptrToFile);
			fclose(ptrToFile);
		}
	}
	// Close a FILE----------------------------------

	//-----------------check player have a prevous game or no--------------------
	int result;
	if(isEmpty != -1){
		printf("file is empty\n");
		initialize(cells); 
		result = response(cells,ptrToFile);
	}else{
		int userChoices;
		do{
			printf("\n\t-------------------{{PACMAN_GAME}}-------------------\ndo you want to \n1)play previous game  \n2)creat a new game \n");
			scanf("%d",&userChoices);
			if(userChoices == 1){
				result = response(cells,ptrToFile);
			}else if(userChoices == 2){
				res = 0;     
				score = 0;         
				food = 0;  
				curr = 0;
				initialize(cells);
				result = response(cells,ptrToFile);
			}
		}while(!(userChoices == 1 || userChoices ==2));
	}

	if(result == 0){
		return 0;
	}
}
// ================================END==================================== {{MAIN_FUNCTION}} ===============================================//



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
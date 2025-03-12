#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define constants for grid size
#define ROWS 20
#define COLS 40

// Function prototypes
void initialize_grid(int grid[ROWS][COLS]);
void print_grid(int grid[ROWS][COLS]);
int count_live_neighbors(int grid[ROWS][COLS], int row, int col);
void update_grid(int grid[ROWS][COLS], int next_grid[ROWS][COLS]);
void simulate_generation(int grid[ROWS][COLS], int next_grid[ROWS][COLS]);


int main() {
    int grid[ROWS][COLS];
    int next_grid[ROWS][COLS]; // Temporary grid to store the next state

    // Initialize the grid (e.g., with random cells)
    initialize_grid(grid);

    // Simulate the game for a few generations
    for (int generation = 0; generation < 50; generation++) {
        printf("Generation %d:
", generation);
        print_grid(grid);
        simulate_generation(grid, next_grid);
        // Copy the updated grid back to the main grid
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                grid[i][j] = next_grid[i][j];
            }
        }
        // Add a small delay (optional) for visualization
        // (requires including <unistd.h> or <windows.h> for appropriate functions)
        #ifdef _WIN32
            Sleep(100); // Windows (milliseconds)
        #else
            usleep(100000); // Unix-like systems (microseconds)
        #endif
        system("cls || clear"); // Clear the console (cross-platform)
    }

    return 0;
}


// Function to initialize the grid (e.g., with random cells)
void initialize_grid(int grid[ROWS][COLS]) {
    srand(time(NULL)); // Seed the random number generator

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = (rand() % 2); // 0 or 1 (dead or alive)
        }
    }
}


// Function to print the grid to the console
void print_grid(int grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", (grid[i][j] == 1) ? 'O' : '.'); // 'O' for alive, '.' for dead
        }
        printf("
");
    }
}


// Function to count the live neighbors of a cell
int count_live_neighbors(int grid[ROWS][COLS], int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue; // Skip the cell itself
            }
            int neighbor_row = row + i;
            int neighbor_col = col + j;

            // Handle edge cases (wrap around)
            if (neighbor_row < 0) {
                neighbor_row = ROWS - 1;
            } else if (neighbor_row >= ROWS) {
                neighbor_row = 0;
            }
            if (neighbor_col < 0) {
                neighbor_col = COLS - 1;
            } else if (neighbor_col >= COLS) {
                neighbor_col = 0;
            }

            if (grid[neighbor_row][neighbor_col] == 1) {
                count++;
            }
        }
    }
    return count;
}


// Function to update the grid based on Conway's Game of Life rules
void update_grid(int grid[ROWS][COLS], int next_grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int live_neighbors = count_live_neighbors(grid, i, j);

            if (grid[i][j] == 1) { // Cell is alive
                if (live_neighbors < 2 || live_neighbors > 3) {
                    next_grid[i][j] = 0; // Dies (underpopulation or overpopulation)
                } else {
                    next_grid[i][j] = 1; // Survives
                }
            } else { // Cell is dead
                if (live_neighbors == 3) {
                    next_grid[i][j] = 1; // Becomes alive (reproduction)
                } else {
                    next_grid[i][j] = 0; // Remains dead
                }
            }
        }
    }
}


// Function to simulate a single generation
void simulate_generation(int grid[ROWS][COLS], int next_grid[ROWS][COLS]) {
    update_grid(grid, next_grid);
}

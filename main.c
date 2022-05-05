#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define ROW_SIZE 9
#define COL_SIZE 9
#define NUM_X_BLOCKS 3
#define NUM_Y_BLOCKS 3
#define NUM_BLOCKS (NUM_X_BLOCKS * NUM_Y_BLOCKS)
#define BLOCK_X_SIZE 3
#define BLOCK_Y_SIZE 3
#define BLOCK_SIZE (BLOCK_X_SIZE * BLOCK_Y_SIZE)
#define BOARD_SIZE (ROW_SIZE * COL_SIZE)

void print_board(uint8_t *board) {
	for (int y = 0; y < COL_SIZE; y++) {
		for (int x = 0; x < ROW_SIZE; x++) {
			int val = board[y * ROW_SIZE + x];
			if (!val) {
				printf("_ ");
			} else {
				printf("%u ", val);
			}
		}
		printf("\n");
	}
}

// Rotate by 3 every line until at a multiple of 3 row start,
// and then add an additional +1 to avoid pattern repeat
uint8_t *generate_board(uint8_t *board) {
	int v = 5;
	for (int i = 0; i < BOARD_SIZE; i++) {
		board[i] = v + 1;

		if (i != 0 && ((i + 1) % ROW_SIZE) == 0) {
			v += 3;
			if (((i / ROW_SIZE) + 1) % 3 == 0) {
				v += 1;
			}
		}

		v = (v + 1) % ROW_SIZE;
	}

	return board;
}

bool validate_board(uint8_t *board) {
	// Check rows
	for (int y = 0; y < COL_SIZE; y++) {
		uint8_t row_set[ROW_SIZE + 1] = {0};
		for (int x = 0; x < ROW_SIZE; x++) {
			int val = board[y * ROW_SIZE + x];
			if (val && row_set[val] > 0) {
				printf("%d @ (%d, %d) is a duplicate row value!\n", val, x + 1, y + 1);
				return false;
			}
			row_set[val] = 1;
		}
	}

	// Check cols
	for (int x = 0; x < ROW_SIZE; x++) {
		uint8_t col_set[COL_SIZE + 1] = {0};
		for (int y = 0; y < COL_SIZE; y++) {
			int val = board[y * ROW_SIZE + x];
			if (val && col_set[val] > 0) {
				printf("%d @ (%d, %d) is a duplicate col value!\n", val, x + 1, y + 1);
				return false;
			}
			col_set[val] = 1;
		}
	}

	// Check squares
	for (int i = 0; i < NUM_BLOCKS; i++) {
		int block_x = (i / NUM_X_BLOCKS);
		int block_y = (i % NUM_Y_BLOCKS);

		uint8_t block_set[BLOCK_SIZE + 1] = {0};
		for (int y = 0; y < NUM_Y_BLOCKS; y++) {
			for (int x = 0; x < NUM_X_BLOCKS; x++) {

				int comp_x = (x + (block_x * NUM_X_BLOCKS));
				int comp_y = (y + (block_y * NUM_Y_BLOCKS));

				int val = board[comp_y * ROW_SIZE + comp_x];

				if (val && block_set[val] > 0) {
					printf("%d @ (%d, %d) is a duplicate block value!\n", val, comp_x + 1, comp_y + 1);
					return false;
				}
				block_set[val] = 1;
			}
		}
	}

	return true;
}

int main() {
	uint8_t board[BOARD_SIZE] = {0};

	generate_board(board);
	validate_board(board);
	print_board(board);

	return 0;
}

//
// Created by ludovic on 07/09/2025.
//

#include <stdio.h>

int main(int arge, char** argv) {
	char c = 0;
	while (c >= 0) {
		printf("%/c %d \n", c, c);
		c += 1;
	}
	return 0;
}


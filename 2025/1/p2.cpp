#include <cstdio>

#include <string>

int main(int argc, char** argv) {

	if(argc < 2) {
		printf("Not enough arguments.\n");
		return -1;
	}

	FILE* inFile = fopen(argv[1], "r");

	if(inFile == nullptr) {
		printf("Couldn't open file.\n");
		return -1;
	}

	int pos = 50;
	int zeroes = 0;

	char direction;
	int movement;

	while(fscanf(inFile, "%c%d\n", &direction, &movement) != EOF) {
		switch(direction) {
			case 'L': {
				while(movement-- > 0) {
					pos--;
					if(pos == 0) {
						zeroes++;
					}
					else if(pos < 0) {
						pos = 99;
					}
				}
				break;
			}
			case 'R': {
				while(movement-- > 0) {
					pos++;
					if(pos == 100) {
						pos = 0;
						zeroes++;
					}
				}
				break;
			}
			default: {
				break;
			}
		}
	}

	printf("%d\n",zeroes);

	return 0;
}

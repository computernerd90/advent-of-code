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
		//printf("direction: %c, movement: %d, ", direction, movement);
		
		switch(direction) {
			case 'L':
				pos -= movement;
				break;
			case 'R':
				pos += movement;
				break;
			default:
				break;
		}

		if(pos >= 100) {
			while(pos >= 100)
				pos -= 100;
		} else if(pos < 0) {
			while(pos < 0)
				pos += 100;
		}

		//printf("pos: %d\n", pos);
		if(pos == 0)
			zeroes++;
	}

	printf("%d\n",zeroes);

	return 0;
}

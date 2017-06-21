
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int quotient(int n) {

	int inc = 0;
	inc = n / 9371;
	if (inc == 0)
		inc = 1; //9371 is a prime number.
	printf("%d", inc);
	return inc;
}

void Brent(int memory[], int loc, int name) {


	int add1, add2;
	int loc1 = 0, loc2 = 0;
	int c1 = 0, c2 = 0;

	add1 = quotient(memory[loc]);
	add2 = quotient(name);

	loc1 = loc + add1;
	loc2 = loc + add2;

	if (loc1>9370)
		loc1 = loc1 % 9371;
	if (loc2>9370)
		loc2 = loc2 % 9371;


	while (memory[loc1] != 0)
	{
		loc1 += add1;

		if (loc1>9370)
			loc1 = loc1 % 9371;
		c1++;

	}

	while (memory[loc2] != 0)
	{

		loc2 += add2;

		if (loc2>9370)
			loc2 = loc2 % 9371;

		c2++;

	}


	if (c1<c2)
	{
		memory[loc1] = memory[loc];
		memory[loc] = name;
		return;
	}

	memory[loc2] = name;
	printf("ok\n");

}

void store(int array[], int n) {

	int hash = n % 9371; //9371 is a prime number.
	if (array[hash] == 0)
		array[hash] = n;
	else Brent(array, hash, n); //Collision happend, solve it with Brent Method.
}

void main() {

	FILE *fptr;
	FILE *sptr;

	char buffer[100], name[15], c;
	int AirQuality[MAX], i, j;
	int hash, iname = 0, s = 1;

	fpos_t pos; //Postion object to track line position.

	for (i = 0; i <= MAX; i++) { //Initial file naming structure to zero.
		AirQuality[i] = 0;
	}

	if ((fptr = fopen("AirQuality.csv", "r")) == NULL)
		printf("Failed\n");

	else {

		i = 0;

		for (j = 0; j < 9357; j++) {

			char name[30];
			fgetpos(fptr, &pos); //Track line position.

			while ((c = getc(fptr)) != ':') { //Naming the new file using a hash of txte and time.
				if (c != ','&&c != '-'&&c != '\n') { //Removing redundant characters and zeros.
					name[i++] = c;
					if (i == 5 && c == '0')
						i--;
				}
			}
			name[i] = '\0';

			fseek(fptr, pos, SEEK_SET);
			fscanf(fptr, "%s", buffer); //Copying a line to the buffer.
			sscanf(name, "%d", &iname);
			strcat(name, ".txt");

			if ((sptr = fopen(name, "r")) == NULL) { //Tring to open a file with unique hash key.

				if ((sptr = fopen(name, "w")) != NULL) {

					printf("%s", name);
					fprintf(sptr, "%s", &buffer); //Moving txt from buffer to the new file.
					fclose(sptr);
					printf(" done\n");
					store(AirQuality, iname); //store file name to the array with hash function iname mod 9371.	

				}

				else {
					printf("Failed\n");
					s = 0;
				}
			}

			else {
				printf("Var zaten\n");
				s = 0;
				fclose(sptr);
			}

			i = 0;
			fseek(fptr, ftell(fptr) + 1, SEEK_SET); //Set cursor to the next line begining.

		}		

	}

	if (s == 1) {

		printf("\n                 Done\n\n");
		system("PAUSE");
		exit(0);
	}
	else {
		printf("\n     Failed! please make sure that no old files exist and test program again.\n");
		system("PAUSE");
		exit(0);
	}
	fclose(fptr);
}

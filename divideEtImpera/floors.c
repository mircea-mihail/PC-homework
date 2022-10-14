//the problem this code solvs is written at the end

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

//this function can both randomly generate a floor for the bottles to break at, 
//but, using the "index", you can also pick a specific one
void fileGen(int n){
	FILE *fp = fopen("floors.in", "w" );
	if(fp == NULL){
		printf("file generation error\n");
		exit(EXIT_FAILURE);
	}

	fprintf(fp, "%d\n", n);
	
	srand(time(NULL));
	int index = rand() % n;
	
	//index = 0;

	for(int i = 0; i < index; i++)
		fprintf(fp, "%d ", 1);

	for(int i = index; i< n; i++)
		fprintf(fp, "%d ", 0);
	
	fclose(fp);
}

void reading(int **t, int *n){
	FILE *fp = fopen("floors.in", "r");
	if(fp == NULL){
		printf("there was an error finding the file\n");
		exit(EXIT_FAILURE);
	}
	fscanf(fp, "%d", &(*n));
	if(*n == EOF){
		printf("error reading the number of floors\n");
		exit(EXIT_FAILURE);
	}

	*t = (int *)malloc(sizeof(int) * *n);

	if(t == NULL){
		printf("error malloc-ing the floors\n");
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < *n; i++){
		fscanf(fp, "%d", &((*t)[i]));
		if((*t)[i] == EOF){
			printf("error reading a floor\n");
			exit(EXIT_FAILURE);
		}
	}
	fclose(fp);
}

void printing(int *t, int n){
	for(int i = 0; i < n; i++)
		printf("%d ", t[i]);
	printf("\n\n");
}

int iterativeFinalFloor(int *block, int index, int n, int *noBottles, int *totalThrows, int recursiveBrokenFloor, FILE *fp){
	//the recursive function already checks the index when it's over 14, but if the bottle breaks
	//on the 14th floor where the recursive function checks for the first time, the index stays 0, unckecked.
	//this means that we can no longer continue with the index from + 1, witchout checking floor 0

	if(index == 0){
		*totalThrows = *totalThrows + 1;
		if(block[index] == 0){
			printf("on floor %d a bottle broke\n", index);
			fprintf(fp, "on floor %d a bottle broke\n", index);
			*noBottles = *noBottles - 1;	
			return index;
		}
		else {
			printf("on floor %d a bottle survived the fall\n", index);
			fprintf(fp, "on floor %d a bottle survived the fall\n", index);
		}
	}
	for(int i = index + 1; i < n; i++){
		if(i == recursiveBrokenFloor)
			return i;
		//this floor has already been checked before, as such there is no point in throwing another bottle 
		//by accounting for this already tested floor, for 100 floors the worst case number for checked floors is a constant 14
		*totalThrows = *totalThrows + 1;
		if(block[i] == 0){
			printf("on floor %d a bottle broke\n", i);
			fprintf(fp, "on floor %d a bottle broke\n", i);
			*noBottles = *noBottles - 1;
		}
		else {
			printf("on floor %d a bottle survived the fall\n", i);
			fprintf(fp, "on floor %d a bottle survived the fall\n", i);
		}
		if(*noBottles == 0)
			return i; 
	}
	return n;
}

//the ideal solution looks like a series:
//x+(x-1)+(x-2)+...+3+2+1 = noRemainingFloors ==>
//x(x+1)/2 = noRemainingFloors
//
//as a result, we get the DIVIDE formula:
//x^2 + x - 2*noRemainingFloors = 0 

int formula(int noRemainingFloors){
	return (int)((sqrt(1 + 8 * noRemainingFloors) - 1)/2);
}

//recursiveFloor(bloc, 0, 0, n - 1, noBottles, totalThrows, recursiveBrokenFloor, fp); (noBottles == 2)
void recursiveFloor(int *bloc, int *safeFloor, int down, int up, int *noBottles, int *totalThrows, int *recursiveBrokenFloor, FILE *fp){
	if(*noBottles == 1 || down > up)
		return;

	//no throwing bottles on floor 0!
	//(we let the iterative function deal with that)
	if(down != 0){
		if(bloc[down] == 0){
			*noBottles = *noBottles - 1;
			printf("on floor %d a bottle broke\n", down);
			fprintf(fp, "on floor %d a bottle broke\n", down);
			*recursiveBrokenFloor = down;
			*totalThrows = *totalThrows + 1;
		}
		else{
			printf("on floor %d a bottle survived the fall\n", down);
			fprintf(fp, "on floor %d a bottle survived the fall\n", down);
			*safeFloor = down;
			*totalThrows = *totalThrows + 1;
		}
	}

	int forfor = formula(up - down);
	if(forfor == 0)
		return;
	//if the formula returns 0 the recursiveFloor func loops forever

	down = down + formula(up - down);

	recursiveFloor(bloc, safeFloor, down, up, noBottles, totalThrows, recursiveBrokenFloor, fp);

}

void counter(int n){
	printf("the block's schematic:\n");
	int aux = 1;
	for(int i = 0; i < 10; i++)
		printf("%d ", i);
	while(n > aux * 10){ 
		for(int i = 0; i < 10; i++)
			printf("%d ", i);
		aux ++;
	}
	printf("\n");

}



int main(){
	fileGen(100);
	int *bloc, n, etaj = 0, sticleInitiale, noBottles = 2;
	int recursiveBrokenFloor, totalThrows = 0;
	FILE *fp = fopen("etaje.out", "w");
	if(fp == NULL){
		printf("file finding error\n");
		exit(EXIT_FAILURE);
	}

	sticleInitiale = noBottles;
	reading(&bloc, &n);
	
	//block distribution printing
	counter(n);
	printing(bloc, n);
	
	//on my block, floor 0 is indeed a floor, and as such, the last floor is floor n-1
	recursiveFloor(bloc, &etaj, 0, n - 1, &noBottles, &totalThrows, &recursiveBrokenFloor, fp);

	etaj = iterativeFinalFloor(bloc, etaj, n, &noBottles, &totalThrows, recursiveBrokenFloor, fp);
	
	if(noBottles == sticleInitiale){
		printf("\n\nthe bottle didn't break on any floor\n\n\n");
		fprintf(fp, "\nthe bottle didn't break on any floor\n");
	}
	else{
		printf("\nthe bottle broke on floor %d\n\n", etaj);
		fprintf(fp, "\nthe broke breaks on floor %d,\n", etaj);
	}
	printf("there are %d remaining bottles and\n%d total throws made\n", noBottles, totalThrows);
	fprintf(fp, "there are %d remaining bottles and\n%d total throws made\n", noBottles, totalThrows);
	
	free(bloc);
	fclose(fp);
	return 0;
}

/*
	Maria lives in a block of flats with n floors, numbered from 0 to n-1
She wishes to find out what the highest floor that doesn't break the bottle is.

	Maria only has 2 glass bottles at hand. Using the divide et impera method, 
display the floors she needs to throw the bottle from in order to find the answer,
with the lowest amount of attempts.

	Input data: 
		the floors.in file
		on the first line there is n number of floors

	Output:
		the etaje.out file where the floors where the bottle is thrown at are displayed in order
		each line must contain a floor
*/

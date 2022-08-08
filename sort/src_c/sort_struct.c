/**
 * sort_struct.c
 * 2022-06-01 K.OHWADA
 */

// gcc sort_struct.c
// reference : https://monozukuri-c.com/langc-funclist-qsort/

#include <stdio.h>
#include <stdlib.h>


/**
 * typedef struct
 * structure that stores personal information
 */
typedef struct 
{
	char	name[32];
	int	age;	
	double	height;		
} person;


/**
 * person players
* array to store the players
 */
person players[] =
{
	{"Rafael Nadal", 33, 185.6},
	{"Novak Đokovic", 32, 188.1},
	{"Roger Federer", 38, 185.4},
	{"Kei Nishikori", 29, 178.2},
};

/**
 *  cmpAscAge
* compare age (ascending)
 */
int cmpAscAge(const void * p1, const void * p2)
{	
	int age1 = ((person *)p1)->age;
	int age2 = ((person *)p2)->age;

	if (age1 > age2) return 1;
	if (age1 < age2) return -1;
	return 0;
}


void dump(person players[], int size)
{
	for (int i=0 ; i < size; i++)
	{
		printf("%-20s, %d, %.1lf \n", players[i].name, players[i].age, players[i].height);
	}
	printf("\n");
}


/**
 * main
 */
int main(void)
{
 	int size = sizeof(players) / sizeof(players[0]);
	dump(players, size);

	qsort(players, size, sizeof(person), cmpAscAge);

	dump(players, size);

	return 0;
}


// Kei Nishikori       , 29, 178.2 
// Novak Đokovic      , 32, 188.1 
// Rafael Nadal        , 33, 185.6 
// Roger Federer       , 38, 185.4 


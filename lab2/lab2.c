/*	TE2101 Programming Methodology Lab 2
	PUNG YANHAN A0169467L	*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ROWS 20
#define COLUMNS 20

//Declare GLOBAL variables
int globalmatrix[ROWS][COLUMNS] = { 0 };
int globaledge[ROWS] = { 0 };

/*	Declare function prototype. Call LOCAL variables within.	*/
void random_matrix(int localmatrix[ROWS][COLUMNS]);
void display_matrix(int localmatrix[ROWS][COLUMNS]);
void spacebar(void);
void isolated(int localmatrix[ROWS][COLUMNS]);
void onehop(int localmatrix[ROWS][COLUMNS]);
void twohop(int localmatrix[ROWS][COLUMNS]);
void edgenumber(int localmatrix[ROWS][COLUMNS], int localedge[ROWS]);
void densely_connected(int localedge[ROWS]);
void loosely_connected(int localedge[ROWS]);
void three_clique(int localmatrix[ROWS][COLUMNS]);
void continue_quit(int localmatrix[ROWS][COLUMNS]);

/*	Call function with GLOBAL variables in MAIN.
Able to use the function repeatedly with different GLOBAL variables.	*/
int main()
{
	random_matrix(globalmatrix);
	isolated(globalmatrix);
	display_matrix(globalmatrix);
	spacebar();
	onehop(globalmatrix);
	spacebar();
	twohop(globalmatrix);
	spacebar();
	edgenumber(globalmatrix, globaledge);
	spacebar();
	densely_connected(globaledge);
	spacebar();
	loosely_connected(globaledge);
	spacebar();
	three_clique(globalmatrix);
	spacebar();
	continue_quit(globalmatrix);

	getchar();
	getchar();
	return 0;
}

//Generate random matrix array
void random_matrix(int localmatrix[ROWS][COLUMNS]) 
{

	int i, j;

	//Initialise matrix array to zero
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLUMNS; j++)
		{
			localmatrix[i][j] = 0;
		}
	}

	srand((unsigned int)time(NULL));

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLUMNS; j++)
		{
			/*	Use random (MOD2 + 0) to generate elements with the value zero or one.
				(+0) for lower limit	*/
			localmatrix[i][j] = rand() % 2 + 0;

			//Mirror upper triangular matrix to lower triangular matrix to create symmetry
			if (i > j)
			{
				localmatrix[i][j] = localmatrix[j][i];
			}

			//Make all diagonal entries to zero
			if (i == j)
			{
				localmatrix[i][j] = 0;
			}
		}
	}


}

//Display the generated random matrix
void display_matrix(int localmatrix[ROWS][COLUMNS]) 
{

	int i, j;

	printf("Welcome to my Graph Processing tool!!!\n\n");
	printf("The adjacency matrix for graph G\n");

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLUMNS; j++)
		{
			printf("%d ", localmatrix[i][j]);
		}
		printf("\n");
	}
}

//Create space and bar
void spacebar(void) 
{
	printf("\n");
	printf("==============================\n");
	printf("\n");
}

//Account for isolated nodes
void isolated(int localmatrix[ROWS][COLUMNS]) 
{

	int i, j, isolatedCount;
	int randomCount = 0;

	for (i = 0; i < ROWS; i++) 
	{
		isolatedCount = 0;

		for (j = 0; j < COLUMNS; j++)
		{
			//Condition to detect isolated node
			if (localmatrix[i][j] == 0)
			{
				isolatedCount++;
			}

		}

		/*	When isolated node is detected, randomCount generates a random node [0,19] to connect to.
			if randomCount equals to itself, randomCount will random and add 1 and modulus to prevent
			array overflow	*/
		if (isolatedCount == ROWS)
		{
			randomCount = rand() % ROWS;
			randomCount = (randomCount == i) ? ((randomCount + 1) % ROWS) : randomCount;
			localmatrix[i][randomCount] = 1;
			localmatrix[randomCount][i] = 1;
		}
	}

}

//List of one-hop neighbours
void onehop(int localmatrix[ROWS][COLUMNS]) 
{
	int i, j;

	printf("List of one-hop neighbours\n");

	for (i = 0; i < ROWS; i++)
	{
		//Print the index of all vertices
		printf("Vertix %d: ", i);

		for (j = 0; j < COLUMNS; j++)
		{
			//Condition to detect one-hop and print the one-hop neighbours
			if (localmatrix[i][j] == 1)
			{
				printf("%d ", j);
			}
		}

		printf("\n");
	}
}

//List of two-hop neighbours
void twohop(int localmatrix[ROWS][COLUMNS]) 
{
	int i, j, k;

	printf("List of two-hop neighbours\n");

	for (i = 0; i < ROWS; i++)
	{
		printf("Vertix %d:", i);

		/*	Obtain two-hop neighbours when [i][j] are not one-hop neighbours and not equals to itself,
			search the matrix for [i][k] one-hop neighbours and [k][j] one-hop neighbours	*/
		for (j = 0; j < COLUMNS; j++)
		{

			if (localmatrix[i][j] == 0 && i != j)
			{
				for (k = 0; k < COLUMNS; k++)
				{
					if (localmatrix[i][k] == 1 && localmatrix[k][j] == 1)
					{
						printf("%d ", j);
						break;
					}
				}

			}

		}
		printf("\n");
	}
}

//List number of Edges for each nodes
void edgenumber(int localmatrix[ROWS][COLUMNS], int localedge[ROWS]) 
{

	int i, j;
	int edgeCount = 0;

	printf("Number of Edges for each nodes\n");

	for (i = 0; i < ROWS; i++)
	{
		edgeCount = 0;
		printf("Vertix %d: ", i);

		for (j = 0; j < COLUMNS; j++)
		{
			//Condition to detect edge
			if (localmatrix[i][j] == 1)
			{
				edgeCount++;
			}
		}

		printf("%d\n", edgeCount);

		//Store the edgeCount in 1 dimensional array
		localedge[i] = edgeCount;
	}

}

//List of densely connected nodes
void densely_connected(int localedge[ROWS])
{
	int i;
	int maxEdge = localedge[0];

	printf("Densely Connected Nodes\n");

	//Obtain maximum value in array
	for (i = 0; i < ROWS; i++)
	{
		if (localedge[i] > maxEdge)
		{
			maxEdge = localedge[i];
		}
	}

	//Print all the maximum value if any
	for (i = 0; i < ROWS; i++)
	{
		if (localedge[i] == maxEdge)
		{
			printf("%d ", i);
		}

	}

}

//List of loosely connected nodes
void loosely_connected(int localedge[ROWS])
{
	int i;
	int minEdge = localedge[0];

	printf("Loosely Connected Nodes\n");

	//Obtain minimum value from array
	for (i = 0; i < ROWS; i++)
	{
		if (localedge[i] < minEdge)
		{
			minEdge = localedge[i];
		}
	}

	//Print all the minimum value if any
	for (i = 0; i < ROWS; i++)
	{
		if (localedge[i] == minEdge)
		{
			printf("%d ", i);
		}
	}

}


//List of 3-Clique structure.
void three_clique(int localmatrix[ROWS][COLUMNS])
{
	int vertices1 = 0, vertices2 = 0, vertices3 = 0;

	printf("You can determine a 3-Clique structure, if it exists in your graph");
	printf("\n");
	printf("Input 3 Vertices <0 to %d>", ROWS - 1);
	printf("\n");
	scanf_s("%d %d %d", &vertices1, &vertices2, &vertices3);

	//Compare 3 input vertices to obtain 3-Clique using Bitwise AND.
	if ((localmatrix[vertices1][vertices2] & localmatrix[vertices1][vertices3] & localmatrix[vertices2][vertices3]) == 1)
	{
		printf("YES, nodes %d, %d and %d are one-hop neighbours and form a 3-Clique", vertices1, vertices2, vertices3);
	}
	else
	{
		printf("NO 3-Clique structure found with nodes %d, %d and %d", vertices1, vertices2, vertices3);
	}

}

//Continue or Quit the program
void continue_quit(int localmatrix[ROWS][COLUMNS])
{
	char retry;

	printf("Do you wish to try again? <Type Y to continue or Q to quit>");
	printf("\n");

	/*	"blank" in the format string tells scanf to skip leading whitespace, 
		"1" read single character	*/
	scanf_s(" %c", &retry, 1);
	printf("\n");

	//OR logic allows the user to input both upper and lower case of the letter. 
	if (retry == 'y' || retry == 'Y')
	{
		three_clique(globalmatrix);
		spacebar();
		continue_quit(globalmatrix);
	}
	else if (retry == 'q' || retry == 'Q')
	{
		printf("Thanks and Good Bye.");
	}
	else
	{
		continue_quit(globalmatrix);
	}
}


/*
 * ENGSCI233: Lab - Error
 * lu_main.c
 *
 * PURPOSE:
 * To TEST your implementation of LU factorisation with partial pivoting.
 *
 * PREPARATION:
 * Have a go at the tasks in errlab_practice.py
 *
 * SUBMISSION:
 * DO NOT submit this file.
 *
 * TO DO:
 * - COMPLETE the functions lu_factor and lu_forward_sub in lu.c
 * - COMPILE your code without errors.
 * - DO NOT modify this file.
 */

/* Import some useful libraries and header files */
#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "allocate.h"
#include "fileio.h"
#include "lu.h"

/* Main program, executed at start-up. */
int main(int argc, char * argv[])
{
	/* Command-line keywords */
	enum { program = 0, file = 1, pivot = 2 };

	int n;
	int pivoting = 0;
	double num;

	FILE * fid = NULL;

	/* Print help information */
	if (argc == 1)
	{
		printf("usage: %s filename <pivot=0|1>\n", argv[program]);
		return EXIT_SUCCESS;
	}

	/* Get pivoting flag from command line */
	if (argc == 3)
	{
		sscanf(argv[pivot], "%d", &pivoting);
	}

	/* Open data file and read in problem size */
	FOPEN(fid, argv[file], "r");
	fscanf(fid, "%d", &n);
		
	/* allocate memory for A, b and p*/
	double **A;
	A = malloc(n * sizeof *A);
	for (int i = 0; i<n; i++) A[i] = malloc(n * sizeof *A[i]);

	double *b;
	b = malloc(n * sizeof *b);

	int *p;
	p = malloc(n * sizeof *p);
	
	/* Read in A matrix */
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fscanf(fid, "%lf ", &num);
			A[i][j] = num;
		}
	}

	/* Read in RHS vector */
	for (int i = 0; i < n; i++) {
		fscanf(fid, "%lf ", &num);
		b[i] = num;

	}

	FCLOSE(fid);

	/* Initialise row swap vector */
	for (int i = 0; i < n; i++) {
		p[i] = i;
	}

	/* Print to screen A matrix and RHS vectors */
	printf("A = [\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%f ", A[i][j]);
		}
		printf("\n");
	}
	printf("]\n");
	
	printf("b = [\n");
	for (int i = 0; i < n; i++) printf("%f \n", b[i]);
	printf("]\n");

	/* Factor the A matrix */
	lu_factor(n, A, p, pivoting);

	/* Print to screen LU factors and row swap vector*/
	printf("LU = [\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%f ", A[i][j]);
		}
		printf("\n");
	}
	printf("]\n");

	printf("p = [\n");
	for (int i = 0; i < n; i++) printf("%d \n", p[i]);
	printf("]\n");

	/* Solve for x */
	lu_solve(n, A, p, b);

	/* Output solutions */
	printf("x = [\n");
	for (int i = 0; i < n; i++) printf("%f \n", b[i]);
	printf("]\n");

	/* Free allocated memory */
	for (int i = 0; i < n; i++) free(A[i]);
	free(A);
	free(b);
	free(p);

	return 0;
}

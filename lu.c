/*
 * ENGSCI233: Lab - Error - NAME: Jaime Wu ID: 442689185 UPI: jwu153
 * lu.c
 *
 * PURPOSE:
 * To IMPLEMENT LU factorisation with partial pivoting.
 *
 * PREPARATION:
 * Have a go at the tasks in errlab_practice.py
 *
 * SUBMISSION:
 * - You MUST submit this file as part of the lab.
 * - DO NOT modify the filename.
 *
 * TO DO:
 * - COMPLETE the functions lu_factor and lu_forward_sub.
 * - COMPILE your code without errors.
 * - TEST your implementation in lu_main.c, work through any issues in DEBUGGING.
 * - DO NOT modify any of the other functions.
 * - Try to make use of LATE DECLARATION in your functions. See lu_backward_sub for an example.
 *
 * HINTS:
 * - Get a Python implementation working first.
 * - Check the syntax advice commented in lu_backward_sub.
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "lu.h"

/* This function is incomplete, you must complete it as part of the lab. */
/*                  ----------                                           */
void lu_factor(int n, double **A, int *p, int pivoting)
{
	// Declare variables 
	double pivot_value, sf;

	// Loop over each row in the matrix 
	for (int i = 0; i < n; i++) {

		// If we want to use partial pivoting then pivoting is set to 1, otherwise 0
		if (pivoting) {
			// Late declaration of variables 
			double value, *temp;
			int idx;

			// Get the index of the row that has the largest absolute value to use as pivot
			idx = i;
			value = A[i][i];

			// Algorithm for finding largest absolute value (row wise)
			for (int row = i; row < n; row++) {
				if (fabs(A[row][i]) > fabs(value)) {
					idx = row;
					value = A[row][i];
				}
			}

			// Make the row swap, and store the index of the row swap in a vector p
			// Row swap achieved by swapping the addresses of elements in first order array 
			p[i] = idx;
			temp = A[idx];
			A[idx] = A[i];
			A[i] = temp;
		} else {
			// If we are not usinng partial pivoting then make first element of vector p -1 (to indicate no row swaps) 
			p[0] = -1;
		}

		// Get the pivot value 
		pivot_value = A[i][i];

		// Print a warning in case of a small pivot value
		if (fabs(pivot_value) < ZERO_TOLERANCE) {
			printf("\nENGSCI233:TinyPivot - Pivot value is close to zero\n");
		}

		// Perform row reduction operations by starting at one row below the pivot row till the end of the matrix 
		for (int r = i+1; r < n; r++) {
			// Calculates a subtraction factor for row reduction
			sf = A[r][i]/pivot_value;

			// Perform the row reduction calculation across each required row 
			for (int c = i; c < n; c++) {
				A[r][c] = A[r][c] - sf * A[i][c];
			}

			// Store the subtraction factor on the lower triangular part of the matrix (i.e. replacing the zeros from the row reduction)
			A[r][i] = sf;
		}
	}
}

/* This function is incomplete, you must complete it as part of the lab. */
/*                  ----------                                           */
void lu_forward_sub(int n, double **A, int *p, double *y)
{

	// If we want to use partial pivoting then first element of p is not -1 
	if (p[0] != -1) {
		// Initialise variables (late declaration)
		double temp;
		int idx;

		// Perform row swapping on the RHS vector (i.e. vector B from LUX = B) to match row swapping prior in LU
		for (int i = 0; i < n; i++) {
			// Vector p contains which rows have been switched after every iteration 
			idx = p[i];

			// Performs the row swap for the RHS vector B
			temp = y[idx];
			y[idx] = y[i];
			y[i] = temp;
		}
	}

	// Perform forward substitution operations 
	for (int r = 0; r < n; r++) {
		// Calculates the y vector via a dot product
		for (int j = 0; j < r; j++) {
			y[r] = y[r] + -A[r][j] * y[j];
		}

	}
}

/* This function is complete, do not modify it. */
/*                  --------                    */
void lu_backward_sub(int n, double **A, double *x)
{
	/* Backward substitution */

	/* Don't forget key C syntax:
	 *  - semi-colons at the end of each command
	 *  - for loops and if code BLOCKS inside in braces {}
	 *  - for loop iteration control and if conditions in parentheses ()
	 *  - declare variable types BEFORE using them (int, double, str, bool)
	 */

	int i;                          /* early declaration, telling the code that you will EVENTUALLY use an integer called i */

	for (i = n - 1; i >= 0; i--)    /* iteration control format: (initial value; stopping condition; iteration increment) */
	{
		if (fabs(A[i][i]) < ZERO_TOLERANCE) {   /* fabs() is the absolute value function for floats */
			fprintf(stderr, "Warning: Near-zero denominator.\n");
		}
		double sum = x[i];                       /* late declaration, telling the code that you will NOW use a variable called 'sum' */
		for (int j = i + 1; j < n; j++) {
			sum -= A[i][j] * x[j];            /* array indexing: Array[row_index][column_index], from zero*/
		}
		x[i] = sum / A[i][i];
	}
}

/* This function is complete, do not modify it. */
/*                  --------                    */
void lu_solve(int n, double **A, int *p, double *x)
{

	/* Solve forward problem */
	lu_forward_sub(n, A, p, x);

	/* Output intermediate solution */
	printf("y = [\n");
	for (int i = 0; i < n; i++) printf("%f \n", x[i]);
	printf("]\n");

	/* Solve backward problem */
	lu_backward_sub(n, A, x);

}

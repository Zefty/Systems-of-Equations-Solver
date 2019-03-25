
/*
 * lu.h
 *
 * Routines for solving square systems of linear equations with
 * one right-hand side Ax=b using Doolittle LU factorisation
 * with partial pivoting
 */


/* Zero tolerance for double precision */
#define ZERO_TOLERANCE 1.0E-12


/*
 * Doolittle LU factorisation with partial pivoting, A=LU
 * Input:
 *   n   = size of matrix A
 *   A   = matrix A to be factorised, (nxn) stored by row
 *   pivoting = flag to switch on partial pivoting
 * Output:
 *   A   = factorised A matrix, (nxn) stored by row
 *   p   = pivot vector, (nx1) 
 * Failure scenarios:
 *   Encounter a "zero" pivot
 */
void lu_factor(int n, double **A, int *p, int pivoting);


/*
 * Solves factorised system using forward and back substitution
 * Input:
 *   n   = size of matrix A
 *   A   = factorised A matrix, (nxn) stored by row
 *   p   = pivot vector, (nx1)
 *   b   = right-hand vector, (nx1)
 * Output:
 *   b   = solution vector, (nx1)
 * Failure scenarios:
 *   As for lu_backward_sub
 */
void lu_solve(int n, double **A, int *p, double *b);


/*
 * Forward substitution, Ly=b
 * Input:
 *   n   = size of matrix A
 *   A   = factorised A matrix, (nxn) stored by row
 *   p   = pivot vector, (nx1)
 *   b   = right-hand side vector, (nx1)
 * Output:
 *   b   = intermediate solution vector, (nx1) 
 * Failure scenarios:
 *   None
 */
void lu_forward_sub(int n, double **A, int *p, double *b);


/*
 * Backward substitution, Ux=y
 * Input:
 *   n = size of matrix A
 *   A = factorised A matrix, (nxn) stored by row
 *   y = intermediate solution vector, (nx1)
 * Output:
 *   y = solution vector, (nx1)
 * Failure scenarios:
 *   Division by "zero"
 */
void lu_backward_sub(int n, double **A, double *y);

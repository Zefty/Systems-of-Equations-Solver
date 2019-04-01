from errlab_functions import*
tol = 1.e-10							# error tolerance

[A, b] = lu_read('test1.txt')						# read a matrix and RHS vector
LU,p = lu_factor(A, pivot=True, display=True) 

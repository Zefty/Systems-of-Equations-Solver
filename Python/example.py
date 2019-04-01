from errlab_functions import*
from numpy.linalg import norm           # norm function computes the 'length' of a vector
tol = 1.e-10							# error tolerance
[A, b] = lu_read('test1.txt')						# read a matrix and RHS vector
LU,p = lu_factor(A, pivot=False, display=True) 
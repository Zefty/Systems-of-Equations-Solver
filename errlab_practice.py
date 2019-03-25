# ENGSCI233: Lab - Error
# errlab_practice.py

# PURPOSE:
# To TEST your implementation of LU factorisation with partial pivoting.

# PREPARATION:
# Notebooks error.ipynb and lu_factorisation.ipynb (refresher on LU factorisation, in supplementary/).

# SUBMISSION:
# DO NOT submit this file. 

# imports
from errlab_functions import*
from numpy.linalg import norm           # norm function computes the 'length' of a vector
tol = 1.e-10							# error tolerance


# EXERCISE 1: LU factorisation 
# In Section 1 of the lu_factorisation notebook, we recapped Doolittle factorisation to generate upper and lower
# triangular factors of a matrix A.

# TO DO:
# - Perform LU factorisation BY HAND for the matrix.
#        _              _
#       |  2   3  -4   2 |
#   A = | -4  -5   6  -3 |
#       |  2   2   1   0 |
#       |_-6  -7  14  -4_|
#
# - COMPLETE the function LU_FACTOR in the file errlab_functions.py
# - How do I know its CORRECT? Test your implementation by PASSING the ASSERT commands below.
# - How do I DEBUG? Check the print out at the end of each iteration matches your own BY HAND steps.
# - You DO NOT need to modify any of the commands below.


[A, b] = lu_read('test1.txt')						# read a matrix and RHS vector
LU,p = lu_factor(A, pivot=False, display=True)   	# change display to False when LU_FACTOR working
LU_soln = np.array([
	[ 2, 3,-4, 2],
	[-2, 1,-2, 1],
	[ 1,-1, 3,-1],
	[-3, 2, 2, 2]])									# correct output of LU_FACTOR
assert norm(LU - LU_soln) < tol						# test agreement



# EXERCISE 2: Forward and backward substitution
# In Section 1 of the lu_factorisation notebook, we recapped forward and backward substitution to obtain,
# first, the intermediate vector, y, and then the solution vector, x, using matrices L and U.

# TO DO:
# - Perform forward and backward substitution BY HAND for the LU factors and RHS vector.
#        _              _             _              _             _  _
#       |  1   0   0   0 |           |  2   3  -4   2 |           |  4 |
#   L = | -2   1   0   0 |       U = |  0   1  -2   1 |       b = | -8 |
#       |  1  -1   1   0 |           |  0   0   3  -1 |           |  9 |
#       |_-3   2   2   1_|           |_ 0   0   0   2_|           |_ 6_|
#
# - COMPLETE the functions LU_FORWARD_SUB and LU_BACKWARD_SUB in the file errlab_functions.py
# - How do I know its CORRECT? Test your implementation by PASSING the ASSERT commands below.
# - How do I DEBUG? Enter debugging and check vectors y and x match your own BY HAND steps at each iteration.
# - You DO NOT need to modify any of the commands below.

# testing forward substitution
y = lu_forward_sub(LU, b) 		
y_soln = np.array([4,0,5,8])						# correct output of LU_FORWARD_SUB
assert norm(y[:,0] - y_soln) < tol


# testing backward substitution
x = lu_backward_sub(LU, y) 	
x_soln = np.array([1, 2, 3, 4])						# correct output of LU_BACKWARD_SUB
assert norm(x[:,0] - x_soln) < tol



# EXERCISE 3: Partial pivoting
# In Section 2 of the lu_factorisation notebook, we showed how to modify Dootlittle factorisation to 
# include and record partial pivoting ROW SWAPS.

# TO DO:
# - Perform LU factorisation, forward and backward substitution BY HAND using partial pivoting.
# - MODIFY the function LU_FACTOR and LU_FORWARD_SUB in the file errlab_functions.py to implement 
#   partial pivoting
# - How do I know its CORRECT? Test your implementation by PASSING the ASSERT commands below.
# - How do I DEBUG? Enter debugging and check vectors y and x match your own BY HAND steps at each iteration.
# - You DO NOT need to modify any of the commands below.

# testing LU factorisation with partial pivoting
[A, b] = lu_read('test1.txt')
LU,p = lu_factor(A, pivot=True, display=True)
	# test row swap vector
p_soln = [3,3,2,3]									# correct output of LU_FACTOR
assert all([r1 == r2 for r1, r2 in zip(p, p_soln)])
	# test factorized matrix
LU_soln = np.array([
	[  -6,  -7,  14,  -4],
	[-1/3, 2/3, 2/3, 2/3],
	[-1/3,-1/2,   6,  -1],
	[ 2/3,-1/2,-1/2,-1/2]])							# correct output of LU_FACTOR
assert norm(LU - LU_soln) < tol


# testing forward substitution with partial pivoting
y = lu_forward_sub(LU, b, p) 	
y_soln = np.array([6,6,14,-2])						# correct output of LU_FORWARD_SUB
assert norm(y[:,0] - y_soln) < tol


# testing backward substitution
x = lu_backward_sub(LU, y) 	
x_soln = np.array([1, 2, 3, 4])						# correct output of LU_BACKWARD_SUB
assert norm(x[:,0] - x_soln) < tol


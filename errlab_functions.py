# ENGSCI233: Lab - Error
# errlab_functions.py

# PURPOSE:
# To IMPLEMENT LU factorisation with partial pivoting and solve matrix equation.

# PREPARATION:
# Notebook error.ipynb, ESPECIALLY Section 3.3 refresher on LU factorisation.

# SUBMISSION:
# - DO NOT submit this file.

# TO DO:
# - COMPLETE the functions lu_factor(), lu_forward_sub() and lu_backward_sub().
# - TEST each function is working correctly by passing the asserts in errlab_practice.py.
# - DO NOT modify the other functions.

import numpy as np
from copy import copy
from warnings import warn

# this function is complete
def lu_read(filename):	
		
	with open(filename, 'r') as fp:
		# Row dimension
		nums = fp.readline().strip()
		row = int(nums)
		
		A = []
		for i in range(row):
			nums = fp.readline().rstrip().split()
			A.append([float(num) for num in nums])
		A = np.array(A)
		
		b = []
		nums = fp.readline().rstrip().split()
		b.append([float(num) for num in nums])
		b = np.array(b)
		
	return A, b.T

	
# **this function is incomplete**
#					 ----------
def lu_factor(A, pivot=False, display=False):
		
	# get dimensions of square matrix 
	n = np.shape(A)[0] 	
	
	# create initial row swap vector: p = [0, 1, 2, ... n]
	p = np.arange(n) 		

	# display matrix DO NOT MODIFY
	if display:
		print('')
		print('After {:d} steps'.format(0))
		print('LU=')
		print(A)
		print('p=')
		print(p)

	# loop over each row in the matrix
	# **hint** what is the pivot index, row and column?
	for i in range(n):		
		
		# Step 2: Row swaps for partial pivoting
		#    DO NOT attempt until Steps 0 and 1 below are confirmed to be working.
		if pivot:
			# **hint** Pseudocode the key steps below (locating pivots, row swaps etc).
			# **note** When swapping rows, use the copy() command, i.e., temp = copy(A[1,:])
			idx = i 
			value = A[i,i]

			for row in range(i,n):
				if abs(A[row,i]) > abs(value):
					value = A[row,i]
					idx = row
			
			p[i] = idx
			temp_pivot = copy(A[idx,:])
			temp_replace = copy(A[i,:])

			A[i,:] = temp_pivot
			A[idx,:] = temp_replace
	
			# **delete the command below when code has been written**

		# Step 0: Get the pivot value
		pivot_value = A[i,i]
		
		# Print a warning in case of small pivot value.
		if abs(pivot_value) < zero_tol():
			warn('ENGSCI233:TinyPivot - Pivot value is close to zero')
			
		# Step 1: Perform the row reduction operations 
		# **hint** Pseudocode the key steps first (loop over which rows? subtract how much from what?)

		for r in range(i+1,n):
			sf = A[r,i]/pivot_value

			for c in range(i,n):
				A[r,c] = A[r,c] - sf*A[i,c]

			A[r,i] = sf
				

		# display matrix DO NOT MODIFY
		if display:
			print('')
			print('After {:d} steps'.format(i))
			print('LU=')
			print(A)
			print('p=')
			print(p)
	
	return A, p

	
# **this function is incomplete**
#					 ----------
def lu_forward_sub(L, b, p=None):
	
	# check shape of L consistent with shape of b (for matrix mult L^T*b)
	assert np.shape(L)[0] == len(b), 'incompatible dimensions of L and b'
	
	# make a copy so RHS vector not destroyed during operations
	y = copy(b)
	
	# Step 0: Get matrix dimension										
	# **hint** See how this is done in lu_factor()
	n = np.shape(L)[0] 
		
	# Step 2: Perform partial pivoting row swaps on RHS
	print(p)
	if p is not None:
		# **hint** Pseudocode the key steps below	
		# **note** When swapping values, use the copy() command, i.e., temp = copy(y[i])
		idx = 0 	
		for i in range(n):
			idx = p[i]

			temp_swap = copy(b[idx])
			temp_replace = copy(b[i])

			b[i] = temp_swap
			b[idx] = temp_replace			
		# **delete the command below when code has been written**
	
	# Step 1: Perform forward substitution operations
	# **hint** Pseudocode the key steps below (loops, dot products etc.)

	for r in range(n):
		y[r] = b[r] + np.dot(-L[r,0:r],y[0:r])	
		
	return y

	
# **this function is incomplete**
#					 ----------
def lu_backward_sub(U, y):
	
	# check shape consistency
	assert np.shape(U)[0] == len(y), 'incompatible dimensions of U and y'
	
	n = np.shape(U)[0] 

	x = copy(y)
	
	# Perform backward substitution operations
	for r in range(n-1,-1,-1):
		x[r] = (y[r] + np.dot(-U[r,n:r:-1],x[n-1:r:-1]))/U[r,r]

	return x
	# **delete the command below when code has been written**


# this function is complete
def zero_tol():
	#ZERO_TOL  Tolerance for comparison with zero.
	# See also EPS.
	return 1.e-12
# Systems of Equation Solver
Put systems of equations into matrix form Ax=B

           2.0  3.0 -4.0  2.0
      A = -4.0 -5.0  6.0 -3.0
           2.0  2.0  1.0  0.0
          -6.0 -7.0 14.0 -4.0
       
      B =  4.0 -8.0  9.0  6.0

Input: .txt file

      Size of square matrix 
      A
      B
      
      /*Example:      
      L1    4 
      L2    2.0  3.0 -4.0  2.0
      L3    
      .
      .
      .    -6.0 -7.0 14.0 -4.0
      L     4.0 -8.0  9.0  6.0*/
      
      


## Compiling Instructions ## 

### Method 1: ###
Open project file and build solution from VS Studio

### Method 2: ###
Compile via VS Studio Developer CMD 

            cl *.c 
     
Launching Instructions
      
Shift right click folder and open Windows Powershell
            
            ./solver file-name.txt 1
            
      OR
      
           ./lu file-name.txt 1 

Note: Turning partial pivoting functionality on/off 
           
Partial Pivoting = True 
      
           ./solver file-name.txt 1
           
Partial Pivoting = False 
      
           ./solver file-name.txt 0
           
           
           
           
             




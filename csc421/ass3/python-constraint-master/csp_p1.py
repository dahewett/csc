

from constraint import *

# Init problem
problem = Problem()
# Set up domain for letters
domain = [i for i in range(10)]
# Addd vars
problem.addVariables(['T', 'W', 'F', 'O', 'R', 'U'], domain)
problem.addVariables(['C1', 'C2', 'C3'],[0, 1])

# Set up Constraints 
problem.addConstraint (AllDifferentConstraint(), ['T', 'W', 'F', 'O', 'R', 'U'])
problem.addConstraint (lambda T: T != 0, ('T'))
problem.addConstraint (lambda F: F != 0, ('F'))
problem.addConstraint (lambda O, R, C1: (O + O) == R + ( C1 * 10), ('O', 'R', 'C1'))
problem.addConstraint (lambda U, W, C1, C2: C1 + W + W == U + (10 * C2), ('U', 'W', 'C1', 'C2'))
problem.addConstraint (lambda T, O, C2, C3: C2 + T + T == O + (10 * C3), ('T', 'O', 'C2', 'C3'))
problem.addConstraint (lambda F, C3: F == C3, ('F', 'C3'))

# Get solution
sol = problem.getSolutions()
# Print sol
print(sol)

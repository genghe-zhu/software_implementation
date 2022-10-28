#!/bin/bash
#
# testing.sh - test sudoku implementation
#
# usage: testing.sh
# (no arguments)
#
# ./sudoku.sh create/solve size [server]
# output: all the test results to testing.out file
#
# Authors: William Scott, Isabella Zenkl, Genghe Zhu, Rachael Williams

make -s clean 
make -s

# REQUIRED: create three valid puzzles of size 9x9, 4x4, and 6x6 to test solver with regression and store in regress dir as 9puzzle.txt, 4puzzle.txt, 6puzzle.txt
# uncomment below if need to generate puzzles
#./sudoku create 9 > regress/9puzzle.txt
#./sudoku create 6 > regress/6puzzle.txt
#./sudoku create 4 > regress/4puzzle.txt
#./sudoku.sh create 3 > regress/cube.txt

#Test 1: test with incorrect number of arguments.
echo "Test 1: test with incorrect number of arguments. Should fail with exit code = 35"
if ./sudoku.sh
then
	echo "Test 1: Failed:("
    echo
else
    echo "exit code = " $?
	echo "Test 1: Passed:)"
fi
echo

#Test 2: test with invalid first argument.
echo "Test 2: test with invalid first argument. Should fail with exit code = 36"
if ./sudoku.sh bad 9
then
	echo "Test 2: Failed:("
    echo
else
    echo "exit code = " $?
	echo "Test 2: Passed:)"
fi
echo 

#Test 3: test with invalid second argument.
echo "Test 3: test with invalid second argument. Should fail with exit code = 37"
if ./sudoku.sh create 7
then
	echo "Test 3: Failed:("
    echo
else
    echo "exit code = " $?
	echo "Test 3: Passed:)"
fi
echo

#Test 4: test with invalid third argument.
echo "Test 4: test with invalid third argument. Should fail with exit code = 38"
if ./sudoku.sh create 9 bad
then
	echo "Test 4: Failed:("
    echo
else
    echo "exit code = " $?
	echo "Test 4: Passed:)"
fi
echo

#Test 5: valid creator test with size = 9.
echo "Test 5: valid creator test with size = 9"
if ./sudoku.sh create 9
then
	echo "Test 5: Passed:)"
else
    echo "exit code = " $?
	echo "Test 5: Failed:("
fi
echo 

#Test 6: valid creator test with size = 4.
echo "Test 6: valid creator test with size = 4"
if ./sudoku.sh create 4
then
	echo "Test 6: Passed:)"
else
    echo "exit code = " $?
	echo "Test 6: Failed:("
fi
echo 

#Test 7: valid creator test with size = 6.
echo "Test 7: valid creator test with size = 6"
if ./sudoku.sh create 6
then
	echo "Test 7: Passed:)"
else
    echo "exit code = " $?
	echo "Test 7: Failed:("
fi
echo 

#Test 8: valid solver test with size = 9 puzzle.
echo "Test 8: valid solver test with size = 9 puzzle"
if cat regress/9puzzle.txt | ./sudoku solve 9
then
	echo "Test 8: Passed:)"
else
    echo "exit code = " $?
	echo "Test 8: Failed:("
fi
echo

#Test 9: valid solver test with size = 4 puzzle.
echo "Test 9: valid solver test with size = 4 puzzle"
if cat regress/4puzzle.txt | ./sudoku solve 4
then
	echo "Test 9: Passed:)"
else
    echo "exit code = " $?
	echo "Test 9: Failed:("
fi
echo


#Test 10: valid solver test with size = 6 puzzle.
echo "Test 10: valid solver test with size = 6 puzzle"
if cat regress/6puzzle.txt | ./sudoku solve 6
then
	echo "Test 10: Passed:)"
else
    echo "exit code = " $?
	echo "Test 10: Failed:("
fi
echo

#Test 11: invalid solver test with size = 9 puzzle.
echo "Test 11: invalid solver test from inputting larger puzzle than solving. Should fail with exit code = 3"
if cat regress/9puzzle.txt | ./sudoku solve 4
then
	echo "Test 11: Failed:("
	echo
else
	echo "exit code = " $?
	echo "Test 11: Passed:)"
fi
echo

#Test 12: invalid solver test with size = 9 puzzle.
echo "Test 12: invalid solver test from inputting smaller puzzle than solving. Should fail with exit code = 3"
if cat regress/6puzzle.txt | ./sudoku solve 9
then
	echo "Test 12: Failed:("
	echo
else
	echo "exit code = " $?
	echo "Test 12: Passed:)"
fi
echo

#Test 13: invalid solver test with bad input
echo "Test 13: invalid solver test with bad input. Should fail with exit code = 3"
if echo 1 2 3 bad input | ./sudoku solve 9
then
	echo "Test 13: Failed:("
	echo
else
	echo "exit code = " $?
	echo "Test 13: Passed:)"
fi
echo

#Test 14: combining ./sudoku.sh and ./sudoku
echo "Test 14: combining ./sudoku.sh and ./sudoku with size = 9 puzzle"
if ./sudoku.sh create 9 | ./sudoku solve 9
then
	echo "Test 14: Passed:)"
else
    echo "exit code = " $?
	echo "Test 14: Failed:("
fi
echo

#Test 15: combining ./sudoku.sh and ./sudoku
echo "Test 15: combining ./sudoku.sh and ./sudoku with size = 4 puzzle"
if ./sudoku.sh create 4 | ./sudoku solve 4
then
	echo "Test 15: Passed:)"
else
    echo "exit code = " $?
	echo "Test 15: Failed:("
fi
echo

#Test 16: combining ./sudoku.sh and ./sudoku
echo "Test 16: combining ./sudoku.sh and ./sudoku with size = 6 puzzle"
if ./sudoku.sh create 6 | ./sudoku solve 6
then
	echo "Test 16: Passed:)"
else
    echo "exit code = " $?
	echo "Test 16: Failed:("
fi
echo

####### cube stuff ######
#Test 17: creating cube
echo "Test 17: creating a cube"
if ./sudoku.sh create 3
then
	echo "Test 17: Passed:)"
else
    echo "exit code = " $?
	echo "Test 17: Failed:("
fi
echo

#Test 18: creating cube
echo "Test 18: piping in cube into solver"
if cat regress/cube.txt | ./sudoku solve 3
then
	echo "Test 18: Passed:)"
else
    echo "exit code = " $?
	echo "Test 18: Failed:("
fi
echo

#Test 19: combining ./sudoku.sh and ./sudoku
echo "Test 19: combining ./sudoku.sh and ./sudoku with cube"
if ./sudoku.sh create 3 | ./sudoku solve 3
then
	echo "Test 19: Passed:)"
else
   echo "exit code = " $?
	echo "Test 19: Failed:("
fi
echo

##### bad cube #####
#Test 20: 
echo "Test 20: combining passing input out of column range into solve for cube. Should fail with exit code = 4"
if ./sudoku.sh create 6 | ./sudoku solve 3
then
	echo "Test 20: Failed:("
else
   echo "exit code = " $?
	echo "Test 20: Passed:)"
fi
echo

#Test 21: 
echo "Test 21: combining passing a non cube puzzle into solve for cube. Should fail with exit code = 1"
if ./sudoku.sh create 4 | ./sudoku solve 3
then
	echo "Test 20: Failed:("
else
   echo "exit code = " $?
	echo "Test 20: Passed:)"
fi
echo
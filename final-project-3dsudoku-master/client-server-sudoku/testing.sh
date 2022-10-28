#!/bin/bash
#
# testing.sh - test sudoku client-server implementation
#
# usage: testing.sh
# (no arguments)
#
# input: none
# output: all the test results to testing.out file
#
# William Garrett Scott

make -s clean
make -s 

HOSTNAME=$(ifconfig | grep 'inet ' | grep -E -o "([0-9]{1,3}[\.]){3}[0-9]{1,3}" | head -1)
let 'port = 3000'

#Test 1: test with incorrect number of arguments.
echo "Test 1: test with incorrect number of arguments. Should fail with exit code = 1"
if ./solverclient
then
	echo "Test 1: Failed:("
   echo
else
   echo "exit code = " $?
	echo "Test 1: Passed:)"
fi

echo 

#Test 2: test with bad hostname.
echo "Test 2: test with bad hostname. Should fail with exit code = 3"
if ./solverclient badhost $port
then
	echo "Test 2: Failed:("
   echo
else
   echo "exit code = " $?
	echo "Test 2: Passed:)"
fi

echo 

#Test 3: test with bad port.
echo "Test 3: test with bad hostname. Should fail with exit code = 4"
if ./solverclient $HOSTNAME 10
then
	echo "Test 3: Failed:("
   echo
else
   echo "exit code = " $?
	echo "Test 3: Passed:)"
fi

echo

#Test 4: connect to creator sever. request bad puzzle
echo "Test 4: connect to creator sever and request bad puzzle. Should fail with exit code = 16"
if echo bad | ./solverclient $HOSTNAME $port 
then
   echo "Test 4: Failed:("
else
   echo "exit code = " $?
   echo "Test 4: Passed:)"
fi

echo 

#Test 5: connect to creator sever. request bad puzzle
echo "Test 5: connect to creator sever and request bad puzzle. Should fail with exit code = 5"
if echo 100 | ./solverclient $HOSTNAME $port 
then
   echo "Test 5: Failed:("
else
   echo "exit code = " $?
   echo "Test 5: Passed:)"
fi

echo

#Test 6: connect to creator sever. request 9x9 puzzle
echo "Test 6: connect to creator sever and request 9x9 puzzle"
if echo 9 | ./solverclient $HOSTNAME $port 
then
	echo "Test 6: Passed:)"
else
   echo "exit code = " $?
   echo "Test 6: Failed:("
fi

echo

# #Test 7: connect to creator sever. request 4x4 puzzle
# echo "Test 7: connect to creator sever and request 4x4 puzzle"
# if echo 4 | ./solverclient $HOSTNAME $port 
# then
# 	echo "Test 7: Passed:)"
# else
#    echo "exit code = " $?
#    echo "Test 7: Failed:("
# fi

# echo

#Test 8: connect to creator sever. request 6x6 puzzle
echo "Test 8: connect to creator sever and request 6x6 puzzle"
if echo 6 | ./solverclient $HOSTNAME $port 
then
	echo "Test 8: Passed:)"
else
   echo "exit code = " $?
   echo "Test 8: Failed:("
fi

echo 

#Test 9: connect to creator sever. request 16x16 puzzle
echo "Test 9: connect to creator sever and request 16x16 puzzle"
if echo 16 | ./solverclient $HOSTNAME $port 
then
	echo "Test 9: Passed:)"
else
   echo "exit code = " $?
   echo "Test 9: Failed:("
fi

echo 

#Test 10: connect to creator sever. request cube
echo "Test 10: connect to creator sever and request cube"
if echo 3 | ./solverclient $HOSTNAME $port 
then
	echo "Test 10: Passed:)"
else
   echo "exit code = " $?
   echo "Test 10: Failed:("
fi
chill.c - a program to calculate "wind chill" based on current temperature and wind speed
 
Input: 0, 1, or 2 arguments
Output: 0 arguments -> windchill table for temp -10 to 40
	1 arguments -> windchill for user given temp
	2 arguments -> windchill for given temp and wind velocity 

Exit status: 
0 = no error
1 = too many arguments
2 = Temperature must be less than 50 degrees fahrenheit
3 = Temperature must be greater than -99 degrees fahrenheit
4 = Wind velocity must be greater than or equal to 0.5 MPH

Compiling:
run program with mygcc chill.c -lm -o chill because uses math.h library

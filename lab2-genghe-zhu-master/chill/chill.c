/* 
 * chill.c - a program to calculate "wind chill" based on current temperature and wind speed
 *
 * Input: 0, 1, or 2 arguments
 * Output: wind chill based on the arguments
 *
 * Exit status: 
 * 0 = no error
 * 1 = too many arguments
 * 2 = Temperature must be less than 50 degrees fahrenheit
 * 3 = Temperature must be greater than -99 degrees fahrenheit
 * 4 = Wind velocity must be greater than or equal to 0.5 MPH
 *
 *
 * CS50, Summer 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// function prototype *declarations*
void windchill(float temp, float velocity);
void windchillForOneTemp(float temp); 
void windchillForAllTemp();
void printHeader();

// Main function - ask for a guess, quit if it matches the answer and keep asking otherwise
int main(int argc, char *argv[]) {
  
  // too many arguments
  if (argc > 3) {
    fprintf(stderr, "Arguments must be less than 2\n");
    fprintf(stderr, "Usage: ./chill [temperature] [wind_velocity]\n");
    return 1;
  } 

  // if there are no arguments
  if (argc == 1) {
    printHeader();
    windchillForAllTemp();
  // if there are one or two arguments  
  } else {

    // convert first argument from string into double
    double temp = atof(argv[1]);

    // check temperature boundaries 
    if (temp >= 50) {
      fprintf(stderr, "Temperature must be less than 50 degrees fahrenheit\n");
      return 2;
    } else if (temp <= -99) {
      fprintf(stderr, "Temperature must be greater than -99 degrees fahrenheit\n");
      return 3;
    }

    // if there is one argument
    if (argc == 2) {
      printHeader();
      windchillForOneTemp(temp);

    // if there are two arguments  
    } else {

      // convert second argument from string into double
      double wind = atof(argv[2]);

      // check wind boundaries
      if (wind <= 0.5) {
        fprintf(stderr, "Wind velocity must be greater than or equal to 0.5 MPH\n");
        return 4;
      } else {
        printHeader();
        windchill(temp, wind);
      }
    }
  } 
  
  return 0;  // exit status
}


// prints out windchill given temp and wind velocity
void windchill(float temp, float wind) 
{
  float chill = 35.74 + 0.6215 * temp - 35.75 * (pow(wind, 0.16)) + 0.4275 * (pow(wind, 0.16));
  printf("%4.1f    %4.1f    %5.1f\n", temp, wind, chill);

}

// print out all the windchill for one temperature
void windchillForOneTemp(float temp)
{
  for (int i = 5; i <= 15; i += 5) {
    windchill(temp, (float)i);
  }
}

// print out all the windchill for all temperatures
void windchillForAllTemp()
{
  for (int i = -10; i <= 40; i += 10) {
    windchillForOneTemp((float)i);
    printf("\n");
  }
}

// print the header for the output 
void printHeader() 
{
  printf(" Temp    Wind    Chill\n");
  printf("-----    ----    -----\n");
}

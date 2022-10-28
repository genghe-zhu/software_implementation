/* 
 * histo.c - a program to print a histogram
 *
 * Input: read from stdin
 * Output: prints a histogram 
 *
 * Exit status: 
 * 0 = no error
 *
 *
 * CS50, Summer 2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int bins = 16;

// function prototype *declarations*
void mergeBins(int *histogram);
void printHistoRange(int maxValue, int binSize);
void printHist(int *histogram, int binSize);

// Main function - ask for a guess, quit if it matches the answer and keep asking otherwise
int main() 
{
    int maxValue = bins;
    int binSize = bins/16;
    int histogram[bins]; 

    // initialize the histogram values to 0
    for (int i = 0; i < bins; i++) {
        histogram[i] = 0;
    }

    printHistoRange(maxValue, binSize);

    int num; 
    int res = scanf("%d", &num);
    
    while (res == 1) {

        // change range until value fits into histogram
        while (num >= maxValue) {
            maxValue *= 2;
            binSize *= 2;
            printHistoRange(maxValue, binSize);
            mergeBins(&histogram[0]);
        }

        // ignore negative numbers
        if (num >= 0) {
            int position = num/binSize;

            histogram[position]++;
        } 

        res = scanf("%d", &num);
    }

    printHist(histogram, binSize);

    // exit status
    return 0;
  
}

// merge the bins given that the range doubled
void mergeBins(int *histogram)
{
    // merge the bins so that bin 1 becomes bin 1 + bin 2, etc 
    // fill the first 8 bins with the previous values
    for (int i = 0; i < bins; i += 2) {
        histogram[i/2] = histogram[i] + histogram[i+1];
    }

    // initialize the rest of the bins as 0
    for (int i = bins/2; i < bins; i++) {
        histogram[i] = 0;
    }

}

// print the number of bins, the bin size, and the range
void printHistoRange(int maxValue, int binSize)
{
    printf("%d bins of size %d for range [0,%d)\n", bins, binSize, maxValue);
}

// print the histogram
void printHist(int *histogram, int binSize) 
{
    // loop through all the bins
    for (int i = 0; i < bins; i++) {
        // get the number of digits for formatting 
        int maxNum = bins*binSize;
        int numDigits = 1;
        while ((maxNum /= 10) >= 1) {
            numDigits++;
        }

        // print the range
        printf("[ %*d: %*d] ", numDigits, i*binSize, numDigits, (i+1)*binSize-1);
        if (histogram[i] != 0) {
            printf("%d", histogram[i]);
        } 
        printf("\n"); 
    }
}


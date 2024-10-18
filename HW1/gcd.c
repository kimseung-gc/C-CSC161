/***********************************************************************
 * Name(s)  Seunghyeon Kim                                             *
 * Homework 1: Conditionals and Loops                                  *
 *                                                                     *
 * Assignment for Feb 17                                               *
 ***********************************************************************/

/***********************************************************************
 * Academic honesty certification:                                     *
 *   Written/online sources used:                                      *
 *     King, K. N. (2008). C Programming: A modern approach. W. W.     *
 * 　　　Norton.                                                         *
 *     Johnson, Barbara Z. “CSC 161 - Imperative Problem Solving -     *
 *     Homework 1.” CSC161,                                            *
 *     https://johnsonba.cs.grinnell.edu/CSC161/2023S/homework/hw1.html.
 *   My/our signature(s) below confirms that the above list of sources *
 *   is complete AND that I/we have not talked to anyone else          *
 *   (e.g., CSC 161 students) about the solution to this problem       *
 *                                                                     *
 *   Signature: SHK                                                    *
 ***********************************************************************/

#include <stdio.h>

/* HW1 problem 2
 * Program receives an input for gradings.
 *      It will calculate GCD of two integers that are input.
 */

// Question 2 initialization

/* Pre conditions: there has to be two integers put in
 * Post conditions: it returns the greatest common denominator between m and n the inputs.
 * It returns 0 when m or n is 0.
 */

int GCD (int m, int n);

int 
main(void){
    /* Prints the introduction of the program #2, the greatest common
       denominator. */
    printf("This program takes in two integer inputs, and prints their greatest common denominator\n");
    /* m is the first integer input and n is the second integer input before
       calculating the greatest common denominator of the two. Then it will
       be stored in gcd variable. */
    int m = 0, n = 0, gcd = 0;
    printf("Enter two integers: ");
    scanf("%d%d", &m, &n);
    gcd = GCD(m, n);
    printf("Their greatest common denominator is: %d\n", gcd);
    return 0;
}

int 
GCD(int m, int n)
{
    if (m==0){
        return n;
    }
    else if (n==0){
        return m;
    }
    /* d is a temporary variable that stores the initial value of n
       in order to copy it to m later on in the process of while loop.*/
    else{
        int d = 0;
        while (n != 0)
        {
            d = n;
            n = m%n;
            m = d;
        }
        return m;
    }
}
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

/* HW1 problem 1
 * Program receives an input for gradings.
 *      It will calculate the alphabetical gradings for a given numerical grading.
 */

/* num2LetHelper
 * Pre conditions: the input has to be an integer from 0 to 100
 * Post conditions: it will not return anything.
 * This function does not return anything, but prints a character 
 * (either '-', NULL, or '+') depending on the students' grade.
 */

void num2LetHelper (int remainder);

/* num2Let
 * Pre conditions: the input has to be integer from 0 to 100
 * Post conditions: it will return nothing. The return is for the successful execution
 * of the code like the main function. It is also used as an escape method from the FATAL
 * ERROR part.
 * A character from 'A' to 'F' will be printed if the input is correct. If the input is 
 * not correct,the function will throw an error.
 */

void num2Let (int numberGrade);

int 
main(void)
{
    /* Prints the introduction of the program #1, the numerical grading to
       alphabetical. */
    printf("This program takes in an integer input from 0 to 100, and prints the alphabetical grades\nby the range.\n");
    /* input is the input for converting numerical grading to an alphabetical
       grading. It is set as -1 in order to print error messages immediately
       when an invalid input is put. */
    int input = -1;
    printf("Please input an integer from 0 to 100: ");
    scanf("%d", &input);
    num2Let(input);
    return 0;
}

void 
num2LetHelper (int numberGrade)
{
    /* rem is the variable in order to store the remainder of dividing 
       numerical grade by 10 */
    int rem = numberGrade%10;
    if (numberGrade == 100){
        printf("+\n");
    }
    else if (rem < 3){
        printf("-\n");
    }
    else if (rem < 8){
        printf("\n");
    }
    else if (rem < 10){
        printf("+\n");
    }
}

void
num2Let (int numberGrade)
{
    if(numberGrade > 100 || numberGrade < 0){
        printf("FATAL ERROR, the program has been terminated (note: give an integer between 0 - 100!!)\n");
    }
    else if(numberGrade >= 90){
        printf("The grade is...\n A");
        num2LetHelper(numberGrade);
    }
    else if(numberGrade >= 80){
        printf("The grade is...\n B");
        num2LetHelper(numberGrade);
    }
    else if(numberGrade >= 70){
        printf("The grade is...\n C");
        num2LetHelper(numberGrade);
    }
    else if(numberGrade >= 60){
        printf("The grade is...\n D");
        num2LetHelper(numberGrade);
    }
    else if(numberGrade >= 0){
        printf("The grade is...\n F\n");
    }
    else{
        printf("FATAL ERROR, the program has been terminated (note: give an integer between 0 - 100!!)\n");
    }
}

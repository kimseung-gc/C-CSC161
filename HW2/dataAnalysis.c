/***********************************************************************
     * Name:                                                               *
     * Assignment name (Homework  2)                                       *
     * Data Analysis                                                       *
     * Assignment for May 12th 2023                                        *
     ***********************************************************************/

    /* *********************************************************************
     * Citations:                                                          *
     * 소비자물가지수 조사(공공용). 1 Feb. 2021,                                  *
     *      https://kosis.kr/statHtml/downLarge.do?file=101_DT_1J20003_    *
     *      M_20230506082756.txt.                                          *
     * Translated:                                                         *
     * Consumer price index investigation (for public use). 9 Apr. 2023,   *
     *      https://kosis.kr/statHtml/downLarge.do?file=101_DT_1J20003_    *
     *      M_20230506082756.txt.                                          *
     * Academic honesty certification:                                     *
     *   My signature below confirms that the above list of sources        *
     *   is complete AND that I/we have not talked to anyone else          *
     *   (e.g., CSC 161 students) about the solution to this problem       *
     *                                                                     *
     *   Signature: SHK                                                    *
     ***********************************************************************/
/*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "dataAnalysisUnited.h"

/* All the documentations are stored in the dataAnalysisUnited.h file. */

int 
main (int argc, char* argv[])
{
    char line[MAX_STRING_LENGTH+1];
    if(argc != 3){
        fprintf (stderr, "Usage: %s file-input file-output\n",argv[0]);
        return EXIT_FAILURE;
    }
    FILE * fl = fopen(argv[1], "r");
    if(fl == NULL){
        printf("Error in opening the file!\n");
        return -1;
    }
    for(int i = 0; i<2; i++){
        if(fgets(line, MAX_STRING_LENGTH, fl) == NULL){
            printf("The file is empty!\n");
            return -1;
        }
    }
    dataStack_t * dtSt = NULL;
    for(int i = 1; i < 50; i++){
        floatStack strSt = stringSplitCPI(line, "\"\t\"");
        if(strSt.top == NULL || strcmp(strSt.name,"Empty")==0 || isEmptyFloat(&strSt)){//Error checking the stack before proceeding with the data processing.
            return -1;
        }
        makeNewData(&dtSt, &strSt);
        if(fgets(line, MAX_STRING_LENGTH, fl) == NULL){// if it reaches end of line earlier than 50 iterations, it will stop the loop.
            i = 50;
        }
    }
    printData(dtSt);
    saveData(dtSt, argv[2]);
    if (fclose (fl))                       /* Close the file stream */
    {
        fprintf (stderr, "%s: Error closing file %s: %s\n",
                argv[0], argv[1], strerror(errno));
        return EXIT_FAILURE;
    }
    return 0;
}
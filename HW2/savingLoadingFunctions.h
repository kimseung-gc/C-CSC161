#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#ifndef __savingLoadingFunctions_h__
#define __savingLoadingFunctions_h__

#include <string.h>
#include "floatStack.h"
#include "frequencyStack.h"
#include "dataAnalysis.h"
#include <errno.h>

void
printingBufferSizeKR(FILE * stream, char * item, int bufferMAX){
    int temp = strlen(item)/3;
    for(int i = 0; i<bufferMAX-temp; i++){
        fprintf(stream, " ");
    }
}

void saveData(dataStack_t * stack, char * fileName){
    FILE * stream = fopen (fileName, "w");
    if (stream == NULL)                       /* Verify the open was successful */
    {                                         /* Report a failure */
        fprintf (stderr, "%s: Cannot open %s: %s\n",
                "Admin", fileName, strerror(errno));
        return;
    }
    fprintf(stream, "Region                        Standard Dev  Average         Mode       Min        Q1         Median     Q3         Max\n");
    for(dataStack_t * current = stack; current != NULL; current = stack){
        fprintf(stream, "%-30s", current->name);
        //printingBufferSizeKR(stream, current->name, 10);
        fprintf(stream, "%-13lf", current->stdDeviation);
        fprintf(stream, "%s", DIVIDER);
        fprintf(stream, "%-15lf", current->mean);
        fprintf(stream, "%s", DIVIDER);
        fprintf(stream, "%-10d", current->mode);
        fprintf(stream, "%s", DIVIDER);
        fprintf(stream, "%-10d", current->min);
        fprintf(stream, "%s", DIVIDER);
        fprintf(stream, "%-10d", current->Q1);
        fprintf(stream, "%s", DIVIDER);
        fprintf(stream, "%-10d", current->median);
        fprintf(stream, "%s", DIVIDER);
        fprintf(stream, "%-10d", current->Q3);
        fprintf(stream, "%s", DIVIDER);
        fprintf(stream, "%-10d", current->max);
        fprintf(stream, "\n");
        dataStack_t * temp = current->next;
        free(current);
        stack = temp;
    }
    if (fclose (stream))                       /* Close the file stream */
    {
        fprintf (stderr, "%s: Error closing file %s: %s\n",
                "Admin", fileName, strerror(errno));
        return;
    }
}

#endif
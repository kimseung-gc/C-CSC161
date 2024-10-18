#ifndef __3SavingFunction_h__
#define __3SavingFunction_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "1PrintingFunctions.h"

#define DIVIDER "|"

/* void save(ticket_t * first, int len, char * fileName)
 * Pre-condition: This function requires a pointer to the first element of the 
 * list named <first>, the length of the list, and the name of the file that
 * you would like to save the data of the list to.
 * Post-condition: This function does not return any output, but it creates a 
 * file named <fileName>, and it writes the length of the list, and each of the
 * data that the elements of the list had in the order 
 * ticketNum|companyID|problemType|technicianName.
 */
void
save (ticket_t * first, int len, char * fileName){
    FILE * stream = fopen (fileName, "w");
    if (stream == NULL)                       /* Verify the open was successful */
    {                                         /* Report a failure */
        fprintf (stderr, "%s: Cannot open %s: %s\n",
                "Admin", fileName, strerror(errno));
        return;
    }
    fprintf(stream, "%d\n", len);
    for(ticket_t * current = first; current != NULL; current = current->nextTicket){
        fprintf(stream, "%d%s%s%s%s%s%s\n", current->ticketNum, DIVIDER, current->ci, DIVIDER, current->probT, DIVIDER, current->name);
    }
    if (fclose (stream))                       /* Close the file stream */
    {
        fprintf (stderr, "%s: Error closing file %s: %s\n",
                "Admin", fileName, strerror(errno));
        return;
    }
}

/* int loadChunk(FILE * stream, char * stat, ticket_t ** tik)
 * Pre-condition: This function requires a pointer to the file as <stream>, 
 * <stat> which requires the status of the tickets, and a double pointer to
 * the initial element of the ticket list.
 * Post-condition: This function returns the length of the list that it assigns to 
 * (for the calculation of total ticket number), and returns -1 if something goes 
 * wrong. It replaces the *<tik> with a newly allocated memory which will be the data 
 * that decodes ticketNum|companyID|problemType|technicianName format from the previous 
 * function. This function is a helper function for the loadFile function.
 */
int
loadChunk(FILE * stream, char* stat, ticket_t ** tik){
    ticket_t * prev;
    int len = 0;
    fscanf(stream, "%d\n", &len);
    ticket_t * init = (ticket_t*) malloc (sizeof (ticket_t));
    if(init == NULL){
        perror ("Unable to allocate memory for a ticket\n");
        return -1;
    }
    if(len > 0){
        ticket_t * current = init;
        int j = 0;
        char c = 0;
        char str[MAXSTRLEN+1]; 
        for(int i = 0; i<len; i++){
            while(((c = fgetc(stream)) != '|')&&(j<MAXSTRLEN)){// load each of the data with decoded string.
                str[j] = c;
                j++;
            }
            str[j] = '\0';
            j = 0;
            current->ticketNum = atoi(str);
            while(((c = fgetc(stream)) != '|')&&(j<MAXSTRLEN)){
                str[j] = c;
                j++;
            }
            str[j] = '\0';
            j = 0;
            strcpy(current->ci, str);
            while(((c = fgetc(stream)) != '|')&&(j<MAXSTRLEN)){
                str[j] = c;
                j++;
            }
            str[j] = '\0';
            j = 0;
            strcpy(current->probT, str);
            while(((c = fgetc(stream)) != '\n')&&(j<MAXSTRLEN)){
                str[j] = c;
                j++;
            }
            str[j] = '\0';
            j = 0;
            strcpy(current->name, str);
            strcpy(current->status, stat);
            current->nextTicket = (ticket_t*) malloc (sizeof (ticket_t));
            prev = current;
            current = current->nextTicket;
        }
        free(current);
        prev->nextTicket = NULL;
        *tik = init;
    }else{
        *tik = NULL;
        free(init);
    }
    return len;
}

/* int loadFile(ticket_t** tik, char * loadingFile, char * type)
 * Pre-condition: This function requires the name of the loading file, double
 * pointer to the initial element of the list, and the type of data(such as "New,"
 * "Assigned," or "Completed")
 * Post-condition: This function returns the output of loadChunk (the length of 
 * the list for total ticket calculation), and returns -1 if something wrong 
 * happens. It replaces the *<tik> with a newly allocated memory which will be 
 * the data that decodes ticketNum|companyID|problemType|technicianName format 
 * from the previous function. This function is a helper function for the loadFile 
 * function.
 */
int
loadFile(ticket_t** tik, char * loadingFile, char * type){
    char * fileName = loadingFile;
    FILE * stream = fopen (fileName, "r");
    if (stream == NULL){
        fprintf (stderr, "%s: Cannot open %s: %s\n",
                "Admin", fileName, strerror(errno));
        return -1;
    }
    int temp = loadChunk(stream, type, tik);
    if (fclose (stream)){
        fprintf (stderr, "%s: Error closing file %s: %s\n",
                "Admin", fileName, strerror(errno));
        return -1;
    }
    return temp;
}

#endif

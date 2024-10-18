#ifndef __1PrintingFunctions_h__
#define __1PrintingFunctions_h__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSTRLEN 50
#define STR(EXPR) #EXPR
#define SCANSTR(LEN) "%" STR(LEN) "s"

typedef struct ticket ticket_t;

struct ticket
{
    int ticketNum;
    char ci[MAXSTRLEN+1];
    char probT[MAXSTRLEN+1];
    char status[MAXSTRLEN+1];
    char name[MAXSTRLEN+1];
    ticket_t* nextTicket;
};

/* helper function to read a string into a buffer of length MAXSTRLEN */
/* void getString(char * prompt, char * buffer)
 * Pre-conditions: The input <prompt> must be a string while <buffer> must 
 * be the address to store the string that was input.
 * Post-conditions: The functions will not return anything while it will
 * assign <buffer> the input string that was input after printing the
 * <prompt>.
 */
void
getString(char * prompt, char * buffer) {
  int numTokens;
  do {
    printf ("%s", prompt);
    numTokens = scanf (SCANSTR(MAXSTRLEN), buffer);
    if (numTokens==0) {
      printf ("Error reading value. Please try again.\n");
      continue;
    }
  } while (numTokens==0);
}

/* void printDetails(ticket_t * tik)
 * Pre-conditions: The input has to be a pointer that points to the exact ticket
 * to print the details out of.
 * Post-conditions: It will print the details of the ticket located in <tik>
 */
void 
printDetails(ticket_t * tik){
    printf("========================================Ticket Details=========================================\n");
    printf("    Ticket Details:\n");
    printf("        Ticket Number:              %d\n", tik->ticketNum);
    printf("        Company Identifier:         %s\n", tik->ci);
    printf("        Problem Type:               %s\n", tik->probT);
    printf("        Status:                     %s\n", tik->status);
    printf("        Name of Technician:         %s\n", tik->name);
    printf("        Address Stored in Computer: %p\n", tik);
}

/* void introductionProcess()
 * Pre-conditions: None
 * Post-conditions: It will print the introduction of the program (AKA menu)
 */
void 
introductionProcess(){
    printf("\n");
    printf("======================================Ticket Tracker 1.0=======================================\n");
    printf("      0. Print details of an existing ticket\n");
    printf("      1. Create a new tracking ticket\n");
    printf("      2. Assign a new ticket to a technician for handling\n");
    printf("      3. Mark a ticket complete\n");
    printf("      4. Print a list of new tickets\n");
    printf("      5. Print a list of assigned tickets\n");
    printf("      6. Print a list of completed tickets\n");
    printf("      7. Exit the program\n");
    printf("      8. Save and exit the program\n");
    printf("      9. Load saved files\n");
}


/* void printTickets (ticket_t * first)
 * Pre-conditions: The input must be the pointer to the first element of the
 * ticket list.
 * Post-conditions: It will print the list of tickets in the format of ticket 
 * number, company identifier, problem type, and name of the technician. If
 * one of the variables have a long string as their value, the function will
 * adjust it so that it will use ... at the last three indices of the string.
 * e.x. TICKETIER3404555 -> TICKETIER3...
 */
void 
printTickets (ticket_t * first) {
    char temp[MAXSTRLEN+1];
    printf("Ticket Number |      Company Identifier      |      Problem Type      | Name of Technician\n");//18
    for (ticket_t * current = first ; current != NULL ; current = current->nextTicket ) {
        printf("%-14d|", current->ticketNum);
        if(strlen(current->ci) > 28){
            for(int j = 0; j<25; j++){
                temp[j] = current->ci[j];
            }
            temp[25] = '.';
            temp[26] = '.';
            temp[27] = '.';
            printf(" %-29.28s|", temp);
        }else{
            printf(" %-29.28s|", current->ci);
        }
        if(strlen(current->probT) > 22){
            for(int j = 0; j<19; j++){
                temp[j] = current->probT[j];
            }
            temp[19] = '.';
            temp[20] = '.';
            temp[21] = '.';
            printf(" %-23.22s|", temp);
        }else{
            printf(" %-23.22s|", current->probT);
        }
        printf(" %s\n", current->name);
    }
    printf ("\nEnd of List\n");
}

/* void detailsRequest(ticket_t* tikNew, ticket_t* tikAssigned, ticket_t* tikCompleted)
 * Pre-conditions: The pointers to the first element of all three lists(New, Assigned, 
 * Completed) are required.
 * Post-conditions: It will ask for the targeting ticket's ticketNumber, and it will
 * find the target in all three lists. If it does not exist, it will print an error
 * message saying "Ticket not found." Otherwise, it will print the ticket's details.
 */
void 
detailsRequest(ticket_t* tikNew, ticket_t* tikAssigned, ticket_t* tikCompleted){
    if((tikNew == NULL)&&(tikAssigned == NULL)&&(tikCompleted == NULL)){
        printf("There are no tickets available!\n");
        return;
    }
    int tikN = 0;
    printf("Which ticket number would you like the details of?                       ");
    int temp = 0;
    temp = scanf("%d", &tikN);
    if(temp == 0){
        printf("Invalid input! Please try again! \n");
        fflush(stdin);
        return;
    }
    ticket_t * target = NULL;
    for(ticket_t * current = tikNew; current != NULL; current = current->nextTicket){
        if(current->ticketNum == tikN){
            target = current;
        }
    }
    if(target == NULL){
        for(ticket_t * current = tikAssigned; current != NULL; current = current->nextTicket){
            if(current->ticketNum == tikN){
                target = current;
            }
        }
    }
    if(target == NULL){
        for(ticket_t * current = tikCompleted; current != NULL; current = current->nextTicket){
            if(current->ticketNum == tikN){
                target = current;
            }
        }
    }
    if(target == NULL){
        printf("Ticket not found!\n");
        return;
    }else{
        printDetails(target);
    }
}

#endif
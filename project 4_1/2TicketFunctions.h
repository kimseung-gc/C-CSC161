#ifndef __2TicketFunctions_H__
#define __2TicketFunctions_H__
#include "1PrintingFunctions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* void createNewTicket(ticket_t** tik, int ttl)
 * Pre-conditions: <tik> must be a double pointer to the initial element of the
 * new ticket list. <ttl> must be the number of total tickets that are present
 * inside the list. <ttl> is required to assign the ticketNum of the new ticket as
 * <ttl>+1.
 * Post-conditions: It will not return anything, but it will assign a dynamically
 * allocated first element of the new ticket list or add the element at the end
 * of the list. As the tickets are new, their newTicket->status is assigned "new"
 * and newTicket->name is assigned "unassigned" as their values. Their other values
 * such as newTicket->ci and newTicket->probT are assigned as their input values. 
 * Note that their inputs are supposed to have no spaces within them.
 */
void 
createNewTicket(ticket_t** tik, int ttl){
    ticket_t * newTicket = (ticket_t*) malloc (sizeof (ticket_t));
    ticket_t * lastTicket;
    if (newTicket==NULL) {
        perror ("Unable to allocate memory for a ticket\n");
        return;
    }
    getString ( "What is the company identifier?                                          ", newTicket->ci );
    getString ( "what is problem type?                                                    ", newTicket->probT );
    if(*tik == NULL){
        *tik = newTicket;
        newTicket->ticketNum = ttl+1;
        strcpy(newTicket->status, "new");
        strcpy(newTicket->name, "unassigned");
        printf("Created the first new ticket!\n");
    }else{
        for(ticket_t * current = *tik; current != NULL; current = current->nextTicket){
            if(current->nextTicket == NULL){
                lastTicket = current;
            }
        }
        lastTicket->nextTicket = newTicket;
        newTicket->ticketNum = ttl+1;
        strcpy(newTicket->status, "New");
        strcpy(newTicket->name, "Unassigned");
        printf("Successfully created %.6dth new ticket!\n", newTicket->ticketNum);
    }
    printDetails(newTicket);
}

/* void techTicketAssignation(ticket_t** tikNew, ticket_t** tikAssigned)
 * Pre-conditions: <tikNew> must be a double pointer to the initial element of the
 * new ticket list. <tikAssigned> must also be a double pointer to the initial 
 * element of the assigned ticket list.
 * Post-conditions: This function does not return anything, but it takes in two 
 * input from user (the ticket number for ticket assignation and the other for the 
 * name of the technician). This function removes the target ticket from the new 
 * list and assigns the ticket to the assigned ticket list. If the ticket is in
 * the middle of the list, it will connect the element in front of the target
 * and behind the target.
 */
void 
techTicketAssignation(ticket_t** tikNew, ticket_t** tikAssigned){
    if(*tikNew == NULL){
        printf("There are no new tickets available!\n");
        return;
    }
    int tikN = 0;
    printf("Which ticket number would you like to assign a technician?               ");
    int temp = 0;
    temp = scanf("%d", &tikN);
    if(temp == 0){
        printf("Invalid input! Please try again! \n");
        fflush(stdin);
        return;
    }
    ticket_t * target = NULL;
    ticket_t * beforeTarget = NULL;
    ticket_t * lastTikAssigned = NULL;
    for(ticket_t * current = *tikNew; current != NULL; current = current->nextTicket){
        if((current->nextTicket != NULL)&&((current->nextTicket)->ticketNum == tikN)){
            beforeTarget = current;
        }
        if(current->ticketNum == tikN){
            target = current;
        }
    }
    for(ticket_t * current = *tikAssigned; current != NULL; current = current->nextTicket){
        if(current->nextTicket == NULL){
            lastTikAssigned = current;
        }
    }
    if(target == NULL){
        printf("Target ticket number is invalid! Please try another one. \n");
        return;
    }
    char nameOfTech[MAXSTRLEN+1];
    char ch;
    int i = 0;
    printf("What is the name of the technician? Press enter after finishing typing   " );
    getchar();
    while(((ch = getchar())!='\n')&&(i<=MAXSTRLEN)){
        nameOfTech[i] = ch;
        i++;
    }
    nameOfTech[i] = '\0';
    strcpy(target->status, "Assigned");
    strcpy(target->name, nameOfTech);
    if(beforeTarget == NULL){
        if(lastTikAssigned == NULL){
            *tikAssigned = target;
        }else{
            lastTikAssigned->nextTicket = target;
        }
        *tikNew = target->nextTicket;
        target->nextTicket = NULL;
    }else{
        beforeTarget->nextTicket = target->nextTicket;
        target->nextTicket = NULL;
        if(lastTikAssigned == NULL){
            *tikAssigned = target;
        }else{
            lastTikAssigned->nextTicket = target;
        }
    }
    printf("Ticket successfully assigned!\n");
    printDetails(target);
}

/* void markTicketComplete(ticket_t** tikAssigned, ticket_t** tikOld)
 * Pre-conditions: <tikAssigned> must also be a double pointer to the initial 
 * element of the assigned ticket list. <tikOld> must be a double pointer to 
 * the initial element of the completed ticket list. 
 * Post-conditions: This function does not return anything, but it takes in one 
 * input from user (the ticket number for ticket completion). This function 
 * removes the target ticket from the assigned list and assigns the ticket to 
 * the completed ticket list. If the ticket is in the middle of the list, it 
 * will connect the element in front of the target and behind the target.
 */
void 
markTicketComplete(ticket_t** tikAssigned, ticket_t** tikOld){
    ticket_t * lastOldTik = NULL;
    ticket_t * target = NULL;
    ticket_t * beforeTarget = NULL;
    int tikN = 0;
    printf("Which ticket number would you like to mark complete? ");
    int temp = scanf("%d", &tikN);
    if(temp == 0){
        printf("Invalid input! Please try again! \n");
        fflush(stdin);
        return;
    }
    for(ticket_t * current = *tikOld; current != NULL; current = current->nextTicket){
        if(current->nextTicket == NULL){
            lastOldTik = current;
        }
    }
    for(ticket_t * current = *tikAssigned; current != NULL; current = current->nextTicket){
        if((current->nextTicket != NULL)&&((current->nextTicket)->ticketNum == tikN)){
            beforeTarget = current;
        }
        if(current->ticketNum == tikN){
            target = current;
        }
    }
    if(target == NULL){
        printf("Ticket not found! \n");
        return;
    }
    strcpy(target->status, "Completed");
    if(beforeTarget == NULL){
        *tikAssigned = target->nextTicket;
        target->nextTicket = NULL;
        if(*tikOld == NULL){
            *tikOld = target;
        }else{
            lastOldTik->nextTicket = target;
        }
    }else{
        beforeTarget->nextTicket = target->nextTicket;
        target->nextTicket = NULL;
        if(lastOldTik == NULL){
            *tikOld = target;
        }else{
            lastOldTik->nextTicket = target;
        }
    }
    printf("Ticket successfully completed!\n");
    printDetails(target);
}

/* int lengthOfList(ticket_t * tik)
 * Pre-conditions: The input must be the pointer to the first element of a
 * ticket list.
 * Post-conditions: It will return the length of the list.
 */
int 
lengthOfList(ticket_t * tik){
    int i = 0;
    for(ticket_t * current = tik; current != NULL; current = current->nextTicket){
        i++;
    }
    return i;
}

#endif
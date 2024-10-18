    /***********************************************************************
     * Name(s)  Seunghyeon Kim, Joshua Delarosa                            *
     * Assignment name (Project  4)                                        *
     * Ticket Tracker                                                      *
     * Assignment for 28th April 2023                                      *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *   Written/online sources used:                                      *
     *     namelist.c was used!                                            *
     *   Help obtained                                                     *
     *     Professor Barbara                                               *
     *   My/our signature(s) below confirms that the above list of sources *
     *   is complete AND that I/we have not talked to anyone else          *
     *   (e.g., CSC 161 students) about the solution to this problem       *
     *                                                                     *
     *   Signature: SHK JD                                                 *
     ***********************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "2TicketFunctions.h"
#include "3SavingFunction.h"

int main(void){
    char n = 0;
    ticket_t * firstTikNew = NULL;
    ticket_t * firstTikAssigned = NULL;
    ticket_t * firstTikCompleted = NULL;
    int ttlTik = 0;
    printf("\n");
    printf("=====================================Ticket Tracker Intro======================================\n");
    printf("      This program is a program that keeps track of all the tickets\n");
    printf("      made for a start-up tech support company. \n");
    do{
        fflush(stdin);
        n = 0;
        introductionProcess();
        int temp = scanf("%c", &n);
        switch (n){
        case '0':
            detailsRequest(firstTikNew, firstTikAssigned, firstTikCompleted);
            break;
        case '1':
            createNewTicket(&firstTikNew, ttlTik);
            ttlTik++;
            break;
        case '2':
            techTicketAssignation(&firstTikNew, &firstTikAssigned);
            break;
        case '3':
            markTicketComplete(&firstTikAssigned, &firstTikCompleted);
            break;
        case '4':
            printf ("The names on the new tickets list are:\n\n");
            printf("=====================================New Ticket Details========================================\n");
            printTickets(firstTikNew);
            break;
        case '5':
            printf ("The names on the assigned tickets list are:\n\n");
            printf("==================================Assigned Ticket Details======================================\n");
            printTickets(firstTikAssigned);
            break;
        case '6':
            printf ("The names on the completed tickets list are:\n\n");
            printf("==================================Completed Ticket details=====================================\n");
            printTickets(firstTikCompleted);
            break;
        case '7':
            printf("Have a nice day sir/maam!\n");
            break;
        case '8':
            save(firstTikNew, lengthOfList(firstTikNew), "savedFileNew");
            save(firstTikAssigned, lengthOfList(firstTikAssigned), "savedFileAssigned");
            save(firstTikCompleted, lengthOfList(firstTikCompleted), "savedFileCompleted");
            printf("Files are successfully saved! Have a nice day sir/maam!\n");
            break;
        case '9':
            if((ttlTik = loadFile(&firstTikNew, "savedFileNew", "New")) == -1 || 
                (ttlTik += loadFile(&firstTikAssigned, "savedFileAssigned", "Assigned")) == -1 || 
                (ttlTik += loadFile(&firstTikCompleted, "savedFileCompleted", "Completed")) == -1){
                    printf("Some of the files were not found!");
                    ttlTik = 0;
                }else{
                printf("Files are successfully loaded!\n");
            }
            break;
        default:
            if(temp == 0){
                printf("Unable to assign the following character to the variable!\n");
            }else{
                printf("Invalid Input! please input a valid one!\n");
                printf("Note that the integer must be in the range [0, 9]!\n");
            }
        }
    }while (n != '7' && n != '8');
    return 0;
}
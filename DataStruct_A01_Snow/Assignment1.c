/*
 * FILE             :Assignment 1
 * PROGRAMMER       : Cameron Snow
 * FIRST VERSION    : 2026-10-10
 * DESCRIPTION      :
 *      This program promts the user for inupt before constructing 
 *          2 doubly linkd lists sorted by destination and fare respectivly,
 *          prints out the list sorted by fare  then destination, askes user for 
 *          a destination and date pair to change the fare before then redisplaying the lists
 */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct FlightInfo
{
    char Destination[15];
    char Date[9];
    double Fare;

    // Fare sorted doubly linked list
    struct FlightInfo* PreviousFlightByFare;
    struct FlightInfo* NextFlightByFare;

    // Destination sorted doubly linked list
    struct FlightInfo* PreviousFlightByDestination;
    struct FlightInfo* NextFlightByDestination;
};

/*
* METHOD       : createNewFlight
* DESCRIPTION  :
*     gets a string of the member name, formatted as "Lastname, Firstname"
* PARAMETERS   :
*   char* destination    : destination to be added
*   char* date           : date to be added
*   double fare          : fare to be added
* RETURNS      :
*   struct FlightInfo    : the FlightStruct with all variables set
*/
struct FlightInfo* createNewFlight(char* destination, char* date, double fare)
{
    struct FlightInfo* newFlight = (struct FlightInfo*)malloc(sizeof(struct FlightInfo));

    // on failure to allocate new struct
    if (newFlight == NULL) 
    {
        exit(EXIT_FAILURE);
    }

    // assigne values 
    strcpy(newFlight->Destination, destination);
    strcpy(newFlight->Date, date);
    newFlight->Fare = fare;

    // explicitly init links as NULL to protect from undefined behavior
    newFlight->NextFlightByFare = NULL;
    newFlight->PreviousFlightByFare = NULL;

    newFlight->NextFlightByDestination = NULL;
    newFlight->PreviousFlightByDestination = NULL;



    return newFlight;
}

/*
* METHOD       : insertDualSorted
* DESCRIPTION  :
*   takes in current list heds and tails as well as data points to be stored in struct 
*        then links the a nerw struct into the doubly linked lists
* PARAMETERS   :
*   struct FlightInfo** headByFare           : head of list by fare
*   struct FlightInfo** tailByFare           : tail of list by fare
*   struct FlightInfo** headByDestination    : head of list by destination
*   struct FlightInfo** tailByDestination    : tail of list by destination
*   char* destination                        : destination to be added
*   char* date                               : date to be added
*   double fare                              : fare to be added
* RETURNS      :
*   N/A
*/
void insertDualSorted(struct FlightInfo** headByFare, struct FlightInfo** tailByFare, struct FlightInfo** headByDestination, struct FlightInfo** tailByDestination, char* destination, char* date, double fare)
{
    struct FlightInfo* newFlight = createNewFlight(destination, date, fare);

    // Fare Sorting ==============================
    // Empty list, newFlight is both head and tail
    if (*headByFare == NULL)
    {
        *tailByFare = newFlight;
        *headByFare = newFlight;
    }
    // new fare is smaller than heads fare, make new head
    else if (fare <= (*headByFare)->Fare)
    {
        newFlight->NextFlightByFare = *headByFare; // new head links old head as next
        (*headByFare)->PreviousFlightByFare = newFlight; //old head links new head as prev
        *headByFare = newFlight; // newFlight is now head
    }
    // new fare is larger than tails fare, make new tail
    else if (fare >= (*tailByFare)->Fare)
    {
        newFlight->PreviousFlightByFare = *tailByFare; // new tail links old tail as prev
        newFlight->NextFlightByFare = NULL; // this flight is the end of the list 
        (*tailByFare)->NextFlightByFare = newFlight; // old tail links new tail as next
        *tailByFare = newFlight; // new flight is now tail
    }
    else
    {
        // newFlight was not smallest or largest in list, 
        // make current struct to navigate though list
        struct FlightInfo* currentByFare = (*headByFare)->NextFlightByFare; // head was already compared, start at next

        // while the currently checked flight is not null and currents fare is less than the new fare
        while (currentByFare != NULL && currentByFare->Fare < fare)
        {
            currentByFare = currentByFare->NextFlightByFare; // step through list
        }

        newFlight->NextFlightByFare = currentByFare; // newFlights next is now current
        newFlight->PreviousFlightByFare = currentByFare->PreviousFlightByFare; // newFlights prev is now currents prev

        currentByFare->PreviousFlightByFare->NextFlightByFare = newFlight;
        currentByFare->PreviousFlightByFare = newFlight; // current links newFlight as previous

    }

    // Destination sorting ==============================
    // Empty list, will be both head and tail
    if (*headByDestination == NULL)
    {
        *tailByDestination = newFlight;
        *headByDestination = newFlight;
    }

    // if destinations are identical or newFlights destination has a smaller value character in its first diff
    else if (strcmp(destination, (*headByDestination)->Destination) <= 0)
    {
        newFlight->NextFlightByDestination = *headByDestination; // newFlight links next to current head
        (*headByDestination)->PreviousFlightByDestination = newFlight; // current head links prev to newFlight
        *headByDestination = newFlight; // newflight is now head 
    }

    // if new destination compares as after tail destination
    else if (strcmp(destination, (*tailByDestination)->Destination) > 0)
    {
        newFlight->PreviousFlightByDestination = *tailByDestination;
        newFlight->NextFlightByDestination = NULL;
        (*tailByDestination)->NextFlightByDestination = newFlight;
        *tailByDestination = newFlight;
    }
    else //check logic, was missing input
    {
        struct FlightInfo* currentByDestination = (*headByDestination)->NextFlightByDestination;

        // 
        while (currentByDestination->NextFlightByDestination != NULL && strcmp(destination, currentByDestination->Destination) > 0) // is destination "larger" t
        {
            currentByDestination = currentByDestination->NextFlightByDestination;
        }

        newFlight->NextFlightByDestination = currentByDestination; // newFlights next is now current
        newFlight->PreviousFlightByDestination = currentByDestination->PreviousFlightByDestination; // newFlights prev is now currents prev

        currentByDestination->PreviousFlightByDestination->NextFlightByDestination = newFlight; // current's prev's next points to newFlight
        currentByDestination->PreviousFlightByDestination = newFlight; // current links newFlight as previous
    }

}

/*
* METHOD       : nullTerminate
* DESCRIPTION  :
*     gets user input, adds or replaces end of string with a null terminator, then
*     sanitises stdin buffer of any unhandled characters
* PARAMETERS   :
*   char* buffer         : character array to be collected and mutated within the function
*   size_t bufferSize    : size of the character array
* RETURNS      :
*   struct FlightInfo    : the FlightStruct with all variables set
*/
void nullTerminate(char* buffer, size_t bufferSize)
{
    // if the buffer is empty, get it to hold a nullterm
    if (fgets(buffer, bufferSize, stdin) == NULL)
    {
        buffer[0] = '\0';
    }

    // look for newline in string
    char* newLine = strchr(buffer, '\n');
    if (newLine != NULL) // found new line, replacing with nullterm
    {
        *newLine = '\0';
    }
    else // new line was not found (wasn't collected by fgets), empty stdin of any unhandled newlines
    {
        int charInt;
        while ((charInt = getchar()) != '\n');
    }
}

/*
* METHOD       : printSortedFare
* DESCRIPTION  :
*     prints the fare sorted list
* PARAMETERS   :
*   struct FlightInfo* head : head to start listing process with
* RETURNS      :
*   N/A
*/
void printSortedFare(struct FlightInfo* head)
{
    struct FlightInfo* current = head;
    while (current != NULL) // while current is not null, print its data and set current to next in list
    {
        printf("Destination: %s, Date: %s, Fare: $%.2f\n", current->Destination, current->Date, current->Fare);
        current = current->NextFlightByFare;
    }
}

/*
* METHOD       : printSortedDestination
* DESCRIPTION  :
*     prints the destination sorted list
* PARAMETERS   :
*   struct FlightInfo* head : The head to start the listing process with
* RETURNS      :
*   N/A
*/
void printSortedDestination(struct FlightInfo* head)
{
    struct FlightInfo* current = head;
    while (current != NULL) // while current is not null, print its data and set current to next in list
    {
        printf("Destination: %s, Date: %s, Fare: $%.2f\n", current->Destination, current->Date, current->Fare);
        current = current->NextFlightByDestination;
    }
}

/*
* METHOD       : findFlight
* DESCRIPTION  :
*   looks for a flight matching both the destination and date input, sorts
* PARAMETERS   :
*   struct FlightInfo* head     : head to start the search from
*   char* destination           : the destination to comapre againt the list item
*   char* date                  : the date to compare agains the list item
* RETURNS      :
*   struct FlightInfo* current  : the matching flight, NULL if no match
*/
struct FlightInfo* findFlight(struct FlightInfo* headByDestination, char* destination, char* date)
{
    struct FlightInfo* current = headByDestination;
    while (current != NULL) // 
    {
        if (strcmp(current->Destination, destination) == 0 && strcmp(current->Date, date) == 0) // check for both fields to match, return current if so
        {
            return current;
        }
        current = current->NextFlightByDestination; // move to next
    }
    return NULL; // no match
}


/*
* METHOD       : deleteFlight
* DESCRIPTION  :
*    takes flight found in findFlight and removes it from the lists, relinking the previous and next 
* PARAMETERS   :
*   struct FlightInfo** headByFare           : head of list by fare
*   struct FlightInfo** tailByFare           : tail of list by fare
*   struct FlightInfo** headByDestination    : head of list by destination
*   struct FlightInfo** tailByDestination    : tail of list by destination
*   struct FlightInfo*  targetFlight         : target in list to be removed
* RETURNS      :
*   N/A
*/
void deleteFlight(struct FlightInfo** headByFare, struct FlightInfo** tailByFare, struct FlightInfo** headByDestination, struct FlightInfo** tailByDestination, struct FlightInfo* targetFlight)
{
    if (targetFlight == NULL) // no match found, exit function
    {
        return;
    }

    // relink fare list 
    if (targetFlight->PreviousFlightByFare != NULL) // target was not head, must relink previous to next
    {
        targetFlight->PreviousFlightByFare->NextFlightByFare = targetFlight->NextFlightByFare;
    }
    else // target was head assign new head
    {
        *headByFare = targetFlight->NextFlightByFare;
    }

    if (targetFlight->NextFlightByFare != NULL) // target was not tail, must relink next to previous
    {
        targetFlight->NextFlightByFare->PreviousFlightByFare = targetFlight->PreviousFlightByFare;
    }
    else // target was tail, assign new tail
    {
        *tailByFare = targetFlight->PreviousFlightByFare;
    }

    //relink destination list 
    if (targetFlight->PreviousFlightByDestination != NULL) // target was ot head, must relink previous to next
    {
        targetFlight->PreviousFlightByDestination->NextFlightByDestination = targetFlight->NextFlightByDestination;
    }
    else // target was head assign new head
    {
        *headByDestination = targetFlight->NextFlightByDestination;
    }

    if (targetFlight->NextFlightByDestination != NULL) // target was not tail, must relink next to previous
    {
        targetFlight->NextFlightByDestination->PreviousFlightByDestination = targetFlight->PreviousFlightByDestination;
    }
    else // target was tail, assign new tail
    {
        *tailByDestination = targetFlight->PreviousFlightByDestination;
    }

    free(targetFlight); // free memory of removed flight

}

mutateLists(struct FlightInfo** headByFare, struct FlightInfo** tailByFare, struct FlightInfo** headByDestination, struct FlightInfo** tailByDestination, struct FlightInfo* targetFlight)
{
    char fareString[10];
    double fare;

    // get new fare to add
    printf("Current Fare: $%.2f\nEnter new fare: ", targetFlight->Fare);
    nullTerminate(fareString, sizeof(fareString));
    if (strcmp(fareString, ".") != 0) //as long as fare input is not '.'
    {
        struct FlightInfo* temp = createNewFlight(targetFlight->Destination, targetFlight->Date, targetFlight->Fare); // temporary copy for data modification
        sscanf(fareString, "%lf", &fare); //convert fareString data to double
        temp->Fare = fare;
        // delete old flight and replace with updated version
        deleteFlight(headByFare, tailByFare, headByDestination, tailByDestination, targetFlight);
        insertDualSorted(headByFare, tailByFare, headByDestination, tailByDestination, temp->Destination, temp->Date, temp->Fare);

    }
    else // no change will be made
    {
        printf("Fare remains unchanged");
    }
}

clearLists(struct FlightInfo** headByDestination)
{

    // structs to hold current and next flights
    struct FlightInfo* current;
    struct FlightInfo* next;
    current = *headByDestination;

    while (current != NULL)
    {
        next = current->NextFlightByDestination; //store the next flight in list before freeing the current one

        free(current); 

        current = next; //set current to next

    }
    *headByDestination = NULL; // ensure the head pointer is NULL

}

int main()
{

    // init heads and tails for fare and destination sorted lists
    struct FlightInfo* headByDestination = NULL;
    struct FlightInfo* tailByDestination = NULL;

    struct FlightInfo* headByFare = NULL;
    struct FlightInfo* tailByFare = NULL;

    // struct FlightInfo* targetFlight;

    char newDestination[15];
    char newDate[9];
    char newFareString[10]; //should hold fares up to 999999.99\0
    double newFare;
    int collectionLoop = 1;


    while (collectionLoop == 1)
    {
        // get user inputs
        printf("Enter destination: ");
        nullTerminate(newDestination, sizeof(newDestination));


        printf("Enter date: ");
        nullTerminate(newDate, sizeof(newDate));


        printf("Enter fare: ");
        nullTerminate(newFareString, sizeof(newFareString));

        // if dest and fare are not ".", insert into list
        if (strcmp(newDestination, ".") != 0 && strcmp(newFareString, ".") != 0)
        {

            sscanf(newFareString, "%lf", &newFare);
            insertDualSorted(&headByFare, &tailByFare, &headByDestination, &tailByDestination, newDestination, newDate, newFare);
        }
        else // break from loop
        {
            collectionLoop = 0;
        }
    }

    // THERE ARE HERE TO SPEED UP TESTING OF CODE, UNCOMMENT TO ADD 5 FLIGHTS TO LIST IN ADDITION TO USER INPUT
    //insertDualSorted(&headByFare, &tailByFare, &headByDestination, &tailByDestination, "Kitchener\0", "20022026\0", 356.67);
    //insertDualSorted(&headByFare, &tailByFare, &headByDestination, &tailByDestination, "Bancroft\0", "16012026\0", 350.00);
    //insertDualSorted(&headByFare, &tailByFare, &headByDestination, &tailByDestination, "Ottawa\0", "01212026\0", 246.93);
    //insertDualSorted(&headByFare, &tailByFare, &headByDestination, &tailByDestination, "Toronto\0", "01272027\0", 496.67);
    //insertDualSorted(&headByFare, &tailByFare, &headByDestination, &tailByDestination, "Quebec\0", "05232027\0", 160.67);

    printSortedFare(headByFare);
    printf("\n");
    printSortedDestination(headByDestination);

    printf("Enter distination to search: ");
    nullTerminate(newDestination, sizeof(newDestination));
    printf("Enter date to search: ");
    nullTerminate(newDate, sizeof(newDate));
    if (findFlight(headByDestination, newDestination, newDate) != NULL) // found a matching flight
    {
        mutateLists(&headByFare, &tailByFare, &headByDestination, &tailByDestination, findFlight(headByDestination, newDestination, newDate));
    }
    
    printSortedFare(headByFare);
    printf("\n");
    printSortedDestination(headByDestination);

    clearLists(&headByDestination);
}

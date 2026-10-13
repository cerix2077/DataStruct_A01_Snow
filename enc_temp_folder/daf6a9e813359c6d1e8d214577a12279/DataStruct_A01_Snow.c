/*
 * FILE             :Assignment 1
 * PROGRAMMER       : Cameron Snow
 * FIRST VERSION    : 2026-10-10
 * DESCRIPTION      :
 *      This program promts the user for inupt before constructing 
 *          2 doubly linkd lists sorted by destination and fare respectivly,
 *          prints out the list sorted by fare  then destination, askes user for 
 *          a destination and date pair to change the fare of then redisplaying the lists
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

    //
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

        currentByDestination->PreviousFlightByDestination->NextFlightByDestination = newFlight; // im not writing this one in english
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
    if (fgets(buffer, bufferSize, stdin) == NULL)
    {
        buffer[0] = '\0';
    }

    char* newLine = strchr(buffer, '\n');
    if (newLine != NULL)
        {
        *newLine = '\0';
        }
    else
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
*   struct FlightInfo* head :
* RETURNS      :
*   
*/
void printSortedFare(struct FlightInfo* head)
{
    printf("\nDEBUG BY FARE\n");
    struct FlightInfo* current = head;
    while (current != NULL)
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
*   
*/
void printSortedDestination(struct FlightInfo* head)
{
    printf("\nDEBUG BY DEST\n");
    struct FlightInfo* current = head;
    while (current != NULL)
    {
        printf("Destination: %s, Date: %s, Fare: $%.2f\n", current->Destination, current->Date, current->Fare);
        current = current->NextFlightByDestination;
    }
}

/*
* METHOD       : findFlight
* DESCRIPTION  :
*
* PARAMETERS   :
*
* RETURNS      :
*
*/
struct FlightInfo* findFlight(struct FlightInfo* head, char* destination, char* date)
{
    while (head != NULL && (strcmp(head->Destination, destination) != 0 && strcmp(head->Date, date) != 0))
    {
        printf("not this fella\n");
    }
    printf("out\n");
}

/*
* METHOD       : deleteflight
* DESCRIPTION  :
*
* PARAMETERS   :
*
* RETURNS      :
*
*/
void deleteflight()
{

}

int main()
{

    // init heads and tails for fare and destination sorted lists
    struct FlightInfo* headByDestination = NULL;
    struct FlightInfo* tailByDestination = NULL;

    struct FlightInfo* headByFare = NULL;
    struct FlightInfo* tailByFare = NULL;

    char newDestination[15];
    char newDate[9];
    char newFareString[10]; //should hold fares up to 999999.99\0
    double newFare;
    int collectionLoop = 1;


    while (collectionLoop == 1)
    {
        printf("Enter destination:");
        nullTerminate(newDestination, sizeof(newDestination));

        
        printf("Enter date:");
        nullTerminate(newDate, sizeof(newDate));

        
        printf("Enter fare:");
        nullTerminate(newFareString, sizeof(newFareString));


        printf("DEBUG: %s, %s, %s\n", newDestination, newDate, newFareString);

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

    insertDualSorted(&headByFare, &tailByFare, &headByDestination, &tailByDestination, "Kitchener\0", "10212026\0", 356.67);
    insertDualSorted(&headByFare, &tailByFare, &headByDestination, &tailByDestination, "Bancroft\0", "10212026\0", 350.00);
    insertDualSorted(&headByFare, &tailByFare, &headByDestination, &tailByDestination, "Ottowa\0", "10212026\0", 246.93);
    insertDualSorted(&headByFare, &tailByFare, &headByDestination, &tailByDestination, "Toronto\0", "10212026\0", 496.67);
    insertDualSorted(&headByFare, &tailByFare, &headByDestination, &tailByDestination, "Quebec\0", "10212026\0", 160.67);

    printSortedFare(headByFare);

    printSortedDestination(headByDestination);

    findFlight(headByDestination, newDestination, newDate);
}

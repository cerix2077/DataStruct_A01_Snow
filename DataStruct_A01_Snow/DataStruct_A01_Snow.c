
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

void insertFareSorted(struct FlightInfo** head, struct FlightInfo** tail, char* destination, char* date, double fare)
{
    struct FlightInfo* newFlight = createNewFlight(destination, date, fare);

    // Empty list, newFlight is both head and tail
    if (*head == NULL)
    {
        *tail = newFlight;
        *head = newFlight;
        return;
    }

    // new fare is smaller than heads fare, make new head
    if (fare <= (*head)->Fare)
    {
        newFlight->NextFlightByFare = *head; // new head links old head as next
        (*head)->PreviousFlightByFare = newFlight; //old head links new head as prev
        *head = newFlight; // newFlight is now head
        return;
    }

    // new fare is larger than tails fare, make new tail
    if (fare >= (*tail)->Fare)
    {
        newFlight->PreviousFlightByFare = *tail; // new tail links old tail as prev
        newFlight->NextFlightByFare = NULL; // this flight is the end of the list 
        (*tail)->NextFlightByFare = newFlight; // old tail links new tail as next
        *tail = newFlight; // new flight is now tail
        return;
    }

    // newFlight was not smallest or largest in list, 
    // make current struct to navigate though list
    struct FlightInfo* current = (*head)->NextFlightByFare; // head was already compared, start at next

    // while the currently checked flight is not null and currents fare is less than the new fare
    while (current != NULL && current->Fare < fare)
    {
        current = current->NextFlightByFare; // step through list
    }

    newFlight->NextFlightByFare = current; // newFlights next is now current
    newFlight->PreviousFlightByFare = current->PreviousFlightByFare; // newFlights prev is now currents prev

    //current->NextFlightByFare = newFlight; // does next flight need to be updated if we are inserting before?
    current->PreviousFlightByFare = newFlight; // current links newFlight as previous
}

void insertDestinationSorted(struct FlightInfo** head, struct FlightInfo** tail, char* destination, char* date, double fare)
{
    struct FlightInfo* newFlight = createNewFlight(destination, date, fare);

    // Empty list, will be both head and tail
    if (*head == NULL)
    {
        *tail = newFlight;
        *head = newFlight;
        return;
    }

    // if destinations are identical or newFlights destination has a smaller value character in its first diff
    if (strcmp(newFlight->Destination, (*head)->Destination) <= 0)
    {
        newFlight->NextFlightByDestination = *head; // newFlight links next to current head
        (*head)->PreviousFlightByDestination = newFlight; // current head links prev to newFlight
        *head = newFlight; // newflight is now head 
        return;
    }

    // if new destination compares as after tail destination
    if (strcmp(newFlight->Destination, (*tail)->Destination) > 0)
    {
        newFlight->PreviousFlightByDestination = tail;
        newFlight->NextFlightByDestination = NULL;
        (*tail)->NextFlightByDestination = newFlight;
        *tail = newFlight;
        return;
    }

    struct FlightInfo* current = (*head)->NextFlightByDestination;

    // 
    while (current->NextFlightByDestination != NULL && strcmp(newFlight->Destination, current->Destination) > 0)
    {
        current = current->NextFlightByDestination;
    }

    newFlight->NextFlightByFare = current->NextFlightByDestination; // newFlights next is now current
    newFlight->PreviousFlightByFare = current; // newFlights prev is now currents prev

    //current->NextFlightByFare = newFlight; // does next flight need to be updated if we are inserting before?
    current->PreviousFlightByFare = newFlight; // current links newFlight as previous

}

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

    //current->NextFlightByFare = newFlight; // does next flight need to be updated if we are inserting before?
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
        newFlight->PreviousFlightByDestination = tailByDestination;
        newFlight->NextFlightByDestination = NULL;
        (*tailByDestination)->NextFlightByDestination = newFlight;
        *tailByDestination = newFlight;
    }
    else
    {
    struct FlightInfo* currentByDestination = (*headByDestination)->NextFlightByDestination;

    // 
    while (currentByDestination->NextFlightByDestination != NULL && strcmp(destination, currentByDestination->Destination) > 0)
    {
        currentByDestination = currentByDestination->NextFlightByDestination;
    }

    newFlight->NextFlightByDestination = currentByDestination->NextFlightByDestination; // newFlights next is now current
    newFlight->PreviousFlightByDestination = currentByDestination; // newFlights prev is now currents prev

    //current->NextFlightByFare = newFlight; // does next flight need to be updated if we are inserting before?
    currentByDestination->PreviousFlightByDestination = newFlight; // current links newFlight as previous
    }

}

void printSortedFare(struct FlightInfo* head)
{
    struct FlightInfo* current = head;
    while (current != NULL)
    {
        printf("DEBUG BY FARE\n");
        printf("Destination: %s, Date: %s, Fare: $%.2f\n", current->Destination, current->Date, current->Fare);
        current = current->NextFlightByFare;
    }
}

void printSortedDestination(struct FlightInfo* head)
{
    struct FlightInfo* current = head;
    while (current != NULL)
    {
        printf("DEBUG BY DEST\n");
        printf("Destination: %s, Date: %s, Fare: $%.2f\n", current->Destination, current->Date, current->Fare);
        current = current->NextFlightByDestination;
    }
}

struct FlightInfo* findFlight(struct FlightInfo* head)
{

}

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

    //insertFareSorted(headByFare, tailByFare, "Kitchener\0", "10212026\0", 356.67);
    //insertFareSorted(headByFare, tailByFare, "Ottowa\0", "10212026\0", 246.93);
    //insertFareSorted(headByFare, tailByFare, "Bancroft\0", "10212026\0", 350.00);
    //insertFareSorted(headByFare, tailByFare, "Toronto\0", "10212026\0", 496.67);
    //insertFareSorted(headByFare, tailByFare, "Quebec\0", "10212026\0", 160.67);

    insertDualSorted(&headByFare, &tailByFare, &headByDestination, &tailByDestination, "Kitchener\0", "10212026\0", 356.67);
    insertDualSorted(&headByFare, &tailByFare, &headByDestination, &tailByDestination, "Bancroft\0", "10212026\0", 350.00);
    insertDualSorted(&headByFare, &tailByFare, &headByDestination, &tailByDestination, "Ottowa\0", "10212026\0", 246.93);
    insertDualSorted(&headByFare, &tailByFare, &headByDestination, &tailByDestination, "Toronto\0", "10212026\0", 496.67);
    insertDualSorted(&headByFare, &tailByFare, &headByDestination, &tailByDestination, "Quebec\0", "10212026\0", 160.67);

    printSortedFare(headByFare);

    printSortedDestination(headByDestination);
}

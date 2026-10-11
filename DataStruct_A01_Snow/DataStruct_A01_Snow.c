
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct FlightInfo
{
    char Destination[15];
    char Date[9];
    float Fare;

    // Fare sorted odubly linked list
    struct FlightInfo* PreviousFlightByFare ;
    struct FlightInfo* NextFlightByFare;

    // Destination sorted doubly linked list
    struct FlightInfo* PreviousFlightByDestination;
    struct FlightInfo* NextFlightByDestination;
};

struct FlightInfo* CreateNewFlight(char* destination, char* date, float fare)
{
    struct FlightInfo* newFlight = (struct FlightInfo*)malloc(sizeof(struct FlightInfo));

    if (newFlight == NULL)
    {
        exit(EXIT_FAILURE);
    }
    strcpy(newFlight->Destination, destination);
    strcpy(newFlight->Date, date);
    newFlight->Fare = fare;
    return newFlight;
}

void insertFareSorted(struct FlightInfo** head, struct FlightInfo** tail, char* destination, char* date, float fare)
{
    struct FlightInfo* newFlight = CreateNewFlight(destination, date, fare);

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
        (*tail)->NextFlightByFare = newFlight; // old tail links new tail as next
        *tail = newFlight; // new flight is now tail
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

void insertDestinationSorted(struct FlightInfo** head, struct FlightInfo** tail, char* destination, char* date, float fare)
{
    struct FlightInfo* newFlight = CreateNewFlight(destination, date, fare);

    // Empty list, will be both head and tail
    if (*head == NULL)
    {
        *tail = newFlight;
        *head = newFlight;
        return;
    }
}

void printSortedFare(struct FlightInfo* head)
{
    struct FlightInfo* current = head;
    while (current != NULL)
    {
        printf("infoDisplay\n");
        current = current->NextFlightByFare;
    }
}

void printSortedDestination(struct FlightInfo* head)
{
    struct FlightInfo* current = head;
    while (current != NULL)
    {
        printf("infoDisplay\n");
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
    struct FlightInfo* headByDestination = NULL;
    // struct FlightInfo* tailByDestination = NULL;

    struct FlightInfo* headByFare = NULL;
    // struct FlightInfo* tailByFare = NULL;
}


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

struct FlightInfo* CreateNewFlight(char* destination, char* date, double fare)
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

void insertFareSorted(struct FlightInfo** head, struct FlightInfo** tail, char* destination, char* date, double fare)
{
    struct FlightInfo* newFlight = CreateNewFlight(destination, date, fare);

    // Empty list, will be both head and tail
    if (*head == NULL)
    {
        *tail = newFlight;
        *head = newFlight;
    }
}

void insertDestinationSorted(struct FlightInfo** head, struct FlightInfo** tail, char* destination, char* date, double fare)
{
    struct FlightInfo* newFlight = CreateNewFlight(destination, date, fare);
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

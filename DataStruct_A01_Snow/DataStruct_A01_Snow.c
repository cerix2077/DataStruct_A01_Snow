
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

int main()
{
    struct FlightInfo* headByDestination = NULL;
    struct FlightInfo* tailByDestination = NULL;

    struct FlightInfo* headByFare = NULL;
    struct FlightInfo* tailByFare = NULL;
}


#include <stdio.h>

struct FlightInfo
{
    char destination[15];
    char date[9];
    float fare;
    struct FlightInfo* previousFlight ;
    struct FlightInfo* nextFlight;
};



int main()
{
    
}

// Implementation of the Flight DB ADT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FlightDb.h"
#include "List.h"
#include "Tree.h"

struct flightDb {
    Tree byFlightNum;
    Tree byDeparture;
    Tree byDay;
    //Tree byNextFlight;
};

// Helper functions
int compareByFlightNum(Record r1, Record r2);
int compareByAirport(Record r1, Record r2);
int compareByDay(Record r1, Record r2);

FlightDb DbNew(void) {
    FlightDb db = malloc(sizeof(*db));
    if (db == NULL)
    {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    db->byFlightNum = TreeNew(compareByFlightNum);
    db->byDeparture = TreeNew(compareByAirport);
    db->byDay = TreeNew(compareByDay);
    //db->byNextFlight = TreeNew(compareByAirport);
    return db;
    
}

void DbFree(FlightDb db) {
    TreeFree(db->byFlightNum, false);
    TreeFree(db->byDeparture, false);
    TreeFree(db->byDay, true);
    free(db);
}

bool DbInsertRecord(FlightDb db, Record r) {
    if(TreeInsert(db->byDeparture, r)) {
        TreeInsert(db->byFlightNum, r);
        TreeInsert(db->byDay, r);
        return true;
    }
    else {
        return false;
    }  
       
}

// Returns a list of records with the given flight number, in increasing order
// (day, hour, minute) of departure.
List DbFindByFlightNumber(FlightDb db, char *flightNumber) {
    
    Record dummy_lower = RecordNew(flightNumber, "", "", 0, 0, 0, 0);
    Record dummy_upper = RecordNew(flightNumber, "", "", 6, 23, 59, 0);

    // Add all records with the same flight number to the list in increasing order
    List l = TreeSearchBetween(db->byFlightNum, dummy_lower, dummy_upper);
    RecordFree(dummy_lower);
    RecordFree(dummy_upper);
 
    return l;
}

List DbFindByDepartureAirportDay(FlightDb db, char *departureAirport,
                                 int day) {
    Record dummy_lower = RecordNew("", departureAirport, "", day, 0, 0, 0);
    Record dummy_upper = RecordNew("", departureAirport, "", day, 23, 59, 0);

    List l = TreeSearchBetween(db->byDeparture, dummy_lower, dummy_upper);
    RecordFree(dummy_lower);
    RecordFree(dummy_upper);

    return l;
}

List DbFindBetweenTimes(FlightDb db, 
                        int day1, int hour1, int min1, 
                        int day2, int hour2, int min2) {
    

    Record dummy_lower = RecordNew("", "", "", day1, hour1, min1, 0);
    Record dummy_upper = RecordNew("", "", "", day2, hour2, min2, 0);
    
    List l = TreeSearchBetween(db->byDay, dummy_lower, dummy_upper);
    RecordFree(dummy_lower);
    RecordFree(dummy_upper);

    return l;
}

Record DbFindNextFlight(FlightDb db, char *flightNumber, 
                        int day, int hour, int min) {
    Record dummy_lower = RecordNew(flightNumber, "", "", day, hour, min, 0);
    Record r = TreeNext(db->byFlightNum, dummy_lower);

    RecordFree(dummy_lower);
    return r;
    
}


// HELPER FUNCTIONS

// Order by flight number, then by departure time
int compareByFlightNum(Record r1, Record r2) {
    int cmp = strcmp(RecordGetFlightNumber(r1), RecordGetFlightNumber(r2));
    if (cmp == 0) {
        int day = RecordGetDepartureDay(r1) - RecordGetDepartureDay(r2);
        if (day == 0) {
            int hour = RecordGetDepartureHour(r1) - RecordGetDepartureHour(r2);
            if (hour == 0) {
                return RecordGetDepartureMinute(r1) - RecordGetDepartureMinute(r2);
            } else {
                return hour;
            }
        } else {
            return day;
        }
    }
    return cmp;
}

// Order by departure airport, then day, then hour, then flight number
int compareByAirport(Record r1, Record r2) {
    int airportCmp = strcmp(RecordGetDepartureAirport(r1), 
                    RecordGetDepartureAirport(r2));
    int day = RecordGetDepartureDay(r1) - RecordGetDepartureDay(r2);
    int hour = RecordGetDepartureHour(r1) - RecordGetDepartureHour(r2);
    int flightCmp = strcmp(RecordGetFlightNumber(r1), RecordGetFlightNumber(r2));
    
    if (airportCmp == 0)
    {
        if (day == 0)
        {
            if (hour == 0)
                return flightCmp;
            else
                return hour;
        } 
        else
            return day;
    }
    else
        return airportCmp;
}


// Order by day, then hour, then minute, then flight number. Day 2 can be 
// later than day 1. Day 1 should come before day 2.
int compareByDay(Record r1, Record r2) {
    int day = RecordGetDepartureDay(r1) - RecordGetDepartureDay(r2);
    int hour = RecordGetDepartureHour(r1) - RecordGetDepartureHour(r2);
    int minute = RecordGetDepartureMinute(r1) - RecordGetDepartureMinute(r2);
    int flightCmp = strcmp(RecordGetFlightNumber(r1), RecordGetFlightNumber(r2));
    
    if (day == 0)
    {
        if (hour == 0)
        {
            if (minute == 0)
                return flightCmp;
            else
                return minute;
        } 
        else
            return hour;
    }
    else
        return day;
}



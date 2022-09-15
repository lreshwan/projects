#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool isSafe(DailySchedule& sched, const AvailabilityMatrix& avail, int row, int col, int id);
bool canWork(DailySchedule& sched, int id, int maxHours);
bool findEmptyShift(DailySchedule& sched, int& row, int& col);
bool scheduleHelper(DailySchedule& schedule, const AvailabilityMatrix& availability, int maxShifts);
// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    //creating and filling empty schedule vector
    vector<Worker_T> emptyVec;
    for(size_t i = 0; i < avail.size(); i++){
        sched.push_back(emptyVec);
    }

    for(size_t i = 0; i < avail.size(); i++){
        for(size_t j = 0; j < dailyNeed; j++){
            sched[i].push_back(-1);
        }
    }
    

    return scheduleHelper(sched, avail, maxShifts);

}

//helper function to check if it is safe to place a worker in that location
bool isSafe(DailySchedule& sched, const AvailabilityMatrix& avail, int row, int col, int id, int maxHours){
    if(avail[row][id]){
        return canWork(sched, id, maxHours);
    }
    else{
        return false;
    }
}

//helper function to check if an individual is availiable to work that day based on the availability matrix
bool canWork(DailySchedule& sched, int id, int maxHours){
    int hours = 0;
    for(size_t i = 0; i < sched.size(); i++){
        for(size_t j = 0; j < sched[0].size(); j++){
            if ((int)sched[i][j] == id)
            {
               hours++; 
            } 
        }
    }
    if(hours >= maxHours){
        return false;
    }
    else{
        return true;
    }
}

//finds next empty shift in the work schedule to place an available worker into
bool findEmptyShift(DailySchedule& sched, int& row, int& col){
    for(row = 0; row < (int)sched.size(); row++){
        for(col = 0; col < (int)sched[row].size(); col++){
            if(sched[row][col] == INVALID_ID){
                return true;
            }
        }
    }
    return false;
}

//main driver recursion function, does the back tracking search
bool scheduleHelper(DailySchedule& schedule, const AvailabilityMatrix& availability, int maxHours){
    int row, col;
    if(!findEmptyShift(schedule, row, col)){
        return true;
    }
    for(size_t i = 0; i < availability[0].size(); i++){
        if(isSafe(schedule, availability, row, col, i, maxHours)){
            schedule[row][col] = i;
            if(scheduleHelper(schedule, availability, maxHours)){
                return true;
            }
            schedule[row][col] = INVALID_ID;
        }
    }
    return false;
  
}


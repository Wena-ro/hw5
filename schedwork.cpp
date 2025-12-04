#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheHelper(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<vector<bool>>& isUsed,
    vector<size_t>& currNum, 
    size_t day, 
    size_t slot);


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

    // initialization 
    size_t ndays = avail.size();
    size_t kworkers = avail[0].size();
    sched = DailySchedule(ndays, std::vector<Worker_T> (dailyNeed));


    // check avaliability of current worker
    vector<vector<bool>> isUsed(ndays, vector<bool>(kworkers, false));


    // check if the worker meet max maxShifts
    // if currNum < maxShift, continue
    vector<size_t> currNum(kworkers, 0);




    // recurrsion function call
    return scheHelper(avail, dailyNeed, maxShifts, sched, isUsed, currNum, 0, 0);
}



bool scheHelper(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<vector<bool>>& isUsed,
    vector<size_t>& currNum, 
    size_t day, 
    size_t slot)
    {

        // Base case, where everything is fulfilled
        if(day == avail.size()){
            return true;
        }

        size_t nextDay = day;
        size_t nextSlot = slot + 1;

        if(nextSlot == dailyNeed){
            nextDay = day + 1;
            nextSlot = 0;
        }

        size_t kworkers = avail[0].size();

        for(Worker_T w = 0; w < kworkers; w++){
            if(avail[day][w] == 1){
                if(currNum[w] < maxShifts){
                    if(isUsed[day][w] == false){


                        sched[day][slot] = w;
                        currNum[w]++;
                        isUsed[day][w] = true;


                        if(scheHelper(avail, dailyNeed, maxShifts, sched, isUsed, currNum, nextDay, nextSlot)){
                            return true;
                        }


                        isUsed[day][w] = false;
                        currNum[w]--;
                    }
                }
            }

        }

        return false;

    }
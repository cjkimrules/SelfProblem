#ifndef TIME_SLOT
#define TIME_SLOT

#include <string>
#include <vector>
#include "Time.h"

using namespace std;

// This class will store a time slot like following:
// 12:00 - 15:30
// StartHour: 12
// StartMinute: 0
// EndHour: 15
// EndMinute: 30
class TimeSlot{
    Time startTime;
    Time endTime;

public:
    TimeSlot(int sh, int sm, int eh, int em);
    TimeSlot(Time const& start, Time const& end);
    TimeSlot(string startTime, string endTime);
    Time GetStartTime() const;
    Time GetEndTime() const;
    string PrintStartTime() const;
    string PrintEndTime() const;
    int DurationInMinutes();
};

TimeSlot* MergeTimeSlots(TimeSlot const& a, TimeSlot const& b);

#endif
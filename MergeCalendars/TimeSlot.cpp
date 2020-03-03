#include <string>
#include <vector>
#include <algorithm>
#include "TimeSlot.h"
#include "Time.h"

using namespace std;


vector<string> ParseString(string input, string delimiter){
    vector<string> output;
    
    int pos = 0;
    string token;
    while((pos = input.find(delimiter)) != string::npos){
        token = input.substr(0, pos);
        output.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    output.push_back(input);

    return output;
}

// Parse time into two integers by delimiter ":"
TimeSlot::TimeSlot(string startTime, string endTime){
    vector<string> start = ParseString(startTime, ":");
    vector<string> end = ParseString(endTime, ":");
    this->startTime.SetTime(stoi(start[0]), stoi(start[1]));
    this->endTime.SetTime(stoi(end[0]), stoi(end[1]));
}

TimeSlot::TimeSlot(int sh, int sm, int eh, int em){
    this->startTime.SetTime(sh, sm);
    this->endTime.SetTime(eh, em);
}

TimeSlot::TimeSlot(Time const& start, Time const& end){
    this->startTime.SetTime(start.GetHour(), start.GetMinute());
    this->endTime.SetTime(end.GetHour(), end.GetMinute());
}

Time TimeSlot::GetStartTime() const { return this->startTime; }
Time TimeSlot::GetEndTime() const { return this->endTime; }

string ConvertTimeToString(int h, int m){
    if(m < 10){
        return to_string(h) + ":0" + to_string(m); // 9:00, 16:00
    }else{
        return to_string(h) + ":" + to_string(m); // 9:15, 13:59
    }
}
string TimeSlot::PrintStartTime() const { return ConvertTimeToString(this->startTime.GetHour(), this->startTime.GetMinute()); }
string TimeSlot::PrintEndTime() const { return ConvertTimeToString(this->endTime.GetHour(), this->endTime.GetMinute()); }

// See if there is mergeable time between "this" and "other" time slots.
// If none is available, then return null.
TimeSlot* MergeTimeSlots(TimeSlot const& a, TimeSlot const& b) {
    // 1. Compare both start times, pick the one that's later time.
    Time StartTime = GetMaxTime(a.GetStartTime(), b.GetStartTime());
    Time EndTime = GetMinTime(a.GetEndTime(), b.GetEndTime());

    // 2. If EndTime is earlier than or equal to StartTime, we know we had no time merged properly.
    // ex) [13:00, 15:00], [16:00, 17:00], we will get [16:00, 15:00], which we can tell
    //      there was no compromised time.
    if(EndTime <= StartTime){
        return nullptr;
    }

    return new TimeSlot(StartTime, EndTime);
}


int TimeSlot::DurationInMinutes(){
    Time duration = this->endTime - this->startTime;
    return duration.GetHour() * 60 + duration.GetMinute();
}
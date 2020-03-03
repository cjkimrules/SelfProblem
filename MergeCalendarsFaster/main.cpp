/******************************************************************************
Author: CJ Kim
Date: 3/2/2020
Title: Merge Calendars Faster
Explain: Imagine two people want to find a good time to have a meeting.
         They would like to find that good time slot by comparing both people's
         calendars.

         Given a list of lists of strings.
         List #1 : Person A's occupied time slots.
         List #2 : Person A's perferred time range. (Daily Bounds)
         List #3 : Person B's occupied time slots.
         List #4 : Person B's preferred time range. (Daily Bounds)
         List #5 : Time (in minutes) alotted for meeting.

         Time will be written in string in this format: "14:30"
         Time is also in military time.

         Input: [[9:00, 10:30], [12:00, 13:00], [16:00, 1800]]
                [9:00, 20:00]
                [[10:00, 11:30], [12:30, 14:30], [14:30, 15:00], [16:00, 17:00]]
                [10:00, 18:30]
                30
         Output: [[11:30, 12:00], [15:00, 16:00], [18:00, 18:30]]
*******************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include "TimeSlot.h"

using namespace std;

/*
 * Time Complexity is (Number of Schedules of Person A) + (Number of Schedules of Person B)
 *
 * The reason that there could've been an upgrade is that we are not merging at all.
 * I was too stuck to the concept of "Merging Free Time Slots".
 * All we had to do was combine occupied time slots together in sorted manner and flip them
 * within the Daily Bounds.
 */

vector<TimeSlot>* CombineSorted(vector<TimeSlot>& a, vector<TimeSlot>& b){
    vector<TimeSlot>* Combined = new vector<TimeSlot>();

    int Pointer_A = 0;
    int Pointer_B = 0;
    while(Pointer_A < a.size() && Pointer_B < b.size()){
        if(a[Pointer_A].GetStartTime() < b[Pointer_B].GetStartTime()){
            Combined->emplace_back(a[Pointer_A]);
            Pointer_A ++;
        }else{
            Combined->emplace_back(b[Pointer_B]);
            Pointer_B ++;
        }
    }
    // Put the rest that may have not been added because one array was emptied out first.
    for(int i = Pointer_A; i < a.size(); i ++){
        Combined->emplace_back(a[Pointer_A]);
    }
    for(int i = Pointer_B; i < b.size(); i ++){
        Combined->emplace_back(b[Pointer_B]);
    }

    return Combined;
}

// There will be time slots where end time overlaps with other time slot.
// Combine properly and finalize all time slots.
void ArrangeSortedTimeSlots(vector<TimeSlot>* combined){
    // NOT FINISHED
}

bool TimeFitsInBound(Time start, Time end, int TimeInMinutes){
    if((end - start) >= Time(TimeInMinutes / 60, TimeInMinutes % 60)){
        return true;
    }
    return false;
}

// Using Daily Bounds and Occupied Slots, find all the Available Time Slots.
vector<TimeSlot>* FindAvailSlots(vector<TimeSlot> const* OccupiedSlots, TimeSlot const* DailyBound, const int MinTime){
    vector<TimeSlot>* AvailSlots = new vector<TimeSlot>();
    
    // Check if there is available time between Daily Bound and first schedule.
    // In case there may be no schedule for person A.
    if(OccupiedSlots->size() > 0){
        // Time between DailyBound and First Schedule's Starting Time.
        if(DailyBound->GetStartTime() < OccupiedSlots->at(0).GetStartTime()){
            if(TimeFitsInBound(DailyBound->GetStartTime(), OccupiedSlots->at(0).GetStartTime(), MinTime)){
                AvailSlots->push_back(TimeSlot(DailyBound->GetStartTime(), OccupiedSlots->at(0).GetStartTime()));
            }
        }

        // All Time Slots in between will be handled only with Occupied Slots, because we know
        // these times are within the bounds of our preferred time (inside Daily Boundary).
        // We need 2 Occupied Slots to create an available slot in between, so we have one less to loop through.
        for(int i = 0; i < OccupiedSlots->size() - 1; i ++){
            // If occupied slots are back to back which means if there is a schedule right after another,
            // we do not add 0 minutes as Available.
            if(OccupiedSlots->at(i + 1).GetStartTime() > OccupiedSlots->at(i).GetEndTime()){
                if(TimeFitsInBound(OccupiedSlots->at(i).GetEndTime(), OccupiedSlots->at(i + 1).GetStartTime(), MinTime)){
                    AvailSlots->push_back(TimeSlot(OccupiedSlots->at(i).GetEndTime(), OccupiedSlots->at(i + 1).GetStartTime()));
                }

            }
        }

        // Time between DailyBound and Last Schedule's Ending Time.
        if(DailyBound->GetEndTime() > OccupiedSlots->at(OccupiedSlots->size() - 1).GetEndTime()){
            if(TimeFitsInBound(OccupiedSlots->at(OccupiedSlots->size() - 1).GetEndTime(), DailyBound->GetEndTime(), MinTime)){
                AvailSlots->push_back(TimeSlot(OccupiedSlots->at(OccupiedSlots->size() - 1).GetEndTime(), DailyBound->GetEndTime()));
            }
        }
    }else{
        // If there was no occupied slots, which means person A has no schedule for this day.
        // That means the Daily Bounds (preferred time) will be all available.
        AvailSlots->push_back(TimeSlot(DailyBound->GetStartTime(), DailyBound->GetEndTime()));
    }

    return AvailSlots;
}

vector<string>* MergeCalendars(vector<vector<string>>& Calendars){
    // First we will find all the available time slots for both people.
    // Right now, the time slots given are "occupied" time slots, not available ones.
    // We will convert them using "Daily Bounds"

    // Get all the occupied time slots for both A and B for easier calculations.
    vector<TimeSlot> OccupiedSlots_A, OccupiedSlots_B;
    // Odd index is starting time. Even index is ending time.
    for(int i = 0; i < Calendars[0].size() / 2; i ++){
        OccupiedSlots_A.emplace_back(TimeSlot(Calendars[0][2 * i], Calendars[0][2 * i + 1]));
    }
    for(int i = 0; i < Calendars[2].size() / 2; i ++){
        OccupiedSlots_B.emplace_back(TimeSlot(Calendars[2][2 * i], Calendars[2][2 * i + 1]));
    }
    
    // Combine two occupied slots in sorted order by StartTime.
    vector<TimeSlot>* OccupiedSlot = CombineSorted(OccupiedSlots_A, OccupiedSlots_B);
    // If there are any overlappings between neighboring time slots, then merge them.
    ArrangeSortedTimeSlots(OccupiedSlot);

    // Have one DailyBound where both people are satisfied.
    TimeSlot DailyBound_A(Calendars[1][0], Calendars[1][1]);
    TimeSlot DailyBound_B(Calendars[3][0], Calendars[3][1]);
    TimeSlot* DailyBound = MergeTimeSlots(DailyBound_A, DailyBound_B);

    // Depending on the required minimum time, merge two Time Slots.
    int MinTime = stoi(Calendars[4][0]);
    vector<TimeSlot>* CompromisedSlots = FindAvailSlots(OccupiedSlot, DailyBound, MinTime);

    delete OccupiedSlot;
    delete DailyBound;

    // Compose a list of strings to output.
    vector<string>* CompromisedStrings = new vector<string>();
    for(int i = 0; i < CompromisedSlots->size(); i ++){
        CompromisedStrings->push_back(CompromisedSlots->at(i).PrintStartTime());
        CompromisedStrings->push_back(CompromisedSlots->at(i).PrintEndTime());
    }
    delete CompromisedSlots;

    return CompromisedStrings;
}



bool CompareVectors(vector<string> const& a, vector<string> const& b){
    if(a.size() != b.size()) return false;

    for(int i = 0; i < a.size(); i ++){
        if(a[i] != b[i]) return false;
    }
    return true;
}

void Tester(const int TestNum, const string Memo, vector<vector<string>> input, vector<string> const& output){
    cout << "#" << TestNum << " " << Memo << "            ";
    vector<string>* result = MergeCalendars(input);
    if(CompareVectors(*result, output)){
        cout << "Passed" << endl;
    }else{
        cout << "Failed" << endl;
    }
    delete result;
}

int main(){
    vector<vector<string>> input;
    input.push_back(vector<string>{"9:00", "10:30", "12:00", "13:00", "16:00", "18:00"});
    input.push_back(vector<string>{"9:00", "20:00"});
    input.push_back(vector<string>{"10:00", "11:30", "12:30", "14:30", "14:30", "15:00", "16:00", "17:00"});
    input.push_back(vector<string>{"10:00", "18:30"});
    input.push_back(vector<string>{"30"});

    Tester(1, "No Early or Late", input, vector<string>{"11:30", "12:00", "15:00", "16:00", "18:00", "18:30"});
    
    input.clear();
    input.push_back(vector<string>{"9:00", "10:30", "12:00", "13:00", "16:00", "18:00"});
    input.push_back(vector<string>{"9:00", "20:00"});
    input.push_back(vector<string>{"10:00", "11:30", "12:30", "14:30", "14:30", "15:00", "16:00", "17:00"});
    input.push_back(vector<string>{"10:00", "18:30"});
    input.push_back(vector<string>{"60"});

    Tester(2, "Increase MinTime", input, vector<string>{"15:00", "16:00"});
    
    input.clear();
    input.push_back(vector<string>{"9:00", "10:30", "12:00", "13:00", "16:00", "18:00"});
    input.push_back(vector<string>{"7:00", "20:00"});
    input.push_back(vector<string>{"10:00", "11:30", "12:30", "14:30", "14:30", "15:00", "16:00", "17:00"});
    input.push_back(vector<string>{"8:00", "18:30"});
    input.push_back(vector<string>{"30"});

    Tester(3, "Early or Late", input, vector<string>{"8:00", "9:00", "11:30", "12:00", "15:00", "16:00", "18:00", "18:30"});
}
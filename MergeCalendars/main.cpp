/******************************************************************************
Author: CJ Kim
Date: 3/2/2020
Title: Merge Calendars
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

// Time Complexity is (Number of Schedules of Person A) * (Number of Schedules of Person B)
//
// Time Complexity cannot be A * Log(B), using binary search to find the appropriate time slot to merge.
// Because, this is not a one-to-one merge. This is not, I found the time slot and that is it.
// Person A: [9:00, 15:00]
// Person B: [10:00, 11:00], [13:00, 14:30]
// MinTime : 30 minutes
// Output  : [10:00, 11:00], [13:00, 14:30]
// Like this example, one time slot can "merge" with multiple of other's time slots.
// Techincally, this is one-to-all merge. That's why we have to loop through every other slots for each slot.
//
// Now you may wonder what if I delete the ones that were used for merging. Then it could be A + B time.
// This is also not possible, because consider this example now.
// Person A: [10:00, 13:00], [14:00, 16:30]
// Person B: [12:00, 15:00]
// MinTime : 30 minutes
// Output  : [12:00, 13:00], [14:00, 15:00]
// If we were to "remove" the time slot because we used it to merge, then after merging
// [10:00, 13:00] and [12:00, 15:00] into [12:00, 13:00], [12:00, 15:00] will be removed.
// But we may still need it for the next time slot, [14:00, 16:30]. In fact, we do.
// So we can't delete the time slot after merging either.

// Using Daily Bounds and Occupied Slots, find all the Available Time Slots.
vector<TimeSlot>* FindAvailSlots(TimeSlot const& DailyBound, vector<TimeSlot> const& OccupiedSlots){
    vector<TimeSlot>* AvailSlots = new vector<TimeSlot>();
    
    // Check if there is available time between Daily Bound and first schedule.
    // In case there may be no schedule for person A.
    if(OccupiedSlots.size() > 0){
        // Time between DailyBound and First Schedule's Starting Time.
        if(DailyBound.GetStartTime() < OccupiedSlots[0].GetStartTime()){
            AvailSlots->push_back(TimeSlot(DailyBound.GetStartTime(), OccupiedSlots[0].GetStartTime()));
        }

        // All Time Slots in between will be handled only with Occupied Slots, because we know
        // these times are within the bounds of our preferred time (inside Daily Boundary).
        // We need 2 Occupied Slots to create an available slot in between, so we have one less to loop through.
        for(int i = 0; i < OccupiedSlots.size() - 1; i ++){
            // If occupied slots are back to back which means if there is a schedule right after another,
            // we do not add 0 minutes as Available.
            if(OccupiedSlots[i + 1].GetStartTime() > OccupiedSlots[i].GetEndTime()){
                AvailSlots->push_back(TimeSlot(OccupiedSlots[i].GetEndTime(), OccupiedSlots[i + 1].GetStartTime()));
            }
        }

        // Time between DailyBound and Last Schedule's Ending Time.
        if(DailyBound.GetEndTime() > OccupiedSlots[OccupiedSlots.size() - 1].GetEndTime()){
            AvailSlots->push_back(TimeSlot(OccupiedSlots[OccupiedSlots.size() - 1].GetEndTime(), DailyBound.GetEndTime()));
        }
    }else{
        // If there was no occupied slots, which means person A has no schedule for this day.
        // That means the Daily Bounds (preferred time) will be all available.
        AvailSlots->push_back(TimeSlot(DailyBound.GetStartTime(), DailyBound.GetEndTime()));
    }

    return AvailSlots;
}

// Using minimum required time to consider while we combine 2 time slots.
vector<TimeSlot>* CombineAvailSlots(vector<TimeSlot>* a, vector<TimeSlot>* b, int MinTime){
    vector<TimeSlot>* MergedSlot = new vector<TimeSlot>();

    // Unfortunately, we have to look at each time slot for every other time slot, because take a look at following,
    // Person A: [9:00, 15:00]
    // Person B: [10:00, 11:00], [13:00, 14:30]
    // MinTime : 30 minutes
    // Output  : [10:00, 11:00], [13:00, 14:30]
    // This is because both of Person B's available time slots fall under Person A's slot.
    for(int i = 0; i < a->size(); i ++){
        for(int j = 0; j < b->size(); j ++){
            // This found "merged" will be stored in "MergedSlot" in chronological order (sorted),
            // because we are looping with index "i" in chronological order.
            TimeSlot* merged = MergeTimeSlots(a->at(i), b->at(j));
            if(merged != nullptr){
                // Make sure merged time satisfies minimum required time for the meeting.
                if(merged->DurationInMinutes() >= MinTime){
                    MergedSlot->push_back(TimeSlot(merged->GetStartTime(), merged->GetEndTime()));
                }

                delete merged;
            }
        }
    }

    return MergedSlot;
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
    
    TimeSlot DailyBound_A(Calendars[1][0], Calendars[1][1]);
    TimeSlot DailyBound_B(Calendars[3][0], Calendars[3][1]);

    // Using "Occupied Time Slots" and "Daily Bounds", get Available time slots.
    // It is guaranteed that the time slots are in chronological order (aka sorted).
    vector<TimeSlot>* AvailSlots_A = FindAvailSlots(DailyBound_A, OccupiedSlots_A); 
    vector<TimeSlot>* AvailSlots_B = FindAvailSlots(DailyBound_B, OccupiedSlots_B);;

    // Depending on the required minimum time, merge two Time Slots.
    int MinTime = stoi(Calendars[4][0]);
    vector<TimeSlot>* CompromisedSlots = CombineAvailSlots(AvailSlots_A, AvailSlots_B, MinTime);

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
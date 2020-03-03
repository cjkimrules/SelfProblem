
#include <algorithm>
#include "Time.h"

using namespace std;


Time::Time(int h, int m){
    this->hour = h;
    this->minute = m;
}
int Time::GetHour() const{
    return this->hour;
}
int Time::GetMinute() const{
    return this->minute;
}
void Time::SetTime(int h, int m){
    this->hour = h;
    this->minute = m;
}

Time Time::operator + (Time const& other){
    int hour = this->GetHour() + other.GetHour();
    int min = this->GetMinute() + other.GetMinute();
    if(min >= 60){
        min -= 60;
        hour ++;
    }

    return Time(hour, min);
}
Time Time::operator - (Time const& other){
    int hour = this->GetHour() - other.GetHour();
    int min = this->GetMinute() - other.GetMinute();
    if(min < 0){
        min += 60;
        hour --;
    }

    return Time(hour, min);
}

bool Time::operator < (Time const& other){
    if(this->GetHour() > other.GetHour()) return false;
    if((this->GetHour() == other.GetHour()) && (this->GetMinute() >= other.GetMinute())) return false;
    return true;
}
bool Time::operator > (Time const& other){
    if(this->GetHour() < other.GetHour()) return false;
    if((this->GetHour() == other.GetHour()) && (this->GetMinute() <= other.GetMinute())) return false;
    return true;
}
bool Time::operator == (Time const& other){
    if(this->GetHour() != other.GetHour()) return false;
    if(this->GetMinute() != other.GetMinute()) return false;
    return true;
}
bool Time::operator <= (Time const& other){
    return *this < other || *this == other;
}
bool Time::operator >= (Time const& other){
    return *this > other || *this == other;
}


Time GetMaxTime(Time const& a, Time const&  b){
    int maxHour, maxMinute;
    if(a.GetHour() == b.GetHour()){
        maxHour = a.GetHour();
        maxMinute = max(a.GetMinute(), b.GetMinute());
    }else if(a.GetHour() < b.GetHour()){
        maxHour = b.GetHour();
        maxMinute = b.GetMinute();
    }else{
        maxHour = a.GetHour();
        maxMinute = a.GetMinute();
    }
    return Time(maxHour, maxMinute);
}

Time GetMinTime(Time const& a, Time const& b){
    int minHour, minMinute;
    if(a.GetHour() == b.GetHour()){
        minHour = a.GetHour();
        minMinute = min(a.GetMinute(), b.GetMinute());
    }else if(a.GetHour() < b.GetHour()){
        minHour = a.GetHour();
        minMinute = a.GetMinute();
    }else{
        minHour = b.GetHour();
        minMinute = b.GetMinute();
    }
    return Time(minHour, minMinute);
}

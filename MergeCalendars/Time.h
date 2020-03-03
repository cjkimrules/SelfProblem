#ifndef TIME
#define TIME

class Time{
    int hour;
    int minute;

public:
    Time(int h = 0, int m = 0);
    int GetHour() const;
    int GetMinute() const;
    void SetTime(int h, int m);
    
    // Operators
    Time operator + (Time const& other);
    Time operator - (Time const& other);
    bool operator < (Time const& other);
    bool operator > (Time const& other);
    bool operator == (Time const& other);
    bool operator <= (Time const& other);
    bool operator >= (Time const& other);
};

Time GetMaxTime(Time const& a, Time const& b);
Time GetMinTime(Time const& a, Time const& b);

#endif
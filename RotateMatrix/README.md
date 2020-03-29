## Rotate Given Matrix by 90 Degrees Counter-ClockWise

This was an interview question asked by Amazon (posted online, I didn't had this question personally).


"main.py" does recursive way, where rotation happens for every layer.
Looping until it gets to the core. This takes some memory space and runtime (quadratic time and stack memory), but this can be done better by just looping.

"main_better.py" is done without recursive, but this is sort of "cheating" way.
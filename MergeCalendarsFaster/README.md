## Merge Two People's Calendars to Find a Time for a Meeting.

### See details in "MergeCalendars" repository. This is more like an upgrade version.

The code is a bit longer but that usually happens when we try to optimize the time complexity.
I had to put extra functions but they still look a bit messy. I wasn't trying to go for how clean it looks,
but rather get the better optimal solution.

In the older (squared time) project, I converted Occupied slots to Available Slots then used bounds
and combined with others using MinTime. The key was to NOT convert Occupied Slots into Available Slots
until the very end. We could've just combined Occupied Slots altogether and using the Daily Bounds and MinTime
to flip them into Available Slots.

The problem of previous was to do A ∩ B to find all possible Available Slots from All Available Slots.
New Solution is better because we just do A ∪ B to find combined Occupied Slots from All Occupied Slots.
Then simply convert Occupied Slots into Available Slots. "∪" is much simpler to combine when arrays are sorted,
rather than "∩".

To know more about symbols, "∩" & "∪":

https://courses.lumenlearning.com/boundless-statistics/chapter/what-are-the-chances/
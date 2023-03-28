/*
FYP : 22013

Module:
    Hybrid Query Driver - Query Driver Utilities

Description:
    Defines the time-related utilities of the Hybrid Query Driver, which are
    used across the benchmarking system..
*/
#include "QDU001_Time.h"

/*
Description:
    Provides a common method to get the current time in the form of number of
    milliseconds passed since epoch.
*/
uint64_t get_current_epoch_time_in_milliseconds() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
          ).count();
}

#ifndef SYSTEM_H
#define SYSTEM_H


#include <stdint.h>  // for using standard integer types

#include "config.h"  // for configuration macros


// return codes for the system_power() function
enum {
    SYSTEM_ADAPTOR,
    SYSTEM_BATTERY,
};


// flags for system.status
#define SYSTEM_SLEEP          0x01
#define SYSTEM_ALARM_SOUNDING 0x02


typedef struct {
    uint8_t status;
    uint8_t initial_mcusr;
} system_t;


extern volatile system_t system;


void system_init(void);

inline void system_wake(void) {};
inline void system_sleep(void) {};

inline void system_tick(void) { 
    // if sleeping, enable analog comparater so system will know
    // if external power has been restored;  this must be done
    // here instead of in system_sleep_loop() because the analog
    // comparator needs a few microseconds to start
    if(system.status & SYSTEM_SLEEP) ACSR = _BV(ACBG);
};

inline void system_semitick(void) {};

void system_idle_loop(void);
void system_sleep_loop(void);

uint8_t system_power(void);

#endif
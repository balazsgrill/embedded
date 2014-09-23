#include <xc.h>
#include "mtypes.h"
#include "runtime.h"
#include "scheduler.h"

#define NUM_OF_TASKS 2

static uint8 sch_counters[NUM_OF_TASKS];

void sch_init(){

    uint8 i;
    for(i = 0;i<NUM_OF_TASKS;i++){
        sch_counters[i] = 0;
    }

    /* Select system clock */
    T1CONbits.T1OSCEN = 0;
    T1CONbits.TMR1CS0 = 0;
    T1CONbits.TMR1CS1 = 0;

    /* Prescaler 1:1 */
    T1CONbits.T1CKPS0 = 0;
    T1CONbits.T1CKPS1 = 0;

    /* System clock : 2Mhz
     * 1 Tick = 0,032 sec (30,51 hz)
     * 1sec = ~30 counts
     */

    PIR1bits.TMR1IF = 0;

    /* Enable timer 1 */
    T1CONbits.TMR1ON = 1;
}

void sch_step(){
    if (PIR1bits.TMR1IF){
        PIR1bits.TMR1IF = 0;
        uint8 i;
        for(i = 0;i<NUM_OF_TASKS;i++){
            if (sch_counters[i] > 0u){
                sch_counters[i]--;
                if (sch_counters[i] == 0u){
                    SCH_TIMER_TRIGGER(i);
                }
            }
        }
    }
}

void sch_start(uint8 id, uint8 timer){
    if (id < NUM_OF_TASKS){
        sch_counters[id] = timer;
    }
}

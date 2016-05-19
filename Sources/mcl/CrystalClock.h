#ifndef CRYSTALCLOCK_H_
#define CRYSTALCLOCK_H_


#define CORE_CLOCK				 (48000000)
#define PERIPHERAL_BUS_CLOCK (CORE_CLOCK/2)

void InitClock(void);

extern int rul_currentSystemClockHz;


#endif /* CRYSTALCLOCK_H_ */

#ifndef __DRIVE_ADC_H__
#define __DRIVE_ADC_H__

extern void Drive_AdcConfig(void);
extern uint32_t Drive_ADCConvert(uint32_t Channel);
extern void Drive_AdcGpio_init(void);

#endif



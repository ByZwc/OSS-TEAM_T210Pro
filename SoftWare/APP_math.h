#ifndef __APP_MATH_H__
#define __APP_MATH_H__

#define NUM_TAPS 4
#define BLOCK_SIZE 1

typedef struct
{
    float32_t x;    // �˲����
    float32_t p;    // ����Э����
    float32_t diff; // �������趨����
    float32_t q;    // ��������
    float32_t r;    // ��������
    float32_t k;    // ����������
} TYPEDEF_KALMAN_S;

float32_t APP_FirFilter_NtcTemp(float32_t Src);
float32_t APP_FirFilter_ADC(float32_t Src);
float32_t app_DisplayFilter_RC(float32_t Cur, float32_t Tar);
float32_t app_DisplayFilter_kalman(float32_t Cur, float32_t Tar);

float32_t app_solderingT210_adcTurnToTemp(uint32_t solderingT210AdcVlaue);
float32_t app_solderingT245_adcTurnToTemp(uint32_t solderingT45_AdcVlaue);
float32_t APP_solderingElectricity_Get(uint32_t solderingElectricity_AdcVlaue);
float32_t APP_PcbNtc_adcTurnToTemp(uint32_t pcbNtc_AdcVlaue);
float32_t APP_solderingID_Check(uint32_t solderingID_AdcVlaue);

void APP_shortCircuitProtection(void);
void app_PcbTempProtect_Task(void);
void app_pid_Task(void);
void app_GetAdcVlaue_electricity_Task(void);
void app_Samp_electricity_Task(void);
float APP_Power_complementaryFilter_Task(void);
#endif

//*****************************************************************************************/

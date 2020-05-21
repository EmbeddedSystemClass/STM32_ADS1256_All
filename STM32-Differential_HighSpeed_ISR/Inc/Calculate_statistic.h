#include "arm_math.h"
#include <stdio.h>
#include <math.h>


float Calculate_max(float *data);
float Calculate_FreqMax(float *data,int freqSettingValue, int8_t freq_index);
float Calculate_skewness(float *data, int n);
float Calculate_kurtosis(float *data, int n);
float Calculate_rms(float *data, int n);
float Calculate_FreqOverAll(float *data, int n);

typedef struct Statistic_value
{
	float32_t Statistic_max;
	float32_t Statistic_min;
	float32_t Statistic_var;
	float32_t Statistic_rms;
	float32_t Statistic_mean;
	float32_t Statistic_std;
	float32_t Statistic_crestFactor;
	float32_t Statistic_kurtosis;
	float32_t Statistic_skewness;
	float32_t Statistic_FreqOvall;
	float32_t Statistic_FreqPeak[20];
	float32_t Statistic_p2p;
	float32_t Statistic_SpeedOvall;

	float32_t Statistic_max_Temp;
	float32_t Statistic_min_Temp;
	float32_t Statistic_var_Temp;
	float32_t Statistic_rms_Temp;
	float32_t Statistic_mean_Temp;
	float32_t Statistic_std_Temp;
	float32_t Statistic_crestFactor_Temp;
	float32_t Statistic_kurtosis_Temp;
	float32_t Statistic_skewness_Temp;
	float32_t Statistic_FreqOvall_Temp;
	float32_t Statistic_p2p_Temp;
	float32_t Statistic_SpeedOvall_Temp;

}Sv;

struct Freq_settingValue
{
	int freq1;
	int freq2;
	int freq3;
	int freq4;
	int freq5;
	int freq6;
	int freq7;
	int freq8;
	int freq9;
	int freq10;
	int freq11;
	int freq12;
	int freq13;
	int freq14;

}freq_settingValue;


Sv statistic_value;

#include "Calculate_statistic.h"


float Calculate_max(float *data)
{
	float max= 0;
	float mid= 0;  //
		for(int i = 0;i<4096;i++){
		/*因為arr[i]是固定的 ，所以可以用arr[i]先和max比較，如果大於max 則
			把max的值賦給mid的值，然後把arr[i]賦給max  這樣max肯定比mid大*/
		if(data[i]>max){
		mid = max;
		max =data[i];

			}else if(data[i]>mid){/*  另一種情況 arr[i]處於兩者之間*/
				mid = data[i];//  則吧arr[i]賦給mid
			}


		}
		printf("max=%d,mid=%d\n",max,mid);


		return max;
}
float Calculate_FreqMax(float *data, int freqSettingValue, int8_t freq_index)
{
	if(freqSettingValue != 0)
	{
		volatile float temp = 0;
			if(freqSettingValue < 25)
			{
				for(int i = freqSettingValue- 25; i<freqSettingValue + 25; i++)
					{

						if(data[i] > temp)
						{
							temp += data[i];
						}
					}
			}
			else
			{

				for(int i = freqSettingValue; i<freqSettingValue + 25; i++)
					{

						if(data[i] > temp)
						{
							temp += data[i];
						}
					}
			}
		statistic_value.Statistic_FreqPeak[freq_index] = temp;
	}

}


float Calculate_3timesFeatureAverage(Sv data)
{

	return 1;
}

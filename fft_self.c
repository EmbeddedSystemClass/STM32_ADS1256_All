#include "fft_self.h"

/* ------------------------------------------------------------------
* Global variables for FFT Bin Example
* ------------------------------------------------------------------- */
uint32_t fftSize = 4096;
uint32_t ifftFlag = 0;
uint32_t doBitReverse = 1;

/* Reference index at which max energy of bin ocuurs */
uint32_t refIndex = 213, testIndex = 0;
void fft_real_image_4096(float* data, float* outputdata){
     arm_status status;
	 float32_t maxValue;

	 status = ARM_MATH_SUCCESS;

	 /* Process the data through the CFFT/CIFFT module */
	 arm_cfft_f32(&arm_cfft_sR_f32_len4096, data, ifftFlag, doBitReverse);

	 /* Process the data through the Complex Magnitude Module for
	 calculating the magnitude at each bin */
	 arm_cmplx_mag_f32(data, outputdata, fftSize);

	 /* Calculates maxValue and returns corresponding BIN value */
	 arm_max_f32(outputdata, fftSize, &maxValue, &testIndex);

	 if(testIndex !=  refIndex)
	 {
	   status = ARM_MATH_TEST_FAILURE;
	 }

}

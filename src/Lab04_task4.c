//--------------------------------
// Lab 4 - Sample - Lab04_sample.c
//--------------------------------
//
//

#include "init.h"
volatile uint32_t count1 = 0;
void configureADC();
void configureDAC();
double calculator(double first, double second, double third, double fourth);
DAC_HandleTypeDef hdac1;

ADC_HandleTypeDef hadc;
ADC_ChannelConfTypeDef sConfig;
GPIO_InitTypeDef gpio;
uint16_t rawValue;
volatile float voltage;
volatile float highestVoltage=0;
volatile float lowestVoltage=0;
volatile float averageVoltage;
volatile int count=0;

double thirdValue = 0;
double secondValue = 0;
double firstValue = 0;
double secondDacValue=0;
double firstDacValue = 0;

double thirdValue2 = 0;
double secondValue2 = 0;
double firstValue2 = 0;
double secondDacValue2=0;
double firstDacValue2 = 0;
double result = 0;

// Main Execution Loop
int main(void)
{

	//Initialize the system
	Sys_Init();
	configureADC();
	configureDAC();
	HAL_Init();

	//HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);

	while (1)
	{

		HAL_ADC_Start(&hadc);
		HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);
		HAL_ADC_PollForConversion(&hadc, 1000);
		count1 = HAL_ADC_GetValue(&hadc);

		HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, count1);





	}
}

void configureDAC()
{
	// Enable the DAC Clock.
	__HAL_RCC_SYSCFG_CLK_ENABLE();
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;

	DAC_ChannelConfTypeDef sConfig;
	HAL_DAC_Init(&hdac1); // Initialize the ADC
	hdac1.Instance = DAC1;

	//DAC channel OUT2 config
	sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
	HAL_DAC_MspInit(&hdac1);

// Configure the ADC channel
	HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1);



}

void configureADC()
{
	// Enable the ADC Clock.
	//__HAL_RCC_SYSCFG_CLK_ENABLE();
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	hadc.Instance = ADC1;
	hadc.NbrOfCurrentConversionRank = 1;
	hadc.Init.Resolution = ADC_RESOLUTION_12B;
	hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	hadc.Init.ContinuousConvMode = DISABLE;
	hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc.Init.DiscontinuousConvMode = DISABLE;
	hadc.Init.ScanConvMode = DISABLE;
	hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc.Init.NbrOfConversion =1;


	HAL_ADC_Init(&hadc); // Initialize the ADC

	sConfig.Channel = ADC_CHANNEL_6;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;

	// Configure the ADC channel

	HAL_ADC_ConfigChannel(&hadc, &sConfig);
}


void HAL_DAC_MspInit(DAC_HandleTypeDef *hadc)
{
	GPIO_InitTypeDef gpio;

	__GPIOA_CLK_ENABLE();

	//output -  gpio configuration for A4

	gpio.Pin = GPIO_PIN_4;
	gpio.Mode = GPIO_MODE_ANALOG;
	gpio.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &gpio);


}

void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOJ_CLK_ENABLE();

	//PA6
	gpio.Pin = GPIO_PIN_6;
	gpio.Mode = GPIO_MODE_ANALOG;
	gpio.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA,&gpio);

	//PJ4
	gpio.Pin = GPIO_PIN_4;
	gpio.Mode = GPIO_MODE_INPUT;
	gpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOJ,&gpio);



// GPIO init

}
void ADC_IRQHandler(ADC_HandleTypeDef* hadc){
	HAL_ADC_IRQHandler(hadc);
}
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	thirdValue = secondValue;
	secondValue = firstValue;
	firstValue = HAL_ADC_GetValue(hadc);

	secondDacValue = firstDacValue;

	firstDacValue = (.3125*firstValue)+(.240385*secondValue)+(.3125*thirdValue)+(.296875*secondDacValue);

	result = calculator(firstValue, secondValue, thirdValue,result);

	HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);
	HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_L, firstDacValue);
	HAL_ADC_Start_IT(hadc);
}

double calculator(double firstValue, double secondValue, double thirdValue, double fourthValue)
{

	//secondDacValue2 = firstDacValue2;

	double input1 = firstValue;
	double input2 = secondValue;
	double input3 = thirdValue;
	double input4 = fourthValue;
	//double input5;

//	double var1 = 2;
//	double var2 = 3;
//	double var3 = 5;
//
//
//	int32_t const1 = 2;
//	volatile double consts1;
//
//	double var4;
//	double var5;
//	double var6;
//
//	double var7;
//	double var8 = 0.3333;
//	double var9 = 5;

	double ten = 10;
	double thirtytwo = 32;
	double thirteen = 13;
	double nineteen = 19;
	double twenty = 20;
	volatile double c1 = 0;
	volatile double c2 = 0;
	volatile double c3 = 0;
	volatile double c4 = 0;
	volatile double c5 = 0;

	double constant1 = 1.000;



	double rr0;
	double output1 = input1;
	double outputcopy1;


	//for before  x(k)
	asm volatile ("VDIV.F64 %P[rr0],%P[fac1],%P[fac2]": [rr0] "=w" (c1): [fac1] "w" (ten) , [fac2] "w" (thirtytwo));

	//for x(k-1)
	asm volatile ("VDIV.F64 %P[rr0],%P[fac1],%P[fac2]": [rr0] "=w" (c3): [fac1] "w" (ten) , [fac2] "w" (thirteen));
	asm volatile ("VMLA.F64 %P[rr0],%P[fac1],%P[fac2]": [rr0] "+&w" (output1): [fac1] "w" (c3) , [fac2] "w" (input2));

	//for x(k-2)
	asm volatile ("VMLA.F64 %P[rr0],%P[fac1],%P[fac2]": [rr0] "+&w" (output1): [fac1] "w" (constant1) , [fac2] "w" (input3));

	//for y(k-1)
	asm volatile ("VDIV.F64 %P[rr0],%P[fac1],%P[fac2]": [rr0] "=w" (c4): [fac1] "w" (nineteen) , [fac2] "w" (twenty));
	asm volatile ("VMLA.F64 %P[rr0],%P[fac1],%P[fac2]": [rr0] "+&w" (output1): [fac1] "w" (c4) , [fac2] "w" (input4));

	//multiplying equation within parenthesis by 10/32
	outputcopy1 = output1;
	asm volatile ("VMUL.F64 %P[rr0],%P[fac1],%P[fac2]": [rr0] "=w" (outputcopy1): [fac1] "w" (c1) , [fac2] "w" (output1));

	return outputcopy1;

}

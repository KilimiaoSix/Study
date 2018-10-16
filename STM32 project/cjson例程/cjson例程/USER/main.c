/**
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/main.c 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    24-July-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stdlib.h"
#include <stdarg.h>
#include "stdio.h"
#include <string.h>
#include "stm32f0xx.h"
#include "stm32f0xx_conf.h"
#include "Mcu_config.h"
#include "cJSON.h"

/** @addtogroup STM32F0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

char * makeJson()
{
  cJSON * pJsonRoot = NULL;
	cJSON * pSubJson;
	char * p;

  pJsonRoot = cJSON_CreateObject();
  if(NULL == pJsonRoot)
  {
      //error happend here
      return NULL;
  }
  cJSON_AddStringToObject(pJsonRoot, "hello", "hello world");
	cJSON_AddStringToObject(pJsonRoot, "upload", "yunpingtai");
  cJSON_AddNumberToObject(pJsonRoot, "IntNumber", 10010);
	cJSON_AddNumberToObject(pJsonRoot, "FloatNumber", 11.11);
  cJSON_AddBoolToObject(pJsonRoot, "bool", 1);
  pSubJson = NULL;
  pSubJson = cJSON_CreateObject();
  if(NULL == pSubJson)
  {
      // create object faild, exit
      cJSON_Delete(pJsonRoot);
      return NULL;
  }
  cJSON_AddStringToObject(pSubJson, "subjsonobj", "a sub json string");
  cJSON_AddItemToObject(pJsonRoot, "subobj", pSubJson);

  p = cJSON_Print(pJsonRoot);
  if(NULL == p)
  {
      //convert json list to string faild, exit
      //because sub json pSubJson han been add to pJsonRoot, so just delete pJsonRoot, if you also delete pSubJson, it will coredump, and error is : double free
      cJSON_Delete(pJsonRoot);
      return NULL;
  }
  
  cJSON_Delete(pJsonRoot);

  return p;
}

void parseJson(char * pMsg)
{
    cJSON * pSub;	
		cJSON * pJson;
		cJSON * pSubSub;
    if(NULL == pMsg)
    {
        return;
    }
    pJson = cJSON_Parse(pMsg);
    if(NULL == pJson)                                                                                         
    {
        // parse faild, return
      return ;
    }

    // get string from json		
		pSub = cJSON_GetObjectItem(pJson, "hello");
    if(NULL == pSub)
    {
        //get object named "hello" faild
			  cJSON_Delete(pJson);
				return;
    }
    printf("obj_1 : %s\n", pSub->valuestring);

    // get string from json			
    pSub = cJSON_GetObjectItem(pJson, "upload");
    if(NULL == pSub)
    {
        //get object named "upload" faild
			  cJSON_Delete(pJson);
				return;			
    }
    printf("obj_2 : %s\n", pSub->valuestring);
		
    // get number from json
    pSub = cJSON_GetObjectItem(pJson, "IntNumber");
    if(NULL == pSub)
    {
        //get number from json faild
			  cJSON_Delete(pJson);
				return;			
    }
    printf("obj_3 : %d\n", pSub->valueint);
	
    // get number from json
    pSub = cJSON_GetObjectItem(pJson, "FloatNumber");
    if(NULL == pSub)
    {
        //get number from json faild
			  cJSON_Delete(pJson);
				return;				
    }
    printf("obj_4 : %f\n", pSub->valuedouble);

    // get bool from json
    pSub = cJSON_GetObjectItem(pJson, "bool");
    if(NULL == pSub)
    {
        // get bool from json faild
			  cJSON_Delete(pJson);
				return;				
    }                                                                                                         
    printf("obj_5 : %d\n", pSub->valueint);

		// get sub object
    pSub = cJSON_GetObjectItem(pJson, "subobj");
    if(NULL == pSub)
    {
        // get sub object faild
			  cJSON_Delete(pJson);
				return;
    }
    pSubSub = cJSON_GetObjectItem(pSub, "subjsonobj");
    if(NULL == pSubSub)
    {
        // get object from subject object faild
			  cJSON_Delete(pJson);
				return;
    }
    printf("sub_obj_1 : %s\n", pSubSub->valuestring);

    cJSON_Delete(pJson);
}


char * makeArray(int iSize)
{
    cJSON * root =  cJSON_CreateArray();    
    int i;	
		char * out;	
	
    if(NULL == root)
    {
        printf("create json array faild\n");
        return NULL;
    }
    i = 0;
    
    for(i = 0; i < iSize; i++)
    {
        cJSON_AddNumberToObject(root, "hehe", i);
    }
    out = cJSON_Print(root);
    cJSON_Delete(root);

    return out;
}


void parseArray(char * pJson)
{
    cJSON * root;
		cJSON * pSub;
    int iSize;
		int iValue;	
		int iCnt;	
	
    if(NULL == pJson)
    {                                                                                                
        return ;
    }
    root = NULL;
    if((root = cJSON_Parse(pJson)) == NULL)
    {
        return ;
    }
    iSize = cJSON_GetArraySize(root);
    for(iCnt = 0; iCnt < iSize; iCnt++)
    {
        pSub = cJSON_GetArrayItem(root, iCnt);
        if(NULL == pSub)
        {
            continue;
        }
        iValue = pSub->valueint;
        printf("value[%2d] : [%d]\n", iCnt, iValue);
    }
    cJSON_Delete(root);
    return;
}

/*
二手开发板供求交易信息群 68936520
stm32技术交流群227043677
arm技术交流群324753668
*/
int main(void)
{
	//uint8_t value;
  char * p;
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */
	
	MCU_Init();
	delay_1ms(1000);
	printf("This is a cjson programming example.\r\n");

	while(1)
	{
		
		p = makeJson();
    if(NULL == p)
    {
        return 0;
    }
    printf("%s\n", p);
    parseJson(p);
		free(p);
		
		p = makeArray(5);
    if(NULL == p)
    {
        return 0;
    }
    printf("%s\n", p);
    parseArray(p);
		free(p);
		
		delay_1ms(5000);
  }
}


PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
	
  USART_SendData(USART2, (uint8_t) ch);

  /* Loop until transmit data register is empty */
  while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
  {}

  return ch;
}
#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: UART_Printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

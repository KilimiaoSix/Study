#include "timer.h"
void TIM4_Init(u32 arr,u32 psc)
{
   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
   
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  

   //¶¨Ê±Æ÷TIM1³õÊ¼»¯
	TIM_TimeBaseStructure.TIM_Period = arr; //ÉèÖÃÔÚÏÂÒ»¸ö¸üĞÂÊÂ¼ş×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ	
	TIM_TimeBaseStructure.TIM_Prescaler = psc; //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ıÊıµÄÔ¤·ÖÆµÖµ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIMÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //¸ù¾İÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î»
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //Ê¹ÄÜÖ¸¶¨µÄTIM1ÖĞ¶Ï ¿ªÆô¸üĞÂÖĞ¶Ï
   
   //ÖĞ¶ÏÓÅÏÈ¼¶NVICÉèÖÃ
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4ÖĞ¶Ï
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;  //ÏÈÕ¼ÓÅÏÈ¼¶0¼¶
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;  //´ÓÓÅÏÈ¼¶3¼¶
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQÍ¨µÀ±»Ê¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);  //³õÊ¼»¯NVIC¼Ä´æÆ÷

	TIM_Cmd(TIM4, ENABLE);  //Ê¹ÄÜTIMx	
}
//void TIM4_IRQHandler(void)
//{
//   if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //¼ì²éTIM3¸üĞÂÖĞ¶Ï·¢ÉúÓë·ñ
//   {
////      if(Stop_Flag)
////         {
////            THROTTLE=THROTTLE_MIN;  //¹Ø±ÕÓÍÃÅ
////            subject_flag=0;  //½áÊøÊÖ¶¯¿ØÖÆ×´Ì¬
////            Stop_Flag=0; //¸´Î»ÏµÍ³
////            return;
////         }
////         
////      if(subject_flag==1)  //Èç¹ûÏÖÔÚÊÇÔÚ×öµÚÒ»Ìâ
////      {
////         openMVControl=1;  //À­¸ßÇı¶¯½Å£¬±íÊ¾ÔÚÕÒÔ²
////         if(Take_flag)  //Æô¶¯·ÉĞĞÆ÷
////         {
////            Flight_control_Unlock();//½âËø·É¿Ø
////            Take_off(&HStruct);  //Æğ·É
////            Take_flag=0;
////            delay_ms(1000);delay_ms(1000);//ÑÓÊ±6Ãëºó¿ªÊ¼×·Ô²
////            delay_ms(1000);delay_ms(1000);
////            delay_ms(1000);delay_ms(1000);
////         }  //Ö´ĞĞÍêÆğ·ÉÖ¸Áîºó·É»ú¾Í²»ÔÚÊ¹ÓÃÆğ·Éº¯Êı
////         //Chase_Circle(&XStruct,&YStruct);  //ĞŞÕı×ø±ê£¬±£Ö¤ÄÜ¹»½µÂäÔÚAÇøÓò
////         High_control(&HStruct,high);  //ÎÈ¶¨¸ß¶È
//////         if((cir_Point_x-XMiddle)<5&&(cir_Point_y-YMiddle)<5)  //µ±²îÖµĞ¡ÓÚÎå¸öÏñËØµãÊ±£¬½µÂä
//////         {
//////            Land_flag=1;
//////            delay_ms(1000);delay_ms(1000);//ÑÓÊ±Á½Ãëºó¿ªÊ¼½µÂä
//////         }
//////         if(Land_flag)  //µ±½µÂä±êÖ¾Î»ÖÃ1Ê±¿ªÊ¼Ö´ĞĞ½µÂäº¯Êı
//////         {
//////            Land(&HStruct);
//////            Take_flag=1;
//////            Land_flag=0;
//////            subject_flag=0;
//////            openMVControl=0;  //À­µÍÇı¶¯½Å£¬½«openMV»Ø¹éÄ¬ÈÏÄ£Ê½
//////         }
////      }
////      else if(subject_flag==2)  //Èç¹ûÏÖÔÚÊÇÔÚ×öµÚ¶şÌâ
////      {
////         openMVControl = 0;  //À­µÍÇı¶¯½Å£¬¿ªÊ¼Ñ°ÏßÄ£Ê½
////         if(Take_flag)  //Æô¶¯·ÉĞĞÆ÷
////         {
////            Flight_control_Unlock();//½âËø·É¿Ø
////            Take_off(&HStruct);  //Æğ·É
////            Take_flag=0;
////            delay_ms(1000);delay_ms(1000);//ÑÓÊ±6Ãëºó¿ªÊ¼Ñ°Ïß
////            delay_ms(1000);delay_ms(1000);
////            delay_ms(1000);delay_ms(1000);
////         }  //Ö´ĞĞÍêÆğ·ÉÖ¸Áîºó·É»ú¾Í²»ÔÚÊ¹ÓÃÆğ·Éº¯Êı
////         High_control(&HStruct,high);  //ÎÈ¶¨¸ß¶È
////         if(uFindLin_flag)  //Èç¹û´¦ÓÚÑ°ÏßÄ£Ê½
////            Traction_control(&XStruct,&YStruct,&ZStruct);  //Ñ­¼£
////         else if(uFindCir_flag)//Èç¹û´¦ÓÚ×·Ô²Ä£Ê½
////            Chase_Circle(&XStruct,&YStruct);//×·Ô²
////         else if(uLanding)  //Òì³£Çé¿ö
////            Land_flag=1;    //Æô¶¯½µÂäº¯Êı
////         if(uFindCir_flag&&((cir_Point_x-XMiddle)<5&&(cir_Point_y-YMiddle)<5))  //Èç¹û´¦ÓÚ×·Ô²Ä£Ê½ÇÒ×ø±ê²îÖµĞ¡ÓÚÎå¸öÏñËØµã£¬Ê¹ÄÜ½µÂäº¯Êı
////            Land_flag=1;
////            delay_ms(1000);delay_ms(1000);//ÑÓÊ±Á½Ãëºó¿ªÊ¼½µÂä
////         if(Land_flag)  //µ±½µÂä±êÖ¾Î»ÖÃ1Ê±¿ªÊ¼Ö´ĞĞ½µÂäº¯Êı
////         {
////            Land(&HStruct);
////            Take_flag=1;
////            Land_flag=0;
////            uLanding=0;  //¸´Î»Òì³£×´Ì¬±êÖ¾Î»
////            subject_flag=0;
////            openMVControl=1;  //À­¸ßÇı¶¯½Å£¬ÍË³öÑ°Ô²Ëø¶¨£¬½øÈëÑ°Ô²Ä£Ê½
////         }
////      }
////      else if(subject_flag==3)  //Èç¹ûÏÖÔÚÊÇÔÚ×öµÚÈıÌâ
////      {
////         openMVControl = 0;  //À­µÍÇı¶¯½Å£¬¿ªÊ¼Ñ°ÏßÄ£Ê½
////         if(Take_flag)  //Æô¶¯·ÉĞĞÆ÷
////         {
////            Flight_control_Unlock();//½âËø·É¿Ø
////            Take_off(&HStruct);  //Æğ·É
////            Take_flag=0;
////            delay_ms(1000);delay_ms(1000);//ÑÓÊ±6Ãëºó¿ªÊ¼Ñ°Ïß
////            delay_ms(1000);delay_ms(1000);
////            delay_ms(1000);delay_ms(1000);
////         }  //Ö´ĞĞÍêÆğ·ÉÖ¸Áîºó·É»ú¾Í²»ÔÚÊ¹ÓÃÆğ·Éº¯Êı
////         Straight_line_judgment();  //Ïß¶ÎĞ£×¼
////         if(Number==0||Number>2)
////            HStruct.Goal=0.6;
////         else if(Number==2)
////            HStruct.Goal=1.5;
////         High_control(&HStruct,high);  //ÎÈ¶¨¸ß¶È
////         if(uFindLin_flag)  //Èç¹û´¦ÓÚÑ°ÏßÄ£Ê½
////            Traction_control(&XStruct,&YStruct,&ZStruct);  //Ñ­¼£
////         else if(uFindCir_flag)//Èç¹û´¦ÓÚ×·Ô²Ä£Ê½
////            Chase_Circle(&XStruct,&YStruct);//×·Ô²
////         else if(uLanding)  //Òì³£Çé¿ö
////            Land_flag=1;    //Æô¶¯½µÂäº¯Êı
////         if(uFindCir_flag&&((cir_Point_x-XMiddle)<5&&(cir_Point_y-YMiddle)<5))  //Èç¹û´¦ÓÚ×·Ô²Ä£Ê½ÇÒ×ø±ê²îÖµĞ¡ÓÚÎå¸öÏñËØµã£¬Ê¹ÄÜ½µÂäº¯Êı
////            Land_flag=1;
////            delay_ms(1000);delay_ms(1000);//ÑÓÊ±Á½Ãëºó¿ªÊ¼½µÂä
////         if(Land_flag)  //µ±½µÂä±êÖ¾Î»ÖÃ1Ê±¿ªÊ¼Ö´ĞĞ½µÂäº¯Êı
////         {
////            Land(&HStruct);
////            Take_flag=1;
////            Land_flag=0;
////            uLanding=0;  //¸´Î»Òì³£×´Ì¬±êÖ¾Î»
////            subject_flag=0;
////            openMVControl=1;  //À­¸ßÇı¶¯½Å£¬ÍË³öÑ°Ô²Ëø¶¨£¬½øÈëÑ°Ô²Ä£Ê½
////         }
////      }
////      else if(subject_flag == 4)//ÊÖ¶¯¿ØÖÆ
////      {
////         if(Unlock_Flag)
////         {
////            Flight_control_Unlock();
////            Unlock_Flag=0;
////         }
////         if(Rise_Flag)
////         {
////            if(THROTTLE<THROTTLE_MAX)
////            {
////               THROTTLE+=10;  //ÂıÂıÀ­¸ßÓÍÃÅ
////               Rise_Flag=0;   //¸´Î»ÓÍÃÅÔö¼Ó±êÖ¾Î
////            }
////         }
////         
////         if(Down_Flag)     
////         {
////            if(THROTTLE>THROTTLE_MIN)
////            {
////               THROTTLE-=10;  //ÂıÂı½µµÍÓÍÃÅ
////               Down_Flag=0;   //¸´Î»ÓÍÃÅÔö¼Ó±êÖ¾Î»
////            }
////         }
////         
////         if(Left_Flag)  
////         {
////            if(ROLL>1350)  //ÇãĞ±½ÇÏŞ·ù
////               ROLL-=50;   //ÇãĞ±½ÇÎ¢Ôö
////            else
////               ROLL=1350;  
////            Left_Flag=0;
////         }
////         else if(ROLL<ROLL_MIDDLE)
////            ROLL++;        //Èç¹ûÃ»ÓĞ×ó×ª±êÖ¾Î»£¬ÂıÂı¸´Î»×ó×ª¿ØÖÆ¼Ä´æÆ÷
////         
////         if(Right_Flag)  
////         {
////            if(ROLL<1650)  //ÇãĞ±½ÇÏŞ·ù
////               ROLL+=50;   //ÇãĞ±½ÇÎ¢Ôö
////            else
////               ROLL=1650;  
////            Right_Flag=0;
////         }
////         else if(ROLL>ROLL_MIDDLE)
////            ROLL--;        //Èç¹ûÃ»ÓĞÓÒ×ª±êÖ¾Î»£¬ÂıÂı¸´Î»ÓÒ×ª¿ØÖÆ¼Ä´æÆ÷
////         
////         if(Forward_Flag)  
////         {
////            if(PITCH<1650)  //ÇãĞ±½ÇÏŞ·ù
////               PITCH+=50;   //ÇãĞ±½ÇÎ¢Ôö
////            else
////               PITCH=1650;  
////            Forward_Flag=0;
////         }
////         else if(PITCH>PITCH_MIDDLE)
////            PITCH--;        //Èç¹ûÃ»ÓĞÇ°½ø±êÖ¾Î»£HÂıÂı¸´Î»Ç°½ø¿ØÖÆ¼Ä´æÆ÷
////         
////         if(Back_Flag)  
////         {
////            if(PITCH>1350)  //ÇãĞ±½ÇÏŞ·ù
////               PITCH-=50;   //ÇãĞ±½ÇÎ¢Ôö
////            else
////               PITCH=1350;  
////            Back_Flag=0;
////         }
////         else if(PITCH<PITCH_MIDDLE)
////            PITCH++;        //Èç¹ûÃ»ÓĞºóÍË±êÖ¾     ÂıÂı¸´Î»ºóÍË¿ØÖÆ¼Ä´æÆ÷
////         
////         if(LeftHand_Flag)
////         {
////            if(YAW>1350)    //ÇãĞ±½ÇÏŞ·ù
////               YAW-=50;     //ÇãĞ±½ÇÎ¢Ôö
////            else
////               YAW=1350;
////            LeftHand_Flag=0;
////         }
////         else if(YAW<YAW_MIDDLE)
////            YAW++;        //Èç¹ûÃ»ÓĞ×óĞı±êÖ¾Î»£¬¸´Î»×óĞı¿ØÖÆ¼Ä´æÆ÷
////         
////         if(RightHand_Flag)
////         {
////            if(YAW<1650)    //ÇãĞ±½ÇÏŞ·ù
////               YAW+=50;     //ÇãĞ±½ÇÎ¢Ôö
////            else
////               YAW=1650;
////            RightHand_Flag=0;
////         }
////         else if(YAW>YAW_MIDDLE)
////            YAW--;        //Èç¹ûÃ»ÓĞÓÒĞı±êÖ¾Î»£¬¸´Î»ÓÒĞı¿ØÖÆ¼Ä´æÆ÷
////         
////         if(Reset_Flag)  //Èç¹ûÊÕµ½¸´Î»ÇãĞı½Ç±êÖ¾£¬½áÊø¶ÔÈıÖáµÄPWM²¨Êä³ö
////         {
////            YAW=YAW_MIDDLE;  //¸´Î»Æ«º½
////            PITCH=PITCH_MIDDLE;  //¸´Î»¸©Ñö
////            ROLL=ROLL_MIDDLE;  //¸´Î»ºá¹ö
////         }
////      }
////      else if(subject_flag==0)
////      {
////         YAW=YAW_MIDDLE;  //¸´Î»Æ«º½
////         PITCH=PITCH_MIDDLE;  //¸´Î»¸©Ñö
////         ROLL=ROLL_MIDDLE;  //¸´Î»ºá¹ö
////         if(THROTTLE>THROTTLE_MIN)
////            THROTTLE-=10;  //Öğ½¥½µµÍÓÍÃÅÖ±ÖÁÓÍÃÅ×îĞ¡
////         delay_ms(100);
////      }
////   }
//   TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
//}

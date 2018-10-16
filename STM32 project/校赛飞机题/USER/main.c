#include "main.h"
int subject_flag=0;
int Take_flag=1;
int Land_flag=0;
int Forward_Flag=0,Back_Flag=0,Left_Flag=0,Right_Flag=0;
int Rise_Flag=0,Down_Flag=0;
int LeftHand_Flag=0,RightHand_Flag=0;
int Reset_Flag=0;
int Stop_Flag=0;
int Unlock_Flag=0;
PIDTypeDef XStruct,YStruct,ZStruct,HStruct;

// int main(void)
// {	
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //ÉèÖÃÖĞ¶ÏÓÅÏÈ¼¶·Ö×é£¬ÅäÖÃÎª·Ö×é2
//    delay_init();  //³õÊ¼»¯ÑÓÊ±º¯Êı
//    uart1_init(115200);  //openMV´®¿Ú³õÊ¼»¯ 
//    uart2_init(9600);  //À¶ÑÀ´®¿Ú³õÊ¼»¯
//    
//    IO_Init();LED_Init();  //³õÊ¼»¯²¿·Ö¿ØÖÆIOºÍLED
//    
//    Wave_Init(0xffff,72-1);//³¬Éù²¨µçÆ½Çı¶¯³õÊ¼»¯£¬¶¨Ê±Æ÷2ÊäÈë²¶»ñÊ¹ÄÜ
//    //PID³õÊ¼»¯
//    PID_Init(&XStruct,0,0,0,XMiddle);
//    PID_Init(&YStruct,0,0,0,YMiddle);
//    PID_Init(&ZStruct,0,0,0,0);
//    PID_Init(&HStruct,0,0,0,0);//¶ÔPID²ÎÊı½á¹¹Ìå½øĞĞ³õÊ¼»¯
//    
//    TIM3_PWM_Init(20000-1,72-1);//Æô¶¯¶¨Ê±Æ÷3µÄPWM²¨Êä³ö
//    
//    TIM4_Init(20000-1,72-1);  //7200Ô¤·ÖÅä 10000µÄÔ¤ÏÈÖØ×°ÔØÖµ Âö³åÆµÂÊ¾­·ÖÆµºó´ó¸ÅÎª1MHz
//                              //¼ÆÊıÒ»´Î´ó¸ÅÎª1us ´ó¸Å20msÖ´ĞĞÒ»´Î¿ØÖÆº¯Êı
//                              //ÍêÈ«Ê¹ÄÜ¶¨Ê±Æ÷4£¬¿ªÊ¼¿ØÖÆ
//    while(1)
//    {
//       LED0=!LED0;
//       LED1=!LED1;
//       delay_ms(500);
//    }//ledµÆ½»ÌæÉÁË¸£¬±íÃæ³ÌĞòÕı³£ÔËĞĞ
//    
//    
// }
int main()//²âÊÔÖ÷º¯Êı
{
   int i=0;
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //ÉèÖÃÖĞ¶ÏÓÅÏÈ¼¶·Ö×é£¬ÅäÖÃÎª·Ö×é2
   delay_init();  //³õÊ¼»¯ÑÓÊ±º¯Êı
   uart1_init(115200);
   uart2_init(9600);
   TIM3_PWM_Init(20000-1,72-1);//Æô¶¯¶¨Ê±Æ÷3µÄPWM²¨Êä³ö
   TIM1_PWM_Init(20000-1,72-1);  
   Wave_Init(0xffff,72-1);
   IO_Init();LED_Init();
   Data_Init();
   PID_Init(&HStruct,200,0,0,0.5,high);//¶ÔPID²ÎÊı½á¹¹Ìå½øĞĞ³õÊ¼»¯  // Kp:200Æ«´ó ÂÔĞ¡ //Kd:¿É¼Ó£¬Ô¤¼Æ300×óÓÒ  //Ki:¸øĞ¡ 1×óÓÒ£¬KiÓ°Ïì½Ï´ó
   LED0=1;
   LED1=0;
   openMVControl=0;
//   TIM4_Init(20000-1,72-1);  
   while(1)
   {  
      if(Stop_Flag)
         {
            THROTTLE=THROTTLE_MIN;  //¹Ø±ÕÓÍÃÅ
            subject_flag=0;  //½áÊøÊÖ¶¯¿ØÖÆ×´Ì¬
            Stop_Flag=0; //¸´Î»ÏµÍ³
            Take_flag=1; 
            Land_flag=0;
         }
         
      if(subject_flag==1)  //Èç¹ûÏÖÔÚÊÇÔÚ×öµÚÒ»Ìâ
      {
         openMVControl=1;  //À­¸ßÇı¶¯½Å£¬±íÊ¾ÔÚÕÒÔ²
         if(Take_flag)  //Æô¶¯·ÉĞĞÆ÷
         {
            Flight_control_Unlock();//½âËø·É¿Ø
            Take_off(&HStruct);  //Æğ·É
            Take_flag=0;
            for(i=0;i<100;i++)
            {
               High_control(&HStruct,high);  //ÎÈ¶¨¸ß¶È
               delay_ms(60);
               if(Stop_Flag)
                  break;
            }
         }  //Ö´ĞĞÍêÆğ·ÉÖ¸Áîºó·É»ú¾Í²»ÔÚÊ¹ÓÃÆğ·Éº¯Êı
         //Chase_Circle(&XStruct,&YStruct);  //ĞŞÕı×ø±ê£¬±£Ö¤ÄÜ¹»½µÂäÔÚAÇøÓò
         High_control(&HStruct,high);  //ÎÈ¶¨¸ß¶È
//         if((cir_Point_x-XMiddle)<5&&(cir_Point_y-YMiddle)<5)  //µ±²îÖµĞ¡ÓÚÎå¸öÏñËØµãÊ±£¬½µÂä
//         {
//            Land_flag=1;
//            for(i=0;i<100;i++)
//            {
//               High_control(&HStruct,high);  //ÎÈ¶¨¸ß¶È
//               delay_ms(20);
//               if(Stop_Flag)
//                  break;
//            }
//         }
//         if(Land_flag)  //µ±½µÂä±êÖ¾Î»ÖÃ1Ê±¿ªÊ¼Ö´ĞĞ½µÂäº¯Êı
//         {
//            Land(&HStruct);
//            Take_flag=1;
//            Land_flag=0;
//            subject_flag=0;
//            openMVControl=0;  //À­µÍÇı¶¯½Å£¬½«openMV»Ø¹éÄ¬ÈÏÄ£Ê½
//         }
      }
      else if(subject_flag==2)  //Èç¹ûÏÖÔÚÊÇÔÚ×öµÚ¶şÌâ
      {
         openMVControl = 0;  //À­µÍÇı¶¯½Å£¬¿ªÊ¼Ñ°ÏßÄ£Ê½
         if(Take_flag)  //Æô¶¯·ÉĞĞÆ÷
         {
            Flight_control_Unlock();//½âËø·É¿Ø
            Take_off(&HStruct);  //Æğ·É
            Take_flag=0;
            for(i=0;i<100;i++)
            {
               High_control(&HStruct,high);  //ÎÈ¶¨¸ß¶È
               delay_ms(60);
               if(Stop_Flag)
                  break;
            }
         }  //Ö´ĞĞÍêÆğ·ÉÖ¸Áîºó·É»ú¾Í²»ÔÚÊ¹ÓÃÆğ·Éº¯Êı
         High_control(&HStruct,high);  //ÎÈ¶¨¸ß¶È
         if(uFindLin_flag)  //Èç¹û´¦ÓÚÑ°ÏßÄ£Ê½
            Traction_control(&XStruct,&YStruct,&ZStruct);  //Ñ­¼£
         else if(uFindCir_flag)//Èç¹û´¦ÓÚ×·Ô²Ä£Ê½
            Chase_Circle(&XStruct,&YStruct);//×·Ô²
         else if(uLanding)  //Òì³£Çé¿ö
            Land_flag=1;    //Æô¶¯½µÂäº¯Êı
         if(uFindCir_flag&&((cir_Point_x-XMiddle)<5&&(cir_Point_y-YMiddle)<5))  //Èç¹û´¦ÓÚ×·Ô²Ä£Ê½ÇÒ×ø±ê²îÖµĞ¡ÓÚÎå¸öÏñËØµã£¬Ê¹ÄÜ½µÂäº¯Êı
         {
            Land_flag=1;
            for(i=0;i<100;i++)
            {
               High_control(&HStruct,high);  //ÎÈ¶¨¸ß¶È
               delay_ms(20);
               if(Stop_Flag)
                  break;
            }
         }
         if(Land_flag)  //µ±½µÂä±êÖ¾Î»ÖÃ1Ê±¿ªÊ¼Ö´ĞĞ½µÂäº¯Êı
         {
            Land(&HStruct);
            Take_flag=1;
            Land_flag=0;
            uLanding=0;  //¸´Î»Òì³£×´Ì¬±êÖ¾Î»
            subject_flag=0;
            openMVControl=1;  //À­¸ßÇı¶¯½Å£¬ÍË³öÑ°Ô²Ëø¶¨£¬½øÈëÑ°Ô²Ä£Ê½
         }
      }
      else if(subject_flag==3)  //Èç¹ûÏÖÔÚÊÇÔÚ×öµÚÈıÌâ
      {
         openMVControl = 0;  //À­µÍÇı¶¯½Å£¬¿ªÊ¼Ñ°ÏßÄ£Ê½
         if(Take_flag)  //Æô¶¯·ÉĞĞÆ÷
         {
            Flight_control_Unlock();//½âËø·É¿Ø
            Take_off(&HStruct);  //Æğ·É
            Take_flag=0;
            for(i=0;i<100;i++)
            {
               High_control(&HStruct,high);  //ÎÈ¶¨¸ß¶È
               delay_ms(60);
               if(Stop_Flag)
                  break;
            }
         }  //Ö´ĞĞÍêÆğ·ÉÖ¸Áîºó·É»ú¾Í²»ÔÚÊ¹ÓÃÆğ·Éº¯Êı
         Straight_line_judgment();  //Ïß¶ÎĞ£×¼
         if(Number==0||Number>2)
            HStruct.Goal=0.6;
         else if(Number==2)
            HStruct.Goal=1.5;
         High_control(&HStruct,high);  //ÎÈ¶¨¸ß¶È
         if(uFindLin_flag)  //Èç¹û´¦ÓÚÑ°ÏßÄ£Ê½
            Traction_control(&XStruct,&YStruct,&ZStruct);  //Ñ­¼£
         else if(uFindCir_flag)//Èç¹û´¦ÓÚ×·Ô²Ä£Ê½
            Chase_Circle(&XStruct,&YStruct);//×·Ô²
         else if(uLanding)  //Òì³£Çé¿ö
            Land_flag=1;    //Æô¶¯½µÂäº¯Êı
         if(uFindCir_flag&&((cir_Point_x-XMiddle)<5&&(cir_Point_y-YMiddle)<5))  //Èç¹û´¦ÓÚ×·Ô²Ä£Ê½ÇÒ×ø±ê²îÖµĞ¡ÓÚÎå¸öÏñËØµã£¬Ê¹ÄÜ½µÂäº¯Êı
         {
            Land_flag=1;
            for(i=0;i<100;i++)
            {
               High_control(&HStruct,high);  //ÎÈ¶¨¸ß¶È
               delay_ms(20);
               if(Stop_Flag)
                  break;
            }
         }
         if(Land_flag)  //µ±½µÂä±êÖ¾Î»ÖÃ1Ê±¿ªÊ¼Ö´ĞĞ½µÂäº¯Êı
         {
            Land(&HStruct);
            Take_flag=1;
            Land_flag=0;
            uLanding=0;  //¸´Î»Òì³£×´Ì¬±êÖ¾Î»
            subject_flag=0;
            openMVControl=1;  //À­¸ßÇı¶¯½Å£¬ÍË³öÑ°Ô²Ëø¶¨£¬½øÈëÑ°Ô²Ä£Ê½
            Number=0;   //³¤Ïß¹éÎ»
         }
      }
      else if(subject_flag == 4)//ÊÖ¶¯¿ØÖÆ
      {
         if(Unlock_Flag)
         {
            Flight_control_Unlock();
            Unlock_Flag=0;
         }
         if(Rise_Flag)
         {
            if(THROTTLE<THROTTLE_MAX)
            {
               THROTTLE+=10;  //ÂıÂıÀ­¸ßÓÍÃÅ
               Rise_Flag=0;   //¸´Î»ÓÍÃÅÔö¼Ó±êÖ¾Î
            }
         }
         
         if(Down_Flag)     
         {
            if(THROTTLE>THROTTLE_MIN)
            {
               THROTTLE-=10;  //ÂıÂı½µµÍÓÍÃÅ
               Down_Flag=0;   //¸´Î»ÓÍÃÅÔö¼Ó±êÖ¾Î»
            }
         }
         
         if(Left_Flag)  
         {
            if(ROLL>1350)  //ÇãĞ±½ÇÏŞ·ù
               ROLL-=50;   //ÇãĞ±½ÇÎ¢Ôö
            else
               ROLL=1350;  
            Left_Flag=0;
         }
         else if(ROLL<ROLL_MIDDLE)
            ROLL++;        //Èç¹ûÃ»ÓĞ×ó×ª±êÖ¾Î»£¬ÂıÂı¸´Î»×ó×ª¿ØÖÆ¼Ä´æÆ÷
         
         if(Right_Flag)  
         {
            if(ROLL<1650)  //ÇãĞ±½ÇÏŞ·ù
               ROLL+=50;   //ÇãĞ±½ÇÎ¢Ôö
            else
               ROLL=1650;  
            Right_Flag=0;
         }
         else if(ROLL>ROLL_MIDDLE)
            ROLL--;        //Èç¹ûÃ»ÓĞÓÒ×ª±êÖ¾Î»£¬ÂıÂı¸´Î»ÓÒ×ª¿ØÖÆ¼Ä´æÆ÷
         
         if(Forward_Flag)  
         {
            if(PITCH<1650)  //ÇãĞ±½ÇÏŞ·ù
               PITCH+=50;   //ÇãĞ±½ÇÎ¢Ôö
            else
               PITCH=1650;  
            Forward_Flag=0;
         }
         else if(PITCH>PITCH_MIDDLE)
            PITCH--;        //Èç¹ûÃ»ÓĞÇ°½ø±êÖ¾Î»£HÂıÂı¸´Î»Ç°½ø¿ØÖÆ¼Ä´æÆ÷
         
         if(Back_Flag)  
         {
            if(PITCH>1350)  //ÇãĞ±½ÇÏŞ·ù
               PITCH-=50;   //ÇãĞ±½ÇÎ¢Ôö
            else
               PITCH=1350;  
            Back_Flag=0;
         }
         else if(PITCH<PITCH_MIDDLE)
            PITCH++;        //Èç¹ûÃ»ÓĞºóÍË±êÖ¾     ÂıÂı¸´Î»ºóÍË¿ØÖÆ¼Ä´æÆ÷
         
         if(LeftHand_Flag)
         {
            if(YAW>1350)    //ÇãĞ±½ÇÏŞ·ù
               YAW-=50;     //ÇãĞ±½ÇÎ¢Ôö
            else
               YAW=1350;
            LeftHand_Flag=0;
         }
         else if(YAW<YAW_MIDDLE)
            YAW++;        //Èç¹ûÃ»ÓĞ×óĞı±êÖ¾Î»£¬¸´Î»×óĞı¿ØÖÆ¼Ä´æÆ÷
         
         if(RightHand_Flag)
         {
            if(YAW<1650)    //ÇãĞ±½ÇÏŞ·ù
               YAW+=50;     //ÇãĞ±½ÇÎ¢Ôö
            else
               YAW=1650;
            RightHand_Flag=0;
         }
         else if(YAW>YAW_MIDDLE)
            YAW--;        //Èç¹ûÃ»ÓĞÓÒĞı±êÖ¾Î»£¬¸´Î»ÓÒĞı¿ØÖÆ¼Ä´æÆ÷
         
         if(Reset_Flag)  //Èç¹ûÊÕµ½¸´Î»ÇãĞı½Ç±êÖ¾£¬½áÊø¶ÔÈıÖáµÄPWM²¨Êä³ö
         {
            YAW=YAW_MIDDLE;  //¸´Î»Æ«º½
            PITCH=PITCH_MIDDLE;  //¸´Î»¸©Ñö
            ROLL=ROLL_MIDDLE;  //¸´Î»ºá¹ö
         }
      }
      if(subject_flag==0)
      {
         YAW=YAW_MIDDLE;  //¸´Î»Æ«º½
         PITCH=PITCH_MIDDLE;  //¸´Î»¸©Ñö
         ROLL=ROLL_MIDDLE;  //¸´Î»ºá¹ö
         if(THROTTLE>THROTTLE_MIN)
            THROTTLE-=10;  //Öğ½¥½µµÍÓÍÃÅÖ±ÖÁÓÍÃÅ×îĞ¡
         delay_ms(10);
      }
      if(i>=10)
      {
         LED0=!LED0;
         LED1=!LED1;
         i=0;
      }
      i++;
      delay_ms(50);
   }
}
 
 


 
/*
 *
 */
#include "serv.h"
static char TAG[] = "task1";

void vTask_test_Queue( void * pvParameters )
{
    char c;
    struct data mess;
    strcat(    mess.str , "01askCode1 hello Word");
   ESP_LOGI(TAG, "start");
 for( ;; )
 {
     if( xQueue1 != 0 )
         {
             /* Send an unsigned long.  Wait for 10 ticks for space to become
             available if necessary. */

             if( xQueueSendToBack( xQueue1, ( void * ) &mess,0  ))
             {	mess.len=20;
            	 c=mess.str[1]; mess.str[1]=mess.str[0];mess.str[0]=c;
                 /* Failed to post the message, even after 10 ticks. */
        	 ESP_LOGI(TAG, " %s ",mess.str);
             }

         }

 }
}

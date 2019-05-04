/*
 *
 */
#include "serv.h"
//static char TAG[] = "send";
/*int  num(char st )
    {
    for (int i = 0; i < sizeof(st) / sizeof(st[0]); i++)
	{
	if (st[i] == '\n')
	    {
		return i+1;
		break;
	    }
	}
    }*/
void Send_Q(float x, float y, float z)
    {
    struct data mess;
  //  struct data mess_mess;
    sprintf(mess.str, "S%4.2f;%3.2f;%3.2f;\n", x, y, z);
    for (int i = 0; i < sizeof(mess.str) / sizeof(mess.str[0]); i++)
	{
	if (mess.str[i] == '\n')
	    {
	    mess.len=i+1;
		break;
	    }
	}
    //   ESP_LOGI(TAG, "%s", mess.str);
    if (xQueue1 != 0)
	{

	if (xQueueSendToFront(xQueue1, (void * ) &mess, 0))
	    {
	    ///    ESP_LOGI(TAG, "xQueueSendToBack");
	    //    ESP_LOGI(TAG, "%s ", mess.str);
	    }
	/*else
	 {
	 xQueueReceive(xQueue1, &(mess_mess), 0); // Error occurred during receiving

	 }*/

	}

    }

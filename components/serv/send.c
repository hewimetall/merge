/*
 *
 */
#include "serv.h"
static char TAG[] = "send";

void Send_Q(float x, float y, float z)
    {
    struct data mess;
    strcat(mess.str, "01askCode1 hello Word");
    mess.len = 20;
    ESP_LOGI(TAG, "test");
    if (xQueue1 != 0)
	{
	if (xQueueSendToBack(xQueue1, (void * ) &mess, 0))
	    {
	    ESP_LOGI(TAG, "xQueueSendToBack");

	    ESP_LOGI(TAG, " %s ", mess.str);
	    }

	}

    }

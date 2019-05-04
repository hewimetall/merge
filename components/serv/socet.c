#include "serv.h"

static char TAG[] = "socket_server";
static int sock;
static struct sockaddr_in source_addr;
#define CONFIG_LOG_DEFAULT_LEVEL 3

void socket_server(void *pvParameters)
{
	struct data mess;

	char rx_buffer[128];
	char addr_str[128];
	int addr_family;
	int ip_protocol;
	EventBits_t EventBits;
	EventBits = xEventGroupWaitBits(wifi_group, /* The event group being tested. */
	BIT_0, /* The bits within the event group to wait for. */
	pdTRUE, /* BIT_0 & BIT_4 should be cleared before returning. */
	pdFALSE, /* Don't wait for both bits, either bit will do. */
	portMAX_DELAY);/* Wait a maximum of 100ms for either bit to be set. */
	ESP_LOGI(TAG, "Socket Start");

	while (1)
	{
		// Filling server information
		struct sockaddr_in dest_addr;
		dest_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		dest_addr.sin_family = AF_INET;
		dest_addr.sin_port = htons(PORT_NUMBER);
		addr_family = AF_INET;
		ip_protocol = IPPROTO_IP;
		inet_ntoa_r(dest_addr.sin_addr, addr_str, sizeof(addr_str) - 1);

		sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
		if (sock < 0)
		{
			ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
			break;
		}
		ESP_LOGI(TAG, "Socket created");
/////////////////////////////////////////////////////////////////////////////////////////////
		xEventGroupSetBits(wifi_group,    // The event group being updated.
				BIT_1);    // The bits being set.
/////////////////////////////////////////////////////////////////////////////////////////////

		int err = bind(sock, (struct sockaddr *) &dest_addr, sizeof(dest_addr));
		if (err < 0)
		{
			ESP_LOGE(TAG, "Socket unable to bind: errno %d", errno);
		}
		ESP_LOGI(TAG, "Socket bound, port %d", PORT_NUMBER);

		while (1)
		{

			socklen_t socklen = sizeof(source_addr);
			/* get Socet_Client via recvfrom in source_addr*/
			int len = recvfrom(sock, rx_buffer, sizeof(rx_buffer) - 1, 0,
					(struct sockaddr *) &source_addr, &socklen);
			if (len < 0)
			{
				ESP_LOGE(TAG, "recv failed: errno %d", errno);
				break;
			}
			else if (rx_buffer[0]=='t') {
				ESP_LOGE(TAG, " RE");

			}
			// Data received
			else
			{
				rx_buffer[len] = 0; // Null-terminate whatever we received and treat like a string...
				ESP_LOGI(TAG, "%s", rx_buffer);
				while (1)
				{
					if (xQueueReceive(xQueue1, &(mess), portMAX_DELAY)) // Error occurred during receiving
					{
						ESP_LOGI(TAG, " %s:%i ",mess.str,mess.len);
						mess.str[mess.len]=0;
						mess.str[0]=0;
						int err = sendto(sock,mess.str,mess.len, 0,
								(struct sockaddr *) &source_addr,
								sizeof(source_addr));
						//	vTaskDelay(10 / portTICK_PERIOD_MS);
						if (err < 0)
						{
							ESP_LOGE(TAG,
									"Error occurred during sending: errno %d",
									errno);
							break;
						}
					}
				}
			}

		}

		if (sock != -1)
		{
			ESP_LOGE(TAG, "Shutting down socket and restarting...");
			shutdown(sock, 0);
			close(sock);
		}
	}
	vTaskDelete(NULL);
}


/**
* A simple network by RF24
* Author : Yoshino-s
* Date : 2017-9-14
*/

#include "general.h"

#define FORWARD_SSID default_SSID

namespace Sensor {
	var(delay_time, 500);

	node I = {
		.father = NULL,
		.sons = {},
		.son_number = 0,
		.type = sensor
	};

	void setup() {
		Serial.begin(9600);
		printf_begin();

		radio.begin();

		radio.enableDynamicPayloads();

		radio.setRetries(15, 15);

		radio.openWritingPipe(default_server_pipe);
		radio.openReadingPipe(1, default_pipe);

		DEBUG("Start Listening.\n\r");
		radio.startListening();

#ifdef _DEBUG
		radio.printDetails();
#endif // _DEBUG
	}
	void loop()
	{
		auto send_buffer_size = strlen(SSID);
		auto send_buffer = SSID;

		radio.stopListening();

		DEBUG("Boardcast, SSID : %s.\n\r", send_buffer);
		radio.write(send_buffer, send_buffer_size);

		radio.startListening();

		unsigned long started_waiting_at = millis();
		bool timeout = false;
		while (!radio.available() && !timeout)
			if (millis() - started_waiting_at > delay_time)
				timeout = true;

		if (timeout)
		{
			printf("Can't get .\n\r");
		}
		else
		{
			uint8_t len = radio.getDynamicPayloadSize();
			radio.read(receive_payload, len);

			receive_payload[len] = 0;

			printf("Got data size=%i value=%s\n\r", len, receive_payload);
		}
	}
}
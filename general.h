/**
* General part of simple network by RF24
* Author : Yoshino-s
* Date : 2017-9-14
*/
#include <Arduino.h>


#include <SPI.h>
#include "printf.h"
#include "RF24.h"
#include "nRF24L01.h"

#include <avr/sleep.h>
#include <avr/power.h>

#include "wdt_sleep.h"
#include "try.h"

RF24 radio(9, 10);

auto default_SSID = "default";

typedef enum { server, sender, listener, transmitter, invalid } role_e;

typedef struct _node{
	struct _node* father;
	struct _node* sons[10];
	uint8_t son_number;
	role_e type;
	unsigned char ip[4];
} node;

//
// Topology
//

// Radio pipe addresses for the 2 nodes to communicate.
//Use pipes[0] to Write and use pipes[1] to Read
const uint64_t default_pipe =        0xF0F0F0F0F0F0;

const uint64_t default_server_pipe = 0xC0A800010000;

const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

//
// Payload
//

const int min_payload_size = 4;
const int max_payload_size = 32;

char receive_payload[max_payload_size + 1]; // +1 to allow room for a terminating NULL char

uint64_t ipToPipe(unsigned char ip[4]) {

}
/*
 * main.c
 *
 * Copyright 2011 Thomas Buck <xythobuz@me.com>
 * Copyright 2011 Max Nuding <max.nuding@gmail.com>
 * Copyright 2011 Felix Bäder <baeder.felix@gmail.com>
 *
 * This file is part of LED-Cube.
 *
 * LED-Cube is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LED-Cube is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LED-Cube.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#include "adc.h"
#include "eq.h"

#ifndef F_CPU
#define F_CPU 16000000L
#endif

void blinkStatus(void) {
	uint8_t i, mem[7] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

	PORTB |= (1 << PB2);
	PORTB &= ~(1 << PB1);
	eqLed(mem);
	_delay_ms(250);
	PORTB &= ~(1 << PB2);
	PORTB |= (1 << PB1);
	for (i = 0; i < 7; i++) {
		mem[i] = 0x00;
	}
	eqLed(mem);
	_delay_ms(250);
}

int main(void) {
	uint8_t *music;

	DDRB = 0x3F;
	DDRC = 0x0C;
	DDRD = 0xFF;
	
	adcInit();
	equalizerInit();

	blinkStatus();
	blinkStatus();

	while (1) {
		music = equalizerGet();

		free(music);

		// Heartbeat
		PORTB ^= (1 << PB1);
		_delay_ms(1); // Everything locks if this is removed :(
	}

	return 0;
}

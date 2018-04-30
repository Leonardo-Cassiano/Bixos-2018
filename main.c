#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "hardware.h"
#include "motors.h"
#include "sensors.h"
#include "utils.h"
#include "timer.h"

#define v0Esquerda   100
#define v0Direita 	-100

// 0 1 2 3 4 5 6

int main(void) {
	int diferenca;
	int vEsquerda;
	int vDireita;
	hardware_init();
	for (;;) {
		sensor_update();

		diferenca = (sensors[6]+sensors[5]+sensors[4])-(sensors[0]+sensors[1]+sensors[2]);

		if (v0Esquerda + diferenca > 255) {
			vEsquerda = 255
		}
		else if (v0Esquerda + diferenca < -255) {
			vEsquerda = -255
		}
		else {
			vEsquerda = v0Esquerda + diferenca
		}
		if (v0Direita + diferenca > 255) {
			vDireita = 255
		}
		else if (v0Direita + diferenca < -255) {
			vDireita = -255
		}
		else {
			vDireita = v0Direita + diferenca
		}

		set_motors(vEsquerda,vDireita)

		_delay_ms(10);
	}
	return 0;
}

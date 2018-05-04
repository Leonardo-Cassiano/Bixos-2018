#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "hardware.h"
#include "motors.h"
#include "sensors.h"
#include "utils.h"
#include "timer.h"

#define v0Esquerda   150
#define v0Direita 	 150
#define limite       20
#define incremento   30

// 0 1 2 3 4 5 6

int main(void) {
	int diferenca;
	int vEsquerda;
	int vDireita;
	hardware_init();
    vDireita = v0Direita;
    vEsquerda = v0Esquerda;
    set_motors(v0Esquerda,v0Direita);
	for (;;) {
		sensor_update();

		diferenca = (sensors[6]+sensors[5]+sensors[4])-(sensors[0]+sensors[1]+sensors[2]);

        if (abs(diferenca) > limite){ //define mudança da velocidade da roda caso entre na linha
            if (diferenca < 0){
               vEsquerda = v0Esquerda + incremento;
               vDireita = v0Direita - incremento;
               set_motors(vEsquerda,vDireita);
            }
            else{

                vDireita = v0Direita + incremento;
                vEsquerda = v0Esquerda - incremento; //substituir por diferenca dividido por constante
                set_motors(vEsquerda,vDireita);

            }
        }



	}
	return 0;
}



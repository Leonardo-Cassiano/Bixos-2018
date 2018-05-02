#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "utils.h"
#include "sensors.h"
#include "motors.h"
#include "timer.h"

#define velocidadeEsq 100
#define velocidadeDir -100
#define limite 500

int main () {
    int diferenca;
    motors_init();
    timer_init();
    sensors_init();
    _delay_ms(5000);
    for (;;) {
        update_line_sensors();
        update_distance_sensors();
        diferenca = distance_sensors[0] - distance_sensors[1];
        motors (velocidadeEsq - diferenca , velocidadeDir + diferenca);
        if(limite < line_sensors[0]){
            motors(velocicadeEsq - diferenca , 0 );  //depois de usar a diferenca entre valores comparado a um threshold
            _delay_ms(500);

        }
        else if(limite < line_sensors[1]){
            motors(0 , velocidadeDir + diferenca);
            _delay_ms(500);
        }
        else if(line_sensors[0] > limite && line_sensors[1] > limite){
            motors(-(velocidadeEsq - diferenca) , -(velocidadeDir + diferenca));
            _delay_ms(500);
        }

    }
    return 0;
}

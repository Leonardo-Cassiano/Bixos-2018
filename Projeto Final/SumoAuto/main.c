#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "utils.h"
#include "sensors.h"
#include "motors.h"
#include "timer.h"
#include "usart.h"


#define velocidadeEsq 90
#define velocidadeDir 90
#define limite 200
#define visao 1000
#define incremento 30

int main () {
    int diferenca;
    motors_init();
    timer_init();
    sensors_init();
    _delay_ms(5000);
    motors (velocidadeEsq, velocidadeDir);
    for (;;) {
        update_line_sensors();
        update_distance_sensors();


        // controle com seguidor de linha

        if(line_sensors[0] < limite && line_sensors[1] < limite){ // encontrou a linha de frente
            motors(-(velocidadeEsq + incremento) , -(velocidadeDir + incremento));
            _delay_ms(100);
            motors(-(velocidadeEsq + incremento), velocidadeDir + incremento);
            _delay_ms(100);
        }
        else if(limite > line_sensors[0]){ // encontrou a linha a esquerda
            motors(velocidadeEsq + incremento ,0 );
            _delay_ms(200);
        }
        else if(limite > line_sensors[1]){ // encontrou a linha a direita
            motors(0 , velocidadeDir + incremento);
            _delay_ms(200);
        }

        else {
            diferenca = distance_sensors[0] - distance_sensors[1];

            // controle com sensor de distancia

            if (abs(diferenca) > visao){
                if (diferenca > 0){
                    motors(velocidadeEsq, velocidadeDir + incremento);
                }
                else if (diferenca < 0){
                    motors(velocidadeEsq + incremento, velocidadeDir);
                }
            }
            else{
                motors(velocidadeEsq + incremento, velocidadeDir + incremento);
            }
        _delay_ms(20);




        }

    }
    return 0;
}

#ifndef LIB_RELOGIO_H
#define LIB_RELOGIO_H

#include <stdint.h>

extern volatile uint8_t task_incrementa_horas_alarme = 0;
extern volatile uint8_t task_decrementa_horas_alarme = 0;
extern volatile uint8_t task_incrementa_minutos_alarme = 0;
extern volatile uint8_t task_decrementa_minutos_alarme = 0;

void calculaHora();
void incrementaMinutoRelogio();
void decrementaMinutoRelogio();
void incrementaHoraRelogio();
void decrementaHoraRelogio();
void taskRelogio();
void taskAjusteMinutos();
void taskAjusteHoras();
void taskAlarmeMinutos();
void taskAlarmeHoras();

#endif
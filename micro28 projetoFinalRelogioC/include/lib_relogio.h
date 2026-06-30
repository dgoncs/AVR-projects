#ifndef LIB_RELOGIO_H
#define LIB_RELOGIO_H

#include <stdint.h>

extern volatile uint8_t task_incrementa_horas_relogio;
extern volatile uint8_t task_decrementa_horas_relogio;
extern volatile uint8_t task_incrementa_minutos_relogio;
extern volatile uint8_t task_decrementa_minutos_relogio;
extern volatile uint8_t task_incrementa_horas_alarme;
extern volatile uint8_t task_decrementa_horas_alarme;
extern volatile uint8_t task_incrementa_minutos_alarme;
extern volatile uint8_t task_decrementa_minutos_alarme;

void taskRelogio();
void taskMostraRelogio();
void taskAjusteMinutos();
void taskAjusteHoras();
void taskAlarmeMinutos();
void taskAlarmeHoras();

#endif

#include <lib_display7s.h>
#include <lib_macros.h>
#include <avr/io.h>
#include <lib_botoes.h>

static volatile uint16_t contRelogio = 0;
static volatile uint16_t contAlarme = 0;
static volatile uint8_t minuto_unidade = 0;
static volatile uint8_t minuto_dezena = 0;
static volatile uint8_t hora_unidade = 0;
static volatile uint8_t hora_dezena = 0;
static volatile uint8_t alarme_minuto_unidade = 0;
static volatile uint8_t alarme_minuto_dezena = 0;
static volatile uint8_t alarme_hora_unidade = 2;
static volatile uint8_t alarme_hora_dezena = 1;
volatile uint8_t alarme_on = 0;
volatile uint8_t task_incrementa_horas_relogio = 0;
volatile uint8_t task_decrementa_horas_relogio = 0;
volatile uint8_t task_incrementa_minutos_relogio = 0;
volatile uint8_t task_decrementa_minutos_relogio = 0;
volatile uint8_t task_incrementa_horas_alarme = 0;
volatile uint8_t task_decrementa_horas_alarme = 0;
volatile uint8_t task_incrementa_minutos_alarme = 0;
volatile uint8_t task_decrementa_minutos_alarme = 0;

void recalculaHora()
{
    minuto_unidade++;

    if (minuto_unidade >= 10)
    {
        minuto_unidade = 0;
        minuto_dezena++;

        if (minuto_dezena >= 6)
        {
            minuto_dezena = 0;
            hora_unidade++;

            if (hora_unidade >= 10)
            {
                hora_unidade = 0;
                hora_dezena++;
                return;
            }

            // caso especial 23 -> 00
            if (hora_dezena >= 2 && hora_unidade >= 4)
            {
                minuto_unidade = 0;
                minuto_dezena = 0;
                hora_unidade = 0;
                hora_dezena = 0;
            }
        }
    }
}

void incrementaMinutoRelogio()
{
    minuto_unidade++;

    if (minuto_unidade >= 10)
    {
        minuto_unidade = 0;
        minuto_dezena++;

        // caso especial 59 -> 00
        if (minuto_dezena >= 6)
        {
            minuto_dezena = 0;
        }
    }
}

void decrementaMinutoRelogio()
{
    if (minuto_unidade <= 0)
    {
        minuto_unidade = 9;

        // caso especial 00 -> 59
        if (minuto_dezena <= 0)
        {
            minuto_dezena = 5;
            return;
        }

        minuto_dezena--;
        return;
    }

    minuto_unidade--;
}

void incrementaHoraRelogio()
{
    hora_unidade++;

    if (hora_unidade >= 10)
    {
        hora_unidade = 0;
        hora_dezena++;
        return;
    }

    // caso especial 23 -> 00
    if (hora_dezena >= 2 && hora_unidade >= 4)
    {
        hora_unidade = 0;
        hora_dezena = 0;
    }
}

void decrementaHoraRelogio()
{
    if (hora_unidade <= 0)
    {
        // caso especial 00 -> 23
        if (hora_dezena <= 0)
        {
            hora_dezena = 2;
            hora_unidade = 3;
            return;
        }

        hora_unidade = 9;
        hora_dezena--;
        return;
    }

    hora_unidade--;
}

void incrementaMinutoAlarme()
{
    alarme_minuto_unidade++;

    if (alarme_minuto_unidade >= 10)
    {
        alarme_minuto_unidade = 0;
        alarme_minuto_dezena++;

        // caso especial 59 -> 00
        if (alarme_minuto_dezena >= 6)
        {
            alarme_minuto_dezena = 0;
        }
    }
}

void decrementaMinutoAlarme()
{
    if (alarme_minuto_unidade <= 0)
    {
        alarme_minuto_unidade = 9;

        // caso especial 00 -> 59
        if (alarme_minuto_dezena <= 0)
        {
            alarme_minuto_dezena = 5;
            return;
        }

        alarme_minuto_dezena--;
        return;
    }

    alarme_minuto_unidade--;
}

void incrementaHoraAlarme()
{
    alarme_hora_unidade++;

    if (alarme_hora_unidade >= 10)
    {
        alarme_hora_unidade = 0;
        alarme_hora_dezena++;
        return;
    }

    // caso especial 23 -> 00
    if (alarme_hora_dezena >= 2 && alarme_hora_unidade >= 4)
    {
        alarme_hora_unidade = 0;
        alarme_hora_dezena = 0;
    }
}

void decrementaHoraAlarme()
{
    if (alarme_hora_unidade <= 0)
    {
        // caso especial 00 -> 23
        if (alarme_hora_dezena <= 0)
        {
            alarme_hora_dezena = 2;
            alarme_hora_unidade = 3;
            return;
        }

        alarme_hora_unidade = 9;
        alarme_hora_dezena--;
        return;
    }

    alarme_hora_unidade--;
}

void taskAlarme()
{
    if (contAlarme >= 999)
    {
        contAlarme = 0;
    }
    else
    {
        contAlarme++;
    }

    if (alarme_on <= 0)
    {
        if (alarme_minuto_unidade == minuto_unidade && alarme_minuto_dezena == minuto_dezena && alarme_hora_unidade == hora_unidade && alarme_hora_dezena == hora_dezena)
        {
            alarme_on = 1;
            return;
        }

        // bitClear(PORTD, PD3);
        bitClear(PORTB, PB5);
        return;
    }

    if (contAlarme >= 500)
    {
        // bitClear(PORTD, PD3);
        bitClear(PORTB, PB5);
        return;
    }

    bitSet(PORTB, PB5);
    return;
}

void taskRelogio()
{
    if (contRelogio >= 999)
    {
        contRelogio = 0;
        recalculaHora();
        return;
    }

    contRelogio++;
}

void taskMostraRelogio()
{
    dig7a = hora_dezena;
    dig7c = minuto_dezena;
    dig7d = minuto_unidade;

    if (contRelogio >= 500)
    {
        dig7b = hora_unidade + 11;
        return;
    }

    dig7b = hora_unidade;
}

void taskAjusteMinutos()
{
    if (task_decrementa_minutos_relogio >= 1)
    {
        task_decrementa_minutos_relogio = 0;
        decrementaMinutoRelogio();
    }
    if (task_incrementa_minutos_relogio >= 1)
    {
        task_incrementa_minutos_relogio = 0;
        incrementaMinutoRelogio();
    }

    dig7a = hora_dezena;
    dig7b = hora_unidade;

    if (contRelogio >= 500)
    {
        dig7c = 10;
        dig7d = 10;
    }
    else
    {
        dig7c = minuto_dezena;
        dig7d = minuto_unidade;
    }

    if (contRelogio >= 999)
    {
        contRelogio = 0;
        return;
    }

    contRelogio++;
}

void taskAjusteHoras()
{
    if (task_decrementa_horas_relogio >= 1)
    {
        task_decrementa_horas_relogio = 0;
        decrementaHoraRelogio();
    }
    if (task_incrementa_horas_relogio >= 1)
    {
        task_incrementa_horas_relogio = 0;
        incrementaHoraRelogio();
    }

    if (contRelogio >= 500)
    {
        dig7a = 10;
        dig7b = 10;
    }
    else
    {
        dig7a = hora_dezena;
        dig7b = hora_unidade;
    }

    dig7c = minuto_dezena;
    dig7d = minuto_unidade;

    if (contRelogio >= 999)
    {
        contRelogio = 0;
        return;
    }

    contRelogio++;
}

void taskAlarmeMinutos()
{
    if (task_decrementa_minutos_alarme >= 1)
    {
        task_decrementa_minutos_alarme = 0;
        decrementaMinutoAlarme();
    }
    if (task_incrementa_minutos_alarme >= 1)
    {
        task_incrementa_minutos_alarme = 0;
        incrementaMinutoAlarme();
    }

    dig7a = alarme_hora_dezena;
    dig7b = alarme_hora_unidade + 11;

    if (contAlarme >= 500)
    {
        dig7c = 10;
        dig7d = 10;
    }
    else
    {
        dig7c = alarme_minuto_dezena;
        dig7d = alarme_minuto_unidade;
    }

    if (contAlarme >= 999)
    {
        contAlarme = 0;
        return;
    }

    contAlarme++;
}

void taskAlarmeHoras()
{
    if (task_decrementa_horas_alarme >= 1)
    {
        task_decrementa_horas_alarme = 0;
        decrementaHoraAlarme();
    }
    if (task_incrementa_horas_alarme >= 1)
    {
        task_incrementa_horas_alarme = 0;
        incrementaHoraAlarme();
    }

    if (contAlarme >= 500)
    {
        dig7a = 10;
        dig7b = 21;
    }
    else
    {
        dig7a = alarme_hora_dezena;
        dig7b = alarme_hora_unidade + 11;
    }

    dig7c = alarme_minuto_dezena;
    dig7d = alarme_minuto_unidade;

    if (contAlarme >= 999)
    {
        contAlarme = 0;
        return;
    }

    contAlarme++;
}

#include <lib_display7s.h>

volatile uint8_t minuto_unidade = 0;
volatile uint8_t minuto_dezena = 0;
volatile uint8_t hora_unidade = 0;
volatile uint8_t hora_dezena = 0;
volatile uint8_t alarme_minuto_unidade = 0;
volatile uint8_t alarme_minuto_dezena = 0;
volatile uint8_t alarme_hora_unidade = 0;
volatile uint8_t alarme_hora_dezena = 0;
static volatile uint16_t contRelogio = 0;
static volatile uint16_t contAlarme = 0;
volatile uint8_t task_incrementa_horas_relogio = 0;
volatile uint8_t task_decrementa_horas_relogio = 0;
volatile uint8_t task_incrementa_minutos_relogio = 0;
volatile uint8_t task_decrementa_minutos_relogio = 0;
volatile uint8_t task_incrementa_horas_alarme = 0;
volatile uint8_t task_decrementa_horas_alarme = 0;
volatile uint8_t task_incrementa_minutos_alarme = 0;
volatile uint8_t task_decrementa_minutos_alarme = 0;

void taskVarreduraDisplay()
{
    if (contVarredura >= 5)
    {
        contVarredura = 0;
        trocaDisplay();
    }
    else
    {
        contVarredura++;
    }
}

void calculaHora()
{
    static uint8_t minuto_unidade = 0;
    static uint8_t minuto_dezena = 0;
    static uint8_t hora_unidade = 0;
    static uint8_t hora_dezena = 0;

    dig7a = hora_dezena;
    dig7b = hora_unidade;
    dig7c = minuto_dezena;
    dig7d = minuto_unidade;

    minuto_unidade++;
    if (minuto_unidade > 9)
    {
        minuto_unidade = 0;
        minuto_dezena++;
    }
    if (minuto_dezena > 5)
    {
        minuto_dezena = 0;
        hora_unidade++;
    }
    if (hora_unidade > 9)
    {
        hora_unidade = 0;
        hora_dezena++;
    }
    if (hora_dezena > 23)
    {
        minuto_unidade = 0;
        minuto_dezena = 0;
        hora_unidade = 0;
        hora_dezena = 0;
    }
}

void incrementaMinutoRelogio()
{
    if (minuto_unidade >= 9)
    {
        minuto_unidade = 0;

        // caso especial 59 -> 00
        if (minuto_dezena >= 5)
        {
            minuto_dezena = 0;
        }
        else
        {
            minuto_dezena++;
        }
    }
    else
    {
        minuto_unidade++;
    }

    dig7a = hora_dezena;
    dig7b = hora_unidade;
    dig7c = minuto_dezena;
    dig7d = minuto_unidade;
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
        }
        else
        {
            minuto_dezena--;
        }
    }
    else
    {
        minuto_unidade--;
    }

    dig7a = hora_dezena;
    dig7b = hora_unidade;
    dig7c = minuto_dezena;
    dig7d = minuto_unidade;
}

void incrementaHoraRelogio()
{
    // caso especial 23 -> 00
    if (hora_dezena >= 2 && hora_unidade >= 3)
    {
        hora_unidade = 0;
        hora_dezena = 0;
    }
    else if (hora_unidade >= 9)
    {
        hora_unidade = 0;
        hora_dezena++;
    }
    else
    {
        hora_unidade++;
    }

    dig7a = hora_dezena;
    dig7b = hora_unidade;
    dig7c = minuto_dezena;
    dig7d = minuto_unidade;
}

void decrementaHoraRelogio()
{
    if (minuto_unidade <= 0)
    {
        minuto_unidade = 9;

        if (minuto_dezena <= 0)
        {
            minuto_dezena = 5;
        }
        else
        {
            minuto_dezena--;
        }
    }
    else
    {
        minuto_unidade--;
    }

    dig7a = hora_dezena;
    dig7b = hora_unidade;
    dig7c = minuto_dezena;
    dig7d = minuto_unidade;
}

void incrementaMinutoAlarme()
{
    if (alarme_minuto_unidade >= 9)
    {
        alarme_minuto_unidade = 0;

        // caso especial 59 -> 00
        if (alarme_minuto_dezena >= 5)
        {
            alarme_minuto_dezena = 0;
        }
        else
        {
            alarme_minuto_dezena++;
        }
    }
    else
    {
        alarme_minuto_unidade++;
    }

    dig7a = alarme_hora_dezena;
    dig7b = alarme_hora_unidade;
    dig7c = alarme_minuto_dezena;
    dig7d = alarme_minuto_unidade;
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
        }
        else
        {
            alarme_minuto_dezena--;
        }
    }
    else
    {
        alarme_minuto_unidade--;
    }

    dig7a = alarme_hora_dezena;
    dig7b = alarme_hora_unidade;
    dig7c = alarme_minuto_dezena;
    dig7d = alarme_minuto_unidade;
}

void incrementaHoraAlarme()
{
    // caso especial 23 -> 00
    if (alarme_hora_dezena >= 2 && alarme_hora_unidade >= 3)
    {
        alarme_hora_unidade = 0;
        alarme_hora_dezena = 0;
    }
    else if (alarme_hora_unidade >= 9)
    {
        alarme_hora_unidade = 0;
        alarme_hora_dezena++;
    }
    else
    {
        alarme_hora_unidade++;
    }

    dig7a = alarme_hora_dezena;
    dig7b = alarme_hora_unidade;
    dig7c = alarme_minuto_dezena;
    dig7d = alarme_minuto_unidade;
}

void decrementaHoraAlarme()
{
    if (alarme_minuto_unidade <= 0)
    {
        alarme_minuto_unidade = 9;

        if (alarme_minuto_dezena <= 0)
        {
            alarme_minuto_dezena = 5;
        }
        else
        {
            alarme_minuto_dezena--;
        }
    }
    else
    {
        alarme_minuto_unidade--;
    }

    dig7a = alarme_hora_dezena;
    dig7b = alarme_hora_unidade;
    dig7c = alarme_minuto_dezena;
    dig7d = alarme_minuto_unidade;
}

void taskRelogio()
{
    if (contRelogio >= 1000)
    {
        contRelogio = 0;
        calculaHora();
    }
    else
    {
        contRelogio++;
    }
}

void taskAjusteMinutos()
{
    if (contRelogio >= 1000)
    {
        contRelogio = 0;

        if (task_decrementa_minutos_alarme >= 1)
        {
            task_decrementa_minutos_alarme = 0;
            decrementaMinutoRelogio();
        }
        if (task_incrementa_minutos_alarme >= 1)
        {
            task_incrementa_minutos_alarme = 0;
            incrementaMinutoRelogio();
        }
    }
    else
    {
        if (contRelogio >= 500)
        {
            dig7a = hora_dezena;
            dig7b = hora_unidade;
            dig7c = 10;
            dig7d = 10;
        }

        contRelogio++;
    }
}

void taskAjusteHoras()
{
    if (contRelogio >= 1000)
    {
        contRelogio = 0;

        if (task_decrementa_horas_alarme >= 1)
        {
            task_decrementa_horas_alarme = 0;
            decrementaHoraRelogio();
        }
        if (task_incrementa_horas_alarme >= 1)
        {
            task_incrementa_horas_alarme = 0;
            incrementaHoraRelogio();
        }
    }
    else
    {
        if (contRelogio >= 500)
        {
            dig7a = 10;
            dig7b = 10;
            dig7c = minuto_dezena;
            dig7d = minuto_unidade;
        }

        contRelogio++;
    }
}

void taskAlarmeMinutos()
{
    if (contAlarme >= 1000)
    {
        contAlarme = 0;

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
        dig7b = alarme_hora_unidade;
        dig7c = alarme_minuto_dezena;
        dig7d = alarme_minuto_unidade;
    }
    else
    {
        if (contAlarme >= 500)
        {
            dig7a = alarme_hora_dezena;
            dig7b = alarme_hora_unidade;
            dig7c = 10;
            dig7d = 10;
        }

        contAlarme++;
    }
}

void taskAlarmeHoras()
{
    if (contAlarme >= 1000)
    {
        contAlarme = 0;
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
    }
    else
    {
        if (contAlarme >= 500)
        {
            dig7a = 10;
            dig7b = 10;
            dig7c = alarme_minuto_dezena;
            dig7d = alarme_minuto_unidade;
        }

        contAlarme++;
    }
}
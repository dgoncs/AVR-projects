#include <lib_macros.h>
#include <lib_timer.h>
#include <avr/io.h>

#define SDI PB0
#define SCLK PD7
#define SLC PD4

volatile uint8_t dig7a;
volatile uint8_t dig7b;
volatile uint8_t dig7c;
volatile uint8_t dig7d;
static volatile uint16_t contVarredura = 0;
static volatile uint16_t contRelogio = 0;
static volatile uint16_t contAlarme = 0;
volatile uint8_t minuto_unidade = 0;
volatile uint8_t minuto_dezena = 0;
volatile uint8_t hora_unidade = 0;
volatile uint8_t hora_dezena = 0;
volatile uint8_t alarme_minuto_unidade = 0;
volatile uint8_t alarme_minuto_dezena = 0;
volatile uint8_t alarme_hora_unidade = 0;
volatile uint8_t alarme_hora_dezena = 0;

uint8_t decod7seg[] = {
    0b00000011, // 0
    0b10011111, // 1
    0b00100101, // 2
    0b00001101, // 3
    0b10011001, // 4
    0b01001001, // 5
    0b01000001, // 6
    0b00011111, // 7
    0b00000001, // 8
    0b00001001, // 9
    0b11111111  // apagado
};

uint8_t displays[] = {0b10000000, 0b01000000, 0b00100000, 0b00010000};

void setup_display7seg()
{
    bitSet(DDRB, SDI);
    bitSet(DDRD, SCLK);
    bitSet(DDRD, SLC);
}

void display7segWrite(uint8_t b1, uint8_t b2)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if (b1 & 0b00000001)
            bitSet(PORTB, 0);
        else
            bitClear(PORTB, 0);

        bitSet(PORTD, 7);
        bitClear(PORTD, 7);
        b1 >>= 1;
    }

    for (uint8_t i = 0; i < 8; i++)
    {
        if (b2 & 0b00000001)
            bitSet(PORTB, 0);
        else
            bitClear(PORTB, 0);

        bitSet(PORTD, 7);
        bitClear(PORTD, 7);
        b2 >>= 1;
    }

    bitSet(PORTD, 4);
    bitClear(PORTD, 4);
}

void apagaTodosDigitos()
{
    for (int i = 0; i < 4; i++)
    {
        display7segWrite(decod7seg[16], displays[i]);
    }
}

void trocaDisplay()
{
    static volatile uint8_t displayAtual = {0};

    switch (displayAtual)
    {
    case 0:
        display7segWrite(decod7seg[dig7a], displays[displayAtual]);
        displayAtual = 1;
        break;
    case 1:
        display7segWrite(decod7seg[dig7b], displays[displayAtual]);
        displayAtual = 2;
        break;
    case 2:
        display7segWrite(decod7seg[dig7c], displays[displayAtual]);
        displayAtual = 3;
        break;
    case 3:
        display7segWrite(decod7seg[dig7d], displays[displayAtual]);
        displayAtual = 0;
        break;
    }
}

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
    //caso especial 23 -> 00
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

void taskRelogio()
{
    if (contRelogio >= 1000)
    {
        contRelogio = 0;
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
        // se s2: incrementaMinutoRelogio();
        // se s3: decrementaMinutoRelogio();
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
        // se s2: incrementaHoraRelogio();
        // se s3: decrementaHoraRelogio();
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
        // se s2: incrementaHoraAlarme();
        // se s3: decrementaHoraAlarme();
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

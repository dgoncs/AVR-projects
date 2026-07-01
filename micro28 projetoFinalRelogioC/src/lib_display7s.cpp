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
volatile uint16_t contVarredura = 0;

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
    0b11111111, // apagado
    0b00000010, // 0.
    0b10011110, // 1.
    0b00100100, // 2.
    0b00001100, // 3.
    0b10011000, // 4.
    0b01001000, // 5.
    0b01000000, // 6.
    0b00011110, // 7.
    0b00000000, // 8.
    0b00001000, // 9.
    0b11111110  // .
};

uint8_t decod7segComPonto[] = {
    0b00000010, // 0.
    0b10011110, // 1.
    0b00100100, // 2.
    0b00001100, // 3.
    0b10011000, // 4.
    0b01001000, // 5.
    0b01000000, // 6.
    0b00011110, // 7.
    0b00000000, // 8.
    0b00001000, // 9.
    0b11111110  // .
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

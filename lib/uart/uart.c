#include <avr/io.h>
#include <util/delay.h>

#define DMX_BAUD_RATE 115200
#define F_CPU         16000000UL

// Calcolo del valore UBRR per la velocità di 250 kbps
#define UBRR_VALUE ((F_CPU / (DMX_BAUD_RATE * 16UL)) - 1)

// Inizializzazione della USART per la trasmissione DMX
void usart_init() {

    UBRR0H = (uint8_t)(UBRR_VALUE >> 8);
    UBRR0L = (uint8_t)UBRR_VALUE;
    
    UCSR0C = (1 << USBS0) | (3 << UCSZ00); // 2 stop bit, 8 data bit
    
    // Abilita la trasmissione
    UCSR0B = (1 << TXEN0);

    return;
}

void usart_transmit(uint8_t data) {

    // Attendi che il buffer di trasmissione sia vuoto
    while (!(UCSR0A & (1 << UDRE0)));
    
    // Invia il dato
    UDR0 = data;

    return;
}
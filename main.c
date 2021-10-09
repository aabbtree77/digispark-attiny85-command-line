//R. G. May 3rd 2021, MIT licence

#define F_CPU 16500000UL  
#include <avr/io.h>        
#include <util/delay.h>
//#include <avr/interrupt.h>

// MACROS FOR EASY PIN HANDLING FOR ATMEL GCC-AVR
//these macros are used indirectly by other macros , mainly for string concatenation
#define _SET(type,name,bit)          type ## name  |= _BV(bit)    
#define _CLEAR(type,name,bit)        type ## name  &= ~ _BV(bit)        
#define _TOGGLE(type,name,bit)       type ## name  ^= _BV(bit)    
#define _GET(type,name,bit)          ((type ## name >> bit) &  1)
#define _PUT(type,name,bit,value)    type ## name = ( type ## name & ( ~ _BV(bit)) ) | ( ( 1 & (unsigned char)value ) << bit )

//these macros are used by end user
#define OUTPUT(pin)         _SET(DDR,pin)    
#define INPUT(pin)          _CLEAR(DDR,pin)    
#define HIGH(pin)           _SET(PORT,pin)
#define LOW(pin)            _CLEAR(PORT,pin)    
#define TOGGLE(pin)         _TOGGLE(PORT,pin)    
#define READ(pin)           _GET(PIN,pin)

/*
    BASIC STAMPS STYLE COMMANDS FOR ATMEL GCC-AVR

    Usage Example:
    ———————————————–
    #define pinLed B,5  //define pins like this

    OUTPUT(pinLed);       //typo fixed
    //OUTPUT(pinLED);     //compiles as DDRB |= (1<<5);
    HIGH(pinLed);         //compiles as PORTB |= (1<<5);
    ———————————————–
*/

#define OutX B,0

//max delay with _delay_ms is 262.14 ms / F_CPU in MHz, i.e. 32 ms for 8 MHz.
//so lets iterate 1ms, that looses precision with function call overhead, 
//but we do not care in this application
void delay1ms(uint32_t ms) {
    uint32_t i;
    for(i=0;i<ms;i++) _delay_ms(1);
}

void delay1us(uint32_t us) {
    uint32_t i;
    for(i=0;i<us;i++) _delay_us(1);
}

//Max size for uint16_t is 65,535 - not enough in general.
//Max size for uint32_t is 4,294,967,295 - OK.

/*** Main void ***/
int main(void){
    
    OUTPUT(OutX);
    LOW(OutX); 

    while(1){   
            HIGH(OutX);
            delay1ms(1000);
            LOW(OutX);
            delay1ms(2000);
    }
}

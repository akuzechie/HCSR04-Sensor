;------------------------
; Assembly Code
;------------------------
#define __SFR_OFFSET 0x00
#include "avr/io.h"
;------------------------
.global set_EchoPin
.global echoPW_rising
.global echoPW_falling
.global timer1_clr_flag
.global delay_timer0
.global delay_1s
;===============================================================
set_EchoPin:
;-----------
    CBI   DDRB, 0         ;pin PB0 as i/p (Echo)
    RET
;===============================================================
echoPW_rising:
;-------------
    LDI   R20, 0b00000000
    STS   TCCR1A, R20     ;Timer 1 normal mode
    LDI   R20, 0b11000101 ;set for rising edge detection &
    STS   TCCR1B, R20     ;prescaler=1024, noise cancellation ON
    ;-----------------------------------------------------------
l1: IN    R21, TIFR1
    SBRS  R21, ICF1
    RJMP  l1              ;loop until rising edge is detected
    RET
;===============================================================
echoPW_falling:
;--------------
    LDI   R20, 0b10000101
    STS   TCCR1B, R20     ;set for falling edge detection
    ;-----------------------------------------------------------
l2: IN    R21, TIFR1
    SBRS  R21, ICF1
    RJMP  l2              ;loop until falling edge is detected
    RET
;===============================================================
timer1_clr_flag:
;---------------
    OUT   TIFR1, R21      ;clear flag for next sensor reading
    RET
;===============================================================
delay_timer0:             ;10 usec delay via Timer 0
;------------
    CLR   R20
    OUT   TCNT0, R20      ;initialize timer0 with count=0
    LDI   R20, 20
    OUT   OCR0A, R20      ;OCR0 = 20
    LDI   R20, 0b00001010
    OUT   TCCR0B, R20     ;timer0: CTC mode, prescaler 8
    ;-----------------------------------------------------------
l0: IN    R20, TIFR0      ;get TIFR0 byte & check
    SBRS  R20, OCF0A      ;if OCF0=1, skip next instruction
    RJMP  l0              ;else, loop back & check OCF0 flag
    ;-----------------------------------------------------------
    CLR   R20
    OUT   TCCR0B, R20     ;stop timer0
    ;-----------------------------------------------------------
    LDI   R20, (1<<OCF0A)
    OUT   TIFR0, R20      ;clear OCF0 flag
    RET
;===============================================================
delay_1s:
;--------
    LDI   R21, 255
l6: LDI   R22, 255
l7: LDI   R23, 82
l8: DEC   R23
    BRNE  l8
    DEC   R22
    BRNE  l7
    DEC   R21
    BRNE  l6
    RET
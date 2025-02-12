# 1 "main.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/opt/microchip/xc8/v2.36/pic/include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "main.c" 2
# 15 "main.c"
# 1 "./main.h" 1
# 39 "./main.h"
#pragma config FOSC = INTOSCIO
#pragma config WDTE = ON
#pragma config PWRTE = ON
#pragma config MCLRE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config CP = OFF





# 1 "/opt/microchip/xc8/v2.36/pic/include/xc.h" 1 3
# 18 "/opt/microchip/xc8/v2.36/pic/include/xc.h" 3
extern const char __xc8_OPTIM_SPEED;

extern double __fpnormalize(double);



# 1 "/opt/microchip/xc8/v2.36/pic/include/c90/xc8debug.h" 1 3
# 13 "/opt/microchip/xc8/v2.36/pic/include/c90/xc8debug.h" 3
#pragma intrinsic(__builtin_software_breakpoint)
extern void __builtin_software_breakpoint(void);
# 24 "/opt/microchip/xc8/v2.36/pic/include/xc.h" 2 3
# 1 "/opt/microchip/xc8/v2.36/pic/include/builtins.h" 1 3



# 1 "/opt/microchip/xc8/v2.36/pic/include/c90/stdint.h" 1 3
# 13 "/opt/microchip/xc8/v2.36/pic/include/c90/stdint.h" 3
typedef signed char int8_t;






typedef signed int int16_t;







typedef __int24 int24_t;







typedef signed long int int32_t;
# 52 "/opt/microchip/xc8/v2.36/pic/include/c90/stdint.h" 3
typedef unsigned char uint8_t;





typedef unsigned int uint16_t;






typedef __uint24 uint24_t;






typedef unsigned long int uint32_t;
# 88 "/opt/microchip/xc8/v2.36/pic/include/c90/stdint.h" 3
typedef signed char int_least8_t;







typedef signed int int_least16_t;
# 109 "/opt/microchip/xc8/v2.36/pic/include/c90/stdint.h" 3
typedef __int24 int_least24_t;
# 118 "/opt/microchip/xc8/v2.36/pic/include/c90/stdint.h" 3
typedef signed long int int_least32_t;
# 136 "/opt/microchip/xc8/v2.36/pic/include/c90/stdint.h" 3
typedef unsigned char uint_least8_t;






typedef unsigned int uint_least16_t;
# 154 "/opt/microchip/xc8/v2.36/pic/include/c90/stdint.h" 3
typedef __uint24 uint_least24_t;







typedef unsigned long int uint_least32_t;
# 181 "/opt/microchip/xc8/v2.36/pic/include/c90/stdint.h" 3
typedef signed char int_fast8_t;






typedef signed int int_fast16_t;
# 200 "/opt/microchip/xc8/v2.36/pic/include/c90/stdint.h" 3
typedef __int24 int_fast24_t;







typedef signed long int int_fast32_t;
# 224 "/opt/microchip/xc8/v2.36/pic/include/c90/stdint.h" 3
typedef unsigned char uint_fast8_t;





typedef unsigned int uint_fast16_t;
# 240 "/opt/microchip/xc8/v2.36/pic/include/c90/stdint.h" 3
typedef __uint24 uint_fast24_t;






typedef unsigned long int uint_fast32_t;
# 268 "/opt/microchip/xc8/v2.36/pic/include/c90/stdint.h" 3
typedef int32_t intmax_t;
# 282 "/opt/microchip/xc8/v2.36/pic/include/c90/stdint.h" 3
typedef uint32_t uintmax_t;






typedef int16_t intptr_t;




typedef uint16_t uintptr_t;
# 5 "/opt/microchip/xc8/v2.36/pic/include/builtins.h" 2 3


#pragma intrinsic(__nop)
extern void __nop(void);


#pragma intrinsic(_delay)
extern __attribute__((nonreentrant)) void _delay(uint32_t);
#pragma intrinsic(_delaywdt)
extern __attribute__((nonreentrant)) void _delaywdt(uint32_t);
# 25 "/opt/microchip/xc8/v2.36/pic/include/xc.h" 2 3



# 1 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/pic.h" 1 3




# 1 "/opt/microchip/xc8/v2.36/pic/include/htc.h" 1 3



# 1 "/opt/microchip/xc8/v2.36/pic/include/xc.h" 1 3
# 5 "/opt/microchip/xc8/v2.36/pic/include/htc.h" 2 3
# 6 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/pic.h" 2 3







# 1 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/pic_chip_select.h" 1 3
# 213 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/pic_chip_select.h" 3
# 1 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 1 3
# 44 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 3
# 1 "/opt/microchip/xc8/v2.36/pic/include/__at.h" 1 3
# 45 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 2 3







extern volatile unsigned char INDF __attribute__((address(0x000)));

__asm("INDF equ 00h");




extern volatile unsigned char TMR0 __attribute__((address(0x001)));

__asm("TMR0 equ 01h");




extern volatile unsigned char PCL __attribute__((address(0x002)));

__asm("PCL equ 02h");




extern volatile unsigned char STATUS __attribute__((address(0x003)));

__asm("STATUS equ 03h");


typedef union {
    struct {
        unsigned C :1;
        unsigned DC :1;
        unsigned Z :1;
        unsigned nPD :1;
        unsigned nTO :1;
        unsigned RP :2;
        unsigned IRP :1;
    };
    struct {
        unsigned :5;
        unsigned RP0 :1;
        unsigned RP1 :1;
    };
    struct {
        unsigned CARRY :1;
        unsigned :1;
        unsigned ZERO :1;
    };
} STATUSbits_t;
extern volatile STATUSbits_t STATUSbits __attribute__((address(0x003)));
# 159 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 3
extern volatile unsigned char FSR __attribute__((address(0x004)));

__asm("FSR equ 04h");




extern volatile unsigned char PORTA __attribute__((address(0x005)));

__asm("PORTA equ 05h");


typedef union {
    struct {
        unsigned RA0 :1;
        unsigned RA1 :1;
        unsigned RA2 :1;
        unsigned RA3 :1;
        unsigned RA4 :1;
        unsigned RA5 :1;
        unsigned RA6 :1;
        unsigned RA7 :1;
    };
} PORTAbits_t;
extern volatile PORTAbits_t PORTAbits __attribute__((address(0x005)));
# 228 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 3
extern volatile unsigned char PORTB __attribute__((address(0x006)));

__asm("PORTB equ 06h");


typedef union {
    struct {
        unsigned RB0 :1;
        unsigned RB1 :1;
        unsigned RB2 :1;
        unsigned RB3 :1;
        unsigned RB4 :1;
        unsigned RB5 :1;
        unsigned RB6 :1;
        unsigned RB7 :1;
    };
} PORTBbits_t;
extern volatile PORTBbits_t PORTBbits __attribute__((address(0x006)));
# 290 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 3
extern volatile unsigned char PCLATH __attribute__((address(0x00A)));

__asm("PCLATH equ 0Ah");


typedef union {
    struct {
        unsigned PCLATH :5;
    };
} PCLATHbits_t;
extern volatile PCLATHbits_t PCLATHbits __attribute__((address(0x00A)));
# 310 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 3
extern volatile unsigned char INTCON __attribute__((address(0x00B)));

__asm("INTCON equ 0Bh");


typedef union {
    struct {
        unsigned RBIF :1;
        unsigned INTF :1;
        unsigned T0IF :1;
        unsigned RBIE :1;
        unsigned INTE :1;
        unsigned T0IE :1;
        unsigned PEIE :1;
        unsigned GIE :1;
    };
    struct {
        unsigned :2;
        unsigned TMR0IF :1;
        unsigned :2;
        unsigned TMR0IE :1;
    };
} INTCONbits_t;
extern volatile INTCONbits_t INTCONbits __attribute__((address(0x00B)));
# 388 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 3
extern volatile unsigned char PIR1 __attribute__((address(0x00C)));

__asm("PIR1 equ 0Ch");


typedef union {
    struct {
        unsigned TMR1IF :1;
        unsigned TMR2IF :1;
        unsigned CCP1IF :1;
        unsigned :1;
        unsigned TXIF :1;
        unsigned RCIF :1;
        unsigned CMIF :1;
        unsigned EEIF :1;
    };
} PIR1bits_t;
extern volatile PIR1bits_t PIR1bits __attribute__((address(0x00C)));
# 445 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 3
extern volatile unsigned short TMR1 __attribute__((address(0x00E)));

__asm("TMR1 equ 0Eh");




extern volatile unsigned char TMR1L __attribute__((address(0x00E)));

__asm("TMR1L equ 0Eh");




extern volatile unsigned char TMR1H __attribute__((address(0x00F)));

__asm("TMR1H equ 0Fh");




extern volatile unsigned char T1CON __attribute__((address(0x010)));

__asm("T1CON equ 010h");


typedef union {
    struct {
        unsigned TMR1ON :1;
        unsigned TMR1CS :1;
        unsigned nT1SYNC :1;
        unsigned T1OSCEN :1;
        unsigned T1CKPS :2;
    };
    struct {
        unsigned :4;
        unsigned T1CKPS0 :1;
        unsigned T1CKPS1 :1;
    };
} T1CONbits_t;
extern volatile T1CONbits_t T1CONbits __attribute__((address(0x010)));
# 525 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 3
extern volatile unsigned char TMR2 __attribute__((address(0x011)));

__asm("TMR2 equ 011h");




extern volatile unsigned char T2CON __attribute__((address(0x012)));

__asm("T2CON equ 012h");


typedef union {
    struct {
        unsigned T2CKPS :2;
        unsigned TMR2ON :1;
        unsigned TOUTPS :4;
    };
    struct {
        unsigned T2CKPS0 :1;
        unsigned T2CKPS1 :1;
        unsigned :1;
        unsigned TOUTPS0 :1;
        unsigned TOUTPS1 :1;
        unsigned TOUTPS2 :1;
        unsigned TOUTPS3 :1;
    };
} T2CONbits_t;
extern volatile T2CONbits_t T2CONbits __attribute__((address(0x012)));
# 603 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 3
extern volatile unsigned short CCPR1 __attribute__((address(0x015)));

__asm("CCPR1 equ 015h");




extern volatile unsigned char CCPR1L __attribute__((address(0x015)));

__asm("CCPR1L equ 015h");




extern volatile unsigned char CCPR1H __attribute__((address(0x016)));

__asm("CCPR1H equ 016h");




extern volatile unsigned char CCP1CON __attribute__((address(0x017)));

__asm("CCP1CON equ 017h");


typedef union {
    struct {
        unsigned CCP1M :4;
        unsigned CCP1Y :1;
        unsigned CCP1X :1;
    };
    struct {
        unsigned CCP1M0 :1;
        unsigned CCP1M1 :1;
        unsigned CCP1M2 :1;
        unsigned CCP1M3 :1;
    };
} CCP1CONbits_t;
extern volatile CCP1CONbits_t CCP1CONbits __attribute__((address(0x017)));
# 682 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 3
extern volatile unsigned char RCSTA __attribute__((address(0x018)));

__asm("RCSTA equ 018h");


typedef union {
    struct {
        unsigned RX9D :1;
        unsigned OERR :1;
        unsigned FERR :1;
        unsigned ADEN :1;
        unsigned CREN :1;
        unsigned SREN :1;
        unsigned RX9 :1;
        unsigned SPEN :1;
    };
    struct {
        unsigned :3;
        unsigned ADDEN :1;
    };
} RCSTAbits_t;
extern volatile RCSTAbits_t RCSTAbits __attribute__((address(0x018)));
# 753 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 3
extern volatile unsigned char TXREG __attribute__((address(0x019)));

__asm("TXREG equ 019h");




extern volatile unsigned char RCREG __attribute__((address(0x01A)));

__asm("RCREG equ 01Ah");




extern volatile unsigned char CMCON __attribute__((address(0x01F)));

__asm("CMCON equ 01Fh");


typedef union {
    struct {
        unsigned CM :3;
        unsigned CIS :1;
        unsigned C1INV :1;
        unsigned C2INV :1;
        unsigned C1OUT :1;
        unsigned C2OUT :1;
    };
    struct {
        unsigned CM0 :1;
        unsigned CM1 :1;
        unsigned CM2 :1;
    };
} CMCONbits_t;
extern volatile CMCONbits_t CMCONbits __attribute__((address(0x01F)));
# 837 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 3
extern volatile unsigned char OPTION_REG __attribute__((address(0x081)));

__asm("OPTION_REG equ 081h");


typedef union {
    struct {
        unsigned PS :3;
        unsigned PSA :1;
        unsigned T0SE :1;
        unsigned T0CS :1;
        unsigned INTEDG :1;
        unsigned nRBPU :1;
    };
    struct {
        unsigned PS0 :1;
        unsigned PS1 :1;
        unsigned PS2 :1;
    };
} OPTION_REGbits_t;
extern volatile OPTION_REGbits_t OPTION_REGbits __attribute__((address(0x081)));
# 907 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 3
extern volatile unsigned char TRISA __attribute__((address(0x085)));

__asm("TRISA equ 085h");


typedef union {
    struct {
        unsigned TRISA0 :1;
        unsigned TRISA1 :1;
        unsigned TRISA2 :1;
        unsigned TRISA3 :1;
        unsigned TRISA4 :1;
        unsigned TRISA5 :1;
        unsigned TRISA6 :1;
        unsigned TRISA7 :1;
    };
} TRISAbits_t;
extern volatile TRISAbits_t TRISAbits __attribute__((address(0x085)));
# 969 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 3
extern volatile unsigned char TRISB __attribute__((address(0x086)));

__asm("TRISB equ 086h");


typedef union {
    struct {
        unsigned TRISB0 :1;
        unsigned TRISB1 :1;
        unsigned TRISB2 :1;
        unsigned TRISB3 :1;
        unsigned TRISB4 :1;
        unsigned TRISB5 :1;
        unsigned TRISB6 :1;
        unsigned TRISB7 :1;
    };
} TRISBbits_t;
extern volatile TRISBbits_t TRISBbits __attribute__((address(0x086)));
# 1031 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 3
extern volatile unsigned char PIE1 __attribute__((address(0x08C)));

__asm("PIE1 equ 08Ch");


typedef union {
    struct {
        unsigned TMR1IE :1;
        unsigned TMR2IE :1;
        unsigned CCP1IE :1;
        unsigned :1;
        unsigned TXIE :1;
        unsigned RCIE :1;
        unsigned CMIE :1;
        unsigned EEIE :1;
    };
} PIE1bits_t;
extern volatile PIE1bits_t PIE1bits __attribute__((address(0x08C)));
# 1088 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 3
extern volatile unsigned char PCON __attribute__((address(0x08E)));

__asm("PCON equ 08Eh");


typedef union {
    struct {
        unsigned nBOR :1;
        unsigned nPOR :1;
        unsigned :1;
        unsigned OSCF :1;
    };
    struct {
        unsigned nBO :1;
    };
    struct {
        unsigned nBOD :1;
    };
} PCONbits_t;
extern volatile PCONbits_t PCONbits __attribute__((address(0x08E)));
# 1137 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 3
extern volatile unsigned char PR2 __attribute__((address(0x092)));

__asm("PR2 equ 092h");




extern volatile unsigned char TXSTA __attribute__((address(0x098)));

__asm("TXSTA equ 098h");


typedef union {
    struct {
        unsigned TX9D :1;
        unsigned TRMT :1;
        unsigned BRGH :1;
        unsigned :1;
        unsigned SYNC :1;
        unsigned TXEN :1;
        unsigned TX9 :1;
        unsigned CSRC :1;
    };
} TXSTAbits_t;
extern volatile TXSTAbits_t TXSTAbits __attribute__((address(0x098)));
# 1201 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 3
extern volatile unsigned char SPBRG __attribute__((address(0x099)));

__asm("SPBRG equ 099h");




extern volatile unsigned char EEDATA __attribute__((address(0x09A)));

__asm("EEDATA equ 09Ah");




extern volatile unsigned char EEADR __attribute__((address(0x09B)));

__asm("EEADR equ 09Bh");




extern volatile unsigned char EECON1 __attribute__((address(0x09C)));

__asm("EECON1 equ 09Ch");


typedef union {
    struct {
        unsigned RD :1;
        unsigned WR :1;
        unsigned WREN :1;
        unsigned WRERR :1;
    };
} EECON1bits_t;
extern volatile EECON1bits_t EECON1bits __attribute__((address(0x09C)));
# 1260 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 3
extern volatile unsigned char EECON2 __attribute__((address(0x09D)));

__asm("EECON2 equ 09Dh");




extern volatile unsigned char VRCON __attribute__((address(0x09F)));

__asm("VRCON equ 09Fh");


typedef union {
    struct {
        unsigned VR :4;
        unsigned :1;
        unsigned VRR :1;
        unsigned VROE :1;
        unsigned VREN :1;
    };
    struct {
        unsigned VR0 :1;
        unsigned VR1 :1;
        unsigned VR2 :1;
        unsigned VR3 :1;
    };
} VRCONbits_t;
extern volatile VRCONbits_t VRCONbits __attribute__((address(0x09F)));
# 1342 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/proc/pic16f648a.h" 3
extern volatile __bit ADDEN __attribute__((address(0xC3)));


extern volatile __bit ADEN __attribute__((address(0xC3)));


extern volatile __bit BRGH __attribute__((address(0x4C2)));


extern volatile __bit C1INV __attribute__((address(0xFC)));


extern volatile __bit C1OUT __attribute__((address(0xFE)));


extern volatile __bit C2INV __attribute__((address(0xFD)));


extern volatile __bit C2OUT __attribute__((address(0xFF)));


extern volatile __bit CARRY __attribute__((address(0x18)));


extern volatile __bit CCP1IE __attribute__((address(0x462)));


extern volatile __bit CCP1IF __attribute__((address(0x62)));


extern volatile __bit CCP1M0 __attribute__((address(0xB8)));


extern volatile __bit CCP1M1 __attribute__((address(0xB9)));


extern volatile __bit CCP1M2 __attribute__((address(0xBA)));


extern volatile __bit CCP1M3 __attribute__((address(0xBB)));


extern volatile __bit CCP1X __attribute__((address(0xBD)));


extern volatile __bit CCP1Y __attribute__((address(0xBC)));


extern volatile __bit CIS __attribute__((address(0xFB)));


extern volatile __bit CM0 __attribute__((address(0xF8)));


extern volatile __bit CM1 __attribute__((address(0xF9)));


extern volatile __bit CM2 __attribute__((address(0xFA)));


extern volatile __bit CMIE __attribute__((address(0x466)));


extern volatile __bit CMIF __attribute__((address(0x66)));


extern volatile __bit CREN __attribute__((address(0xC4)));


extern volatile __bit CSRC __attribute__((address(0x4C7)));


extern volatile __bit DC __attribute__((address(0x19)));


extern volatile __bit EEIE __attribute__((address(0x467)));


extern volatile __bit EEIF __attribute__((address(0x67)));


extern volatile __bit FERR __attribute__((address(0xC2)));


extern volatile __bit GIE __attribute__((address(0x5F)));


extern volatile __bit INTE __attribute__((address(0x5C)));


extern volatile __bit INTEDG __attribute__((address(0x40E)));


extern volatile __bit INTF __attribute__((address(0x59)));


extern volatile __bit IRP __attribute__((address(0x1F)));


extern volatile __bit OERR __attribute__((address(0xC1)));


extern volatile __bit OSCF __attribute__((address(0x473)));


extern volatile __bit PEIE __attribute__((address(0x5E)));


extern volatile __bit PS0 __attribute__((address(0x408)));


extern volatile __bit PS1 __attribute__((address(0x409)));


extern volatile __bit PS2 __attribute__((address(0x40A)));


extern volatile __bit PSA __attribute__((address(0x40B)));


extern volatile __bit RA0 __attribute__((address(0x28)));


extern volatile __bit RA1 __attribute__((address(0x29)));


extern volatile __bit RA2 __attribute__((address(0x2A)));


extern volatile __bit RA3 __attribute__((address(0x2B)));


extern volatile __bit RA4 __attribute__((address(0x2C)));


extern volatile __bit RA5 __attribute__((address(0x2D)));


extern volatile __bit RA6 __attribute__((address(0x2E)));


extern volatile __bit RA7 __attribute__((address(0x2F)));


extern volatile __bit RB0 __attribute__((address(0x30)));


extern volatile __bit RB1 __attribute__((address(0x31)));


extern volatile __bit RB2 __attribute__((address(0x32)));


extern volatile __bit RB3 __attribute__((address(0x33)));


extern volatile __bit RB4 __attribute__((address(0x34)));


extern volatile __bit RB5 __attribute__((address(0x35)));


extern volatile __bit RB6 __attribute__((address(0x36)));


extern volatile __bit RB7 __attribute__((address(0x37)));


extern volatile __bit RBIE __attribute__((address(0x5B)));


extern volatile __bit RBIF __attribute__((address(0x58)));


extern volatile __bit RCIE __attribute__((address(0x465)));


extern volatile __bit RCIF __attribute__((address(0x65)));


extern volatile __bit RD __attribute__((address(0x4E0)));


extern volatile __bit RP0 __attribute__((address(0x1D)));


extern volatile __bit RP1 __attribute__((address(0x1E)));


extern volatile __bit RX9 __attribute__((address(0xC6)));


extern volatile __bit RX9D __attribute__((address(0xC0)));


extern volatile __bit SPEN __attribute__((address(0xC7)));


extern volatile __bit SREN __attribute__((address(0xC5)));


extern volatile __bit SYNC __attribute__((address(0x4C4)));


extern volatile __bit T0CS __attribute__((address(0x40D)));


extern volatile __bit T0IE __attribute__((address(0x5D)));


extern volatile __bit T0IF __attribute__((address(0x5A)));


extern volatile __bit T0SE __attribute__((address(0x40C)));


extern volatile __bit T1CKPS0 __attribute__((address(0x84)));


extern volatile __bit T1CKPS1 __attribute__((address(0x85)));


extern volatile __bit T1OSCEN __attribute__((address(0x83)));


extern volatile __bit T2CKPS0 __attribute__((address(0x90)));


extern volatile __bit T2CKPS1 __attribute__((address(0x91)));


extern volatile __bit TMR0IE __attribute__((address(0x5D)));


extern volatile __bit TMR0IF __attribute__((address(0x5A)));


extern volatile __bit TMR1CS __attribute__((address(0x81)));


extern volatile __bit TMR1IE __attribute__((address(0x460)));


extern volatile __bit TMR1IF __attribute__((address(0x60)));


extern volatile __bit TMR1ON __attribute__((address(0x80)));


extern volatile __bit TMR2IE __attribute__((address(0x461)));


extern volatile __bit TMR2IF __attribute__((address(0x61)));


extern volatile __bit TMR2ON __attribute__((address(0x92)));


extern volatile __bit TOUTPS0 __attribute__((address(0x93)));


extern volatile __bit TOUTPS1 __attribute__((address(0x94)));


extern volatile __bit TOUTPS2 __attribute__((address(0x95)));


extern volatile __bit TOUTPS3 __attribute__((address(0x96)));


extern volatile __bit TRISA0 __attribute__((address(0x428)));


extern volatile __bit TRISA1 __attribute__((address(0x429)));


extern volatile __bit TRISA2 __attribute__((address(0x42A)));


extern volatile __bit TRISA3 __attribute__((address(0x42B)));


extern volatile __bit TRISA4 __attribute__((address(0x42C)));


extern volatile __bit TRISA5 __attribute__((address(0x42D)));


extern volatile __bit TRISA6 __attribute__((address(0x42E)));


extern volatile __bit TRISA7 __attribute__((address(0x42F)));


extern volatile __bit TRISB0 __attribute__((address(0x430)));


extern volatile __bit TRISB1 __attribute__((address(0x431)));


extern volatile __bit TRISB2 __attribute__((address(0x432)));


extern volatile __bit TRISB3 __attribute__((address(0x433)));


extern volatile __bit TRISB4 __attribute__((address(0x434)));


extern volatile __bit TRISB5 __attribute__((address(0x435)));


extern volatile __bit TRISB6 __attribute__((address(0x436)));


extern volatile __bit TRISB7 __attribute__((address(0x437)));


extern volatile __bit TRMT __attribute__((address(0x4C1)));


extern volatile __bit TX9 __attribute__((address(0x4C6)));


extern volatile __bit TX9D __attribute__((address(0x4C0)));


extern volatile __bit TXEN __attribute__((address(0x4C5)));


extern volatile __bit TXIE __attribute__((address(0x464)));


extern volatile __bit TXIF __attribute__((address(0x64)));


extern volatile __bit VR0 __attribute__((address(0x4F8)));


extern volatile __bit VR1 __attribute__((address(0x4F9)));


extern volatile __bit VR2 __attribute__((address(0x4FA)));


extern volatile __bit VR3 __attribute__((address(0x4FB)));


extern volatile __bit VREN __attribute__((address(0x4FF)));


extern volatile __bit VROE __attribute__((address(0x4FE)));


extern volatile __bit VRR __attribute__((address(0x4FD)));


extern volatile __bit WR __attribute__((address(0x4E1)));


extern volatile __bit WREN __attribute__((address(0x4E2)));


extern volatile __bit WRERR __attribute__((address(0x4E3)));


extern volatile __bit ZERO __attribute__((address(0x1A)));


extern volatile __bit nBO __attribute__((address(0x470)));


extern volatile __bit nBOD __attribute__((address(0x470)));


extern volatile __bit nBOR __attribute__((address(0x470)));


extern volatile __bit nPD __attribute__((address(0x1B)));


extern volatile __bit nPOR __attribute__((address(0x471)));


extern volatile __bit nRBPU __attribute__((address(0x40F)));


extern volatile __bit nT1SYNC __attribute__((address(0x82)));


extern volatile __bit nTO __attribute__((address(0x1C)));
# 214 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/pic_chip_select.h" 2 3
# 14 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/pic.h" 2 3
# 76 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/pic.h" 3
__attribute__((__unsupported__("The " "FLASH_READ" " macro function is no longer supported. Please use the MPLAB X MCC."))) unsigned char __flash_read(unsigned short addr);

__attribute__((__unsupported__("The " "FLASH_WRITE" " macro function is no longer supported. Please use the MPLAB X MCC."))) void __flash_write(unsigned short addr, unsigned short data);

__attribute__((__unsupported__("The " "FLASH_ERASE" " macro function is no longer supported. Please use the MPLAB X MCC."))) void __flash_erase(unsigned short addr);



# 1 "/opt/microchip/xc8/v2.36/pic/include/eeprom_routines.h" 1 3
# 114 "/opt/microchip/xc8/v2.36/pic/include/eeprom_routines.h" 3
extern void eeprom_write(unsigned char addr, unsigned char value);
extern unsigned char eeprom_read(unsigned char addr);
# 84 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/pic.h" 2 3
# 118 "/home/rh/.mchp_packs/Microchip/PIC16Fxxx_DFP/1.6.156/xc8/pic/include/pic.h" 3
extern __bank0 unsigned char __resetbits;
extern __bank0 __bit __powerdown;
extern __bank0 __bit __timeout;
# 29 "/opt/microchip/xc8/v2.36/pic/include/xc.h" 2 3
# 51 "./main.h" 2

# 1 "/opt/microchip/xc8/v2.36/pic/include/c90/stdint.h" 1 3
# 52 "./main.h" 2

# 1 "/opt/microchip/xc8/v2.36/pic/include/c90/stdbool.h" 1 3
# 53 "./main.h" 2
# 15 "main.c" 2

# 1 "./usart.h" 1
# 15 "./usart.h"
void UART_Init(void);
void UART_Write(char data);
void UART_Write_Text(char *text);
void UART_Write_Text_CRLF(char *text);
# 16 "main.c" 2
# 67 "main.c"
volatile uint8_t data_receiv = 0;
volatile uint8_t buffer_index1 = 0;
volatile uint8_t buffer_index2 = 0;
volatile uint8_t buffer_data0[7] = {0};
volatile uint8_t buffer_data1[7] = {0};
volatile uint8_t buffer_data2[7] = {0};
volatile uint8_t buffer_data3[7] = {0};
volatile uint8_t buffer_data4[7] = {0};
volatile _Bool buffer_ready[5] = {0};
volatile uint8_t header_cnt = 0;

volatile uint8_t timeout_receiv = 0;
volatile uint8_t timeout_uart1 = 0;
volatile uint8_t timeout_uart2 = 0;
volatile uint8_t timeout_uart3 = 0;

volatile _Bool preset_pan_enabled = 0;
volatile _Bool preset_pan_enabled_old = 0;

volatile _Bool preset_tilt_enabled = 0;
volatile _Bool preset_tilt_enabled_old = 0;

volatile _Bool pan_enabled = 0;
volatile _Bool pan_direction = 0;
volatile uint8_t pan_speed = 0;
volatile uint8_t pan_speed_old = 0;
volatile uint16_t pan_counter = 0;

volatile _Bool tilt_enabled = 0;
volatile _Bool tilt_direction = 0;
volatile uint8_t tilt_speed = 0;
volatile uint8_t tilt_speed_old = 0;
volatile uint16_t tilt_counter = 0;

volatile uint8_t pan_step_phase = 0;
volatile uint8_t tilt_step_phase = 0;

volatile uint8_t timer1_pan = 0;
volatile uint8_t timer1_tilt = 0;
volatile uint8_t timer1_pan_ref = 0;
volatile uint8_t timer1_tilt_ref = 0;

volatile uint16_t pan_goto = 0;
volatile uint16_t tilt_goto = 0;

uint8_t frame_index = 0;
uint8_t frame_data[7] = {0};

uint8_t header_pos = 0;


uint8_t response_type = 0x00;

uint8_t P_addr = 0;
uint8_t P_cmd1 = 0;
uint8_t P_cmd2 = 0;
uint8_t P_dat1 = 0;
uint8_t P_dat2 = 0;
uint8_t P_chksum = 0;

uint8_t preset_id = 0;

uint8_t alarms_data = 0;

_Bool is_reboot = 0;

_Bool is_init = 0;

const _Bool steps_1A[8] = {1, 1, 0, 0, 0, 0, 0, 1};
const _Bool steps_1B[8] = {0, 1, 1, 1, 0, 0, 0, 0};
const _Bool steps_2A[8] = {0, 0, 0, 1, 1, 1, 0, 0};
const _Bool steps_2B[8] = {0, 0, 0, 0, 0, 1, 1, 1};

const uint8_t speed_ref[8] = {0x06, 0x0C, 0x12, 0x19, 0x1F, 0x25, 0x2C, 0x32};

void __attribute__((picinterrupt(("")))) myISR();
void main(void);
void UC_Init(void);
void TIMER1_Init(void);
void TIMER2_Init(void);
unsigned char CKSM_calc(uint8_t *in_dat);
void SEND_resp_general(uint8_t cmd_cksm);
void delay_wdt(uint16_t _ms);
void MOTOR_Init(void);
uint8_t SPEED_calc(uint8_t speed);
void eeprom_update(uint8_t addr, uint8_t value);
void PRESET_save(uint8_t id, uint16_t pan, uint16_t tilt);
void PRESET_load(uint8_t id, uint16_t *pan, uint16_t *tilt);
void BAUDS_set(uint8_t index);
uint8_t BAUDS_get(void);
void print_cnt(uint16_t _pan, uint16_t _tilt);
void print_val(uint16_t value);
void print_preset(uint8_t id, uint16_t pan, uint16_t tilt, char *text);
void print_cmd_mov(char *text, uint16_t pan, uint16_t tilt);

void __attribute__((picinterrupt(("")))) myISR() {
    if (PIR1bits.RCIF == 1) {
        data_receiv = RCREG;

        timeout_uart1 = 0;
        timeout_uart2 = 0;

        PORTBbits.RB3 = !PORTBbits.RB3;

        if (is_init == 1) {
            return;
        }

        if (data_receiv == 0xFF) {
            timeout_receiv = 0;
        }

        if ((buffer_index2 <= 6) || ((buffer_index2 == 0) && (data_receiv == 0xFF))) {
            switch (buffer_index1) {
                case 0:
                    buffer_data0[buffer_index2++] = data_receiv;
                    break;
                case 1:
                    buffer_data1[buffer_index2++] = data_receiv;
                    break;
                case 2:
                    buffer_data2[buffer_index2++] = data_receiv;
                    break;
                case 3:
                    buffer_data3[buffer_index2++] = data_receiv;
                    break;
                case 4:
                    buffer_data4[buffer_index2++] = data_receiv;
                    break;
                default:

                    break;
            }
        }

        if (buffer_index2 == 7) {
            buffer_index2 = 0;

            buffer_ready[buffer_index1] = 1;

            if (buffer_index1 < 4) {
                buffer_index1++;
            } else {
                buffer_index1 = 0;
            }
        }

        PIR1bits.RCIF = 0;
    } else if (PIR1bits.TMR1IF == 1) {

        PIR1bits.TMR1IF = 0;
        PIE1bits.TMR1IE = 1;
        TMR1H = 12;
        TMR1L = 38;


        PIR1bits.TMR1IF = 0;



        if (timeout_uart1 < 120) {
            timeout_uart1++;
        } else {
            timeout_uart1 = 0;

            if (timeout_uart2 < 2) {
                timeout_uart2++;
            } else {
                timeout_uart2 = 0;




                RCSTAbits.FERR = 0;
                RCSTAbits.OERR = 0;

                (void) RCREG;
                (void) RCREG;

                RCSTAbits.CREN = 0;
                RCSTAbits.SPEN = 0;

                RCSTAbits.CREN = 1;
                RCSTAbits.SPEN = 1;
            }
        }
    } else if (PIR1bits.TMR2IF == 1) {
        PIR1bits.TMR2IF = 0;

        if (timeout_receiv < 15) {
            timeout_receiv++;
        } else if (buffer_index2 > 0) {
            buffer_index2 = 0;
        }

        if (timer1_pan < timer1_pan_ref) {
            timer1_pan++;
        } else {
            timer1_pan = 0;

            if (pan_enabled == 1) {
                if (pan_direction == 0) {
                    if (pan_counter < (11700 - 1)) {
                        pan_counter++;

                        if ((pan_step_phase == 0) || (pan_step_phase > 7)) {
                            pan_step_phase = 7;
                        } else {
                            pan_step_phase--;
                        }
                    }
                } else {
                    if ((pan_counter > 0) || (is_init == 1)) {
                        pan_counter--;

                        if (pan_step_phase >= 7) {
                            pan_step_phase = 0;
                        } else {
                            pan_step_phase++;
                        }
                    }
                }

                if (pan_goto == pan_counter) {
                    if (preset_pan_enabled == 1) {
                        preset_pan_enabled = 0;

                        pan_enabled = 0;
                    }
                }

                PORTAbits.RA0 = steps_1A[pan_step_phase];
                PORTAbits.RA7 = steps_1B[pan_step_phase];
                PORTAbits.RA6 = steps_2A[pan_step_phase];
                PORTAbits.RA1 = steps_2B[pan_step_phase];
            } else {
                PORTAbits.RA0 = 0;
                PORTAbits.RA7 = 0;
                PORTAbits.RA6 = 0;
                PORTAbits.RA1 = 0;
            }


        }

        if (timer1_tilt < timer1_tilt_ref) {
            timer1_tilt++;
        } else {
            timer1_tilt = 0;

            if (tilt_enabled == 1) {
                if (tilt_direction == 0) {
                    if (tilt_counter < (2300 - 1)) {
                        tilt_counter++;

                        if ((tilt_step_phase == 0) || (tilt_step_phase > 7)) {
                            tilt_step_phase = 7;
                        } else {
                            tilt_step_phase--;
                        }
                    }
                } else {
                    if ((tilt_counter > 0) || (is_init == 1)) {
                        tilt_counter--;

                        if (tilt_step_phase >= 7) {
                            tilt_step_phase = 0;
                        } else {
                            tilt_step_phase++;
                        }
                    }
                }

                if (tilt_goto == tilt_counter) {
                    if (preset_tilt_enabled == 1) {
                        preset_tilt_enabled = 0;

                        tilt_enabled = 0;
                    }
                }

                PORTBbits.RB4 = steps_1A[tilt_step_phase];
                PORTBbits.RB5 = steps_1B[tilt_step_phase];
                PORTBbits.RB6 = steps_2A[tilt_step_phase];
                PORTBbits.RB7 = steps_2B[tilt_step_phase];
            } else {
                PORTBbits.RB4 = 0;
                PORTBbits.RB5 = 0;
                PORTBbits.RB6 = 0;
                PORTBbits.RB7 = 0;
            }
        }
    }
}

void main(void) {
    UC_Init();

    UART_Init();

    TIMER1_Init();

    TIMER2_Init();

    delay_wdt(500);

    UART_Write_Text_CRLF("\r\n\r\nStart");

    UART_Write_Text_CRLF("Goto PAN and TILT Home");

    delay_wdt(50);

    MOTOR_Init();

    UART_Write_Text_CRLF("Waiting for commands");

    while (1) {
        __asm("clrwdt");

        if (buffer_ready[frame_index] == 1) {
            buffer_ready[frame_index] = 0;

            for (uint8_t i = 0; i < 7; i++) {
                if (frame_index == 0) {
                    frame_data[i] = buffer_data0[i];
                } else if (frame_index == 1) {
                    frame_data[i] = buffer_data1[i];
                } else if (frame_index == 2) {
                    frame_data[i] = buffer_data2[i];
                } else if (frame_index == 3) {
                    frame_data[i] = buffer_data3[i];
                } else if (frame_index == 4) {
                    frame_data[i] = buffer_data4[i];
                }


            }

            if (frame_data[0] == 0xFF) {
                uint8_t chksum_calc = 0;

                for (uint8_t m = 1; m <= 5; m++) {
                    chksum_calc += frame_data[m];
                }

                if (chksum_calc == frame_data[6]) {

                    P_addr = frame_data[1];
                    P_cmd1 = frame_data[2];
                    P_cmd2 = frame_data[3];
                    P_dat1 = frame_data[4];
                    P_dat2 = frame_data[5];
                    P_chksum = frame_data[6];

                    response_type = 0x00;


                    if (P_addr == 0x01) {
                        if ((P_cmd1 == 0xF0) && (P_cmd2 == 0x83) && (P_dat1 == 0x00) && (P_dat2 == 0x01)) {
                            UART_Write_Text_CRLF("REBOOT");

                            while (1) {

                            }
                        } else if ((P_cmd1 == 0x00) && (P_cmd2 == 0x67) && (P_dat1 == 0x00)) {

                            if (is_reboot == 1) {
                                BAUDS_set(P_dat2);

                                UART_Write_Text("SET BAUD RATE");

                                switch (P_dat2) {
                                    case 0x00:
                                        UART_Write_Text_CRLF("2400");
                                        break;
                                    case 0x01:
                                        UART_Write_Text_CRLF("4800");
                                        break;
                                    case 0x03:
                                        UART_Write_Text_CRLF("19200");
                                        break;
                                    case 0x04:
                                        UART_Write_Text_CRLF("38400");
                                        break;
                                    case 0x05:
                                        UART_Write_Text_CRLF("115200");
                                        break;
                                    default:

                                        UART_Write_Text_CRLF("9600");
                                        break;
                                }

                                UART_Write_Text("\r\nPLEASE ");
                            } else {
                                UART_Write_Text("\r\nNEED ");
                            }

                            UART_Write_Text_CRLF("REBOOT");
                        } else if ((P_cmd1 == 0x00) && (P_cmd2 == 0x00) && (P_dat1 == 0x00) && (P_dat2 == 0x00)) {
                            pan_enabled = 0;
                            tilt_enabled = 0;
                            preset_pan_enabled = 0;
                            preset_tilt_enabled = 0;

                            response_type = 0x01;
                            UART_Write_Text("STOP (");
                            print_cnt(pan_counter, tilt_counter);
                            UART_Write_Text_CRLF(")");

                        } else if ((P_cmd1 == 0x00) && (P_cmd2 == 0x03) && (P_dat1 == 0x00)) {
                            preset_id = P_dat2;
                            PRESET_save(preset_id, pan_counter, tilt_counter);
                            response_type = 0x01;

                            print_preset(preset_id, pan_counter, tilt_counter, "SET PRESET ");
                        } else if ((P_cmd1 == 0x00) && (P_cmd2 == 0x05) && (P_dat1 == 0x00)) {
                            preset_id = P_dat2;
                            PRESET_save(preset_id, 0xFFFF, 0xFFFF);

                            uint16_t pan_tmp = 0;
                            uint16_t tilt_tmp = 0;
                            PRESET_load(preset_id, &pan_tmp, &tilt_tmp);
                            pan_goto = pan_tmp;
                            tilt_goto = tilt_tmp;

                            response_type = 0x01;

                            print_preset(preset_id, pan_goto, tilt_goto, "CLEAR PRESET ");
                        } else if ((P_cmd1 == 0x00) && (P_cmd2 == 0x07) && (P_dat1 == 0x00)) {
                            preset_id = P_dat2;

                            uint16_t pan_tmp = 0;
                            uint16_t tilt_tmp = 0;
                            PRESET_load(preset_id, &pan_tmp, &tilt_tmp);
                            pan_goto = pan_tmp;
                            tilt_goto = tilt_tmp;

                            preset_pan_enabled = 1;
                            preset_pan_enabled_old = 0;

                            pan_speed = 0x32;
                            timer1_pan_ref = SPEED_calc(pan_speed);
                            pan_enabled = 1;

                            if (pan_goto < 11700) {
                                if (pan_goto > pan_counter) {
                                    pan_direction = 0;
                                } else if (pan_goto < pan_counter) {
                                    pan_direction = 1;
                                } else {
                                    preset_pan_enabled = 0;
                                    pan_enabled = 0;
                                }
                            } else {
                                preset_pan_enabled = 0;
                                pan_enabled = 0;
                            }

                            preset_tilt_enabled = 1;
                            preset_tilt_enabled_old = 0;

                            tilt_speed = 0x32;
                            timer1_tilt_ref = SPEED_calc(tilt_speed);
                            tilt_enabled = 1;

                            if (tilt_goto < 2300) {
                                if (tilt_goto > tilt_counter) {
                                    tilt_direction = 0;
                                } else if (tilt_goto < tilt_counter) {
                                    tilt_direction = 1;
                                } else {
                                    preset_tilt_enabled = 0;
                                    tilt_enabled = 0;
                                }
                            } else {
                                preset_tilt_enabled = 0;
                                tilt_enabled = 0;
                            }

                            response_type = 0x01;

                            print_preset(preset_id, pan_goto, tilt_goto, "GOTO PRESET ");
                        } else {
                            if ((P_cmd2 & 0x04) == 0x04) {
                                pan_speed = P_dat1;
                                timer1_pan_ref = SPEED_calc(pan_speed);
                                pan_direction = 0;
                                pan_enabled = 1;

                                preset_pan_enabled = 0;
                                preset_tilt_enabled = 0;

                                response_type = 0x01;
                                is_reboot = 0;

                                print_cmd_mov("LEFT", pan_counter, tilt_counter);
                            } else if ((P_cmd2 & 0x02) == 0x02) {
                                pan_speed = P_dat1;
                                timer1_pan_ref = SPEED_calc(pan_speed);
                                pan_direction = 1;
                                pan_enabled = 1;

                                preset_pan_enabled = 0;
                                preset_tilt_enabled = 0;

                                response_type = 0x01;
                                is_reboot = 0;

                                print_cmd_mov("RIGHT", pan_counter, tilt_counter);
                            }

                            if ((P_cmd2 & 0x10) == 0x10) {
                                tilt_speed = P_dat2;
                                timer1_tilt_ref = SPEED_calc(tilt_speed);
                                tilt_direction = 0;
                                tilt_enabled = 1;

                                preset_pan_enabled = 0;
                                preset_tilt_enabled = 0;

                                response_type = 0x01;
                                is_reboot = 0;

                                print_cmd_mov("DOWN", pan_counter, tilt_counter);
                            } else if ((P_cmd2 & 0x08) == 0x08) {
                                tilt_speed = P_dat2;
                                timer1_tilt_ref = SPEED_calc(tilt_speed);
                                tilt_direction = 1;
                                tilt_enabled = 1;

                                preset_pan_enabled = 0;
                                preset_tilt_enabled = 0;

                                response_type = 0x01;
                                is_reboot = 0;

                                print_cmd_mov("UP", pan_counter, tilt_counter);
                            }
                        }
                    }

                    if (response_type == 0x01) {

                    }
                }
            }
        } else {
            if (frame_index < 4) {
                frame_index++;
            } else {

                frame_index = 0;
            }


        }
    }

    return;
}

void UC_Init(void) {
    PCONbits.OSCF = 1;


    if ((PCONbits.nPOR == 1) && (PCONbits.nBOR == 1)) {

        is_reboot = 1;
    }

    PORTA = 0;
    PORTB = 0;

    CMCON = 7;

    OPTION_REGbits.nRBPU = 1;
    OPTION_REGbits.PSA = 1;
    OPTION_REGbits.PS = 0b111;




    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
# 660 "main.c"
    TRISA = 0b00000000;
# 670 "main.c"
    TRISB = 0b00000010;
# 679 "main.c"
}

void TIMER1_Init(void) {



    T1CONbits.T1CKPS1 = 1;
    T1CONbits.T1CKPS0 = 1;
    T1CONbits.T1OSCEN = 0;
    T1CONbits.nT1SYNC = 1;
    T1CONbits.TMR1CS = 0;
    T1CONbits.TMR1ON = 1;


    TMR1H = 12;
    TMR1L = 38;

    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
}

void TIMER2_Init(void) {



    T2CONbits.TOUTPS = 0;
    T2CONbits.T2CKPS = 1;
    PR2 = 250;

    PIR1bits.TMR2IF = 0;
    PIE1bits.TMR2IE = 1;

    T2CONbits.TMR2ON = 1;
}
# 757 "main.c"
void delay_wdt(uint16_t _ms) {
    __asm("clrwdt");

    while (_ms--) {

        __asm("clrwdt");
        _delay((unsigned long)((1)*(4000000/4000.0)));
    };
}

void MOTOR_Init(void) {
    is_init = 1;
# 821 "main.c"
    pan_speed = 0x32;
    pan_direction = 1;
    pan_enabled = 1;


    tilt_speed = 0x32;
    tilt_direction = 1;
    tilt_enabled = 1;


    delay_wdt(6000);

    tilt_enabled = 0;

    tilt_counter = 0;

    delay_wdt(100);


    tilt_speed = 0x32;
    tilt_direction = 0;
    tilt_enabled = 1;

    delay_wdt(750);

    tilt_enabled = 0;

    tilt_counter = 0;



    delay_wdt(15650);

    pan_enabled = 0;

    pan_counter = 0;

    delay_wdt(100);


    pan_speed = 0x32;
    pan_direction = 0;
    pan_enabled = 1;

    delay_wdt(500);

    pan_enabled = 0;

    pan_counter = 0;
# 890 "main.c"
    pan_speed = 0x32;
    pan_direction = 0;
    pan_enabled = 1;


    tilt_speed = 0x32;
    tilt_direction = 0;
    tilt_enabled = 1;


    delay_wdt(1000);

    tilt_enabled = 0;



    delay_wdt(3450);

    pan_enabled = 0;

    is_init = 0;
}

uint8_t SPEED_calc(uint8_t speed) {
    uint8_t sp_calc = 0;

    if (speed > 0x32) {
        speed = 0x32;
    }

    if (speed < 0x06) {
        speed = 0x06;
    }

    sp_calc = 1 + ((0x32 - speed) / 2);

    if (sp_calc < 1) {
        sp_calc = 1;
    }

    if (sp_calc > 19) {

        sp_calc = 19;
    }

    return sp_calc;
}

void eeprom_update(uint8_t addr, uint8_t value) {
    if (value != eeprom_read(addr)) {
        eeprom_write(addr, value);
    }
}

void PRESET_save(uint8_t id, uint16_t pan, uint16_t tilt) {
    uint8_t _addr = id * 4;

    if (id < 50) {

        eeprom_update(_addr, pan & 0xFF);
        eeprom_update(_addr + 1, (pan >> 8) & 0xFF);

        eeprom_update(_addr + 2, tilt & 0xFF);
        eeprom_update(_addr + 3, (tilt >> 8) & 0xFF);
    }
}

void PRESET_load(uint8_t id, uint16_t *pan, uint16_t *tilt) {
    uint8_t _addr = id * 4;

    if (id < 50) {

        *pan = (uint16_t) (eeprom_read(_addr));
        *pan |= (uint16_t) (eeprom_read(_addr + 1) << 8);

        *tilt = (uint16_t) (eeprom_read(_addr + 2));
        *tilt |= (uint16_t) (eeprom_read(_addr + 3) << 8);
    }
}

void BAUDS_set(uint8_t index) {

    eeprom_update(0xFF, index);
}

uint8_t BAUDS_get(void) {

    return eeprom_read(0xFF);
}

void print_cnt(uint16_t _pan, uint16_t _tilt) {
    print_val(_pan);

    UART_Write_Text(", ");

    print_val(_tilt);
}

void print_val(uint16_t value) {
    uint16_t val10000 = 0;
    uint16_t val1000 = 0;
    uint16_t val100 = 0;
    uint16_t val10 = 0;
    uint16_t val1 = 0;

    val10000 = value / 10000;
    value -= val10000 * 10000;

    val1000 = value / 1000;
    value -= val1000 * 1000;

    val100 = value / 100;
    value -= val100 * 100;

    val10 = value / 10;
    value -= val10 * 10;

    val1 = value;

    val10000 += 48;
    val1000 += 48;
    val100 += 48;
    val10 += 48;
    val1 += 48;

    if (val10000 > 0) {
        UART_Write((uint8_t) val10000);
    }

    if ((val10000 > 0) || (val1000 > 0)) {
        UART_Write((uint8_t) val1000);
    }

    if ((val10000 > 0) || (val1000 > 0) || (val100 > 0)) {
        UART_Write((uint8_t) val100);
    }
    if ((val10000 > 0) || (val1000 > 0) || (val100 > 0) || (val10 > 0)) {
        UART_Write((uint8_t) val10);
    }

    UART_Write((uint8_t) val1);
}

void print_preset(uint8_t id, uint16_t pan, uint16_t tilt, char *text) {
    uint8_t preset_id_10 = id / 10;
    uint8_t preset_id_1 = id - (preset_id_10 * 10);

    preset_id_10 += 48;
    preset_id_1 += 48;

    UART_Write_Text(text);
    UART_Write(preset_id_10);
    UART_Write(preset_id_1);
    UART_Write_Text(" (");
    print_cnt(pan, tilt);
    UART_Write_Text_CRLF(")");
}

void print_cmd_mov(char *text, uint16_t pan, uint16_t tilt) {
    UART_Write_Text(text);
    UART_Write_Text(" (");
    print_cnt(pan, tilt);
    UART_Write_Text_CRLF(")");
}

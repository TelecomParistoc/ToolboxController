

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set channel_AN0 aliases
#define channel_AN0_TRIS               TRISA0
#define channel_AN0_LAT                LATA0
#define channel_AN0_PORT               PORTAbits.RA0
#define channel_AN0_ANS                ANSA0
#define channel_AN0_SetHigh()    do { LATA0 = 1; } while(0)
#define channel_AN0_SetLow()   do { LATA0 = 0; } while(0)
#define channel_AN0_Toggle()   do { LATA0 = ~LATA0; } while(0)
#define channel_AN0_GetValue()         PORTAbits.RA0
#define channel_AN0_SetDigitalInput()    do { TRISA0 = 1; } while(0)
#define channel_AN0_SetDigitalOutput()   do { TRISA0 = 0; } while(0)

#define channel_AN0_SetAnalogMode()   do { ANSA0 = 1; } while(0)
#define channel_AN0_SetDigitalMode()   do { ANSA0 = 0; } while(0)
// get/set LED1 aliases
#define LED1_TRIS               TRISA2
#define LED1_LAT                LATA2
#define LED1_PORT               PORTAbits.RA2
#define LED1_ANS                ANSA2
#define LED1_SetHigh()    do { LATA2 = 1; } while(0)
#define LED1_SetLow()   do { LATA2 = 0; } while(0)
#define LED1_Toggle()   do { LATA2 = ~LATA2; } while(0)
#define LED1_GetValue()         PORTAbits.RA2
#define LED1_SetDigitalInput()    do { TRISA2 = 1; } while(0)
#define LED1_SetDigitalOutput()   do { TRISA2 = 0; } while(0)

#define LED1_SetAnalogMode()   do { ANSA2 = 1; } while(0)
#define LED1_SetDigitalMode()   do { ANSA2 = 0; } while(0)
// get/set LED2 aliases
#define LED2_TRIS               TRISA3
#define LED2_LAT                LATA3
#define LED2_PORT               PORTAbits.RA3
#define LED2_ANS                ANSA3
#define LED2_SetHigh()    do { LATA3 = 1; } while(0)
#define LED2_SetLow()   do { LATA3 = 0; } while(0)
#define LED2_Toggle()   do { LATA3 = ~LATA3; } while(0)
#define LED2_GetValue()         PORTAbits.RA3
#define LED2_SetDigitalInput()    do { TRISA3 = 1; } while(0)
#define LED2_SetDigitalOutput()   do { TRISA3 = 0; } while(0)

#define LED2_SetAnalogMode()   do { ANSA3 = 1; } while(0)
#define LED2_SetDigitalMode()   do { ANSA3 = 0; } while(0)
// get/set LED3 aliases
#define LED3_TRIS               TRISA4
#define LED3_LAT                LATA4
#define LED3_PORT               PORTAbits.RA4
#define LED3_SetHigh()    do { LATA4 = 1; } while(0)
#define LED3_SetLow()   do { LATA4 = 0; } while(0)
#define LED3_Toggle()   do { LATA4 = ~LATA4; } while(0)
#define LED3_GetValue()         PORTAbits.RA4
#define LED3_SetDigitalInput()    do { TRISA4 = 1; } while(0)
#define LED3_SetDigitalOutput()   do { TRISA4 = 0; } while(0)

// get/set LED4 aliases
#define LED4_TRIS               TRISA5
#define LED4_LAT                LATA5
#define LED4_PORT               PORTAbits.RA5
#define LED4_ANS                ANSA5
#define LED4_SetHigh()    do { LATA5 = 1; } while(0)
#define LED4_SetLow()   do { LATA5 = 0; } while(0)
#define LED4_Toggle()   do { LATA5 = ~LATA5; } while(0)
#define LED4_GetValue()         PORTAbits.RA5
#define LED4_SetDigitalInput()    do { TRISA5 = 1; } while(0)
#define LED4_SetDigitalOutput()   do { TRISA5 = 0; } while(0)

#define LED4_SetAnalogMode()   do { ANSA5 = 1; } while(0)
#define LED4_SetDigitalMode()   do { ANSA5 = 0; } while(0)
// get/set LOGICR aliases
#define LOGICR_TRIS               TRISA6
#define LOGICR_LAT                LATA6
#define LOGICR_PORT               PORTAbits.RA6
#define LOGICR_SetHigh()    do { LATA6 = 1; } while(0)
#define LOGICR_SetLow()   do { LATA6 = 0; } while(0)
#define LOGICR_Toggle()   do { LATA6 = ~LATA6; } while(0)
#define LOGICR_GetValue()         PORTAbits.RA6
#define LOGICR_SetDigitalInput()    do { TRISA6 = 1; } while(0)
#define LOGICR_SetDigitalOutput()   do { TRISA6 = 0; } while(0)

// get/set MOTORG aliases
#define MOTORG_TRIS               TRISA7
#define MOTORG_LAT                LATA7
#define MOTORG_PORT               PORTAbits.RA7
#define MOTORG_SetHigh()    do { LATA7 = 1; } while(0)
#define MOTORG_SetLow()   do { LATA7 = 0; } while(0)
#define MOTORG_Toggle()   do { LATA7 = ~LATA7; } while(0)
#define MOTORG_GetValue()         PORTAbits.RA7
#define MOTORG_SetDigitalInput()    do { TRISA7 = 1; } while(0)
#define MOTORG_SetDigitalOutput()   do { TRISA7 = 0; } while(0)

// get/set SEN1 aliases
#define SEN1_TRIS               TRISB0
#define SEN1_LAT                LATB0
#define SEN1_PORT               PORTBbits.RB0
#define SEN1_WPU                WPUB0
#define SEN1_ANS                ANSB0
#define SEN1_SetHigh()    do { LATB0 = 1; } while(0)
#define SEN1_SetLow()   do { LATB0 = 0; } while(0)
#define SEN1_Toggle()   do { LATB0 = ~LATB0; } while(0)
#define SEN1_GetValue()         PORTBbits.RB0
#define SEN1_SetDigitalInput()    do { TRISB0 = 1; } while(0)
#define SEN1_SetDigitalOutput()   do { TRISB0 = 0; } while(0)

#define SEN1_SetPullup()    do { WPUB0 = 1; } while(0)
#define SEN1_ResetPullup()   do { WPUB0 = 0; } while(0)
#define SEN1_SetAnalogMode()   do { ANSB0 = 1; } while(0)
#define SEN1_SetDigitalMode()   do { ANSB0 = 0; } while(0)
// get/set BT3 aliases
#define BT3_TRIS               TRISB1
#define BT3_LAT                LATB1
#define BT3_PORT               PORTBbits.RB1
#define BT3_WPU                WPUB1
#define BT3_ANS                ANSB1
#define BT3_SetHigh()    do { LATB1 = 1; } while(0)
#define BT3_SetLow()   do { LATB1 = 0; } while(0)
#define BT3_Toggle()   do { LATB1 = ~LATB1; } while(0)
#define BT3_GetValue()         PORTBbits.RB1
#define BT3_SetDigitalInput()    do { TRISB1 = 1; } while(0)
#define BT3_SetDigitalOutput()   do { TRISB1 = 0; } while(0)

#define BT3_SetPullup()    do { WPUB1 = 1; } while(0)
#define BT3_ResetPullup()   do { WPUB1 = 0; } while(0)
#define BT3_SetAnalogMode()   do { ANSB1 = 1; } while(0)
#define BT3_SetDigitalMode()   do { ANSB1 = 0; } while(0)
// get/set BT2 aliases
#define BT2_TRIS               TRISB2
#define BT2_LAT                LATB2
#define BT2_PORT               PORTBbits.RB2
#define BT2_WPU                WPUB2
#define BT2_ANS                ANSB2
#define BT2_SetHigh()    do { LATB2 = 1; } while(0)
#define BT2_SetLow()   do { LATB2 = 0; } while(0)
#define BT2_Toggle()   do { LATB2 = ~LATB2; } while(0)
#define BT2_GetValue()         PORTBbits.RB2
#define BT2_SetDigitalInput()    do { TRISB2 = 1; } while(0)
#define BT2_SetDigitalOutput()   do { TRISB2 = 0; } while(0)

#define BT2_SetPullup()    do { WPUB2 = 1; } while(0)
#define BT2_ResetPullup()   do { WPUB2 = 0; } while(0)
#define BT2_SetAnalogMode()   do { ANSB2 = 1; } while(0)
#define BT2_SetDigitalMode()   do { ANSB2 = 0; } while(0)
// get/set BT1 aliases
#define BT1_TRIS               TRISB3
#define BT1_LAT                LATB3
#define BT1_PORT               PORTBbits.RB3
#define BT1_WPU                WPUB3
#define BT1_ANS                ANSB3
#define BT1_SetHigh()    do { LATB3 = 1; } while(0)
#define BT1_SetLow()   do { LATB3 = 0; } while(0)
#define BT1_Toggle()   do { LATB3 = ~LATB3; } while(0)
#define BT1_GetValue()         PORTBbits.RB3
#define BT1_SetDigitalInput()    do { TRISB3 = 1; } while(0)
#define BT1_SetDigitalOutput()   do { TRISB3 = 0; } while(0)

#define BT1_SetPullup()    do { WPUB3 = 1; } while(0)
#define BT1_ResetPullup()   do { WPUB3 = 0; } while(0)
#define BT1_SetAnalogMode()   do { ANSB3 = 1; } while(0)
#define BT1_SetDigitalMode()   do { ANSB3 = 0; } while(0)
// get/set SEN2 aliases
#define SEN2_TRIS               TRISB4
#define SEN2_LAT                LATB4
#define SEN2_PORT               PORTBbits.RB4
#define SEN2_WPU                WPUB4
#define SEN2_ANS                ANSB4
#define SEN2_SetHigh()    do { LATB4 = 1; } while(0)
#define SEN2_SetLow()   do { LATB4 = 0; } while(0)
#define SEN2_Toggle()   do { LATB4 = ~LATB4; } while(0)
#define SEN2_GetValue()         PORTBbits.RB4
#define SEN2_SetDigitalInput()    do { TRISB4 = 1; } while(0)
#define SEN2_SetDigitalOutput()   do { TRISB4 = 0; } while(0)

#define SEN2_SetPullup()    do { WPUB4 = 1; } while(0)
#define SEN2_ResetPullup()   do { WPUB4 = 0; } while(0)
#define SEN2_SetAnalogMode()   do { ANSB4 = 1; } while(0)
#define SEN2_SetDigitalMode()   do { ANSB4 = 0; } while(0)
// get/set SEN3 aliases
#define SEN3_TRIS               TRISB5
#define SEN3_LAT                LATB5
#define SEN3_PORT               PORTBbits.RB5
#define SEN3_WPU                WPUB5
#define SEN3_ANS                ANSB5
#define SEN3_SetHigh()    do { LATB5 = 1; } while(0)
#define SEN3_SetLow()   do { LATB5 = 0; } while(0)
#define SEN3_Toggle()   do { LATB5 = ~LATB5; } while(0)
#define SEN3_GetValue()         PORTBbits.RB5
#define SEN3_SetDigitalInput()    do { TRISB5 = 1; } while(0)
#define SEN3_SetDigitalOutput()   do { TRISB5 = 0; } while(0)

#define SEN3_SetPullup()    do { WPUB5 = 1; } while(0)
#define SEN3_ResetPullup()   do { WPUB5 = 0; } while(0)
#define SEN3_SetAnalogMode()   do { ANSB5 = 1; } while(0)
#define SEN3_SetDigitalMode()   do { ANSB5 = 0; } while(0)
// get/set SEN4 aliases
#define SEN4_TRIS               TRISB6
#define SEN4_LAT                LATB6
#define SEN4_PORT               PORTBbits.RB6
#define SEN4_WPU                WPUB6
#define SEN4_SetHigh()    do { LATB6 = 1; } while(0)
#define SEN4_SetLow()   do { LATB6 = 0; } while(0)
#define SEN4_Toggle()   do { LATB6 = ~LATB6; } while(0)
#define SEN4_GetValue()         PORTBbits.RB6
#define SEN4_SetDigitalInput()    do { TRISB6 = 1; } while(0)
#define SEN4_SetDigitalOutput()   do { TRISB6 = 0; } while(0)

#define SEN4_SetPullup()    do { WPUB6 = 1; } while(0)
#define SEN4_ResetPullup()   do { WPUB6 = 0; } while(0)
// get/set SEN5 aliases
#define SEN5_TRIS               TRISB7
#define SEN5_LAT                LATB7
#define SEN5_PORT               PORTBbits.RB7
#define SEN5_WPU                WPUB7
#define SEN5_SetHigh()    do { LATB7 = 1; } while(0)
#define SEN5_SetLow()   do { LATB7 = 0; } while(0)
#define SEN5_Toggle()   do { LATB7 = ~LATB7; } while(0)
#define SEN5_GetValue()         PORTBbits.RB7
#define SEN5_SetDigitalInput()    do { TRISB7 = 1; } while(0)
#define SEN5_SetDigitalOutput()   do { TRISB7 = 0; } while(0)

#define SEN5_SetPullup()    do { WPUB7 = 1; } while(0)
#define SEN5_ResetPullup()   do { WPUB7 = 0; } while(0)
// get/set LOGICG aliases
#define LOGICG_TRIS               TRISC0
#define LOGICG_LAT                LATC0
#define LOGICG_PORT               PORTCbits.RC0
#define LOGICG_SetHigh()    do { LATC0 = 1; } while(0)
#define LOGICG_SetLow()   do { LATC0 = 0; } while(0)
#define LOGICG_Toggle()   do { LATC0 = ~LATC0; } while(0)
#define LOGICG_GetValue()         PORTCbits.RC0
#define LOGICG_SetDigitalInput()    do { TRISC0 = 1; } while(0)
#define LOGICG_SetDigitalOutput()   do { TRISC0 = 0; } while(0)

// get/set P2A aliases
#define P2A_TRIS               TRISC1
#define P2A_LAT                LATC1
#define P2A_PORT               PORTCbits.RC1
#define P2A_SetHigh()    do { LATC1 = 1; } while(0)
#define P2A_SetLow()   do { LATC1 = 0; } while(0)
#define P2A_Toggle()   do { LATC1 = ~LATC1; } while(0)
#define P2A_GetValue()         PORTCbits.RC1
#define P2A_SetDigitalInput()    do { TRISC1 = 1; } while(0)
#define P2A_SetDigitalOutput()   do { TRISC1 = 0; } while(0)

// get/set P1A aliases
#define P1A_TRIS               TRISC2
#define P1A_LAT                LATC2
#define P1A_PORT               PORTCbits.RC2
#define P1A_ANS                ANSC2
#define P1A_SetHigh()    do { LATC2 = 1; } while(0)
#define P1A_SetLow()   do { LATC2 = 0; } while(0)
#define P1A_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define P1A_GetValue()         PORTCbits.RC2
#define P1A_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define P1A_SetDigitalOutput()   do { TRISC2 = 0; } while(0)

#define P1A_SetAnalogMode()   do { ANSC2 = 1; } while(0)
#define P1A_SetDigitalMode()   do { ANSC2 = 0; } while(0)
// get/set SCL1 aliases
#define SCL1_TRIS               TRISC3
#define SCL1_LAT                LATC3
#define SCL1_PORT               PORTCbits.RC3
#define SCL1_ANS                ANSC3
#define SCL1_SetHigh()    do { LATC3 = 1; } while(0)
#define SCL1_SetLow()   do { LATC3 = 0; } while(0)
#define SCL1_Toggle()   do { LATC3 = ~LATC3; } while(0)
#define SCL1_GetValue()         PORTCbits.RC3
#define SCL1_SetDigitalInput()    do { TRISC3 = 1; } while(0)
#define SCL1_SetDigitalOutput()   do { TRISC3 = 0; } while(0)

#define SCL1_SetAnalogMode()   do { ANSC3 = 1; } while(0)
#define SCL1_SetDigitalMode()   do { ANSC3 = 0; } while(0)
// get/set SDA1 aliases
#define SDA1_TRIS               TRISC4
#define SDA1_LAT                LATC4
#define SDA1_PORT               PORTCbits.RC4
#define SDA1_ANS                ANSC4
#define SDA1_SetHigh()    do { LATC4 = 1; } while(0)
#define SDA1_SetLow()   do { LATC4 = 0; } while(0)
#define SDA1_Toggle()   do { LATC4 = ~LATC4; } while(0)
#define SDA1_GetValue()         PORTCbits.RC4
#define SDA1_SetDigitalInput()    do { TRISC4 = 1; } while(0)
#define SDA1_SetDigitalOutput()   do { TRISC4 = 0; } while(0)

#define SDA1_SetAnalogMode()   do { ANSC4 = 1; } while(0)
#define SDA1_SetDigitalMode()   do { ANSC4 = 0; } while(0)
// get/set DETEC5 aliases
#define DETEC5_TRIS               TRISC5
#define DETEC5_LAT                LATC5
#define DETEC5_PORT               PORTCbits.RC5
#define DETEC5_ANS                ANSC5
#define DETEC5_SetHigh()    do { LATC5 = 1; } while(0)
#define DETEC5_SetLow()   do { LATC5 = 0; } while(0)
#define DETEC5_Toggle()   do { LATC5 = ~LATC5; } while(0)
#define DETEC5_GetValue()         PORTCbits.RC5
#define DETEC5_SetDigitalInput()    do { TRISC5 = 1; } while(0)
#define DETEC5_SetDigitalOutput()   do { TRISC5 = 0; } while(0)

#define DETEC5_SetAnalogMode()   do { ANSC5 = 1; } while(0)
#define DETEC5_SetDigitalMode()   do { ANSC5 = 0; } while(0)
// get/set INTOUT aliases
#define INTOUT_TRIS               TRISD0
#define INTOUT_LAT                LATD0
#define INTOUT_PORT               PORTDbits.RD0
#define INTOUT_ANS                ANSD0
#define INTOUT_SetHigh()    do { LATD0 = 1; } while(0)
#define INTOUT_SetLow()   do { LATD0 = 0; } while(0)
#define INTOUT_Toggle()   do { LATD0 = ~LATD0; } while(0)
#define INTOUT_GetValue()         PORTDbits.RD0
#define INTOUT_SetDigitalInput()    do { TRISD0 = 1; } while(0)
#define INTOUT_SetDigitalOutput()   do { TRISD0 = 0; } while(0)

#define INTOUT_SetAnalogMode()   do { ANSD0 = 1; } while(0)
#define INTOUT_SetDigitalMode()   do { ANSD0 = 0; } while(0)
// get/set CCP4 aliases
#define CCP4_TRIS               TRISD1
#define CCP4_LAT                LATD1
#define CCP4_PORT               PORTDbits.RD1
#define CCP4_ANS                ANSD1
#define CCP4_SetHigh()    do { LATD1 = 1; } while(0)
#define CCP4_SetLow()   do { LATD1 = 0; } while(0)
#define CCP4_Toggle()   do { LATD1 = ~LATD1; } while(0)
#define CCP4_GetValue()         PORTDbits.RD1
#define CCP4_SetDigitalInput()    do { TRISD1 = 1; } while(0)
#define CCP4_SetDigitalOutput()   do { TRISD1 = 0; } while(0)

#define CCP4_SetAnalogMode()   do { ANSD1 = 1; } while(0)
#define CCP4_SetDigitalMode()   do { ANSD1 = 0; } while(0)
// get/set DETEC4 aliases
#define DETEC4_TRIS               TRISD2
#define DETEC4_LAT                LATD2
#define DETEC4_PORT               PORTDbits.RD2
#define DETEC4_ANS                ANSD2
#define DETEC4_SetHigh()    do { LATD2 = 1; } while(0)
#define DETEC4_SetLow()   do { LATD2 = 0; } while(0)
#define DETEC4_Toggle()   do { LATD2 = ~LATD2; } while(0)
#define DETEC4_GetValue()         PORTDbits.RD2
#define DETEC4_SetDigitalInput()    do { TRISD2 = 1; } while(0)
#define DETEC4_SetDigitalOutput()   do { TRISD2 = 0; } while(0)

#define DETEC4_SetAnalogMode()   do { ANSD2 = 1; } while(0)
#define DETEC4_SetDigitalMode()   do { ANSD2 = 0; } while(0)
// get/set DETEC3 aliases
#define DETEC3_TRIS               TRISD3
#define DETEC3_LAT                LATD3
#define DETEC3_PORT               PORTDbits.RD3
#define DETEC3_ANS                ANSD3
#define DETEC3_SetHigh()    do { LATD3 = 1; } while(0)
#define DETEC3_SetLow()   do { LATD3 = 0; } while(0)
#define DETEC3_Toggle()   do { LATD3 = ~LATD3; } while(0)
#define DETEC3_GetValue()         PORTDbits.RD3
#define DETEC3_SetDigitalInput()    do { TRISD3 = 1; } while(0)
#define DETEC3_SetDigitalOutput()   do { TRISD3 = 0; } while(0)

#define DETEC3_SetAnalogMode()   do { ANSD3 = 1; } while(0)
#define DETEC3_SetDigitalMode()   do { ANSD3 = 0; } while(0)
// get/set DETEC2 aliases
#define DETEC2_TRIS               TRISD4
#define DETEC2_LAT                LATD4
#define DETEC2_PORT               PORTDbits.RD4
#define DETEC2_ANS                ANSD4
#define DETEC2_SetHigh()    do { LATD4 = 1; } while(0)
#define DETEC2_SetLow()   do { LATD4 = 0; } while(0)
#define DETEC2_Toggle()   do { LATD4 = ~LATD4; } while(0)
#define DETEC2_GetValue()         PORTDbits.RD4
#define DETEC2_SetDigitalInput()    do { TRISD4 = 1; } while(0)
#define DETEC2_SetDigitalOutput()   do { TRISD4 = 0; } while(0)

#define DETEC2_SetAnalogMode()   do { ANSD4 = 1; } while(0)
#define DETEC2_SetDigitalMode()   do { ANSD4 = 0; } while(0)
// get/set DETEC1 aliases
#define DETEC1_TRIS               TRISD5
#define DETEC1_LAT                LATD5
#define DETEC1_PORT               PORTDbits.RD5
#define DETEC1_ANS                ANSD5
#define DETEC1_SetHigh()    do { LATD5 = 1; } while(0)
#define DETEC1_SetLow()   do { LATD5 = 0; } while(0)
#define DETEC1_Toggle()   do { LATD5 = ~LATD5; } while(0)
#define DETEC1_GetValue()         PORTDbits.RD5
#define DETEC1_SetDigitalInput()    do { TRISD5 = 1; } while(0)
#define DETEC1_SetDigitalOutput()   do { TRISD5 = 0; } while(0)

#define DETEC1_SetAnalogMode()   do { ANSD5 = 1; } while(0)
#define DETEC1_SetDigitalMode()   do { ANSD5 = 0; } while(0)
// get/set TX2 aliases
#define TX2_TRIS               TRISD6
#define TX2_LAT                LATD6
#define TX2_PORT               PORTDbits.RD6
#define TX2_ANS                ANSD6
#define TX2_SetHigh()    do { LATD6 = 1; } while(0)
#define TX2_SetLow()   do { LATD6 = 0; } while(0)
#define TX2_Toggle()   do { LATD6 = ~LATD6; } while(0)
#define TX2_GetValue()         PORTDbits.RD6
#define TX2_SetDigitalInput()    do { TRISD6 = 1; } while(0)
#define TX2_SetDigitalOutput()   do { TRISD6 = 0; } while(0)

#define TX2_SetAnalogMode()   do { ANSD6 = 1; } while(0)
#define TX2_SetDigitalMode()   do { ANSD6 = 0; } while(0)
// get/set RX2 aliases
#define RX2_TRIS               TRISD7
#define RX2_LAT                LATD7
#define RX2_PORT               PORTDbits.RD7
#define RX2_ANS                ANSD7
#define RX2_SetHigh()    do { LATD7 = 1; } while(0)
#define RX2_SetLow()   do { LATD7 = 0; } while(0)
#define RX2_Toggle()   do { LATD7 = ~LATD7; } while(0)
#define RX2_GetValue()         PORTDbits.RD7
#define RX2_SetDigitalInput()    do { TRISD7 = 1; } while(0)
#define RX2_SetDigitalOutput()   do { TRISD7 = 0; } while(0)

#define RX2_SetAnalogMode()   do { ANSD7 = 1; } while(0)
#define RX2_SetDigitalMode()   do { ANSD7 = 0; } while(0)
// get/set P3A aliases
#define P3A_TRIS               TRISE0
#define P3A_LAT                LATE0
#define P3A_PORT               PORTEbits.RE0
#define P3A_ANS                ANSE0
#define P3A_SetHigh()    do { LATE0 = 1; } while(0)
#define P3A_SetLow()   do { LATE0 = 0; } while(0)
#define P3A_Toggle()   do { LATE0 = ~LATE0; } while(0)
#define P3A_GetValue()         PORTEbits.RE0
#define P3A_SetDigitalInput()    do { TRISE0 = 1; } while(0)
#define P3A_SetDigitalOutput()   do { TRISE0 = 0; } while(0)

#define P3A_SetAnalogMode()   do { ANSE0 = 1; } while(0)
#define P3A_SetDigitalMode()   do { ANSE0 = 0; } while(0)
// get/set MOTORR aliases
#define MOTORR_TRIS               TRISE1
#define MOTORR_LAT                LATE1
#define MOTORR_PORT               PORTEbits.RE1
#define MOTORR_ANS                ANSE1
#define MOTORR_SetHigh()    do { LATE1 = 1; } while(0)
#define MOTORR_SetLow()   do { LATE1 = 0; } while(0)
#define MOTORR_Toggle()   do { LATE1 = ~LATE1; } while(0)
#define MOTORR_GetValue()         PORTEbits.RE1
#define MOTORR_SetDigitalInput()    do { TRISE1 = 1; } while(0)
#define MOTORR_SetDigitalOutput()   do { TRISE1 = 0; } while(0)

#define MOTORR_SetAnalogMode()   do { ANSE1 = 1; } while(0)
#define MOTORR_SetDigitalMode()   do { ANSE1 = 0; } while(0)
// get/set CCP5 aliases
#define CCP5_TRIS               TRISE2
#define CCP5_LAT                LATE2
#define CCP5_PORT               PORTEbits.RE2
#define CCP5_ANS                ANSE2
#define CCP5_SetHigh()    do { LATE2 = 1; } while(0)
#define CCP5_SetLow()   do { LATE2 = 0; } while(0)
#define CCP5_Toggle()   do { LATE2 = ~LATE2; } while(0)
#define CCP5_GetValue()         PORTEbits.RE2
#define CCP5_SetDigitalInput()    do { TRISE2 = 1; } while(0)
#define CCP5_SetDigitalOutput()   do { TRISE2 = 0; } while(0)

#define CCP5_SetAnalogMode()   do { ANSE2 = 1; } while(0)
#define CCP5_SetDigitalMode()   do { ANSE2 = 0; } while(0)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    GPIO and peripheral I/O initialization
 * @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize(void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);

#endif // PIN_MANAGER_H
/**
 End of File
 */
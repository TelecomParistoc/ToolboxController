/**
  ECCP3 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    eccp3.c

  @Summary
    This is the generated driver implementation file for the ECCP3 driver using MPLAB® Code Configurator

  @Description
    This source file provides APIs for ECCP3.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC18F46K22
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

/**
  Section: Included Files
 */

#include <xc.h>
#include "epwm3.h"

/**
  Section: Macro Declarations
 */

#define PWM3_INITIALIZE_DUTY_VALUE    2

/**
  Section: EPWM Module APIs
 */

void EPWM3_Initialize(void) {
    // Set the PWM to the options selected in MPLAB® Code Configurator

    // DC3B 32; CCP3M P3AP3Chi_P3BP3Dhi; P3M single; 
    CCP3CON = 0x2C;

    // CCP3ASE operating; CCP3AS disabled; PSS3BD P3BP3D_0; PSS3AC P3AP3C_0; 
    ECCP3AS = 0x00;

    // P3RSEN automatic_restart; P3DC 0; 
    PWM3CON = 0x80;

    // STR3A P3A_to_CCP3M; STR3C P3C_to_port; STR3B P3B_to_port; STR3D P3D_to_port; STR3SYNC start_at_begin; 
    PSTR3CON = 0x01;

    // CCPR3L 0; 
    CCPR3L = 0x00;

    // CCPR3H 0x0; 
    CCPR3H = 0x00;


    // Selecting Timer2
    CCPTMRS0bits.C3TSEL = 0x0;
}

void EPWM3_LoadDutyValue(uint16_t dutyValue) {
    // Writing to 8 MSBs of pwm duty cycle in CCPRL register
    CCPR3L = ((dutyValue & 0x03FC) >> 2);

    // Writing to 2 LSBs of pwm duty cycle in CCPCON register
    CCP3CON = (CCP3CON & 0xCF) | ((dutyValue & 0x0003) << 4);
}
/**
 End of File
 */

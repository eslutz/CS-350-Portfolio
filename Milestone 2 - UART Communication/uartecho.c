/*
 * Copyright (c) 2015-2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== uartecho.c ========
 */
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    char input;
    UART_Handle uart;
    UART_Params uartParams;

    /* Call driver init functions */
    GPIO_init();
    UART_init();

    /* Configure the LED pin */
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    /* Create a UART with data processing off. */
    UART_Params_init(&uartParams);
    uartParams.baudRate = 115200;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;

    uart = UART_open(CONFIG_UART_0, &uartParams);

    if (uart == NULL) {
        /* UART_open() failed */
        while (1);
    }

    enum LED_States {LED_START, LED_S0, LED_S1, LED_ON, LED_OFF} LED_STATE; // Define the possible states

    /* Loop forever */
    while(1) {
        switch (LED_STATE)      // Transitions
        {
            case LED_START:     // Check if first char is an 'o'
                if (input == 'o' || input == 'O')
                {
                    LED_STATE = LED_S0;
                }
                break;
            case LED_S0:        // Check if second char is a 'n' of 'f'
                if (input == 'n' || input == 'N')
                {
                    LED_STATE = LED_ON;
                }
                else if (input == 'f' || input == 'F')
                {
                    LED_STATE = LED_S1;
                }
                break;
            case LED_S1:        // Check if third char is an 'f'
                if (input == 'f' || input == 'F')
                {
                    LED_STATE = LED_OFF;
                }
                break;
            case LED_ON:        // Reset to start state
            case LED_OFF:       // Reset to start state
            default:            // Set to start state
                LED_STATE = LED_START;
                break;
        }

        switch (LED_STATE)  // State actions
        {
            case LED_START:                                         // Initial input action
                UART_read(uart, &input, 1);                         // Get first char from input
                UART_write(uart, &input, 1);                        // Display the input
                break;
            case LED_S0:                                            // Second input action
                UART_read(uart, &input, 1);                         // Get second char from input
                UART_write(uart, &input, 1);                        // Display the input
                break;
            case LED_S1:                                            // Third input action
                UART_read(uart, &input, 1);                         // Get third char from input
                UART_write(uart, &input, 1);                        // Display the input
                break;
            case LED_ON:                                            // Turn on led action
                GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);  // Turn red led on
                break;
            case LED_OFF:                                           // Turn off led action
                GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF); // Turn red led off
                break;
            default:
                break;
        }
    }
}

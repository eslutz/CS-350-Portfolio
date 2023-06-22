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
 *  ======== gpiointerrupt.c ========
 */
#include <stddef.h>
#include <stdint.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/I2C.h>
#include <ti/drivers/Timer.h>
#include <ti/drivers/UART.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/* Definitions */
#define DISPLAY(x) UART_write(uart, &output, x)
#define timerPeriod 100
#define numTasks 3
#define checkButtonPeriod 200
#define checkTemperaturePeriod 500
#define updateHeatModeAndServerPeriod 1000

/*
 *  ======== Task Type ========
 *
 *  Defines structure for the task type.
 */
typedef struct task {
    int state;                    // Current state of the task
    unsigned long period;         // Rate at which the task should tick
    unsigned long elapsedTime;    // Time since task's previous tick
    int (*tickFunction)(int);     // Function to call for task's tick
} task;

/*
 *  ======== Driver Handles ========
 */
I2C_Handle i2c;         // I2C driver handle
Timer_Handle timer0;    // Timer driver handle
UART_Handle uart;       // UART driver handle

/*
 *  ======== Global Variables ========
 */
// UART global variables
char output[64];
int bytesToSend;

// I2C global variables
static const struct
{
    uint8_t address;
    uint8_t resultReg;
    char *id;
}
sensors[3] = {
    { 0x48, 0x0000, "11X" },
    { 0x49, 0x0000, "116" },
    { 0x41, 0x0001, "006" }
};
uint8_t txBuffer[1];
uint8_t rxBuffer[2];
I2C_Transaction i2cTransaction;

// Timer global variables
volatile unsigned char TimerFlag = 0;

// Thermostat global variables
enum BUTTON_STATES {INCREASE_TEMPERATURE, DECREASE_TEMPERATURE, BUTTON_INIT} BUTTON_STATE;  // States for setting which button was pressed.
enum TEMPERATURE_SENSOR_STATES {READ_TEMPERATURE, TEMPERATURE_SENSOR_INIT};                 // States for the temperature sensor.
enum HEATING_STATES {HEAT_OFF, HEAT_ON, HEAT_INIT};                                         // States for the heating (heat/led off or on).
int16_t ambientTemperature = 0;                                                             // Initialize temperature to 0 (will be updated by sensor reading).
int16_t setPoint = 20;                                                                      // Initialize set-point for thermostat at 20°C (68°F).
int seconds = 0;                                                                            // Initialize seconds to 0 (will be updated by timer).

/*
 *  ======== Callback ========
 */
// GPIO button callback function to increase the thermostat set-point.
void gpioIncreaseTemperatureCallback(uint_least8_t index)
{
    BUTTON_STATE = INCREASE_TEMPERATURE;
}

// GPIO button callback function to decrease the thermostat set-point.
void gpioDecreaseTemperatureCallback(uint_least8_t index)
{
    BUTTON_STATE = DECREASE_TEMPERATURE;
}

// Timer callback
void timerCallback(Timer_Handle myHandle, int_fast16_t status)
{
    TimerFlag = 1;  // Set flag to 1 to indicate timer is running.
}

/*
 *  ======== Initializations ========
 */
// Initialize UART
void initUART(void)
{
    UART_Params uartParams;

    // Init the driver
    UART_init();

    // Configure the driver
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.baudRate = 115200;

    // Open the driver
    uart = UART_open(CONFIG_UART_0, &uartParams);
    if (uart == NULL)
    {
        /* UART_open() failed */
        while (1);
    }
}

// Initialize I2C
void initI2C(void)
{
    int8_t i, found;
    I2C_Params i2cParams;

    DISPLAY(snprintf(output, 64, "Initializing I2C Driver - "));

    // Init the driver
    I2C_init();

    // Configure the driver
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_400kHz;

    // Open the driver
    i2c = I2C_open(CONFIG_I2C_0, &i2cParams);
    if (i2c == NULL)
    {
        DISPLAY(snprintf(output, 64, "Failed\n\r"));
        while (1);
    }

    DISPLAY(snprintf(output, 32, "Passed\n\r"));

    // Boards were shipped with different sensors.
    // Welcome to the world of embedded systems.
    // Try to determine which sensor we have.
    // Scan through the possible sensor addresses.

    /* Common I2C transaction setup */
    i2cTransaction.writeBuf = txBuffer;
    i2cTransaction.writeCount = 1;
    i2cTransaction.readBuf = rxBuffer;
    i2cTransaction.readCount = 0;

    found = false;
    for (i=0; i<3; ++i)
    {
         i2cTransaction.slaveAddress = sensors[i].address;
         txBuffer[0] = sensors[i].resultReg;

         DISPLAY(snprintf(output, 64, "Is this %s? ", sensors[i].id));
         if (I2C_transfer(i2c, &i2cTransaction))
         {
             DISPLAY(snprintf(output, 64, "Found\n\r"));
             found = true;
             break;
         }
         DISPLAY(snprintf(output, 64, "No\n\r"));
    }

    if(found)
    {
        DISPLAY(snprintf(output, 64, "Detected TMP%s I2C address: %x\n\r", sensors[i].id, i2cTransaction.slaveAddress));
    }
    else
    {
        DISPLAY(snprintf(output, 64, "Temperature sensor not found, contact professor\n\r"));
    }
}

// Initialize GPIO
void initGPIO(void)
{
    /* Call driver init functions for GPIO */
    GPIO_init();

    /* Configure the LED and button pins */
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_BUTTON_0, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

    /* Start with LED off */
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF);

    /* Install Button callback */
    GPIO_setCallback(CONFIG_GPIO_BUTTON_0, gpioIncreaseTemperatureCallback);

    /* Enable interrupts */
    GPIO_enableInt(CONFIG_GPIO_BUTTON_0);

    /*
     *  If more than one input pin is available for your device, interrupts
     *  will be enabled on CONFIG_GPIO_BUTTON1.
     */
    if (CONFIG_GPIO_BUTTON_0 != CONFIG_GPIO_BUTTON_1) {
        /* Configure BUTTON1 pin */
        GPIO_setConfig(CONFIG_GPIO_BUTTON_1, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

        /* Install Button callback */
        GPIO_setCallback(CONFIG_GPIO_BUTTON_1, gpioDecreaseTemperatureCallback);
        GPIO_enableInt(CONFIG_GPIO_BUTTON_1);
    }

    BUTTON_STATE = BUTTON_INIT;
}

// Initialize Timer
void initTimer(void)
{
    Timer_Params params;

    // Init the driver
    Timer_init();

    // Configure the driver
    Timer_Params_init(&params);
    params.period = 100000;                         // Set period to 1/10th of 1 second.
    params.periodUnits = Timer_PERIOD_US;           // Period specified in micro seconds
    params.timerMode = Timer_CONTINUOUS_CALLBACK;   // Timer runs continuously.
    params.timerCallback = timerCallback;           // Calls timerCallback method for timer callback.

    // Open the driver
    timer0 = Timer_open(CONFIG_TIMER_0, &params);
    if (timer0 == NULL)
    {
        /* Failed to initialized timer */
        while (1) {}
    }
    if (Timer_start(timer0) == Timer_STATUS_ERROR)
    {
        /* Failed to start timer */
        while (1) {}
    }
}

/*
 *  ======== adjustSetPointTemperature ========
 *
 *  Check the current state of BUTTON_PRESSED to determine if the
 *  increase or decrease temperature button has been pressed and
 *  then resets BUTTON_PRESSED.
 */
int adjustSetPointTemperature(int state)
{
    // Checks if desired temperature has been adjusted.
    switch (state)
    {
        case INCREASE_TEMPERATURE:
            if (setPoint < 99)      // Ensure temperature is not set to above 99°C.
            {
                setPoint++;
            }
            BUTTON_STATE = BUTTON_INIT;
            break;
        case DECREASE_TEMPERATURE:
            if (setPoint > 0)       // Ensure temperature is not set lower than 0°C.
            {
                setPoint--;
            }
            BUTTON_STATE = BUTTON_INIT;
            break;
    }
    state = BUTTON_STATE;           // Reset the state of BUTTON_PRESSED after reading.

    return state;
}

/*
 *  ======== readTemp ========
 *
 *  Read in the current temperature from the sensor and return the reading.
 */
int16_t readTemp(void)
{
    int16_t temperature = 0;
    i2cTransaction.readCount = 2;
    if (I2C_transfer(i2c, &i2cTransaction))
    {
        /*
        * Extract degrees C from the received data;
        * see TMP sensor datasheet
        */
        temperature = (rxBuffer[0] << 8) | (rxBuffer[1]); temperature *= 0.0078125;
        /*
        * If the MSB is set '1', then we have a 2's complement * negative value which needs to be sign extended
        */
        if (rxBuffer[0] & 0x80)
        {
            temperature |= 0xF000;
        }
    }
    else
    {
        DISPLAY(snprintf(output, 64, "Error reading temperature sensor (%d)\n\r",i2cTransaction.status));
        DISPLAY(snprintf(output, 64, "Please power cycle your board by unplugging USB and plugging back in.\n\r"));
    }
    return temperature;
}

/*
 *  ======== getAmbientTemperature ========
 *
 *  Checks the current state to determine if the temperature should be read.
 */
int getAmbientTemperature(int state)
{
    switch (state)
    {
        case TEMPERATURE_SENSOR_INIT:
            state = READ_TEMPERATURE;
            break;
        case READ_TEMPERATURE:
            ambientTemperature = readTemp();    // Sets the current ambient temperature.
            break;
    }

    return state;
}

/*
 *  ======== setHeatMode ========
 *
 *  Compares the ambient temperature to the set-point.
 *  Turns on the heat (Led on) if ambient temperature is lower than the set-point.
 *  Turns off the heat (Led off) if ambient temperature is higher than the set-point.
 */
int setHeatMode(int state)
{
    if (seconds != 0)
    {
        // Determines if heat needs to be turned on and sets heat (led) to on or off.
        if (ambientTemperature < setPoint)  // Turn on the heat.
        {
            GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);
            state = HEAT_ON;
        }
        else                                // Turn off the heat.
        {
            GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF);
            state = HEAT_OFF;
        }

        // Report status to the server.
        DISPLAY(snprintf(output,
                             64,
                             "<%02d,%02d,%d,%04d>\n\r",
                             ambientTemperature,
                             setPoint,
                             state,
                             seconds));
    }

    seconds++;                              // Increment the second counter.

    return state;
}

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    // Create task list with tasks.
    task tasks[numTasks] = {
        // Task 1 - Check button state and update set point.
        {
            .state = BUTTON_INIT,
            .period = checkButtonPeriod,
            .elapsedTime = checkButtonPeriod,
            .tickFunction = &adjustSetPointTemperature
        },
        // Task 2 - Get temperature from sensor.
        {
            .state = TEMPERATURE_SENSOR_INIT,
            .period = checkTemperaturePeriod,
            .elapsedTime = checkTemperaturePeriod,
            .tickFunction = &getAmbientTemperature
        },
        // Task 3 - Update heat mode and server.
        {
            .state = HEAT_INIT,
            .period = updateHeatModeAndServerPeriod,
            .elapsedTime = updateHeatModeAndServerPeriod,
            .tickFunction = &setHeatMode
        }
    };

    // Call init functions for the drivers.
    initUART();
    initI2C();
    initGPIO();
    initTimer();

    // Loop forever.
    while (1)
    {
        unsigned int i = 0;
        for (i = 0; i < numTasks; ++i)
        {
            if ( tasks[i].elapsedTime >= tasks[i].period )
            {
                tasks[i].state = tasks[i].tickFunction(tasks[i].state);
                tasks[i].elapsedTime = 0;
             }
             tasks[i].elapsedTime += timerPeriod;
        }

        // Wait for timer period.
        while(!TimerFlag){}
        // Set the timer flag variable to FALSE.
        TimerFlag = 0;
    }

    return (NULL);
}



#ifndef TMR1_H
#define TMR1_H

/*
    Секция: Включаемые файлы.
*/

#include <stdbool.h>
#include <stdint.h>

/*
    Секция: APIs.
*/

/*
    @Summary
        Initializes the TMR1

    @Description
        This routine initializes the TMR1.
        This routine must be called before any other TMR1 routine is called.
        This routine should only be called once during system initialization.

    @Preconditions
        None

    @Param
        None

    @Returns
        None

    @Comment


    @Example
        <code>
        main()
        {
            // Initialize TMR1 module
            TMR1_Initialize();

            // Do something else...
        }
        </code>
*/
void TMR1_Initialize(void);

/*
    @Summary
        This function starts the TMR1.

    @Description
        This function starts the TMR1 operation.
        This function must be called after the initialization of TMR1.

    @Preconditions
        Initialize  the TMR1 before calling this function.

    @Param
        None

    @Returns
        None

    @Example
        <code>
        // Initialize TMR1 module

        // Start TMR1
        TMR1_StartTimer();

        // Do something else...
        </code>
*/
void TMR1_StartTimer(void);

/*
    @Summary
        This function stops the TMR1.

    @Description
        This function stops the TMR1 operation.
        This function must be called after the start of TMR1.

    @Preconditions
        Initialize  the TMR1 before calling this function.

    @Param
        None

    @Returns
        None

    @Example
        <code>
        // Initialize TMR1 module

        // Start TMR1
        TMR1_StartTimer();

        // Do something else...

        // Stop TMR1;
        TMR1_StopTimer();
        </code>
*/
void TMR1_StopTimer(void);

/*
    @Summary
        Reads the TMR1 register.

    @Description
        This function reads the TMR1 register value and return it.

    @Preconditions
        Initialize  the TMR1 before calling this function.

    @Param
        None

    @Returns
        This function returns the current value of TMR1 register.

    @Example
        <code>
        // Initialize TMR1 module

        // Start TMR1
        TMR1_StartTimer();

        // Read the current value of TMR1
        if(0 == TMR1_ReadTimer())
        {
            // Do something else...

            // Reload the TMR value
            TMR1_Reload();
        }
        </code>
*/
uint16_t TMR1_ReadTimer(void);

/*
    @Summary
        Writes the TMR1 register.

    @Description
        This function writes the TMR1 register.
        This function must be called after the initialization of TMR1.

    @Preconditions
        Initialize  the TMR1 before calling this function.

    @Param
        timerVal - Value to write into TMR1 register.

    @Returns
        None

    @Example
        <code>
        #define PERIOD 0x80
        #define ZERO   0x00

        while(1)
        {
            // Read the TMR1 register
            if(ZERO == TMR1_ReadTimer())
            {
                // Do something else...

                // Write the TMR1 register
                TMR1_WriteTimer(PERIOD);
            }

            // Do something else...
        }
        </code>
*/
void TMR1_WriteTimer(uint16_t timerVal);

/*
    @Summary
        Reload the TMR1 register.

    @Description
        This function reloads the TMR1 register.
        This function must be called to write initial value into TMR1 register.

    @Preconditions
        Initialize  the TMR1 before calling this function.

    @Param
        None

    @Returns
        None

    @Example
        <code>
        while(1)
        {
            if(TMR1IF)
            {
                // Do something else...

                // clear the TMR1 interrupt flag
                TMR1IF = 0;

                // Reload the initial value of TMR1
                TMR1_Reload();
            }
        }
        </code>
*/
void TMR1_Reload(void);

/*
    @Summary
        Starts the single pulse acquisition in TMR1 gate operation.

    @Description
        This function starts the single pulse acquisition in TMR1 gate operation.
        This function must be used when the TMR1 gate is enabled.

    @Preconditions
        Initialize  the TMR1 with gate enable before calling this function.

    @Param
        None

    @Returns
        None

    @Example
        <code>
        uint16_t xVal;
        uint16_t yVal;

        // enable TMR1 singlepulse mode
        TMR1_StartSinglePulseAcquistion();

        // check TMR1 gate status
        if(TMR1_CheckGateValueStatus()== 0)
            xVal = TMR1_ReadTimer();

        // wait untill gate interrupt occured
        while(TMR1GIF == 0)
        {
        }

        yVal = TMR1_ReadTimer();
        </code>
*/
void TMR1_StartSinglePulseAcquisition(void);

/*
    @Summary
        Check the current state of Timer1 gate.

    @Description
        This function reads the TMR1 gate value and return it.
        This function must be used when the TMR1 gate is enabled.

    @Preconditions
        Initialize  the TMR1 with gate enable before calling this function.

    @Param
        None

    @Returns
        None

    @Example
        <code>
        uint16_t xVal;
        uint16_t yVal;

        // enable TMR1 singlepulse mode
        TMR1_StartSinglePulseAcquistion();

        // check TMR1 gate status
        if(TMR1_CheckGateValueStatus()== 0)
            xVal = TMR1_ReadTimer();

        // wait untill gate interrupt occured
        while(TMR1IF == 0)
        {
        }

        yVal = TMR1_ReadTimer();
        </code>
*/
uint8_t TMR1_CheckGateValueStatus(void);

/*
    @Summary
        Boolean routine to poll or to check for the overflow flag on the fly.

    @Description
        This function is called to check for the timer overflow flag.
        This function is usd in timer polling method.

    @Preconditions
        Initialize  the TMR1 module before calling this routine.

    @Param
        None

    @Returns
        true - timer overflow has occured.
        false - timer overflow has not occured.

    @Example
        <code>
        while(1)
        {
            // check the overflow flag
            if(TMR1_HasOverflowOccured())
            {
                // Do something else...

                // clear the TMR1 interrupt flag
                TMR1IF = 0;

                // Reload the TMR1 value
                TMR1_Reload();
            }
        }
        </code>
*/
bool TMR1_HasOverflowOccured(void);

#endif

/*
    Конец файда.
*/

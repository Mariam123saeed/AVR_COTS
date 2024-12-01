/*
 * SPI_program.c
 *
 *  Created on: Oct 1, 2024
 *      Author: Mariam
 */
/*UTILS/LIB*/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/*MCAL*/
#include "SPI_interface.h"
#include "SPI_config.h"
#include "SPI_register.h"

/*Global variable to carry the Transmit Data*/
static u8 * SPI_pu8TxData = NULL ;

/*Global variable to carry the Receive Data*/
static u8 * SPI_pu8RxData = NULL ;

/*Global pointer to function to carry the notification function called by ISR*/
static void (* PRV_SPICallBackFunc)(void)= NULL;

/*Global flag for the SPI Busy State*/
  u8 SPI_u8State= IDLE ;


//-------------------------------------------------------------------------------------------------------------------------------



void SPI_voidInit(void)
{
	    /* Master/Slave Select */
	    #if  SPI_MASTER_SLAVE_SELECT == SPI_MASTER
		     SET_BIT(SPCR_REG, MSTR);
		     /* Clock Rate */
		     	    #if SPI_CLK_RATE == SPI_FREQ_DIVIDED_BY_2
		     	        CLR_BIT(SPCR_REG, SPR0);
		     	        CLR_BIT(SPCR_REG, SPR1);
		     	        SET_BIT(SPSR_REG, SPI2X);
		     	    #elif SPI_CLK_RATE == SPI_FREQ_DIVIDED_BY_4
		     	        CLR_BIT(SPCR_REG, SPR0);
		     	        CLR_BIT(SPCR_REG, SPR1);
		     	        CLR_BIT(SPSR_REG, SPI2X);
		     	    #elif SPI_CLK_RATE == SPI_FREQ_DIVIDED_BY_8
		     	        SET_BIT(SPCR_REG, SPR0);
		     	        CLR_BIT(SPCR_REG, SPR1);
		     	        SET_BIT(SPSR_REG, SPI2X);
		     	    #elif SPI_CLK_RATE == SPI_FREQ_DIVIDED_BY_16
		     	        SET_BIT(SPCR_REG, SPR0);
		     	        CLR_BIT(SPCR_REG, SPR1);
		     	        CLR_BIT(SPSR_REG, SPI2X);
		     	    #elif SPI_CLK_RATE == SPI_FREQ_DIVIDED_BY_32
		     	        CLR_BIT(SPCR_REG, SPR0);
		     	        SET_BIT(SPCR_REG, SPR1);
		     	        SET_BIT(SPSR_REG, SPI2X);
		     	    #elif SPI_CLK_RATE == SPI_FREQ_DIVIDED_BY_64
		     	        CLR_BIT(SPCR_REG, SPR0);
		     	        SET_BIT(SPCR_REG, SPR1);
		     	        CLR_BIT(SPSR_REG, SPI2X);
		     	    #elif SPI_CLK_RATE == SPI_FREQ_DIVIDED_BY_128
		     	        SET_BIT(SPCR_REG, SPR0);
		     	        SET_BIT(SPCR_REG, SPR1);
		     	        CLR_BIT(SPSR_REG, SPI2X);
		     	    #else
		     	        #error "wrong SPI_CLK_RATE config"
		     	    #endif

	    #elif SPI_MASTER_SLAVE_SELECT == SPI_SLAVE
		    CLR_BIT(SPCR_REG, MSTR);
	    #else
		     #error "wrong SPI_MASTER_SLAVE_SELECT config"
		#endif
	    /* Data Order */
	    #if SPI_DATA_ORDER == SPI_DATA_LSB_FIRST
	        SET_BIT(SPCR_REG, DORD);
	    #elif SPI_DATA_ORDER == SPI_DATA_MSB_FIRST
	        CLR_BIT(SPCR_REG, DORD);
	    #else
	        #error "wrong SPI_DATA_ORDER config"
	    #endif

	    /* Clock Polarity */
	    #if SPI_CLK_POLARITY == SPI_RISING_LEADING_FALLING_TRAILING
	        CLR_BIT(SPCR_REG, CPOL);
	    #elif SPI_CLK_POLARITY == SPI_FALLING_LEADING_RISING_TRAILING
	        SET_BIT(SPCR_REG, CPOL);
	    #else
	        #error "wrong SPI_CLK_POLARITY config"
	    #endif

	    /* Clock Phase */
	    #if SPI_CLK_PHASE == SPI_SAMPLE_LEADING_SETUP_TRAILING
	        CLR_BIT(SPCR_REG, CPHA);
	    #elif SPI_CLK_PHASE == SPI_SETUP_LEADING_SAMPLE_TRAILING
	        SET_BIT(SPCR_REG, CPHA);
	    #else
	        #error "wrong SPI_CLK_PHASE config"
	    #endif


	    /* SPI Interrupt Enable */
	    #if SPI_INTERRUPT_MODE == SPI_INTERRUPT_DISABLE
	        CLR_BIT(SPCR_REG, SPIE);
	    #elif SPI_INTERRUPT_MODE == SPI_INTERRUPT_ENABLE
	        SET_BIT(SPCR_REG, SPIE);
	    #else
	        #error "wrong SPI_INTERRUPT_ENABLE_MODE config"
	    #endif

	    /* SPI Enable */
	    #if SPI_ENABLE_MODE == SPI_DISABLE
	        CLR_BIT(SPCR_REG, SPE);
	    #elif SPI_ENABLE_MODE == SPI_ENABLE
	        SET_BIT(SPCR_REG, SPE);
	    #else
	        #error "wrong SPI_ENABLE_MODE config"
	    #endif

}
/**********************************************************************************************************************************************/
void SPI_voidTransmiteData (u8 copy_u8TxData)
{
	/* Start transmission */
	SPDR_REG = copy_u8TxData;
	/* Wait for transmission complete */
	while (0 == GET_BIT (SPSR_REG,SPIF));

}
/**********************************************************************************************************************************************/
void SPI_voidRecieveData (u8 *copy_pu8RxData)
{
	u8 local_u8ErrorStatus = TRUE;
	if (copy_pu8RxData != NULL)
	{
		while (0 == GET_BIT (SPSR_REG,SPIF));
		*copy_pu8RxData = SPDR_REG ;
	}
	else
	{
		local_u8ErrorStatus = FALSE;
	}
}
/**********************************************************************************************************************************************/
u8 SPI_u8TrancieveData(u8 copy_u8TxData, u8 *copy_pu8RxData) {
    if (copy_pu8RxData != NULL) {
        SPDR_REG = copy_u8TxData;
        while (GET_BIT(SPSR_REG, SPIF) == 0);
        *copy_pu8RxData = SPDR_REG;
        return TRUE;
    } else {
        return FALSE;
    }
}

/**********************************************************************************************************************************************/
void SPI_voidTxString      (u8* copy_u8TxString)
{
	if (copy_u8TxString !=NULL)
	{
		u8 local_u8Conter=0;
	   while (copy_u8TxString [local_u8Conter] !='\0')
		{
		   SPI_voidTransmiteData(copy_u8TxString [local_u8Conter]);
		   local_u8Conter ++;
		}
	}
}
/**********************************************************************************************************************************************/
void SPI_voidRxString      (u8* copy_u8RxString)
{
	if (copy_u8RxString !=NULL)
	{
		u8 local_u8Conter=0;
		while (1)
		{
			SPI_voidRecieveData(&copy_u8RxString[local_u8Conter]);
			/* Receive the whole string until the '#' */
			if(copy_u8RxString[local_u8Conter] == '#')
			{
				break;
			}
			else
			{
			  local_u8Conter ++;
			}

			}
		/* After receiving the whole string plus the '#', replace the '#' with '\0' */
		copy_u8RxString[local_u8Conter] = '\0';
	}
}
/**********************************************************************************************************************************************/
void SPI_voidTranceiveAsynch(u8 copy_u8TxData, u8 *copy_pu8RxData, void (*copy_NotificationFunc)(void))
{
    u8 Local_u8ErrorState = TRUE;

    if (SPI_u8State == IDLE)
        {
        	if ((copy_pu8RxData != NULL) && (copy_NotificationFunc != NULL))
        	{
        		        /* SPI is now Busy */
        		        SPI_u8State = BUSY;
        	            /* Assign the SPI data and notification function globally */
        	        	SPI_pu8TxData = copy_u8TxData;
        	            SPI_pu8RxData = copy_pu8RxData;
        	            PRV_SPICallBackFunc = copy_NotificationFunc;

        	            /* Transmit the data */
        	            SPDR_REG = SPI_pu8TxData;

        	            /* Enable SPI Interrupt */
        	            SET_BIT(SPCR_REG,SPIE);
        	  }
        	 else
        	 {
        	    Local_u8ErrorState = FALSE;
        	 }
        }
        else
        {
            Local_u8ErrorState = FALSE;
        }





}

/**********************************************************************************************************************************************/
//ISR
void __vector_12(void) __attribute__ ((signal));
void __vector_12(void)
{
    /* Receive Data */
    *SPI_pu8RxData = SPDR_REG;

    /* SPI is now IDLE */
     SPI_u8State = IDLE;

    /* Disable SPI Interrupt */
    CLR_BIT(SPCR_REG, SPIE);

    /* Call Notification Function */
    if (PRV_SPICallBackFunc != NULL) {
        	 PRV_SPICallBackFunc();
        }
}

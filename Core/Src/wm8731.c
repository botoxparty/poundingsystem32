/**
 ******************************************************************************
 * File Name		: wm8731.h
 * Author			: Adam Hammad
 * Date				: 13 December 2020
 * Description		: Drivers for Wolfson WM8731
 ******************************************************************************
 */

#include "wm8731.h";
uint16_t audiobuff[1]; // Ping pong buffer
extern I2C_HandleTypeDef hi2c2;
extern I2S_HandleTypeDef hi2s2;

const uint16_t w8731_init_data[] =
    {
        0x017, // Reg 00: Left Line In (0dB, mute off)
        0x017, // Reg 01: Right Line In (0dB, mute off)
        0x079, // Reg 02: Left Headphone out (0dB)
        0x079, // Reg 03: Right Headphone out (0dB)
        0x015, // Reg 04: Analog Audio Path Control (DAC sel, Mute Mic)
        0x000, // Reg 05: Digital Audio Path Control
        0x060, // Reg 06: Power Down Control (Clkout, Osc, Mic Off)
               //	0x00E,			// Reg 07: Digital Audio Interface Format (i2s, 32-bit, slave)
        0x002, // Reg 07: Digital Audio Interface Format (i2s, 16-bit, slave)
        0x000, // Reg 08: Sampling Control (Normal, 256x, 48k ADC/DAC)
        0x001  // Reg 09: Active Control
};

/**
  * @brief  Resets the audio codec. It restores the default configuration of the
  *         codec (this function shall be called before initializing the codec).
  * @note   This function calls an external driver function: The IO Expander driver.
  * @param  None
  * @retval None
  */
void WM8731_Init(void)
{
    // Initialise I2S
    HAL_I2S_MspInit(&hi2s2);

    uint8_t i;

    WM8731_WriteRegister(0x0f, 0);

    /* Load default values */
    for (i = 0; i < W8731_NUM_REGS; i++)
    {
        WM8731_WriteRegister(i, w8731_init_data[i]);
    }

    // Transmit audio data
    HAL_I2S_Transmit_DMA(&hi2s2, (uint16_t *)&audiobuff[0], DMA_MAX((2 * BUFF_LEN) / AUDIODATA_SIZE)); // size must be in bytes
}

/**
  * @brief  Writes a Byte to a given register into the audio codec through the
            control interface (I2C)
  * @param  RegisterAddr: The address (location) of the register to be written.
  * @param  RegisterValue: the Byte value to be written into destination register.
  * @retval 0 if correct communication, else wrong communication
  */
uint32_t WM8731_WriteRegister(uint8_t RegisterAddr, uint16_t RegisterValue)
{
    HAL_StatusTypeDef status = HAL_OK;

    uint8_t data[2];

    /* Assemble 2-byte data in WM8731 format */
    data[0] = ((RegisterAddr << 1) & 0xFE) | ((RegisterValue >> 8) & 0x01); // 0x0C in your example
    data[1] = RegisterValue & 0xFF;                                         // MSB byte of 16bit data

    status = HAL_I2C_Master_Transmit(&hi2c2, CODEC_ADDRESS, data, 2, CODEC_LONG_TIMEOUT); // data is the start pointer of our array
    /* Check the communication status */
    if (status != HAL_OK)
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
        // Error handling, for example re-initialization of the I2C peripheral
        Error_Handler();
    }

    // data is the start pointer of our array
    /* Return the verifying value: 0 (Passed) or 1 (Failed) */
    return status;
}
// what is this file and why is it required.
// how do imports work with the compiler, in order, etc.
// #include <cstdint>
#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "wm8978.h"

class WM8978
{
public:
    // what are the other data types besides int?
    // what is signed vs unsigned?
    int HP_VOLUME = 40;
    int SPK_VOLUME = 80;
    WM8978(I2C_HandleTypeDef i2c, I2S_HandleTypeDef i2s)
    {
        hi2c = i2c;
        hi2s = i2s;
        // naming these variables
        // what is a handle again?
        Init();
    }
    // Headphone volume
    void SetHPVol(uint8_t voll, uint8_t volr)
    {
        HP_VOLUME = voll;
        voll &= 0X3F;
        volr &= 0X3F;
        if (voll == 0)
            voll |= 1 << 6; //volume is 0, mute on
        if (volr == 0)
            volr |= 1 << 6;                 //volume is 0, mute on
        WriteRegister(52, voll);            //R52, left channel volume
        WriteRegister(53, volr | (1 << 8)); //R53, right channel volume
    }

    // Speaker volume
    // voll:left channel volume(0~63)
    void SetSPKVol(uint8_t volx)
    {
        SPK_VOLUME = volx;
        volx &= 0X3F;
        if (volx == 0)
            volx |= 1 << 6;                 //volume is 0, mute on
        WriteRegister(54, volx);            //R54, left channel audio volume
        WriteRegister(55, volx | (1 << 8)); //R55, right channel audio volume
    }
    // WM8978 L2/R2(Line In)db config(L2/R2-->ADC input db)
    // gain:0~7,0 means channel mute,1~7,��Ӧ-12dB~6dB,3dB/Step
    void SetLineInGain(uint8_t gain)
    {
        uint16_t regval;
        gain &= 0X07;
        regval = ReadRegister(47);
        regval &= ~(7 << 4); //reset old config
        WriteRegister(47, regval | gain << 4);
        regval = ReadRegister(48);
        regval &= ~(7 << 4); //reset old config
        WriteRegister(48, regval | gain << 4);
    }
    // WM8978 AUXR,AUXL(PWM audio config)db config(AUXR/L-->ADC input db)
    // gain:0~7,0 channel mute,1~7,��Ӧ-12dB~6dB,3dB/Step
    void SetAuxGain(uint8_t gain)
    {
        uint16_t regval;
        gain &= 0X07;
        regval = ReadRegister(47);
        regval &= ~(7 << 0); //reset old config
        WriteRegister(47, regval | gain << 0);
        regval = ReadRegister(48);
        regval &= ~(7 << 0); //reset old config
        WriteRegister(48, regval | gain << 0);
    }

private:
    I2C_HandleTypeDef hi2c;
    I2S_HandleTypeDef hi2s;
    int REGISTER_VALUES[58] =
        {
            0X0000, 0X0000, 0X0000, 0X0000, 0X0050, 0X0000, 0X0140, 0X0000,
            0X0000, 0X0000, 0X0000, 0X00FF, 0X00FF, 0X0000, 0X0100, 0X00FF,
            0X00FF, 0X0000, 0X012C, 0X002C, 0X002C, 0X002C, 0X002C, 0X0000,
            0X0032, 0X0000, 0X0000, 0X0000, 0X0000, 0X0000, 0X0000, 0X0000,
            0X0038, 0X000B, 0X0032, 0X0000, 0X0008, 0X000C, 0X0093, 0X00E9,
            0X0000, 0X0000, 0X0000, 0X0000, 0X0003, 0X0010, 0X0010, 0X0100,
            0X0100, 0X0002, 0X0001, 0X0001, 0X0039, 0X0039, 0X0039, 0X0039,
            0X0001, 0X0001};

    void WriteRegister(uint8_t reg, uint16_t val)
    {
        uint8_t data[2];
        data[0] = (reg << 1) | ((uint8_t)((val >> 8) & 0x01)); //reg address + data highest bit
        data[1] = (uint8_t)(val & 0XFF);

        HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(&hi2c, CODEC_ADDRESS, data, 2, CODEC_LONG_TIMEOUT); // data is the start pointer of our array
                                                                                                               //     /* Check the communication status */
        if (status != HAL_OK)
        {
            // HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, 1);
            // // Error handling, for example re-initialization of the I2C peripheral
            // Error_Handler();
        }

        REGISTER_VALUES[reg] = val;
    }

    uint16_t ReadRegister(uint8_t reg)
    {
        return REGISTER_VALUES[reg];
    }

    void ClockConfig(bool useExternal)
    {
        if (useExternal)
        {
            WriteRegister(6, 0);
            return;
        }

        uint16_t regval = CLKSEL_PLL | MCLK_DIV2 | BCLK_DIV8;
        regval = CLKSEL_PLL | MCLK_DIV2 | BCLK_DIV8 | (regval & MS);
        WriteRegister(6, regval);
    }

    bool Init()
    {
        WriteRegister(0, 0); // Soft Reset

        WriteRegister(1, 0X1B);  // Register 1, MICEN 1(MIC enabled),BIASEN 1(emu on),VMIDSEL[1:0]:11(5K)
        WriteRegister(2, 0X1B0); // Register 2, ROUT1,LOUT1 output enabled(headphone),BOOSTENR,BOOSTENL enabled.
        WriteRegister(3, 0X6C);  // Register 3, LOUT2,ROUT2 output enabled(speaker on),RMIX,LMIX enabled

        ClockConfig(true); // Register 6, MCLK from out

        WriteRegister(43, 1 << 4); // Register 43,INVROUT2 inverted, drive speaker
        WriteRegister(47, 1 << 8); // Register 47,PGABOOSTL,left MIC got 20 db
        WriteRegister(48, 1 << 8); // Register 48,PGABOOSTR, right MIC got 20 db
        WriteRegister(49, 1 << 1); // Register 49,TSDEN, open hot protecting
        WriteRegister(10, 1 << 3); // Register 10,SOFTMUTE closed,128x sample rate, best SNR
        WriteRegister(14, 1 << 3); // Register 14,ADC 128x sample rate

        //	//audio output setting
        ADDAConfig(1, 1);     //open DAC
        InputConfig(1, 0, 0); //close input channel
        OutputConfig(1, 0);   //open DAC output
        I2SConfig(2, 0);      //I2S work mode

        //     //record setting
        //     // WM8978_ADDA_Cfg(0, 1);     //open ADC
        //     // WM8978_Input_Cfg(1, 1, 0); //open input channel(MIC&LINE IN)
        //     // WM8978_Output_Cfg(0, 1);   //open BYPASS output
        //     // WM8978_MIC_Gain(46);       //MIC db setting
        // //
        SetHPVol(HP_VOLUME, HP_VOLUME);
        SetSPKVol(SPK_VOLUME);

        HAL_I2S_Transmit_DMA(&hi2s, (uint16_t *)&audiobuff[0], DMA_MAX((2 * BUFF_LEN) / AUDIODATA_SIZE)); // size must be in bytes
    }

    //WM8978 DAC/ADC config
    //adcen:adc enable(1)/disable(0)
    //dacen:dac enable(1)/disable(0)
    void ADDAConfig(uint8_t dacen, uint8_t adcen)
    {
        uint16_t regval;
        regval = ReadRegister(3); // Read Register 3
        if (dacen)
            regval |= 3 << 0; // Register 3 set lowest 2 bits to 1. Enable DACR&DACL
        else
            regval &= ~(3 << 0); // Register 3 set lowest 2 bits to 0, Disable DACR&DACL.
        WriteRegister(3, regval);
        regval = ReadRegister(2); // Read Register 2
        if (adcen)
            regval |= 3 << 0; // Register 2 set lowest bits to 1, Enable ADCR&ADCL
        else
            regval &= ~(3 << 0);  // Register 2 set lowest bits to 0, Disable ADCR&ADCL.
        WriteRegister(2, regval); // Register 2
    }

    //WM8978 input config
    //micen:MIC enable(1)/disable(0)
    //lineinen:Line In enable(1)/disable(0)
    //auxen:aux enable(1)/disable(0)
    void InputConfig(uint8_t micen, uint8_t lineinen, uint8_t auxen)
    {
        uint16_t regval;
        regval = ReadRegister(2);
        if (micen)
            regval |= 3 << 2; //open INPPGAENR,INPPGAENL(MIC��PGA�Ŵ�)
        else
            regval &= ~(3 << 2); //close INPPGAENR,INPPGAENL.
        WriteRegister(2, regval);
        regval = ReadRegister(44);
        if (micen)
            regval |= 3 << 4 | 3 << 0; //enable LIN2INPPGA,LIP2INPGA,RIN2INPPGA,RIP2INPGA.
        else
            regval &= ~(3 << 4 | 3 << 0); //disable LIN2INPPGA,LIP2INPGA,RIN2INPPGA,RIP2INPGA.
        WriteRegister(44, regval);
        if (lineinen)
            SetLineInGain(5); //LINE IN 0dB
        else
            SetLineInGain(0); //disable LINE IN
        if (auxen)
            SetAuxGain(7); //AUX 6dB
        else
            SetAuxGain(0); //disable AUX input
    }

    //WM8978 output setting
    //dacen:DAC output enabled(1)/disabled(0)
    //bpsen:Bypass output(record,include MIC,LINE IN,AUX��) enabled(1)/disabled(0)
    void OutputConfig(uint8_t dacen, uint8_t bpsen)
    {
        uint16_t regval = 0;
        if (dacen)
            regval |= 1 << 0; //DAC output enabled
        if (bpsen)
        {
            regval |= 1 << 1; //BYPASS enabled
            regval |= 5 << 2; //0dB
        }
        WriteRegister(50, regval);
        WriteRegister(51, regval);
    }

    //I2S working mode
    //fmt:0,LSB;1,MSB;2,I2S;3,PCM/DSP;
    //len:0,16bist;1,20bits;2,24bits;3,32bits;
    void I2SConfig(uint8_t fmt, uint8_t len)
    {
        fmt &= 0x02;
        len &= 0x03;
        WriteRegister(4, (fmt << 3) | (len << 5)); //R4,WM8978 working mode
    }
};
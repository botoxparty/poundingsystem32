// Menu

class UI {

    cursorPosition = 0;
}

class UIFooter {

}

class UIMenu {

}

class UIMenu

class UIScrollPage {

}

// Synthesiser
class Synth {
    frequency = 100;
    what() {

    }
}

// Audio Codec
class WM8971 {

    constructor(i2c, i2s) {
        this.init(i2c, i2s)
    }

    public setHeadphoneVolume(value: number) {}
    public setLineoutVolume(value: number) {}
    public setMicGain(value: number) {}
    public setLineInGain(value: number) {}
    public setAuxGain(value: number) {}

    private init(i2c, i2s) {
        // i2c init registers
        // transmit audio buffer to i2s
    }

    private ReadRegister() {}
    private WriteRegister() {}
    private ADDA_Config() {}
    private CLK_Config() {}
    private I2S_Config() {}
    private Input_Config() {}
    private Output_Config() {}
}

// Interface


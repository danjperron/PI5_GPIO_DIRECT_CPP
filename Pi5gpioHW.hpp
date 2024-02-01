#include <stdint.h>

    // PADS

    const int PADS_SLEWFAST=1;
    const int PADS_SCHMITT=2;
    const int PADS_PULL_DOWN=4;
    const int PADS_PULL_UP=8;
    const int PADS_DRIVE_2MA = 0;
    const int PADS_DRIVE_4MA = 16;
    const int PADS_DRIVE_8MA = 32;
    const int PADS_DRIVE_12MA = 48;
    const int PADS_INPUT_ENABLE = 64;
    const int PADS_OUTPUT_DISABLE= 128;



class Pi5gpioHW
{
 public:
    Pi5gpioHW();
    ~Pi5gpioHW();
    void PinMode(int Pin, int pad , int mode, int riodrive);
    void getPinMode(int Pin, int & pad , int &mode, int &riodrive);
    int readDigital(int Pin);
    void writeDigital(int Pin, int value);
    void toggleDigital(int Pin);
    static int  setIOMap();
    static void  releaseIOMap();
    static uint32_t *rio0;
    static uint32_t *rio0_set;
    static uint32_t *rio0_clr;
    static uint32_t *rio0_xor;
    static uint32_t *iobank0;
    static uint32_t *iobank0pads;


 private:
    static void *base;
    static uint32_t *pwm0;

    static const uint32_t OFFSET_IOBANK0=0xd0000;
    static const uint32_t OFFSET_IOBANK0PADS=0xf0000;
    static const uint32_t OFFSET_RIO0=0xe0000;
    static const uint32_t  RIO_XOR=0x1000;
    static const uint32_t  RIO_SET=0x2000;
    static const uint32_t  RIO_CLR=0x3000;


};


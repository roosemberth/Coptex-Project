typedef volatile unsigned char I2C_REG;

typedef struct  _PCA9698{
    I2C_REG IPR[5];
    I2C_REG Reserved0[3];
    I2C_REG OPR[5];
    I2C_REG Reserved1[3];
    I2C_REG PIR[5];
    I2C_REG Reserved2[3];
    I2C_REG IOCR[5];
    I2C_REG Reserved3[3];
    I2C_REG MSKR[5];
    I2C_REG Reserved4[3];
    I2C_REG OUTCONFR;
    I2C_REG ALLBANKR;
    I2C_REG MODER;
} PCA9698, *PCA9698_P;

#define PCA9698_IPR             ((I2C_REG) 0x00)
#define PCA9698_OPR             ((I2C_REG) 0x08)
#define PCA9698_PIR             ((I2C_REG) 0x10)
#define PCA9698_IOCR            ((I2C_REG) 0x18)
#define PCA9698_MSKR            ((I2C_REG) 0x20)
#define PCA9698_OUTCONFR        ((I2C_REG) 0x28)
#define PCA9698_ALLBANKR        ((I2C_REG) 0x29)
#define PCA9698_MODER           ((I2C_REG) 0x2A)

#define PCA9698_PIN1            (0x1  <<  0)
#define PCA9698_PIN2            (0x1  <<  1)
#define PCA9698_PIN3            (0x1  <<  2)
#define PCA9698_PIN4            (0x1  <<  3)
#define PCA9698_PIN5            (0x1  <<  4)
#define PCA9698_PIN6            (0x1  <<  5)
#define PCA9698_PIN7            (0x1  <<  6)
#define PCA9698_PIN8            (0x1  <<  7)

#define PCA9698_OUTCONFR_OUT01  (0x1  <<  0)
#define PCA9698_OUTCONFR_OUT23  (0x1  <<  1)
#define PCA9698_OUTCONFR_OUT45  (0x1  <<  2)
#define PCA9698_OUTCONFR_OUT67  (0x1  <<  3)
#define PCA9698_OUTCONFR_OUT1   (0x1  <<  4)
#define PCA9698_OUTCONFR_OUT2   (0x1  <<  5)
#define PCA9698_OUTCONFR_OUT3   (0x1  <<  6)
#define PCA9698_OUTCONFR_OUT4   (0x1  <<  7)

#define PCA9698_ALLBANKR_BANK0  (0x1  <<  0)
#define PCA9698_ALLBANKR_BANK1  (0x1  <<  1)
#define PCA9698_ALLBANKR_BANK2  (0x1  <<  2)
#define PCA9698_ALLBANKR_BANK3  (0x1  <<  3)
#define PCA9698_ALLBANKR_BANK4  (0x1  <<  4)
#define PCA9698_ALLBANKR_BSEL   (0x1  <<  7)

#define PCA9698_MODER_OEPOL     (0x1  <<  0)
#define PCA9698_MODER_OCH       (0x1  <<  1)
#define PCA9698_MODER_IOAC      (0x1  <<  3)
#define PCA9698_MODER_SMBA      (0x1  <<  4)

 #ifndef ColorDetectorModule_H_
#define ColorDetectorModule_H_

#include "ModuleParent.h"

//Function Id
#define GRID_SETTING             0x01
#define COLOR_CALCULATION_TYPE   0x02    // for Dominant or average 
#define COLOR_SCHEME             0x03    // bit size of color
#define COLOR_DATA               0x04


//Literals
#define RGB_3BIT      3
#define RGB_15BIT       15
#define RGB_24BIT       24

#define GRAYSCALE_1BIT  1
#define GRAYSCALE_4BIT  4
#define GRAYSCALE_8BIT  8

//#define GRID_5x1                 0x04
#define GRID_3x3                 0x03
#define GRID_1x1                 0x01
#define GRID_5x5                 0x05

#define DOMINANT         0x01
#define AVERAGE           0x02

class ColorDetectorModule:public ModuleParent
{
public:
ColorDetectorModule();
void setColorScheme(byte);
void setGridSize(byte);
void setCalculationMode(byte);
uint8_t getRedColor();
uint8_t getBlueColor();
uint8_t getGreenColor();
uint8_t getRedColor(byte,byte);   //for different blocks of grid
uint8_t getBlueColor(byte,byte);  //for different blocks of grid
uint8_t getGreenColor(byte,byte); //for different blocks of grid
uint8_t getGridSize();
uint8_t getColorScheme();
uint8_t getCalculationMode();
void sendSettings(uint8_t,uint8_t,uint8_t);
int getColorValue(uint8_t,uint8_t,uint8_t);
//void sendSettings(void(*)(void));
//uint8_t singlecolorArray[2][3];
//uint8_t gridcolorArray[10][3];
//uint8_t grid5x5Array[26][3];
private:
void processData();
//void (*settingsCallBack)(void);

uint8_t** colorArray;
uint8_t currentArgnumber=0;
uint8_t gridSize=0;
uint8_t colorScheme=0;
uint8_t calculationMode=0;
};
extern ColorDetectorModule ColorDetector;
#endif

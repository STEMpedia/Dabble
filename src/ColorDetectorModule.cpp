#define FROM_DABBLE_LIBRARY
#include "Dabble.h"
#include "ColorDetectorModule.h"

float idealColorValue[5][3] ={  {255, 0, 0},         //RGB for red
							    {0, 255, 0},         //RGB for Green
								{0, 0, 255},         //RGB for Blue
								{255, 242, 0},       //RGB for Yellow
								{148, 0, 211},       //RGB for Violet
							 }; 


ColorDetectorModule::ColorDetectorModule():ModuleParent(COLORDETECTOR_ID),ColorPrediction()
{
}

void ColorDetectorModule::sendSettings(void(*function)(void))
{
	checksettingsCallBack=true;
	settingsCallBack = function;
}
void ColorDetectorModule::processData()
{
	if(checksettingsCallBack == true)
	{
		checksettingsCallBack=false;
	    (*settingsCallBack)();
	}
	byte functionID = getDabbleInstance().getFunctionId();
	if(functionID == COLOR_DATA)
	{
		colorScheme = getDabbleInstance().getArgumentData(0)[0];      //First arg line stores color settings
		calculationMode = getDabbleInstance().getArgumentData(0)[1];
		gridSize = getDabbleInstance().getArgumentData(0)[2];
		
		//Second arg line onwards color values are stored.
		if(currentArgnumber != getDabbleInstance().getArgumentNo())   //checks if 
		{
			if(currentArgnumber!=0)
			{
				for (int i = 0; i < currentArgnumber-1; i++)
                 {
                   delete [] colorArray[i];
                 }
              delete [] colorArray;
			}
			colorArray = new uint8_t*[getDabbleInstance().getArgumentNo()-1];
            for (int i = 0; i < getDabbleInstance().getArgumentNo()-1; i++)  //color values comes from second line
            {
              colorArray[i] = new uint8_t[3];
            }
        }
		currentArgnumber=getDabbleInstance().getArgumentNo();
		for (int i = 1; i < getDabbleInstance().getArgumentNo(); i++) //color values comes from second line
          {
            for (int j = 0; j < 3; j++)
               {
                 colorArray[i-1][j] = getDabbleInstance().getArgumentData(i)[j];
				 #ifdef DEBUG
				 Serial.print(colorArray[i-1][j]);
				 Serial.print(" ");
				 #endif
               }
			   #ifdef DEBUG
			   Serial.println();
			   #endif
		  }
    }
}
void ColorDetectorModule::setColorScheme(byte bitScheme)
{
	Dabble.sendModuleFrame(COLORDETECTOR_ID,0,COLOR_SCHEME,1,new FunctionArg(1,&bitScheme));
}

void ColorDetectorModule::setGridSize(byte gridsize)
{
	Dabble.sendModuleFrame(COLORDETECTOR_ID,0,GRID_SETTING,1,new FunctionArg(1,&gridsize));
}

void ColorDetectorModule::setCalculationMode(byte calculationMode)
{
    Dabble.sendModuleFrame(COLORDETECTOR_ID,0,COLOR_CALCULATION_TYPE,1,new FunctionArg(1,&calculationMode));	
}

int ColorDetectorModule::getRedColor()
{
   if(currentArgnumber !=0 )
   {
		return colorArray[0][0];
   }
   else
   {
		return -1;
   }
}

int ColorDetectorModule::getGreenColor()
{
   if(currentArgnumber !=0 )
   {
		return colorArray[0][1];
   }
   else
   {
		return -1;
   }
}

int ColorDetectorModule::getBlueColor()
{
   if(currentArgnumber !=0 )
   {
		return colorArray[0][2];
   }
   else
   {
		return -1;
   }
}


int ColorDetectorModule::getRedColor(byte row, byte col)
{
	if(currentArgnumber!=0)
	{
		if(row == 0)
		{
			return colorArray[col][0];
		}
		else if(row == 1)
		{
			return colorArray[(currentArgnumber/gridSize)+col][0];
		}
		else if(row == 2)
		{
			return colorArray[((currentArgnumber/gridSize)*2)+col][0];
		}
		else if(row == 3)
		{
			return colorArray[((currentArgnumber/gridSize)*3)+col][0];
		}
		else if(row == 4)
		{
			return colorArray[((currentArgnumber/gridSize)*4)+col][0];
		}
	}
	else
	{
		return -1;
	}
}

int ColorDetectorModule::getGreenColor(byte row, byte col)
{
	if(currentArgnumber!=0)
	{
		if(row == 0)
		{
			return colorArray[col][1];
		}
		else if(row == 1)
		{
			return colorArray[(currentArgnumber/gridSize)+col][1];
		}
		else if(row == 2)
		{
			return colorArray[((currentArgnumber/gridSize)*2)+col][1];
		}
		else if(row == 3)
		{
			return colorArray[((currentArgnumber/gridSize)*3)+col][1];
		}
		else if(row == 4)
		{
			return colorArray[((currentArgnumber/gridSize)*4)+col][1];
		}
	}
	else
	{
		return -1;
	}
}
int ColorDetectorModule::getBlueColor(byte row, byte col)
{
	if(currentArgnumber!=0)
	{
		if(row == 0)
		{
			return colorArray[col][2];
		}
		else if(row == 1)
		{
			return colorArray[(currentArgnumber/gridSize)+col][2];
		}
		else if(row == 2)
		{
			return colorArray[((currentArgnumber/gridSize)*2)+col][2];
		}
		else if(row == 3)
		{
			return colorArray[((currentArgnumber/gridSize)*3)+col][2];
		}
		else if(row == 4)
		{
			return colorArray[((currentArgnumber/gridSize)*4)+col][2];
		}
	}
	else
	{
		return -1;
	}
}

int ColorDetectorModule::getGrayScaleColor(byte row,byte col)
{
	if(currentArgnumber!=0 && (colorScheme == GRAYSCALE_1bit || colorScheme == GRAYSCALE_4bit || colorScheme == GRAYSCALE_8bit))
	{
		if(row == 0)
		{
			return colorArray[col][0];
		}
		else if(row == 1)
		{
			return colorArray[(currentArgnumber/gridSize)+col][0];
		}
		else if(row == 2)
		{
			return colorArray[((currentArgnumber/gridSize)*2)+col][0];
		}
		else if(row == 3)
		{
			return colorArray[((currentArgnumber/gridSize)*3)+col][0];
		}
		else if(row == 4)
		{
			return colorArray[((currentArgnumber/gridSize)*4)+col][0];
		}
	}
	else
	{
		return -1;
	}
}

uint8_t ColorDetectorModule::getGridSize()
{
	return gridSize;
}

uint8_t ColorDetectorModule::getColorScheme()
{
	return colorScheme;
}

uint8_t ColorDetectorModule::getCalculationMode()
{
	return calculationMode;
}


ColorPrediction::ColorPrediction(){
	min_deviation = 255;
}

bool ColorPrediction::checkColor(int *colorValue, uint8_t colorName)
{
	if((colorValue[0]==-1) || (colorValue[1]==-1) || (colorValue[2]==-1))
	{
		return 0;
	}
	else{
	min_deviation = 255;
	for(int i = 0;i<5;i++)
	{
		deviation = sqrt((sq(idealColorValue[i][0] - colorValue[0]) + sq(idealColorValue[i][1] - colorValue[1]) + sq(idealColorValue[i][2] - colorValue[2])) / 3);
		if(min_deviation>deviation)
		{
			min_deviation = deviation;
			colorFlag = i+1;
		}
	}
	if(colorFlag == colorName)
		return 1;
	else
		return 0;
	}
}

float ColorPrediction::getColorError(uint8_t *colorValue,uint8_t *referenceValue)
{
	if((colorValue[0]==-1) || (colorValue[1]==-1) || (colorValue[2]==-1))
	{
		return -1;
	}
	else
	{
	deviation = sqrt((sq(referenceValue[0] - colorValue[0]) + sq(referenceValue[1] - colorValue[1]) + sq(referenceValue[2] - colorValue[2])) / 3);
	return deviation;
	}
}
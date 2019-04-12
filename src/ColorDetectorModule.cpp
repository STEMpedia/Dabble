#define FROM_DABBLE_LIBRARY
#include "Dabble.h"
#include "ColorDetectorModule.h"
int checksettingsCallBack = 0;
ColorDetectorModule::ColorDetectorModule(): ModuleParent(COLORDETECTOR_ID)
{
}

void ColorDetectorModule::sendSettings(uint8_t Grid, uint8_t calcMode, uint8_t ColorScheme)
{
  checksettingsCallBack = 3;
 // Serial.println(checksettingsCallBack);
  if (Grid == 1)  //1x1
  {
    gridSize = 1;
  }
  else if (Grid == 2)  //3x3
  {
    gridSize = 3;
  }
  else if (Grid == 3) //5x5
  {
    gridSize = 5;
  }
  if (calcMode == 1)  //Dominant
  {
    calculationMode = 1;
  }
  else if (calcMode == 2) // Average
  {
    calculationMode = 2;
  }
  if (ColorScheme == 6 )   //GrayScale_1bit
  {
    colorScheme = 1 ;
  }
  else if (ColorScheme == 5 )   //GrayScale_4bit
  {
    colorScheme = 4;
  }
  else if (ColorScheme == 4 )   //GrayScale_8bit
  {
    colorScheme = 8 ;
  }
  else if (ColorScheme == 3 )   //Rgb_3bit
  {
    colorScheme = 3 ;
  }
  else if (ColorScheme == 2 )   //Rgb_15bit
  {
    colorScheme = 15 ;
  }
  else if (ColorScheme == 1)  //Rgb_24bit
  {
    colorScheme = 24;
  }

}

void ColorDetectorModule::sendSettings(void(*function)(void))
  {
	checksettingsCallBack=true;
	//settingsCallBack = function;
  }
void ColorDetectorModule::processData()
{
  if (checksettingsCallBack != 0)
  {
    while (checksettingsCallBack != 0)
    {
      if (checksettingsCallBack == 3)
      {
        Dabble.sendModuleFrame(COLORDETECTOR_ID, 0, COLOR_SCHEME, 1, new FunctionArg(1, &colorScheme));
        checksettingsCallBack = 2;
      }
      else if (checksettingsCallBack == 2)
      {
        Dabble.sendModuleFrame(COLORDETECTOR_ID, 0, GRID_SETTING, 1, new FunctionArg(1, &gridSize));
        checksettingsCallBack = 1;
      }
      else if (checksettingsCallBack == 1)
      {
        Dabble.sendModuleFrame(COLORDETECTOR_ID, 0, COLOR_CALCULATION_TYPE, 1, new FunctionArg(1, &calculationMode));
        checksettingsCallBack = 0;
      }
    }
  }
  byte functionID = getDabbleInstance().getFunctionId();
  if (functionID == COLOR_DATA )
  {
    if (checksettingsCallBack == 0)
    {
      colorScheme = getDabbleInstance().getArgumentData(0)[0];      //First arg line stores color settings
      calculationMode = getDabbleInstance().getArgumentData(0)[1];
      gridSize = getDabbleInstance().getArgumentData(0)[2];
    }
    //Second arg line onwards color values are stored.
    if (currentArgnumber != getDabbleInstance().getArgumentNo())
    {
      if (currentArgnumber != 0)
      {
        for (int i = 0; i < currentArgnumber - 1; i++)
        {
          delete [] colorArray[i];
        }
        delete [] colorArray;
      }
      colorArray = new uint8_t*[getDabbleInstance().getArgumentNo() - 1];
      for (int i = 0; i < getDabbleInstance().getArgumentNo() - 1; i++) //color values comes from second line
      {
        colorArray[i] = new uint8_t[3];
      }
    }
    currentArgnumber = getDabbleInstance().getArgumentNo();
    for (int i = 1; i < getDabbleInstance().getArgumentNo(); i++) //color values comes from second line
    {
      for (int j = 0; j < 3; j++)
      {
        colorArray[i - 1][j] = getDabbleInstance().getArgumentData(i)[j];
#ifdef DEBUG
        Serial.print(colorArray[i - 1][j]);
        Serial.print(" ");
#endif
      }
#ifdef DEBUG
      Serial.println();
#endif
    }
    /* if(getDabbleInstance().getArgumentNo() == 2)
      {
      for(int i = 0 ; i < 2 ;i++)
       {
      for(int j =0 ;j < 3;j++ )
       {
         singlecolorArray[i][j] = getDabbleInstance().getArgumentData(i)[j];
       //Serial.print(singlecolorArray[i][j]);
       //Serial.print("  ");
       }
         //Serial.println();
       }
      }
      if(getDabbleInstance().getArgumentNo() == 10)
      {
      for(int i = 0 ; i < 10 ;i++)
      {
      for(int j =0 ;j < 3;j++ )
       {
         gridcolorArray[i][j] = getDabbleInstance().getArgumentData(i)[j];
       Serial.print(gridcolorArray[i][j]);
       Serial.print("  ");
       }
         Serial.println();
      }
      }
      if(getDabbleInstance().getArgumentNo() == 26)
      {
      for(int i = 0 ; i < 26 ;i++)
      {
      for(int j =0 ;j < 3;j++ )
       {
         //gridcolorArray[i][j] = getDabbleInstance().getArgumentData(i)[j];
       Serial.print(getDabbleInstance().getArgumentData(i)[j]);
       Serial.print("  ");
       }
         Serial.println();
      }
      }
      }
      //functionID and incoming data based settings left
      /*if(functionID == COLOR_DATA)
      {
      newColorReceived = 1;
      if(newColorReceived == 1)
      {
      newColorReceived = 0;
       //delete previous data
      int a = sizeof(gridcolorArray)/sizeof(gridcolorArray[0]);
      //int b = sizeof(gridcolorArray[0]);
      for (int i = 0; i < a; i++)
       {
       delete [] gridcolorArray[i];
       }
       delete [] gridcolorArray;
      }

      // dynamic array as per data size
      gridcolorArray = new uint8_t*[getDabbleInstance().getArgumentNo()];
      for (int i = 0; i < getDabbleInstance().getArgumentNo(); i++)
      {
      gridcolorArray[i] = new uint8_t[3];        //
      }

      //data allocation in array
      for(int i = 0 ; i < getDabbleInstance().getArgumentNo() ;i++)
      {
      for(int j =0 ;j < 3;j++ )
      {
      gridcolorArray[i][j] = getDabbleInstance().getArgumentData(i)[j];
      Serial.print(gridcolorArray[i][j]);
      Serial.print("  ");
      }
      Serial.println();
      }
      }*/
  }
}
void ColorDetectorModule::setColorScheme(byte bitScheme)
{
  Dabble.sendModuleFrame(COLORDETECTOR_ID, 0, COLOR_SCHEME, 1, new FunctionArg(1, &bitScheme));
}

void ColorDetectorModule::setGridSize(byte gridsize)
{
  Dabble.sendModuleFrame(COLORDETECTOR_ID, 0, GRID_SETTING, 1, new FunctionArg(1, &gridsize));
}

void ColorDetectorModule::setCalculationMode(byte calculationMode)
{
  Dabble.sendModuleFrame(COLORDETECTOR_ID, 0, COLOR_CALCULATION_TYPE, 1, new FunctionArg(1, &calculationMode));
}

uint8_t ColorDetectorModule::getRedColor()
{
  if (currentArgnumber != 0 )
  {
    return colorArray[0][0];
  }
  else
  {
    return 0;
  }
}

uint8_t ColorDetectorModule::getGreenColor()
{
  if (currentArgnumber != 0 )
  {
    return colorArray[0][1];
  }
  else
  {
    return 0;
  }
}

uint8_t ColorDetectorModule::getBlueColor()
{
  if (currentArgnumber != 0 )
  {
    return colorArray[0][2];
  }
  else
  {
    return 0;
  }
}


uint8_t ColorDetectorModule::getRedColor(byte row, byte col)
{
  if (currentArgnumber != 0)
  {
    if (row == 0)
    {
      return colorArray[col][0];
    }
    else if (row == 1)
    {
      return colorArray[(currentArgnumber / gridSize) + col][0];
    }
    else if (row == 2)
    {
      return colorArray[((currentArgnumber / gridSize) * 2) + col][0];
    }
    else if (row == 3)
    {
      return colorArray[((currentArgnumber / gridSize) * 3) + col][0];
    }
    else if (row == 4)
    {
      return colorArray[((currentArgnumber / gridSize) * 4) + col][0];
    }
  }
  else
  {
    return 0;
  }
}

uint8_t ColorDetectorModule::getGreenColor(byte row, byte col)
{
  if (currentArgnumber != 0)
  {
    if (row == 0)
    {
      return colorArray[col][1];
    }
    else if (row == 1)
    {
      return colorArray[(currentArgnumber / gridSize) + col][1];
    }
    else if (row == 2)
    {
      return colorArray[((currentArgnumber / gridSize) * 2) + col][1];
    }
    else if (row == 3)
    {
      return colorArray[((currentArgnumber / gridSize) * 3) + col][1];
    }
    else if (row == 4)
    {
      return colorArray[((currentArgnumber / gridSize) * 4) + col][1];
    }
  }
  else
  {
    return 0;
  }
}
uint8_t ColorDetectorModule::getBlueColor(byte row, byte col)
{
  if (currentArgnumber != 0)
  {
    if (row == 0)
    {
      return colorArray[col][2];
    }
    else if (row == 1)
    {
      return colorArray[(currentArgnumber / gridSize) + col][2];
    }
    else if (row == 2)
    {
      return colorArray[((currentArgnumber / gridSize) * 2) + col][2];
    }
    else if (row == 3)
    {
      return colorArray[((currentArgnumber / gridSize) * 3) + col][2];
    }
    else if (row == 4)
    {
      return colorArray[((currentArgnumber / gridSize) * 4) + col][2];
    }
  }
  else
  {
    return 0;
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

int ColorDetectorModule::getColorValue(uint8_t colorName, uint8_t Row, uint8_t Col)
{
  if (gridSize == 3 && (Row < 3 && Col < 3))
  {
    if (colorName == 1)   //Red
    {
      return getRedColor(Row, Col);
    }
    else if (colorName == 2)   //Green
    {
      return getGreenColor(Row, Col);
    }
    else if (colorName == 3)   //Blue
    {
      return getBlueColor(Row, Col);
    }
    else if (colorName == 4) //Black
    {
      if ((colorScheme == GRAYSCALE_1BIT) || (colorScheme == GRAYSCALE_4BIT) || (colorScheme == GRAYSCALE_8BIT))
        return getRedColor(Row, Col);
      else
        return -1;
    }
  }
  else if (gridSize == 5 && (Row < 5 && Col < 5))
  {
    if (colorName == 1)   //Red
    {
      return getRedColor(Row, Col);
    }
    else if (colorName == 2)   //Green
    {
      return getGreenColor(Row, Col);
    }
    else if (colorName == 3)   //Blue
    {
      return getBlueColor(Row, Col);
    }
    else if (colorName == 4) //Black
    {
      if ((colorScheme == GRAYSCALE_1BIT) || (colorScheme == GRAYSCALE_4BIT) || (colorScheme == GRAYSCALE_8BIT))
        return getRedColor(Row, Col);
      else
        return -1;
    }
  }
  else if (gridSize == 1 && (Row < 1 && Col < 1))
  {
    if (colorName == 1)   //Red
    {
      return getRedColor();
    }
    else if (colorName == 2)   //Green
    {
      return getGreenColor();
    }
    else if (colorName == 3)   //Blue
    {
      return getBlueColor();
    }
    else if (colorName == 4) //Black
    {
      if ((colorScheme == GRAYSCALE_1BIT) || (colorScheme == GRAYSCALE_4BIT) || (colorScheme == GRAYSCALE_8BIT))
        return getRedColor();
      else
        return -1;
    }
  }
  else
  {
    return -1;
  }

}
/*uint8_t ColorDetectorModule::getRedColor(byte a)
  {
	return gridcolorArray[a][0];
  }

  uint8_t ColorDetectorModule::getGreenColor(byte a)
  {
	return gridcolorArray[a][1];
  }

  uint8_t ColorDetectorModule::getBlueColor(byte a)
  {
	return gridcolorArray[a][2];
  }

  uint8_t ColorDetectorModule::getRedColor()
  {
	return singlecolorArray[1][0];
  }

  uint8_t ColorDetectorModule::getGreenColor()
  {
	return singlecolorArray[1][1];
  }

  uint8_t ColorDetectorModule::getBlueColor()
  {
	return singlecolorArray[1][2];
  }*/

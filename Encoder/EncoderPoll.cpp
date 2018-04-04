#include "EncoderPoll.h"
#include <Arduino.h>

EncoderPoll::EncoderPoll(int _aPin, int _bPin, CountMode _mode)
	: mode(_mode)
	, lastEncoderVal(0)
	, aPin(_aPin)
	, bPin(_bPin)
  , constrainRange(false)
{
	pinMode(aPin, INPUT_PULLUP);
	pinMode(bPin, INPUT_PULLUP);
}

EncoderPoll::EncoderPoll(int _aPin, int _bPin, int _highValue, int _lowValue, CountMode _mode, int startValue)
  : mode(_mode)
  , lastEncoderVal(0)
  , aPin(_aPin)
  , bPin(_bPin)
  , constrainRange(true)
  , highValue(_highValue)
  , lowValue(_lowValue)
  , currentPosition(startValue)
{
  pinMode(aPin, INPUT_PULLUP);
  pinMode(bPin, INPUT_PULLUP);
}

void EncoderPoll::RunEncoder()
{
	int newA = digitalRead(aPin);
  int newB = digitalRead(bPin);
  
    int newEncoderVal = newA | newB << 1;

    if(newEncoderVal != lastEncoderVal)
    {

      if(newEncoderVal == ENCODER_POS_0){
        if(lastEncoderVal == ENCODER_POS_1){
          currentPosition--;
        }
        else{
          currentPosition++;
        }
      }
      else if(newEncoderVal == ENCODER_POS_1){
        if(lastEncoderVal == ENCODER_POS_2){
          currentPosition--;
        }
        else{
          currentPosition++;
        }
      }
      else if(newEncoderVal == ENCODER_POS_2){
        if(lastEncoderVal == ENCODER_POS_3){
          currentPosition--;
        }
        else{
          currentPosition++;
        }
      }
      else if(newEncoderVal == ENCODER_POS_3){
        if(lastEncoderVal == ENCODER_POS_0){
          currentPosition--;
        }
        else{
          currentPosition++;
        }
      }  

    lastEncoderVal = newEncoderVal;
  }

  if(constrainRange){
    if(currentPosition > highValue) currentPosition = highValue;
    else if(currentPosition < lowValue) currentPosition = lowValue;
  }
}

int EncoderPoll::ReadEncoder()
{
	if(mode == Quad4X)
	{
		return currentPosition;
	}
	else if(mode == Quad2X)
	{
		return currentPosition/2;
	}
	else
	{
		return currentPosition/4;
	}
}
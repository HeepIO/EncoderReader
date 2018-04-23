#include "HeepDeviceDefinitions.h"
#include "EncoderPoll.h"

#define ENCODER_PIN_1 5
#define ENCODER_PIN_2 4

EncoderPoll Encoder(ENCODER_PIN_1,ENCODER_PIN_2, 400, 0, EncoderPoll::Quad1X);

#define BUTTON_PIN 14

void InitializeControlHardware(){
  pinMode(BUTTON_PIN,INPUT_PULLUP);
}

int ReadDimmer(){
  int currentSetting = Encoder.ReadEncoder();
  SetControlValueByName("Dimmer",currentSetting);
  return currentSetting;
}

int ReadButton(){
  int currentSetting = digitalRead(BUTTON_PIN);
  SetControlValueByName("Button",currentSetting);
  return currentSetting;
}

void setup()
{

  Serial.begin(115200);
  InitializeControlHardware();
  AddRangeControl("Dimmer",HEEP_OUTPUT,100,0,0);
  AddOnOffControl("Button",HEEP_OUTPUT,0);
  StartHeep(heepDeviceName, 4);

}

void loop()
{
  PerformHeepTasks();
  ReadDimmer();
  ReadButton();

}
#include <FastLED.h>
#define NUM_LEDS 40
int num=NUM_LEDS;
#define DATA_PIN 3

int senzorPin=A0;
int ledPin=9;
int threshold=1 ;
int value=0;
int mappedValue=0;
int oldVal=0;
int difference;

int pinIn=A0, control=9;
int interval=100; //ms
float maximum=0, absoluteMaximum, controlValue;
int history[500];
long current=0;
float sound, soundSum=0;
int valueCounter=499;


CRGB leds[NUM_LEDS];
int hue;
int brightness;




void setup() {
  analogReference(INTERNAL);
  Serial.begin(9600);
  LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
  pinMode(senzorPin, INPUT);
}

int i;

void loop() {
  i=0;
  
  for(i = 0; i < NUM_LEDS; i++) 
  {
    brightness = getValue();
  leds[i] = CHSV(hue, 255, brightness);
  FastLED.show(); 
  delay(3);
  }
    
}


int getValue()
{
sound=analogRead(pinIn);

if(maximum<sound)
 {
      hue=(hue+3)%255;
  maximum=sound;
 }
addElement(sound);
maximum=maximum*0.99;
absoluteMaximum=getMax();
controlValue=map(maximum,0,absoluteMaximum,0,255);

if(controlValue>255)
controlValue=255; 

if(controlValue>5)
  {
    ;
  }
else
  controlValue=5;
  
//analogWrite(control, controlValue);
//Serial.println(sound);
Serial.println(controlValue);
return controlValue;

}


  //functions

void addElement(float x)
{

  for(int i=1; i<=valueCounter; i++)
  {
    history[i-1]=history[i];
  }
  
   history[valueCounter]=x;
}

float getMax()
{
      int i; 
      
    // Initialize maximum element 
    int maxArray = history[0]; 
  
    // Traverse array elements  
    // from second and compare 
    // every element with current max  
    for (i = 0; i < valueCounter; i++) 
     {       //  Serial.print(history[i]);
             // Serial.print(" ");
      if (history[i] > maxArray) 
  
            {
              maxArray = history[i]; 
            }
     }
            
    return maxArray; 


  
}

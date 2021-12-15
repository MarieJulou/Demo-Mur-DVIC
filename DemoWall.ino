#include <Adafruit_CircuitPlayground.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

//ACCELEROMETER
#define NUM_LEDS 10
float X, Y, Z;

#define analogPinFr 9
#define analogPinET 10
#define CAP_THRESHOLD   20

int rawFr = 0;
int Vin = 3.3;
float Vout = 0;
float RFrconnue = 30;
float RFrinconnue = 0; //400
int GreenQuantity = 0;

int analogPinEt = 10;

int rawEt = 0;
float REtconnue = 30;
float REtinconnue = 0; //400
int BlueQuantity = 0;

void setup() {
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(30);
  Serial.begin(9600);
  
}

void loop() {
  CircuitPlayground.clearPixels();
  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();
  Z = CircuitPlayground.motionZ();

  rawEt = analogRead(analogPinEt);
  rawFr = analogRead(analogPinFr); 
  RFrinconnue = rawFr * Vin;
  Vout = (RFrinconnue)/1024.0;
  RFrinconnue = (Vin/Vout) - 1;
  RFrinconnue= RFrconnue * RFrinconnue;
  Serial.print("Vout: ");
  Serial.println(Vout);
  if(Vout < 2.3){
    for( int i = 0; i < NUM_LEDS; i++){
    CircuitPlayground.setPixelColor( i, 0, 20, 155);
    delay(25);
    }
  }
  Serial.print("resiste capteur froissement: ");
  Serial.println(RFrinconnue);
  REtinconnue = rawEt * Vin;
  Vout = (REtinconnue)/1024.0;
  REtinconnue = (Vin/Vout) - 1;
  REtinconnue= REtconnue * REtinconnue;
  Serial.print("Vout: ");
  Serial.println(Vout);
  if(Vout < 0.60){
    for( int i = 0; i < NUM_LEDS; i++){
    CircuitPlayground.setPixelColor( i, 155, 20, 0);
    delay(25);
    }
  }
  Serial.print("resiste capteur étirement: ");
  Serial.println(REtinconnue);
  Serial.println(CircuitPlayground.readCap(0));
  if(CircuitPlayground.readCap(0) > CAP_THRESHOLD){
    fading(3);
  }
  if(CircuitPlayground.readCap(6) > CAP_THRESHOLD){
    fading(7);
  }
  
  delay(300);
}

void fading(int center){
  for( int i = 0; i < NUM_LEDS; i++){
    CircuitPlayground.setPixelColor((NUM_LEDS + center + i)%10, i*55, int(Z)*15, 255-i*55);
    CircuitPlayground.setPixelColor((NUM_LEDS + center - i)%NUM_LEDS, i*55, int(Z)*15, 255-i*55);
    delay(25);
  }
}

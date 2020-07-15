#include <Wire.h>
#include <math.h>
#include <PZEM004Tv30.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x3f, 20, 4); //0x27  0x3f, 20, 4

float w1, w2, w3, v1, v2, v3, a1, a2, a3, wh1, wh2, wh3;

String vS1, aS1, wS1, whS1, vS2, aS2, wS2, whS2, vS3, aS3, wS3, whS3;

PZEM004Tv30 pzem1(2, 16);  // (RX,TX) connect to TX,RX of PZEM
PZEM004Tv30 pzem2(12, 14); 
PZEM004Tv30 pzem3(D3, D7); 

void setup() {
  Serial.begin(115200);

  pinMode(A0, OUTPUT); 
  
  lcd.begin();
  lcd.backlight();
  
  pzem1.setAddress(0x42);
  pzem2.setAddress(0x42);
  pzem3.setAddress(0x42);

}

void loop() {
  updatePzem();
  Serial.println("pzem1: " + String(v1) + " v " + String(w1) + " w " + "pzem2: " + String(v2) + " v " + String(w2) + " w " + "pzem3: " + String(v3) + " v " + String(w3) + " w");
  updateDisplay();
}

void updateDisplay(){
  String displayStr = "";

  displayStr += (formatCell(v1) + " ");
  displayStr += (formatCell(v2) + " ");
  displayStr += (formatCell(v3));

  lcd.clear();
  lcd.print( displayStr);
}

String formatCell(float val) {
  if (isnan(val)){
    return "   0.0";
  } 
  else if (val <= 0){
    return "   0.0";
  } 
  else if (val < 10){
    return "  " + String(val).substring(0, 3);
  } 
  else if (val < 100){
    return "  " + String(val).substring(0, 4);
  }
  else if (val < 1000){
    return " " + String(val).substring(0, 5);
  }
  else if (val < 10000){
    return String(val).substring(0, 6);
  }
  else if (val < 100000){
    return " " + String(val).substring(0, 5);
  }
  return String(val);
}

void updatePzem(){
  v1 = pzem1.voltage();
  v2 = pzem2.voltage();
  v3 = pzem3.voltage();

  v1 = 0;
  v2 = 0;
  v3 = 0;

  a1 = pzem1.current();
  a2 = pzem2.current();
  a3 = pzem3.current();

  w1 = pzem1.power();
  w2 = pzem2.power();
  w3 = pzem3.power();

  wh1 = pzem1.energy();
  wh2 = pzem2.energy();
  wh3 = pzem3.energy();
}

#include <Wire.h>
#include <PZEM004Tv30.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x3f, 20, 4); //0x27  0x3f, 20, 4

float w1, w2, w3, v1, v2, v3, a1, a2, a3, wh1, wh2, wh3;

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
  v1 = pzem1.voltage();
  v2 = pzem2.voltage();
  v3 = pzem3.voltage();

  a1 = pzem1.current();
  a2 = pzem2.current();
  a3 = pzem3.current();

  w1 = pzem1.power();
  w2 = pzem2.power();
  w3 = pzem3.power();

  wh1 = pzem1.energy();
  wh2 = pzem2.energy();
  wh3 = pzem3.energy();

  Serial.println("pzem1: " + String(v1) + " v " + String(w1) + " w " + "pzem2: " + String(v2) + " v " + String(w2) + " w " + "pzem3: " + String(v3) + " v " + String(w3) + " w");

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ln   V    A     W    ");
  lcd.setCursor(0,1);
  
  //if (v1 > 100 && a1 < 10 && w1 > 100 && w1 < 999){
    
  if ( v1 > 0.0 ){
    String Ad1 = " 0 ";
    String Wd1 = "0";
  
    if ( a1 < 10 ){
      Ad1 = String( a1 ).substring(0,3); 
    } else {
      Ad1 = String( a1 ).substring(0,4);
    }

    if (w1 <= 0) { 
      Wd1 = "  0";
    } else {
      Wd1 = String( int( w1 ) );
    }
  
    lcd.print("1   " + String(v1).substring(0, 3)  + "  " + Ad1 + "  " + Wd1 + "      " );
  }
  else {
    lcd.print("1    0    0     0    ");
  }

  lcd.setCursor(0,2);

  if ( v2 > 0.0 ){
    String Ad2 = " 0 ";
    String Wd2 = "0";
  
    if ( a2 < 10 ){
      Ad2 = String( a2 ).substring(0,3); 
    } else {
      Ad2 = String( a2 ).substring(0,4);
    }

    if (w2 <= 0) { 
      Wd2 = "  0";
    } else {
      Wd2 = String( int( w2 ) );
    }
  
    lcd.print("2   " + String(v2).substring(0, 3)  + "  " + Ad2 + "  " + Wd2 + "      " );
  }
  else {
    lcd.print("2    0    0     0    ");
  }

  lcd.setCursor(0,3);

  if ( v3 > 0.0 ){
    String Ad3 = " 0 ";
    String Wd3 = "0";
  
    if ( a3 < 10 ){
      Ad3 = String( a3 ).substring(0,3); 
    } else {
      Ad3 = String( a3 ).substring(0,4);
    }

    if (w3 <= 0) { 
      Wd3 = "  0";
    } else {
      Wd3 = String( int( w3 ) );
    }
  
    lcd.print("3   " + String(v3).substring(0, 3)  + "  " + Ad3 + "  " + Wd3 + "      " );
  }
  else {
    lcd.print("3    0    0     0    ");
  }
  
  lcd.setCursor(0,0);
}

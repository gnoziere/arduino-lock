/*
 * Based on the tutorial: http://www.circuitbasics.com/how-to-set-up-a-keypad-on-an-arduino/
 * Code to activate an electromagnet using a password entered with a keypad and LCD screen
 */

#include <Wire.h> 
#include <LiquidCrystal.h>
#include <Keypad.h>

#define Password_Length 5

int signalPin = 53;

char Data[Password_Length]; 
char Master[Password_Length] = "1234"; 
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {23, 25, 27, 29};
byte colPins[COLS] = {31, 33, 35, 37};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){ 
  Serial.begin(9600);
    
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Enter Password:");

  pinMode(signalPin, OUTPUT);
  digitalWrite(signalPin, HIGH);
}

void loop(){
  customKey = customKeypad.getKey();
  
  if (customKey) {
    Serial.print(customKey);
    Data[data_count] = customKey; 
    lcd.setCursor(data_count, 1); 
    lcd.print(Data[data_count]); 
    data_count++; 
  }

  if (data_count == Password_Length-1) {
    lcd.clear();

    if (!strcmp(Data, Master)) {
      lcd.print("Correct!");
      digitalWrite(signalPin, LOW); 
      delay(10000);
      digitalWrite(signalPin, HIGH);
    } else {
      lcd.print("Incorrect!");
      delay(1000);
    }
    
    lcd.clear();
    clearData();  
  }
}

void clearData(){
  while(data_count != 0) {
    Data[data_count--] = 0; 
  }
  return;
}

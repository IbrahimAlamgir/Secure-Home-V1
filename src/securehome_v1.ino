```cpp
#include <Wire.h>               
#include <LiquidCrystal_I2C.h>  

const int PIR_PIN = 2;          
const int BTN_PIN = 3;          
const int LDR_PIN = A0;         
const int BUZZER_PIN = 8;       
const int RED_PIN = 9;          
const int GRN_PIN = 10;         
const int BLU_PIN = 11;         

enum SystemState { DISARMED, ARMED, ALARM }; 
SystemState currentState = DISARMED;         

volatile bool intruderDetected = false;      
unsigned long lastBlinkTime = 0;             
bool alarmToggle = false;                    

LiquidCrystal_I2C lcd(32, 16, 2);            

void setup() {
  pinMode(RED_PIN, OUTPUT);                  
  pinMode(GRN_PIN, OUTPUT);                  
  pinMode(BLU_PIN, OUTPUT);                  
  pinMode(BUZZER_PIN, OUTPUT);               
  
  pinMode(BTN_PIN, INPUT);                   
  pinMode(PIR_PIN, INPUT);                   
  
  lcd.init();                                
  lcd.backlight();                           
  
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), movementISR, RISING); 
  
  delay(1000);                               
  goDisarmed();                              
}

void loop() {
  monitorButton();                           
  runSystemLogic();                          
}

void movementISR() {
  if (currentState == ARMED) {
    intruderDetected = true;                 
  }
}

void monitorButton() {
  static bool lastBtn = LOW;                 
  bool currentBtn = digitalRead(BTN_PIN);    
  
  if (currentBtn == HIGH && lastBtn == LOW) { 
    if (currentState == DISARMED) goArmed(); 
    else goDisarmed();                       
  }
  delay(50);                                 
  lastBtn = currentBtn;                      
}

void goArmed() {
  intruderDetected = false;                  
  currentState = ARMED;                      
  updateLCD("SYSTEM ARMED", "Monitoring..."); 
  setRGB(0, 0, 255);                         
}

void goDisarmed() {
  currentState = DISARMED;                   
  intruderDetected = false;                  
  noTone(BUZZER_PIN);                        
  updateLCD("SYSTEM READY", "State: DISARMED"); 
  setRGB(0, 255, 0);                         
}

void runSystemLogic() {
  int lightLevel = analogRead(LDR_PIN);      
  
  if (currentState == ARMED && (intruderDetected || lightLevel > 700)) { 
    currentState = ALARM;                    
    updateLCD("INTRUDER ALERT!", "CHECK SENSORS"); 
  }
  
  if (currentState == ALARM) {
    flashAlarm();                            
  }
}

void flashAlarm() {
  if (millis() - lastBlinkTime > 400) {      
    alarmToggle = !alarmToggle;              
    if (alarmToggle) {
      setRGB(255, 0, 0);                     
      tone(BUZZER_PIN, 1000);                
    } else {
      setRGB(0, 0, 0);                       
      noTone(BUZZER_PIN);                    
    }
    lastBlinkTime = millis();                
  }
}

void setRGB(int r, int g, int b) {
  analogWrite(RED_PIN, r);                   
  analogWrite(GRN_PIN, g);                   
  analogWrite(BLU_PIN, b);                   
}

void updateLCD(String l1, String l2) {
  lcd.clear();                               
  lcd.setCursor(0, 0);                       
  lcd.print(l1);                             
  lcd.setCursor(0, 1);                       
  lcd.print(l2);                             
}

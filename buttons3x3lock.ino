int tuchPins[9] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
bool tuchPinsEnable[9] = {true, true, true, true, false, true, true, true, true};
    
const byte ledRows[3] = {A0, A1, A2}; //+
const byte ledCols[3] = {A3, A4, A5}; //-

int code[9] = {5, 7, 9, 1, 3, 2, 4, 6, 8};
int i, state = 0;

int ledmatrix[3][3] = { {0,0,0}, {0,0,0}, {0,0,0} }; //обернено перша одиничка то 9 третя то 7

int blinkCount = 0;
unsigned long previousMillis = 0;
const long interval = 700;           // интервал между включение/выключением светодиода (1 секунда = 1000)

void setup() {
   Serial.begin(9600); //delete
  for (i = 0; i < 9; i++) {
    pinMode(tuchPins[i], INPUT);
  }
  for (i = 0; i < 3; i++) {
    pinMode(ledRows[i], OUTPUT);
    pinMode(ledCols[i], OUTPUT);
  }
  for (i = 0; i < 3; i++) {
    digitalWrite(ledRows[i], LOW);
    digitalWrite(ledCols[i], HIGH);
  }

}

void loop() {
  if (state == 9) {
   unsigned long currentMillis = millis();
   
    
   if (currentMillis - previousMillis >= interval && blinkCount < 4) {
    // сохраняем время последнего переключения
    previousMillis = currentMillis;
 Serial.println("win!!");
    // если светодиод не горит, то зажигаем, и наоборот
    if (ledmatrix[0][0] == 0) {
      for (int c = 0; c < 3; c++){
        for (int v = 0; v < 3; v++){
          ledmatrix[c][v] = 1;
          
        }
      }
      blinkCount++;
    } else {
      for (int c = 0; c < 3; c++){
        for (int v = 0; v < 3; v++){
          ledmatrix[c][v] = 0;
        }
      }
    }
   }

   if (blinkCount == 4) 
   {
    Serial.println("new game start");
     blinkCount = 0;
     state = 0;
      for (int p = 0; p < 9; p++){
       tuchPinsEnable[p] = true;
      }
       tuchPinsEnable[4] = false;
      for (int c = 0; c < 3; c++){
        for (int v = 0; v < 3; v++){
          ledmatrix[c][v] = 0;
        }
      }
   }
    
  }
  else {
  
  if (digitalRead(tuchPins[code[state]-1])==HIGH && tuchPinsEnable[code[state]-1] == false)
  {
    
    tuchPinsEnable[code[state+1]-1] = false;
    LedOn(code[state]);
    state++;
    
    Serial.print(tuchPinsEnable[0]);
    Serial.print(tuchPinsEnable[1]);
    Serial.print(tuchPinsEnable[2]);
    Serial.print(tuchPinsEnable[3]);
    Serial.print(tuchPinsEnable[4]);
    Serial.print(tuchPinsEnable[5]);
    Serial.print(tuchPinsEnable[6]);
    Serial.print(tuchPinsEnable[7]);
    Serial.println(tuchPinsEnable[8]);
  }
  for (int q = 1; q < 9; q++) //з 1 тому шо первий сенсор все видає HIGH
  {
    //Serial.println(tuchPinsEnable[code[state]-1]);
    if (q != code[state]-1 && digitalRead(tuchPins[q]) == HIGH && tuchPinsEnable[q] == true) {
      Serial.print(q+1);
      Serial.println(" wrong");
      Serial.println(tuchPinsEnable[code[state]-1]);
      state = 0;
      for (int p = 0; p < 9; p++){
       tuchPinsEnable[p] = true;
      }
       tuchPinsEnable[4] = false;
      for (int c = 0; c < 3; c++){
        for (int v = 0; v < 3; v++){
          ledmatrix[c][v] = 0;
        }
      }
    }
  }
 printclickkey();
 }
 ledsRefresh();
}

void ledsRefresh(){
  for (int h = 0; h < 3; h++){
    digitalWrite(ledCols[h], LOW);
    for (int j = 0; j < 3; j++){
      if (ledmatrix[h][j] == 1) {
        digitalWrite(ledRows[j], HIGH);
      }
      else {
        digitalWrite(ledRows[j], LOW);
      }
    }
    delay(2);
    for (int i = 0; i < 3; i++) {
      digitalWrite(ledRows[i], LOW);
      digitalWrite(ledCols[i], HIGH);
    }
  }
}

void LedOn(int number) {
  switch (number) {
   case 1:
        ledmatrix[2][0] = 1;
      break;
   case 2:
        ledmatrix[2][1] = 1;
      break;
   case 3:
        ledmatrix[2][2] = 1;
      break;
   case 4:
        ledmatrix[1][0] = 1;
      break;
   case 5:
        ledmatrix[1][1] = 1;
      break;
   case 6:
        ledmatrix[1][2] = 1;
      break;
   case 7:
        ledmatrix[0][0] = 1;
      break;
   case 8:
        ledmatrix[0][1] = 1;
      break;
   case 9:
        ledmatrix[0][2] = 1;
      break;
  }
  
}

void printclickkey() { 
if (digitalRead(tuchPins[0])==HIGH)
 {
    //Serial.println("1"); 
    //LedOn(1);
 }
 if (digitalRead(tuchPins[1])==HIGH)
 {
    Serial.println("2");
     //LedOn(2);
 }
 if (digitalRead(tuchPins[2])==HIGH)
 {
    Serial.println("3"); 
    //LedOn(3);
 }
 if (digitalRead(tuchPins[3])==HIGH)
 {
    Serial.println("4");
    //LedOn(4);
 }
 if (digitalRead(tuchPins[4])==HIGH)
 {
    Serial.println("5"); 
    //LedOn(5);
 }
 if (digitalRead(tuchPins[5])==HIGH)
 {
    Serial.println("6"); 
    //LedOn(6);
 }
 if (digitalRead(tuchPins[6])==HIGH)
 {
    Serial.println("7"); 
    //LedOn(7);
 }
 if (digitalRead(tuchPins[7])==HIGH)
 {
    Serial.println("8"); 
    //LedOn(8);
 }
 if (digitalRead(tuchPins[8])==HIGH)
 {
    Serial.println("9"); 
    //LedOn(9);
 }
}

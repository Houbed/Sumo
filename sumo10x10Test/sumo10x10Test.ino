const int LCS = 7;
const int RCS = 4;

const int RS = 3;
const int LS = 6;
const int FRS = 8;
const int FMS = 12;
const int FLS = 7;
const int BLS = 5;

const int RE1 = 10;
const int RE2 = 11;
const int LE1 = 5;
const int LE2 = 6;

const int start = 9;

const int range = 400;
const int Cwhite = 100;

boolean Direction = true;

int LCSV, RCSV, RSV, LSV, FRSV, FMSV, FLSV,BLSV; 
long timeStart;

void setup() {
  Serial.begin(9600);
  pinMode(RE1, OUTPUT);
  pinMode(RE2, OUTPUT);
  pinMode(LE1, OUTPUT);
  pinMode(LE2, OUTPUT);
  
  pinMode(FRS, INPUT);
  pinMode(FLS, INPUT);

  pinMode(start, INPUT);
  while (!digitalRead(start)){
    Serial.println(digitalRead(FLS));
    }
  drive(255,255);
  delay(300);
}

void loop() {

  LCSV = analogRead(LCS);
  RCSV = analogRead(RCS);
  RSV = analogRead(RS);
  LSV = analogRead(LS);
  FRSV = digitalRead(FRS);
  FMSV = digitalRead(FMS);
  FLSV = digitalRead(FLS);
  BLSV = analogRead(BLS);

  if (!digitalRead(start)) drive(0,0);

  else if (LCSV < Cwhite) {drive(-255, -100); delay(200); drive(-255, 255); delay(100); timeStart = millis();}
  else if (RCSV < Cwhite) {drive(-100, -255); delay(200); drive(255, -255); delay(100); timeStart = millis();}
  else if (LCSV < Cwhite and RCSV < Cwhite) {drive(-255, -255); delay(300);  timeStart = millis();}
    
  else if (FLSV == 1 and FMSV == 1 and FRSV == 1) {
    if  (millis()-timeStart<2000) drive(255, 255);
    else {drive(0,-255); delay(100);  timeStart = millis();}
  }
  else if (FLSV == 1 and FMSV == 1) {drive(100, 255); Direction = true; timeStart = millis();} // перед
  else if (FLSV == 1 and FMSV == 0 and FRSV == 0) {drive(0,255); Direction = true;  timeStart = millis();} // перед
  else if (FLSV == 0 and FMSV == 1 and FRSV == 1) {drive(255,100); Direction = false;  timeStart = millis();} // перед
  else if (FLSV == 0 and FMSV == 0 and FRSV == 1) {drive(255,0); Direction = false;  timeStart = millis();}
  
  else if (LSV > range) {drive(-200,255); Direction = true;  timeStart = millis();}
  else if (RSV > range) {drive(255,-200); Direction = false;  timeStart = millis();}          // поиск

  else if (BLSV  > range){drive(0, 255); delay(100); Direction = true;  timeStart = millis();}
  else if(Direction) {drive(30,100);  timeStart = millis();}
  else {drive(100,30); timeStart = millis();}
  delay(1);
  
}
void drive(int RS,int LS){
  if (RS > 0){
   digitalWrite(RE1, LOW);//вперед
   analogWrite(RE2, abs(RS));;
    }
  if (RS <= 0){
   digitalWrite(RE2, LOW);//назад
   analogWrite(RE1, abs(RS));
    } 
  if (LS > 0){
   digitalWrite(LE1, LOW);//вперед
   analogWrite(LE2, abs(LS));
    }
  if (LS <= 0){
   digitalWrite(LE2, LOW);//назад
   analogWrite(LE1, abs(LS));
    }   
}

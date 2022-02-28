const int LCS = 7;
const int RCS = 4;

const int RS = 3;
const int LS = 6;
const int FRS = 8;
const int FLS = 7;
const int BLS = 5;

const int RE1 = 10;
const int RE2 = 11;
const int LE1 = 5;
const int LE2 = 6;

const int start = 9;

const int range = 250;
const int Cwhite = 200;

boolean Direction = true;  

void setup() {
  Serial.begin(9600);
  pinMode(RE1, OUTPUT);
  pinMode(RE2, OUTPUT);
  pinMode(LE1, OUTPUT);
  pinMode(LE2, OUTPUT);
  
  pinMode(FRS, INPUT);
  pinMode(FLS, INPUT);

  pinMode(start, INPUT);
  
  while (!digitalRead(start)){Serial.println(analogRead(LCS));}
  while (analogRead(LCS) > Cwhite or analogRead(RCS) > Cwhite){drive(1,100,1,100);}
  drive(0,255,0,255); delay(800);
}

void loop() {

  if (!digitalRead(start)) drive(0,0,0,0);
  
  else if (analogRead(LCS) < Cwhite and analogRead(RCS) < Cwhite) {drive(0,250,0,250); delay(300);}
  else if (analogRead(LCS) < Cwhite) {drive(0,250,0,150); delay(300);}
  else if (analogRead(RCS) < Cwhite) {drive(0,150,0,250); delay(300);}
    
  else if (digitalRead(FLS) == 1 and digitalRead(FRS) == 1)  drive(1,255,1,255);
  else if (digitalRead(FLS) > digitalRead(FRS)) {drive(1,0,1,255); Direction = true;} // перед
  else if (digitalRead(FLS) < digitalRead(FRS)) {drive(1,255,1,0); Direction = false;}
  
  else if (analogRead(LS) > range) {drive(0,200,1,200); Direction = true;}
  else if (analogRead(RS) > range) {drive(1,200,0,200); Direction = false;}          // поиск

  else if (analogRead(BLS) > range){drive(0,200,1,200); Direction = true;}
  else if(Direction) drive(0,200,1,200);
  else drive(1,200,0,200);
  Serial.println(analogRead(LS));
}
void drive(int RD,int RS,int LD,int LS){
  if (RD == 1){
   digitalWrite(RE1, LOW);//назад
   analogWrite(RE2, RS);;
    }
  if (RD == 0){
   digitalWrite(RE2, LOW);//назад
   analogWrite(RE1, RS);
    } 
  if (LD == 1){
   digitalWrite(LE1, LOW);//вперед
   analogWrite(LE2, LS);
    }
  if (LD == 0){
   digitalWrite(LE2, LOW);//назад
   analogWrite(LE1, LS);
    }   
}

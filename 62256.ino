#define WE 12
#define OE 11
#define CE 10
#define IOS 2
#define IOE 9
#define AS 22
#define AE 36





void setup() {
  Serial.begin(9600);
  pinMode(WE, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(CE, OUTPUT);

  for(int i = IOS; i <= IOE; i++){
    pinMode(i, OUTPUT);
  }

  for(int i = AS; i <= AE; i++){
    pinMode(i, OUTPUT);
  }

  startHigh();
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  writeAddr(154, 69);
  delay(100);
  Serial.println(readAddr(154));
}

void writeAddr(int addr, int data){
  startHigh();
  setIODir(OUTPUT);
  setAddr(addr);
  writeIO(data);
  digitalWrite(CE, LOW);
  digitalWrite(WE, LOW);
  digitalWrite(WE, HIGH);
  digitalWrite(CE, HIGH);
  
}

int readAddr(int addr){
  startHigh();
  setAddr(addr);
  digitalWrite(CE, LOW);
  digitalWrite(OE, LOW);
  setIODir(INPUT);
  int retNum = readIO();
  digitalWrite(CE, HIGH);
  digitalWrite(OE, HIGH);
  return retNum;
}

void startHigh(){
  digitalWrite(WE, HIGH);
  digitalWrite(CE, HIGH);
  digitalWrite(OE, HIGH);
}


int readIO(){
  int bitMask = 1, retNum = 0;
  for(int i = IOS; i <= IOE; i++){
    digitalRead(i);
    retNum += digitalRead(i) << (i - IOS);
    bitMask <<= 1;
  }

  return retNum;
}

void writeIO(int data){
  int bitMask = 1;
  for(int i = IOS; i <= IOE; i++){
    digitalWrite(i, (data & bitMask) >> (i - IOS));
    bitMask <<= 1;
  }
}

void setAddr(int addr){
  int bitMask = 1;
  for(int i = AS; i <= AE; i++){
    digitalWrite(i, (addr & bitMask) >> (i - AS));
    bitMask <<= 1;
  }
}

void setIODir(int dir){ // 0 = input, 1 = output
  if(dir == INPUT){
    for(int i = IOS; i <= IOE; i++){
      pinMode(i, INPUT);
    }
  }
  if(dir == OUTPUT){
    for(int i = IOS; i <= IOE; i++){
      pinMode(i, OUTPUT);
    }
  }
}

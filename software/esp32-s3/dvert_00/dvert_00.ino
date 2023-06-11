/*

* Register:
b7 b6 b5 b4 b3 b2 b1 b0
x  x  x  x  x  0  0  0     REG_CFG
x  x  x  x  x  0  0  1     REG_RD
x  x  x  x  x  0  1  0     REG_WR
x  x  x  x  x  0  1  1     REG_PWM
x  x  x  x  x  1  0  0     CFG_PWM
x  x  x  x  x  1  0  1     RD_CFG
x  x  x  x  x  1  1  0     VERT_VERS

b3: 0 <-- byte
b3: 1 <-- bit

b4: 0 <-- A rib
b4: 1 <-- B rib

b7 b6 b5 : bit port address (if b3 == 1)

** Register REG_CFG:
b7 b6 b5 b4 b3 b2 b1 b0
x  x  x  x  x  0  0  0     REG_CFG

i2cset -y 1 <I2C addr byte> <REG byte> <COMMAND word> w
0: Output
1: Input
00: 8 outputs
FF: 8 inputs

A output, B input:
i2cset -y 1 0x20 0x00 0x00FF w

A and B inputs:
i2cset -y 1 0x20 0x00 0xFFFF w

A input and B output:
i2cset -y 1 0x20 0x00 0xFF00 w

A and B outputs:
i2cset -y 1 0x20 0x00 0x0000 w

** Register REG_WR:
b7 b6 b5 b4 b3 b2 b1 b0
x  x  x  x  x  0  1  0     REG_WR

Writing bit or byte:
b3 (REG_WR): 0 <-- byte
b3 (REG_WR): 1 <-- bit

A or B rib:
b4 (REG_WR): 0 <-- A rib
b4 (REG_WR): 1 <-- B rib

Which bit (0..7):
b7 b6 b5 b4 b3 b2 b1 b0
0  0  0  x  1  0  1  0     bit 0
0  0  1  x  1  0  1  0     bit 1
0  1  0  x  1  0  1  0     bit 2
0  1  1  x  1  0  1  0     bit 3
1  0  0  x  1  0  1  0     bit 4
1  0  1  x  1  0  1  0     bit 5
1  1  0  x  1  0  1  0     bit 6
1  1  1  x  1  0  1  0     bit 7

Sending 1 (0x01) to 0x20 vertebra / A rib / bit Output 0 
i2cset -y 1 0x20 0x0a 0x01
Reg 0x0a:
b7 b6 b5 b4 b3 b2 b1 b0
0  0  0  0  1  0  1  0

Sending 0 (0x00) to 0x20 vertebra / A rib / bit Output 0 
i2cset -y 1 0x20 0x0a 0x00

Sending 1 (0x01) to 0x20 vertebra / B rib / bit Output 0 
i2cset -y 1 0x20 0x1a 0x01
Reg 0x1a:
b7 b6 b5 b4 b3 b2 b1 b0
0  0  0  1  1  0  1  0

Sending 0 (0x00) to 0x20 vertebra / B rib / bit Output 0 
i2cset -y 1 0x20 0x1a 0x00

Sending 01011010 (0x5a) to 0x20 vertebra / A rib  
i2cset -y 1 0x20 0x02 0x5a

Sending 10110101 (0xa5) to 0x20 vertebra / A rib  
i2cset -y 1 0x20 0x02 0xa5

Sending 00001111 (0x0f) to 0x20 vertebra / B rib  
i2cset -y 1 0x20 0x12 0x0f

Sending 11110000 (0xf0) to 0x20 vertebra / B rib  
i2cset -y 1 0x20 0x12 0x0f

Sending 11110000 (0xf0) to 0x20 vertebra / A rib  
i2cset -y 1 0x20 0x02 0x0f

** Register REG_RD:
* b7 b6 b5 b4 b3 b2 b1 b0
x  x  x  x  x  0  0  1     REG_RD

b4: 0 <-- A rib
b4: 1 <-- B rib

Raspberry Pi needs two I2C sendings to read properly.

Reading A rib / 0x20 vertebra
i2cget -y 1 0x20 0x01
i2cget -y 1 0x20 0x01

Reading B rib / 0x20 vertebra
i2cget -y 1 0x20 0x11
i2cget -y 1 0x20 0x11

** Register CFG_PWM:
b7 b6 b5 b4 b3 b2 b1 b0
x  x  x  x  x  1  0  0     CFG_PWM

This digital vertebra is using an ESP32-S3.
ESP32 has 16 PWM channels, ESP32-C3 has 6 PWM channels.
ESP32-S2 and ESP32-S3 have 8 PWM channels.

Only one register ( A rib or B rib ) can be PWM at the same time.

A rib (0x00) as 8 PWM outputs:
i2cset -y 1 0x20 0x04 0x00

B rib (0x01) as 8 PWM outputs:
i2cset -y 1 0x20 0x04 0x01


** Register REG_PWM:
b7 b6 b5 b4 b3 b2 b1 b0
x  x  x  x  x  0  1  1     REG_PWM

Sending 200 (range from 0 to 255) to B rib (b4 = 1) to bit (b3 = 1) 2 (b7=0, b6=1, b5 = 0) at 0x20 vertebra
i2cset -y 1 0x20 0x5B 200
b7 b6 b5 b4 b3 b2 b1 b0
0  1  0  1  1  0  1  1     REG_PWM

Sending 5 (range from 0 to 255) to B rib (b4 = 1) to 8 outputs (b3 = 0) at 0x20 vertebra
i2cset -y 1 0x20 0x13 5
b7 b6 b5 b4 b3 b2 b1 b0
0  0  0  1  0  0  1  1     REG_PWM

** Register RD_CFG:
b7 b6 b5 b4 b3 b2 b1 b0
x  x  x  x  x  1  0  1     RD_CFG

Raspberry Pi needs two I2C sendings to read properly.
i2cget -y 1 0x20 0x05
i2cget -y 1 0x20 0x05

Answer
0  x  x  x  0  0  0  1     A input
0  0  0  1  0  x  x  x     B input
0  x  x  x  0  0  1  0     A output
0  0  1  0  0  x  x  x     B output
0  x  x  x  0  1  0  0     A pwm
0  1  0  0  0  x  x  x     B pwm

** Register VERSION:
b7 b6 b5 b4 b3 b2 b1 b0
x  x  x  x  x  1  1  0     VERT_VERS

Raspberry Pi needs two I2C sendings to read properly.
i2cget -y 1 0x20 0x06 w
i2cget -y 1 0x20 0x06 w


Jordi Binefa - 20230602
iotvertebrae.com
 */
#include <Wire.h>

#define I2C_ADDR_BASE 0x20

#define DVERT_VERSION    0x01
#define DVERT_SUBVERSION 0x00

#define ADDR0 20
#define ADDR1 19
#define ADDR2 16
#define ADDR3 15
#define LED_MQTT 48
#define A0 14
#define A1 21
#define A2 39
#define A3 40
#define A4 41
#define A5 42
#define A6 2
#define A7 1
#define B0 4
#define B1 5
#define B2 6
#define B3 7
#define B4 13
#define B5 12
#define B6 11
#define B7 10

#define REG_CFG   0x00
#define REG_RD    0x01
#define REG_WR    0x02
#define REG_PWM   0x03
#define CFG_PWM   0x04
#define RD_CFG    0x05
#define VERT_VERS 0x06

const byte cbA[8] = {A0,A1,A2,A3,A4,A5,A6,A7};
const byte cbB[8] = {B0,B1,B2,B3,B4,B5,B6,B7};
byte byI2cAddr;
byte byLastReadNumber,byRibCfg;

void vSetupAddr(){
  pinMode(LED_MQTT, OUTPUT);
  pinMode(ADDR0, INPUT_PULLUP);
  pinMode(ADDR1, INPUT_PULLUP);
  pinMode(ADDR2, INPUT_PULLUP);
  pinMode(ADDR3, INPUT_PULLUP); 
}

void vSetupIO(String sQ,int nMode){
  int i;
  
  if(sQ == "A"){
    byRibCfg &= 0xF0;
    byRibCfg |= (nMode == INPUT)?0x01:0x02;
    for(i = 0; i < 8; i++)
      pinMode(cbA[i],nMode);
  }
  if(sQ == "B"){
    byRibCfg &= 0x0F;
    byRibCfg |= (nMode == INPUT)?0x10:0x20;
    for(i = 0; i < 8; i++)
      pinMode(cbB[i],nMode);
  }
}

void vSetupGPIO(word wCfg){
  word wI = 0x0001;
  int i;

  // Serial.print("Word: 0x");
  Serial.println(wCfg,HEX);

  for(i = 0; i < 8; i++,wI<<=1){
    pinMode(cbB[i],(wCfg & wI)?INPUT:OUTPUT);
    // Serial.print("cbB[");
    // Serial.print(i);
    // Serial.print("]: ");
    // Serial.println((wCfg & wI)?"INPUT":"OUTPUT");
    byRibCfg &= 0x0F; // It has sense when B rib are 8 inputs or 8 outputs
    byRibCfg |= (wCfg & wI)?0x10:0x20; // It has sense when B rib are 8 inputs or 8 outputs
  }
  for(i = 0; i < 8; i++,wI<<=1){
    pinMode(cbA[i],(wCfg & wI)?INPUT:OUTPUT);
    // Serial.print("cbA[");
    // Serial.print(i);
    // Serial.print("]: ");
    // Serial.println((wCfg & wI)?"INPUT":"OUTPUT");
    byRibCfg &= 0xF0; // It has sense when A rib are 8 inputs or 8 outputs
    byRibCfg |= (wCfg & wI)?0x01:0x02; // It has sense when A rib are 8 inputs or 8 outputs
  }  
}

void vSetupPWM(byte by){
  const int pwmFreq = 500,pwmResolution = 8;
  int i;
  
  if(by == 0x00){ // A port as PWM
    byRibCfg &= 0xF0;
    byRibCfg |= 0x04;
    for(i = 0; i < 8; i++){
      ledcSetup(i,pwmFreq,pwmResolution); // i: channel (0..15)
      ledcAttachPin(cbA[i], i);
      Serial.print("cbA[");
      Serial.print(i);
      Serial.print("] attached to ");
      Serial.print(i);
      Serial.println(" pwm channel");
    }
  }else{ // B port as PWM
    byRibCfg &= 0x0F;
    byRibCfg |= 0x40;
    for(i = 0; i < 8; i++){
      // ledcSetup(i+8,pwmFreq,pwmResolution); // i: channel (0..15)
      // ledcAttachPin(cbB[i], i+8);
      ledcSetup(i,pwmFreq,pwmResolution); // i: channel (0..7)
      ledcAttachPin(cbB[i], i);
      Serial.print("cbB[");
      Serial.print(i);
      Serial.print("] attached to ");
      // Serial.print(i+8);
      Serial.print(i);
      Serial.println(" pwm channel");
    }
  }
}

byte byReadI2cAddress(){
  byte byAddr = (digitalRead(ADDR3))?0x00:0x1;
  
  byAddr |= (digitalRead(ADDR2))?0x00:0x2;
  byAddr |= (digitalRead(ADDR1))?0x00:0x4;
  byAddr |= (digitalRead(ADDR0))?0x00:0x8;
  
  return I2C_ADDR_BASE | byAddr;
}

void vWrite(String sQ,byte by){
  byte byI = 0x01;
  int i;

  Serial.print("vWrite(");
  Serial.print(by,HEX);
  Serial.println("){");
  for(i = 0; i < 8; i++,byI<<=1){
    //Serial.print("GPIO: ");
    //Serial.print((sQ == "A")?cbA[i]:cbB[i]);
    //Serial.print(", Value: ");
    //Serial.println((by&byI)?HIGH:LOW);
    digitalWrite((sQ == "A")?cbA[i]:cbB[i],by&byI);
  }
  Serial.println(sQ);
  Serial.println("}vWrite");
}

byte byRead(String sQ){
  byte byI = 0x01,byR = 0x00;
  int i;

  for(i = 0; i < 8; i++,byI<<=1){
    byR |= (digitalRead((sQ == "A")?cbA[i]:cbB[i]))?byI:0x00;
    /* Serial.print((sQ == "A")?"a[":"b[");
    Serial.print(i);
    Serial.print("]: ");
    Serial.print(digitalRead((sQ == "A")?cbA[i]:cbB[i]));
    Serial.print(" - byI: ");
    Serial.print(byI,HEX);
    Serial.print(" - byR: ");
    Serial.println(byR,HEX); */
  }
  
  return byR; 
}

void requestEvent() {
  delay(100);
  if((byLastReadNumber & 0x07) == REG_RD){
        if(byLastReadNumber & 0x10){
          // Wire.write(0xB);
          Wire.write(byRead("B"));
        }else{
          // Wire.write(0xA);
          Wire.write(byRead("A"));
        }
  }
  if((byLastReadNumber & 0x7) == RD_CFG){
    Wire.write(byRibCfg);
  }
  if((byLastReadNumber & 0x7) == VERT_VERS){
        Wire.write(DVERT_SUBVERSION);
        Wire.write(DVERT_VERSION);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println(__FILE__);
  
  vSetupAddr();
  byI2cAddr = byReadI2cAddress();
  Serial.print("I2C address: 0x");
  Serial.println(byI2cAddr,HEX);

  Wire.begin(byI2cAddr);
  Wire.onReceive(BlinkLED);
  Wire.onRequest(requestEvent);

  byRibCfg = 0x00;
  vSetupIO("A",OUTPUT);
  vSetupIO("B",OUTPUT);
}

void BlinkLED(int Press) {
  enum {cfg,rd,wr,pwm,cfgPwm,rdCfg,versio,no} enReg = no;
  int n = 0,nPwmChannel,nBit,i;
  byte byCfgA,byCfgB,byReg;

  digitalWrite(LED_MQTT,HIGH);
  while (1 < Wire.available()) { // loop through all but the last
    byLastReadNumber = Wire.read();   // receive byte as a character
    Serial.print(n,DEC);
    Serial.print(") El màster m'ha fet arribar un 0x");
    Serial.println(byLastReadNumber,HEX);
    switch(n++){
      case 0:
        Serial.print("byLastReadNumber & 0x07: 0x");
        Serial.println(byLastReadNumber & 0x07,HEX);
        switch(byLastReadNumber & 0x07){
          case REG_CFG: enReg = cfg; break;
          case REG_RD:  enReg = rd; break;
          case REG_WR:  enReg = wr; break;
          case REG_PWM: enReg = pwm; break;
          case CFG_PWM: enReg = cfgPwm; /*Serial.println("enReg = cfgPwm")*/;break;
          case RD_CFG: enReg = rdCfg; Serial.println("enReg = rdCfg");break;
          case VERT_VERS: enReg = versio; Serial.println("enReg = versio");break;
          default: enReg = no; Serial.println("enReg = no");
        }
        byReg = byLastReadNumber;
        break;
      case 1:
        switch(enReg){
          case cfg:
            // Serial.print("Configuració B: 0x");
            // Serial.println(byLastReadNumber,HEX);
            byCfgB = byLastReadNumber;
            break;
        }
        break;
    }
  }
  byLastReadNumber = Wire.read();
  Serial.print(n,DEC);
  Serial.print("> El màster m'ha fet arribar un 0x");
  Serial.println(byLastReadNumber,HEX);
  switch(n){
    case 0:
      byReg = byLastReadNumber;
      if((byReg & 0x7) == REG_RD){
        Serial.print("byReg: 0x");
        Serial.println(byReg,HEX);
        Serial.println((byReg & 0x10)?"Sol·licitud de lectura B":"Sol·licitud de lectura A");
        /*if(byReg & 0x10){
          Wire.write(0xB);
        }else{
          Wire.write(0xA);
        }*/
      }   
      if((byReg & 0x7) == RD_CFG){
        Serial.println("Reading rib configuration");
      }
      if((byReg & 0x7) == VERT_VERS){
        Serial.println("Reading version");
        Wire.write(DVERT_VERSION);
        Wire.write(DVERT_SUBVERSION);
      }
      break;
    case 1:
      switch(enReg){
          case wr:
            if(byReg & 0x08){
              // Escriptura a nivell de bit
              Serial.print("bit: ");
              Serial.println(byReg >> 5);
              digitalWrite((byReg & 0x10)?cbB[byReg >> 5]:cbA[byReg >> 5],byLastReadNumber);
            }else{
              // Escriptura a nivell de byte
              // Serial.println(byReg,HEX);
              vWrite((byReg & 0x10)?"B":"A",byLastReadNumber);
            }
            break;        
           case pwm:
            Serial.print("PWM byReg: 0x");
            Serial.println(byReg,HEX);
            if(byReg & 0x08){
              // Escriptura a nivell de bit
              Serial.print("PWM ");
              Serial.print((byReg & 0x10)?"b[":"a[");
              nBit = byReg >> 5;
              Serial.print(nBit);
              Serial.print("]: ");
              Serial.println(byLastReadNumber,DEC);
              // nPwmChannel = nBit + ((byReg & 0x10)?8:0);
              nPwmChannel = nBit;
              Serial.print("PWM channel: ");
              Serial.println(nPwmChannel,DEC);
              ledcWrite(nPwmChannel,byLastReadNumber);
            }else{
              // Escriptura a nivell de byte
              // Serial.println(byReg,HEX);
              Serial.print("PWM ");
              Serial.print((byReg & 0x10)?"B: ":"A: ");
              Serial.println(byLastReadNumber,DEC);             
              Serial.print("PWM channels: ");
              //Serial.println((byReg & 0x10)?"All from 8 to 15":"All from 0 to 7");
              Serial.println("All from 0 to 7");
              for(i = 0; i < 8 ; i++){
                ledcWrite(i,byLastReadNumber);
              }
            }
            break;
           case cfgPwm:
            Serial.print("CFG PWM: ");
            Serial.println(byLastReadNumber,DEC);
            vSetupPWM(byLastReadNumber); // A: 0x00, B: 0x01
            break;        
     }
      break;
   
    case 2:
      switch(enReg){
          case cfg:
            // Serial.print("Configuració A: 0x");
            // Serial.println(byLastReadNumber,HEX);
            byCfgA = byLastReadNumber;
            vSetupGPIO(byCfgA << 8 | byCfgB);
            break;
      }
      break;
    default:
      switch(enReg){
          case cfg:
            Serial.println("I don't understand your port setup.");
      }    
  }
  digitalWrite(LED_MQTT,LOW);
}
/*
void requestEvent() {
  Serial.print("Esclau respon 0x");
  Serial.print(byLastReadNumber%2,HEX);
  Serial.print(" 0x");
  Serial.println(byLastReadNumber+5,HEX);
  Wire.write(byLastReadNumber%2); // respond with message of 1 byte
  Wire.write(byLastReadNumber+5); // respond with message of 1 byte
  // Wire.endTransmission(); // No millora el decalatge
  // as expected by master
  Serial.println((byLastReadNumber & 0x10)?"B":"A");
}*/

void loop() {
  delay(100);
}

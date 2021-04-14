#include<SoftwareSerial.h>

long pmcf10 = 0;
long pmcf25 = 0;
long pmcf100 = 0;
long pmat10 = 0;
long pmat25 = 0;
long pmat100 = 0;
int count = 0;
unsigned char c, last_c;

SoftwareSerial PMS(2,3);
SoftwareSerial BT(10,9);

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  PMS.begin(9600);
}

void loop() {
  unsigned char high;
  while(PMS.available()){
    last_c = c;
    c = PMS.read();
    if(last_c == 0x42 && c == 0x4d) count = 1;
    if(count == 4 || count == 6 || count == 8 || count == 10 || count == 12 || count == 14) high = c;
    else if(count == 7){
      pmcf25 = 256*high + c;
      Serial.print("CF=1,PM25=:");
      Serial.print(pmcf25);
      Serial.print("ug/m3");
      Serial.print("\n");
      BT.println(pmcf25);
    }
    else if(count == 13){
      pmat25 = 256*high + c;
      Serial.print("atmosphere,PM25=:");
      Serial.print(pmat25);
      Serial.print("ug/m3");
      Serial.print("\n");
    }
    if(count < 100)count++;
  }
}

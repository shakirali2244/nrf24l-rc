#include <SPI.h>
#include <RH_NRF24.h>
#include <Servo.h> 
RH_NRF24 nrf24;
Servo throttle;
Servo roll;
Servo pitch;
Servo yaw;

String safeVal = "00323232";
String payload;
char mem[2];
char *ptr;

void setup(){
  Serial.begin(9600);
  while (!Serial); 
  if (!nrf24.init())
    Serial.println("init failed");
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");
  Serial.println("all passed");
  throttle.attach(3);
  roll.attach(5);
  pitch.attach(6);
  yaw.attach(9);
}

unsigned long hex2int(char *a, unsigned int len)
{
   int i;
   unsigned long val = 0;

   for(i=0;i<len;i++)
      if(a[i] <= 57)
       val += (a[i]-48)*(1<<(4*(len-1-i)));
      else
       val += (a[i]-55)*(1<<(4*(len-1-i)));
   return val;
}

void ParseAndWrite(char payload[]){
  mem[0] = payload[0];
  mem[1] = payload[1];
  ptr = mem;
  unsigned long throttle = hex2int(ptr,2);
  mem[0] = payload[2];
  mem[1] = payload[3];
  ptr = mem;
  unsigned long roll = hex2int(ptr,2); 
  mem[0] = payload[4];
  mem[1] = payload[5];
  ptr = mem;
  unsigned long pitch = hex2int(ptr,2);
  mem[0] = payload[6];
  mem[1] = payload[7];
  ptr = mem;
  unsigned long yaw = hex2int(ptr,2);
  Serial.println("tadasd");
  Serial.println("throttle,roll,pitch,yaw " + String((throttle+100)*10,DEC) + String((roll+100)*10,DEC) + String((pitch+100)*10,DEC) + String((yaw+100)*10,DEC));
}

void loop(){
uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
uint8_t len = sizeof(buf);
if (nrf24.recv(buf, &len)){
Serial.println("got payload: ");

char buffer[];
buffer = (char*)buf;
ParseAndWrite(buf);
}else{
  payload = safeVal;
  char buffer[10];
  payload.toCharArray(buffer,10);
  ParseAndWrite(buffer);
}
  delay(400);
}

#include <SPI.h>
#include <RH_NRF24.h>
#include <Servo.h> 
RH_NRF24 nrf24;
Servo throttle_pin;

String safeVal = "00323232";
String payload;
int pos = 150;
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
  throttle_pin.attach(3);
  throttle_pin.write(30);
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
  float throttle_val = (throttle * 255 )/100;
  float roll_val = (roll * 255 )/100;
  float pitch_val = (pitch * 255 )/100;
  float yaw_val = (yaw * 255 )/100;
  int pos = int(throttle_val);
  pos = map(pos, 0, 255, 1000, 2000);
  delay(15);
  throttle_pin.writeMicroseconds(pos);  
  //Serial.print(int(throttle_val));
  //Serial.print(" ");
  //Serial.print(int(roll_val));
  //Serial.print(" ");
  //Serial.print(int(pitch_val));
  //Serial.print(" ");
  //Serial.println(int(yaw_val));
  Serial.println(int(throttle_val));
  //analogWrite(roll_pin,int(throttle_val));
  //Serial.println("throttle,roll,pitch,yaw %i %i %i %i ", int(throttle_val) ,int(roll_val) , int(pitch_val) , int(yaw_val));
}
  
void loop(){
  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  if (nrf24.recv(buf, &len)){
    //Serial.println((char*)buf);
    char buffer[len];
   for (int i = 0; i < len; i++){
     buffer[i] = (char)buf[i];
   }
    //buffer = (char)buf;
    ParseAndWrite(buffer);
  }
  while(!nrf24.waitAvailableTimeout(30)){
    payload = safeVal;
    char buffer[11];
    payload.toCharArray(buffer,11);
    ParseAndWrite(buffer);
  }
}


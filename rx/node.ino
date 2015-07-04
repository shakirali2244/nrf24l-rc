#include <SPI.h>
#include <RH_NRF24.h>
#include <Servo.h> 
RH_NRF24 nrf24;
Servo throttle_pin;
Servo roll_pin;
Servo pitch_pin;
Servo yaw_pin;

String safeVal = "00505050";
String payload;
String mem;
//char *ptr;

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
  roll_pin.attach(5);
  pitch_pin.attach(6);
}

void ParseAndWrite(char payload[]){
  
   mem="\0";
   mem+=payload[0];
   mem+=payload[1];
   int throttle_val = map( mem.toInt(), 0, 100, 1000, 2000);
   throttle_pin.writeMicroseconds(throttle_val);
   mem="\0";
   mem+=payload[2];
   mem+=payload[3];
   int roll_val = map( mem.toInt(), 0, 100, 1000, 2000);
   roll_pin.writeMicroseconds(roll_val);
   mem="\0";
   mem+=payload[4];
   mem+=payload[5];
   int pitch_val = map( mem.toInt(), 0, 100, 1000, 2000);
   pitch_pin.writeMicroseconds(pitch_val);
   Serial.println(payload);
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
  while(!nrf24.waitAvailableTimeout(200)){
    payload = safeVal;
    char buffer[11];
    payload.toCharArray(buffer,11);
    ParseAndWrite(buffer);
  }
}


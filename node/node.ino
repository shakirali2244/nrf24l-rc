#include <SPI.h>
#include <RH_NRF24.h>
RH_NRF24 nrf24;

String payload;
String mem;
int relay = 6;

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
  send("hello server");
  pinMode(relay,OUTPUT);
}

void ParseAndWrite(char payload[]){
   mem="\0";
   mem+=payload[0];
   digitalWrite(relay,mem.toInt());
   Serial.println("Wrote");
   Serial.println(mem.toInt());
}
void send(String payload){
  uint8_t data[RH_NRF24_MAX_MESSAGE_LEN];
  payload.getBytes(data, RH_NRF24_MAX_MESSAGE_LEN) ;
  nrf24.send(data, sizeof(data));
  nrf24.waitPacketSent();
  Serial.println("Sent payload :"+payload);
}
  
  
void loop(){
  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  if (nrf24.recv(buf, &len)){
    char buffer[len];
   for (int i = 0; i < len; i++){
     buffer[i] = (char)buf[i];
   }
    ParseAndWrite(buffer);
  }
}


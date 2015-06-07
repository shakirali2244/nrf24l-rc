
#include <SPI.h>
#include <RH_NRF24.h>

RH_NRF24 nrf24;
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
}

String content = "00323232";
String safeVal = "00323232";
char character;

void send(String payload){
  uint8_t data[RH_NRF24_MAX_MESSAGE_LEN];
  payload.getBytes(data, RH_NRF24_MAX_MESSAGE_LEN) ;
  nrf24.send(data, sizeof(data));
  nrf24.waitPacketSent();
  Serial.println("Sent payload :"+payload);
}

void loop(){
  if(Serial.available()){
    content = "\0";
    while(Serial.available()) {
      character = Serial.read();
      content.concat(character);
      delay(10);
    }
    send(content);
    delay(100);
  }else{
    send(content);
  }
}




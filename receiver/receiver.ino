#include <WiFi.h>
#include <esp_now.h>

const uint8_t senderMacAddress[] = {0xD4, 0xD4, 0xDA, 0x5D, 0x1C, 0x10}; // Replace with the sender's MAC address

struct __attribute__((packed)) JoystickData {
  int xAxis;
  int yAxis;
};

typedef struct motor {
  int id; // Useless?
  int dir_pin;
  int pwm_pin;
  int state;
  int speed;
} mot;

#define MT_CTRL(num, pin1, pin2) \
{ \
  .id = num, \
  .dir_pin = pin1, \
  .pwm_pin = pin2, \
  .state = LOW, \
  .speed = 100, \
}

mot mot1 MT_CTRL(1, 5, 18);  // Motor 1
mot mot2 MT_CTRL(2, 2, 4);  // Motor 2

void __motor_activate(struct motor mot) {
  if (mot.dir_pin)
    digitalWrite(mot.dir_pin, mot.state);
  // Unfortunately, ESP8266 does not support analogWrite on all pins
  // You may need to use a different microcontroller that supports PWM on these pins
}

void forward(int speed) {
  mot1.state = LOW;
  mot2.state = LOW;
  mot1.speed = speed;
  mot2.speed = speed;
  __motor_activate(mot1);
  __motor_activate(mot2);
}

void backward(int speed) {
  mot1.state = HIGH;
  mot2.state = HIGH;
  mot1.speed = speed;
  mot2.speed = speed;
  __motor_activate(mot1);
  __motor_activate(mot2);
}

void left(int speed) {
  mot1.state = LOW;
  mot2.state = HIGH;
  mot1.speed = speed;
  mot2.speed = speed;
  __motor_activate(mot1);
  __motor_activate(mot2);
}

void right(int speed) {
  mot1.state = HIGH;
  mot2.state = LOW;
  mot1.speed = speed;
  mot2.speed = speed;
  __motor_activate(mot1);
  __motor_activate(mot2);
}

void stop() {
  mot1.state = LOW;
  mot2.state = LOW;
  mot1.speed = 0;
  mot2.speed = 0;
  __motor_activate(mot1);
  __motor_activate(mot2);
}

void OnDataRecv(const uint8_t *senderMac, const uint8_t *data, int dataLength) {
  JoystickData joystick;
  memcpy(&joystick, data, sizeof(joystick));

  // Use joystick voltage values directly to control motors
  int LY = joystick.yAxis;
  int LX=joystick.xAxis;
  // Serial.println(LY);
    int x_volt = ( (LX * 3.3 ) / 4095 );  /*Convert digital value to voltage */
 int  y_volt = ( ( LY * 3.3 ) / 4095 ); 
Serial.println(x_volt); 


  // Map joystick voltage values to motor speeds
  int speed = map(LY, 0, 1023, 0, 255);

  if (y_volt >= 2) {
    forward(speed);
    Serial.println("forward");
  } else if (y_volt <2 && y_volt >=1 && x_volt <2 && x_volt >=1) {
    stop();
    Serial.println("stop");
   
    
  } else if(y_volt < 1){
    
     backward(speed);
Serial.println("backward"); 
 }



else if (x_volt >= 2) {
    left(speed);
    Serial.println("left");
  } 
  else if(x_volt < 1){
    
    right(speed);
Serial.println("right");  }
}

void setup() {
  pinMode(mot1.dir_pin, OUTPUT);
  pinMode(mot2.dir_pin, OUTPUT);
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(); // We do not want to connect to a WiFi network

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW initialization failed");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);

  // Add the sender as a peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, senderMacAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  Serial.println("Initialized.");
}

void loop() {
  // You can add your own code here if needed
  delay(100); // Delay to allow processing of incoming messages
}

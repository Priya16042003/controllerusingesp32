#include <WiFi.h>
#include <esp_now.h>

const uint8_t receiverMacAddress[] = {0x78, 0x21, 0x84, 0xE1, 0x70, 0x20}; // Replace with the receiver's MAC address

struct __attribute__((packed)) JoystickData {
  int xAxis;
  int yAxis;
};

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  if (status == ESP_NOW_SEND_SUCCESS) {
    Serial.println("Joystick data sent successfully");
  } else {
    Serial.println("Error sending the joystick data");
  }
}

void setup() {
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(); // We do not want to connect to a WiFi network

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW initialization failed");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  // Add the receiver as a peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, receiverMacAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  Serial.println("Initialized.");
}

void loop() {
  // Simulate joystick data (replace this with your actual joystick data)
  JoystickData joystick;
  joystick.xAxis = analogRead(36); // Read X-axis value
  joystick.yAxis = analogRead(39); // Read Y-axis value

  // Send joystick data as a packet
  esp_err_t result = esp_now_send(receiverMacAddress, (uint8_t *)&joystick, sizeof(joystick));

  if (result == ESP_OK) {
    Serial.println("Joystick data sent with success");
    Serial.println( joystick.xAxis);
  } else {
    Serial.println("Error sending the joystick data");
  }

  delay(100); // Adjust the delay based on your desired sending rate
}

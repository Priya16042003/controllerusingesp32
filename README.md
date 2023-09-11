# ESP-NOW Joystick Controller

This project consists of a sender and receiver code for controlling motors using a joystick over ESP-NOW communication. The sender reads joystick data and transmits it to the receiver, which controls the motors based on the received data.

## Getting Started

### Prerequisites

To use this code, you will need:

- Two ESP32 (or compatible) microcontrollers, one for the sender and one for the receiver.
- Arduino IDE with ESP32 support.
- Joystick (analog or digital) for the sender.

### Wiring

#### Sender (Joystick Controller)

- Connect the joystick's X-axis to `A0` and the Y-axis to `A1`.
- Upload the sender code to one of the ESP32 devices.

#### Receiver (Motor Controller)

- Connect the motor driver pins (`dir_pin` and `pwm_pin`) to the motors.
- Upload the receiver code to the other ESP32 device.

## Usage

1. Power up both sender and receiver modules.
2. The sender reads joystick data and sends it to the receiver.
3. The receiver processes the data and controls the motors accordingly.
4. The system will execute actions based on joystick movements:
   - Forward: Joystick forward movement
   - Backward: Joystick backward movement
   - Left: Joystick left movement
   - Right: Joystick right movement
   - Stop: Joystick at the center position

## Configuration

- Modify MAC addresses in the code to match your ESP32 modules' MAC addresses.
- Adjust pin configurations if necessary (e.g., motor driver pins).

## Dependencies

This project uses the following Arduino libraries:

- [WiFi](https://www.arduino.cc/en/Reference/WiFi) - For Wi-Fi connectivity.
- [esp_now](https://github.com/espressif/arduino-esp32/tree/master/libraries/esp_now) - For ESP-NOW communication.

## Contributing

If you'd like to contribute to this project, please follow these guidelines:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Make your changes and test thoroughly.
4. Create a pull request with a clear description of your changes.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Authors

- Priya Jain(https://github.com/Priya16042003)




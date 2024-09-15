# Current Sensor Limiter System

This project is designed to control relays based on the current and voltage readings from sensors. The system monitors power consumption and adjusts relay states to limit power usage, with setpoint adjustment functionality and EEPROM storage for retaining setpoint values.

## Components and Wiring

### Sensors

| **Component**      | **Arduino Pin** |
| ------------------ | --------------- |
| **Current Sensor** |                 |
| VCC                | VCC             |
| GND                | GND             |
| Data               | A2              |
| **Voltage Sensor** |                 |
| VCC                | VCC             |
| GND                | GND             |
| Data               | A3              |

### Buttons

| **Component**   | **Arduino Pin** |
| --------------- | --------------- |
| **Button Up**   |                 |
| IN              | A0              |
| OUT             | GND             |
| **Button Down** |                 |
| IN              | A1              |
| OUT             | GND             |

### Relay Module

| **Component** | **Arduino Pin** |
| ------------- | --------------- |
| **Relay 1**   | 6               |
| **Relay 2**   | 5               |
| **Relay 3**   | 4               |
| **Relay 4**   | 3               |
| **VCC**       | VCC             |
| **GND**       | GND             |

## Features

1. **Real-time Monitoring**:
   - Current (`I`) and Voltage (`V`) are monitored from sensors and displayed on the LCD.
2. **Setpoint Adjustment**:

   - Power setpoint can be increased or decreased using the Up and Down buttons.
   - The setpoint is stored in EEPROM and will persist between power cycles.

3. **Relay Control**:
   - Four relays are controlled based on power consumption and the setpoint.
   - The system adjusts which relays are on/off according to the current power consumption relative to the setpoint.

## Calibration

- Current and voltage sensors have predefined zero points. These can be modified in the code to match your sensor setup.

## Code Details

### Pin Assignments

- **Relay Pins**: 6 (Relay 1), 5 (Relay 2), 4 (Relay 3), 3 (Relay 4)
- **Button Pins**: A0 (Button Up), A1 (Button Down)
- **Sensor Pins**: A2 (Current), A3 (Voltage)

### Relay Operation Logic

Relays will turn on or off based on the calculated power (`daya`) and the setpoint:

- If `count == 0`: All relays are off.
- If `count == 1`: Relay 1 is on, others are off.
- If `count == 2`: Relay 1 and 2 are on, others are off.
- If `count == 3`: Relay 1, 2, and 3 are on.
- If `count == 4`: All relays are on.

### Power Monitoring and Control

- **Power Calculation**:
  Power (`daya`) is calculated as the product of current (`arus`) and voltage (`tegangan`):

  ```cpp
  daya = arus * tegangan;
  ```

- Setpoint Adjustment:
  - The setpoint can be increased or decreased in steps of 5 using the Up and Down buttons.
  - The setpoint is stored in EEPROM and loaded during startup.
- Current and Voltage Calculation: The project includes functions to accurately measure current and voltage:

```cpp
double get_voltage(int ampPin) // Reads voltage from the sensor
float get_current(int ampPin)  // Reads current from the sensor
```

## Installation Instructions

1. Copy Libraries: Copy the contents of the lib folder to your Documents/Arduino/libraries directory.

2. Calibration: Follow the sensor calibration process, as shown in this tutorial.

3. Upload the Code: Upload the code to your Arduino.

4. Setpoint Adjustment:
   - Use the Up and Down buttons to modify the setpoint.
   - The setpoint will be displayed on the LCD and saved in EEPROM.

## Folders Structure

- Lock Mode: The code for lock mode is found in the arduino folder.
- No Lock Mode: The code for no lock mode is found in the arduino_nolock folder.

## License

This project is open-source and licensed under the MIT License.

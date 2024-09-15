# Current Sensor Control System

This project is designed to control multiple relays based on current and voltage readings using an Arduino. The system adjusts the relays depending on the power consumption in relation to a setpoint value. The setpoint is stored in EEPROM and can be adjusted using buttons.

## Components Used
- Arduino (compatible board)
- Liquid Crystal Display (I2C)
- Current Sensor
- Voltage Sensor
- Relays (up to 4)
- Buttons (Up/Down for adjusting setpoint)

## Wiring Setup

| **Component**     | **Arduino Pin** |
|-------------------|-----------------|
| **Current Sensor** |                 |
| VCC               | VCC             |
| GND               | GND             |
| Data              | A2              |
| **Voltage Sensor** |                 |
| VCC               | VCC             |
| GND               | GND             |
| Data              | A3              |
| **Button Up**      |                 |
| IN                | A0              |
| OUT               | GND             |
| **Button Down**    |                 |
| IN                | A1              |
| OUT               | GND             |
| **Relay Module**   |                 |
| GND               | GND             |
| VCC               | VCC             |
| Relay 1           | 6               |
| Relay 2           | 5               |
| Relay 3           | 4               |
| Relay 4           | 3               |

## Features

1. **Current and Voltage Monitoring**: 
   - Reads current and voltage values from sensors.
   - Displays the readings on an LCD (I2C).
   
2. **Setpoint Control**:
   - Adjust the power threshold (setpoint) using the Up and Down buttons.
   - Setpoint is stored in EEPROM to maintain values between power cycles.

3. **Relay Control**:
   - The relays are triggered based on power consumption relative to the setpoint.
   - Four relays can be controlled, and the number of active relays depends on how close the power consumption is to the setpoint.

4. **Calibration**:
   - The system uses predefined zero points for current and voltage.
   - You can modify these zero points in the code as needed.

## Code Overview

### Pin Definitions
- **Relay Pins**: `pin_relay1`, `pin_relay2`, `pin_relay3`, `pin_relay4`
- **Button Pins**: `pin_up` (for increasing setpoint), `pin_down` (for decreasing setpoint)
- **Sensor Pins**: `pin_arus` (current sensor), `pin_tegangan` (voltage sensor)
  
### Relay Control
The relays are controlled based on the value of `count`:
- `count == 0`: All relays are off.
- `count == 1`: Relay 1 is on.
- `count == 2`: Relay 1 and Relay 2 are on.
- `count == 3`: Relay 1, Relay 2, and Relay 3 are on.
- `count == 4`: All relays are on.

### Power Calculation
The power consumption is calculated by multiplying the current (`arus`) and voltage (`tegangan`):
```cpp
daya = arus * tegangan;
```

## Voltage and Current Measurement

- get_voltage(): Reads and calculates the voltage from the sensor.
- get_current(): Reads and calculates the current from the sensor.

## Installation

1. Clone the project repository.
2. Copy the necessary libraries to your Arduino libraries folder (LiquidCrystal_I2C.h, EEPROM.h).
3. Upload the code to your Arduino board.
4. Wire the components according to the wiring setup above.

## Usage

1. Set the Setpoint:
    - Use the Up/Down buttons to adjust the power setpoint.
    -  The setpoint value is displayed on the LCD.
    - The system will automatically save the setpoint to EEPROM.

2. Monitor Power:
    - The LCD displays the current (I), voltage (V), active relay level (L), power consumption (P), and setpoint (SP).

3. Relay Control:
    - The relays will switch on/off based on the current power consumption and setpoint.

## License

- This project is licensed under the MIT License. Feel free to modify and share it.
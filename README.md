# Current Sensor Limiter (ACS712)

This project implements a current sensor limiter using an Arduino, allowing for the monitoring of current and voltage with options to lock or unlock the system based on current thresholds.

## Setup Instructions

### 1. Copy Libraries

Copy all the files in the `lib` folder and paste them into your `Documents > Arduino > libraries` folder.

### 2. Calibration Process

Follow this [tutorial](https://www.youtube.com/watch?v=ceaQiK_B1sc) for the calibration process of the current sensor. It is important to complete this step before running the system.

### 3. Program Files

The project consists of two main programs:

- **Lock**: Found in the `arduino` folder.
- **No Lock**: Found in the `arduino_nolock` folder.

### 4. Arduino Wiring

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
| **Button Up**      |                 |
| IN                 | A0              |
| OUT                | GND             |
| **Button Down**    |                 |
| IN                 | A1              |
| OUT                | GND             |
| **Relay Module**   |                 |
| GND                | GND             |
| VCC                | VCC             |
| 1                  | 6               |
| 2                  | 5               |
| 3                  | 4               |
| 4                  | 3               |

### Notes:

- Ensure all wiring is correctly connected as per the table above.
- The lock and no-lock functionalities depend on the current sensor readings. Lock mode prevents overcurrent conditions, while no-lock mode simply monitors the readings.

## License

This project is open-source and licensed under the MIT License.

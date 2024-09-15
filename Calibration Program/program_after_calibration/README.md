# Post-Calibration Program for Current/Voltage Sensor

This program is used after performing sensor calibration to measure the current flowing through a load. The zero-point reading obtained during the calibration process is used as a reference to calculate the actual current based on the sensor's ADC values.

## Overview

The program continuously reads the ADC values from the sensor and converts them into current measurements using a polynomial equation. The zero-point value is hardcoded in this program based on previous calibration results.

## Components and Pin Configuration

- **Sensor**: The sensor is connected to **A0** (can be changed by modifying `#define pin_ADC`).
- **Serial Monitor**: Displays the ADC readings and calculated current values.

### Pin Definitions

- `#define pin_ADC A0` — This defines the pin where the sensor is connected (default is A0).

## How the Program Works

1. **Zero-point Initialization**:

   - The zero-point value is hardcoded as `512` in the program. This value is obtained from a prior calibration process when no load was applied.

   ```cpp
   zero_point = 512;
   ```

2. Continuous Monitoring:

- The program continuously reads the ADC values and computes the current by using the polynomial equation:

```cpp
// y = 0.028 * x - 0.0372
double current = (0.028 * nilai_adc_beban) - 0.0372;

```

- The results are displayed in the Serial Monitor every 200ms.

## Code Structure

### Setup

In the setup() function, the program initializes the zero-point:

```cpp
zero_point = 512;
```

This value is based on the calibration done in the previous step. It represents the sensor's ADC value when no load is applied.

## Load Measurement

The loop() continuously monitors the sensor readings and computes the current based on the ADC values:

```cpp
double nilai_adc_beban = get_adc(pin_ADC);
double current = (0.028 * nilai_adc_beban) - 0.0372;

```

The current is then printed to the Serial Monitor.

### Example Output

- Without Load:

```yaml
NILAI ADC TANPA BEBAN: 512
NILAI ARUS: 0.00 A
```

- With Load:

```yaml
NILAI ADC DENGAN BEBAN: 300
NILAI ARUS: 7.84 A
```

## How to Use

1. Connect the Sensor to pin A0 (or adjust pin_ADC if using a different pin).
2. Upload the Code to your Arduino.
3. Open the Serial Monitor at a baud rate of 9600.
4. Observe the current readings as you apply or remove load.

## Customization

- Change the Input Pin: If your sensor is connected to a different pin, update the following line:

```cpp
#define pin_ADC A0

```

- Adjust the Polynomial Equation: If the calibration provides a different polynomial equation, update the formula in the loop() function:

```cpp
double current = (0.028 * nilai_adc_beban) - 0.0372;

```

## License

This project is open-source and available under the MIT License.

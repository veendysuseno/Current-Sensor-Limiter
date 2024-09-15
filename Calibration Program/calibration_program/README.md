# Calibration Program for Current/Voltage Sensor

This program is designed to calibrate the sensor connected to an analog pin by measuring the zero-point reading when no load is applied. It will also display the ADC values when the load is applied to help you fine-tune the sensor readings.

## Overview

The program performs the following functions:

1. **Zero-point Calibration**: It captures the ADC value when no load is applied, which is necessary to get an accurate sensor reading.
2. **Load Measurement**: After calibration, the program reads the ADC value when a load is applied and prints it to the Serial Monitor.

## Components and Pin Configuration

- **Sensor**: The sensor should be connected to **A0** (adjustable by changing the `pin_ADC` in the code).
- **Serial Monitor**: Used to display the calibration and load values.

### Pin Definitions

- `#define pin_ADC A0` — This defines the pin where the sensor is connected (A0 by default).

## How the Program Works

1. **Initial Calibration**:

   - When the program starts, it prompts the user to ensure the load is turned **off** before proceeding with calibration.
   - It then reads the **zero-point** value, which is the baseline ADC reading with no load applied.

2. **Continuous Monitoring**:
   - Once calibrated, the program continuously reads the ADC value from the sensor and subtracts the zero-point value to determine the ADC reading for the load.
   - The result is printed to the Serial Monitor every 200ms.

## Code Structure

### Calibration

In the `setup()` function, the program reads the **zero-point** value:

```cpp
zero_point = analogRead(pin_ADC);
```

- This value is stored and used to offset the readings when the load is applied.

## Load Measurement

In the loop(), the program uses the get_adc() function to continuously calculate the ADC value with the load applied. This is done by subtracting the zero-point from the current ADC value:

```cpp
int RawCurrentIn = analogRead(ampPin) - zero_point;
```

The results are then averaged over a sample duration and printed.

## Example Output

- Without Load:

```vbnet
PASTIKAN BEBAN DALAM KONDISI OFF, SEBELUM KALIBRASI
NILAI ADC TANPA BEBAN: 512
```

- With Load:

```yaml
NILAI ADC DENGAN BEBAN: 300
```

## How to Use

1. Connect the Sensor to pin A0 (or the pin of your choice, ensuring to update the #define pin_ADC accordingly).
2. Upload the Code to your Arduino.
3. Open the Serial Monitor at a baud rate of 9600.
4. Ensure the load is off and observe the calibration message and zero-point reading.
5. Once the calibration is done, apply a load and observe the updated ADC values.

## Customization

- Change the Input Pin: If your sensor is connected to a different pin, update the following line:

```cpp
#define pin_ADC A0
```

- Adjust the Sampling Duration: You can change the sampling period for better accuracy by modifying the sampleDuration in the get_adc() function.

## License

This project is open-source and available under the MIT License.

# Digital Scale Using Load Cell (HX711 + Arduino)

This repository contains two C++ files for building and operating a digital scale using a load cell and the HX711 amplifier module with Arduino.

## Repository Structure

- `scale_calibration.cpp`: Code used to calibrate the scale. It helps determine the calibration factor that converts raw readings to weight in grams.
- `balanca.cpp`: Main code for regular use of the scale after calibration. It continuously reads and displays the weight.

## Requirements

- Arduino Uno (or compatible)
- Load cell
- HX711 module
- HX711 library (available via Arduino Library Manager)
- 5V power supply or USB connection

## How to Use

1. Connect the load cell to the HX711 module and then to the Arduino following a typical wiring diagram.
2. Upload `scale_calibration.cpp` to the Arduino.
3. Use the serial monitor to obtain the calibration factor.
4. Replace the placeholder value in `balanca.cpp` with the obtained calibration factor.
5. Upload `balanca.cpp` to the Arduino to use the scale normally.

## Notes

- The system averages multiple readings for improved stability.
- The calibration code displays raw values and uses a known reference weight.
- Calibration factors may vary depending on the load cell, power supply, and mechanical setup.

## Reference

This project is based on the tutorial from Random Nerd Tutorials:  
[Build a Digital Scale with Arduino and HX711](https://randomnerdtutorials.com/arduino-load-cell-hx711/)

---


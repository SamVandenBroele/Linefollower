# Datasheets

This folder contains the available datasheets and technical documentation
for the components used in the Line Following Robot project.

## Components

- STM32F103C8T6 Microcontroller
- TB6612FNG Dual Motor Driver
- TCRT5000 Reflective Optical Sensor Module
- HM-10 Bluetooth Module
- GA12-N20 6V 300 RPM DC Gear Motor
- DC-DC Buck Converter
- 24LC256 I²C EEPROM

## Notes

### TCRT5000 Sensor Module
The TCRT5000 sensors used in this project are sensor modules containing
a TCRT5000 reflective optical sensor with additional onboard circuitry,
including an LM393 comparator.

No official datasheet for the complete sensor module was available.
Therefore, the manufacturer's datasheet of the TCRT5000 sensor itself
is included as a technical reference.

### GA12-N20 6V 300 RPM Motor
No official manufacturer datasheet was available for the exact
GA12-N20 6V 300 RPM motor used in this project.

The included GA12-N20 document is therefore used as a general technical
reference for the motor family and does not describe the exact 300 RPM
variant.

### DC-DC Buck Converter

The DC-DC buck converter used in this project is a mini step-down module intended to convert the battery voltage to 5 V.
The module is specified for an input voltage of approximately 4.5–24 V and provides selectable output voltages, including 5 V.
No official manufacturer datasheet was available for the exact DC-DC buck converter module used in this project. Therefore, no datasheet for the complete module is included in this folder.

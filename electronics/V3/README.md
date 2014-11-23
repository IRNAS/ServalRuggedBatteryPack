Serval Rugged Battery Pack electronics V3 - pre-release
======================

![ServalRuggedBatteryPack](https://raw.github.com/IRNAS/ServalRuggedBatteryPack/master/electronics/V3/ServalRuggedBatteryPackV3.png)

This version of the battery pack improves on the previous design to allow for much faster charging, enabling the operation under more intermittent power supply conditions, such as winder periods when solar power is used.

Currently published version is for use in debugging process only and should not yet be used in real-world!

### System design
The system is designed in three major sections, Input and charging implementing LiFePO4 cell charging from 5-30V DC sources, Controller implementing the system monitoring functions and battery over-discharge protection with UART connectivity for measurement collection and Output stage with 5V regulated USB output for powering routers and other USB devices.

#### Input and charging
Charging is based on [TI BQ24650](http://www.ti.com/product/bq24650) Solar charge controller with MPPT functionality following the proposed reference design [bq24650EVM](http://www.ti.com/lit/ug/sluu444a/sluu444a.pdf) modified for LiFePO4 charging per [BQ24650 LiFePO4 manual](http://www.ti.com/lit/an/slua565/slua565.pdf). Additionally the MPPT set control is implemented via a digital potentiometer, so the Controller can dynamically change it based on the input voltage measurement. Current sense resistor is additionally monitored using (INA219)[http://www.ti.com/lit/ds/symlink/ina219.pdf], so the Controller can monitor charging and discharging accurately.

#### Controller
Controller is (MSP430G2553)[http://www.ti.com/product/msp430g2553] programmed in (Energia)[http://energia.nu] environment. It monitors the voltages and charging state and protects the battery from over-discharge, controls the output stage and an additional power channel for extra outputs.

#### Output stage
The output stage features (TPS61032)[http://www.ti.com/product/tps61032] high efficiency step-up regulator with 5V fixed output and two USB ports. One facing toward the inside of the device for powering a router for example within the case and an external one facing the connection side of the board with additional resistor dividers to allow charging of mobile devices.

### Known major bugs

Input and charging stage does not operate correctly. While all operating conditions are met and charging phase starts, the BQ24650 IC significantly heats up even with moderately low charging currents of about 500mA and after a few seconds falls into thermal shutdown. As external switching elements are used, there should be no power path going through the IC, however there must be one and the source of this error has not yet been discovered. All the operating conditions specified in the datasheet are met.

### Known minor bugs / ideas for improvement

High thermal conductivity of T1 pin 3 connected to P_GND may cause this pin not to be properly soldered during reflow, this must be kept in mind when assembling.

On rare occasion caused by human factor during measurements, both MOSFETs may turn on and cause a short circuit. While this is unlikely to occur during normal operation, the input fuse must be chosen such, that transistors are not damaged. A secondary fuse for the battery may also be a good idea.
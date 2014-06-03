Serval Rugged Battery Pack electronics V1
======================

![ServalRuggedBatteryPack](https://raw.github.com/IRNAS/ServalRuggedBatteryPack/master/electronics/V1/ServalRuggedBatteryPack-V1-sch-top.png)

This electronics design is a step in development and is not fully optimized for the end use-case. It features two input stages, a 5V input with a charge controller in parallel with a step-down stage in CV/CC mode for charging from voltage inputs of up to 30V.

Batteries used must be single cell LiFePO4.

The controller stage features a MSP430G2452 microcontroller and an INA219 current measurement IC to monitor the battery state and perform battery protection functions, controlling the load via a MOSFET. The two 4 pin output block enable an UART connection to the outside world and programming.

Load output voltage is set resistor network with jumper selection for 5V or 12V output, mind using the appropriate output connector.

### Known bugs

R29 pull-up for the MCU is connected to the VCC (ACU_safe) after the cut-off MOSFET, resulting in an MCU suicide. Connect the resistor to VCC (V_chg) directly. 
C16 must have sufficiently small ESR, add a capacitor in parallel if insufficient charge current is observed.
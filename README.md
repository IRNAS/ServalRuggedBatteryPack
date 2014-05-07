ServalRuggedBatteryPack
=======================

Serval Rugged Battery Pack is designed to be the universal battery supply system for wireless equipment in any situation. Let that be a rescue operation in New Zealand, every-day deployment in Africa or a remote location in Europe, all sharing the same lack of electrical power for communication equipment. Together with [Serval project](http://www.servalproject.org/)  we are creating an universal power solution for [Serval Mesh extender](http://developer.servalproject.org/dokuwiki/doku.php?id=content:meshextender:main_page)  and general use in community wireless networks.

## Early prototpe
Designed to house 2pcs LiFePO4 12Ah batteries and control electronics. Implements most of the described features, however supports only up to 1A charging current, making the usage of such a system rather limited. Improvements are on the way.

Assembly parts:

![SolRouterSer](https://raw.github.com/IRNAS/SolRouterSer/master/photos/SRBP-Proto-2.jpg)

Inside the 3D printed case:

![SolRouterSer](https://raw.github.com/IRNAS/SolRouterSer/master/photos/SRBP-Proto-3.jpg)

In action with Serval Mesh Extender:

![SolRouterSer](https://raw.github.com/IRNAS/SolRouterSer/master/photos/SRBP-Proto-1.jpg)
![SolRouterSer](https://raw.github.com/IRNAS/SolRouterSer/master/photos/SRBP-Proto-4.jpg)

## Development goals
 * Supply power for the wireless device (5V USB or 12V)
 * Enough juice for days of operation
 * Charge it from just about anything
 * Make it hackable and reusable
 * Support real-time monitoring of the system
 
## Usage scenarios

### Serval Mesh Extender
[Serval Mesh extender](http://developer.servalproject.org/dokuwiki/doku.php?id=content:meshextender:main_page) is based on Openwrt devices, currently using Tp-Link MR3020 routers that on their own have a consumption of about 1W, [consumption data](http://developer.servalproject.org/dokuwiki/doku.php?id=content:meshextender:power_consumption_table). The external radio RFD900 peaks up to 1W as well. The desired operation on a single charge is multiple of days.

Maximum consumption of the setup is 2W, for 1 day operation that requires 48Wh.

### wlan slovenija network node
[wlan slovenija](https://wlan-si.net/)  is an open wireless mesh network in Slovenia, with some nodes deployed to temporary events without mains power available. Typical nodes are MR3020 with average consumption of 1W using 5V USB input and WR741ND with average consumption of 1W are 9-12V input.

Maximum consumption for the setup is 1W, more then 2 day of operation is desired.

## Battery technology and tests
The choice for safety, performance and price reasons is LiFePO4, however the design should be hackable to support Li-po as well.

Testing with two WH08Ah LiFePO4 cells in parallel powered MR3020 for 65h with average 230mA drain at battery voltage, average of 3.15V. The delivered power to the voltage regulator was about 47Wh, the actual device somewhere in the 42Wh range.

The upgrade to two 12Ah cells in parallel should deliver about 70Wh.

## Charging
The design goal is to enable fast charging of the battery pack allowed with LiFePO4 to reduce the time as much as possible.

Useful/available charging sources:
 * USB phone charger (5V/1A)
 * TP-Link wr741nd adapter (9V/600mA)
 * Car DC socket (12V/5A)
 * Motorcycle alternator (6V-12V/5A+)
 * Wind turbine (10W+) ???
 * DIY hack generator ?
 * [Hand crank generator](http://wiki.laptop.org/go/Peripherals/Hand_Crank) (15V/1.5A)
 * Solar cell (various)
 
The power quality of sources in the wild may vary, the input should have a wide range, up to 30V with protected to 400V, be AC/DC compatible, so wrong polarity can not be the issue. Charging should occur from any connected source, no matter what its capabilities are.

## Capacity
The device should operate from a single cell to simplify the design, enable easier operation cycles and avoid problems due to cell management. The capacity should depend on teh connected batteries, but generally should be in the range of 12Ah-48Ah, depending on the number of cells connected. This directly affect charging time.

## Monitoring
There should be a low-power processor on board that enables the collection of usage information, performs the battery protection function and enables extensive real-time information if so desired.

Parameters to be observed:
 * Input voltage
 * Output voltage
 * Battery voltage
 * Battery charge/discharge current
 * Temperature
 * Ambient light
 
The following features should be implemented in software:
 * Battery cycle count
 * Battery undervoltage protection
 * Load management
 * Communication with the external device
 
## Electronics
The brains should be MSP430G2452 compatible with [Energia environment](http://energia.nu), because of internal VCC measurement feature, temperature sensor, low power consumption nad affordable cost.

The charging part should ideally be built around BQ24560 IC from TI.

The output step-up part should be built with low-cost step-up devices. Pre-selectable config for 12V or 5V output.

Input connections:
 * micro/mini USB
 * DC jack
 * terminal block (push connect style, no screwdriver required)
 
Output connections:
 * 5V USB A
 * terminal block (push connect style, no screwdriver required)
 
 Allow units to be daisy-chained.
 
### License
![alt text](http://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png "CC-NC-SA")

This work is licensed under [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License] (http://creativecommons.org/licenses/by-nc-sa/4.0/deed.en_US)


 
 

 
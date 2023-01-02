# JaguarLib
Atari Jaguar input library for Arduino

For Arduino Leonard/Pro Micro (5V 16MHz)

## How to use
Jaguar controllers works with 5V so I recommend to use a 5V Arduino.

This library requires [DigitalIO](https://github.com/greiman/DigitalIO).

I recommend the usage of [SukkoPera's fork of DigitalIO](https://github.com/SukkoPera/DigitalIO) as it supports a few more platforms.

Install the library on your Arduino library folder. Also install the required dependencies.

Then open any of the provided [sketches](sketches).


### Jaguar port pins


| Jaguar  | Description |
|---------|-------------|
| 1       | J3_J4       |
| 2       | J2_J5       |
| 3       | J1_J6       |
| 4       | J0_J7       |
| 5       |             | 
| 6       | B0_B2       |
| 7       | VCC/POWER   |
| 8       |             |
| 9       | GROUND      |
| 10      | B1_B3       |
| 11      | J11_J15     |
| 12      | J10_J14     |
| 13      | J9_J13_     |
| 14      | J8_J12      |
| 15      |             |

## Credits

Darthcloud's [BlueRetro Jaguar](https://github.com/darthcloud/BlueRetro/wiki/Jaguar-interface) documentation.

It uses the [DigitalIO](https://github.com/greiman/DigitalIO) from greiman.

I recommend the usage of [SukkoPera's fork of DigitalIO](https://github.com/SukkoPera/DigitalIO) as it supports a few more platforms.

Special thanks to [misteraddons](https://github.com/misteraddons).

## Warning
Code and wiring directions are provided to you 'as is' and without any warranties. Use at your own risk.
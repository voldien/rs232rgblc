# RS232RGBLEDController #
-----

The *RS232RGBLEDController* is extension PCB board for motherboard. Where its connected via the *com port* and the 12V rail. Where a LED strip can be either connected via the RGB headers or the 12V+, GND and data pin. Where it RGB has dedicated pin for RGB and GND. Whereas the other one uses SPI to communicated with LED strip. 

Remark that the schematic and PCB layout and the software driver are still work in progress and has yet not been tested!

## Motivation ##
----
The project was created in order to take advantages of the *com port* commonly found on motherboard, which is seldom used by the majority of desktop user.

The board is intended to add support for a cheap alternative for RGB lightning for desktop computers.

## Installation ##
------
The following section covers how the install the driver on the destkop in order to communicate with the extension board from *userspace*. Where the library for interfacing with the board will be installed along with a command line program, which can alter the behavior of the board in runtime.

## Unix ##
The driver for *UNIX* system can be installed as followed:
```
make 
make install
```


## Examples ##
-----

## License ##
---
The source code for this project is licensed under the GPL+3 License - see the [LICENSE](LICENSE) file for details.
The hardware design for this project is under the OSHW License - See [](LICENSE) for more detials.

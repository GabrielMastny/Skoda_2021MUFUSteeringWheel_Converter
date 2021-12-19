# Škoda converter for 2021 steeringwheel with multifunction
 
 <img src="https://lingtalfi.com/services/pngtext?color=cc0000&size=10&text=By+installing+the+converter%2C+you+can+paralyze+or+seriously+damage+the+vehicle%27s+communication+network+in+the+event+of+unprofessional+intervention+and+thus+deactivate+it.+You+perform+the+tasks+at+your+own+risk%21">
 
 

* Tested on Fabia III MY2015 but should work also on other models. 
* Convertor is conected paralelly to the BUS, in a case converter would stop working, BUS will be unaffected.  
* By connecting converter to switched fuse, converter will be active only if car will be turned on by moveing key to position 1 or by pressing start button. In that case converter won't drain any power if car is switched off. Also if in any case there should be any electrical fault on convertor only fuse will be blown and car should remain unharmed.
* Convertor doesn't stop any signals it just uses fact, that car will trow away all unsupported signals. Converter after recieving usupported signal will simply send new signal that is by car understood.
* At the time of writing manual material for converter costs little bit over 600 Czech Koruna (20+ pound)


## material

  * Arduino nano - cheaper clone should be enough  
  * MCP2515
  * positive voltage regulator L78S05CV 
  * optionaly regulator cooler
  * fuse terminal VAG N90684401
  * grounding eye size M6
  * 16x pin female VAG N90764701; 7x arduino, 7x mcp2511, 2x 2-pole terminal
  * 4x pin male; 2x 2-pole terminal, 2x CAN
  * 2-pole terminal male VAG 4E0972575
  * 2-pole terminal female VAG 4B0971832
  * FLRY power harness, 2x 1m, diameter 0,5mm for power management of converter
  * FLRY data harnes for diameter 0,35mm; 0,5 m for connecting arduino and mcp2515, 2x 1m for CAN
  


## connection

[![](/Images/Converter_Schema.png)]()

### ARDUINO + MCP2515
Connection Arduino and MCP2515 is pretty easy, who doesn't want to create its own connecting harness it is possible to buy premade connection harnes together with arduino, it wasn't suitable for me as it felt it doesn grip arduinos pins good eough for me, so i created my own harness by using two **N90764701** pins and 6cm of cable with diameter 0,35 mm and shrink foil to make sure that pins won't touch. 

<p align="center">
<img src="https://github.com/GabrielMastny/Skoda_2021MUFUSteeringWheel_Converter/blob/main/Images/Pins2.png" width="250" height="250">
<img src="https://github.com/GabrielMastny/Skoda_2021MUFUSteeringWheel_Converter/blob/main/Images/pins.png" width="250" height="250">
</p>

### positive voltage regulator L78S05CV 

For charging both Arduino and MCP2515 which work with 5V voltage is used voltage regulator **L78S05CV**, where by datasheet:
1) left leg is for car's power line (12V), cca 1M of ideally red power harness with fuse terminal **N90684401**. Aviable positions in fuse box will probably wary for different models, suitable possition can be found in [owner's manual](https://manual.skoda-auto.com/004/en-com/Models) in section fuse box
2) middle leg is ground, for that is used grounding point on steeringwheel column. cca 1m of ideally black power harness with grounding eye size m6.
3) right leg is output 5V for Arduino and MCP2515, 2x cca 6cm of ideally red power harness with pin **N90764701**

### Connection to CAN BUS
probably in every model it will be CAN Komfort BUS.
For connecting to CAN it will help to make Y fork cable (credit [wirer](www.wirer.sk)), where as imput is used originac CAN cables and as output pair of cables one to be connected to the previous connection of CAN harness and second as harness to converter.

<p align="center">
<img src="https://github.com/GabrielMastny/Skoda_2021MUFUSteeringWheel_Converter/blob/main/Images/YConn.png" width="250" height="250">
<img src="https://github.com/GabrielMastny/Skoda_2021MUFUSteeringWheel_Converter/blob/main/Images/YConnector.png" width="600" height="250">
</p>

There are probbably two options how to connect to CAN BUS:
1) more proffesional and also more difficult is to make connection directly from BCM, which is hidden inside dashboard near driver's left knee, acces is from below where pedals are. For better manipulation with harnesess it is better to completelly remove BCM, than by workshop manual (not sure if this translation is correct, basically manual that has every technician in authorized skoda repairshops) you can find corect position wher CAN BUS pair is connected. Then you need to unpin them out by specialized tool (really small screwdriver is enough) and instead of them connect back output pair of Y fork connector.

<p align="center">
<img src="https://github.com/GabrielMastny/Skoda_2021MUFUSteeringWheel_Converter/blob/main/Images/YConnFabia.png" width="400" height="400">
</p>

2) Easier way is to connect to Can BUS branch that is used for board of infotainment, that can be located in glove box or hidden inside dashboard, in both cases you will need keys for infotainment removal. From board can be than obtained quadlock connector inside of it is located grey block where on position 6 and 12 is located pair of CAN BUS. Connection with Y fork connector is than similiar as with BCM.

<p align="center">
<img src="https://github.com/GabrielMastny/Skoda_2021MUFUSteeringWheel_Converter/blob/main/Images/QuadlockCANKomfort.png" width="250" height="250">
<img src="https://github.com/GabrielMastny/Skoda_2021MUFUSteeringWheel_Converter/blob/main/Images/QuadlockCANBlock.png" width="250" height="250">
</p>

## Software

### CAN and MUFU steeringWheel

packet of CAN BUS in general looks like this
| CAN_ID [HEX]| DLC | Byte 0-1 [HEX]| Byte 2-3 [HEX]| Byte 4-5 [HEX]| Byte 6-7 [HEX]|
| ----------- | --- |:-------------:| :------------:| :------------:| :------------:|
| 0x5BF       |  8  | 06            | 00            | 0F            | 13            |

where  
CAN_ID: is unique identification of sender in our case steeringwheel.  
DLC: says how big data payload is in bytes.
Byte 0-n: contains data, which needs to be sent to whoever listens to it.

after listening to (CAN_ID 0x5BF) packets of old and new steeringwheel i made two tables:

Functions of old and new steeringwheel
| Funkce                   | Byte 0-1 [HEX]| Byte 2-3 [HEX]| Byte 4-5 [HEX]| Byte 6-7 [HEX]|
| ------------------------ |:-------------:| :------------:| :------------:| :------------:|
| menu wheel scroll up     | 06            | 00            | 0F            | 13            |
| menu wheel scroll down   | 06            | 00            | 01            | 13            |
| menu wheel push          | 07            | 00            | 01            | 13            |
| enter to menu            | 08            | 00            | 01            | 13            |
| volume wheel scroll up   | 12            | 00            | 01            | 13            |
| volume wheel scroll down | 12            | 00            | 0F            | 13            |
| volume wheel push        | 13            | 00            | 01            | 13            |
| source radio/bluetooth/usb| 14            | 00            | 01            | 13            |
| next station/music       | 15            | 00            | 01            | 13            |
| previous station/music   | 16            | 00            | 01            | 13            |
| voice control            | 19            | 00            | 01            | 13            |
| phone                    | 1D            | 00            | 01            | 13            |

Functions of new steeringwheel
| Funkce                   | Byte 0-1 [HEX]| Byte 2-3 [HEX]| Byte 4-5 [HEX]| Byte 6-7 [HEX]|
| ------------------------ |:-------------:| :------------:| :------------:| :------------:|
|  enter to menu           | 02            | 00            | 01            | A3            |
| menu zpet                | 03            | 00            | 01            | A3            |
| vyhřívání volantu        | 25            | 00            | 01            | A3            |
| travel assist            | 74            | 00            | 01            | A3            |
| asistenční systémy       | 0C            | 00            | 01            | A3            |

where 
Byte 0-1 identifies button on steeringwheel 
Byte 2-3 probalby not used 
Byte 4-5 defines if wheel scrolls up or down 01/0F or for how long is button pushed 01-06  
Byte 6-7 i don't have any idea for what are used those ones but old steeringwheel was sending always value 13 and new one always value A3.  

### Tools for uploading code to Arduino

* Arduino IDE [ARDUINO IDE](https://www.arduino.cc/en/software) download and install; It can edit and upload source code to arduino
* [library](https://github.com/atc1441/arduino-mcp2515/archive/master.zip)for MCP2515, leave file zipped
* USB Cable mini, it should be packed together with arduino
* [source code for converter](https://github.com/GabrielMastny/Skoda_2021MUFUSteeringWheel_Converter/blob/main/CAN_Converter_MUFU_Skoda.ino)

### Preparation of IDE
With first startup it is needed to set several things

1) in Tools > Board: choose type of arduino, in this case arduino nano
2) in Tools > Processor: choose processor on board if you have clone then select option 2 Atmega328P(old bootloader), if original one then first option
3) in Tools > Port: choose port to be able select correct one you need to have arduino connected to computer via usb (usualy COMN where N is number)
4) in Sketch > Include Library > Add .ZIP library: is needed to upload [library](https://github.com/atc1441/arduino-mcp2515/archive/master.zip) for MCP2515

### code

in code you will be probably interested only in this part, where you can selcet remmaping of buttons you want. values should be in format 0xnn where n is in hexadecimal range so 0-9 or A-F

as a bonus you can disable start-stop function..

```
//////////////////////////////////////////////////////
//              Set your mapping                    //
                                                    //
const uint8_t user_EnterMenu           = 0x08;      // value 0x08 represents old signal for entering to menu
const uint8_t user_MenuBack            = 0x00;      //
const uint8_t user_heatedSteeringWheel = 0x00;      //
const uint8_t user_travelAssist        = 0x00;      //
const uint8_t user_assistSystems       = 0x1D;      // value 0x1D represents phone menu
// bonus - if you want to disable startstop         //
// change false for true on line below              //
bool disableStartStop = false;                      //
//////////////////////////////////////////////////////
// Do not touch anything below, if you are not sure // 
// what are you doing                               //
//  //  //  //  //  //  //  // // // // // // // // //
```
if you choose to not set anything, by default there will be active remmaping of menu button and instead of assist system button will be remmaped to phone menu.

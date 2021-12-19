# Škoda převodník pro 2021 volant s multifunkcí
 
 <img src="https://lingtalfi.com/services/pngtext?color=cc0000&size=10&text=Instalac%C3%AD+p%C5%99evodn%C3%ADku+m%C5%AF%C5%BEete+p%C5%99i+neodborn%C3%A9m+z%C3%A1sahu+ochromit+p%C5%99%C3%ADpadn%C4%9B+v%C3%A1%C5%BEn%C4%9B+po%C5%A1kodit+komunika%C4%8Dn%C3%AD+s%C3%AD%C5%A5+vozidla+a+t%C3%ADm+ho+vy%C5%99adit+z+provozu.+%C3%9Akony+d%C4%9Bl%C3%A1te+na+vlastn%C3%AD+nebezpe%C4%8D%C3%AD%21">
 
 

* Testováno na vozidle Fabia III MY2015, mělo by podporovat i další modely 
* Převodník se napojuje paralelně na sběrnici, v případě, že by přestal z nějakého důvodu fungovat, sběrnice bude stále funkční.  
* Připojením převodníku na spínanou pojistku bude převodník aktivní pouze pokud je elektronika vozidla zaplá (stisknutím start tlačítka, nebo otočením klíčku do polohy 1), tedy nebude odebírat proud pokud je auto vyplé. Zárovň pokud by mělo dojít k nějaké elektrické závadě schytáto pojistka a ne celá palubní síť.
* Převodník, žádné signály nezadržuje, využívá faktu, že auto některým signálům nového volantu nerozumí, tak je jednoduše zahodí. Převodník po poslechnutí nepodporovaného signálu na základě nastavení, které si uživatel určí, vysílá další signál, kterému by auto už mělo rozumnět.
* V době psaní návodu vychází převodník na něco málo nad 600Kč za materiál.


## materiál

  * [Arduino uno](https://www.gme.cz/100-kompatibilni-klon-arduino-nano-v3-0-r3-original-chip) - stačí levnější klon  
  * [MCP2515](https://www.gme.cz/modul-mcp2515-can-bus-prevodnik-na-spi)
  * [stabilizátor L78S05CV](https://www.gme.cz/stabilizator-pevneho-napeti-stmicroelectronics-78s05) 
  * [chladič stabilizátoru](https://www.gme.cz/do1a-v)
  * [pojistková svorka](https://www.autokabel.cz/kontakt-jpt-28-pro%20vodic-do-1mm-bez-tesneni?search=jpt2801) VAG N90684401
  * [uzemňovací oko](https://www.autokabel.cz/kabelove-oko-m6-modre-smrstovaci?search=KOS06B) velikost oka M6
  * 16x [propojovaci pin samice](https://www.autokabel.cz/dutinka-micro-quadlock-vodic-do-075-mm?search=MQF075) VAG N90764701; 7x arduino, 7x mcp2511, 2x 2-polová svorkovnice kdo se nechce dělat s kabelama sám může si s arduinem koupit propojovací káblíky
  * 4x [propojovaci pin samec](https://www.autokabel.cz/962886-1?search=MQM075) 2x 2-polová svorkovnice, 2x CAN
  * [Svorkovnice 2-pólová samec](https://www.skoda-dily.cz/nahradni-dil/8w0972575-svorkovnice-2-polova-29804.html) VAG 4E0972575
  * [Svorkovnice 2-pólová samice](https://www.skoda-dily.cz/nahradni-dil/8w0971832-svorkovnice-2-polova-23310.html) VAG 4B0971832
  * kabeláž, napájení [červená](https://www.autokabel.cz/autovodic-flry-b-050-mm-cerny?search=FLRY050RD) a [černá](https://www.autokabel.cz/autovodic-flry-b-050-mm-cerny?search=FLRY050BK) s 0,5 mm cca 1m při uložení v blízkosti řídící jednotky.
  * [kabeláž](https://www.autokabel.cz/autovodic-flry-b-035-mm-cerny?search=FLRY035BK) s průměrem 0,35mm na propojení arduina s MCP + Propojení CAN, cca 0,5 m na propojky, 2x 1m pro can ideálně různé barvy
  


## zapojení

[![](/Images/Converter_Schema.png)]()

### ARDUINO + MCP2515

Propojení Arduina s Arduina s MCP2515 je celkem přímočaré, kdo si nechce dělat práci s výrobou propojovacích káblíků, může si koupit už předpřipravené, zdálo se mi, že nedrží zapojení tak jak bych si přál, tak jsem si vytvořil vlastní za použití dvou pinů **N90764701**, cca 6cm kabelu s průměrem 0,35 a smrštťovačky ať se piny nedotýkají  

<p align="center">
<img src="https://github.com/GabrielMastny/Skoda_2021MUFUSteeringWheel_Converter/blob/main/Images/Pins2.png" width="250" height="250">
<img src="https://github.com/GabrielMastny/Skoda_2021MUFUSteeringWheel_Converter/blob/main/Images/pins.png" width="250" height="250">
</p>

### Stabilizátor napětí L78S05CV

Pro napájení Arduina i MCP2515, které operují na napětí 5V je použit stabilizátor napětí **L78S05CV**, kde podle schématu je:
1) levá nožička určená pro připojení do palubní síťe vozidla, cca 1m červeného kabelu zakončený pojistkovou svorkou **N90684401**, jakou využít pozici v pojistkové skříňce se pravděpodobně bude lišit u každého modelu, vhodná pozice lze dohledat v [návodu k obsluze](https://manual.skoda-auto.com/260/cs-CZ/Models) v sekci pojistky
2) středová nožička je zem, pro tu jsem použil zemnící bod za volantem. cca 1m černého kabelu zakončeného zemnícím **okem**
3) pravá nožička je výstup 5V pro Arduino a MCP2515, 2x cca 6cm červeného kabelu zakončeného pinem **N90764701**

### Připojení ke CAN sběrnici
Asi všude se bude jednat o sběrnici CAN Komfort.
Pro připojení ke CAN usnadní práci vytvoření tzv. Y rozdvojky (credit [wirer](www.wirer.sk)), kde se jako vstup použijí původní žíly CAN a zdvojeným výstupem je jedna žíla nahrazující původní zapojení a druhá určená pro převodník.

<p align="center">
<img src="https://github.com/GabrielMastny/Skoda_2021MUFUSteeringWheel_Converter/blob/main/Images/YConn.png" width="250" height="250">
<img src="https://github.com/GabrielMastny/Skoda_2021MUFUSteeringWheel_Converter/blob/main/Images/YConnector.png" width="600" height="250">
</p>


jsou asi dvě možnosti jak se napojit:
1) čistší ale zároveň složitá a to vytáhnout si CAN přímo z řídící jednotky, která je utopená v palubovce u levého kolena řidiče, přístup k ní je zespodu od pedálů, pro lepší manipulaci se svazkem je asi lepší řídící jednotku uplně vyjmout, pak podle dílenské příručky vyhledat ve kterém ze svazků a na jaké pozici v konektoru se žíly nacházejí, ty jsou pak potřeba ze svazku vypíchnout a zapojit na vstup do vyrobené rozdvojky, na původní místo se zapojí výstup z rozdvojky.

<p align="center">
<img src="https://github.com/GabrielMastny/Skoda_2021MUFUSteeringWheel_Converter/blob/main/Images/YConnFabia.png" width="400" height="400">
</p>

2) Jednodušší cesta je napíchnout se na větev CANu určeného pro řídící jednotku rádia, ta se podle modelu auta může nacházet přihrádce u spolujezdce nebo v palubovce, v obou případech je potřeba mít [klíče](https://www.carmedia.cz/4carmedia-klice-pro-demontaz-autoradia-audi-ford-mercedes-vw/?gclid=Cj0KCQiAzfuNBhCGARIsAD1nu--b6_Hi5JH432YFagNTCw8h7Pf7Znbk-ny13aVhsnJL2brC5_pz2W8aAio2EALw_wcB) pro demonáž rádia pro vyjmutí jednotky. z jednotky je potřeba vytýhnout quadlock konektor a z něho šedou patici, kde se na pozicích 6 a 12 nachází vodiče pro CAN, následuje připojení Y rozdvojky stejně jako u řídící jednotky.

<p align="center">
<img src="https://github.com/GabrielMastny/Skoda_2021MUFUSteeringWheel_Converter/blob/main/Images/QuadlockCANKomfort.png" width="250" height="250">
<img src="https://github.com/GabrielMastny/Skoda_2021MUFUSteeringWheel_Converter/blob/main/Images/QuadlockCANBlock.png" width="250" height="250">
</p>



## Software

### CAN a multifunkční volant

Obecně paket Can protokolu vypadá nějak takto:
| CAN_ID [HEX]| DLC | Byte 0-1 [HEX]| Byte 2-3 [HEX]| Byte 4-5 [HEX]| Byte 6-7 [HEX]|
| ----------- | --- |:-------------:| :------------:| :------------:| :------------:|
| 0x5BF       |  8  | 06            | 00            | 0F            | 13            |

kde  
CAN_ID: je jedinečná identifikace odesílatele v našem případě volant.  
DLC: určuje velikost datové části paketu v bytech
Byte 0-n: obsahuje data, které odesílat chce předat komukoliv kdo chce poslouchat

po odposlechnutí paketů (CAN_ID 0x5BF) starého i nového volantu jsem sestavil dvě tabulky:

Funkce starého i nového volantu
| Funkce                   | Byte 0-1 [HEX]| Byte 2-3 [HEX]| Byte 4-5 [HEX]| Byte 6-7 [HEX]|
| ------------------------ |:-------------:| :------------:| :------------:| :------------:|
| kolečko menu nahoru      | 06            | 00            | 0F            | 13            |
| kolečko menu dolu        | 06            | 00            | 01            | 13            |
| kolečko stisk            | 07            | 00            | 01            | 13            |
| vstoupit do menu         | 08            | 00            | 01            | 13            |
| kolečko hlasitost nahoru | 12            | 00            | 01            | 13            |
| kolečko hlasitost dolu   | 12            | 00            | 0F            | 13            |
| kolečko hlasitost stisk  | 13            | 00            | 01            | 13            |
| zdroj radio/bluetooth/usb| 14            | 00            | 01            | 13            |
| další stanice/hudba      | 15            | 00            | 01            | 13            |
| předchozí stanice/hudba  | 16            | 00            | 01            | 13            |
| hlasové ovládání         | 19            | 00            | 01            | 13            |
| telefon                  | 1D            | 00            | 01            | 13            |

Funkce nového volantu
| Funkce                   | Byte 0-1 [HEX]| Byte 2-3 [HEX]| Byte 4-5 [HEX]| Byte 6-7 [HEX]|
| ------------------------ |:-------------:| :------------:| :------------:| :------------:|
| vstoupit do menu         | 02            | 00            | 01            | A3            |
| menu zpet                | 03            | 00            | 01            | A3            |
| vyhřívání volantu        | 25            | 00            | 01            | A3            |
| travel assist            | 74            | 00            | 01            | A3            |
| asistenční systémy       | 0C            | 00            | 01            | A3            |

kde  
Byte 0-1 určuje o jaké tlačítko se jedná  
Byte 2-3 se zřejmě nevyužívá  
Byte 4-5 u koleček určuje na jakou stranu se točí 01/0F, u tlačítek jak dlouho jsou stisklá 01-06  
Byte 6-7 absolutně netuším k čemu je, starý volant posílá vždy hodnotu 13 nový vždy A4, když jsem na test poslal jakoukoliv náhodnou hodnotu tak byl paket vždycky přijat a zpracován.  

### Nástroje pro nahrání kódu do Arduina

* Vývojářské prostředí [ARDUINO IDE](https://www.arduino.cc/en/software) stáhnout a nainstalovat; umožňuje editovat kód pro arduino a také ho nahrává do arduina
* [knihovna](https://github.com/atc1441/arduino-mcp2515/archive/master.zip) pro MCP2515, zip není potřeba rozbalovat
* USB kabel mini, měl by přijít společně s arduinem
* [kód pro převodník](https://github.com/GabrielMastny/Skoda_2021MUFUSteeringWheel_Converter/blob/main/CAN_Converter_MUFU_Skoda.ino)

### Příprava vývojářského prostředí

Při prvním spuštění bude potřeba nastavit několik věcí:
1) V Tools > Board: vybrat typ arduina, v tomto případě Arduino nano
2) V Tools > Processor: Vybrat procesor osazený na desce, pokud máte klon arduina tak vyberte druhou možnost Atmega328P(old bootloader), pokud originál tak možnost první
3) V Tools > Port: vyberte port za předpokladu, že máte arduino už připojené usb kabelem k počítači, v případě, že je vidět více portu tak po odpojení arduina by měl jeden z portů zmizet, tedy ten, který nás zajímá.
4) V Sketch > Include Library > Add .ZIP library: se musí přidat [knihovna](https://github.com/atc1441/arduino-mcp2515/archive/master.zip) pro MCP2515

### kód

Co se  týče kódu tak vá z uživatelského pohledu bude zajímat pouze tato sekce, kde si můžete podle tabulky kódů (vždy jen byte 0-1) přemapovat tlačítka podle vlastní libosti
hodnoty se zadávají ve formátu 0xnn kde n může nabývat hexadecimálních hodnot 0-9 nebo A-H.

jako takový bonus si můžete aktivovat vypnutí funkce start-stop.

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
pokud se rozhodnete v této sekci nic nenastavovat

automaticky se přednastaví funkce tlačítka pro vstup do menu a namísto tlačítka assistentů se nastaví vstup do menu telefonu.









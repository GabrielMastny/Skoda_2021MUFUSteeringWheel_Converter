# Škoda převodník pro 2021 volant s multifunkcí

## materiál

  * [Arduino uno](https://www.gme.cz/100-kompatibilni-klon-arduino-nano-v3-0-r3-original-chip) - stačí levnější klon  
  * [MCP2515](https://www.gme.cz/modul-mcp2515-can-bus-prevodnik-na-spi)
  * [stabilizátor L78S05CV](https://www.gme.cz/stabilizator-pevneho-napeti-stmicroelectronics-78s05) 
  * [chladič stabilizátoru](https://www.gme.cz/do1a-v)
  * [pojistková svorka](https://www.autokabel.cz/kontakt-jpt-28-pro%20vodic-do-1mm-bez-tesneni?search=jpt2801) VAG N90684401
  * [uzemňovací oko](https://www.autokabel.cz/kabelove-oko-m6-modre-smrstovaci?search=KOS06B) velikost oka M6
  * 16x [propojovaci pin samice](https://www.autokabel.cz/dutinka-micro-quadlock-vodic-do-075-mm?search=MQF075) VAG N90764701; 7x arduino, 7x mcp2511, 2x 2-polová svorkovnice kdo se nechce dělat s kabelama sám může si s arduinem koupit propojovací káblíky
  * 4x [propojovaci pin samec](https://www.autokabel.cz/962886-1?search=MQM075) 2x 2-polová svorkovnice, 2x CAN
  * [Svorkovnice 2-pólová samec](https://www.skoda-dily.cz/nahradni-dil/8w0972575-svorkovnice-2-polova-29804.html)
  * [Svorkovnice 2-pólová samice](https://www.skoda-dily.cz/nahradni-dil/8w0971832-svorkovnice-2-polova-23310.html)
  * kabeláž, napájení [červená](https://www.autokabel.cz/autovodic-flry-b-050-mm-cerny?search=FLRY050RD) a [černá](https://www.autokabel.cz/autovodic-flry-b-050-mm-cerny?search=FLRY050BK) s 0,5 mm cca 1m při uložení v blízkosti řídící jednotky.
  * [kabeláž](https://www.autokabel.cz/autovodic-flry-b-035-mm-cerny?search=FLRY035BK) s průměrem 0,35mm na propojení arduina s MCP + Propojení CAN, cca 0,5 m na propojky, 2x 1m pro can ideálně různé barvy
  


## zapojení

[![](/Images/Converter_Schema.png)]()

## využítí CAN v automobilech škoda

### CAN komfort a multifunkční volant


| Funkce                   | Byte 0-1      | Byte 2-3      | Byte 4-5      | Byte 6-7      |
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

| Funkce                   | Byte 0-1      | Byte 2-3      | Byte 4-5      | Byte 6-7      |
| ------------------------ |:-------------:| :------------:| :------------:| :------------:|
| vstoupit do menu         | 02            | 00            | 01            | A3            |
| vyhřívání volantu        | 25            | 00            | 01            | A3            |
| travel assist            | 74            | 00            | 01            | A3            |
| asistenční systémy       | 0C            | 00            | 01            | A3            |



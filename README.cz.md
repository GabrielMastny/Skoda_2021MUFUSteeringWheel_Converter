# Škoda převodník pro 2021 volant s multifunkcí

## zapojení

[![](/Images/Converter_Schema.png)]()


## CAN protokol obecně

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



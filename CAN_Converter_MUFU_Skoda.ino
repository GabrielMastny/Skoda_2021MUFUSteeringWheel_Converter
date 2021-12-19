/**
 * Converter for Skoda 2021 mufu steeringwheel
 *part of https://github.com/GabrielMastny/Skoda_2021MUFUSteeringWheel_Converter
 *
 * @author  Gabriel Mastny aka ExecutedDonut
 * @version 1.0
 * @date 19.12.2021
 */

#include <SPI.h>
#include <mcp2515.h>

//////////////////////////////////////////////////////
//              Set your mapping                    //
                                                    //
const uint8_t user_EnterMenu           = 0x00;      //
const uint8_t user_MenuBack            = 0x00;      //
const uint8_t user_heatedSteeringWheel = 0x00;      //
const uint8_t user_travelAssist        = 0x00;      //
const uint8_t user_assistSystems       = 0x00;      //
// bonus - if you want to disable startstop         //
// change false for true on line below              //
bool disableStartStop = false;                      //
//////////////////////////////////////////////////////
// Do not touch anything below, if you are not sure // 
// what are you doing                               //
//  //  //  //  //  //  //  // // // // // // // // //

struct can_frame canMsg;
const uint32_t mufu_BTN_CAN_ID      = 0x5BF;
const uint32_t startStop_BTN_CAN_ID = 0x65A;

const uint8_t new_menu_BTN_ID             = 0x02;
const uint8_t menuBack_BTN_ID             = 0x03;
const uint8_t heatedSteeringWheel_BTN_ID  = 0x25;
const uint8_t travelAssist_BTN_ID         = 0x74;
const uint8_t assistSystems_BTN_ID        = 0x0C;

uint8_t remapped_menu_BTN_ID                = 0x08;
uint8_t remapped_menuBack_BTN_ID            = 0x00;
uint8_t remapped_heatedSteeringWheel_BTN_ID = 0x00;
uint8_t remapped_travelAssist_BTN_ID        = 0x00;
uint8_t remapped_assistSystems_BTN_ID       = 0x1D;


MCP2515 mcp2515(10);

void SwitchStartStop()
{
  struct can_frame startStopMsg;
  startStopMsg.can_id = startStop_BTN_CAN_ID;
  startStopMsg.can_dlc = 8;
  uint8_t data[8] = {0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x3C, 0x0};
  for(int i = 0; i < 8; i++)
  startStopMsg.data[i] = data[i];

  Serial.println("Switching start stop");
  mcp2515.sendMessage(&startStopMsg);
}

void ModifyAndSend(uint8_t newBtnID)
{
  canMsg.data[0] = newBtnID;
  mcp2515.sendMessage(&canMsg);
}

void setup() 
{
  remapped_menu_BTN_ID = (user_EnterMenu > 0)? user_EnterMenu : remapped_menu_BTN_ID;
  remapped_menuBack_BTN_ID = (user_MenuBack > 0)? user_EnterMenu : remapped_menuBack_BTN_ID;
  remapped_heatedSteeringWheel_BTN_ID = (user_heatedSteeringWheel > 0)? user_EnterMenu : remapped_heatedSteeringWheel_BTN_ID;
  remapped_travelAssist_BTN_ID = (user_travelAssist > 0)? user_EnterMenu : remapped_travelAssist_BTN_ID;
  remapped_assistSystems_BTN_ID = (user_assistSystems > 0)? user_EnterMenu : remapped_assistSystems_BTN_ID;
  
  Serial.begin(115200);
  SPI.begin();
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS);
  mcp2515.setNormalMode();
  
  if (disableStartStop) SwitchStartStop();  
}

void loop() 
{
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) 
  {
    if (canMsg.can_id == mufu_BTN_CAN_ID)
    {
      uint8_t btn_id = canMsg.data[0];

      if (btn_id == new_menu_BTN_ID && remapped_menu_BTN_ID != 0) ModifyAndSend(remapped_menu_BTN_ID);
      else if (btn_id == menuBack_BTN_ID && remapped_menuBack_BTN_ID != 0) ModifyAndSend(remapped_menuBack_BTN_ID);
      else if (btn_id == heatedSteeringWheel_BTN_ID && remapped_heatedSteeringWheel_BTN_ID != 0) ModifyAndSend(remapped_heatedSteeringWheel_BTN_ID);
      else if (btn_id == travelAssist_BTN_ID && remapped_travelAssist_BTN_ID != 0) ModifyAndSend(remapped_travelAssist_BTN_ID);
      else if (btn_id == assistSystems_BTN_ID && remapped_assistSystems_BTN_ID != 0) ModifyAndSend(remapped_assistSystems_BTN_ID);
    }   
  }

}

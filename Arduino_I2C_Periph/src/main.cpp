#include <Arduino.h>
#include "TWI_StatusCodes.h"


#define DEVICE_ADDR 0xAU
#define DEVICE_ADDR_POS 0x1U

void initTWI_Peripheral(void);
void readStatusCode(void);
void ack(void);
void nack(void);
void readBus(void);
void transmitBus(uint8_t data);


volatile uint8_t newCommandFlag = 0U;
volatile uint8_t receivedCommand = 0U, responseData = 0U;



void setup() 
{
  Serial.begin(9600);
  initTWI_Peripheral();

  Serial.println("Arduino intialization complete!");
}

void loop() 
{
   if(newCommandFlag){
      newCommandFlag = 0U;

      Serial.print("Received Command: ");
      Serial.println(receivedCommand);

      //------Selecting Command Response -----
      switch(receivedCommand){
         case 1:
            responseData = 10U;
            break;
         case 2:
            responseData = 20U;
            break;
         case 3:
            responseData = 30U;
            break;
         case 4:
            responseData = 40U;
            break;
         case 6:
            responseData = 7U;
            break;
         default:
            responseData = 255U;
            break;
         }
      Serial.print("Transmitting Response: ");
      Serial.println(responseData);
   }

}



void initTWI_Peripheral(void)
{
/**************Initializing TWI*******************/
//Write address in slave address register bits[7:1]
TWAR = 0;
TWAR |= DEVICE_ADDR  << DEVICE_ADDR_POS;

//Enable Acknowledge Bit, interrupt and 2 wire interface
TWCR |= ((1<<TWEA) | (1<<TWIE) | (1<<TWEN));
}

void ack(void)
{
   TWCR = ((1<<TWEN) | (1<<TWIE) | (1<<TWINT) | (1<<TWEA));
}

void nack(void)
{
   TWCR = ((1<<TWEN) | (1<<TWIE) | (1<<TWINT));
}

void readBus(void)
{
   receivedCommand = TWDR;
}

void transmitBus(void)
{
   TWDR = responseData;
}

void readStatusCode(void)
{
  uint8_t code = TWSR & STATUS_REG_MASK;

  switch(code){
      /**********Slave Receiver***********/
      case R_SLA_ACK:
      case R_GCALL_ACK:
      case R_ARB_LOST_SLA_ACK:
      case R_ARB_LOST_GCALL_ACK:
         ack();
         break;
      case R_DATA_ACK:
      case R_GCALL_DATA_ACK:
         //Read bus and return ack
         readBus();
         newCommandFlag = 1U;
         ack();
         break;
      case R_DATA_NACK:
      case R_GCALL_DATA_NACK:
         ack(); //send nack
         break;
      case R_STOP:
         ack(); 
         break;
      /**********Slave Transmitter***********/
      case T_SLA_ACK:
         transmitBus();
         ack();
         break;
      case T_ARB_LOST_SLA_ACK:
         nack();
         break;
      case T_DATA_ACK:
         ack();
        // nack();
         break;
      case T_DATA_NACK:
         //nack();
         ack();
         break;
      case T_DONE_ACK :
         ack();
         break;
      default:
         break;
  }
}


ISR(TWI_vect)
{
    readStatusCode();
}
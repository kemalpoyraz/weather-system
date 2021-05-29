#include <errno.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_BUF 64

#define ECB 1
#include "aes.h"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "SocketClient.h"

using namespace std;
using namespace exploringBB;


uint8_t key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

void phex(uint8_t*);
void decimalToHex(int, uint8_t[]);
void DBPost(uint8_t[], uint8_t[], int, int);

#define TO_HEX(i) (i <= 9 ? '0' + i : 'A' - 10 + i)

int main(int argc, char *argv){

  uint8_t encryptedTemperature[16];
  uint8_t decryptedTemperature[16];

  uint8_t encryptedPressure[16];
  uint8_t decryptedPressure[16];

  system("i2cdetect -l");
  system("i2cdetect -y -r 1");

  FILE *fp;
  char path[MAX_BUF];
  //Open a file to I2C Bus 3 and tell it that there is a BMP085 located at 0x77.
  snprintf(path,sizeof path, "/sys/class/i2c-adapter/i2c-1/new_device");

  if((fp = fopen(path,"w")) == NULL){

    printf("file open failed\n\n");
    return 1;
  }

  rewind(fp);
  fprintf(fp, "bmp085 0x77\n\n");
  fflush(fp);
  fclose(fp);
  char buf[MAX_BUF];
  //Attempt to open the file of the device.
  snprintf(path, sizeof path, "/sys/bus/i2c/drivers/bmp085/1-0077/temp0_input");

  if((fp = fopen(path, "r")) == NULL){

    printf("cannot open device file\n\n");
    return 1;
  }

  //Attempt to read the temperature from the device.
  if((fgets(buf, MAX_BUF, fp)) == NULL){

    printf("cannot read device\n\n");
  }

  fclose(fp);
  int temp = atoi(buf);
  int tempd = temp / 10;
  printf("Current Temperature: %d\n",tempd);
  //Attempt to open the file of the device.
  snprintf(path, sizeof path, "/sys/bus/i2c/drivers/bmp085/1-0077/pressure0_input");

  if((fp = fopen(path, "r")) == NULL){

    printf("cannot read\n\n");
    return 1;
  }

  //Attempt to read the pressure from the device.
  if((fgets(buf, MAX_BUF, fp)) == NULL){

    printf("cannot read\n\n");
  }

  fclose(fp);
  int pressure = atoi(buf);
  int pressured = pressure / 100;
  printf("Current Pressure: %d\n\n",pressured);

//Temperature processes start

  uint8_t uintTemperature[16];

  uintTemperature[0] = (uint8_t)tempd;
  uintTemperature[1] = 0x00;
  uintTemperature[2] = 0x00;
  uintTemperature[3] = 0x00;
  uintTemperature[4] = 0x00;
  uintTemperature[5] = 0x00;
  uintTemperature[6] = 0x00;
  uintTemperature[7] = 0x00;
  uintTemperature[8] = 0x00;
  uintTemperature[9] = 0x00;
  uintTemperature[10] = 0x00;
  uintTemperature[11] = 0x00;
  uintTemperature[12] = 0x00;
  uintTemperature[13] = 0x00;
  uintTemperature[14] = 0x00;
  uintTemperature[15] = 0x00;

  printf("uint8_t Temperature: ");
  phex(uintTemperature);

  //encrypt temperature
  printf("\nEncrypt Temperature........\n");
  AES128_ECB_encrypt(uintTemperature, key, encryptedTemperature);

  printf("Encrypted Temperature: ");
  phex(encryptedTemperature);

  //decrypt temperature
  printf("\nDecrypting Temperature........\n");
  AES128_ECB_decrypt(encryptedTemperature, key, decryptedTemperature);

  printf("Decrypted Temperature: ");
  phex(decryptedTemperature);

//Temperature process end

//Pressure process start

  uint8_t uintPressure[16];

  int result = pressured / 10;
  int remainder = pressured % 10;

  uintPressure[0] = (uint8_t)result;
  uintPressure[1] = (uint8_t)remainder;
  uintPressure[2] = 0x00;
  uintPressure[3] = 0x00;
  uintPressure[4] = 0x00;
  uintPressure[5] = 0x00;
  uintPressure[6] = 0x00;
  uintPressure[7] = 0x00;
  uintPressure[8] = 0x00;
  uintPressure[9] = 0x00;
  uintPressure[10] = 0x00;
  uintPressure[11] = 0x00;
  uintPressure[12] = 0x00;
  uintPressure[13] = 0x00;
  uintPressure[14] = 0x00;
  uintPressure[15] = 0x00;

  printf("\n\nuint8_t Pressure: ");
  phex(uintPressure);

  printf("\nEncrypt Pressure........\n");
  AES128_ECB_encrypt(uintPressure, key, encryptedPressure);

  printf("Encrypted Pressure: ");
  phex(encryptedPressure);

  printf("\nDecrypt Pressure........\n");
  AES128_ECB_decrypt(encryptedPressure, key, decryptedPressure);

  printf("Decrypted Pressure: ");
  phex(decryptedPressure);


  DBPost(encryptedTemperature, encryptedPressure, tempd, pressured);

//Pressure process end
}

void phex(uint8_t* str)
{
    unsigned char i;
    for(i = 0; i < 16; ++i)
        printf("%d ", str[i]); //%.2x
    printf("\n");
}


void DBPost (uint8_t temp[], uint8_t press[], int tempd, int pressured)
{
   int tempTemp[16], tempPress[16];

   ostringstream head, data;

   data << "field1=";

   for(int i = 0; i < 16; i++)
   {
      tempTemp[i] = (int)temp[i];
      data << tempTemp[i];
   }
   data << "&field2=";

   for(int j = 0; j < 16; j++)
   {
      tempPress[j] = (int)press[j];
      data << tempPress[j];
   }
   data << "&field3=" << tempd << "&field4=" << pressured << endl;

   cout << "Starting ThingSpeak Connection" << endl;
   SocketClient sc("api.thingspeak.com",80); //thingspeak.com

   sc.connectToServer();
   head << "POST /update HTTP/1.1\n"
        << "Host: api.thingspeak.com\n" //update
        << "Connection: close\n"
        << "X-THINGSPEAKAPIKEY: B5KM6KYU4CMSV7K6\n"
        << "Content-Type: application/x-www-form-urlencoded\n"
        << "Content-Length:" << string(data.str()).length() << "\n\n";
   sc.send(string(head.str()));
   sc.send(string(data.str()));
   string rec = sc.receive(1024);
   cout << "[" << rec << "]" << endl;
   cout << "End of ThingSpeak Connection" << endl;
   sc.disconnectFromServer();
}
/*Arduino communicates with both the W5100 and SD card using the SPI bus (through the ICSP header). This is on digital pins 10, 11, 12, and 13 on the Uno and pins 50, 51, and 52 on the Mega. On both boards, pin 10 is used to select the W5100 and pin 4 for the SD card. These pins cannot be used for general I/O. On the Mega, the hardware SS pin, 53, is not used to select either the W5100 or the SD card, but it must be kept as an output or the SPI interface won't work.*/

#include "LiquidCrystal.h"
#include <Keypad.h>
#include <Wire.h>
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 };

byte ip[]={192,168,1,120}; //IP address for your arduino.

char server[] = "192.168.1.100"; //IP address of your computer.

String receivedString=""; //Variable in which the server response is recorded.

char checkvalue[10];

EthernetClient client;

// initialize the library by providing the nuber of pins to it
LiquidCrystal lcd(14,15,16,17,18,19);

char statkey; char pkey1;  char pkey2;  char pkey3;         //for users to press three digits code while parking process 
char upkey1;  char upkey2;  char upkey3;                    //for users to press three digits code while retrieving process
char parray1[5];  char parray2[5];  char parray3[5];  char parray4[5];        //this array stores three digit parking code given by user
char uparray1[5];  char uparray2[5];  char uparray3[5]; char uparray4[5];     //this array checks previously stored user's code
int count=0;  
char customKey; // for user to press A or B for park or unpark
int led1=38;
int led2=40;
int led3=42;
int led4=44;
int rled1=0;          //to prompt slot reserved or slot empty
int rled2=0;
int rled3=0;
int rled4=0;
int hours=00;
int minutes=00;
int seconds=00;
int cost;

unsigned long start_time, stop_time, *pointer1,*pointer2,*pointer3,*pointer4;

int ldrvalue=A0;
int switch1=A2;
int switch2=A3;
int switch3=A4;
int switch4=A5;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads

char hexaKeys[ROWS][COLS] = {
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}
};

byte rowPins[ROWS] = {36,34, 32, 30}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {28, 26, 24, 22}; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);


void resetcount()
{
  count=0;
}

void sendtoserver(char x)
{
  //Send slot information to database
            if(client.connect(server,80))
              {
                  Serial.println("Connected to server");
                  if(x=='1')
                  {
                    Serial.println("Slot 1 written to db");
                    client.print(String("GET ") + "/transfer.php/?slotnumber=1\r\n\r\n" + " HTTP/1.1\r\n" + "Host: " + server + "\r\n" + "Connection: close\r\n\r\n");
                    client.stop();
                  }
                  
                  else if(x=='2')
                  {
                    Serial.println("Slot 2 written to db");
                    client.print(String("GET ") + "/transfer.php/?slotnumber=2\r\n\r\n" + " HTTP/1.1\r\n" + "Host: " + server + "\r\n" + "Connection: close\r\n\r\n");
                    client.stop();
                  }

                  else if(x=='3')
                  {
                    Serial.println("Slot 3 written to db");
                    client.print(String("GET ") + "/transfer.php/?slotnumber=3\r\n\r\n" + " HTTP/1.1\r\n" + "Host: " + server + "\r\n" + "Connection: close\r\n\r\n");
                    client.stop();  
                  }

                  else if(x=='4')
                  {
                    Serial.println("Slot 4 written to db");
                    client.print(String("GET ") + "/transfer.php/?slotnumber=4\r\n\r\n" + " HTTP/1.1\r\n" + "Host: " + server + "\r\n" + "Connection: close\r\n\r\n");
                    client.stop();  
                  }

                  else if(x=='5')
                  {
                    Serial.println("Slot 1 deleted from db");
                    client.print(String("GET ") + "/transfer.php/?slotnumber=5\r\n\r\n" + " HTTP/1.1\r\n" + "Host: " + server + "\r\n" + "Connection: close\r\n\r\n");
                    client.stop();  
                  }

                  else if(x=='6')
                  {
                    Serial.println("Slot 2 deleted from db");
                    client.print(String("GET ") + "/transfer.php/?slotnumber=6\r\n\r\n" + " HTTP/1.1\r\n" + "Host: " + server + "\r\n" + "Connection: close\r\n\r\n");
                    client.stop();  
                  }

                  else if(x=='7')
                  {
                    Serial.println("Slot 3 deleted from db");
                    client.print(String("GET ") + "/transfer.php/?slotnumber=7\r\n\r\n" + " HTTP/1.1\r\n" + "Host: " + server + "\r\n" + "Connection: close\r\n\r\n");
                    client.stop();  
                  }

                  else if(x=='8')
                  {
                    Serial.println("Slot 4 deleted from db");
                    client.print(String("GET ") + "/transfer.php/?slotnumber=8\r\n\r\n" + " HTTP/1.1\r\n" + "Host: " + server + "\r\n" + "Connection: close\r\n\r\n");
                    client.stop();  
                  }
                  
                  else
                  {
                    Serial.println("Sorry! No changes made to the db");  
                  }
              }

              else
              {
                  Serial.println("Sorry! Couldn't get connection to server");  
              }
  
}


void receivefromserver()
{
  receivedString="";
  //Receive slotnumber from database
  if (client.connect(server, 80)) 
  {
    Serial.println("Connected to server, You can now receive data from database");
    client.print(String("GET ") + "/retrieve.php/\r\n\r\n" + " HTTP/1.1\r\n" + "Host: " + server + "\r\n" + "Connection: close\r\n\r\n"); //GET request for server response.
    unsigned long timeout = millis();
    while (client.available() == 0) 
    {
      if (millis() - timeout > 25000) //If nothing is available on server for 25 seconds, close the connection.
      { 
        return;
      }
    }
    while(client.available())
    {
      String line = client.readStringUntil(' '); //Read the server response line by line..
      receivedString+=line; //And store it in rcv.
    }
    client.stop(); // Close the connection.
  }
  else
  {
    Serial.println("Sorry!!Couldn't receive data from database");
  }
  
  receivedString.toCharArray(checkvalue, 10); 

  
  if(checkvalue[0]=='1'|| checkvalue[1]=='1' || checkvalue[2]=='1' || checkvalue[3]=='1')
  {
     digitalWrite(led1,HIGH);
     rled1=digitalRead(led1); 
  }

  if(checkvalue[0]=='2' || checkvalue[1]=='2' || checkvalue[2]=='2' || checkvalue[3]=='2')
  {
     digitalWrite(led2,HIGH);
     rled2=digitalRead(led2);  
  }

  if(checkvalue[0]=='3' || checkvalue[1]=='3' || checkvalue[2]=='3' || checkvalue[3]=='3')
  { 
     digitalWrite(led3,HIGH);
     rled3=digitalRead(led3);  
  }

  if(checkvalue[0]=='4' || checkvalue[1]=='4' || checkvalue[2]=='4' || checkvalue[3]=='4')
  {
     digitalWrite(led4,HIGH);
     rled4=digitalRead(led4);
  }
  
}

void start()
{
    lcd.setCursor(0,0);
    lcd.print("Press any one:  ");
    Serial.println("Press any one:  ");

    lcd.setCursor(0,1);
    lcd.print("Park=A Unpark=B ");
    Serial.println("Park=A Unpark=B ");
    
    customKey=customKeypad.getKey();
    Serial.println(customKey);
    switch(customKey)
    {
      case NO_KEY:
      start();
      break;
      
      case '0': case '1': case '2': case '3': case '4': case '5':
      case '6': case '7': case '8': case '9': case 'C': case 'D':
      case '*': case '#':
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Sorry! Try Again");
      Serial.println("Sorry! Try Again");
      delay(1000);
      start();
      break;
      
      case 'A':
      park();
      break;
      
      case 'B':
      unpark();
      break;
    }
    

}

void park()
{
    receivefromserver();
    
    delay(50);
    switch1=analogRead(A2);
    delay(50);
    switch1=analogRead(A2);
    delay(50);
    switch2=analogRead(A3);
    delay(50);
    switch2=analogRead(A3);
    delay(50);
    switch3=analogRead(A4);
    delay(50);
    switch3=analogRead(A4);
    delay(50);
    switch4=analogRead(A5);
    delay(50);
    switch4=analogRead(A5);
    delay(50);

    Serial.println(switch1);
    Serial.println(switch2);
    Serial.println(switch3);
    Serial.println(switch4);
    
    if(switch1 > 500)
    {
      
      sendtoserver('5');
      digitalWrite(led1,LOW);
      rled1 = digitalRead(led1);    
    }
    if(switch2 > 500)
    {
      
      sendtoserver('6');
      digitalWrite(led2,LOW);
      rled2 = digitalRead(led2);  
    }
    if(switch3 > 500)
    {
      
      sendtoserver('7');
      digitalWrite(led3,LOW);
      rled3 = digitalRead(led3);  
    }
    if(switch4 > 500)
    {
      
      sendtoserver('8');
      digitalWrite(led4,LOW);
      rled4 = digitalRead(led4);  
    }
    
    ldrvalue=analogRead(A0);
    delay(50);
    ldrvalue=analogRead(A0);
    Serial.println(ldrvalue);
    if(ldrvalue > 20)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Platform empty");
      delay(4000);
      start();  
    }
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Slot 1,2,3,4?");
    Serial.println("Slot 1,2,3,4?");
    lcd.setCursor(0,1);
    lcd.print("Park to:");
    Serial.println("Park to:");
    do{
      statkey=customKeypad.getKey();
    }while(statkey == NO_KEY);
    lcd.setCursor(9,1);
    lcd.print(statkey);
    Serial.println(statkey);
    delay(1000);
    switch(statkey)
    {
      case '1':
              if(rled1==HIGH)
              {
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Parking lot");
                Serial.println("Parking lot");
                lcd.setCursor(0,1);
                lcd.print("Occupied");
                Serial.println("Occupied");
                delay(1000);
                
                start();
              }
              
              lcd.clear(); 
              lcd.setCursor(0,0);
              lcd.print("Press your code ");
              Serial.println("Press your code ");
              do{
                  pkey1=customKeypad.getKey();   
                 }while(pkey1 == NO_KEY);
    
              parray1[0]=pkey1;
              lcd.setCursor(0,1);
              lcd.print(pkey1);
              Serial.println(pkey1);
              delay(1000);
    
              do{
                  pkey2=customKeypad.getKey();   
                  }while(pkey2 == NO_KEY);
    
               parray1[1]=pkey2;
               lcd.setCursor(1,1);
               lcd.print(pkey2);
               Serial.println(pkey2);
               delay(1000);

              do{
                 pkey3=customKeypad.getKey();   
                 }while(pkey3 == NO_KEY);
     
              parray1[2]=pkey3;
              lcd.setCursor(2,1);
              lcd.print(pkey3);
              Serial.println(pkey3);
              delay(1000);
  
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Thank you for   ");
              Serial.println("Thank you for   ");
              lcd.setCursor(0,1);
              lcd.print("Registering     ");
              Serial.println("Registering     ");
              delay(3000);

              //Send slot information to database
              
              sendtoserver('1');

              digitalWrite(led1,HIGH);
              rled1=digitalRead(led1);
              
              //Motor code to park in lower station
              Wire.begin();
              Wire.beginTransmission(5);
              Wire.write('A');
              Wire.endTransmission();

              //start timer
              start_time=micros();  
              pointer1=&start_time;
              
              start(); 
              break;    
      
      
      case '2':
              if(rled2==HIGH)
              {
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Parking lot");
                lcd.setCursor(0,1);
                lcd.print("Unavailable");
                Serial.println("Parking lot occupied");
                delay(1000);
                start();
              }
              
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Press your code ");
              Serial.println("Press your code ");
               do{
                  pkey1=customKeypad.getKey();   
                 }while(pkey1 == NO_KEY);
    
              parray2[0]=pkey1;
              lcd.setCursor(0,1);
              lcd.print(pkey1);
              Serial.println(pkey1);
              delay(1000);
    
              do{
                pkey2=customKeypad.getKey();   
                }while(pkey2 == NO_KEY);
    
             parray2[1]=pkey2;
             lcd.setCursor(1,1);
             lcd.print(pkey2);
             Serial.println(pkey2);
             delay(1000);

            do{
               pkey3=customKeypad.getKey();   
              }while(pkey3 == NO_KEY);
     
             parray2[2]=pkey3;
             lcd.setCursor(2,1);
             lcd.print(pkey3);
             Serial.println(pkey3);
             delay(1000);
  
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Thank you for   ");
            lcd.setCursor(0,1);
            lcd.print("Registering     ");
            Serial.println("Thank you for registering");
            delay(3000);
            
            //Send slot information to database

            sendtoserver('2');

            digitalWrite(led2,HIGH);
            rled2=digitalRead(led2);
            
            //Motor code to park in lower station
              Wire.begin();
              Wire.beginTransmission(5);
              Wire.write('B');
              Wire.endTransmission();

            // start timer
            start_time=micros();  
            pointer2=&start_time;
            
            start();
            break;


            case '3':
              if(rled3==HIGH)
              {
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Parking lot");
                lcd.setCursor(0,1);
                lcd.print("Unavailable");
                Serial.println("Parking lot occupied");
                delay(1000);
                start();
              }
              
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Press your code ");
              Serial.println("Press your code ");
               do{
                  pkey1=customKeypad.getKey();   
                 }while(pkey1 == NO_KEY);
    
              parray3[0]=pkey1;
              lcd.setCursor(0,1);
              lcd.print(pkey1);
              Serial.println(pkey1);
              delay(1000);
    
              do{
                pkey2=customKeypad.getKey();   
                }while(pkey2 == NO_KEY);
    
             parray3[1]=pkey2;
             lcd.setCursor(1,1);
             lcd.print(pkey2);
             Serial.println(pkey2);
             delay(1000);

            do{
               pkey3=customKeypad.getKey();   
              }while(pkey3 == NO_KEY);
     
             parray3[2]=pkey3;
             lcd.setCursor(2,1);
             lcd.print(pkey3);
             Serial.println(pkey3);
             delay(1000);
  
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Thank you for   ");
            lcd.setCursor(0,1);
            lcd.print("Registering     ");
            Serial.println("Thank you for registering");
            delay(3000);

            //Send slot information to database

            sendtoserver('3');

            digitalWrite(led3,HIGH);
            rled3=digitalRead(led3);
            
            //Motor code to park in lower station
              Wire.begin();
              Wire.beginTransmission(5);
              Wire.write('C');
              Wire.endTransmission();

            //start timer
            start_time=micros();  
            pointer3=&start_time;
            
            start();
            break;


            case '4':
              if(rled4==HIGH)
              {
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Parking lot");
                lcd.setCursor(0,1);
                lcd.print("Unavailable");
                Serial.println("Parking lot occupied");
                delay(1000);
                start();
              }
              
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Press your code ");
              Serial.println("Press your code ");
               do{
                  pkey1=customKeypad.getKey();   
                 }while(pkey1 == NO_KEY);
    
              parray4[0]=pkey1;
              lcd.setCursor(0,1);
              lcd.print(pkey1);
              Serial.println(pkey1);
              delay(1000);
    
              do{
                pkey2=customKeypad.getKey();   
                }while(pkey2 == NO_KEY);
    
             parray4[1]=pkey2;
             lcd.setCursor(1,1);
             lcd.print(pkey2);
             Serial.println(pkey2);
             delay(1000);

            do{
               pkey3=customKeypad.getKey();   
              }while(pkey3 == NO_KEY);
     
             parray4[2]=pkey3;
             lcd.setCursor(2,1);
             lcd.print(pkey3);
             Serial.println(pkey3);
             delay(1000);
  
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Thank you for   ");
            lcd.setCursor(0,1);
            lcd.print("Registering     ");
            Serial.println("Thank you for registering");
            delay(3000);

            //Send slotnumber to db

            sendtoserver('4');

            digitalWrite(led4,HIGH);
            rled4=digitalRead(led4);

            //Motor code to park in lower station
              Wire.begin();
              Wire.beginTransmission(5);
              Wire.write('D');
              Wire.endTransmission();
            
            //start timer

              start_time=micros();  
              pointer1=&start_time;
            
            start();
            break;
           
      case 'A': case 'B': case '0': case '5':
      case '6': case '7': case '8': case '9': case 'C': case 'D':
      case '*': case '#':
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Sorry! Try Again");
      Serial.println("Sorry! Try Again");
      delay(1000);
      start();
      break;
       
    }
}

void unpark()
{
    ldrvalue=analogRead(A0);
    if(ldrvalue < 20)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Platform is occupied");
      delay(3000);
      start();  
    }
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Slot 1,2,3,4?");
    Serial.println("Slot 1,2,3,4?");
    lcd.setCursor(0,1);
    lcd.print("Unpark from:");
    Serial.println("Unpark from:");
    do{
      statkey=customKeypad.getKey();
    }while(statkey == NO_KEY);
    lcd.setCursor(13,1);
    lcd.print(statkey);
    Serial.println(statkey);
    delay(1000);
    switch(statkey)
    {
      case'1':
              if(rled1==LOW)
              {
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Parking lot");
                lcd.setCursor(0,1);
                lcd.print("Vacant");
                Serial.println("Parking lot Vacant");
                delay(1000);
                start();
              }
             
             lcd.clear();
             lcd.setCursor(0,0);
             lcd.print("Press your code ");
             Serial.println("Press your code ");
             do{
                upkey1=customKeypad.getKey();   
               }while(upkey1 == NO_KEY);
    
             uparray1[0]=upkey1;
             lcd.setCursor(0,1);
             lcd.print(upkey1);
             Serial.println(upkey1);
             delay(1000);
    
              do{
                 upkey2=customKeypad.getKey();   
                 }while(upkey2 == NO_KEY);
    
              uparray1[1]=upkey2;
              lcd.setCursor(1,1);
              lcd.print(upkey2);
              Serial.println(upkey2);
              delay(1000);

              do{
                 upkey3=customKeypad.getKey();   
                 }while(upkey3 == NO_KEY);
    
              uparray1[2]=upkey3;
              lcd.setCursor(2,1);
              lcd.print(upkey3);
              Serial.println(upkey3);
              delay(1000);

     
             for(int i=0;i<3;i++)
           {
               if(parray1[i]==uparray1[i])
                 {
                    count++;
                 }
           }
             if(count==3)
           {
                 lcd.clear();
                 lcd.setCursor(0,0);
                 lcd.print("     Matched    ");   
                 lcd.setCursor(0,1);
                 lcd.print("Retrieving car!!");
                 Serial.println("Matched ! Retrieving Car!!");
                 delay(2000);

                 //Delete slotnumber from db

                 sendtoserver('5');

                 digitalWrite(led1,LOW);
                 rled1=digitalRead(led1);
                 
                 //Motor code to unpark in lower station
                  Wire.begin();
                  Wire.beginTransmission(5);
                  Wire.write('a');
                  Wire.endTransmission();

                  //stop timer
                  start_time = *pointer1;
                  stop_time=micros();
                  seconds = (stop_time - start_time)/1000000;
                  if(seconds>60)
                  {
                    minutes=seconds/60;
                    seconds=seconds%60;
                    if(minutes>60)
                    {
                      hours=minutes/60;
                      minutes=minutes%60;  
                    }  
                  }
                  cost= minutes;
                 lcd.clear();
                 lcd.setCursor(0,0); lcd.print("Time:");
                 lcd.setCursor(6,0); lcd.print(hours);
                 lcd.setCursor(8,0); lcd.print(":");
                 lcd.setCursor(9,0); lcd.print(minutes);
                 lcd.setCursor(11,0); lcd.print(":");
                 lcd.setCursor(12,0); lcd.print(seconds);
                 lcd.setCursor(0,1);  lcd.print("Cost:");
                 lcd.setCursor(6,1);  lcd.print(cost);
                 delay(10000);
                 
                 resetcount();
                 start();
           }
               else
           {
                 lcd.clear();
                 lcd.setCursor(0,0);
                 lcd.print("       Error!!  ");
                 lcd.setCursor(0,1);
                 lcd.print("Please try again");
                 Serial.println("Please try again");
                 delay(1000);
                 start();
            }
             break;
             
      case'2':
              if(rled2==LOW)
              {
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Parking lot");
                Serial.println("Parking lot");
                lcd.setCursor(0,1);
                lcd.print("Vacant");
                Serial.println("Vacant");
                delay(1000);
                start();
              }
             
             lcd.clear();
             lcd.setCursor(0,0);
             lcd.print("Press your code ");
             Serial.println("Press your code ");
             do{
                upkey1=customKeypad.getKey();   
               }while(upkey1 == NO_KEY);
    
             uparray2[0]=upkey1;
             lcd.setCursor(0,1);
             lcd.print(upkey1);
             Serial.println(upkey1);
             delay(1000);
    
              do{
                 upkey2=customKeypad.getKey();   
                 }while(upkey2 == NO_KEY);
    
              uparray2[1]=upkey2;
              lcd.setCursor(1,1);
              lcd.print(upkey2);
              Serial.println(upkey2);
              delay(1000);

              do{
                 upkey3=customKeypad.getKey();   
                 }while(upkey3 == NO_KEY);
    
              uparray2[2]=upkey3;
              lcd.setCursor(2,1);
              lcd.print(upkey3);
              Serial.println(upkey3);
              delay(1000);

     
             for(int i=0;i<3;i++)
           {
               if(parray2[i]==uparray2[i])
                 {
                    count++;
                 }
           }
             if(count==3)
           {
                 lcd.clear();
                 lcd.setCursor(0,0);
                 lcd.print("     Matched    ");   
                 lcd.setCursor(0,1);
                 lcd.print("Retrieving car!!");
                 Serial.println("Matched!! Retrieving car!");
                 delay(2000);

                 //Delete slotnumber from db
                 sendtoserver('6');

                 digitalWrite(led2,LOW);
                 rled2=digitalRead(led2);
                 
                 //Motor code to unpark in upper station
                  Wire.begin();
                  Wire.beginTransmission(5);
                  Wire.write('b');
                  Wire.endTransmission();

                  //stop timer
                  start_time = *pointer2;
                  stop_time=micros();
                  seconds = (stop_time - start_time)/1000000;
                  if(seconds>60)
                  {
                    minutes=seconds/60;
                    seconds=seconds%60;
                    if(minutes>60)
                    {
                      hours=minutes/60;
                      minutes=minutes%60;  
                    }  
                  }
                  cost= minutes;
                 lcd.clear();
                 lcd.setCursor(0,0); lcd.print("Time:");
                 lcd.setCursor(6,0); lcd.print(hours);
                 lcd.setCursor(8,0); lcd.print(":");
                 lcd.setCursor(9,0); lcd.print(minutes);
                 lcd.setCursor(11,0); lcd.print(":");
                 lcd.setCursor(12,0); lcd.print(seconds);
                 lcd.setCursor(0,1);  lcd.print("Cost:");
                 lcd.setCursor(6,1);  lcd.print(cost);
                 delay(10000);
                 resetcount();
                 start();
           }
               else
           {
                 lcd.clear();
                 lcd.setCursor(0,0);
                 lcd.print("       Error!!  ");
                 lcd.setCursor(0,1);
                 lcd.print("Please try again");
                 Serial.println("Please try again");
                 delay(1000);
                 resetcount();
                 start();
            }
             break;


             case'3':
              if(rled3==LOW)
              {
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Parking lot");
                Serial.println("Parking lot");
                lcd.setCursor(0,1);
                lcd.print("Vacant");
                Serial.println("Vacant");
                delay(1000);
                start();
              }
             
             lcd.clear();
             lcd.setCursor(0,0);
             lcd.print("Press your code ");
             Serial.println("Press your code ");
             do{
                upkey1=customKeypad.getKey();   
               }while(upkey1 == NO_KEY);
    
             uparray3[0]=upkey1;
             lcd.setCursor(0,1);
             lcd.print(upkey1);
             Serial.println(upkey1);
             delay(1000);
    
              do{
                 upkey2=customKeypad.getKey();   
                 }while(upkey2 == NO_KEY);
    
              uparray3[1]=upkey2;
              lcd.setCursor(1,1);
              lcd.print(upkey2);
              Serial.println(upkey2);
              delay(1000);

              do{
                 upkey3=customKeypad.getKey();   
                 }while(upkey3 == NO_KEY);
    
              uparray3[2]=upkey3;
              lcd.setCursor(2,1);
              lcd.print(upkey3);
              Serial.println(upkey3);
              delay(1000);

     
             for(int i=0;i<3;i++)
           {
               if(parray3[i]==uparray3[i])
                 {
                    count++;
                 }
           }
             if(count==3)
           {
                 lcd.clear();
                 lcd.setCursor(0,0);
                 lcd.print("     Matched    ");   
                 lcd.setCursor(0,1);
                 lcd.print("Retrieving car!!");
                 Serial.println("Matched!! Retrieving car!");
                 delay(2000);

                 //Delete slotnumber from db
                 sendtoserver('7');

                 digitalWrite(led3,LOW);
                 rled3=digitalRead(led3);
                 
                 //Motor code to unpark in upper station
                  Wire.begin();
                  Wire.beginTransmission(5);
                  Wire.write('c');
                  Wire.endTransmission();

                  //stop timer
                  start_time = *pointer3;
                  stop_time=micros();
                  seconds = (stop_time - start_time)/1000000;
                  if(seconds>60)
                  {
                    minutes=seconds/60;
                    seconds=seconds%60;
                    if(minutes>60)
                    {
                      hours=minutes/60;
                      minutes=minutes%60;  
                    }  
                  }
                  cost= minutes;
                 lcd.clear();
                 lcd.setCursor(0,0); lcd.print("Time:");
                 lcd.setCursor(6,0); lcd.print(hours);
                 lcd.setCursor(8,0); lcd.print(":");
                 lcd.setCursor(9,0); lcd.print(minutes);
                 lcd.setCursor(11,0); lcd.print(":");
                 lcd.setCursor(12,0); lcd.print(seconds);
                 lcd.setCursor(0,1);  lcd.print("Cost:");
                 lcd.setCursor(6,1);  lcd.print(cost);
                 delay(10000);
              
                 resetcount();
                 start();
           }
               else
           {
                 lcd.clear();
                 lcd.setCursor(0,0);
                 lcd.print("       Error!!  ");
                 lcd.setCursor(0,1);
                 lcd.print("Please try again");
                 Serial.println("Please try again");
                 delay(1000);
                 resetcount();
                 start();
            }
             break;


             case'4':
              if(rled4==LOW)
              {
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Parking lot");
                Serial.println("Parking lot");
                lcd.setCursor(0,1);
                lcd.print("Vacant");
                Serial.println("Vacant");
                delay(1000);
                start();
              }
             
             lcd.clear();
             lcd.setCursor(0,0);
             lcd.print("Press your code ");
             Serial.println("Press your code ");
             do{
                upkey1=customKeypad.getKey();   
               }while(upkey1 == NO_KEY);
    
             uparray4[0]=upkey1;
             lcd.setCursor(0,1);
             lcd.print(upkey1);
             Serial.println(upkey1);
             delay(1000);
    
              do{
                 upkey2=customKeypad.getKey();   
                 }while(upkey2 == NO_KEY);
    
              uparray4[1]=upkey2;
              lcd.setCursor(1,1);
              lcd.print(upkey2);
              Serial.println(upkey2);
              delay(1000);

              do{
                 upkey3=customKeypad.getKey();   
                 }while(upkey3 == NO_KEY);
    
              uparray4[2]=upkey3;
              lcd.setCursor(2,1);
              lcd.print(upkey3);
              Serial.println(upkey3);
              delay(1000);

     
             for(int i=0;i<3;i++)
           {
               if(parray4[i]==uparray4[i])
                 {
                    count++;
                 }
           }
             if(count==3)
           {
                 lcd.clear();
                 lcd.setCursor(0,0);
                 lcd.print("     Matched    ");   
                 lcd.setCursor(0,1);
                 lcd.print("Retrieving car!!");
                 Serial.println("Matched!! Retrieving car!");
                 delay(2000);

                 //Delete slotnumber from db
                 sendtoserver('8');
                 
                 digitalWrite(led4,LOW);
                 rled4=digitalRead(led4);
                 
                 //Motor code to unpark in upper station
                  Wire.begin();
                  Wire.beginTransmission(5);
                  Wire.write('d');
                  Wire.endTransmission();

                  //stop timer
                  start_time = *pointer4;
                  stop_time=micros();
                  seconds = (stop_time - start_time)/1000000;
                  if(seconds>60)
                  {
                    minutes=seconds/60;
                    seconds=seconds%60;
                    if(minutes>60)
                    {
                      hours=minutes/60;
                      minutes=minutes%60;  
                    }  
                  }
                  cost= minutes;
                 lcd.clear();
                 lcd.setCursor(0,0); lcd.print("Time:");
                 lcd.setCursor(6,0); lcd.print(hours);
                 lcd.setCursor(8,0); lcd.print(":");
                 lcd.setCursor(9,0); lcd.print(minutes);
                 lcd.setCursor(11,0); lcd.print(":");
                 lcd.setCursor(12,0); lcd.print(seconds);
                 lcd.setCursor(0,1);  lcd.print("Cost:");
                 lcd.setCursor(6,1);  lcd.print(cost);
                 delay(10000);
              
                 resetcount();
                 start();
           }
               else
           {
                 lcd.clear();
                 lcd.setCursor(0,0);
                 lcd.print("       Error!!  ");
                 lcd.setCursor(0,1);
                 lcd.print("Please try again");
                 Serial.println("Please try again");
                 delay(1000);
                 resetcount();
                 start();
            }
             break;
      case 'A': case 'B': case '0': case '5':
      case '6': case '7': case '8': case '9': case 'C': case 'D':
      case '*': case '#':
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Sorry! Try Again");
      Serial.println("Sorry! Try Again");
      delay(1000);
      start();
      break;
    }
   
 }
    
void setup()
{
    Serial.flush();
    Serial.begin(9600);
    pinMode(led1,OUTPUT);
    pinMode(led2,OUTPUT);
    pinMode(led3,OUTPUT);
    pinMode(led4,OUTPUT);
    pinMode(rled1,INPUT);
    pinMode(rled2,INPUT);
    pinMode(rled3,INPUT);
    pinMode(rled4,INPUT);
    pinMode(A0,INPUT);
    pinMode(A2,INPUT);
    pinMode(A3,INPUT);
    pinMode(A4,INPUT);
    pinMode(A5,INPUT);
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    digitalWrite(led4,LOW);
    lcd.begin(16,2);
    lcd.setCursor(0,0);
    lcd.print("   SMART  CAR");
    Serial.println("SMART CAR PARKING PROJECT");
    lcd.setCursor(0,1);
    lcd.print("PARKING PROJECT");
    delay(4000);
    lcd.clear();
    Ethernet.begin(mac, ip);
    delay(1000);
    start();
}



void loop()
{
   
}

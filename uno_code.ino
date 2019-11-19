#include<Wire.h>
#define EN        8  
#define X_DIR     5 
#define Y_DIR     6
#define Z_DIR     7
#define X_STP     2
#define Y_STP     3
#define Z_STP     4 
#define limitX    9   //Limit pins: X->9 , Y->10 , Z->11
#define limitY    10
#define limitZ    11

int stps=200;// Steps to move
int value;

void setup()
{
    
    pinMode(X_DIR, OUTPUT); pinMode(X_STP, OUTPUT);
    pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);
    pinMode(Z_DIR, OUTPUT); pinMode(Z_STP, OUTPUT);
    pinMode(limitX, INPUT_PULLUP);
    pinMode(limitY, INPUT_PULLUP);
    pinMode(limitZ, INPUT_PULLUP);
    pinMode(EN, OUTPUT);
    Wire.begin(5);
    
    
}

void loop()
{
    Wire.onReceive(receiveEvent);
    while(!digitalRead(limitX))
  {
      digitalWrite(X_STP,HIGH); 
      delayMicroseconds(1300); 
      digitalWrite(X_STP,LOW); 
      delayMicroseconds(1300);
    
  }

  while(!digitalRead(limitY))
  {
      digitalWrite(Y_STP,HIGH); 
      delayMicroseconds(1300); 
      digitalWrite(Y_STP,LOW); 
      delayMicroseconds(1300);
    
  }
  
  while(!digitalRead(limitZ))
  {
      digitalWrite(Z_STP,HIGH); 
      delayMicroseconds(1300); 
      digitalWrite(Z_STP,LOW); 
      delayMicroseconds(1300);
    
  }

   
  
}

void step(boolean dir, byte dirPin, byte stepperPin, int steps, unsigned long stepDelay)

{

  digitalWrite(dirPin, dir);

  delay(100);

  for (int i = 0; i < steps; i++) {

    digitalWrite(stepperPin, HIGH);

    delayMicroseconds(stepDelay); 

    digitalWrite(stepperPin, LOW);

    delayMicroseconds(stepDelay); 

  }

}

void receiveEvent(int bytes)
{
  //X(true)->motor goes right , X(false)->motor goes left , Y(true)-> motor goes up , Y(false)->motor goes down , Z(true)->motor goes front , Z(false)->motor goes back
  
    while(Wire.available())
    {
     char c= Wire.read();

     //Character: Park 1,2,3,4 -> A,B,C,D and Unpark 1,2,3,4 -> a,b,c,d
       
       if(c=='A')//park1
        { 

          for(int j=0;j<5;j++)
            {
               step(true, Y_DIR, Y_STP, stps,1000); 
             
            }
            for(int j=0;j<18;j++)
            {
               step(true, Z_DIR, Z_STP, stps,1000); 
               
            }

            for(int j=0;j<4;j++)
            {
               step(false, Y_DIR, Y_STP, stps,1000); 
             
            }

            for(int j=0;j<18;j++)
            {
               step(false, Z_DIR, Z_STP, stps,1000); 
               
            }
          
            for(int j=0;j<1;j++)
            {
               step(false, Y_DIR, Y_STP, stps,1000); 
               
            }
          
        }
                     
        else if(c=='B')//park2
        { 
            for(int j=0;j<30;j++)
            {
               step(true, X_DIR, X_STP, stps,1000); 
             
            }
            for(int j=0;j<5;j++)
            {
               step(true, Y_DIR, Y_STP, stps,1000); 
             
            }
            for(int j=0;j<18;j++)
            {
               step(true, Z_DIR, Z_STP, stps,1000); 
               
            }

            for(int j=0;j<4;j++)
            {
               step(false, Y_DIR, Y_STP, stps,1000); 
             
            }

            for(int j=0;j<18;j++)
            {
               step(false, Z_DIR, Z_STP, stps,1000); 
               
            }
          
            for(int j=0;j<1;j++)
            {
               step(false, Y_DIR, Y_STP, stps,1000); 
               
            }
            for(int j=0;j<30;j++)
            {
               step(false, X_DIR, X_STP, stps,1000); 
             
            }
            
        }   
            
        else if(c=='C')//park3
        {
            for(int j=0;j<30;j++)
            {
               step(true, Y_DIR, Y_STP, stps,1000); 
             
            }
            for(int j=0;j<18;j++)
            {
               step(true, Z_DIR, Z_STP, stps,1000); 
               
            }

            for(int j=0;j<6;j++)
            {
               step(false, Y_DIR, Y_STP, stps,1000); 
             
            }

            for(int j=0;j<18;j++)
            {
               step(false, Z_DIR, Z_STP, stps,1000); 
               
            }
          
            for(int j=0;j<24;j++)
            {
               step(false, Y_DIR, Y_STP, stps,1000); 
               
            }
             
        }            
            
        else if(c=='D')//park4
        { 
          for(int j=0;j<30;j++)
            {
               step(true, X_DIR, X_STP, stps,1000); 
             
            }
          for(int j=0;j<30;j++)
            {
               step(true, Y_DIR, Y_STP, stps,1000); 
             
            }
            for(int j=0;j<18;j++)
            {
               step(true, Z_DIR, Z_STP, stps,1000); 
               
            }

            for(int j=0;j<6;j++)
            {
               step(false, Y_DIR, Y_STP, stps,1000); 
             
            }

            for(int j=0;j<18;j++)
            {
               step(false, Z_DIR, Z_STP, stps,1000); 
               
            }
          
            for(int j=0;j<24;j++)
            {
               step(false, Y_DIR, Y_STP, stps,1000); 
               
            }
            for(int j=0;j<30;j++)
            {
               step(false, X_DIR, X_STP, stps,1000); 
             
            }          
            
        }

        else if(c=='a')//unpark1
        {
            
            for(int j=0;j<18;j++)
            {
               step(true, Z_DIR, Z_STP, stps,1000); 
               
            }

            for(int j=0;j<6;j++)
            {
               step(true, Y_DIR, Y_STP, stps,1000); 
             
            }

            for(int j=0;j<18;j++)
            {
               step(false, Z_DIR, Z_STP, stps,1000); 
               
            }
          
            for(int j=0;j<6;j++)
            {
               step(false, Y_DIR, Y_STP, stps,1000); 
               
            } 
                        
        }

        else if(c=='b')//unpark2
        {

         for(int j=0;j<30;j++)
            {
               step(true, X_DIR, X_STP, stps,1000); 
             
            }
            
            for(int j=0;j<18;j++)
            {
               step(true, Z_DIR, Z_STP, stps,1000); 
               
            }

            for(int j=0;j<6;j++)
            {
               step(true, Y_DIR, Y_STP, stps,1000); 
             
            }

            for(int j=0;j<18;j++)
            {
               step(false, Z_DIR, Z_STP, stps,1000); 
               
            }
          
            for(int j=0;j<6;j++)
            {
               step(false, Y_DIR, Y_STP, stps,1000); 
               
            }
            for(int j=0;j<30;j++)
            {
               step(false, X_DIR, X_STP, stps,1000); 
             
            }
            
                       
        }

        else if(c=='c')//unpark3
        {
          for(int j=0;j<25;j++)
            {
               step(true, Y_DIR, Y_STP, stps,1000); 
             
            }
            for(int j=0;j<18;j++)
            {
               step(true, Z_DIR, Z_STP, stps,1000); 
               
            }

            for(int j=0;j<5;j++)
            {
               step(true, Y_DIR, Y_STP, stps,1000); 
             
            }

            for(int j=0;j<18;j++)
            {
               step(false, Z_DIR, Z_STP, stps,1000); 
               
            }
          
            for(int j=0;j<30;j++)
            {
               step(false, Y_DIR, Y_STP, stps,1000); 
               
            }
            
           
        }
        
        else if(c=='d')//unpark4
        {
          for(int j=0;j<30;j++)
            {
               step(true, X_DIR, X_STP, stps,1000); 
             
            }
          for(int j=0;j<25;j++)
            {
               step(true, Y_DIR, Y_STP, stps,1000); 
             
            }
            for(int j=0;j<18;j++)
            {
               step(true, Z_DIR, Z_STP, stps,1000); 
               
            }

            for(int j=0;j<5;j++)
            {
               step(true, Y_DIR, Y_STP, stps,1000); 
             
            }

            for(int j=0;j<18;j++)
            {
               step(false, Z_DIR, Z_STP, stps,1000); 
               
            }
          
            for(int j=0;j<30;j++)
            {
               step(false, Y_DIR, Y_STP, stps,1000); 
               
            }
            for(int j=0;j<30;j++)
            {
               step(false, X_DIR, X_STP, stps,1000); 
             
            }  
           
             
        }
             
       }
            
 }

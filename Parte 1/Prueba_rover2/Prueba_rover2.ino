#include <Wire.h>

// wired connections
byte slave_addres = 7;
int cmd;

// Izquierda delante
#define HG7881_B_IA 4 
#define HG7881_B_IB 5 

// functional connections
#define MOTOR_B_PWM HG7881_B_IA 
#define MOTOR_B_DIR HG7881_B_IB 

// wired connections2
// Izquierda detras
#define HG7881_B_IA2 6 
#define HG7881_B_IB2 7
 
// functional connections2
#define MOTOR_B_PWM2 HG7881_B_IA2 
#define MOTOR_B_DIR2 HG7881_B_IB2 

// wired connections3
// Derecha detras
#define HG7881_B_IA3 8
#define HG7881_B_IB3 9

// functional connections3
#define MOTOR_B_PWM3 HG7881_B_IA3 
#define MOTOR_B_DIR3 HG7881_B_IB3 

// wired connections4
// derecha delante
#define HG7881_B_IA4 10 
#define HG7881_B_IB4 11 

// functional connections4
#define MOTOR_B_PWM4 HG7881_B_IA4
#define MOTOR_B_DIR4 HG7881_B_IB4

// wired connections5
#define HG7881_B_IA5 2 
#define HG7881_B_IB5 3 

// functional connections5
#define MOTOR_B_PWM5 HG7881_B_IA5 
#define MOTOR_B_DIR5 HG7881_B_IB5 

// wired connections6
#define HG7881_B_IA6 44 
#define HG7881_B_IB6 45 

// functional connections6
#define MOTOR_B_PWM6 HG7881_B_IA6 
#define MOTOR_B_DIR6 HG7881_B_IB6 

// the actual values for "fast" and "slow" depend on the motor
#define PWM_SLOW 160  // arbitrary slow speed PWM duty cycle
#define PWM_FAST 255 // arbitrary fast speed PWM duty cycle
#define DIR_DELAY 1000 // brief delay for abrupt motor changes

void setup(){
  Serial.begin(115200);

  Wire.begin(slave_addres);
  Wire.onReceive(processUL);
  Wire.onRequest(sendUL);
  
  pinMode( MOTOR_B_DIR, OUTPUT );
  pinMode( MOTOR_B_PWM, OUTPUT );
  digitalWrite( MOTOR_B_DIR, LOW );
  digitalWrite( MOTOR_B_PWM, LOW );
  
  pinMode( MOTOR_B_DIR2, OUTPUT );
  pinMode( MOTOR_B_PWM2, OUTPUT );
  digitalWrite( MOTOR_B_DIR2, LOW );
  digitalWrite( MOTOR_B_PWM2, LOW );

  pinMode( MOTOR_B_DIR3, OUTPUT );
  pinMode( MOTOR_B_PWM3, OUTPUT );
  digitalWrite( MOTOR_B_DIR3, LOW );
  digitalWrite( MOTOR_B_PWM3, LOW );

  pinMode( MOTOR_B_DIR4, OUTPUT );
  pinMode( MOTOR_B_PWM4, OUTPUT );
  digitalWrite( MOTOR_B_DIR4, LOW );
  digitalWrite( MOTOR_B_PWM4, LOW );

  pinMode( MOTOR_B_DIR5, OUTPUT );
  pinMode( MOTOR_B_PWM5, OUTPUT );
  digitalWrite( MOTOR_B_DIR5, LOW );
  digitalWrite( MOTOR_B_PWM5, LOW );

  pinMode( MOTOR_B_DIR6, OUTPUT );
  pinMode( MOTOR_B_PWM6, OUTPUT );
  digitalWrite( MOTOR_B_DIR6, LOW );
  digitalWrite( MOTOR_B_PWM6, LOW );
  
}

void loop(){
  
}

void processUL(int n){
  boolean isValidInput;
  
  ///if(n == 5 || n==7 || n == 9 || n == 11){
    Wire.read();
    char uChar = Wire.read();
    char lChar = Wire.read();
    int fDigit = Wire.read();
    int sDigit = Wire.read();
    /*int arg1 = 0, arg2 = 0, arg3 = 0;

    if(n >= 7){
      Wire.read();
      arg1 = Wire.read();
    }
    
    if(n >= 9){
      Wire.read();
      arg2 = Wire.read();
    }
 
    if(n >= 11){
      Wire.read();
      arg3 = Wire.read();
    }*/
    
    Serial.println((String) uChar + (String) lChar + fDigit + sDigit);
    cmd = fDigit*10 + sDigit;
    
  // draw a menu on the serial port
  /*Serial.println( "-----------------------------" );
  Serial.println( "MENU:" );
  Serial.println( "1) Fast forward" );
  Serial.println( "2) Forward" );
  Serial.println( "3) Soft stop (coast)" );
  Serial.println( "4) Reverse" );
  Serial.println( "5) Fast reverse" );
  Serial.println( "6) Hard stop (brake)" );
  Serial.println( "-----------------------------" );
  */
    
                  // get the next character from the serial port
    //Serial.print( "?" );
    //while( !Serial.available() ); // LOOP...
    //c = Serial.read();

                  // execute the menu option based on the character recieved
    switch( cmd ){
      case 1: // 1) Fast forward
        Serial.println( "Fast forward..." );
        delay(DIR_DELAY);
        FastForward();
        isValidInput = true;
        break; 
        
      case 2: // 2) Forward
        Serial.println( "Forward..." );
        delay(DIR_DELAY);
        Forward();
        isValidInput = true;
        break;      

      case 3: // 3) Soft stop (preferred)
        Serial.println( "Soft stop (coast)..." );
        SoftStop();
        isValidInput = true;
        break;

      case 4: // 4) Reverse
        Serial.println( "Fast forward..." );
        delay(DIR_DELAY);
        Reverse();
        isValidInput = true;
        break;

      case 5: // 5) Fast reverse
        Serial.println( "Fast Reverse..." );
        delay(DIR_DELAY);
        FastReverse();
        isValidInput = true;
        break;

      case 6: // 6) Hard stop (use with caution)
        Serial.println( "Hard stop (brake)..." );
        digitalWrite( MOTOR_B_DIR, HIGH );
        digitalWrite( MOTOR_B_PWM, HIGH );
        isValidInput = true;
        break;      
         
      default:
        // wrong character! display the menu again!
        isValidInput = false;
        break;
    }
}

void FastForward(){
  digitalWrite( MOTOR_B_DIR, LOW ); // direction = forward
  analogWrite( MOTOR_B_PWM, PWM_FAST ); // PWM speed = fast
        
  digitalWrite( MOTOR_B_DIR2, LOW ); // direction = forward
  analogWrite( MOTOR_B_PWM2,PWM_FAST ); // PWM speed = fast

  digitalWrite( MOTOR_B_DIR3, LOW ); // direction = forward
  analogWrite( MOTOR_B_PWM3, PWM_FAST ); // PWM speed = fast

  digitalWrite( MOTOR_B_DIR4, LOW ); // direction = forward
  analogWrite( MOTOR_B_PWM4, PWM_FAST ); // PWM speed = fast

  digitalWrite( MOTOR_B_DIR5, LOW ); // direction = forward
  analogWrite( MOTOR_B_PWM5, PWM_FAST ); // PWM speed = fast

  digitalWrite( MOTOR_B_DIR6, LOW ); // direction = forward
  analogWrite( MOTOR_B_PWM6, PWM_FAST ); // PWM speed = fast
}

void Forward(){
  digitalWrite( MOTOR_B_DIR, LOW ); // direction = forward
  analogWrite( MOTOR_B_PWM, PWM_SLOW ); // PWM speed = slow
        
  digitalWrite( MOTOR_B_DIR2, LOW ); // direction = forward
  analogWrite( MOTOR_B_PWM2, PWM_SLOW ); // PWM speed = slow

  digitalWrite( MOTOR_B_DIR3, LOW ); // direction = forward
  analogWrite( MOTOR_B_PWM3, PWM_SLOW ); // PWM speed = slow

  digitalWrite( MOTOR_B_DIR4, LOW ); // direction = forward
  analogWrite( MOTOR_B_PWM4, PWM_SLOW ); // PWM speed = slow

  digitalWrite( MOTOR_B_DIR5, LOW ); // direction = forward
  analogWrite( MOTOR_B_PWM5, PWM_SLOW ); // PWM speed = slow

  digitalWrite( MOTOR_B_DIR6, LOW ); // direction = forward
  analogWrite( MOTOR_B_PWM6, PWM_SLOW ); // PWM speed = slow
}

void SoftStop(){
  digitalWrite( MOTOR_B_DIR, LOW );
  digitalWrite( MOTOR_B_PWM, LOW );
        
  digitalWrite( MOTOR_B_DIR2, LOW );
  digitalWrite( MOTOR_B_PWM2, LOW );

  digitalWrite( MOTOR_B_DIR3, LOW );
  digitalWrite( MOTOR_B_PWM3, LOW );

  digitalWrite( MOTOR_B_DIR4, LOW );
  digitalWrite( MOTOR_B_PWM4, LOW );

  digitalWrite( MOTOR_B_DIR5, LOW );
  digitalWrite( MOTOR_B_PWM5, LOW );

  digitalWrite( MOTOR_B_DIR6, LOW );
  digitalWrite( MOTOR_B_PWM6, LOW );
}

void Reverse(){
  digitalWrite( MOTOR_B_PWM, LOW ); // direction = reverse
  analogWrite( MOTOR_B_DIR, PWM_SLOW ); // PWM speed = slow
        
  digitalWrite( MOTOR_B_PWM2, LOW ); // direction = reverse
  analogWrite( MOTOR_B_DIR2, PWM_SLOW ); // PWM speed = slow

  digitalWrite( MOTOR_B_PWM3, LOW ); // direction = reverse
  analogWrite( MOTOR_B_DIR3, PWM_SLOW ); // PWM speed = slow

  digitalWrite( MOTOR_B_PWM4, LOW ); // direction = reverse
  analogWrite( MOTOR_B_DIR4, PWM_SLOW ); // PWM speed = slow

  digitalWrite( MOTOR_B_PWM5, LOW ); // direction = reverse
  analogWrite( MOTOR_B_DIR5, PWM_SLOW ); // PWM speed = slow

  digitalWrite( MOTOR_B_PWM6, LOW ); // direction = reverse
  analogWrite( MOTOR_B_DIR6, PWM_SLOW ); // PWM speed = slow
}

void FastReverse(){
  digitalWrite( MOTOR_B_PWM, LOW ); // direction = reverse      
  analogWrite( MOTOR_B_DIR, PWM_FAST ); // PWM speed = fast
        
  digitalWrite( MOTOR_B_PWM2, LOW ); // direction = reverse      
  analogWrite( MOTOR_B_DIR2, PWM_FAST ); // PWM speed = fast

  digitalWrite( MOTOR_B_PWM3, LOW ); // direction = reverse      
  analogWrite( MOTOR_B_DIR3, PWM_FAST ); // PWM speed = fast

  digitalWrite( MOTOR_B_PWM4, LOW ); // direction = reverse      
  analogWrite( MOTOR_B_DIR4, PWM_FAST ); // PWM speed = fast

  digitalWrite( MOTOR_B_PWM5, LOW ); // direction = reverse      
  analogWrite( MOTOR_B_DIR5, PWM_FAST ); // PWM speed = fast

  digitalWrite( MOTOR_B_PWM6, LOW ); // direction = reverse      
  analogWrite( MOTOR_B_DIR6, PWM_FAST ); // PWM speed = fast
}

void LeftTurn(){ // falta la configuración del motor paso a paso para las direcciones 

  digitalWrite( MOTOR_B_PWM, LOW ); // direction = reverse      
  analogWrite( MOTOR_B_DIR, PWM_SLOW ); // PWM speed = slow
        
  digitalWrite( MOTOR_B_PWM2, LOW ); // direction = reverse      
  analogWrite( MOTOR_B_DIR2, PWM_SLOW ); // PWM speed = slow

  digitalWrite( MOTOR_B_DIR3, LOW ); // direction = forward      
  analogWrite( MOTOR_B_PWM3, PWM_FAST ); // PWM speed = slow

  digitalWrite( MOTOR_B_DIR4, LOW ); // direction = forward      
  analogWrite( MOTOR_B_PWM4, PWM_FAST ); // PWM speed = slow
  
//  MOTOR PASO A PASO PARA LA DIRECCIÓN HAY QUE ESPERAR PARA TENERLO
  void SpinControl();
  
}
void RightTurn(){
  digitalWrite( MOTOR_B_DIR, LOW ); // direction = forward     
  analogWrite( MOTOR_B_PWM, PWM_SLOW ); // PWM speed = slow
        
  digitalWrite( MOTOR_B_DIR2, LOW ); // direction = forward      
  analogWrite( MOTOR_B_PWM2, PWM_SLOW ); // PWM speed = slow

  digitalWrite( MOTOR_B_PWM3, LOW ); // direction = reverse      
  analogWrite( MOTOR_B_DIR3, PWM_FAST ); // PWM speed = slow

  digitalWrite( MOTOR_B_PWM4, LOW ); // direction = reverse      
  analogWrite( MOTOR_B_DIR4, PWM_FAST ); // PWM speed = slow  

//  MOTOR PASO A PASO PARA LA DIRECCIÓN HAY QUE ESPERAR PARA TENERLO
 void SpinControl();
}


/*
void SpinControl(){
  
  char c = Serial.read();
  leeCadena += c;
  if (leeCadena.length > 0){
  dato_rx = leeCadena.toInt();
    Serial.print(dato_rx);
    Serial.print(" Grados ");
    
    dato_rx = (dato_rx*1.4222222);
  }
  while(dato_rx > numero_pasos){
    paso_izquierda();
    numero_pasos = numero_pasos + 1;
  }
  while(dato_rx < numero_pasos){
    paso_derecha();
    numero_pasos = numero_pasos - 1;
  }
  leeCadena = "";
  apagado();  
}
  
*/

void sendUL(int n){
  Wire.write("OK");
}


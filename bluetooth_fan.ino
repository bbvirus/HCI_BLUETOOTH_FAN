#include <SoftwareSerial.h>

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
int MOTOR = 9;

void setup()
{
  Serial.begin(9600);  // Begin the serial monitor at 9600bps

  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  bluetooth.print("$");  // Print three times individually
  bluetooth.print("$");
  bluetooth.print("$");  // Enter command mode
  delay(100);  // Short delay, wait for the Mate to send back CMD
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);  // Start bluetooth serial at 9600

  pinMode(MOTOR, OUTPUT);
  
  Serial.println("HI");
}

void loop()
{
  if(bluetooth.available()){
    char data = (char)bluetooth.read();
    Serial.print(data);
    
    if(data == 'h'){
      analogWrite(MOTOR, 255);
    }
    
    if(data == 'm'){
      analogWrite(MOTOR, 170);
    }
    
    if(data == 'n'){
      analogWrite(MOTOR, 120);
    }
    
    if(data == 'l'){
      analogWrite(MOTOR, 0);
    }
  }

  if(Serial.available()){
    bluetooth.print((char)Serial.read());
  }
}

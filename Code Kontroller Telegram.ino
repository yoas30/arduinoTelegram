
#include "CTBot.h"


CTBot myBot;


String ssid = "DELLA";
String pass = "della2000";
String token = "6823105395:AAHupWkFr7ra8UuQ3uOrvluA0h770xJ-QZc";



int relayLampu = 0;   //Lampu - Pin D3  ==> BIRUs
int relayPompaAir = 2;   // Pompa Air - Pin D4  ==> HIJAU
int ledrelayLampu = 13; //OK - Pin D7
int ledrelayPompaAir = 12; //OK - Pin D6  
int buzzer = 15;  //OK - Pin D8
                  


void setup() {
  // initialize the Serial
  Serial.begin(115200);
  Serial.println("Starting TelegramBot...");


  // connect the ESP8266 to the desired access point
  myBot.wifiConnect(ssid, pass);
  // set the telegram bot token
  myBot.setTelegramToken(token);


  pinMode(relayLampu, OUTPUT_OPEN_DRAIN);
  pinMode(relayPompaAir, OUTPUT_OPEN_DRAIN);
  digitalWrite(relayLampu, HIGH);           //Relay Normally Close (NC)
  digitalWrite(relayPompaAir, HIGH);           //Relay Normally Close (NC)


  pinMode(ledrelayLampu, OUTPUT || INPUT);
  pinMode(ledrelayPompaAir, OUTPUT || INPUT);
  digitalWrite(ledrelayLampu, LOW);          
  digitalWrite(ledrelayPompaAir, LOW);      


  pinMode(buzzer, OUTPUT);


  // check if all things are ok
  if (myBot.testConnection()){
    Serial.println("\ntestConnection OK!");
    }
  else{
    Serial.println("\ntestConnection GAGAL!");
  }


}



void loop() {
     
  // a variable to store telegram message data
  TBMessage msg;


  // if there is an incoming message...
  if (myBot.getNewMessage(msg)) {
    if (msg.text.equalsIgnoreCase("/pompaOn")) 
    { 
      digitalWrite(relayPompaAir, LOW);  
      myBot.sendMessage(msg.sender.id, "Pompa Air Dihidupkan!");
      digitalWrite(ledrelayPompaAir, HIGH);
      beepHidup(); 
    }
    else if (msg.text.equalsIgnoreCase("/pompaOff")) 
    {             
      digitalWrite(relayPompaAir, HIGH);                            
      myBot.sendMessage(msg.sender.id, "Pompa Air Dimatikan!"); 
      digitalWrite(ledrelayPompaAir, LOW);
      beepMati(); 
    }
    else if (msg.text.equalsIgnoreCase("/lampuOff")) 
    {             
      digitalWrite(relayLampu, HIGH);                            
      myBot.sendMessage(msg.sender.id, "Lampu Dimatikan!"); 
      digitalWrite(ledrelayLampu, LOW);
      beepMati(); 
    }
    else if (msg.text.equalsIgnoreCase("/lampuOn")) 
    { 
      digitalWrite(relayLampu, LOW);  
      myBot.sendMessage(msg.sender.id, "Lampu Dihidupkan!");
      digitalWrite(ledrelayLampu, HIGH);
      beepHidup(); 
    }
    else if (msg.text.equalsIgnoreCase("/allOn")) 
    {             
      digitalWrite(relayPompaAir, LOW);
      digitalWrite(relayLampu, LOW);                            
      myBot.sendMessage(msg.sender.id, "Pompa Air dan Lampu Dihidupkan!"); 
      digitalWrite(ledrelayPompaAir, HIGH);
      digitalWrite(ledrelayLampu, HIGH);
      beepHidup(); 
    }
    else if (msg.text.equalsIgnoreCase("/allOff")) 
    {             
      digitalWrite(relayPompaAir, HIGH);
      digitalWrite(relayLampu, HIGH);                            
      myBot.sendMessage(msg.sender.id, "Pompa Air dan Lampu Dimatikan!"); 
      digitalWrite(ledrelayPompaAir, LOW);
      digitalWrite(ledrelayLampu, LOW);
      beepMati(); 
    }
    else if (msg.text.equalsIgnoreCase("/status")) 
      {     
          if(digitalRead(ledrelayLampu) == HIGH && digitalRead(ledrelayPompaAir) == HIGH){
          myBot.sendMessage(msg.sender.id, "Pompa Air dan Lampu Masih Hidup!");
          }  
          else if (digitalRead(ledrelayLampu) == LOW && digitalRead(ledrelayPompaAir) == LOW){
          myBot.sendMessage(msg.sender.id, "Pompa Air dan Lampu Telah Mati!");
          }
          else if (digitalRead(ledrelayLampu) == HIGH && digitalRead(ledrelayPompaAir) == LOW){
          myBot.sendMessage(msg.sender.id, "Pompa Air Mati dan Lampu Hidup!");
          }
          else if (digitalRead(ledrelayLampu) == LOW && digitalRead(ledrelayPompaAir) == HIGH){
          myBot.sendMessage(msg.sender.id, "Pompa Air Hidup dan Lampu Mati!");
          }
      }
    else if (msg.text.equalsIgnoreCase("/start")){                                                   
      // generate the message for the sender
      String reply1;
            reply1 = "Hallo >>" + msg.sender.username + "<<.\n";
            reply1 += "Klik perintah tanda biru dibawah \n";
            reply1 += "/status    : cek status Listrik\n";
            reply1 += "/pompaOn   : Menyalakan Pompa Air\n";
            reply1 += "/pompaOff  : Mematikan Pompa Air\n";
            reply1 += "/lampuOn   : Menyalakan Lampu\n";
            reply1 += "/lampuOff  : Mematikan Lampu\n";
            reply1 += "/allOn     : Menyalakan Semua Listrik\n";
            reply1 += "/allOff    : Mematikan Semua listrik\n";
      myBot.sendMessage(msg.sender.id, reply1);             
    }
    else{
      String reply2;
            reply2 = "Perintah Salah "+ msg.sender.username + " !\n";
            reply2 += "Coba lagi dengan perintah yang benar!\n";
      myBot.sendMessage(msg.sender.id, reply2);
    }
   
  }
  // wait 500 milliseconds
  delay(500);
}


void beepHidup (){
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
}


void beepMati (){
  digitalWrite(buzzer, HIGH);
  delay(250);
  digitalWrite(buzzer, LOW);
  delay(50);
  digitalWrite(buzzer, HIGH);
  delay(250);
  digitalWrite(buzzer, LOW);
}
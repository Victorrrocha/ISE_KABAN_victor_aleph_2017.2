#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Debug.h>
#include <MFRC522Extended.h>
#include <MFRC522Hack.h>
#include <require_cpp11.h>
#include <stdio.h>

//Programa original : RFID - Controle de Acesso leitor RFID
//Autor : FILIPEFLOP

//Programa Adaptado: somador de compras automatizado
//Autor da adaptação: Victor Barbosa Rocha 

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

char st[20];
float saldo = 0;
int contadorA = 0;
int contadorB = 0;

void setup() 
{
  Serial.begin(9600); // Inicia a serial
  SPI.begin();    // Inicia  SPI bus
  mfrc522.PCD_Init(); // Inicia MFRC522
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
    //Define o número de colunas e linhas do LCD:  
    //lcd.begin(16, 2);  
    //mensageminicial();
}

void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  if (conteudo.substring(1) == "15 5B 0E 88" && contadorA ==  0) //UID 1 - Chaveiro
  {
    contadorA += 1;
    Serial.println("Gorro de frio");
    saldo += 45,90;
    Serial.println("Saldo atual");
    Serial.println(saldo);
    Serial.println();
  }

  if (conteudo.substring(1) == "56 6C 96 A5" && contadorB == 0) //UID 2 - Cartao
  {
    contadorB += 1;
    Serial.println("Blusa Azul");
    saldo += 39,90;
    Serial.println("Saldo atual");
    Serial.println(saldo);
    Serial.println();
  }

  /*if(contador == 2)
  {
    contador = 0;
  }*/
} 


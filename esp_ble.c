#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
    #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

const int ledVermelho = 10;
const int ledVerde = 8;

BluetoothSerial SerialBT;

void setup() {
    Serial.begin(115200);

    //Polarizacao invertida: 0(liga) / 1(desliga)
    pinMode(ledVermelho, OUTPUT);
    pinMode(ledVerde, OUTPUT);

    digitalWrite(ledVermelho, 1);
    digitalWrite(ledVerde, 1);
    //Initialize the software serial

    SerialBT.begin("ESP32test"); //Bluetooth device name
    Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
    // Verifica se o monitor serial enviou dados
    if (Serial.available()) {
        char r = Serial.read(); // Lê o dado e salva em registrador
        SerialBT.write(r); // Envia o dado recebido do serial para o Bluetooth
        Serial.print(r); // Imprime o dado
    }

    //Verifica se bluetooth recebeu um dado
    if (SerialBT.available()) {
        char r = SerialBT.read(); // Lê o dado e salva em registrador
        Serial.print(r); // Imprime o dado recebido

        if (r == '0') {
            Serial.print("ACESSO NEGADO");
            digitalWrite(ledVermelho, 0);
            digitalWrite(ledVerde, 1);
            Serial.println("");
        }
        else if (r == '1') {
            Serial.print("ACESSO PERMITIDO");
            digitalWrite(ledVermelho, 1);
            digitalWrite(ledVerde, 0);
            Serial.println("");
        }
    }
}
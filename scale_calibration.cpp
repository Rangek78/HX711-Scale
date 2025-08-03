/*
Soma atual: 390521.00
Número de medições feitas: 20
Resultado final: 20551.60
Peso de referência: 47g

fator_calibracao = 20551.60/47
fator_calibracao = 437.2680851064
*/

#include <Arduino.h>
#include "HX711.h"

// Ligação do HX711 no Arduino
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

long calibrate();

// Botão para tara da balança
const int TARE_BUTTON_PIN = 7;
HX711 scale;
int button_state;
float avg = 0.0;

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void loop() {
  button_state = digitalRead(TARE_BUTTON_PIN);
  if (scale.is_ready()) {
    if (button_state == 1 && avg == 0) {
      float it = 0.0;
      while (digitalRead(TARE_BUTTON_PIN) == 1) {
        it = it + 1.0;
        Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n");
        Serial.println("Pressione o botão a qualquer momento para terminar a calibração.");
        Serial.print("Soma atual: ");
        Serial.print(avg);
        Serial.print("\tNúmero de medições feitas: ");
        Serial.println(it);
        avg += calibrate();
        delay(1000);
        if (digitalRead(TARE_BUTTON_PIN) == 0) {
          Serial.print("\n\nResultado final: ");
          Serial.println(avg/it);
          delay(5000);
        }
      }
    } else {
      Serial.println("Pressione o botão para começar a calibração.");
      avg = 0;
      while(digitalRead(TARE_BUTTON_PIN) == 0) {

      }
    }
  } else {
    Serial.println("\nHX711 não encontrado.");
  }
    delay(1000);
}

long calibrate() {
  scale.set_scale();
  Serial.print("Tara... remove qualquer peso da balança. ");
  delay(2000);
  scale.tare();
  Serial.println("Pronto... ");
  Serial.print("Coloque um peso conhecido na balança... ");
  delay(2000);
  long reading = scale.get_units(10);
  return reading;
}
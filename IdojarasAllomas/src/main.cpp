/**
 * @file main.cpp
 * @author Aladár (aka ALA)
 * @brief Vezérlési kód az időjárás állomás működtetéséhez.
 * 
 * @copyright Copyright (c) 2024 P2GyK Informatika Zrt.
 * 
 */

#include <Arduino.h>           // ALA: általános vezérlési kód használatához
#include <DHT.h>               // ALA: DHT osztály használatához
#include <LiquidCrystal_I2C.h> // ALA: LiquidCrystal_I2C osztály használatához

#include "idojaras_szamitasok.h" // ALA: Kriszta által kidolgozott
                                 //      segédfüggvények időjárási számításokhoz

LiquidCrystal_I2C lcd_display(0x27, 16, 2);
DHT dht_sensor(15, DHT11);

uint8_t previous_button_state = LOW;
bool display_in_fahrenheit = false;

// ALA: a setup() függvény induláskor fut le inicializációkhoz
void setup() {
  // ALA: kijelző inicializálása, háttérfény bekapcsolása és puffer törlése
  lcd_display.init();
  lcd_display.backlight();
  lcd_display.clear();
  
  // ALA: időjárásszenzor inicializálása
  dht_sensor.begin();

  pinMode(18, INPUT);
}

// ALA: a loop() függvény inicializálás után fut végtelen ciklusként
void loop() {
  // ALA: hőmérséklet és páratartalom értékek lekérése a szenzortól
  // Kriszta aka KRI: nem lenne elég később helyben meghívni a függvényeket?
  //      így csak fölöslegesen sok kódot írsz...
  // ALA: így átláthatóbb és könyebben karbantartható marad, egyébként is,
  //      const minősítő miatt a fordító jó eséllyel kioptimalizálja
  const float temperature = dht_sensor.readTemperature();
  const float humidity = dht_sensor.readHumidity();

  const uint8_t current_button_state = digitalRead(18);
  if (previous_button_state == LOW && current_button_state == HIGH) {
    display_in_fahrenheit ^= 1;
  }
  previous_button_state = current_button_state;

  // ALA: lekért értékek kiírása a kijelzőre
  lcd_display.setCursor(0,0);
  lcd_display.print("Homerseklet:");
  display_in_fahrenheit
    ? lcd_display.printf("%3.0fF", celsius_to_fahrenheit(temperature))
    : lcd_display.printf("%3.0fC", temperature);
  lcd_display.setCursor(0,1);
  lcd_display.printf("Paratartalom:%2.0f%%", humidity);
  // KRI: %% mégis minek?
  // ALA: sima % kell, de úgy csak eldobja, így tudom egyedül escapelni, hogy
  //      ténylegesen kiírja

  // KRI: itt minek a késleltetés?
  // ALA: túl gyakran pollolva túlmelegedne a kicsi, 2sec jónak tűnt
  delay(2000);
}

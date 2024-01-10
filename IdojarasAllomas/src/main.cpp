/**
 * @file main.cpp
 * @author Aladár (aka ALA)
 * @brief Vezérlési kód az időjárás állomás működtetéséhez.
 * 
 * @copyright Copyright (c) 2024 P2GyK Informatika Zrt.
 * 
 */

#include <Arduino.h>           // ALA- általános vezérlési kód használatához
#include <DHT.h>               // ALA- DHT osztály használatához
#include <LiquidCrystal_I2C.h> // ALA- LiquidCrystal_I2C osztály használatához

LiquidCrystal_I2C lcd_kijelzo(0x27, 16, 2);
DHT dht_szenzor(15, DHT11);

// ALA- a setup() függvény induláskor fut le inicializációkhoz
void setup() {
  // ALA- kijelző inicializálása, háttérfény bekapcsolása és puffer törlése
  lcd_kijelzo.init();
  lcd_kijelzo.backlight();
  lcd_kijelzo.clear();
  // ALA- időjárásszenzor inicializálása
  dht_szenzor.begin();
}

// ALA- a loop() függvény inicializálás után fut végtelen ciklusként
void loop() {
  // ALA- hőmérséklet és páratartalom értékek lekérése a szenzortól
  // Kriszta aka KRI- nem lenne elég később helyben meghívni a függvényeket?
  //      így csak fölöslegesen sok kódot írsz...
  // ALA- így átláthatóbb és könyebben karbantartható marad, egyébként is,
  //      const minősítő miatt a fordító jó eséllyel kioptimalizálja
  const float homerseklet = dht_szenzor.readTemperature();
  const float paratartalom = dht_szenzor.readHumidity();

  // ALA- lekért értékek kiírása a kijelzőre
  lcd_kijelzo.setCursor(1,0);
  lcd_kijelzo.printf("Homersek.: %2.0fC", homerseklet);
  lcd_kijelzo.setCursor(1,1);
  lcd_kijelzo.printf("Paratart.: %2.0f%%", paratartalom);
  // KRI- %% mégis minek?
  // ALA- sima % kell, de úgy csak eldobja, így tudom egyedül escapelni, hogy
  //      ténylegesen kiírja

  // KRI- itt minek a késleltetés?
  // ALA- túl gyakran pollolva túlmelegedne a kicsi, 3sec jónak tűnt
  delay(3000);
}

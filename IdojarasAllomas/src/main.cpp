#include <Arduino.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#include ".\controller\weather_station_controller.h"
#include ".\model\weather_data_container.h"
#include ".\view\weather_data_view.h"

class WeatherLcdView : public WeatherStation::IWeatherDataView {
public:
  WeatherLcdView(LiquidCrystal_I2C& lcd) : lcd_display(lcd) {}
  void displayCurrent(WeatherStation::WeatherDatapoint current_datapoint) override {
    lcd_display.setCursor(0,0);
    lcd_display.printf("Homerseklet:%3.0fC", current_datapoint.getTemperature());
    lcd_display.setCursor(0,1);
    lcd_display.printf("Paratartalom:%2.0f%%", current_datapoint.getHumidity());
  }
  void displayHistory(std::vector<WeatherStation::WeatherDatapoint> history_datapoints) override {
    lcd_display.setCursor(0,0);
    lcd_display.printf("Hom. elozo 5 ora");
    lcd_display.setCursor(0,1);

    std::vector<float> history;
    size_t minute_counter = 0;
    float accumulator = 0.f;

    for (auto iter = history_datapoints.rbegin(); iter != history_datapoints.rend(); iter++) {
      accumulator += iter->getTemperature();
      minute_counter++;
      if (minute_counter % 60 == 0) { history.push_back(accumulator / 60.f); accumulator = 0.f; }
    }

    history.resize(5);

    lcd_display.printf("%2.0fC-%2.0f-%2.0f-%2.0f-%2.0fC", history[4], history[3], history[2], history[1], history[0]);
  }

private:
  LiquidCrystal_I2C& lcd_display;
}; // class WeatherLcdView

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht_sensor(15, DHT11);
unsigned long last_updated = 0;

int history_button_prev_state = LOW;
bool display_current = true;

void WeatherStation::WeatherStationController::update() {
  if (unsigned long current_time = ::millis(); current_time > last_updated + 60000 || last_updated == 0) {
    weather_data_model.addWeatherDatapoint({current_time, dht_sensor.readTemperature(), dht_sensor.readHumidity()});
    
    display_current
      ? weather_data_view.displayCurrent(weather_data_model.getCurrent())
      : weather_data_view.displayHistory(weather_data_model.getHistory());

    last_updated = current_time;
  }

  if (int history_button_new_state = digitalRead(18); history_button_new_state != history_button_prev_state) {
    if (history_button_new_state == HIGH) display_current ^= 1;

    display_current
      ? weather_data_view.displayCurrent(weather_data_model.getCurrent())
      : weather_data_view.displayHistory(weather_data_model.getHistory());

    history_button_prev_state = history_button_new_state;
  }
}

WeatherLcdView weather_lcd_view(lcd);
WeatherStation::WeatherDataContainer weather_data_container{};

WeatherStation::WeatherStationController weather_station_controller(weather_lcd_view, weather_data_container);

void setup() {
  Serial.begin(MONITOR_SPEED);

  pinMode(18, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  dht_sensor.begin();

  Serial.println("Init");
}

void loop() {
  weather_station_controller.update();
}

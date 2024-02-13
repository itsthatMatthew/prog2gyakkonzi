#pragma once

#include <vector>
#include "..\model\weather_datapoint.h"

namespace WeatherStation {

struct IWeatherDataView {
  virtual void displayCurrent(WeatherStation::WeatherDatapoint) = 0;
  virtual void displayHistory(std::vector<WeatherStation::WeatherDatapoint>) = 0;
}; // struct IWeatherDataView

} // namespace WeatherStation
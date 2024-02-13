#pragma once

#include <vector>
#include "weather_datapoint.h"

namespace WeatherStation {

struct IWeatherDataModel {
  virtual void addWeatherDatapoint(WeatherDatapoint) = 0;
  virtual WeatherStation::WeatherDatapoint getCurrent() = 0;
  virtual std::vector<WeatherStation::WeatherDatapoint> getHistory() = 0;
}; // struct IWeatherDataModel

} // namespace WeatherStation
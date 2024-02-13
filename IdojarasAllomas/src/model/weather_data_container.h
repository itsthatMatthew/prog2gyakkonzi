#pragma once

#include <vector>
#include "weather_datapoint.h"
#include "weather_data_model.h"

namespace WeatherStation {

struct WeatherDataContainer
  : public WeatherStation::IWeatherDataModel
  , private std::vector<WeatherStation::WeatherDatapoint> {
  WeatherDataContainer() = default;
  void addWeatherDatapoint(WeatherStation::WeatherDatapoint data_point) override { push_back(data_point); }
  [[nodiscard]] WeatherStation::WeatherDatapoint getCurrent() override { return back(); }
  [[nodiscard]] std::vector<WeatherStation::WeatherDatapoint> getHistory() override { return *this; }
}; // class WeatherDataContainer

} // namespace WeatherStation
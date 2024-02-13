#pragma once

#include <vector>
#include "..\view\weather_data_view.h"
#include "..\model\weather_data_model.h"

namespace WeatherStation {

class WeatherStationController {
public:
  WeatherStationController(WeatherStation::IWeatherDataView&weather_data_view,
                           WeatherStation::IWeatherDataModel& weather_data_model)
    : weather_data_view(weather_data_view)
    , weather_data_model(weather_data_model)
  {}
  void update();
private:
  WeatherStation::IWeatherDataView& weather_data_view;
  WeatherStation::IWeatherDataModel& weather_data_model;
}; // struct WeatherStationController

} // namespace WeatherStation
/// Weather calculation functions
/// Copyright 1989 Géza

// Kriszta: Gézának a régi cuccai, nem merem törölni, nehogy elnrontson valamit

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "idojaras_szamitasok.h" // Kriszta: átírtam, hogy a miénket használja

/// Temp calc functions

float dew_point(float Tair, float Rh) {
  float X = log(Rh / 100.f) + ((17.269f * Tair) / (237.3f + Tair));
  return (237.3f * X) / (17.269f - X);
}

float svp(float D) {
  return 6.11f + 0.339f * (D - 32.f);
}

float saturated_vapor_pressure_in_millibars_from_celsius(float Tair, float Rh) {
  // Kriszta: itt fahrenheitben kellett neki a hőmérséklet
  return svp(celsius_to_fahrenheit(dew_point(Tair, Rh)));
}

/// Timestamped weather data points

struct WeatherDataPoint {
  time_t unix_time;
  size_t temperature;
  size_t humidity;
};

WeatherDataPoint* add_new_weather_data_point(
WeatherDataPoint *src_array, size_t *array_size, WeatherDataPoint *new_data) {
    WeatherDataPoint *new_array =
      (WeatherDataPoint*)malloc((*array_size + 1) * sizeof(WeatherDataPoint));
    if (new_array == NULL) return src_array;

    if (src_array != NULL) {
      for (size_t idx = 0; idx != *array_size; idx++) {
        new_array[idx] = src_array[idx];
      }
    }
    free(src_array);
    new_array[(*array_size)++] = *new_data;

    return new_array;
}

WeatherDataPoint* remove_all_weather_data_point(
WeatherDataPoint *din_array, size_t *array_size) {
  if (din_array != NULL) {
    free(din_array);
    *array_size = 0;
  }
  return NULL;
}
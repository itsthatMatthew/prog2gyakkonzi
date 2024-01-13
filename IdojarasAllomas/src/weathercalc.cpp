/// Weather calculation functions
/// Copyright 1989 Géza

#include <math.h>

// Kriszta: Gézának a régi cuccai, nem merem törölni, nehogy elnrontson valamit

#include "idojaras_szamitasok.h" // Kriszta: átírtam, hogy a miénket használja

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
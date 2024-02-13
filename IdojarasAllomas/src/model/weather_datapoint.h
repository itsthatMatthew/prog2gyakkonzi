#pragma once

#include <time.h>

namespace WeatherStation {

/**
 * \brief A base temperature conversion strategy to convert from celsius to other units of temperature measurement.
 * 
 */
struct TemperatureConversionStrategy {
  static constexpr float convert(float celsius) { return celsius; }
};

/**
 * \brief Calculate heat index (src: https://en.wikipedia.org/wiki/Heat_index#Formula)
 *
 * \param T temperature in degrees celsius
 * \param R relative humidity in percentage
 * \return float the calculated heat index
 */
inline float calcHeatIndex(float T, float R) {
  const float C[] = {-8.78469475556,1.61139411,2.33854883889,-0.14611605,-0.012308094,-0.0164248277778,0.002211732,0.00072546,-0.000003582};
  return C[0] + C[1] * T + C[2] * R + C[3] * T * R + C[4] * T * T + C[5] * R * R + C[6] * T * T * R + C[7] * T * R * R + C[8] * T * T * R * R;
}

class WeatherDatapoint {
public:
  WeatherDatapoint(time_t time, float temperature, float humidity)
    : m_time(time), m_temperature(temperature), m_humidity(humidity) {}

  [[nodiscard]] time_t getTime() { return m_time; }
  template<typename ConvStrat = TemperatureConversionStrategy>
  [[nodiscard]] float getTemperature() { return ConvStrat::convert(m_temperature); }
  [[nodiscard]] float getHumidity() { return m_humidity; }
  template<typename ConvStrat = TemperatureConversionStrategy>
  [[nodiscard]] float getHeatindex() { return ConvStrat::convert(calcHeatIndex(m_temperature, m_humidity)); }
private:
  time_t m_time;
  float m_temperature;
  float m_humidity;
}; // WeatherDatapoint

} // namespace WeatherStation
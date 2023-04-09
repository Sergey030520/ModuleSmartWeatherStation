//
// Created by sergey-athlete on 30.03.23.
//

#ifndef MODULEWEATHERSTATION_ALGORITHMZAMBRETTI_H
#define MODULEWEATHERSTATION_ALGORITHMZAMBRETTI_H

#include <map>
#include <utility>
#include <vector>
#include "Sensor/ISensor.h"

struct WeatherIcon{
    std::string weather;
    std::string pathToImage;
    WeatherIcon(std::string inWeather, std::string inPathToImage):  weather(std::move(inWeather)),
            pathToImage(std::move(inPathToImage)){}
};

enum WeatherStatus{
    ERROR_WEATHER = -1,
    SETTLED_FINE_DROP = 0, FINE_WEATHER_DROP, FINE_BECOMING_LESS_SETTLED, FAIRLY_FINE_SHOWERY_LATER,
    SHOWERY_BECOMING_MORE_UNSETTLED, UNSETTLED_RAIN_LATER, RAIN_AT_TIMES_WORSE_LATER,
    RAIN_AT_TIMES_BECOMING_VERY_UNSETTLED, VERY_UNSETTLED_RAIN_DROP,

    SETTLED_FINE_STABLE, FINE_WEATHER_STABLE, FINE_POSSIBLY_SHOWERS,
    FAIRLY_FINE_SHOWERS_LIKELY, SHOWERY_BRIGHT_INTERVALS, CHANGEABLE_SOME_RAIN,
    UNSETTLED_RAIN_AT_TIMES, RAIN_AT_FREQUENT_INTERVALS, VERY_UNSETTLED_RAIN_STABLE,
    STORMY_MUCH_RAIN_STABLE,

    SETTLED_FINE_RISES, FINE_WEATHER_RISES,BECOMING_FINE,
    FAIRLY_FINE_IMPROVING, FAIRLY_FINE_POSSIBLY_SHOWERS_EARLY, SHOWERY_EARLY_IMPROVING,
    CHANGEABLE_MENDING, RATHER_UNSETTLED_CLEARING_LATER, UNSETTLED_PROBABLY_IMPROVING,
    UNSETTLED_SHORT_FINE_INTERVALS, VERY_UNSETTLED_FINER_AT_TIMES, STORMY_POSSIBLY_IMPROVING,
    STORMY_MUCH_RAIN_RISES
};



#define RANGE_PRESSURE(minPressure, maxPressure, pressure) (minPressure <= pressure && pressure <= maxPressure)

enum PressureStatus{
    DROP, STABLE, RISES
};
enum Season{
    WINTER, SPRING, SUMMER, AUTUMN
};

class AlgorithmZambretti {
    float prePressure;
    float altitude;
    float coefficient = 1.6;
private:
    float normalize(float pressure, float tempC);
    PressureStatus barometry(float bp, Season season);
    float forecast(float  bp, PressureStatus statusBP);
public:
    AlgorithmZambretti(float pressure, float temp, float altitude);
    WeatherStatus engine(float pressureMBar, float tempC, Season season);
    static WeatherIcon forecastProcessing(WeatherStatus status, float temp);
    static Season getSeasonByMonth(int month);
};


#endif //MODULEWEATHERSTATION_ALGORITHMZAMBRETTI_H

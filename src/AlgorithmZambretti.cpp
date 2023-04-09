#include "../include/AlgorithmZambretti.h"
#include <math.h>

using namespace std;

AlgorithmZambretti::AlgorithmZambretti(float pressure, float temp, float altitude): altitude(altitude){
    prePressure = normalize(pressure, temp);


}

float AlgorithmZambretti::normalize(float pressure, float tempC) {
    auto value = 1-((0.0065 * altitude) / (tempC + (0.0065 * altitude) + 273.15));
    return (float)(pressure* pow(value, -5.257));
}

PressureStatus AlgorithmZambretti::barometry(float bp, Season season) {
    float delta = bp - prePressure;
    switch (season) {
        case WINTER:{
            if(delta <= -coefficient && RANGE_PRESSURE(996, 1070, bp)){
                return DROP;
            }else if(delta >= coefficient && RANGE_PRESSURE(957, 1020, bp)){
                return RISES;
            }else{
                return STABLE;
            }
        }
        case SPRING:{
            if(delta <= coefficient && RANGE_PRESSURE(980, 1060, bp)){
                return DROP;
            }else if(delta <= coefficient && RANGE_PRESSURE(950, 1030, bp)){
                return RISES;
            }else{
                return STABLE;
            }
        }
        case SUMMER:{
            if(delta <= coefficient && RANGE_PRESSURE(970, 1050, bp)){
                return DROP;
            }else if(delta <= coefficient && RANGE_PRESSURE(947, 1030, bp)){
                return RISES;
            }else{
                return STABLE;
            }
        }
        case AUTUMN:{
            if(delta <= coefficient && RANGE_PRESSURE(975, 1060, bp)){
                return DROP;
            }else if(delta <= coefficient && RANGE_PRESSURE(950, 1030, bp)){
                return RISES;
            }else{
                return STABLE;
            }
        }
    }
    return STABLE;
}

float AlgorithmZambretti::forecast(float bp, PressureStatus statusBP) {
    switch(statusBP){
        case DROP:{
            return (float)(130.f - 0.12f * bp);
        }
        case STABLE:{
            return (float)(144.f - 0.13f * bp);
        }
        case RISES:{
            return (float)(185.f - 0.16f * bp);
        }
        default:{
            return -1;
        }
    }
}

WeatherStatus AlgorithmZambretti::engine(float pressureMBar, float tempC, Season season) {
    float bp = normalize(pressureMBar, tempC);
    PressureStatus statusBP = barometry(bp, season);
    float forecastValue = forecast(bp, statusBP);
    prePressure = bp;
    return (WeatherStatus)--forecastValue;
}

WeatherIcon AlgorithmZambretti::forecastProcessing(WeatherStatus status, float temp) {
    switch(status){
        case SETTLED_FINE_DROP:{
            if(temp <= -8){
                return {"Fine Weather",
                        ":images/freezing.png"};
            }else if(temp >= 26){
                return {"Fine Weather",
                        ":images/hot.png"};
            }else {
                return {"Fine Weather",
                        ":images/sun.png"};
            }
        }
        case FINE_WEATHER_DROP:{
            if(temp <= -8){
                return {"Settled Fine",
                        ":images/freezing.png"};
            }else if(temp >= 26){
                return {"Settled Fine",
                        ":images/hot.png"};
            }else {
                return {"Settled Fine",
                        ":images/images/sun.png"};
            }
        }
        case FINE_BECOMING_LESS_SETTLED:{
            if(temp <= 0){
                return {"Fine, Becoming Less Settled",
                        ":images/snowy.png"};
            }else {
                return {"Fine, Becoming Less Settled",
                        ":images/rainfall_stormy_weather.png"};
            }
        }
        case FAIRLY_FINE_SHOWERY_LATER:{
            if(temp <= 0){
                return {"Fine, Becoming Less Settled",
                        ":images/snowy.png"};
            }else {
                return {"Fairly Fine, Snow Coming Latter",
                        ":images/sunny_rain_later.png"};
            }
        }
        case SHOWERY_BECOMING_MORE_UNSETTLED:{
            if(temp <= 0){
                return {"Snowy, Becoming More Unsettled",
                        ":images/snow.png"};
            }else{
                return {"Showery, Becoming More Unsettled",
                        ":images/rain-weather.png"};
            }
        }
        case UNSETTLED_RAIN_LATER:{
            if(temp <= 0) {
                return {"Unsettled, Snow Later",
                        ":images/snow_fickle_weather.png"};
            }else{
                return {"Unsettled, Rain Later",
                        ":images/sunny_rain_later.png"};
            }
        }
        case RAIN_AT_TIMES_WORSE_LATER:{
            if(temp <= 0) {
                return {"Snow at Times, Worse Later",
                        ":images/snow_fickle_weather.png"};
            }else{
                return {"Rain at Times, Worse Later",
                        ":images/storm-rain-thunder-day.png"};
            }
        }
        case RAIN_AT_TIMES_BECOMING_VERY_UNSETTLED:{
            if(temp <= 0) {
                return {"Snow at Times, Becoming Very Unsettled",
                        ":images/snow_fickle_weather.png"};
            }else{
                return {"Rain at Times, Becoming Very Unsettled",
                        ":images/storm-rain-thunder-day.png"};
            }
        }
        case VERY_UNSETTLED_RAIN_DROP:{
            if(temp <= 0) {
                return {"Very Unsettled, Rain",
                        ":images/cloudy_stormy.png"};
            }else{
                return {"Very Unsettled, Rain",
                        ":images/cloudy_stormy.png"};
            }
        }
        case SETTLED_FINE_STABLE:{
            if(temp <= -8){
                return {"Settled Fine",
                        ":images/freezing.png"};
            }else if(temp >= 26){
                return {"Settled Fine",
                        ":images/hot.png"};
            }else {
                return {"Settled Fine",
                        ":images/sun.png"};
            }
        }
        case FINE_WEATHER_STABLE:{
            if(temp <= -8){
                return {"Fine Weather",
                        ":images/freezing.png"};
            }else if(temp >= 26){
                return {"Fine Weather",
                        ":images/hot.png"};
            }else {
                return {"Fine Weather",
                        ":images/sun.png"};
            }
        }
        case FINE_POSSIBLY_SHOWERS:{
            if(temp <= 0) {
                return {"Fine, Possibly Snow",
                        ":images/snowy.png"};
            }else{
                return {"Fine, Possibly Showers",
                        ":images/sunny_rain_later.png"};
            }
        }
        case FAIRLY_FINE_SHOWERS_LIKELY:{
            if(temp <= 0) {
                return {"Fairly Fine, Snow Likely",
                        ":images/snowy.png"};
            }else{
                return {"Fairly Fine, Showers Likely",
                        ":images/sunny_rain_later.png"};
            }
        }
        case SHOWERY_BRIGHT_INTERVALS:{
            if(temp <= 0) {
                return {"Snowy, Bright Intervals",
                        ":images/snowy.png"};
            }else{
                return {"Showery, Bright Intervals",
                        ":images/sunny_rain_later.png"};
            }
        }
        case CHANGEABLE_SOME_RAIN:{
            if(temp <= 0) {
                return {"Changeable, Some Snow",
                        ":images/snowy.png"};
            }else{
                return {"Changeable, Some Rain",
                        ":images/sunny_rain_later.png"};
            }
        }
        case UNSETTLED_RAIN_AT_TIMES:{
            if(temp <= 0) {
                return {"Unsettled, Snow at Times",
                        ":images/snow_fickle_weather.png"};
            }else{
                return {"Unsettled, Rain at Times",
                        ":images/rain-weather.png"};
            }
        }
        case RAIN_AT_FREQUENT_INTERVALS:{
            if(temp <= 0) {
                return {"Snow at Frequent Intervals",
                        ":images/snow.png"};
            }else{
                return {"Rain at Frequent Intervals",
                        ":images/rain-weather.png"};
            }
        }
        case VERY_UNSETTLED_RAIN_STABLE:{
            if(temp <= 0) {
                return {"Very Unsettled, Snow",
                        ":images/snow.png"};
            }else{
                return {"Very Unsettled, Rain",
                        ":images/rain-weather.png"};
            }
        }
        case STORMY_MUCH_RAIN_STABLE:{
            if(temp <= 0) {
                return {"Stormy, Much Snow",
                        ":images/snow.png"};
            }else{
                return {"Stormy, Much Rain",
                        ":images/lightening-storm.png"};
            }
        }
        case SETTLED_FINE_RISES:{
            if(temp <= -8){
                return {"Settled Fine",
                        ":images/freezing.png"};
            }else if(temp >= 26){
                return {"Settled Fine",
                        ":images/hot.png"};
            }else {
                return {"Settled Fine",
                        ":images/sun.png"};
            }
        }
        case FINE_WEATHER_RISES:{
            if(temp <= -8){
                return {"Settled Fine",
                        ":images/freezing.png"};
            }else if(temp >= 26){
                return {"Settled Fine",
                        ":images/hot.png"};
            }else {
                return {"Settled Fine",
                        ":images/sun.png"};
            }
        }
        case BECOMING_FINE:{
            if(temp <= -8){
                return {"Becoming Fine",
                        ":images/freezing.png"};
            }else if(temp >= 26){
                return {"Becoming Fine",
                        ":images/hot.png"};
            }else {
                return {"Becoming Fine",
                        ":images/sun.png"};
            }
        }
        case FAIRLY_FINE_IMPROVING:{
            return {"Fairly Fine, Improving",
                    ":images/sun.png"};
        }
        case FAIRLY_FINE_POSSIBLY_SHOWERS_EARLY: {
            if (temp <= 0) {
                return {"Fairly Fine, Possibly Showers Early",
                        ":images/snowy.png"};
            } else {
                return {"Fairly Fine, Possibly Showers Early",
                        ":images/sunny_rain.png"};
            }
        }
        case SHOWERY_EARLY_IMPROVING:{
            if (temp <= 0) {
                return {"Snowfall, Improving",
                        ":images/snowy.png"};
            } else {
                return {"Showery Early, Improving",
                        ":images/sunny_rain.png"};
            }
        }
        case CHANGEABLE_MENDING:{
            return {"Changeable, Mending",
                    ":images/snow_fickle_weather.png"};
        }
        case RATHER_UNSETTLED_CLEARING_LATER:{
            if (temp <= 0) {
                return {"Rather Unsettled, Clearing Later",
                        ":images/images/snowy.png"};
            } else {
                return {"Rather Unsettled, Clearing Later",
                        ":images/snow_fickle_weather.png"};
            }
        }
        case UNSETTLED_PROBABLY_IMPROVING: {
            if (temp <= 0) {
                return {"Unsettled, Probably Improving",
                        ":images/snowy.png"};
            } else {
                return {"Unsettled, Probably Improving",
                        ":images/snow_fickle_weather.png"};
            }
        }
        case UNSETTLED_SHORT_FINE_INTERVALS:{
            if (temp <= 0) {
                return {"Unsettled, Short Fine Intervals",
                        ":images/snowy.png"};
            } else {
                return {"Unsettled, Short Fine Intervals",
                        ":images/rainfall_stormy_weather.png"};
            }
        }
        case VERY_UNSETTLED_FINER_AT_TIMES:{
            return {"Very Unsettled, Finer at Times",
                           ":images/cloudy_stormy.png"};
        }
        case STORMY_POSSIBLY_IMPROVING:{
            if(temp <= 0) {
                return {"Stormy, Possibly Improving",
                        ":images/snow.png"};
            }else{
                return {"Stormy, Possibly Improving",
                        ":images/lightening-storm.png"};
            }
        }
        case STORMY_MUCH_RAIN_RISES:{
            if(temp <= 0) {
                return {"Stormy, Much Snow",
                        ":images/snow.png"};
            }else{
                return {"Stormy, Much Rain",
                        ":images/lightening-storm.png"};
            }
        }
        default:{
            return {"weather-unknown",""};
        }
    }
}

Season AlgorithmZambretti::getSeasonByMonth(int month) {
    if(month == 11 || month == 12 || (month >= 1 && month <= 3)){
        return WINTER;
    }else if(month == 4 || month == 5){
        return SPRING;
    }else if(month >= 6 && month <= 8){
        return SUMMER;
    }else{
        return AUTUMN;
    }
}

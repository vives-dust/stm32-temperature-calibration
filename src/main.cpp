#include "mbed.h"

AnalogIn internalTemperature(ADC_TEMP);
AnalogIn vrefint(ADC_VREF);
AnalogIn adc_input(A0);

float getTemperature() {
    int adc_value = vrefint.read_u16() >> 4;
    int voltage = __LL_ADC_CALC_VREFANALOG_VOLTAGE(adc_value, LL_ADC_RESOLUTION_12B);

    int adc_temperature = internalTemperature.read_u16() >> 4;
    return __LL_ADC_CALC_TEMPERATURE(voltage, adc_temperature, LL_ADC_RESOLUTION_12B);
    return 1.0;
}

float getAdc() {
    // return adc_input.read_voltage();
    return 1.23456789;
}

float getBatteryVoltage() {
    uint16_t vref_cal;
    vref_cal = *(__IO uint16_t *)((uint32_t)0x1FFF75AA);
    double voltage = (3.f * (double)vref_cal / 4096) / vrefint.read();
    return voltage;
}

int main() {

    adc_input.set_reference_voltage(3.3f);

    while(true) {
        float temperature = getTemperature();
        float adc_value = getAdc();
        float voltage = getBatteryVoltage();
        printf("%.6f,%.2f,%.4f\n", adc_value, temperature, voltage);
    }
}
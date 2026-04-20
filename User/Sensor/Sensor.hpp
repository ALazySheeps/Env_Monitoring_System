#ifndef __SENSOR_HPP
#define __SENSOR_HPP

#include "main.h"
#include <string.h>

extern float measuredRefVoltage;

#define V25 1.43f // 25°C 时的传感器电压
#define Avg_Slope 0.0043f // 平均斜率 (mV

class Sensor {
protected:
    int16_t raw_data;
    float data;
public:
    uint8_t name[20];
    uint8_t id;
    Sensor(uint8_t* name, uint8_t id) : raw_data(0), data(0.0f), id(id)
    {
        memcpy(this->name, name, 20);
    }
    virtual ~Sensor() = default;
    virtual void setRawData(int16_t raw_data)
    {
        this->raw_data = raw_data;
    }
    virtual float getData()
    {
        // 默认实现，直接返回原始数据
        return static_cast<float>(raw_data);
    }
};

class LightSensor : public Sensor {
public:
    LightSensor(uint8_t* name, uint8_t id) : Sensor(name, id) {}
    float getData() override
    {
        // Convert raw_data to light intensity
        data = static_cast<float>(raw_data)*100.0f/4095.0f; 
        return data;
    }
};


class TemperatureSensor : public Sensor {
private:
    static constexpr int AVG_COUNT = 20;
    float history[AVG_COUNT];
    int history_index = 0;
    int history_filled = 0;
public:
    TemperatureSensor(uint8_t* name, uint8_t id) : Sensor(name, id)
    {
        memset(history, 0, sizeof(history));
    }

    void setRawData(int16_t raw_data) override
    {
        Sensor::setRawData(raw_data);
        float temp = static_cast<float>(raw_data) / 100.0f;
        history[history_index] = temp;
        history_index = (history_index + 1) % AVG_COUNT;
        if (history_filled < AVG_COUNT) {
            history_filled++;
        }
    }

    float getData() override
    {
        float sum = 0.0f;
        int count = history_filled > 0 ? history_filled : 1;
        for (int i = 0; i < history_filled; i++) {
            sum += history[i];
        }
        data = sum / count;
        return data;
    }
};

class GrayscaleSensor : public Sensor {
public:
    GrayscaleSensor(uint8_t* name, uint8_t id) : Sensor(name, id) {}
    float getData() override
    {
        // Convert raw_data to grayscale value
        data = static_cast<float>(raw_data)*100.0f/4095.0f;
        return data;
    }
};

// 内部电压参考传感器
class RefintSensor : public Sensor {
public:
    RefintSensor(uint8_t* name, uint8_t id) : Sensor(name, id) {}
    void setRawData(int16_t raw_data) override
    {
        Sensor::setRawData(raw_data);
        measuredRefVoltage = getData();
    }
    float getData() override
    {
        // Convert raw_data to reference voltage Vdda
        data = 1.20f * 4095.0f / static_cast<float>(raw_data);
        return data;
    }
};

class InternalTemperatureSensor : public Sensor {
private:
    static constexpr int AVG_COUNT = 20;
    float history[AVG_COUNT];
    int history_index = 0;
    int history_filled = 0;
public:
    InternalTemperatureSensor(uint8_t* name, uint8_t id) : Sensor(name, id)
    {
        memset(history, 0, sizeof(history));
    }

    void setRawData(int16_t raw_data) override
    {
        Sensor::setRawData(raw_data);
        float vol_sensor = static_cast<float>(raw_data) * measuredRefVoltage / 4095.0f;
        history[history_index] = (V25 - vol_sensor) / Avg_Slope + 25.0f;
        history_index = (history_index + 1) % AVG_COUNT;
        if (history_filled < AVG_COUNT) {
            history_filled++;
        }
    }

    float getData() override
    {
        float sum = 0.0f;
        int count = history_filled > 0 ? history_filled : 1;
        for (int i = 0; i < history_filled; i++) {
            sum += history[i];
        }
        data = sum / count;
        return data;
    }
};

// 外部电压参考传感器
class VrefSensor : public Sensor {
public:
    VrefSensor(uint8_t* name, uint8_t id) : Sensor(name, id) {}
    float getData() override
    {
        // Convert raw_data to temperature in Celsius
        data = static_cast<float>(raw_data)*3.3f/4095.0f; 
        return data;
    }
};

class Sensors {
private:
    Sensor** sensors;   // 传感器指针数组
    uint16_t* adc_buf;

public:
    uint8_t count;

    Sensors(uint8_t count) : adc_buf(nullptr), count(count)
    {
        // 分配指针数组
        sensors = new Sensor*[count];
        for (int i = 0; i < count; i++) {
            sensors[i] = nullptr; // 初始化为 nullptr
        }
        adc_buf = new uint16_t[count];
        for (int i = 0; i < count; i++) {
            adc_buf[i] = 0; // 初始化 ADC 缓冲区
        }
    }

    // 获取 ADC 缓冲区指针
    uint16_t* getAdcBuf()
    {
        return adc_buf;
    }

    // 设置传感器原始数据(该函数放在DMA中断回调)
    void update()
    {
        for(int i = 0; i < count; i++)
        {
            sensors[i]->setRawData(adc_buf[i]);
        }
    }

    // 添加传感器
    void addSensor(uint8_t index, Sensor* sensor)
    {
        if (index < count) {
            sensors[index] = sensor;
        }
    }

    // 读取传感器数据
    float getSensor(uint8_t index)
    {
        if (index < count)
            return sensors[index]->getData();
        return 0;
    }

    ~Sensors()
    {
        // 释放所有指针
        for (int i = 0; i < count; i++) {
            delete sensors[i];
        }
        delete[] sensors;
    }
};


#endif /* __SENSOR_HPP */

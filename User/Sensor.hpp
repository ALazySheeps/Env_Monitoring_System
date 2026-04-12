#ifndef __SENSOR_HPP
#define __SENSOR_HPP

#include "main.h"
#include <string.h>

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
    void setRawData(int16_t raw_data)
    {
        this->raw_data = raw_data;
    }
    virtual float getData()
    {
        // 默认实现，直接返回原始数据
        return static_cast<float>(raw_data);
    }
};

class TemperatureSensor : public Sensor {
public:
    TemperatureSensor(uint8_t* name, uint8_t id) : Sensor(name, id) {}
    float getData() override
    {
        // Convert raw_data to temperature in Celsius
        data = (raw_data / 1024.0f) * 100.0f; // Example conversion
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

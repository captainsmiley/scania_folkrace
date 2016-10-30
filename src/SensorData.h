/*
 * SensorData.h
 *
 *  Created on: 30 okt. 2016
 *      Author: tgtob
 */

#ifndef SRC_SENSORDATA_H_
#define SRC_SENSORDATA_H_

#include <Arduino.h>

template <class T>
class SensorData {
public:
	SensorData(T len);
	void add(T data);
	T get();
	T get(uint16_t n) const;
	T getAvg(uint16_t n) const;
	virtual ~SensorData();
private:
	T *m_data;
	uint16_t m_len;
	uint16_t m_pos;
};

#include <SensorData.tpp>

#endif /* SRC_SENSORDATA_H_ */

/*
 * SensorData.cpp
 *
 *  Created on: 30 okt. 2016
 *      Author: tgtob
 */

#include <SensorData.h>

template <class T>
SensorData<T>::SensorData(T len) :
m_data( (T*) calloc(len,sizeof(T))),
m_len(len),
m_pos(0)
{
	// TODO Auto-generated constructor stub

}

template <class T>
void SensorData<T>::add(T data)
{
	m_pos++;
	if (m_pos>=m_len) m_pos = 0;
//	noInterrupts();
	cli();
	*(m_data + m_pos) = data;
	sei();
//	interrupts();
}
template <class T>
T SensorData<T>::get(uint16_t n) const
{
	uint16_t pos;
	if (n>m_pos) pos = m_len - (n-m_pos);
	else pos = m_pos - n;

	cli();
	T data = *(m_data+pos);
	sei();
	return data;
}

template <class T>
T SensorData<T>::getAvg(uint16_t n) const
{
	T res = 0;
	for(int i=0;i<n;++i) res += get(i);
	return res/n;
}

template <class T>
T SensorData<T>::getAvg(uint16_t n, uint16_t t) const
{
	T res = 0;
	for(int i=0;i<n;++i) res += get(i+t);
	return res/n;
}

template <class T>
T SensorData<T>::get()
{
	cli();
	T data = *(m_data+m_pos);
	sei();
	return data;
}

template <class T>
T SensorData<T>::getDev(uint16_t n) const
{
	T dev = 0;
	uint16_t avg = getAvg(n);
	for(int i=0;i<n;++i)
	{
		dev += abs( ((int)get(i)) - ( (int) avg ));
	}
	return dev/n;
}

template <class T>
SensorData<T>::~SensorData() {
	// TODO Auto-generated destructor stub
}


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>


using namespace std;

enum class SensorType
{
	Altitude,
	SpeedInKmh,
	FuelConsumption
};

class SensorData
{
	float value;
	SensorType sensorType;
	time_t time;
public:
	SensorType GetSensorType() { return sensorType; }
	float GetValue() { return value; }
	void SetValue(float v) { value = v; }
	time_t GetTime() { return time; }
	SensorData(SensorType sensorType, float value, time_t time)
	{
		this->value = value;
		this->sensorType = sensorType;
		this->time = time;
	}
};


void FillData(vector<SensorData> &v);
time_t CreateTime(int year, int month, int day, int hour, int minute, int second);
int main()
{
	vector<SensorData> v;
	FillData(v);

	int c = 0;

	for (int i = 0; i < (int)v.size(); i++)
	{
		if (v[i].GetSensorType() == SensorType::Altitude)
		{
			time_t a = CreateTime(2012, 1, 2, 0, 0, 0);
			time_t b = CreateTime(2012, 1, 3, 0, 0, 0);

			if (v[i].GetTime() >= a && v[i].GetTime() < b)
			{
				c++;
			}
		}
	}

	cout << "Antal Altitude-registreringar 2012-01-02: " << c << "\n";

	int f = 0;

	for (int i = 0; i < (int)v.size(); i++)
	{
		if (v[i].GetSensorType() == SensorType::SpeedInKmh)
		{
			if (v[i].GetValue() > 99.9f)
			{
				f = 1;
			}
		}
	}

	if (f == 1)
		cout << "Maxhastighet uppnådd\n";
	else
		cout << "Ingen maxhastighet uppnådd\n";

	for (int i = 0; i < (int)v.size(); i++)
	{
		if (v[i].GetSensorType() == SensorType::FuelConsumption)
		{
			float x = v[i].GetValue();
			x = x * 1.75f;
			v[i].SetValue(x);
		}
	}
}



void FillData(vector<SensorData>& v)
{
	srand(time(NULL));

	time_t tid = CreateTime(2012, 1, 1, 1, 1, 1 );
	for (int i = 0; i < 100000; i++)
	{
		SensorType type = static_cast<SensorType>(rand() % 3);
		float value = 0.0f;
		if (type == SensorType::Altitude)
			value = rand() % 1000;
		else if (type == SensorType::FuelConsumption)
			value = rand() * 3.0f;
		else if (type == SensorType::SpeedInKmh)
			value = rand() % 110;
		else
		{
			value = 99;
		}
		v.push_back(SensorData(type,value,tid));
		tid = tid + rand() % 10 + 1;
	}
}

time_t CreateTime(int year, int month, int day, int hour, int minute, int second)
{
	struct tm tid = { 0 };
	tid.tm_year = year-1900;
	tid.tm_mon = month - 1;
	tid.tm_mday = day;
	tid.tm_hour = hour;
	tid.tm_min = minute;
	tid.tm_sec = second;
	return mktime(&tid);
}
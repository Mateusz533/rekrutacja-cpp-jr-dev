#pragma once

template<typename T>
class IPersistanceController {
public:
	virtual ~IPersistanceController() {};
	virtual bool fetchData(T& buffer) = 0;
	virtual bool saveData(const T& data) = 0;
	virtual bool saveDataAs(const T& data) = 0;
};

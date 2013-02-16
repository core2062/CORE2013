#ifndef DECIMALDATA_H
#define DECIMALDATA_H

#include <iomanip>
#include <string>
#include "DisplayData.h"

namespace insight
{

class DecimalData : public DisplayData
{
public:
	DecimalData();
	DecimalData(std::string, int precision = 2);
	virtual std::string getFormattedString(char);
	
	void setData(float);
	void setHeader(std::string);
	void setPrecision(int);
	
private:
	std::string m_decimalHeader;
	float m_decimalData;
	int m_precision;
	
	std::string m_formattedString;
	bool m_updateString;
};
}
#endif

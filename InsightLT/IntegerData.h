#ifndef INTEGERDATA_H
#define INTEGERDATA_H

#include <iomanip>
#include <string>
#include "DisplayData.h"

namespace insight
{

class IntegerData : public DisplayData
{
public:
	IntegerData();
	IntegerData(std::string);
	virtual std::string getFormattedString(char);
	
	void setData(int);
	void setHeader(std::string);
	
private:
	std::string m_integerHeader;
	int m_integerData;
	
	std::string m_formattedString;
	bool m_updateString;
};
}
#endif

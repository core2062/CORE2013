#ifndef STRINGDATA_H
#define STRINGDATA_H

#include <iomanip>
#include <string>
#include "DisplayData.h"

namespace insight
{

class StringData : public DisplayData
{
public:
	StringData();
	StringData(std::string);
	virtual std::string getFormattedString(char);
	
	void setData(std::string);
	void setHeader(std::string);
	
private:
	std::string m_stringHeader;
	std::string m_stringData;
	
	std::string m_formattedString;
	bool m_updateString;
};
}
#endif

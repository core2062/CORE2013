#include <string>
#include <sstream>
#include "IntegerData.h"

using namespace std;
using namespace insight;

/* Constructor
 * 
 */
IntegerData::IntegerData()
{
	m_integerData = 0;
}

/* Construct to define header
 * 
 * header - header string, left justified in the zone
 */
IntegerData::IntegerData(std::string header)
{
	m_integerHeader = m_integerHeader;
	m_integerData = 0;
}

/* Get the formatted string for the zone
 * 
 * lengthOfZone - lenght to format to
 * 
 */
std::string IntegerData::getFormattedString(char lengthOfZone)
{
	if(m_updateString)
	{
		ostringstream oss;
		oss << m_integerData;
		string tmpString = oss.str();
		m_formattedString.clear();
		m_updateString = false;
		if(m_integerHeader.length() + tmpString.length() > lengthOfZone)
		{
			
			if(tmpString.length() > lengthOfZone)
			{
				tmpString.erase(tmpString.end() - (tmpString.length() - lengthOfZone), tmpString.end());
			}
			m_formattedString = m_integerHeader.substr(0, lengthOfZone - tmpString.length()) + tmpString;
		}
		else
		{
			m_formattedString = m_integerHeader + string(lengthOfZone - (m_integerHeader.length() + tmpString.length()), ' ').
							append(tmpString);
		}	
	}		
	return m_formattedString;
}

/* Set the data. This is called to set the data, as the display runs
 * the updated values will be displayed
 * 
 * data - the data to display
 * 
 */
void IntegerData::setData(int data)
{
	m_updateString = true;
	m_integerData = data;
}

/* Set the header. This is called to set or change the header, as the display
 * runs the updated value will be displayed
 * 
 * header - data description to display
 */
void IntegerData::setHeader(string header)
{
	m_updateString = true;
	m_integerHeader.clear();
	m_integerHeader = header;
}

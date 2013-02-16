#include <string>
#include "StringData.h"

using namespace std;
using namespace insight;

/* Constructor
 * 
 */
StringData::StringData()
{
	
}

/* Construct to define header
 * 
 * header - header string, left justified in the zone
 */
StringData::StringData(string header)
{
	setHeader(header);
}

/* Get the formatted string for the zone
 * 
 * lengthOfZone - lenght to format to
 * 
 */
std::string StringData::getFormattedString(char lengthOfZone)
{
	if(m_updateString)
	{
		m_formattedString.clear();
		m_updateString = false;
		if(m_stringHeader.length() + m_stringData.length() > lengthOfZone)
		{
			string tmpString = m_stringData;
			if(m_stringData.length() > lengthOfZone)
			{
				tmpString.erase(tmpString.end() - (tmpString.length() - lengthOfZone), tmpString.end());
			}
			m_formattedString = m_stringHeader.substr(0, lengthOfZone - tmpString.length()) + tmpString;
		}
		else
		{
			m_formattedString = m_stringHeader + string(lengthOfZone - (m_stringHeader.length() + m_stringData.length()), ' ').
							append(m_stringData);
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
void StringData::setData(string data)
{
	m_updateString = true;
	m_stringData.clear();
	m_stringData = data;
}

/* Set the header. This is called to set or change the header, as the display
 * runs the updated value will be displayed
 * 
 * header - data description to display
 */
void StringData::setHeader(string header)
{
	m_updateString = true;
	m_stringHeader.clear();
	m_stringHeader = header;
}

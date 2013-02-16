#include "DecimalData.h"
#include <iomanip>
#include <sstream>

using namespace std;
using namespace insight;

/* Constructor
 * 
 */
DecimalData::DecimalData()
{
	m_precision = 2;
	m_decimalData = 0;
}

/* Construct to define header
 * 
 * header - header string, left justified in the zone
 * precision - number of decimal places to display
 */
DecimalData::DecimalData(string header, int precision)
{
	m_decimalHeader = header;
	m_precision = precision;
	m_decimalData = 0;
}

/* Get the formatted string for the zone
 * 
 * lengthOfZone - lenght to format to
 * 
 */
string DecimalData::getFormattedString(char lengthOfZone)
{
	if(m_updateString)
	{
		ostringstream oss;
		oss.setf(ios::fixed,ios::floatfield); 
		oss.precision(m_precision);
		oss << m_decimalData;
		string tmpString = oss.str();
		m_formattedString.clear();
		m_updateString = false;
		if(m_decimalHeader.length() + tmpString.length() > lengthOfZone)
		{
			
			if(tmpString.length() > lengthOfZone)
			{
				tmpString.erase(tmpString.end() - (tmpString.length() - lengthOfZone), tmpString.end());
			}
			m_formattedString = m_decimalHeader.substr(0, lengthOfZone - tmpString.length()) + tmpString;
		}
		else
		{
			m_formattedString = m_decimalHeader + string(lengthOfZone - (m_decimalHeader.length() + tmpString.length()), ' ').
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
void DecimalData::setData(float data)
{
	m_updateString = true;
	m_decimalData = data;
}

/* Set the header. This is called to set or change the header, as the display
 * runs the updated value will be displayed
 * 
 * 
 */
void DecimalData::setHeader(string header)
{
	m_updateString = true;
	m_decimalHeader = header;
}

/* Set the precision to display the data at
 * 
 * precision - decimal places to display
 */
void DecimalData::setPrecision(int precision)
{
	m_updateString = true;
	m_precision = precision;
}

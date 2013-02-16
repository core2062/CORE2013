InsightLT_CPP
=============

CPP implementation of the InsightLT API


Welcome and thank you for your interest in the InsightLT robot diagnostic 
display.

This is the initial release of code and documentation and will probably be 
updated frequently. Please check the repository for the latest code updates and 
bug fixes.

To report a bug, please log an issue on git hub to have it resolved in a timely
manner. Make sure to include you email address so any details may be collected
to fix the issue.

How To Add the Code to your WindRiver Project
---------------------------------------------
The InsightLT project is a collection of source files.

The easiest way to currently add Insight to your project is as follows.
1)Create a new folder in your project and name it "InsightLT"

2)Copy all of the source files into this folder.(.h and .cpp)

Alternatively you could just add the source files to your project in the
current source folder.


To use the InsightLT objects you will need to include them like so...
#include "InsightLT/InsightLT.h" 
(note: the first InsightLT is the name of the folder in the previous step)

An explanation of using the Zones and configurations is in the file
"DisplayConfigurations.txt"
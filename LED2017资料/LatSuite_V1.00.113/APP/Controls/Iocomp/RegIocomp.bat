
@ECHO OFF
REM =================================================================
REM Iocomp Software ActiveX Registration Batch File
REM Copyright 1998-2001 Iocomp Software
REM http://www.icomp.com
REM Last Modified: November 20, 2001
REM =================================================================
REM This batch file will register our current set of ActiveX controls
REM on Windows 32-bit systems as of the date of this writing.
REM Windows 95/98/ME/NT40/2000/XP
REM =================================================================

:Begin
Echo.
Echo 正在注册部件...,Attempting to Register ActiveX components...
Echo.

:DeterminePaths
REM Initialize variables
SET AnalogSystem=
SET DigitalSystem=
SET StripSystem=
SET ProfSystem=
SET PlotSystem=
SET ComponentFound=

REM Find path to all components
IF EXIST %WINDIR%\SYSTEM\iPlotLibrary.ocx (
	DEL %WINDIR%\SYSTEM\iPlotLibrary.ocx
)
IF EXIST %WINDIR%\SYSTEM\iProfessionalLibrary.ocx (
	DEL %WINDIR%\SYSTEM\iProfessionalLibrary.ocx
)
IF EXIST %WINDIR%\SYSTEM\iProfessionalLibrary_original.ocx (
	DEL %WINDIR%\SYSTEM\iProfessionalLibrary_original.ocx
)
IF EXIST %WINDIR%\SYSTEM\isAnalogLibrary.ocx (
	DEL %WINDIR%\SYSTEM\isAnalogLibrary.ocx
)
IF EXIST %WINDIR%\SYSTEM\isDigitalLibrary.ocx (
	DEL %WINDIR%\SYSTEM\isDigitalLibrary.ocx
)
IF EXIST %WINDIR%\SYSTEM\iStripChartXControl.ocx (
	DEL %WINDIR%\SYSTEM\iStripChartXControl.ocx
)
XCOPY iPlotLibrary.ocx %WINDIR%\SYSTEM\
XCOPY iProfessionalLibrary.ocx %WINDIR%\SYSTEM\
XCOPY iProfessionalLibrary_original.ocx %WINDIR%\SYSTEM\
XCOPY isAnalogLibrary.ocx %WINDIR%\SYSTEM\
XCOPY isDigitalLibrary.ocx %WINDIR%\SYSTEM\
XCOPY iStripChartXControl.ocx %WINDIR%\SYSTEM\
IF EXIST %WINDIR%\SYSTEM\isAnalogLibrary.ocx SET AnalogSystem=%WINDIR%\SYSTEM
IF EXIST %WINDIR%\SYSTEM\isDigitalLibrary.ocx SET DigitalSystem=%WINDIR%\SYSTEM
IF EXIST %WINDIR%\SYSTEM\iStripChartXControl.ocx SET StripSystem=%WINDIR%\SYSTEM
IF EXIST %WINDIR%\SYSTEM\iProfessionalLibrary.ocx SET ProfSystem=%WINDIR%\SYSTEM
IF EXIST %WINDIR%\SYSTEM\iPlotLibrary.ocx SET PlotSystem=%WINDIR%\SYSTEM
IF EXIST %WINDIR%\SYSTEM32\isAnalogLibrary.ocx SET AnalogSystem=%WINDIR%\SYSTEM32
IF EXIST %WINDIR%\SYSTEM32\isDigitalLibrary.ocx SET DigitalSystem=%WINDIR%\SYSTEM32
IF EXIST %WINDIR%\SYSTEM32\iStripChartXControl.ocx SET StripSystem=%WINDIR%\SYSTEM32
IF EXIST %WINDIR%\SYSTEM32\iProfessionalLibrary.ocx SET ProfSystem=%WINDIR%\SYSTEM32
IF EXIST %WINDIR%\SYSTEM32\iPlotLibrary.ocx SET PlotSystem=%WINDIR%\SYSTEM32



REM Check to see if any component was found
IF NOT "%AnalogSystem%"=="" SET ComponentFound=YES
IF NOT "%DigitalSystem%"=="" SET ComponentFound=YES
IF NOT "%StripSystem%"=="" SET ComponentFound=YES
IF NOT "%ProfSystem%"=="" SET ComponentFound=YES
IF NOT "%PlotSystem%"=="" SET ComponentFound=YES

Rem Produce error if no components were found
IF "%ComponentFound%"=="YES" GOTO Register
GOTO Error

:Register
IF NOT "%AnalogSystem%"=="" Echo Registering Analog Library...
IF NOT "%AnalogSystem%"=="" regsvr32 /s /c %AnalogSystem%\isAnalogLibrary.ocx
IF NOT "%DigitalSystem%"=="" Echo Registering Digital Library...
IF NOT "%DigitalSystem%"=="" regsvr32 /s /c %DigitalSystem%\isDigitalLibrary.ocx
IF NOT "%StripSystem%"=="" Echo Registering Strip Chart Control...
IF NOT "%StripSystem%"=="" regsvr32 /s /c %StripSystem%\iStripChartXControl.ocx
IF NOT "%ProfSystem%"=="" Echo Registering Professional Library...
IF NOT "%ProfSystem%"=="" regsvr32 /s /c %ProfSystem%\iProfessionalLibrary.ocx
IF NOT "%PlotSystem%"=="" Echo Registering Plot Library...
IF NOT "%PlotSystem%"=="" regsvr32 /s /c %PlotSystem%\iPlotLibrary.ocx
GOTO COMPLETE

:ERROR
Echo.
Echo No Iocomp ActiveX Components were found to register
Echo in the Windows System directories.
Echo Registration Failed!
Echo.
GOTO END

:COMPLETE
Echo.
Echo Registration of Iocomp ActiveX components complete!
Echo.
GOTO END

:END
REM Release variables
SET AnalogSystem=
SET DigitalSystem=
SET StripSystem=
SET ProfSystem=
SET ComponentFound=
ECHO ON

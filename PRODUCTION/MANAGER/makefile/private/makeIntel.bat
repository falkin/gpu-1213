@echo off

REM 0.0.7
REM Cedric.bilat@he-arc.ch
REM Utilisation 
REM		${MAKE_INTEL} -f intelWin.mk
REM Configuration
REM		La variable ${MAKE_INTEL} est defini dans les scripts de lancement
REM			intel64.cmd
REM

REM ---------
REM - INTEL -
REM ---------

echo.
@call %SCRIPT_INTEL_CONFIG%
set args=%1%
set args=%args% %2%
set args=%args% %3%
make %args%

rem Les varaibles %1% et %2% et %3% sont les para entrées du .bat
rem Exemple use : ../PRODUCTION/MANAGER/makefile/private/makeIntel.bat -f intelWin.mk

REM ---------
REM - END -
REM ---------
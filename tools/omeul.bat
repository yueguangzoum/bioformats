@echo off

rem omeul.bat: a command-line client-side import tool for the OME Perl server

rem Required JARs: loci_tools.jar, ome_tools.jar

rem JAR libraries must be in the same directory as this
rem command line script for the command to function.

set SCIFIO_DIR=%~dp0
if "%SCIFIO_DIR:~-1%" == "\" set SCIFIO_DIR=%SCIFIO_DIR:~0,-1%

call "%SCIFIO_DIR%\config.bat"

if "%SCIFIO_DEVEL%" == "" (
  rem Developer environment variable unset; look for proper libraries.
  if exist "%SCIFIO_DIR%\ome_tools.jar" goto found
  if exist "%SCIFIO_DIR%\ome-io.jar" goto found
  goto missing
)

:found
set SCIFIO_PROG=loci.formats.ome.OMEWriter
set SCIFIO_CP="%SCIFIO_DIR%\ome_tools.jar";"%SCIFIO_DIR%\ome-io.jar"
call "%SCIFIO_DIR%\launch.bat" %*
goto end

:missing
echo Required JAR libraries not found. Please download:
echo   ome_tools.jar
echo from:
echo   http://www.loci.wisc.edu/bio-formats/downloads
echo.
echo Please note that omeul is legacy software that
echo has been discontinued. Use at your own risk.

:end

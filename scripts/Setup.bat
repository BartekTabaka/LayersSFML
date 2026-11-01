@echo off
setlocal

cd /d "%~dp0.." || goto :error

set "buildDir=build"

echo.
echo ========================
echo Checking build directory...
echo ========================

if exist "%buildDir%" (
    echo Folder "%buildDir%" exists. Removing...
    rmdir /s /q "%buildDir%"

    if exist "%buildDir%" (
        echo ERROR: Failed to remove the build directory!
        goto :error
    )

    echo Folder "%buildDir%" removed successfully.
) else (
    echo Folder "%buildDir%" does not exist.
)

echo.
echo ========================
echo Generating solution...
echo ========================

cmake -B "%buildDir%" -S . -G "Visual Studio 17 2022"

if errorlevel 1 goto :error

echo.
echo Solution generated successfully!
echo Location: %buildDir%
echo.
goto :end

:error
echo.
echo ========================
echo BUILD GENERATION FAILED!
echo ========================

:end
echo.
pause
endlocal
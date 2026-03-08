@echo off
echo Running Dialogue Compiler...
python compiler.py
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Something went wrong! Check your CSV files.
    pause
) else (
    echo.
    echo [SUCCESS] DT_Result.csv has been generated!
    echo You can now import it into Unreal Engine.
    timeout /t 5
)
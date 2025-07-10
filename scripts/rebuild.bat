@echo off
echo Cleaning old build...
call npx node-gyp clean || echo CLEAN FAILED

echo Configuring project...
call npx node-gyp configure || echo CONFIGURE FAILED

echo Running auto scripts...
call node .\scripts\gen_vsc_cpp_settings.js
call node .\scripts\gen_binding_gyp.js

echo Building project...
call npx node-gyp build

if %errorlevel% neq 0 (
    echo.
    echo ❌ Build failed!
    pause
    exit /b %errorlevel%
)

echo.
echo ✅ Build succeeded!
pause
@echo off

set DEMO_ROOT=%~dp0

mkdir "%DEMO_ROOT%\Plugins"

rem Fetch NextCAS-SDK, SDK Plugin
git clone git@118.31.50.10:tudou/NextCAS-SDK.git %DEMO_ROOT%\Plugins\NextCAS-SDK -b main

rem Fetch NHMiniZip, Zip Plugin
git clone git@118.31.50.10:tudou/NHMiniZip.git %DEMO_ROOT%\Plugins\NHMiniZip -b main

rem Fetch NHMMKV, Key-Value cache Plugin
git clone git@118.31.50.10:tudou/NHMMKV.git %DEMO_ROOT%\Plugins\NHMMKV -b main

rem Fetch NextCAS-Assets
rem git clone git@118.31.50.10:tudou/NextCAS-Assets.git %DEMO_ROOT%\Plugins\NextCAS-Assets -b main

rem Copy Unreal Assets
rem robocopy \\WeMetaNAS\wemeta-application\NextCAS-SDK\Paks\ %DEMO_ROOT%\Plugins\NextCAS-Assets\Paks\ /MIR /NFL /NDL

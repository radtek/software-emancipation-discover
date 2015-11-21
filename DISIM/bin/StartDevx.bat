@echo off
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:: Copyright (c) 2015, Synopsys, Inc.                                     :
:: All rights reserved.                                                   :
::                                                                        :
:: Redistribution and use in source and binary forms, with or without     :
:: modification, are permitted provided that the following conditions are :
:: met:                                                                   :
::                                                                        :
:: 1. Redistributions of source code must retain the above copyright      :
:: notice, this list of conditions and the following disclaimer.          :
::                                                                        :
:: 2. Redistributions in binary form must reproduce the above copyright   :
:: notice, this list of conditions and the following disclaimer in the    :
:: documentation and/or other materials provided with the distribution.   :
::                                                                        :
:: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    :
:: "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      :
:: LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  :
:: A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   :
:: HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, :
:: SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       :
:: LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  :
:: DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  :
:: THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    :
:: (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  :
:: OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   :
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
REM StartDevx.bat

REM Setting up env variables
if "%PSETHOME%" == "" goto :FindPSETHOME
"%PSETHOME%/bin/ci_environment"
if not errorlevel 1 goto :HavePSETHOME
echo DIScover is not installed in %%PSETHOME%%.
goto :Done

:FindPSETHOME
ci_environment
if not errorlevel 1 goto :HaveInstallation
echo DIScover is not installed in %%PATH%%.
goto :Done

:HaveInstallation
ci_environment --psethome --check
if errorlevel 1 goto :Done
for /F "delims=" %%v in ('ci_environment --psethome') do set PSETHOME=%%v

:HavePSETHOME

"%PSETHOME%\mb\fork.exe" "\"%PSETHOME%\bin\disperl\" \"%PSETHOME%\mb\IMUtil.pl\" -eStartDeveloperXpress -D-"

:Done

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

if .%DIS_USE_MS_CM% == . goto NO_PROTOCOL_SUPPORT
echo %%%%cm_continue
goto exit

:NO_PROTOCOL_SUPPORT
if .%cm_description% == . goto nodesc
ccm ci /g /c "%cm_description%" "%cm_revision_file%"
goto exit

:nodesc
if .%cm_description_file% == . goto nodescfile
ccm ci /g /cf "%cm_description_file%" "%cm_revision_file%"
goto exit

:nodescfile
ccm ci /g /nc "%cm_revision_file%"

:exit



@echo off
REM SDCC OBJ MAKEFILE
SET CFILENAME=VDP_SPRITES_12_MSXROM
if exist build\ goto NEXTSTEP1
echo MAKEDIR build
md build
:NEXTSTEP1
sdcc -v
echo Compiling...
sdcc -mz80 -c -o build\ --use-stdout source\%CFILENAME%.c
pause
exit /b

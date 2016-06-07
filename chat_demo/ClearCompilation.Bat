@echo off
for /f "delims=" %%i in ("%cd%") do set folder=%%~ni
echo %folder%
echo 回车确认清理数据!


echo ------正在清理VS2010工程中不需要的文件--------
echo 开始清理请稍等......

echo ---------------正在清理SDF文件-----------------
del /q/a/f/s %folder%\*.sdf

echo ---------------正在清理Ipch文件----------------
del /q/a/f/s %folder%\ipch\*.*

echo ---------------正在清理Debug文件---------------
del /q/a/f/s %folder%\Debug\*.obj
del /q/a/f/s %folder%\Debug\*.tlog
del /q/a/f/s %folder%\Debug\*.log
del /q/a/f/s %folder%\Debug\*.idb
del /q/a/f/s %folder%\Debug\*.pdb
del /q/a/f/s %folder%\Debug\*.ilk
del /q/a/f/s %folder%\Debug\*.pch
del /q/a/f/s %folder%\Debug\*.bsc
del /q/a/f/s %folder%\Debug\*.sbr

echo -------------正在清理Release文件--------------
del /q/a/f/s %folder%\Release\*.obj
del /q/a/f/s %folder%\Release\*.tlog
del /q/a/f/s %folder%\Release\*.log
del /q/a/f/s %folder%\Release\*.idb
del /q/a/f/s %folder%\Release\*.pdb
del /q/a/f/s %folder%\Release\*.ilk
del /q/a/f/s %folder%\Release\*.pch

echo ---------------正在清理Temp文件---------------
del /q/a/f/s %folder%\Temp\*.*


echo ---------------正在清理SDF文件-----------------
del /q/a/f/s *.sdf

echo ---------------正在清理Ipch文件----------------
del /q/a/f/s ipch\*.*

echo ---------------正在清理Debug文件---------------
del /q/a/f/s Debug\*.obj
del /q/a/f/s Debug\*.tlog
del /q/a/f/s Debug\*.log
del /q/a/f/s Debug\*.idb
del /q/a/f/s Debug\*.pdb
del /q/a/f/s Debug\*.ilk
del /q/a/f/s Debug\*.pch
del /q/a/f/s Debug\*.bsc
del /q/a/f/s Debug\*.sbr

echo -------------正在清理Release文件--------------
del /q/a/f/s Release\*.obj
del /q/a/f/s Release\*.tlog
del /q/a/f/s Release\*.log
del /q/a/f/s Release\*.idb
del /q/a/f/s Release\*.pdb
del /q/a/f/s Release\*.ilk
del /q/a/f/s Release\*.pch

echo ---------------正在清理Temp文件---------------
del /q/a/f/s Temp\*.*

ECHO ---------------
ECHO    清理完毕！
ECHO ---------------

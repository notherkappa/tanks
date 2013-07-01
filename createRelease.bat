xcopy sprites\*.* release\sprites\*.* /E /Y /C /H 
xcopy userdata\*.* release\userdata\*.* /E /Y /C /H 
xcopy maps\*.* release\maps\*.* /E /Y /C /H 

copy tanks.exe release\tanksdc.exe

del release\tanks.exe
upx -9 -orelease\tanks.exe release\tanksdc.exe
del release\tanksdc.exe
del release\tanks.rar

rar a -r release\tanks.rar release\
exit
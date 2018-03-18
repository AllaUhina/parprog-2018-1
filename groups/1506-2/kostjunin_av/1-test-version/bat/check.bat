@echo off

for /l %%i in (1,1,31) do (
	echo test %%i 
	generator %%i
	solver %%i
	checker %%i
	echo. & echo.
)
set /a var=1
for /l %%k in (32,1,34) do (
	echo test %%k 
	generator %%k a
	set /a var+=1
	solver %%k
	checker %%k
	echo. & echo.
)

pause

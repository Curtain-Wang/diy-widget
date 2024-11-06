@echo off
REM 设置代码页为UTF-8
chcp 65001

for /d %%i in ("%cd%\build\*Debug") do (
    if exist "%%i\debug" (
        echo 处理目录：%%i\debug
		
		echo 复制debug的dll文件
        for %%j in ("%%i\debug\*.dll") do (
			echo 复制 %%j 到 "D:\software\QT\6.5.3\msvc2019_64\plugins\designer"
			copy %%j "D:\software\QT\6.5.3\msvc2019_64\plugins\designer"
			
			echo 复制 %%j 到 "D:\software\QT\Tools\QtCreator\bin\plugins\designer"
			copy %%j "D:\software\QT\Tools\QtCreator\bin\plugins\designer"
			
			echo 复制 %%j 到 "D:\project\github\SSBMonitor-Custom-AnLi\build\Desktop_Qt_6_5_3_MSVC2019_64bit-Debug\debug"
			copy %%j "D:\project\github\SSBMonitor-Custom-AnLi\build\Desktop_Qt_6_5_3_MSVC2019_64bit-Debug\debug"
			
			echo 复制 %%j 到 "D:\project\github\SSBMonitor-Custom-AnLi\diydll"
			copy %%j "D:\project\github\SSBMonitor-Custom-AnLi\diydll"
        )
		
		echo 复制debug的lib文件
		for %%j in ("%%i\debug\*.lib") do (
			echo 复制 %%j 到 "D:\project\github\SSBMonitor-Custom-AnLi\include"
			copy %%j "D:\project\github\SSBMonitor-Custom-AnLi\include"
		)
    )
)

for /d %%i in ("%cd%\build\*Release") do (
    if exist "%%i\release" (
        echo 处理目录：%%i\release
		
		echo 复制release的dll文件
        for %%j in ("%%i\release\*.dll") do (
			echo 复制 %%j 到 "D:\software\QT\6.5.3\msvc2019_64\plugins\designer"
			copy %%j "D:\software\QT\6.5.3\msvc2019_64\plugins\designer"
			
			echo 复制 %%j 到 "D:\software\QT\Tools\QtCreator\bin\plugins\designer"
			copy %%j "D:\software\QT\Tools\QtCreator\bin\plugins\designer"
			
			echo 复制 %%j 到 "D:\project\github\SSBMonitor-Custom-AnLi\build\Desktop_Qt_6_5_3_MSVC2019_64bit-Release\release"
			copy %%j "D:\project\github\SSBMonitor-Custom-AnLi\build\Desktop_Qt_6_5_3_MSVC2019_64bit-Release\release"
			
			echo 复制 %%j 到 "D:\project\github\SSBMonitor-Custom-AnLi\diydll"
			copy %%j "D:\project\github\SSBMonitor-Custom-AnLi\diydll"
        )
		
		echo 复制release的lib文件
		for %%j in ("%%i\release\*.lib") do (
			echo 复制 %%j 到 "D:\project\github\SSBMonitor-Custom-AnLi\include"
			copy %%j "D:\project\github\SSBMonitor-Custom-AnLi\include"
		)
    )
)

echo 复制 tpseccircuitdiagram.h 到 "D:\project\github\SSBMonitor-Custom-AnLi\include"
copy tpseccircuitdiagram.h "D:\project\github\SSBMonitor-Custom-AnLi\include"

echo 操作完成！
pause
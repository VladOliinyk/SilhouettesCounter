Due to the fact that presented .exe file compiled using static links to all needed library, the presented .exe file maybe don't run on your machine.

It is not critical!

The problem lies in the difference of the compilers on Your machine, and the machine which was statically compiled this .exe file.
And, of course, maybe problem in the static links compiling :)

This problem can be solved in this way:
1. Install the QT Creator from here: https://www.qt.io/download-open-source/
1.1 Qt 5.6.0 for Windows 64-bit (VS 2015, 836 MB) http://download.qt.io/official_releases/qt/5.6/5.6.0/qt-opensource-windows-x86-msvc2015_64-5.6.0.exe
1.2 Qt 5.6.0 for Windows 32-bit (VS 2015, 840 MB) http://download.qt.io/official_releases/qt/5.6/5.6.0/qt-opensource-windows-x86-msvc2015-5.6.0.exe

2. Download the source files of the project here: https://github.com/VladOliynyk/SilhouettesCounter

3. Compile project where you want. 

I hope this problem will not arise for you :D

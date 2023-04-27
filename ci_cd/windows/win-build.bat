echo Making exe
SET PATH=%PATH%;C:\Qt\Tools\mingw1120_64\bin;C:\Qt\6.4.1\mingw_64\bin
C:\Qt\6.4.1\mingw_64\bin\qmake.exe -o Makefile src/PacketSender.pro -spec win32-g++
C:\Qt\Tools\mingw1120_64\bin\mingw32-make.exe -f Makefile.Release -j8
echo Signing exe
cd release
copy /Y C:\Users\danie\Desktop\code_sign_exe_com.bat .
call code_sign_exe_com.bat
echo Copying signed exe
copy /Y packetsender.exe D:\github\naglecode-installers\packetsenderinstaller\qt6_4_1_mingw64\packetsender.exe
copy /Y packetsender.exe D:\github\naglecode-installers\packetsenderinstaller\PacketSenderPortable\packetsender.exe
cd ..

echo Cleaning build
rd /s /q release

echo Making command line exe
C:\Qt\6.4.1\mingw_64\bin\qmake.exe -o Makefile src/PacketSenderCLI.pro -spec win32-g++
C:\Qt\Tools\mingw1120_64\bin\mingw32-make.exe -f Makefile.Release -j8

echo Signing command line exe
cd release
copy /Y C:\Users\danie\Desktop\code_sign_exe_com.bat .
call code_sign_exe_com.bat
echo Copying command line exe
copy /Y packetsendercli.exe D:\github\naglecode-installers\packetsenderinstaller\qt6_4_1_mingw64\packetsender.com
copy /Y packetsendercli.exe D:\github\naglecode-installers\packetsenderinstaller\PacketSenderPortable\packetsender.com
cd ..

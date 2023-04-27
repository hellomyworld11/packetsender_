#!/usr/bin/env bash

if [ -z "$1" ]
  then
    echo "Please supply build version (e.g. 8.0.3)"
    exit
fi
BUILD_VERSION="$1";
php ci_cd/linux/linux-prebuild.php $BUILD_VERSION
# exit 99
cd src
qmake --version
qmake PacketSender.pro
make clean
make -j4
ls
mkdir -p appdir/usr/bin ;
mkdir -p appdir/usr/share/icons ;
cd appdir
cp ../packetsender usr/bin/
cp ../pslogo256.png packetsender.png
cp ../pslogo256.png usr/share/icons/packetsender.png
cp ../packetsender.desktop packetsender.desktop

cd ..
wget -c "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage"
chmod a+x linuxdeployqt*.AppImage
unset QTDIR; unset QT_PLUGIN_PATH ; unset LD_LIBRARY_PATH
./linuxdeployqt*.AppImage ./appdir/usr/bin/packetsender -appimage  -bundle-non-qt-libs

#curl --upload-file ./PacketSender-*.AppImage https://transfer.sh/PacketSender-git$(git rev-parse --short HEAD)-x86_64.AppImage

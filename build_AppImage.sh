#!/bin/sh

cmake .
make -j4
make install DESTDIR=AppDir

wget https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
chmod +x linuxdeploy-x86_64.AppImage

./linuxdeploy-x86_64.AppImage --appdir AppDir
 ./linuxdeploy-x86_64.AppImage --appdir AppDir --output appimage

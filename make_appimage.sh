#!/bin/bash
if [[ $# -ne 1 ]]
then
	echo "usage: make_appimage.sh path_to_linuxdeploy"
	echo "don't forget to build with 'make -f makefile_linux -j2 BUILDTYPEFLAGS=-DAS_APPIMAGE=1'"
	echo "don't forget to build the dependencies first!!"
	exit 1
fi;

if [ -d AppDir ];
then
	rm -rf AppDir/
fi

rm *.AppImage

if [ -f AppDir ];
then
	rm -rf AppDir
fi

#export SIGN=1
#export SIGN_KEY=0xLAST8CHARSOFGPGKEYID

$1 --appdir AppDir
cp -r data AppDir/usr/share
mkdir -p AppDir/usr/share/metainfo
cp linuxdeploy/*.xml AppDir/usr/share/metainfo/
$1 --executable ./winter.out --appdir AppDir -i ./linuxdeploy/winter.png -d ./linuxdeploy/winter.desktop --output appimage
exit 0

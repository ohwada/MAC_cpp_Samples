#!/bin/sh

# mkipk.sh
# generates an ipkg for embedded Brickout

# Bill Kendrick
# bill@newbreedsoftware.com

# June 10, 2002 - June 10, 2002


VER=2002.06.09


PACKAGE=brickout
TMPDIR=tmp
CONTROL=$TMPDIR/CONTROL/control
ARCH=arm
RM=rm

echo "SETTING UP"
mkdir $TMPDIR
mkdir $TMPDIR/CONTROL


echo
echo "MAKING SURE BINARY EXISTS"
make clean
make zaurus

echo 
echo "CREATING CONTROL FILE"

echo "Package: $PACKAGE" > $CONTROL
echo "Priority: optional" >> $CONTROL
echo "Version: $VER" >> $CONTROL
echo "Section: games" >> $CONTROL
echo "Architecture: $ARCH" >> $CONTROL
echo "Maintainer: Bill Kendrick (bill@newbreedsoftware.com)" >> $CONTROL
echo "Description: Squish the bugs before they suck all your blood." >> $CONTROL

echo
echo "COPYING DATA FILES"

mkdir -p $TMPDIR/opt/QtPalmtop/share/brickout
mkdir $TMPDIR/opt/QtPalmtop/share/brickout/sounds/
mkdir $TMPDIR/opt/QtPalmtop/share/brickout/music/
mkdir $TMPDIR/opt/QtPalmtop/share/brickout/images/
cp -R sounds/* $TMPDIR/opt/QtPalmtop/share/brickout/sounds/
cp -R music/* $TMPDIR/opt/QtPalmtop/share/brickout/music/
cp -R images-sdl/* $TMPDIR/opt/QtPalmtop/share/brickout/images/

echo
echo "CREATING BINARIES"

mkdir -p $TMPDIR/opt/QtPalmtop/bin/
echo "brickout" > $TMPDIR/opt/QtPalmtop/bin/brickout.sh
chmod 755 $TMPDIR/opt/QtPalmtop/bin/brickout.sh
cp brickout.zaurus $TMPDIR/opt/QtPalmtop/bin/


echo "CREATING ICON AND DESKTOP FILE"

mkdir -p $TMPDIR/opt/QtPalmtop/pics/
cp brickout.png $TMPDIR/opt/QtPalmtop/pics/

mkdir -p $TMPDIR/opt/QtPalmtop/apps/Games/
DESKTOP=$TMPDIR/opt/QtPalmtop/apps/Games/brickout.desktop
echo "[Desktop Entry]" > $DESKTOP
echo "Comment=Brick breaking game" >> $DESKTOP
echo "Exec=brickout.sh" >> $DESKTOP
echo "Icon=brickout" >> $DESKTOP
echo "Type=Application" >> $DESKTOP
echo "Name=Brickout" >> $DESKTOP


echo
echo "CREATING IPK..."

ipkg-build $TMPDIR

echo
echo "CLEANING UP"

$RM -r $TMPDIR

echo


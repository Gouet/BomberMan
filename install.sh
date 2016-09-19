#!/bin/bash

bombermandir="$HOME/Bomberman/"
libdir="$bombermandir/lib/"
iadir="$bombermandir/ia/"
mediadir="$bombermandir/media/"
confrc="$HOME/.`echo $SHELL | cut -d '/' -f 3`rc"
dir=$(echo $bombermandir | sed "s/\//\\\\\//g")

green="\e[32m"
reset="\e[0m"
red="\e[31m"
yellow="\e[33m"

pending="`echo -ne "[$yellow" "Pending" "$reset]"`"
done="`echo -ne "[$green" "OK" "$reset]"`"
error="`echo -ne "[$red" "Error" "$reset]"`"

echo -e "$pending" "Making bomberman"
make -j4 INSTALL=$bombermandir
echo -e "$done" "Bomberman made"

echo -e "$pending" "Creating Bomberman directories"
mkdir -p "$bombermandir"
mkdir -p "$libdir"
mkdir -p "$iadir"
echo -e "$done" "Bomberman directories created"

echo -e "$pending" "Copying bomberman files"
echo -e "[" "$red" "libraries" "$reset" "]"
cp ./fmod/lib/x86_64/* "$libdir"
echo -e "[" "$red" "media" "$reset" "]"
cp -rf "./media" "$bombermandir"
echo -e "[" "$red" "binary" "$reset" "]"
cp -f "./bomberman" "$bombermandir"
echo -e "[" "$red" "ia" "$reset" "]"
cp -f "./ia/iaBehaviour.lua" "$iadir"
cp -f "./ia/positionDirection.lua" "$iadir"
cp -f "./ia/astar.lua" "$iadir"
echo -e "$done" "Bomberman file copied"

tochange=$(find $mediadir -name "*.xml")

for f in $tochange; do
    echo "Setting path of " $f
    sed -i "s/\.\//$dir/g" $f
done

if [ -f $confrc ]; then
    echo "$pending" "Setting path $confrc pathes"
    if [ ! $(echo $LD_LIBRARY_PATH | grep "$libdir") ]; then
	echo "export LD_LIBRARY_PATH=\"\$LD_LIBRARY_PATH:$libdir\"" >> "$confrc"
    fi
    if [ ! $(echo $PATH | grep "$bombermandir") ]; then
	echo "export PATH=\"\$PATH:$bombermandir\"" >> "$confrc"
    fi
    echo -e "$done" "$confrc successfully set"
else
    echo "$error" "$confrc not found"
fi

echo -e "$done" "Bomberman successfully installed"

#!/bin/bash

##
 # Mieszko Mazurek <mimaz@gmx.com> 
 # 2018
 ##

NDK=~/android/sdk/ndk-bundle
TOOLCHAINS=$NDK/toolchains

for dir in $(find $TOOLCHAINS -maxdepth 4 -type d -name "bin"); do
    PATH=$dir:$PATH
done


make ARCH=$1 TARGET=$2 PATH=$PATH

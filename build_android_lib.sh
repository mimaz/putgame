##
 # Mieszko Mazurek <mimaz@gmx.com> 
 # 2018
 ##

#!/bin/bash

TOOLCHAINS=~/android/toolchains

for dir in $(find $TOOLCHAINS -maxdepth 2 -type d -name "bin"); do
    export PATH=$dir:$PATH
done

case $1 in
    x86_64 | x86-64)
        TARGET=x86_64-linux-android-
        LIBNAME=libputgame-android-x86_64.so
        ;;

    x86 | i686)
        TARGET=i686-linux-android-
        LIBNAME=libputgame-android-$1.so
        ;;

    arm)
        TARGET=arm-linux-androideabi-
        LIBNAME=libputgame-android-arm.so
        ;;

    arm64 | aarch64)
        TARGET=aarch64-linux-android-
        LIBNAME=libputgame-android-$1.so
        ;;

    *)
        echo "invalid architecture: $1"
        exit 1
esac

BUILD_DIR=/tmp/putgame-build-$1

mkdir -p $BUILD_DIR

make TARGET=$TARGET \
    OUTPUT=$LIBNAME \
    PLATFORM=ANDROID \
    RELEASE=1 \
    BUILD_DIR=$BUILD_DIR \
    clean \
    libputgame

cp $BUILD_DIR/libputgame.so $LIBNAME

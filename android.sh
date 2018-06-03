##
 # Mieszko Mazurek <mimaz@gmx.com> 
 # 2018
 ##

#!/bin/bash

ARGC=$#
SCRIPT_NAME=$0

function print_usage() {
    echo "Usage $SCRIPT_NAME command [arch]"
}

if (( $ARGC < 1 )); then
    print_usage
    exit 1
fi

ARCH=$1
COMMAND=$2

TOOLCHAINS=~/android/toolchains

JNI_LIBS_DIR=jniLibs
LIB_OUT_DIR=$JNI_LIBS_DIR/$ARCH
BUILD_DIR=$(make build_dir ARCH=$ARCH TARGET=$TARGET)

function set_make_args() {
    if (( $ARGC < 2 )); then
        print_usage
        echo "arch argument required for command $COMMAND"
        exit 1
    fi

    TOOLCHAIN_PATH=""

    for dir in $(find $TOOLCHAINS -maxdepth 2 -type d -name "bin"); do
        TOOLCHAIN_PATH=$dir:$TOOLCHAIN_PATH
    done


    case $ARCH in
        armeabi-v7a)
            TARGET=arm-linux-androideabi-
            ;;

        x86)
            TARGET=i686-linux-android-
            ;;

        x86_64)
            TARGET=x86_64-linux-android-
            ;;

        *)
            echo "invalid architecture $ARCH"
            echo "available architectures - armeabi-v7a, x86, x86_64"
            exit 1
    esac


    MAKE_ARCH_ARGS="TARGET=$TARGET \
                    OUTPUT=$LIBOUT \
                    PLATFORM=ANDROID \
                    RELEASE=1 \
                    BUILD_DIR=$BUILD_DIR"
}


case $COMMAND in
    build)
        set_make_args
        PATH=$TOOLCHAIN_PATH:$PATH make $MAKE_ARCH_ARGS libputgame -j1
        mkdir -p $LIB_OUT_DIR
        cp $BUILD_DIR/libputgame.so $LIB_OUT_DIR/
        ;;

    clean)
        set_make_args
        make $MAKE_ARCH_ARGS clean
        rm -rf $LIB_OUT_DIR
        ;;

    *)
        echo "invalid command $COMMAND"
        echo "available commands - build, clean, cleanall"
esac

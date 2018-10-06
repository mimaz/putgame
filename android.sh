##
 # Mieszko Mazurek <mimaz@gmx.com> 
 # 2018
 ##

#!/bin/bash

COMMANDS="${@:2}"

case $1 in
    arm|armv7a)
        ARCH=arm
        ;;

    x86|i686)
        ARCH=x86
        ;;

    x86_64|x86-64)
        ARCH=x86_64
        ;;
    
    *)
        unset ARCH
        COMMANDS="$1 $COMMANDS"
esac

NDK_DIR=/home/mimakkz/android/ndk-r18
TOOLCHAIN_DIR=toolchains/
JNI_LIBS_DIR=jniLibs/
TARGET_API=21
RELEASE=1
USE_LTO=1
MAKE_JOBS=12

MAKE="make --file android.mk"
LIB_OUT_DIR=$JNI_LIBS_DIR/$ARCH
BUILD_DIR=$($MAKE build_dir ARCH=$ARCH TARGET=$TARGET)
LIB_FILE=$($MAKE lib_file ARCH=$ARCH TARGET=$TARGET)
MAKE_TOOLCHAIN_SCRIPT=$NDK_DIR/build/tools/make_standalone_toolchain.py

function print_usage {
    echo "Usage: $0 [arch] [command]"
}

function set_toolchain_path {
    if [ -z "$(ls $TOOLCHAIN_DIR 2> /dev/null | grep $ARCH)" ]; then
        echo "generating toolchain for $ARCH..."
        $MAKE_TOOLCHAIN_SCRIPT --install-dir $TOOLCHAIN_DIR/$ARCH --arch $ARCH --api $TARGET_API

        if (( $? != 0 )); then
            echo "cannot generate toolchain for $ARCH :("
            exit 1
        fi
    fi

    TOOLCHAIN_PATH=$TOOLCHAIN_DIR/$ARCH/bin
}

function set_make_args {
    case $ARCH in
        arm)
            TARGET=arm-linux-androideabi-
            ;;

        x86)
            TARGET=i686-linux-android-
            ;;

        x86_64)
            TARGET=x86_64-linux-android-
            ;;

        *)
            if [[ -z $ARCH ]]; then
                unset TARGET
            else
                echo "invalid architecture $ARCH"
                echo "available architectures - arm, x86, x86_64"
                exit 1
            fi
    esac


    MAKE_ARGS="TARGET=$TARGET \
               OUTPUT=$LIBOUT \
               PLATFORM=ANDROID \
               RELEASE=$RELEASE \
               USE_LTO=$USE_LTO \
               BUILD_DIR=$BUILD_DIR"
}

function build {
    if [ -z $ARCH ]; then
        echo cannot build project with no architecture set!
        print_usage
        exit 1
    fi

    set_toolchain_path
    set_make_args

    PATH=$TOOLCHAIN_PATH:$PATH $MAKE $MAKE_ARGS -j$MAKE_JOBS all
    mkdir -p $LIB_OUT_DIR

    cp $LIB_FILE $LIB_OUT_DIR/
}

function clean {
    set_make_args
    $MAKE $MAKE_ARGS clean

    rm -rf $LIB_OUT_DIR
}

function cleanall {
    clean

    rm -rf $TOOLCHAIN_DIR
}

for cmd in $COMMANDS; do
    case $cmd in
        build)
            build
            ;;

        clean)
            clean
            ;;

        cleanall)
            cleanall
            ;;

        *)
            echo "invalid command $cmd"
            echo "available commands - build, clean"
    esac
done

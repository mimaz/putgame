##
 # Mieszko Mazurek <mimaz@gmx.com> 
 # 2018
 ##

PLATFORM = ANDROID

include build.mk

LIBGAME_LDFLAGS += -lc -lm -lGLESv3 -llog -lc++_static -static-libstdc++
LIBGAME_SRC_DIRS += java/

all: libputgame

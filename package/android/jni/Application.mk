
# Uncomment this if you're using STL in your project
# See CPLUSPLUS-SUPPORT.html in the NDK documentation for more information
APP_STL := gnustl_static 

APP_ABI := armeabi armeabi-v7a

APP_USE_CPP0X := true
NDK_TOOLCHAIN_VERSION := 4.9
APP_CPPFLAGS += -fexceptions
APP_CPPFLAGS += -frtti
APP_CPPFLAGS += -O2
#APP_CPPFLAGS += -g
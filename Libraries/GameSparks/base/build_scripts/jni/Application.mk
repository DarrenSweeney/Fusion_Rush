
# Uncomment this if you're using STL in your project
# See CPLUSPLUS-SUPPORT.html in the NDK documentation for more information
# APP_STL := stlport_static 

APP_ABI := armeabi-v7a armeabi x86
#APP_STL := stlport_static
#APP_STL := gnustl_static

#NDK_TOOLCHAIN_VERSION=clang3.3
#NDK_TOOLCHAIN_VERSION := 4.8
#LOCAL_CPPFLAGS +=  -Wno-psabi  -fno-rrti -fno-exceptions

#-std=c++11

APP_STL := gnustl_static
APP_CPPFLAGS += -frtti -std=c++11 -fpic -fexceptions -Wall -Werror -Wextra
APP_CFLAGS += -Wno-error=format-security

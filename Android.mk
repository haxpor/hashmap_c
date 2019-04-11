LOCAL_PATH := $(call my-dir)

###########################
#
# shared library
#
###########################

include $(CLEAR_VARS)

LOCAL_MODULE := hashmap_c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include \
	externals/MurmurHash3/include

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

LOCAL_SRC_FILES := src/hashmap_c.c \
	externals/MurmurHash3/src/MurmurHash3.c

LOCAL_CFLAGS += -Wall -std=c99 -O2 -pedantic
LOCAL_LDLIBS := 

ifeq ($(NDK_DEBUG),1)
    cmd-strip :=
endif

include $(BUILD_SHARED_LIBRARY)

###########################
#
# static library
#
###########################

LOCAL_MODULE := hashmap_c_static

LOCAL_MODULE_FILENAME := libhashmap_c

LOCAL_CFLAGS := -Wall -std=c99 -O2 -pedantic
LOCAL_LDLIBS := 
LOCAL_EXPORT_LDLIBS := 

include $(BUILD_STATIC_LIBRARY)

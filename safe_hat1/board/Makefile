#HOME_SDK_PATH =/home/lyx/RV1126_ATK#SDK的路径
#BUILDNAME = alientek_rv1126#buildroot的output生成文件夹名字

HOME_SDK_PATH = /home/yang/SDK/RV1126_RV1109_LINUX_SDK_V2.2.5.1_20231011/#自己的sdk的路径
BUILDNAME =rockchip_rv1126_rv1109_spi_nand


C_FLAGS = -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -Os -DUSE_UPDATEENGINE=ON -DSUCCESSFUL_BOOT=ON  -DNDEBUG   -Wall -Wextra -Wshadow -ffast-math -fPIC -Werror -g -O0 -ggdb -gdwarf -funwind-tables -rdynamic
C_DEFINES = -DAUDIO_ALGORITHM_ENABLE -DLIBDRM -DRKAIQ

C_INCLUDES =-I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/build/rkmedia/. -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/a3dlut -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/ablc -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/accm -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/acp -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/adebayer -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/adehaze -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/adpcc -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/ae -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/af -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/agamma -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/ahdr -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/aie -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/alsc -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/anr -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/aorb -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/asd -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/asharp -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/algos/awb -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/common -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/iq_parser -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/uAPI -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq/xcore -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/libdrm -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/build/rkmedia/include/easymedia -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/build/rkmedia/include/rkmedia -I$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/build/rkmedia/include -isystem $(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/rkaiq

LIBS=-L./ -lrtsp -L$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/build/rkmedia/examples/librtsp  -Wl,-rpath,$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/build/rkmedia/examples/librtsp:$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/build/rkmedia/src:$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/build/rkmedia/examples/../src/rkaudio: $(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/build/rkmedia/examples/../src/libeasymedia.so.1.0.1 $(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/build/rkmedia/examples/../src/rkaudio/libthird_media.so -ldrm -lrockchip_mpp -lliveMedia -lgroupsock -lBasicUsageEnvironment -lUsageEnvironment -lpthread -lasound -lRKAP_3A -lRKAP_ANR -lRKAP_Common -lv4l2 -lrga -lRKAP_3A -lRKAP_ANR -lRKAP_Common -lv4l2 -lrga -lrknn_runtime -lrknn_api -lrockface -lsqlite3 -lmd_share -lod_share  $(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot/usr/lib/librkaiq.so
ROOTDIR =$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/arm-buildroot-linux-gnueabihf/sysroot
GCC_DIR=\
	$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/bin/arm-linux-gnueabihf-gcc
G++_DIR=\
	$(HOME_SDK_PATH)/buildroot/output/$(BUILDNAME)/host/bin/arm-linux-gnueabihf-g++

SRCDIR=./src
OBJDIR=./obj
INCLUDEDIRS=./include
INCLUDES=$(patsubst %,-I%,$(INCLUDEDIRS))
SRCS=$(wildcard $(SRCDIR)/*.c)
OBJS=$(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(SRCS)))
OBJ:=main
$(OBJ):$(OBJS)
	$(GCC_DIR) $^ -o $@ $(INCLUDES)  $(C_DEFINES) $(C_FLAGS) $(LIBS) $(C_INCLUDES) --sysroot=$(ROOTDIR)
$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(GCC_DIR) -c $< -o $@  $(INCLUDES) $(C_DEFINES) $(LIBS) $(C_FLAGS) $(C_INCLUDES) --sysroot=$(ROOTDIR)
clean:
	rm $(OBJDIR)/*.o $(OBJ)

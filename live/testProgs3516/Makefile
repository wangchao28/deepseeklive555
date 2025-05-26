PREFIX = /usr/local
INCLUDES = -I../UsageEnvironment/include -I../groupsock/include -I../liveMedia/include -I../BasicUsageEnvironment/include
# Default library filename suffixes for each library that we link with.  The "config.*" file might redefine these later.
libliveMedia_LIB_SUFFIX = $(LIB_SUFFIX)
libBasicUsageEnvironment_LIB_SUFFIX = $(LIB_SUFFIX)
libUsageEnvironment_LIB_SUFFIX = $(LIB_SUFFIX)
libgroupsock_LIB_SUFFIX = $(LIB_SUFFIX)
##### Change the following for your environment:
CROSS_COMPILE?=		arm-himix100-linux-
COMPILE_OPTS =		$(INCLUDES) -I/usr/local/include -I. -I/home/mist/workspace/live/openssl/include/ -O2 -DSOCKLEN_T=socklen_t -DNO_SSTREAM=1 -D_LARGEFILE_SOURCE=1 -D_FILE_OFFSET_BITS=32 -DNO_STD_LIB -DLOCALE_NOT_USED
C =			c
C_COMPILER =		$(CROSS_COMPILE)gcc
C_FLAGS =		$(COMPILE_OPTS)
CPP =			cpp
CPLUSPLUS_COMPILER =	$(CROSS_COMPILE)g++
CPLUSPLUS_FLAGS =	$(COMPILE_OPTS) -Wall -DBSD=1
OBJ =			o
LINK =			$(CROSS_COMPILE)g++ -o
LINK_OPTS =		
CONSOLE_LINK_OPTS =	$(LINK_OPTS) 
LIBRARY_LINK =		$(CROSS_COMPILE)ar cr 
LIBRARY_LINK_OPTS =	$(LINK_OPTS) 
LIB_SUFFIX =			a
LIBS_FOR_CONSOLE_APPLICATION = -L/home/mist/workspace/live/openssl/lib/ -lssl -lcrypto 
LIBS_FOR_GUI_APPLICATION =
EXE =
PREFIX=/home/mist/workspace/live/hi3516/

##### End of variables to change

ALL = testOnDemandH264Acc$(EXE)
all: $(ALL)

.$(C).$(OBJ):
	$(C_COMPILER) -c $(C_FLAGS) $<
.$(CPP).$(OBJ):
	$(CPLUSPLUS_COMPILER) -c $(CPLUSPLUS_FLAGS) $<

HELPER_OBJS = announceURL.$(OBJ)

ON_DEMAND_RTSP_H264_Acc_OBJS	= testOnDemandH264Acc.$(OBJ)


announceURL.$(CPP): 			   announceURL.hh
testOnDemandH264Acc.$(CPP):		   announceURL.hh

USAGE_ENVIRONMENT_DIR = ../UsageEnvironment
USAGE_ENVIRONMENT_LIB = $(USAGE_ENVIRONMENT_DIR)/libUsageEnvironment.$(libUsageEnvironment_LIB_SUFFIX)
BASIC_USAGE_ENVIRONMENT_DIR = ../BasicUsageEnvironment
BASIC_USAGE_ENVIRONMENT_LIB = $(BASIC_USAGE_ENVIRONMENT_DIR)/libBasicUsageEnvironment.$(libBasicUsageEnvironment_LIB_SUFFIX)
LIVEMEDIA_DIR = ../liveMedia
LIVEMEDIA_LIB = $(LIVEMEDIA_DIR)/libliveMedia.$(libliveMedia_LIB_SUFFIX)
GROUPSOCK_DIR = ../groupsock
GROUPSOCK_LIB = $(GROUPSOCK_DIR)/libgroupsock.$(libgroupsock_LIB_SUFFIX)
LOCAL_LIBS =	$(LIVEMEDIA_LIB) $(GROUPSOCK_LIB) \
		$(BASIC_USAGE_ENVIRONMENT_LIB) $(USAGE_ENVIRONMENT_LIB)
LIBS =			$(LOCAL_LIBS) $(LIBS_FOR_CONSOLE_APPLICATION)


testOnDemandH264Acc$(EXE):	$(ON_DEMAND_RTSP_H264_Acc_OBJS) $(HELPER_OBJS) $(LOCAL_LIBS)
	$(LINK)$@ $(CONSOLE_LINK_OPTS) $(ON_DEMAND_RTSP_H264_Acc_OBJS) $(HELPER_OBJS) $(LIBS)	


clean:
	-rm -rf *.$(OBJ) $(ALL)



##### Any additional, platform-specific rules come here:

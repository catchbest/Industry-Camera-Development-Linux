######################################
#
######################################
#source file

PLATFORM=arm64

#CROSS_COMPILE=arm-linux-gnueabihf-
#PLATFORM_BIN_DIR=arm32

#CROSS_COMPILE=aarch64-linux-gnu-
#PLATFORM_BIN_DIR=arm64


CC=$(CROSS_COMPILE)gcc
CXX=$(CROSS_COMPILE)g++


SOURCE  := $(wildcard *.c) $(wildcard *.cpp)
OBJS    := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCE)))
  
#target you can change test to what you want
TARGET  := capture_$(PLATFORM)
  
#compile and lib parameter
LIBS    := 

LDFLAGS :=  -L../../KSJApi.bin/$(PLATFORM) -lksjapi -lksjlog -lksjbayer -lpthread -lusb-1.0 -ludev -ldl -lopencv_imgproc -lopencv_core -lopencv_highgui
INCLUDE := -I. -I.. -I../../KSJApi.inc 
CFLAGS  := -gdwarf-2   -g3 -Wall  $(DEFINES) $(INCLUDE) -Wl,-rpath,../../KSJApi.bin/$(PLATFORM)
CXXFLAGS:= $(CFLAGS) -DHAVE_CONFIG_H
  
  
  
  
  
#i think you should do anything here
.PHONY : everything objs clean veryclean rebuild
  
everything : $(TARGET)
  
all : $(TARGET)
  
objs : $(OBJS)
  
rebuild: veryclean everything
                
clean :
	rm -fr *.so
	rm -fr *.o
veryclean : clean
	rm -fr $(TARGET)
$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)
install:
	cp $(TARGET) ../build/

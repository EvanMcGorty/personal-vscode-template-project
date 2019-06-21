#the variables VERSION, FLAGS, INCLUDE_PATHS, MODE, SOURCE, OUT, and CXX may optionally be specified at the command line.

#the following lines are the only ones meant to be edited.
INCLUDE_PATHS+=
LIBRARY_PATHS+=
LIBRARIES+=
SOURCE+=

ifndef VERSION
	VERSION=c++17
endif
ifndef SOURCE
	SOURCE=Source.cpp
endif
ifndef MODE
	MODE=test
endif
ifndef CXX
	CXX=clang++
endif
ifndef OUT
	OUT=a
endif


ifeq ($(CXX),clang-cl)
	FLAGS+=/std:$(VERSION)
	FLAGS+=/GX
	FLAGS+=$(foreach dir,$(INCLUDE_PATHS),-I $(dir))
	ENDING_FLAGS+=/link
	ENDING_FLAGS+=$(foreach dir,$(LIBRARY_PATHS),/LIBPATH:$(dir))
	ENDING_FLAGS+=$(foreach dir,$(LIBRARIES),/IMPLIB:$(dir))
	ENDING_FLAGS+=/subsystem:windows
else
	FLAGS+=$(foreach dir,$(LIBRARY_PATHS),-L$(dir))
	FLAGS+=$(foreach dir,$(LIBRARIES),-l$(dir))
	FLAGS+=$(foreach dir,$(INCLUDE_PATHS),-I$(dir))
	FLAGS+=-std=$(VERSION)
endif



ifeq ($(MODE),test)
	FLAGS+=-Os
else ifeq ($(MODE),debug)
	DEBUG_SETTINGS=-fuse-ld=lld -Z7 -MTd
ifneq ($(CXX),clang-cl)
$(error can only debug with clang-cl)
endif

else ifeq ($(MODE),fast)
	FLAGS+=-D NDEBUG
	FLAGS+=-Ofast
endif


FLAGS+=-o $(OUT)



all:
	$(CXX) $(DEBUG_SETTINGS) $(SOURCE) $(FLAGS) $(ENDING_FLAGS)
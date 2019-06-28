#the variables VERSION, FLAGS, INCLUDE_PATHS, MODE, CLANG_SET_TARGET, SOURCE, OUT, LINKER, and CXX may optionally be specified at the command line.
#when a linker is specified, compilation and linking will be done separately

#the following lines assign default values for variables
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


#the following lines are the only ones meant to be edited.
INCLUDE_PATHS+=
LIBRARY_PATHS+=
LIBRARIES+=
SOURCE+=



ifeq ($(CXX),clang-cl)
	FLAGS+=/std:$(VERSION)
	FLAGS+=/GX
	FLAGS+=$(foreach dir,$(INCLUDE_PATHS),-I $(dir))
	LINKING_FLAGS+=$(foreach dir,$(LIBRARY_PATHS),/LIBPATH:$(dir))
	LINKING_FLAGS+=$(foreach dir,$(LIBRARIES),/IMPLIB:$(dir))
else
	LINKING_FLAGS+=$(foreach dir,$(LIBRARY_PATHS),-L$(dir))
	LINKING_FLAGS+=$(foreach dir,$(LIBRARIES),-l$(dir))
	FLAGS+=$(foreach dir,$(INCLUDE_PATHS),-I$(dir))
	FLAGS+=-std=$(VERSION)
endif

ifdef CLANG_SET_TARGET
ifeq ($(CXX),clang-cl)
	FLAGS+=--target=$(CLANG_SET_TARGET)
else
	FLAGS+=-target $(CLANG_SET_TARGET)
endif
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


all:
ifeq ($(CXX),clang-cl)

ifdef LINKER
	$(error cannot link separately with clang-cl)
endif
	$(CXX) $(DEBUG_SETTINGS) $(SOURCE) $(FLAGS) -o $(OUT) /link $(LINKING_FLAGS)
else
ifdef LINKER
	$(CXX) -target x86_64-pc-windows-gnu $(SOURCE) -c $(DEBUG_SETTINGS) $(FLAGS) -o builds/temp_unlinked_binary.o
	$(LINKER) builds/temp_unlinked_binary.o $(LINKING_FLAGS) -o $(OUT)
else
	$(CXX) $(DEBUG_SETTINGS) $(SOURCE) $(FLAGS) -o $(OUT) $(LINKING_FLAGS)
endif
endif

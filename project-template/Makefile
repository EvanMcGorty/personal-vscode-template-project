#the variables VERSION, GENERATED_FLAGS, INCLUDE_PATHS, MODE, CLANG_SET_TARGET, SOURCE, OUT, LINKER, and CXX may optionally be specified at the command line.
#when a linker is specified, compilation and linking will be done separately

#the following lines assign default values for variables. they may be edited.
VERSION=c++17
SOURCE=Source.cpp
MODE=test
CXX=clang++
OUT=builds/a.exe


#the following lines may be edited.
override INCLUDE_PATHS+=
override LIBRARY_PATHS+=
override LIBRARIES+=
override SOURCE+=


GENERATED_FLAGS+=$(FLAGS)


ifeq ($(CXX),clang-cl)

	#the following line may be edited.
	override LIBRARY_PATHS+=

	GENERATED_FLAGS+=/std:$(VERSION)
	GENERATED_FLAGS+=/GX
	GENERATED_FLAGS+=$(foreach dir,$(INCLUDE_PATHS),-I $(dir))
	LINKING_FLAGS+=$(foreach dir,$(LIBRARY_PATHS),/libpath:$(dir))
	LINKING_FLAGS+=$(foreach dir,$(LIBRARIES),$(dir).lib)
else

	#the following line may be edited.
	override LIBRARY_PATHS+=

	LINKING_FLAGS+=$(foreach dir,$(LIBRARY_PATHS),-L$(dir))
	LINKING_FLAGS+=$(foreach dir,$(LIBRARIES),-l$(dir))
	GENERATED_FLAGS+=$(foreach dir,$(INCLUDE_PATHS),-I$(dir))
	GENERATED_FLAGS+=-std=$(VERSION)
endif

ifeq ($(CXX),clang++)
	GENERATED_FLAGS+=-Xclang -flto-visibility-public-std

	#the following line may be edited.
	override LIBRARY_PATHS+=

endif

ifeq ($(CXX),g++)

	#the following line may be edited.
	override LIBRARY_PATHS+=
	
endif

ifdef CLANG_SET_TARGET
ifeq ($(CXX),clang-cl)
	GENERATED_FLAGS+=--target=$(CLANG_SET_TARGET)
else
	GENERATED_FLAGS+=-target $(CLANG_SET_TARGET)
endif
endif


ifeq ($(MODE),test)
	GENERATED_FLAGS+=-Os
else ifeq ($(MODE),debug)
	DEBUG_SETTINGS=-fuse-ld=lld -Z7 -MTd
ifneq ($(CXX),clang-cl)
$(error can only debug with clang-cl)
endif

else ifeq ($(MODE),fast)
	GENERATED_FLAGS+=-D NDEBUG
	GENERATED_FLAGS+=-Ofast
endif


all:
ifeq ($(CXX),clang-cl)

ifdef LINKER
	$(error cannot link separately when compiling with clang-cl)
endif
	$(CXX) $(DEBUG_SETTINGS) $(SOURCE) $(GENERATED_FLAGS) -o $(OUT) /link $(LINKING_FLAGS)
else
ifdef LINKER
	$(CXX) -c $(DEBUG_SETTINGS) $(SOURCE) $(GENERATED_FLAGS) -o builds/temp_unlinked_binary.o
	$(LINKER) builds/temp_unlinked_binary.o $(LINKING_FLAGS) -o $(OUT)
else
	$(CXX) $(DEBUG_SETTINGS) $(SOURCE) $(GENERATED_FLAGS) -o $(OUT) $(LINKING_FLAGS)
endif
endif

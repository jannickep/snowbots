.SUFFIXES: .o .cpp

OPTIMIZE=off
DEBUG=on
CXX=g++
CXXFLAGS = -Wall -ansi -pedantic -Wextra -Winit-self -Wno-long-long -Wformat #-Weffc++ 
# -DTIXML_USE_TICPP
INCLUDEPATH = -I/usr/include/boost/ -I. -I$(CURDIR)/src
CXXFLAGS += $(INCLUDEPATH)
CPPFLAGS += $(INCLUDEPATH)
LIBS= -lrt -L/usr/lib -lboost_system -lboost_thread -lboost_date_time



ifeq ($(OPTIMIZE),on)
  CXXFLAGS+= -O3 -DNDEBUG
endif

ifeq ($(DEBUG),on)
  CXXFLAGS+= -g3
endif


#SKIPFILES=$(wildcard FOOBAR*.cpp)
SOURCES=$(filter-out $(SKIPFILES), $(shell find . -name "*.cpp" -a ! -wholename "*unittests*"  -a ! -wholename "*demo*" | sed 's_\./__'))
OBJECTS=$(SOURCES:%.cpp=%.o)

export CXX CXXFLAGS CPPFLAGS INCLUDEPATH LIBS

DEMOSOURCES=$(shell find . -name "*.cpp" -a -wholename "*demo*")
DEMOBINARIES=$(DEMOSOURCES:%.cpp=%)


FOLDER_SRC=src

MY_TARGETS=$(FOLDER_SRC)

.PHONY : all $(MY_TARGETS) unittests clean docs

all: $(MY_TARGETS) ${DEMOBINARIES}


# need DEMO_RULE to add dependency to the demos object file.
define DEMO_RULE
$(1): $(OBJECTS) $(1).o
endef

$(foreach t, $(DEMOBINARIES),$(eval $(call DEMO_RULE,$(t))))

${DEMOBINARIES} : $(OBJECTS)
	@$(CXX) $(CXXFLAGS) $(OBJECTS) $(LIBS) ${@:%=%.o} -o $@



$(MY_TARGETS):
	$(MAKE) -C $@ all

unittests:
	$(MAKE) all
	$(MAKE) -C src unittests

clean:
	rm -f $(DEMOBINARIES)  *.d *.o
	$(MAKE) -C src/ clean

docs:
	$(MAKE) -C src/ docs

docsclean:
	$(MAKE) -C src/ docsclean


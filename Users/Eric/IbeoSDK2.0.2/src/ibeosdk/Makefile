SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:%.cpp=%.o)

FOLDER_MISC=misc
FOLDER_DATABLOCKS=datablocks
FOLDER_DEVCICES=devices
FOLDER_LISTENER=listener
FOLDER_UNITTESTS=unittests

MY_TARGETS = $(FOLDER_MISC) $(FOLDER_DATABLOCKS) $(FOLDER_DEVCICES) $(FOLDER_LISTENER)

.PHONY : all $(MY_TARGETS) clean unittests

all: $(MY_TARGETS) $(OBJECTS)

$(MY_TARGETS):
	$(MAKE) -C $@ all

%.d: %.cpp
	@$(SHELL) -ec '$(CXX) -MM $(CPPFLAGS) $< \
                      | sed '\''s_\($*\)\.o[ :]*_\1.o $@ : _g'\'' > $@; \
                      [ -s $@ ] || rm -f $@'

clean:
	rm -f *.o *.d
	$(MAKE) -C $(FOLDER_MISC) clean
	$(MAKE) -C $(FOLDER_DATABLOCKS) clean
	$(MAKE) -C $(FOLDER_DEVCICES) clean
	$(MAKE) -C $(FOLDER_LISTENER) clean
	$(MAKE) -C $(FOLDER_UNITTESTS) clean

unittests:
	$(MAKE) all
	$(MAKE) -C $(FOLDER_UNITTESTS)

-include $(OBJECTS:.o=.d)


SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:%.cpp=%.o)

FOLDER_IBEOSDK=ibeosdk
FOLDER_DEMO=demo

MY_TARGETS = $(FOLDER_IBEOSDK) $(FOLDER_DEMO)

.PHONY : all $(MY_TARGETS) clean docs

all: $(MY_TARGETS) $(OBJECTS)

$(MY_TARGETS):
	$(MAKE) -C $@ all

%.d: %.cpp
	@$(SHELL) -ec '$(CXX) -MM $(CPPFLAGS) $< \
                      | sed '\''s_\($*\)\.o[ :]*_\1.o $@ : _g'\'' > $@; \
                      [ -s $@ ] || rm -f $@'

clean:
	rm -f *.o *.d
	$(MAKE) -C $(FOLDER_IBEOSDK) clean
	$(MAKE) -C $(FOLDER_DEMO) clean

docs:
	doxygen ./Doxyfile

docsclean:
	rm -rf docs/latex
	rm -rf docs/html

-include $(OBJECTS:.o=.d)


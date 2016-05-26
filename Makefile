all: clean
	mkdir build && cd build && cmake .. && make && mv 42sh ..

RM += -r
clean:
	$(RM) build
	$(RM) doc/doxygen
	$(RM) 42sh

.PHONY : doc
doc:
	$(RM) doc/doxygen
	$(MAKE) -C build doc

.PHONY: run
run:
	cd build && make && mv 42sh .. && cd .. && ./42sh $(ARGS)

compile:
	$(MAKE) -C build all

check:
	$(MAKE) -C build all
	$(MAKE) -C build check

debug:clean
	mkdir build && cd build && cmake .. -DBUILD_TYPE:STRING=DEBUG && make && mv 42sh ..

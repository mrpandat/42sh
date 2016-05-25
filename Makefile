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


check:
	$(MAKE) -C build check


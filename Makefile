all: clean
	mkdir build && cd build && cmake .. && make && mv 42sh ..

RM += -r
clean:
	$(RM) build
	$(RM) doc/doxygen
	$(RM) doc/git.html
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
	$(RM) doc/report
	$(MAKE) -C build all
	$(MAKE) -C build check


ifeq (test,$(firstword $(MAKECMDGOALS)))
  TEST_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(TEST_ARGS):;@:)
endif

test:
	python3 tests/test.py -c $(TEST_ARGS)

ifeq (testb,$(firstword $(MAKECMDGOALS)))
  TEST_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(TEST_ARGS):;@:)
endif

testb:
	python3 tests/test.py -x $(TEST_ARGS)

report:
	$(MAKE) -C build report


debug:clean
	mkdir build && cd build && cmake .. -DBUILD_TYPE:STRING=DEBUG && make && mv 42sh ..

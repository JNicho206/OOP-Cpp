CC=g++
CFLAGS=-std=c++17 -Wall -g
DFLAGS=

# The source files we use for building custom_tests
ALL_SRC=$(wildcard *.cpp)

# The name of the resulting executable
APP=test

ifeq ($(part1), on)
	DFLAGS += -DPART1
endif

ifeq ($(part2), on)
	DFLAGS += -DPART2
endif

ifdef traces
	empty=
	space=$(empty) $(empty)
	comma=,
	_traces=$(subst $(comma),$(space),$(traces))
endif

ifdef _traces
	ALL_SRC += $(foreach trace,$(_traces),$(trace).cpp)
	DFLAGS += -DRUN_TRACES="$(foreach trace,$(_traces),if ($(trace)()) {std::cout << \"Error in trace $(trace)\\n\"; return 1;})"
	DFLAGS += -DDECLARE_TRACES="$(foreach trace,$(_traces),int $(trace)();)"
endif

trace_%.cpp : trace_%.txt
	python3 trace_files/compile_trace.py $<

part1: $(ALL_SRC)
	$(CC) $(CFLAGS) $^ -DPART1 -o $(APP)	

part2: $(ALL_SRC)
	$(CC) $(CFLAGS) $^ -DPART1 -DPART2 -o $(APP)

custom_tests: $(ALL_SRC)
	$(CC) $(CFLAGS) $^ $(DFLAGS) -o $(APP)

clean:
	rm -f $(APP)

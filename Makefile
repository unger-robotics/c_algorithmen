# ju -- 2026 -- Makefile  (macOS / clang)
# Portabler Auto-Discovery-Build: jedes .c/.cpp unter src/ wird zu einem
# eigenen Programm in build/ (gleiche Unterordner-Struktur).
# Getestet mit Apple clang + GNU Make 3.81.

CC       := cc
CXX      := c++
WARN     := -Wall -Wextra -Wno-missing-field-initializers
CFLAGS   := $(WARN) -std=c17   -O0 -g -Ilib
CXXFLAGS := $(WARN) -std=c++17 -O0 -g -Ilib
LDLIBS   := -lm

BUILD := build
# Gemeinsame Bibliothek, in jedes Programm mitkompiliert.
LIB_C := lib/meineFkt.c lib/trace.c

# Auto-Discovery: keine handgepflegte Ziel-Liste mehr.
SRCS_C   := $(shell find src -name '*.c')
SRCS_CPP := $(shell find src -name '*.cpp')
BIN_C    := $(patsubst src/%.c,$(BUILD)/%,$(SRCS_C))
BIN_CPP  := $(patsubst src/%.cpp,$(BUILD)/%,$(SRCS_CPP))

all: $(BIN_C) $(BIN_CPP)

$(BUILD)/%: src/%.c $(LIB_C)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $< $(LIB_C) $(LDLIBS)

# Unit-Tests (Logik) liegen unter tests/unit/ und damit AUSSERHALB des
# src-Auto-Discovery: sie sind nicht Teil von 'make all' und bekommen kein
# Trace/Golden/Manifest. Eigene Variablen + eigener build/tests-Unterbaum.
TEST_SRC := $(wildcard tests/unit/*.c)
TEST_BIN := $(patsubst tests/unit/%.c,$(BUILD)/tests/%,$(TEST_SRC))

$(BUILD)/tests/%: tests/unit/%.c $(LIB_C)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $< $(LIB_C) $(LDLIBS)

# C++-Beispiele sind eigenstaendig (nutzen die C-Trace-Lib nicht).
$(BUILD)/%: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDLIBS)

# Ein Programm bauen und ausfuehren:
#   make run NAME=grundlagen/modulo
run: $(BUILD)/$(NAME)
	@./$(BUILD)/$(NAME)

# Trace fuer den Web-Player erzeugen:
#   make trace NAME=algorithmen/sortieren/bubblesort OUT=web/traces/bubblesort.json
trace: $(BUILD)/$(NAME)
	@./$(BUILD)/$(NAME) --trace $(OUT)
	@echo "Trace -> $(OUT)"

# Alle Demo-Traces (neu) erzeugen.
traces: all
	@sh tools/gen-traces.sh

# Web-Player lokal servieren (Pflicht wegen fetch/CORS):
#   danach http://localhost:8000/web/ oeffnen
web:
	@echo "Web-Player:  http://localhost:8000/web/"
	@python3 -m http.server 8000

# Logik-Tests: alle Unit-Tests bauen und ausfuehren (Exit != 0 bei Fehler).
test: $(TEST_BIN)
	@fail=0; for t in $(TEST_BIN); do \
	  echo "== $$t =="; "$$t" || fail=1; \
	done; \
	[ $$fail -eq 0 ] && echo "Unit-Tests: alle bestanden." \
	  || { echo "Unit-Tests: FEHLER."; exit 1; }

# Speicher-Check: alle Programme + Unit-Tests mit ASan/UBSan bauen und laufen
# lassen (LSan nur unter Linux). Logik steckt im Skript (auch ohne Make nutzbar).
memcheck:
	@sh tools/check-memory.sh

clean:
	rm -rf $(BUILD)

.PHONY: all run trace traces web test memcheck clean

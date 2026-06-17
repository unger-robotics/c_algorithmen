// ju -- 2026 -- test_trace.c
// Unit-Test fuer den Lebenszyklus der Trace-Bibliothek (lib/trace.c):
//   1. Ohne --trace ist Tracing inaktiv und alle trace_*-Aufrufe sind No-Ops.
//   2. Mit --trace <datei> entsteht eine Datei mit dem erwarteten JSON-Geruest.
// Das volle Trace-Schema prueft tools/check-traces.py an den echten Demo-Traces;
// hier geht es nur um init/No-Op/finish und die grobe Struktur (Substrings).
// Assert-basiert: Exit 0 = ok. Fester /tmp-Pfad (immer beschreibbar, kein
// POSIX-Feature-Macro noetig wie bei mkstemp).

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "trace.h"

#define SELF "/tmp/c_algorithmen_trace_selftest.json"

int main(void) {
  // 1) Ohne --trace: trace_init meldet 0, Tracing bleibt inaktiv. Die folgende
  //    vollstaendige Aufruffolge darf als No-Op weder schreiben noch crashen.
  char *argv_off[] = { "t" };
  assert(trace_init(1, argv_off) == 0);
  assert(trace_is_active() == 0);
  int a[] = { 3, 1, 2 };
  trace_begin("x", "X", "array");
  trace_init_array(a, 3);
  trace_compare(0, 1);
  trace_swap(0, 1);
  trace_done();
  trace_finish();
  assert(trace_is_active() == 0);

  // 2) Mit --trace <datei>: Tracing aktiv, vollstaendige Sequenz schreiben.
  char *argv_on[] = { "t", "--trace", SELF };
  assert(trace_init(3, argv_on) == 1);
  assert(trace_is_active() == 1);
  trace_begin("quicksort", "Quicksort", "array");
  trace_init_array(a, 3);
  trace_compare(0, 1);
  trace_swap(0, 1);
  trace_done();
  trace_finish();
  assert(trace_is_active() == 0);   // finish hat den Strom geschlossen

  // Datei zuruecklesen und grobe Struktur pruefen.
  FILE *f = fopen(SELF, "r");
  assert(f != NULL);
  char buf[4096];
  size_t n = fread(buf, 1, sizeof buf - 1, f);
  buf[n] = '\0';
  fclose(f);
  remove(SELF);

  assert(strstr(buf, "\"algo\":\"quicksort\"") != NULL);
  assert(strstr(buf, "\"view\":\"array\"")     != NULL);
  assert(strstr(buf, "\"events\":")            != NULL);
  assert(strstr(buf, "\"t\":\"done\"")         != NULL);

  printf("test_trace: OK\n");
  return 0;
}

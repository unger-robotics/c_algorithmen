/* ju -- 2026 -- stack.c
 * Stack (Stapel, LIFO): push legt oben ab, pop nimmt oben weg. Nur das
 * oberste Element ist zugänglich. Hier mit einem Array realisiert.
 */
#include <stdio.h>
#include "trace.h"

static int werte[64], ids[64], top = -1, idc = 0;

static void push(int v) {
  int id = idc++;
  top++; werte[top] = v; ids[top] = id;
  trace_node(id, v, -1, NULL);
}
static int pop(void) {
  if (top < 0) return -1;
  int id = ids[top], v = werte[top];
  trace_visit(id);
  trace_remove_node(id);
  top--;
  return v;
}

int main(int argc, char **argv) {
  trace_init(argc, argv);
  trace_begin("stack", "Stack (LIFO)", "tree");
  trace_init_layout("chain-v");
  trace_note("Stack: push legt oben auf, pop nimmt das oberste Element.");

  push(5); push(3); push(8); push(1);
  trace_note("pop() entfernt das zuletzt eingefügte Element (1, dann 8).");
  pop(); pop();
  trace_note("push(9) legt wieder oben auf.");
  push(9);
  trace_done();
  trace_finish();

  printf("Stack von oben: ");
  for (int i = top; i >= 0; i--) printf("%d ", werte[i]);
  printf("\n");
  return 0;
}

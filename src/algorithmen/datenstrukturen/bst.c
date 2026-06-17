/* ju -- 2026 -- bst.c
 * Binärer Suchbaum (BST): kleinere Werte links, größere rechts. Einfügen und
 * Suchen folgen demselben Vergleichspfad von der Wurzel nach unten.
 * Mittlere Höhe O(log n).
 */
#include <stdio.h>
#include <stdlib.h>
#include "trace.h"

typedef struct Node { int val, id; struct Node *l, *r; } Node;
static int idc = 0;

static Node *einfuegen(Node *root, int v, int parentId, const char *seite) {
  if (!root) {
    // Leerer Teilbaum erreicht -> genau hier gehört der neue Wert hin.
    Node *n = malloc(sizeof *n);
    if (!n) { perror("malloc"); exit(1); }   // bei Speichermangel sauber abbrechen
    n->val = v; n->id = idc++; n->l = n->r = NULL;
    trace_node(n->id, v, parentId, seite);
    return n;
  }
  trace_compare_node(root->id, v);            /* Vergleichspfad zeigen */
  // BST-Regel: kleinere Werte links, größere rechts weitersuchen. So bleibt der
  // Baum sortiert und der Pfad von der Wurzel ist eindeutig.
  if (v < root->val) root->l = einfuegen(root->l, v, root->id, "left");
  else               root->r = einfuegen(root->r, v, root->id, "right");
  return root;
}

static void suchen(Node *root, int v) {
  Node *cur = root;
  while (cur) {
    trace_compare_node(cur->id, v);
    if (v == cur->val) { trace_found(cur->id); return; }
    cur = (v < cur->val) ? cur->l : cur->r;
  }
}

static void inorder(Node *n) {
  if (!n) return;
  inorder(n->l); printf("%d ", n->val); inorder(n->r);
}

static void freigeben(Node *n) {   // Baum post-order freigeben: erst Kinder, dann Wurzel
  if (!n) return;
  freigeben(n->l); freigeben(n->r); free(n);
}

int main(int argc, char **argv) {
  trace_init(argc, argv);
  trace_begin("bst", "Binärer Suchbaum", "tree");
  trace_init_layout("tree");
  trace_note("BST: kleinere Werte nach links, größere nach rechts einfügen.");

  int werte[] = {8, 3, 10, 1, 6, 14, 4, 7, 13};
  int n = (int)(sizeof werte / sizeof werte[0]);
  Node *root = NULL;
  for (int i = 0; i < n; i++) root = einfuegen(root, werte[i], -1, NULL);

  trace_note("Suche nach 7: dem Vergleichspfad von der Wurzel folgen.");
  suchen(root, 7);
  trace_done();
  trace_finish();

  printf("Inorder (sortiert): ");
  inorder(root);
  printf("\n");
  freigeben(root);
  return 0;
}

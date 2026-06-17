/* renderTree.js — Renderer für view "tree": Datenstrukturen aus Knoten.
 * Layout über init.layout:
 *   "tree"     binärer Suchbaum (parent + pos = left/right)
 *   "chain-h"  horizontale Kette (verkettete Liste, Queue)
 *   "chain-v"  vertikaler Stapel (Stack)
 *   "hash"     Hashtabelle (Buckets mit Ketten)
 */
(function () {
  "use strict";
  window.RENDERERS = window.RENDERERS || {};

  function cssvar(v) {
    return getComputedStyle(document.documentElement).getPropertyValue(v).trim() || "#888";
  }

  window.RENDERERS.tree = function (canvas, trace) {
    var ctx = canvas.getContext("2d");
    var W = canvas.width, H = canvas.height;
    var layout = (trace.init && trace.init.layout) || "tree";

    var pal = {
      node:    cssvar("--c-default"),
      visit:   cssvar("--c-visit"),
      compare: cssvar("--c-compare"),
      found:   cssvar("--c-found"),
      ink:     cssvar("--ink"),
      muted:   cssvar("--muted"),
      accent:  cssvar("--accent"),
      line:    cssvar("--line")
    };

    var nodes, order, edges, buckets, active, foundId;

    function reset() {
      nodes = {};      // id -> {id,val,parent,pos}
      order = [];      // Einfügereihenfolge (für Ketten)
      edges = [];      // {from,to}
      buckets = {};    // idx -> [ids]  (hash)
      active = {};     // transiente Hervorhebung (nur aktueller Schritt)
      foundId = null;  // gefundener Knoten (bleibt markiert)
    }

    function apply(ev) {
      active = {};
      switch (ev.t) {
        case "addNode":
          nodes[ev.id] = { id: ev.id, val: ev.val, parent: ev.parent, pos: ev.pos };
          order.push(ev.id);
          active.add = ev.id;
          break;
        case "removeNode":
          delete nodes[ev.id];
          order = order.filter(function (x) { return x !== ev.id; });
          edges = edges.filter(function (e) { return e.from !== ev.id && e.to !== ev.id; });
          active.remove = ev.id;
          break;
        case "addEdge":
          edges.push({ from: ev.from, to: ev.to });
          break;
        case "visit":       active.visit = ev.id; break;
        case "compareNode": active.compare = ev.id; break;
        case "found":       foundId = ev.i; break;
        case "bucket":      buckets[ev.idx] = (ev.ids || []).slice(); break;
        default: break;
      }
    }

    function colorOf(id) {
      if (foundId === id)        return pal.found;
      if (active.visit === id)   return pal.visit;
      if (active.compare === id) return pal.compare;
      if (active.add === id)     return pal.accent;
      return pal.node;
    }

    /* ---- gemeinsame Zeichenprimitive -------------------------------------- */
    function nodeCircle(x, y, r, id) {
      ctx.beginPath(); ctx.arc(x, y, r, 0, 2 * Math.PI);
      ctx.fillStyle = colorOf(id); ctx.fill();
      ctx.fillStyle = "#06101f"; ctx.font = "bold 15px system-ui, sans-serif";
      ctx.textAlign = "center"; ctx.textBaseline = "middle";
      ctx.fillText(nodes[id].val, x, y);
    }
    function nodeBox(x, y, w, h, id) {
      ctx.fillStyle = colorOf(id);
      roundRect(x, y, w, h, 8); ctx.fill();
      ctx.fillStyle = "#06101f"; ctx.font = "bold 15px system-ui, sans-serif";
      ctx.textAlign = "center"; ctx.textBaseline = "middle";
      ctx.fillText(nodes[id].val, x + w / 2, y + h / 2);
    }
    function arrow(x1, y1, x2, y2) {
      ctx.strokeStyle = pal.muted; ctx.lineWidth = 2;
      ctx.beginPath(); ctx.moveTo(x1, y1); ctx.lineTo(x2, y2); ctx.stroke();
      var ang = Math.atan2(y2 - y1, x2 - x1), s = 8;
      ctx.beginPath();
      ctx.moveTo(x2, y2);
      ctx.lineTo(x2 - s * Math.cos(ang - 0.4), y2 - s * Math.sin(ang - 0.4));
      ctx.lineTo(x2 - s * Math.cos(ang + 0.4), y2 - s * Math.sin(ang + 0.4));
      ctx.closePath(); ctx.fillStyle = pal.muted; ctx.fill();
    }
    function roundRect(x, y, w, h, r) {
      r = Math.max(0, Math.min(r, w / 2, h / 2));
      ctx.beginPath();
      ctx.moveTo(x + r, y);
      ctx.arcTo(x + w, y, x + w, y + h, r);
      ctx.arcTo(x + w, y + h, x, y + h, r);
      ctx.arcTo(x, y + h, x, y, r);
      ctx.arcTo(x, y, x + w, y, r);
      ctx.closePath();
    }

    /* ---- Layouts ---------------------------------------------------------- */
    function drawChain(horizontal) {
      var ids = order.slice();
      var n = ids.length;
      ctx.textAlign = "center"; ctx.textBaseline = "middle";
      if (!n) return;
      var bw = 64, bh = 44;
      if (horizontal) {
        var gap = 40, totalW = n * bw + (n - 1) * gap;
        var x0 = (W - totalW) / 2, y = H / 2 - bh / 2;
        var pos = {};
        ids.forEach(function (id, k) {
          var x = x0 + k * (bw + gap);
          pos[id] = { x: x, y: y };
        });
        edges.forEach(function (e) {
          if (pos[e.from] && pos[e.to])
            arrow(pos[e.from].x + bw, pos[e.from].y + bh / 2, pos[e.to].x, pos[e.to].y + bh / 2);
        });
        ids.forEach(function (id) { nodeBox(pos[id].x, pos[id].y, bw, bh, id); });
      } else {
        var gapv = 14, totalH = n * (bh + gapv) - gapv;
        var y0 = (H - totalH) / 2, x = W / 2 - bw / 2;
        // jüngstes Element (zuletzt eingefügt) oben darstellen
        ids.slice().reverse().forEach(function (id, k) {
          nodeBox(x, y0 + k * (bh + gapv), bw, bh, id);
        });
        ctx.fillStyle = pal.muted; ctx.font = "13px system-ui, sans-serif";
        ctx.fillText("▲ oben (top)", x + bw / 2, y0 - 14);
      }
    }

    function drawTree() {
      var ids = Object.keys(nodes);
      if (!ids.length) return;
      var children = {};
      var root = null;
      ids.forEach(function (id) {
        var nd = nodes[id];
        if (nd.parent === undefined || nd.parent === null || !nodes[nd.parent]) root = id;
        else (children[nd.parent] = children[nd.parent] || []).push(id);
      });
      // In-Order-Durchlauf -> x-Rang; Tiefe -> y
      var xrank = {}, depth = {}, counter = 0, maxDepth = 0;
      function child(id, side) {
        var cs = children[id] || [];
        for (var i = 0; i < cs.length; i++) if (nodes[cs[i]].pos === side) return cs[i];
        return null;
      }
      (function inorder(id, d) {
        if (id == null) return;
        depth[id] = d; if (d > maxDepth) maxDepth = d;
        inorder(child(id, "left"), d + 1);
        xrank[id] = counter++;
        inorder(child(id, "right"), d + 1);
      })(root, 0);

      var padX = 50, padTop = 50, padBot = 40;
      var n = counter;
      var dx = n > 1 ? (W - 2 * padX) / (n - 1) : 0;
      var dy = maxDepth > 0 ? (H - padTop - padBot) / maxDepth : 0;
      var posOf = function (id) {
        return { x: padX + xrank[id] * dx, y: padTop + depth[id] * dy };
      };
      // Kanten
      ids.forEach(function (id) {
        (children[id] || []).forEach(function (c) {
          var p = posOf(id), q = posOf(c);
          ctx.strokeStyle = pal.muted; ctx.lineWidth = 2;
          ctx.beginPath(); ctx.moveTo(p.x, p.y); ctx.lineTo(q.x, q.y); ctx.stroke();
        });
      });
      // Knoten
      ids.forEach(function (id) { var p = posOf(id); nodeCircle(p.x, p.y, 20, id); });
    }

    function drawHash() {
      var idxs = Object.keys(buckets).map(Number).sort(function (a, b) { return a - b; });
      var B = idxs.length ? Math.max.apply(null, idxs) + 1 : 0;
      if (!B) return;
      var padX = 40, top = 56, colW = (W - 2 * padX) / B, slot = 40;
      ctx.textAlign = "center"; ctx.textBaseline = "middle";
      for (var i = 0; i < B; i++) {
        var cx = padX + i * colW + colW / 2;
        // Bucket-Kopf
        ctx.fillStyle = pal.line; roundRect(cx - 26, 18, 52, 26, 6); ctx.fill();
        ctx.fillStyle = pal.ink; ctx.font = "13px system-ui, sans-serif";
        ctx.fillText("[" + i + "]", cx, 31);
        var chain = buckets[i] || [];
        for (var k = 0; k < chain.length; k++) {
          var id = chain[k], y = top + k * (slot + 12);
          if (k > 0) arrow(cx, y - 12, cx, y - 2);
          if (nodes[id]) nodeBox(cx - 26, y, 52, slot, id);
        }
      }
    }

    function draw() {
      ctx.clearRect(0, 0, W, H);
      if (layout === "chain-h")      drawChain(true);
      else if (layout === "chain-v") drawChain(false);
      else if (layout === "hash")    drawHash();
      else                           drawTree();
    }

    reset();
    return { reset: reset, apply: apply, draw: draw };
  };
})();

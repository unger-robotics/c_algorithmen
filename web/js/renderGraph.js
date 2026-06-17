/* renderGraph.js — Renderer für view "graph" (BFS, DFS, Dijkstra).
 * Knoten tragen feste Koordinaten (0..100) aus dem Trace; der Renderer skaliert
 * sie auf die Canvas. Zeigt Besuch, Warteschlangen-Front, Kanten-Relaxation,
 * Distanzen und den finalen Pfad.
 */
(function () {
  "use strict";
  window.RENDERERS = window.RENDERERS || {};

  function cssvar(v) {
    return getComputedStyle(document.documentElement).getPropertyValue(v).trim() || "#888";
  }

  window.RENDERERS.graph = function (canvas, trace) {
    var ctx = canvas.getContext("2d");
    var W = canvas.width, H = canvas.height;
    var padX = 64, padY = 56, R = 22;

    var pal = {
      node:    cssvar("--c-default"),
      visit:   cssvar("--c-visit"),
      visited: "#3a4a6b",
      path:    cssvar("--c-path"),
      relax:   cssvar("--c-swap"),
      accent:  cssvar("--accent"),
      ink:     cssvar("--ink"),
      muted:   cssvar("--muted"),
      line:    "#3a4866"
    };

    var nodes, edges, dist, visited, pathSet, pathSeq, active;

    function reset() {
      nodes = {}; edges = []; dist = {};
      visited = {}; pathSet = {}; pathSeq = []; active = {};
    }

    function apply(ev) {
      active = {};
      switch (ev.t) {
        case "addNode": nodes[ev.id] = { id: ev.id, label: ev.label, x: ev.x, y: ev.y }; break;
        case "addEdge": edges.push({ from: ev.from, to: ev.to, w: ev.w, dir: ev.dir }); break;
        case "visit":   visited[ev.id] = true; active.visit = ev.id; break;
        case "frontier":active.frontier = {}; (ev.ids || []).forEach(function (i) { active.frontier[i] = true; }); break;
        case "relax":   active.relax = [ev.from, ev.to]; break;
        case "setDist": dist[ev.id] = ev.dist; break;
        case "path":    pathSeq = (ev.ids || []).slice(); pathSet = {};
                        pathSeq.forEach(function (i) { pathSet[i] = true; }); break;
        default: break;
      }
    }

    function px(n) { return padX + n.x / 100 * (W - 2 * padX); }
    function py(n) { return padY + n.y / 100 * (H - 2 * padY); }

    function colorOf(id) {
      if (pathSet[id])         return pal.path;
      if (active.visit === id) return pal.visit;
      if (visited[id])         return pal.visited;
      return pal.node;
    }

    function edgeOnPath(e) {
      // nur Kanten zwischen aufeinanderfolgenden Pfadknoten zählen (nicht jede
      // Kante zwischen zwei beliebigen Pfadknoten)
      for (var i = 0; i + 1 < pathSeq.length; i++)
        if ((pathSeq[i] === e.from && pathSeq[i + 1] === e.to) ||
            (pathSeq[i] === e.to   && pathSeq[i + 1] === e.from)) return true;
      return false;
    }

    function draw() {
      ctx.clearRect(0, 0, W, H);
      ctx.lineWidth = 2;

      // Kanten
      edges.forEach(function (e) {
        var a = nodes[e.from], b = nodes[e.to];
        if (!a || !b) return;
        var x1 = px(a), y1 = py(a), x2 = px(b), y2 = py(b);
        var hot = active.relax && ((active.relax[0] === e.from && active.relax[1] === e.to) ||
                                   (active.relax[0] === e.to && active.relax[1] === e.from));
        var onPath = edgeOnPath(e);
        ctx.strokeStyle = onPath ? pal.path : hot ? pal.relax : pal.line;
        ctx.lineWidth = (onPath || hot) ? 4 : 2;
        ctx.beginPath(); ctx.moveTo(x1, y1); ctx.lineTo(x2, y2); ctx.stroke();
        if (e.w !== undefined) {
          var mx = (x1 + x2) / 2, my = (y1 + y2) / 2;
          ctx.fillStyle = "#0c1322";
          ctx.beginPath(); ctx.arc(mx, my, 12, 0, 2 * Math.PI); ctx.fill();
          ctx.fillStyle = pal.ink; ctx.font = "12px system-ui, sans-serif";
          ctx.textAlign = "center"; ctx.textBaseline = "middle";
          ctx.fillText(e.w, mx, my);
        }
      });

      // Knoten
      Object.keys(nodes).forEach(function (id) {
        var n = nodes[id], x = px(n), y = py(n);
        if (active.frontier && active.frontier[id]) {
          ctx.strokeStyle = pal.accent; ctx.lineWidth = 3;
          ctx.beginPath(); ctx.arc(x, y, R + 5, 0, 2 * Math.PI); ctx.stroke();
        }
        ctx.beginPath(); ctx.arc(x, y, R, 0, 2 * Math.PI);
        ctx.fillStyle = colorOf(id); ctx.fill();
        ctx.fillStyle = "#06101f"; ctx.font = "bold 16px system-ui, sans-serif";
        ctx.textAlign = "center"; ctx.textBaseline = "middle";
        ctx.fillText(n.label, x, y);
        if (dist[id] !== undefined) {
          ctx.fillStyle = pal.accent; ctx.font = "12px system-ui, sans-serif";
          var d = dist[id] >= 1e9 ? "∞" : dist[id];
          ctx.fillText("d=" + d, x, y - R - 10);
        }
      });
    }

    reset();
    return { reset: reset, apply: apply, draw: draw };
  };
})();

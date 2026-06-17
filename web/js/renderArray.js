/* renderArray.js — Renderer für view "array" (Sortieren, Suchen, Strings).
 * Zahlen werden als Balken gezeichnet; liegt init.labels vor (Strings), werden
 * stattdessen gleich hohe Buchstaben-Kästen gezeigt. Farben markieren
 * Vergleich/Tausch/Pivot, endgültig sortierte und gefundene Positionen sowie
 * benannte Zeiger.
 */
(function () {
  "use strict";
  window.RENDERERS = window.RENDERERS || {};

  function cssvar(v) {
    return getComputedStyle(document.documentElement).getPropertyValue(v).trim() || "#888";
  }

  window.RENDERERS.array = function (canvas, trace) {
    var ctx = canvas.getContext("2d");
    var W = canvas.width, H = canvas.height;
    var baseArr = (trace.init && trace.init.array)  ? trace.init.array.slice()  : [];
    var baseLbl = (trace.init && trace.init.labels) ? trace.init.labels.slice() : null;

    var pal = {
      def:    cssvar("--c-default"), compare: cssvar("--c-compare"),
      swap:   cssvar("--c-swap"),    pivot:   cssvar("--c-pivot"),
      sorted: cssvar("--c-sorted"),  found:   cssvar("--c-found"),
      ink:    cssvar("--ink"),       muted:   cssvar("--muted"),
      accent: cssvar("--accent")
    };

    var values, labels, sorted, pointers, found, active;

    function reset() {
      values = baseArr.slice();
      labels = baseLbl ? baseLbl.slice() : null;
      sorted = {}; pointers = {}; found = null; active = {};
    }

    function apply(ev) {
      active = {};
      switch (ev.t) {
        case "compare":    active.compare = [ev.i, ev.j]; break;
        case "swap":
          if (labels) { var s = labels[ev.i]; labels[ev.i] = labels[ev.j]; labels[ev.j] = s; }
          else        { var t = values[ev.i]; values[ev.i] = values[ev.j]; values[ev.j] = t; }
          active.swap = [ev.i, ev.j]; break;
        case "set":        values[ev.i] = ev.val; active.set = ev.i; break;
        case "highlight":  active.highlight = (ev.idx || []).slice(); break;
        case "markSorted": sorted[ev.i] = true; break;
        case "pointer":    pointers[ev.name] = ev.i; break;
        case "found":      found = ev.i; active.found = ev.i; break;
        default:           break;
      }
    }

    function colorOf(i) {
      if (active.compare && (i === active.compare[0] || i === active.compare[1])) return pal.compare;
      if (active.swap && (i === active.swap[0] || i === active.swap[1]))           return pal.swap;
      if (active.highlight && active.highlight.indexOf(i) >= 0)                    return pal.pivot;
      if (found === i)  return pal.found;
      if (sorted[i])    return pal.sorted;
      return pal.def;
    }

    function drawPointers(n, geom) {
      var py = H - 30;
      ctx.fillStyle = pal.accent; ctx.font = "13px system-ui, sans-serif"; ctx.textAlign = "center";
      Object.keys(pointers).forEach(function (name) {
        if (pointers[name] < 0 || pointers[name] >= n) return;
        ctx.fillText("▲ " + name, geom(pointers[name]), py);
      });
    }

    function drawLabels() {
      var n = labels.length;
      ctx.clearRect(0, 0, W, H);
      var padX = 40, bw = Math.min(72, (W - 2 * padX) / n - 12), gap = (W - 2 * padX - n * bw) / (n - 1 || 1);
      var bh = 70, y = H / 2 - bh / 2 - 10;
      var geom = function (i) { return padX + i * (bw + gap) + bw / 2; };
      ctx.textAlign = "center"; ctx.textBaseline = "middle";
      for (var i = 0; i < n; i++) {
        var x = padX + i * (bw + gap);
        ctx.fillStyle = colorOf(i); roundRect(x, y, bw, bh, 8); ctx.fill();
        ctx.fillStyle = "#06101f"; ctx.font = "bold 26px system-ui, sans-serif";
        ctx.fillText(labels[i], x + bw / 2, y + bh / 2);
        ctx.fillStyle = pal.muted; ctx.font = "12px system-ui, sans-serif";
        ctx.fillText(i, x + bw / 2, y + bh + 16);
      }
      drawPointers(n, geom);
    }

    function drawBars() {
      ctx.clearRect(0, 0, W, H);
      var n = values.length; if (!n) return;
      var padX = 40, padTop = 36, padBot = 70;
      var bw = (W - 2 * padX) / n, barW = Math.max(4, bw * 0.72);
      var maxV = Math.max.apply(null, values.concat([1])), areaH = H - padTop - padBot;
      ctx.font = "13px system-ui, sans-serif"; ctx.textAlign = "center";
      for (var i = 0; i < n; i++) {
        var x = padX + i * bw + bw / 2;
        var h = Math.round(areaH * values[i] / maxV), y = H - padBot - h;
        ctx.fillStyle = colorOf(i); roundRect(x - barW / 2, y, barW, h, 4); ctx.fill();
        if (n <= 28) { ctx.fillStyle = pal.ink;   ctx.fillText(values[i], x, y - 6); }
        if (n <= 40) { ctx.fillStyle = pal.muted; ctx.fillText(i, x, H - padBot + 18); }
      }
      drawPointers(n, function (i) { return padX + i * bw + bw / 2; });
    }

    function draw() { if (labels) drawLabels(); else drawBars(); }

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

    reset();
    return { reset: reset, apply: apply, draw: draw };
  };
})();

/* renderArray.js — Renderer für view "array" (Sortieren, Suchen).
 * Zeichnet die Werte als Balken; Farben markieren Vergleich/Tausch/Pivot,
 * endgültig sortierte und gefundene Positionen sowie benannte Zeiger.
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
    var base = (trace.init && trace.init.array) ? trace.init.array.slice() : [];

    var pal = {
      def:    cssvar("--c-default"),
      compare:cssvar("--c-compare"),
      swap:   cssvar("--c-swap"),
      pivot:  cssvar("--c-pivot"),
      sorted: cssvar("--c-sorted"),
      found:  cssvar("--c-found"),
      ink:    cssvar("--ink"),
      muted:  cssvar("--muted"),
      accent: cssvar("--accent")
    };

    var values, sorted, pointers, found, active;

    function reset() {
      values = base.slice();
      sorted = {};
      pointers = {};
      found = null;
      active = {};
    }

    function apply(ev) {
      active = {};   // transiente Hervorhebung gilt nur für diesen Schritt
      switch (ev.t) {
        case "compare":    active.compare = [ev.i, ev.j]; break;
        case "swap":       var t = values[ev.i]; values[ev.i] = values[ev.j]; values[ev.j] = t;
                           active.swap = [ev.i, ev.j]; break;
        case "set":        values[ev.i] = ev.val; active.set = ev.i; break;
        case "highlight":  active.highlight = (ev.idx || []).slice(); break;
        case "markSorted": sorted[ev.i] = true; break;
        case "pointer":    pointers[ev.name] = ev.i; break;
        case "found":      found = ev.i; active.found = ev.i; break;
        default:           break;   // note/done
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

    function draw() {
      ctx.clearRect(0, 0, W, H);
      var n = values.length;
      if (!n) return;
      var padX = 40, padTop = 36, padBot = 70;
      var bw = (W - 2 * padX) / n;
      var barW = Math.max(4, bw * 0.72);
      var maxV = Math.max.apply(null, values.concat([1]));
      var areaH = H - padTop - padBot;

      ctx.font = "13px -apple-system, system-ui, sans-serif";
      ctx.textAlign = "center";

      for (var i = 0; i < n; i++) {
        var x = padX + i * bw + bw / 2;
        var h = Math.round(areaH * values[i] / maxV);
        var y = H - padBot - h;
        ctx.fillStyle = colorOf(i);
        roundRect(ctx, x - barW / 2, y, barW, h, 4); ctx.fill();
        if (n <= 28) { ctx.fillStyle = pal.ink;   ctx.fillText(values[i], x, y - 6); }
        if (n <= 40) { ctx.fillStyle = pal.muted; ctx.fillText(i, x, H - padBot + 18); }
      }

      // benannte Zeiger (lo/hi/mid …) unter ihrer Position
      var py = H - padBot + 40;
      ctx.fillStyle = pal.accent;
      Object.keys(pointers).forEach(function (name) {
        var x = padX + pointers[name] * bw + bw / 2;
        ctx.fillText("▲ " + name, x, py);
      });
    }

    function roundRect(c, x, y, w, h, r) {
      r = Math.max(0, Math.min(r, w / 2, h / 2));
      c.beginPath();
      c.moveTo(x + r, y);
      c.arcTo(x + w, y, x + w, y + h, r);
      c.arcTo(x + w, y + h, x, y + h, r);
      c.arcTo(x, y + h, x, y, r);
      c.arcTo(x, y, x + w, y, r);
      c.closePath();
    }

    reset();
    return { reset: reset, apply: apply, draw: draw };
  };
})();

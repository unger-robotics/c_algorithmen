/* renderLotto.js — Renderer für view "lotto" (Urnenmodell, Lotto 6 aus 49).
 * Zeichnet die Zahlen 1..49 als 7x7-Gitter; gezogene Zahlen werden grün, die
 * zuletzt gezogene gelb hervorgehoben. Ein markSorted-Event = eine Ziehung.
 */
(function () {
  "use strict";
  window.RENDERERS = window.RENDERERS || {};

  function cssvar(v) {
    return getComputedStyle(document.documentElement).getPropertyValue(v).trim() || "#888";
  }

  window.RENDERERS.lotto = function (canvas, trace) {
    var ctx = canvas.getContext("2d");
    var W = canvas.width, H = canvas.height;
    var zahlen = (trace.init && trace.init.array) ? trace.init.array.slice() : [];
    var pal = {
      def:   "#26314a",
      drawn: cssvar("--c-sorted"),
      last:  cssvar("--c-compare"),
      ink:   cssvar("--ink"),
      muted: cssvar("--muted")
    };

    var gezogen, last;

    function reset() { gezogen = []; last = -1; }
    function apply(ev) {
      if (ev.t === "markSorted") { gezogen.push(ev.i); last = ev.i; }
    }

    function draw() {
      ctx.clearRect(0, 0, W, H);
      var n = zahlen.length; if (!n) return;
      var cols = 7, rows = Math.ceil(n / cols);
      var cw = 50, gap = 10;
      var gridW = cols * cw + (cols - 1) * gap;
      var gridH = rows * cw + (rows - 1) * gap;
      var x0 = (W - gridW) / 2, y0 = (H - gridH) / 2 - 16;
      var drawnSet = {};
      gezogen.forEach(function (i) { drawnSet[i] = true; });

      ctx.textAlign = "center"; ctx.textBaseline = "middle";
      for (var idx = 0; idx < n; idx++) {
        var r = Math.floor(idx / cols), c = idx % cols;
        var x = x0 + c * (cw + gap), y = y0 + r * (cw + gap);
        var isLast = idx === last, isDrawn = drawnSet[idx];
        ctx.fillStyle = isLast ? pal.last : isDrawn ? pal.drawn : pal.def;
        roundRect(x, y, cw, cw, 8); ctx.fill();
        ctx.fillStyle = (isLast || isDrawn) ? "#06101f" : pal.muted;
        ctx.font = (isLast || isDrawn ? "bold " : "") + "16px system-ui, sans-serif";
        ctx.fillText(zahlen[idx], x + cw / 2, y + cw / 2);
      }

      // gezogene Zahlen als Liste
      ctx.fillStyle = pal.ink; ctx.font = "15px system-ui, sans-serif"; ctx.textAlign = "center";
      var liste = gezogen.map(function (i) { return zahlen[i]; });
      ctx.fillText("Ziehung " + gezogen.length + " / 6   —   gezogen: " +
                   (liste.length ? liste.join(", ") : "–"), W / 2, y0 + gridH + 30);
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

    reset();
    return { reset: reset, apply: apply, draw: draw };
  };
})();

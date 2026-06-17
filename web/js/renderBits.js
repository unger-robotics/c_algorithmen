/* renderBits.js — Renderer für view "bits" (bitweise Operationen).
 * Zeigt mehrere beschriftete Bit-Reihen (0/1-Zellen). Eine hervorgehobene
 * Spalte markiert die gerade verknüpften Bits, gesetzte Ergebnisbits leuchten.
 * Bit-Wert -1 = noch leere Zelle (Ergebnisreihe wird Schritt für Schritt gefüllt).
 */
(function () {
  "use strict";
  window.RENDERERS = window.RENDERERS || {};

  function cssvar(v) {
    return getComputedStyle(document.documentElement).getPropertyValue(v).trim() || "#888";
  }

  window.RENDERERS.bits = function (canvas, trace) {
    var ctx = canvas.getContext("2d");
    var W = canvas.width, H = canvas.height;
    var pal = {
      one:   cssvar("--c-default"),
      zero:  "#26314a",
      col:   cssvar("--c-compare"),
      set:   cssvar("--c-sorted"),
      ink:   cssvar("--ink"),
      muted: cssvar("--muted"),
      line:  "#3a4866"
    };

    var rows, order, active;

    function reset() { rows = {}; order = []; active = {}; }

    function apply(ev) {
      active = {};
      switch (ev.t) {
        case "bitrow":
          if (!(ev.id in rows)) order.push(ev.id);
          rows[ev.id] = { label: ev.label, bits: ev.bits.slice() };
          break;
        case "bitset":
          if (rows[ev.id]) rows[ev.id].bits[ev.col] = ev.val;
          active.cell = [ev.id, ev.col];
          break;
        case "bitcol":
          active.col = ev.col;
          break;
        default: break;
      }
    }

    function width() {
      var w = 0;
      order.forEach(function (id) { w = Math.max(w, rows[id].bits.length); });
      return w;
    }

    function decimal(bits) {
      var v = 0, any = false;
      for (var i = 0; i < bits.length; i++) { v = v * 2 + (bits[i] > 0 ? 1 : 0); if (bits[i] >= 0) any = true; }
      return any ? v : null;
    }

    function draw() {
      ctx.clearRect(0, 0, W, H);
      var n = width(); if (!n || !order.length) return;
      var labelW = 130, cw = Math.min(40, (W - labelW - 120) / n - 6), gap = 6;
      var gridW = n * (cw + gap) - gap;
      var x0 = labelW, rowH = Math.min(58, (H - 90) / order.length);
      var y0 = (H - order.length * rowH) / 2 + 10;

      ctx.textBaseline = "middle";
      // Spaltenindizes oben
      ctx.fillStyle = pal.muted; ctx.font = "11px system-ui, sans-serif"; ctx.textAlign = "center";
      for (var c = 0; c < n; c++) {
        ctx.fillText(String(n - 1 - c), x0 + c * (cw + gap) + cw / 2, y0 - 16);
      }

      order.forEach(function (id, r) {
        var row = rows[id], y = y0 + r * rowH + rowH / 2 - 8;
        // Beschriftung links
        ctx.fillStyle = pal.ink; ctx.font = "14px system-ui, sans-serif"; ctx.textAlign = "left";
        ctx.fillText(row.label, 16, y);
        // Zellen
        for (var c2 = 0; c2 < n; c2++) {
          var b = row.bits[c2];
          var x = x0 + c2 * (cw + gap), ch = Math.min(rowH - 12, cw);
          var cy = y - ch / 2;
          var isCol = active.col === c2;
          var isSet = active.cell && active.cell[0] === id && active.cell[1] === c2;
          ctx.fillStyle = (b === undefined || b < 0) ? "transparent" : (b ? pal.one : pal.zero);
          if (b !== undefined && b >= 0) { roundRect(x, cy, cw, ch, 6); ctx.fill(); }
          // Rahmen (Spalte / gesetzt)
          ctx.lineWidth = (isSet || isCol) ? 3 : 1.5;
          ctx.strokeStyle = isSet ? pal.set : isCol ? pal.col : pal.line;
          roundRect(x, cy, cw, ch, 6); ctx.stroke();
          // Ziffer
          if (b !== undefined && b >= 0) {
            ctx.fillStyle = b ? "#06101f" : pal.muted;
            ctx.font = "bold 16px system-ui, sans-serif"; ctx.textAlign = "center";
            ctx.fillText(String(b), x + cw / 2, y);
          }
        }
        // Dezimalwert rechts
        var dec = decimal(row.bits);
        if (dec !== null) {
          ctx.fillStyle = pal.muted; ctx.font = "14px system-ui, sans-serif"; ctx.textAlign = "left";
          ctx.fillText("= " + dec, x0 + gridW + 16, y);
        }
      });
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

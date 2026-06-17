/* renderLogik.js — Renderer für view "logik" (Wahrheitstabellen).
 * Baut die Wahrheitstabelle Zeile für Zeile auf: Eingänge E1/E2 und die
 * Verknüpfungen UND/ODER/XOR/NEG. 1-Zellen leuchten, die neueste Zeile ist
 * hervorgehoben. Ein trow-Event = eine Tabellenzeile [E1,E2,UND,ODER,XOR,NEG].
 */
(function () {
  "use strict";
  window.RENDERERS = window.RENDERERS || {};
  var HEAD = ["E1", "E2", "UND", "ODER", "XOR", "NEG"];
  var INPUTS = 2;   // erste zwei Spalten sind Eingänge

  function cssvar(v) {
    return getComputedStyle(document.documentElement).getPropertyValue(v).trim() || "#888";
  }

  window.RENDERERS.logik = function (canvas, trace) {
    var ctx = canvas.getContext("2d");
    var W = canvas.width, H = canvas.height;
    var pal = {
      input: cssvar("--c-default"),
      out:   cssvar("--c-sorted"),
      dim:   "#26314a",
      hi:    cssvar("--c-compare"),
      ink:   cssvar("--ink"),
      muted: cssvar("--muted"),
      line:  "#3a4866"
    };

    var rows, active;
    function reset() { rows = []; active = -1; }
    function apply(ev) { if (ev.t === "trow") { rows.push(ev.v.slice()); active = rows.length - 1; } }

    function draw() {
      ctx.clearRect(0, 0, W, H);
      var cols = HEAD.length, colW = 118, rowH = 48;
      var tableW = cols * colW;
      var x0 = (W - tableW) / 2;
      var nRows = 1 + Math.max(rows.length, 1);
      var y0 = (H - nRows * rowH) / 2 - 6;

      ctx.textAlign = "center"; ctx.textBaseline = "middle";

      // Kopfzeile
      for (var c = 0; c < cols; c++) {
        var hx = x0 + c * colW + colW / 2, hy = y0 + rowH / 2;
        ctx.fillStyle = c < INPUTS ? pal.muted : pal.ink;
        ctx.font = "bold 16px system-ui, sans-serif";
        ctx.fillText(HEAD[c], hx, hy);
      }
      // Trennlinie unter Kopf + senkrechte Linie nach den Eingängen
      ctx.strokeStyle = pal.line; ctx.lineWidth = 1.5;
      ctx.beginPath(); ctx.moveTo(x0, y0 + rowH); ctx.lineTo(x0 + tableW, y0 + rowH); ctx.stroke();
      ctx.beginPath();
      ctx.moveTo(x0 + INPUTS * colW, y0); ctx.lineTo(x0 + INPUTS * colW, y0 + (1 + rows.length) * rowH);
      ctx.stroke();

      // Datenzeilen
      for (var r = 0; r < rows.length; r++) {
        var ry = y0 + (r + 1) * rowH;
        if (r === active) {
          ctx.fillStyle = "rgba(242,193,78,0.10)";
          ctx.fillRect(x0, ry, tableW, rowH);
          ctx.strokeStyle = pal.hi; ctx.lineWidth = 2;
          ctx.strokeRect(x0 + 1, ry + 1, tableW - 2, rowH - 2);
        }
        for (var cc = 0; cc < cols; cc++) {
          var v = rows[r][cc];
          var cx = x0 + cc * colW + colW / 2, cy = ry + rowH / 2;
          var on = v === 1;
          var bg = cc < INPUTS ? (on ? pal.input : pal.dim) : (on ? pal.out : pal.dim);
          ctx.fillStyle = bg;
          roundRect(cx - 16, cy - 14, 32, 28, 7); ctx.fill();
          ctx.fillStyle = on ? "#06101f" : pal.muted;
          ctx.font = "bold 15px system-ui, sans-serif";
          ctx.fillText(String(v), cx, cy);
        }
      }

      // Bildunterschrift: aktuelle Zeile als Aussage
      if (active >= 0) {
        var a = rows[active];
        ctx.fillStyle = pal.muted; ctx.font = "14px system-ui, sans-serif";
        ctx.fillText("E1=" + a[0] + ", E2=" + a[1] + "  →  UND=" + a[2] +
                     ", ODER=" + a[3] + ", XOR=" + a[4] + ", NEG(E1)=" + a[5],
                     W / 2, y0 + (1 + rows.length) * rowH + 28);
      }
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

/* renderSchaltung.js — Renderer für view "schaltung" (schaltung.c).
 * Zeichnet das Schaltbild der konkreten Schaltung
 *   Lampe = (s1∨s2) ∧ ((s3∧s4) ∨ ((s5∨s6)∧s7))
 * mit 7 Schaltern (offen/geschlossen), Stromfluss (grün) und Lampe.
 * Pro Trace-Event ("circuit") wird eine der 128 Schalterstellungen gezeigt.
 */
(function () {
  "use strict";
  window.RENDERERS = window.RENDERERS || {};

  function cssvar(v) {
    return getComputedStyle(document.documentElement).getPropertyValue(v).trim() || "#888";
  }

  // Geometrie der 7 Schalter (Index 0..6 = s1..s7), Werte aus dem Trace-Array s[].
  var SW = [
    { x1: 150, x2: 340, y: 185, label: "s1" },
    { x1: 150, x2: 340, y: 295, label: "s2" },
    { x1: 410, x2: 600, y: 150, label: "s3" },
    { x1: 620, x2: 810, y: 150, label: "s4" },
    { x1: 410, x2: 600, y: 270, label: "s5" },
    { x1: 410, x2: 600, y: 330, label: "s6" },
    { x1: 620, x2: 810, y: 300, label: "s7" }
  ];

  window.RENDERERS.schaltung = function (canvas, trace) {
    var ctx = canvas.getContext("2d");
    var W = canvas.width, H = canvas.height;
    var pal = {
      on:   cssvar("--c-sorted"),
      grey: "#55617e",
      lamp: cssvar("--c-compare"),
      ink:  cssvar("--ink"),
      muted:cssvar("--muted")
    };

    var cur = null;   // {z, s:[7], lampe}

    function reset() { cur = null; }
    function apply(ev) { if (ev.t === "circuit") cur = { z: ev.z, s: ev.s, lampe: ev.lampe }; }

    function poly(points, on) {
      ctx.strokeStyle = on ? pal.on : pal.grey;
      ctx.lineWidth = on ? 3.5 : 2;
      ctx.beginPath();
      ctx.moveTo(points[0][0], points[0][1]);
      for (var i = 1; i < points.length; i++) ctx.lineTo(points[i][0], points[i][1]);
      ctx.stroke();
    }

    function dot(x, y, on) {
      ctx.fillStyle = on ? pal.on : pal.grey;
      ctx.beginPath(); ctx.arc(x, y, 4, 0, 2 * Math.PI); ctx.fill();
    }

    function drawSwitch(def, on, live) {
      var g = 16, tx1 = def.x1 + g, tx2 = def.x2 - g, y = def.y;
      poly([[def.x1, y], [tx1, y]], live);          // Stub links
      poly([[tx2, y], [def.x2, y]], live);          // Stub rechts
      dot(tx1, y, live); dot(tx2, y, live);
      ctx.strokeStyle = live ? pal.on : (on ? pal.ink : pal.grey);
      ctx.lineWidth = 3.5;
      ctx.beginPath();
      ctx.moveTo(tx1, y);
      if (on) ctx.lineTo(tx2, y);                    // geschlossen: durchverbunden
      else    ctx.lineTo(tx2 - 6, y - 22);           // offen: Hebel angehoben
      ctx.stroke();
      ctx.fillStyle = pal.muted; ctx.font = "13px system-ui, sans-serif";
      ctx.textAlign = "center"; ctx.textBaseline = "alphabetic";
      ctx.fillText(def.label, (tx1 + tx2) / 2, y - 28);
    }

    function lamp(x, y, on) {
      if (on) {
        var grd = ctx.createRadialGradient(x, y, 4, x, y, 40);
        grd.addColorStop(0, pal.lamp); grd.addColorStop(1, "rgba(242,193,78,0)");
        ctx.fillStyle = grd; ctx.beginPath(); ctx.arc(x, y, 40, 0, 2 * Math.PI); ctx.fill();
      }
      ctx.strokeStyle = on ? pal.lamp : pal.grey; ctx.lineWidth = 2.5;
      ctx.beginPath(); ctx.arc(x, y, 20, 0, 2 * Math.PI); ctx.stroke();
      var d = 20 * Math.SQRT1_2;
      ctx.beginPath();
      ctx.moveTo(x - d, y - d); ctx.lineTo(x + d, y + d);
      ctx.moveTo(x - d, y + d); ctx.lineTo(x + d, y - d);
      ctx.stroke();
      ctx.fillStyle = on ? pal.lamp : pal.muted; ctx.font = "13px system-ui, sans-serif";
      ctx.textAlign = "center"; ctx.fillText("Lampe", x, y + 38);
    }

    function battery(x, y) {
      ctx.strokeStyle = pal.muted; ctx.lineWidth = 2;
      ctx.beginPath();                          // lange Platte (+)
      ctx.moveTo(x - 13, y - 9); ctx.lineTo(x + 13, y - 9);
      ctx.moveTo(x - 7, y + 4);  ctx.lineTo(x + 7, y + 4);   // kurze Platte (–)
      ctx.stroke();
    }

    function draw() {
      ctx.clearRect(0, 0, W, H);
      var s = cur ? cur.s : [0, 0, 0, 0, 0, 0, 0];
      var lampe = cur ? cur.lampe : 0;

      var b1 = s[0] || s[1];
      var topB = s[2] && s[3];
      var botB = (s[4] || s[5]) && s[6];
      var L = !!lampe, top = L && topB, bot = L && botB;

      // Außenschleife (Batterie -> A ; D -> rechts/unten -> Lampe -> Batterie)
      poly([[810, 240], [880, 240], [880, 430], [70, 430], [70, 240], [150, 240]], L);
      battery(70, 335);
      // Trunk-Busse
      poly([[150, 185], [150, 295]], L);        // Block1 links
      poly([[340, 185], [340, 295]], L);        // Block1 rechts
      poly([[340, 240], [400, 240]], L);        // B -> C
      poly([[400, 150], [400, 330]], L);        // Block2 links
      poly([[810, 150], [810, 330]], L);        // Block2 rechts
      // Block2 obere Reihe (s3-s4 in Reihe)
      poly([[600, 150], [620, 150]], top);
      // Block2 untere Reihe ((s5||s6) dann s7)
      poly([[600, 270], [600, 330]], bot);      // Sub-Bus rechts (s5/s6)
      poly([[600, 300], [620, 300]], bot);      // Verbindung zu s7

      var live = [
        L && s[0], L && s[1],
        top, top,
        bot && s[4], bot && s[5], bot
      ];
      for (var i = 0; i < 7; i++) drawSwitch(SW[i], s[i], live[i]);

      lamp(470, 430, L);

      // Kopfzeile: Kombination + Lampenzustand
      ctx.textAlign = "left"; ctx.textBaseline = "alphabetic";
      ctx.fillStyle = pal.ink; ctx.font = "15px system-ui, sans-serif";
      ctx.fillText("Kombination " + (cur ? cur.z : 0) + " / 128", 40, 36);
      ctx.fillStyle = L ? pal.on : pal.muted;
      ctx.fillText("Lampe: " + (L ? "AN" : "aus"), 220, 36);

      // Formel mit aktuellen Wahrheitswerten (oben, kollidiert nicht mit der Lampe)
      ctx.textAlign = "center"; ctx.fillStyle = pal.muted; ctx.font = "14px system-ui, sans-serif";
      ctx.fillText("Lampe = (s1∨s2)=" + (b1 ? 1 : 0) +
                   " ∧ ( (s3∧s4)=" + (topB ? 1 : 0) +
                   " ∨ ((s5∨s6)∧s7)=" + (botB ? 1 : 0) + " )", W / 2, 78);
    }

    reset();
    return { reset: reset, apply: apply, draw: draw };
  };
})();

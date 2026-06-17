/* player.js — generischer Trace-Player.
 * Lädt einen JSON-Trace, wählt anhand von trace.view einen Renderer aus
 * window.RENDERERS und steuert Wiedergabe (Play/Pause/Step/Tempo/Timeline).
 * Renderer-Vertrag:  factory(canvas, trace) -> { reset(), apply(event), draw() }
 */
(function () {
  "use strict";

  var canvas  = document.getElementById("canvas");
  var elStatus= document.getElementById("status");
  var elStep  = document.getElementById("step");
  var elTotal = document.getElementById("total");
  var elTL    = document.getElementById("timeline");
  var elSpeed = document.getElementById("speed");
  var elMeta  = document.getElementById("meta");
  var elSelect= document.getElementById("algo");
  var elFile  = document.getElementById("file");
  var btnPlay = document.getElementById("play");
  var btnFwd  = document.getElementById("fwd");
  var btnBack = document.getElementById("back");
  var btnReset= document.getElementById("reset");

  var trace = null, renderer = null;
  var cursor = 0;          // 0 = Startzustand, k = nach events[0..k-1]
  var playing = false, timer = null;

  /* ---- Wiedergabe-Kern --------------------------------------------------- */

  function setTrace(t) {
    trace = t;
    var factory = (window.RENDERERS || {})[t.view];
    if (!factory) {
      status("Kein Renderer für view=\"" + t.view + "\" vorhanden.");
      renderer = null; return;
    }
    renderer = factory(canvas, t);
    cursor = 0;
    elTotal.textContent = t.events.length;
    elTL.max = t.events.length;
    elMeta.textContent = t.titel + "  ·  " + t.events.length + " Schritte  ·  view: " + t.view;
    seek(0);
    pause();
  }

  // Vollständiger Replay von init bis k (idempotent) — für Slider/Reset.
  function seek(k) {
    if (!renderer) return;
    k = Math.max(0, Math.min(k, trace.events.length));
    renderer.reset();
    for (var i = 0; i < k; i++) renderer.apply(trace.events[i]);
    cursor = k;
    renderer.draw();
    sync(cursor > 0 ? trace.events[cursor - 1] : null);
  }

  // Ein Schritt vor (inkrementell, schnell) — für Play/Step.
  function stepForward() {
    if (!renderer || cursor >= trace.events.length) { pause(); return; }
    var ev = trace.events[cursor];
    renderer.apply(ev);
    cursor++;
    renderer.draw();
    sync(ev);
    if (cursor >= trace.events.length) pause();
  }

  function sync(ev) {
    elStep.textContent = cursor;
    elTL.value = cursor;
    status(describe(ev));
  }

  function play() {
    if (!renderer || cursor >= trace.events.length) return;
    playing = true; btnPlay.classList.add("active"); btnPlay.textContent = "⏸";
    schedule();
  }
  function pause() {
    playing = false; btnPlay.classList.remove("active"); btnPlay.textContent = "▶";
    if (timer) { clearTimeout(timer); timer = null; }
  }
  function schedule() {
    if (!playing) return;
    var sps = parseInt(elSpeed.value, 10) || 20;     // Schritte pro Sekunde
    timer = setTimeout(function () {
      stepForward();
      schedule();
    }, 1000 / sps);
  }

  /* ---- Statuszeile: Event -> deutscher Text ------------------------------ */

  function describe(ev) {
    if (!ev) return "Startzustand.";
    switch (ev.t) {
      case "note":        return ev.text;
      case "done":        return "Fertig.";
      case "compare":     return "Vergleiche Position " + ev.i + " und " + ev.j + ".";
      case "swap":        return "Tausche Position " + ev.i + " und " + ev.j + ".";
      case "set":         return "Setze Position " + ev.i + " = " + ev.val + ".";
      case "highlight":   return "Hervorgehoben: " + (ev.idx || []).join(", ") + ".";
      case "markSorted":  return (trace && trace.view === "lotto")
                                 ? "Zahl " + (ev.i + 1) + " gezogen."
                                 : "Position " + ev.i + " ist endgültig einsortiert.";
      case "pointer":     return "Zeiger „" + ev.name + "“ → Position " + ev.i + ".";
      case "found":       return "Gefunden an Position " + ev.i + ".";
      case "addNode":     return "Neuer Knoten " + ev.id +
                                 (ev.val !== undefined ? " (Wert " + ev.val + ")" : "") + ".";
      case "removeNode":  return "Entferne Knoten " + ev.id + ".";
      case "addEdge":     return "Kante " + ev.from + " → " + ev.to +
                                 (ev.w !== undefined ? " (Gewicht " + ev.w + ")" : "") + ".";
      case "visit":       return "Besuche Knoten " + ev.id + ".";
      case "compareNode": return "Vergleiche mit Knoten " + ev.id + " (Wert " + ev.val + ").";
      case "bucket":      return "Bucket " + ev.idx + ": [" + (ev.ids || []).join(", ") + "].";
      case "frontier":    return "Warteschlange: [" + (ev.ids || []).join(", ") + "].";
      case "relax":       return "Relaxiere Kante " + ev.from + " → " + ev.to + " (Distanz " + ev.dist + ").";
      case "setDist":     return "Distanz von Knoten " + ev.id + " = " + ev.dist + ".";
      case "path":        return "Kürzester Pfad: " + (ev.ids || []).join(" → ") + ".";
      case "circuit":     return "Kombination " + ev.z + " / 128 — Lampe " + (ev.lampe ? "AN" : "aus") + ".";
      case "bitrow":      return "Reihe: " + ev.label + ".";
      case "bitcol":      return "Diese Bit-Spalte verknüpfen.";
      case "bitset":      return "Ergebnisbit = " + ev.val + ".";
      default:            return ev.t;
    }
  }

  function status(msg) { elStatus.textContent = msg || ""; }

  /* ---- Laden -------------------------------------------------------------- */

  function loadManifest() {
    fetch("traces/manifest.json")
      .then(function (r) { if (!r.ok) throw new Error("kein manifest"); return r.json(); })
      .then(function (m) {
        var groups = {};
        (m.algorithmen || []).forEach(function (a) {
          (groups[a.kategorie] = groups[a.kategorie] || []).push(a);
        });
        elSelect.innerHTML = "";
        Object.keys(groups).forEach(function (kat) {
          var og = document.createElement("optgroup");
          og.label = kat;
          groups[kat].forEach(function (a) {
            var o = document.createElement("option");
            o.value = a.datei; o.textContent = a.titel;
            og.appendChild(o);
          });
          elSelect.appendChild(og);
        });
        if (elSelect.options.length) { elSelect.selectedIndex = 0; loadTrace(elSelect.value); }
      })
      .catch(function () {
        status("Kein Manifest gefunden. Lade einen Trace über „Trace laden…“ " +
               "oder starte den Server mit  make web.");
      });
  }

  function loadTrace(datei) {
    fetch("traces/" + datei)
      .then(function (r) { return r.json(); })
      .then(setTrace)
      .catch(function () { status("Konnte traces/" + datei + " nicht laden."); });
  }

  /* ---- Bedienelemente ----------------------------------------------------- */

  btnPlay.addEventListener("click", function () { playing ? pause() : play(); });
  btnFwd .addEventListener("click", function () { pause(); stepForward(); });
  btnBack.addEventListener("click", function () { pause(); seek(cursor - 1); });
  btnReset.addEventListener("click", function () { pause(); seek(0); });
  elTL.addEventListener("input", function () { pause(); seek(parseInt(elTL.value, 10)); });
  elSelect.addEventListener("change", function () { loadTrace(elSelect.value); });
  elFile.addEventListener("change", function (e) {
    var f = e.target.files[0]; if (!f) return;
    var rd = new FileReader();
    rd.onload = function () {
      try { setTrace(JSON.parse(rd.result)); }
      catch (err) { status("Ungültiges JSON: " + err.message); }
    };
    rd.readAsText(f);
  });

  document.addEventListener("keydown", function (e) {
    if (e.key === " ")      { e.preventDefault(); playing ? pause() : play(); }
    else if (e.key === "ArrowRight") { pause(); stepForward(); }
    else if (e.key === "ArrowLeft")  { pause(); seek(cursor - 1); }
  });

  loadManifest();
})();

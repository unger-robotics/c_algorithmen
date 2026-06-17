#!/usr/bin/env python3
# ju -- 2026 -- check-traces.py
# Prueft die eingecheckten Traces ueber die reine JSON-Wohlgeformtheit hinaus:
#   1. Schema     - Pflichtfelder, Typen, erlaubte view, Event-Struktur
#   2. Manifest   - jede manifest-Zeile zeigt auf eine vorhandene Trace-Datei
#                   und jede Trace-Datei ist im Manifest verzeichnet
#   3. gen-traces - jeder tracende Algorithmus unter src/ hat einen Trace
# Aufruf:  python3 tools/check-traces.py      (Exit 0 = ok, 1 = Fehler)
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
TRACES = ROOT / "web" / "traces"
SRC = ROOT / "src"

# erlaubte views = die im Frontend registrierten Renderer
VIEWS = {"array", "tree", "graph", "bits", "logik", "lotto", "schaltung"}

errors = []


def err(msg):
    errors.append(msg)


def check_trace(path):
    try:
        data = json.loads(path.read_text(encoding="utf-8"))
    except (json.JSONDecodeError, UnicodeDecodeError) as e:
        err(f"{path.name}: kein gueltiges JSON ({e})")
        return
    for field, typ in (("algo", str), ("titel", str), ("view", str),
                       ("init", dict), ("events", list)):
        if field not in data:
            err(f"{path.name}: Pflichtfeld '{field}' fehlt")
        elif not isinstance(data[field], typ):
            err(f"{path.name}: Feld '{field}' hat falschen Typ "
                f"(erwartet {typ.__name__})")
    if isinstance(data.get("view"), str) and data["view"] not in VIEWS:
        err(f"{path.name}: unbekannte view '{data['view']}' "
            f"(erlaubt: {', '.join(sorted(VIEWS))})")
    events = data.get("events")
    if isinstance(events, list):
        if not events:
            err(f"{path.name}: 'events' ist leer")
        for i, ev in enumerate(events):
            if not isinstance(ev, dict) or not isinstance(ev.get("t"), str):
                err(f"{path.name}: event[{i}] hat kein String-Feld 't'")
        if not any(isinstance(ev, dict) and ev.get("t") == "done"
                   for ev in events):
            err(f"{path.name}: kein abschliessendes 'done'-Event")


def main():
    if not TRACES.is_dir():
        err("web/traces/ fehlt — erst 'make traces' ausfuehren")
        print("\n".join(errors)); return 1

    trace_files = sorted(p for p in TRACES.glob("*.json")
                         if p.name != "manifest.json")

    # 1. Schema je Trace
    for p in trace_files:
        check_trace(p)

    # 2. Manifest-Konsistenz
    manifest = TRACES / "manifest.json"
    referenced = set()
    if not manifest.exists():
        err("manifest.json fehlt")
    else:
        try:
            m = json.loads(manifest.read_text(encoding="utf-8"))
            for a in m.get("algorithmen", []):
                datei = a.get("datei")
                referenced.add(datei)
                if not (TRACES / datei).exists():
                    err(f"manifest: verweist auf fehlende Datei '{datei}'")
                for key in ("kategorie", "titel", "datei"):
                    if not a.get(key):
                        err(f"manifest: Eintrag ohne '{key}': {a}")
        except json.JSONDecodeError as e:
            err(f"manifest.json: kein gueltiges JSON ({e})")
    for p in trace_files:
        if p.name not in referenced:
            err(f"{p.name}: existiert, ist aber nicht im Manifest")

    # 3. gen-traces-Vollstaendigkeit: jede tracende Quelle hat einen Trace
    have = {p.stem for p in trace_files}
    for src in sorted(SRC.rglob("*.c")):
        text = src.read_text(encoding="utf-8", errors="replace")
        if "trace_begin(" in text and src.stem not in have:
            err(f"{src.relative_to(ROOT)}: tract (trace_begin), aber kein "
                f"{src.stem}.json — run-Zeile in tools/gen-traces.sh fehlt?")

    if errors:
        print(f"check-traces: {len(errors)} Problem(e):")
        for e in errors:
            print("  -", e)
        return 1
    print(f"check-traces: {len(trace_files)} Traces ok, "
          f"Manifest und gen-traces vollstaendig.")
    return 0


if __name__ == "__main__":
    sys.exit(main())

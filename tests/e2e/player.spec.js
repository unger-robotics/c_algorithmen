// ju -- 2026 -- player.spec.js
// Smoke-Test des Web-Players: jeden Algorithmus aus dem Manifest laden, bis ans
// Ende abspielen (alle Events durch den Renderer schicken) und sicherstellen,
// dass kein Renderer fehlt und keine JS-Konsolen-/Laufzeitfehler auftreten.
import { test, expect } from "@playwright/test";

test("Player spielt jeden Algorithmus fehlerfrei bis zum Ende ab", async ({ page }) => {
  const errors = [];
  page.on("console", (m) => { if (m.type() === "error") errors.push(m.text()); });
  page.on("pageerror", (e) => errors.push(String(e)));

  await page.goto("/web/");

  const select = page.locator("#algo");
  // Manifest geladen -> Dropdown gefüllt
  await expect.poll(async () => await select.locator("option").count())
    .toBeGreaterThan(0);

  const values = await select.locator("option")
    .evaluateAll((opts) => opts.map((o) => o.value));

  for (const v of values) {
    // Auswahl setzen und sicher den Trace-Fetch abwarten
    const [resp] = await Promise.all([
      page.waitForResponse((r) => r.url().includes("traces/" + v) && r.request().method() === "GET"),
      (async () => { await select.selectOption(v); await page.dispatchEvent("#algo", "change"); })(),
    ]);
    expect(resp.ok(), `Trace ${v} lädt nicht (HTTP ${resp.status()})`).toBeTruthy();

    // Renderer muss existieren (Status meldet sonst "Kein Renderer für view=…")
    await expect(page.locator("#status")).not.toContainText("Kein Renderer");

    // bis ans Ende springen: Timeline auf Maximum -> Renderer wendet alle Events an
    const total = Number(await page.locator("#total").textContent());
    expect(total, `Trace ${v} hat keine Events`).toBeGreaterThan(0);
    await page.locator("#timeline").evaluate((el, t) => {
      el.value = String(t);
      el.dispatchEvent(new Event("input"));
    }, total);
    await expect(page.locator("#step")).toHaveText(String(total));
  }

  expect(errors, "JS-Fehler im Player:\n" + errors.join("\n")).toEqual([]);
});

// ju -- 2026 -- playwright.config.js
// Startet den statischen Python-Webserver und testet den Player im Browser.
import { defineConfig, devices } from "@playwright/test";

export default defineConfig({
  testDir: "tests/e2e",
  timeout: 60000,
  reporter: "list",
  use: {
    baseURL: "http://127.0.0.1:8000",
    headless: true,
  },
  projects: [{ name: "chromium", use: { ...devices["Desktop Chrome"] } }],
  webServer: {
    command: "python3 -m http.server 8000",
    url: "http://127.0.0.1:8000/web/",
    reuseExistingServer: !process.env.CI,
    timeout: 30000,
  },
});

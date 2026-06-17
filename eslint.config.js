// ju -- 2026 -- eslint.config.js  (ESLint v9 Flat-Config)
// Lintet die Browser-Skripte des Players (web/js) und die E2E-Tests.
import js from "@eslint/js";
import globals from "globals";

export default [
  js.configs.recommended,
  {
    // Browser-Player: klassische Skripte (IIFE, var), Renderer registrieren
    // sich global in window.RENDERERS.
    files: ["web/js/**/*.js"],
    languageOptions: {
      ecmaVersion: 2021,
      sourceType: "script",
      globals: {
        ...globals.browser,
        RENDERERS: "writable",
      },
    },
    rules: {
      "no-unused-vars": ["warn", { args: "none" }],
    },
  },
  {
    // Node-seitige Test-/Konfigurationsdateien (ESM).
    files: ["tests/e2e/**/*.js", "playwright.config.js"],
    languageOptions: {
      ecmaVersion: 2022,
      sourceType: "module",
      globals: { ...globals.node },
    },
  },
];

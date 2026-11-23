# Source

- **Upstream:** Matt Pocock, `skills/engineering/diagnosing-bugs/SKILL.md` in https://github.com/mattpocock/skills
- **Commit:** `49dd158d1076134a641b33efb035946536778336` (plugin `mattpocock-skills` 1.3.1, as pinned by `claude-plugins-official`)
- **License:** MIT, see `LICENSE` in this folder.

## Changes for Palo Alto

- Removed feedback-loop options 2 (curl/HTTP) and 4 (Playwright/Puppeteer) and renumbered.
- "Replay a captured trace": user-provided artifact only, never fetched.
- HITL bash template (`scripts/hitl-loop.template.sh`) → numbered steps with pasted output. The script itself is not copied.
- Perf baseline: `performance.now()` → `std::chrono::steady_clock`.
- Added "Palo Alto rules" plus a width-bug gotcha.

## Updating

The plugin updates itself. When it does, diff the new upstream file against the commit above and port only the changes that keep these rules.

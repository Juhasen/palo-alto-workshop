# Source

- **Upstream:** Matt Pocock, `skills/engineering/implement/SKILL.md` in https://github.com/mattpocock/skills
- **Commit:** `49dd158d1076134a641b33efb035946536778336` (plugin `mattpocock-skills` 1.3.1, as pinned by `claude-plugins-official`)
- **License:** MIT, see `LICENSE` in this folder.

## Changes for Palo Alto

- Ticket fetch: "from the issue tracker" → `.scratch/` or the Jira connector.
- Calls `mattpocock-skills:tdd` (unchanged upstream skill, no external calls) and `pa-code-review` (adapted), so the chain never falls back to the unadapted `code-review`.
- "Typechecking" → compile; full suite → `build.bat`, with compiler and architecture reported.
- Commit only: no push, no PR.
- Added "Palo Alto rules" section.
- Removed `disable-model-invocation: true` so the `ticket-to-pr` pipeline can call this skill through the Skill tool. Claude can now also pick it on its own; the narrow description keeps that rare.

## Updating

The plugin updates itself. When it does, diff the new upstream file against the commit above and port only the changes that keep these rules.

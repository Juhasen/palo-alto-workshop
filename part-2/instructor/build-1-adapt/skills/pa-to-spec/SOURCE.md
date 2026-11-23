# Source

- **Upstream:** Matt Pocock, `skills/engineering/to-spec/SKILL.md` in https://github.com/mattpocock/skills
- **Commit:** `49dd158d1076134a641b33efb035946536778336` (plugin `mattpocock-skills` 1.3.1, as pinned by `claude-plugins-official`)
- **License:** MIT, see `LICENSE` in this folder.

## Changes for Palo Alto

- Description: "publish to the project issue tracker" → saved under `.scratch/`.
- Tracker setup line: no `/setup-matt-pocock-skills`; read `docs/agents/issue-tracker.md` and stop if it is missing.
- Step 3: "publish to the issue tracker + `ready-for-agent` label" → save `.scratch/<ticket-id>/spec.md` and stop for approval.
- Added "Palo Alto rules" section.
- Removed `disable-model-invocation: true` so the `ticket-to-pr` pipeline can call this skill through the Skill tool. Claude can now also pick it on its own; the narrow description keeps that rare.

## Updating

The plugin updates itself. When it does, diff the new upstream file against the commit above and port only the changes that keep these rules.

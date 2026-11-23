# Source

- **Upstream:** Matt Pocock, `skills/engineering/pr/SKILL.md` and `CREDITS.md` in https://github.com/mattpocock/skills
- **Commit:** `49dd158d1076134a641b33efb035946536778336` (plugin `mattpocock-skills` 1.3.1, as pinned by `claude-plugins-official`)
- **License:** MIT, see `LICENSE` in this folder. The Summary section credits Dex Horthy's `show-me` skill (HumanLayer); `CREDITS.md` is kept unchanged.

## Changes for Palo Alto

Upstream `pr` makes no external calls, so this is a customization, not a safety fix.

- Renamed to `pa-pr`; description says where the body is saved and that no PR is opened.
- Added "Palo Alto rules": save to `.scratch/<ticket-id>/pr.md`, never push or open a PR, endpoint policy, compiler and architecture on every claim, title format.
- Evidence: dropped screenshots (no UI in this code); console output is required; added the evidence table that `ticket-to-pr` used to append itself.
- Merge Danger: added on-disk and wire formats, public headers, and ABI as one-way doors, and Windows/Linux and x86/x64 differences to blast radius.
- Did not copy `agents/openai.yaml`.

## Updating

The plugin updates itself. When it does, diff the new upstream file against the commit above and port only the changes that keep these rules.

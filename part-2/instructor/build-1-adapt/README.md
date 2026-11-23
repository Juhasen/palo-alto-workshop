# Build 1 — Instructor answer key

Participants write `adapt-skill` from the skeleton and let Claude Code adapt the five skills. The reference is [adapt-skill/SKILL.md](adapt-skill/SKILL.md): use it for the 3-minute demo on `diagnosing-bugs`, and hand it out at 0:27 to anyone whose own version is not running yet. The findings below are what a good run should report; use them to check participants' findings tables.

Adapted copies of four Matt Pocock skills (commit `49dd158`, plugin 1.3.1) are in `skills/pa-*`, with `SOURCE.md` listing every change and the MIT `LICENSE`. As the fallback for Build 2, copy `skills\pa-*` into the participant's `.claude\skills\` and `docs\` into the repository root.

## Used as-is, not adapted

`tdd`, `codebase-design`, `grilling`, and `domain-modeling` have no findings at `49dd158`. `pa-implement` calls `mattpocock-skills:tdd`; `ticket-to-pr` calls `mattpocock-skills:grilling` and `domain-modeling`. A good `adapt-skill` run reports them clean and creates no copy.

## What a dry run got wrong (Krystian, 23 Nov)

Fixed in the reference `adapt-skill`; watch for the same in participants' versions:

- **Called skills replaced by prose.** With no `pa-tdd`, it proposed writing out tdd's steps inside `pa-implement`, then proposed adapting `tdd` and `codebase-design` too. Right answer: audit the called skill; if clean, call it by plugin name.
- **"Publish" routed to creating a Jira issue.** The connector is for reading tickets only; publishing means saving `.scratch/<ticket-id>/spec.md`.
- **No tracker config.** `docs/agents/issue-tracker.md` was never written, so the `/setup-matt-pocock-skills` line was deleted instead of pointed at it. Now an explicit step 1.
- **Spec path drift.** It saved `.scratch/spec-<slug>.md`; `ticket-to-pr` expects `.scratch/<ticket-id>/spec.md`.
- **Noise findings.** `agents/openai.yaml`, "HTTP" in design advice, and `fetch()` in TypeScript examples are not findings.

## Findings (what participants should find)

| Skill | Upstream line | Fix |
|---|---|---|
| to-spec | Description and step 3: "publish it to the project issue tracker", "Apply the `ready-for-agent` triage label" | Replace: save `.scratch/<ticket-id>/spec.md`, no labels, stop for approval |
| to-spec | "tell the user to run `/setup-matt-pocock-skills`" | Replace: read `docs/agents/issue-tracker.md`. The setup skill itself runs `gh`/`glab` and creates labels; do not run it |
| implement | "fetch it from the issue tracker" | Route/replace: Jira connector or `.scratch/` |
| implement | "Run typechecking regularly" | Replace: compile, then `build.bat` with compiler and architecture |
| implement | "Commit your work to the current branch." | Keep, and add: never push, never open a PR |
| code-review | "fetched via the workflow in the tracker doc" (GitHub `#123`, GitLab `!67`) | Replace: Jira-style ids resolved to `.scratch/` |
| diagnosing-bugs | Loop option 2 "Curl / HTTP script" | Delete |
| diagnosing-bugs | Loop option 4 "Headless browser script (Playwright / Puppeteer)" | Delete |
| diagnosing-bugs | Loop option 5 "Save a real network request ... replay it" | Replace: user-provided artifact only |
| diagnosing-bugs | Option 10 and checklist: `scripts/hitl-loop.template.sh` (bash) | Replace: numbered steps, output pasted back. Do not copy the script |

Skill calls: `implement` → `tdd` (keep, as `mattpocock-skills:tdd`) and `code-review` (point at `pa-code-review`). `code-review` itself spawns subagents but calls no skill.

## Points to raise

- `to-spec`, `implement`, and `grill-me` are `disable-model-invocation: true`. That keeps Claude from starting them on its own, but it also stops another skill from calling them. The adapted `pa-to-spec` and `pa-implement` drop the flag so `ticket-to-pr` can chain them; for grilling, call the model-invocable `mattpocock-skills:grilling`.

- The subtle hits are phrases, not commands: "publish to the issue tracker" makes the agent pick a CLI on its own.
- `tdd` needs no changes. `pr` makes no external calls either, but `pa-pr` adds the evidence rules (see its `SOURCE.md`); it is a customization, so its findings are all **add** rows. Not every skill needs adapting; audit first.
- The plugin auto-updates. `SOURCE.md` is what lets the team diff the next version instead of trusting it.
- Ask whether the other Palo Alto team's adapted set matches; theirs may already route through the policy broker.

# Workshop Part 2: Skills That Work Together (3 Hours)

**Goal:** after a 15-minute introduction, participants spend the rest of the session building their own `ticket-to-pr` workflow on top of Matt Pocock's skills, adapted to Palo Alto's rules, and run it on a real Jira ticket.

**Pre-workshop preparation (each participant, 10 minutes):**
- Claude Code installed and signed in. Participants use Claude Code only.
- Matt Pocock's skills: `claude plugin install mattpocock-skills@claude-plugins-official`, then `/plugin` shows it enabled.
- Caveman and Ponytail from Part 1 still installed (optional today).
- The Jira connector enabled in Claude. A pasted ticket is the fallback.
- A C++ compiler on `PATH`: MSVC (Developer Command Prompt), `clang++`, or `g++`. Windows matters: Build 3's bug only reproduces there.
- This folder cloned. Check that `build.bat` passes in `build-2-pipeline` (9 checks) and `build-3-extend` (7 checks).
- One small, real Jira ticket per participant for Build 4: a narrow change with a reproducible check.

| Time | Session | Material | Outcome |
|---|---|---|---|
| 0:00–0:15 | Intro (presented by the instructor): what a skill is, two ways it starts, what skills make possible, Matt Pocock's skills, Palo Alto rules, adapting a skill (find, fix, save), what we build. | Slides | Shared vocabulary and the target pipeline. |
| 0:15–0:45 | Build 1: write an `adapt-skill` skill, run it on four skills, and review what it changed. | [build-1-adapt](build-1-adapt/README.md) | `adapt-skill`, `pa-to-spec`, `pa-implement`, `pa-code-review`, `pa-diagnosing-bugs`, and `docs/agents/issue-tracker.md`. |
| 0:45–1:20 | Build 2: write `ticket-to-pr` and run it stage by stage on NET-1502. | [build-2-pipeline](build-2-pipeline/README.md) | A pipeline skill that reaches a PR description or stops with a reason. |
| 1:20–1:30 | Break. | | |
| 1:30–2:00 | Build 3: add a bug-analysis branch (AUD-877), or build a `document-module` skill: cited "how it works today" doc, glossary and ADRs, fresh-context fact-check. | [build-3-extend](build-3-extend/README.md) | One new branch in the pipeline, or a documentation skill the pipeline calls. |
| 2:00–2:45 | Build 4: run the pipeline on your own Jira ticket in your own repository; pairs review each other's spec, diff, and evidence. | [build-4-real-ticket](build-4-real-ticket/README.md) | A real PR description with evidence, plus a list of skill fixes. |
| 2:45–3:00 | Share-out and `/retro`: which adapted skills to keep, and how to publish them through the internal marketplace. | | Next steps and an owner. |

**Rules for the day:** no installs beyond the plugin, no network calls from the agent (Jira only through the connector), plain Markdown skills only. Name the compiler and architecture behind every "it works".

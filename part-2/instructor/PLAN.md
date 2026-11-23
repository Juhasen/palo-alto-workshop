# Part 2 plan (draft): adapting and composing skills into a ticket-to-PR pipeline

**Audience:** the Palo Alto C++ team from Part 1 (C++17, MSVC 19.16, legacy code, some Go).
**Length:** 3 hours.
**Status:** draft material built. Participants clone `../participant/`; the instructor guide is [README.md](README.md).

## Goal

Part 1 showed single skills (Caveman, Ponytail, three hand-written `quick-*` skills). Part 2 opens with a 15-minute presentation on what skills make possible and how to adapt public skills to Palo Alto's rules, then participants spend the rest of the day building their own `ticket-to-pr` workflow on top of Matt Pocock's skills: **ticket (Jira connector, paste as fallback) → spec → implement → validate → PR description.**

The team also asked for public, legally reusable skills for **documentation** and **bug analysis**. They appear as the Build 3 extensions (bug-ticket branch, documentation step), using the sources vetted in [SKILL-SOURCES.md](SKILL-SOURCES.md).

## What participants leave with

1. The Matt Pocock skills they use, installed and **adapted to Palo Alto rules** as project skills: no external calls, outside services only through the internal policy broker, with the upstream license kept.
2. A bug-analysis or documentation branch in their pipeline, tried on sample code.
3. Their own `ticket-to-pr/SKILL.md`, already run once on a real Jira ticket, that orchestrates the other skills, with Gotchas tuned for C++ on Windows.
4. A short answer to "how would we ship this through our internal marketplace?"

## Constraints that shape the design

From [AGENTS.md](AGENTS.md): no installs beyond Caveman and Ponytail, no network from the agent, Markdown-only skills, nothing invasive. Confirmed with Krystian:

- **Participants install Matt's skills as a plugin:** `claude plugin install mattpocock-skills@claude-plugins-official` (Krystian, 2026-11-22). Other sources are copied from GitHub in the browser into `.claude/skills/`. Each demo also ships a pre-copied fallback in case the install is blocked on the day.
- **Another Palo Alto team already runs Pocock's skills**, adapted so they make no external calls; outside services are reached only through the internal **policy broker**. Part 2 teaches that adaptation as an explicit step, so the team owns the result instead of trusting upstream. A plugin's own files are not the place to edit (it updates itself and overwrites changes), so an adapted skill lives as a **project skill** in `.claude/skills/` with its own name, and the original stays unused. The plugin's auto-update is also a discussion point: upstream changes arrive without review.
- **Setup check:** participants use only Claude Code. Confirm with `/plugin` that `mattpocock-skills` is enabled.
- **Visible vs typed skills:** after install, Claude lists only the 11 model-invoked skills (diagnosing-bugs, tdd, code-review, pr, grilling, and so on). The pipeline skills (`to-spec`, `to-tickets`, `implement`, `grill-me`, `setup-matt-pocock-skills`) are user-invoked (`disable-model-invocation: true`), so they appear only when typed, for example `/mattpocock-skills:to-spec`. Say this up front so nobody thinks the install is broken.
- Matt's skills expect an issue tracker. The adapted `docs/agents/issue-tracker.md` says: **"Jira via the Claude connector or the policy broker; otherwise the pasted ticket in `.scratch/<ticket-id>/ticket.md`"**. Specs and tickets live as local Markdown under `.scratch/`, never via `gh` or `glab`.

## Agenda

Shape: **one 15-minute presentation, then hands on keyboards for the rest of the day.** Participants build their own workflow in four build blocks, using what the intro showed. The instructor demonstrates each block's first step for 2 to 3 minutes, then circulates.

| Time | Block | Material | Outcome |
|---|---|---|---|
| 0:00–0:15 | **Intro presentation.** What a skill is and what skills make possible (calling other skills, subagents in fresh context, shared config, connectors, approval gates, team gotchas). Matt Pocock's skills as a map. Palo Alto's rules and **how to adapt a public skill** so it makes no external calls. What we will build: the `ticket-to-pr` pipeline. | [`intro-presentation.html`](intro-presentation.html) (16 slides) | Shared vocabulary and the target picture |
| 0:15–0:45 | **Build 1: adapt the skills you will use.** Install Matt's plugin, open `to-spec`, `implement`, `code-review` and `diagnosing-bugs`, and find every external call or script (`gh`/`glab`, "publish to the issue tracker", curl and Playwright loops, `.sh` helpers). Fix each one by routing it through the Jira connector or policy broker, replacing it with a local file or a paste, or deleting it. Save the adapted copies as project skills (`.claude/skills/pa-<name>/`) with a `SOURCE.md` (upstream commit, MIT license). Write `docs/agents/issue-tracker.md` for Jira plus paste. | Slides 8–11 stay on screen; audit worksheet; instructor's adapted copies as fallback | An adapted skill set each participant understands line by line |
| 0:45–1:20 | **Build 2: the `ticket-to-pr` skeleton on a sample ticket.** Write `.claude/skills/ticket-to-pr/SKILL.md` with five stages: get ticket → spec (stop for approval) → implement in a fresh subagent → validate (`build.bat`, compiler and architecture named, blind `code-review`) → PR body (`pr`). Run it stage by stage on the sample ticket and fix the skill whenever it goes wrong; every fix becomes a Gotcha line. | Sample C++17 module and ticket, skeleton `SKILL.md` with headings only, `build.bat` | A pipeline that runs end to end on known code |
| 1:20–1:30 | Break | | |
| 1:30–2:00 | **Build 3: extend the pipeline (pick one).** (a) **Bug tickets:** if the ticket is a bug, route to `diagnosing-bugs` first (red feedback loop, ranked hypotheses, regression test) and put the analysis in the PR. (b) **Documentation skill:** build `document-module`: a cited "how it works today" doc (HumanLayer `rpi` research pattern), glossary and ADRs via `domain-modeling`, and a fresh-context fact-check that removes unsupported claims; `ticket-to-pr` calls it on changed files. | Seeded bug ticket for (a), undocumented module for (b), fallback outputs | A second branch in their own pipeline |
| 2:00–2:45 | **Build 4: run it on a real ticket.** Each participant pulls a small real ticket from their own Jira through the connector (paste as fallback) and runs their pipeline in their own repository. Pairs swap: each reviews the other's spec, diff, and evidence table. | Their own repository and Jira | A real draft PR description with evidence, and a list of skill fixes |
| 2:45–3:00 | **Share-out and retro.** Two or three participants show their pipeline. Run `/retro` on the session for environment improvements. Decide which adapted skills to keep and how to publish them through the internal marketplace. | | Next steps and an owner |

Timing note: if Build 2 overruns, shorten Build 3 to a show-only of option (a). Build 4 is the part participants value most; protect it.

## How the pipeline uses their marketplace tools and the broker

Most of the team's work runs through tools in their internal marketplace. The pipeline skill should not replace those. Each stage names **what** must happen and **which tool to prefer**, with a fallback:

| Stage | Prefer | Fallback |
|---|---|---|
| Get ticket | Jira connector, or the policy broker | Pasted text saved to `.scratch/<id>/ticket.md` |
| Spec | `to-spec` (adapted) | |
| Review | Their marketplace code-review plugin, if they use one | `code-review` (adapted) |
| PR | Their GitHub/marketplace tooling, through the broker | `pr` skill writes the body; a human opens the PR |

The lesson: a skill is an orchestration layer over tools the team already has, and swapping a tool means editing one line.

## Material

- `participant/`: what participants clone. README (start here), agenda, skill sources, and one folder per build: `build-1-adapt` (instructions, worksheet), `build-2-pipeline` (NET-1502 ticket, C++17 `timeout_parser` module with 9 passing checks, `build.bat`, skeleton skill), `build-3-extend` (AUD-877 bug ticket, legacy `rf_*` module whose overflow appears only on Windows), `build-4-real-ticket` (instructions).
- `instructor/`: the deck, the run-of-show guide, and per-build answer keys: adapted `pa-to-spec`, `pa-implement`, `pa-code-review`, `pa-diagnosing-bugs` (plugin 1.3.1, commit `49dd158`, each with `SOURCE.md` and MIT `LICENSE`), the reference `ticket-to-pr` skill and solution (35 checks), and Build 3's root cause, fix, and fallbacks.

## Resolved

- **Installing Matt's skills:** `claude plugin install mattpocock-skills@claude-plugins-official`; other sources are copied from GitHub in the browser (Krystian, 2026-11-22).
- **Precedent:** another Palo Alto team uses Pocock's skills, adapted to make no external calls and to reach services only through the internal policy broker.
- **Real ticket:** Build 4 uses a real ticket from each participant's own Jira; Build 2 uses a sample ticket.
- **Jira connector:** all participants should have it, so the instructor demo uses it live; paste is the fallback.

## Still open

1. **Policy broker:** how does Claude reach it: an MCP server, a connector, a CLI, or a URL the participant opens? The adapted skills need the exact name to route through. If the other team can share their adapted versions or their adaptation rules, Build 1 can compare against them.
2. **Trail of Bits** (CC BY-SA 4.0) and Anthropic's `doc-coauthoring` (no license file) still need a legal yes before they appear in material.

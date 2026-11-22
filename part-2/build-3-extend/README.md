# Build 3 — Extend the pipeline (25 min, pick one)

**Goal:** give your `ticket-to-pr` skill a second branch. Pick **A** (bug analysis) or **B** (documentation). Both use the legacy `rf_*` module in this folder, which is undocumented, uses 1998 names, and has a platform bug.

Copy your `.claude/` and `docs/` from Build 2 into this folder first.

```powershell
cd build-3-extend          # from the Part 2 folder
build.bat          # 7 checks pass, also on Windows: the existing tests miss the bug
claude
```

## A. Bug tickets go through diagnosis first

The bug is [BUG-TICKET.md](BUG-TICKET.md) (AUD-877): late records in files above 2 GB are wrong on Windows, right on Linux.

1. **Extend the skill (8 min).** In stage 1 of `ticket-to-pr`, if the ticket is a bug, call the Skill tool with `pa-diagnosing-bugs` before the spec. It must save `.scratch/<ticket-id>/analysis.md` with: the one command that goes red, the ranked hypotheses, the one that held, and the regression test. The spec then describes the fix, and the PR body quotes the hypothesis that held.
2. **Run it (12 min).** `/ticket-to-pr BUG-TICKET.md`. Watch phase 1 of the diagnosis: no hypotheses before there is a red test. On Windows the red test is cheap; on Linux it stays green, and that is the finding.
3. **Check (5 min).** Did the loop go red on *your* compiler? Does the analysis name the platforms it ran on and the ones it did not?

Optional comparison: copy Superpowers' `systematic-debugging` skill from GitHub (MIT; drop `find-polluter.sh` and the `.ts` example) and run it on the same ticket.

## B. Documentation as part of the change

The module has no glossary, and its names (`rf_off`, `rsz`, `fsz`) mean nothing to a new reader.

1. **Extend the skill (8 min).** Add a step after validation: call the Skill tool with `mattpocock-skills:domain-modeling` to update `GLOSSARY.md` with the terms the change touched, and to write an ADR under `docs/adr/` when the change makes a decision someone would later ask about. (`grill-with-docs` is user-invoked only, so the pipeline calls `domain-modeling` directly.)
2. **Run it (12 min).** Use the bug ticket, or just run `/mattpocock-skills:grill-with-docs` on the module and answer its questions.
3. **Check (5 min).** Read every glossary line against the code. Delete any claim the code does not support.

Optional comparison: HumanLayer's `rpi` skill (MIT, copy from GitHub, drop its `web-search-researcher` subagent) writes a cited "how this works today" research document.

## Done when

- Your `ticket-to-pr` skill has one new branch and at least one new Gotcha.
- A: `.scratch/AUD-877/analysis.md` exists with a red-then-green test. B: `GLOSSARY.md` (and an ADR if a decision was made) exists, reviewed against the code.

If a live step fails, the instructor has fallback outputs: an analysis, a glossary, and an ADR.

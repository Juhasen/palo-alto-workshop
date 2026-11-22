# Build 3 — Extend the pipeline (30 min, pick one)

**Goal:** give your `ticket-to-pr` skill a second branch. Pick **A** (bug analysis) or **B** (a documentation skill). Both use the legacy `rf_*` module in this folder, which is undocumented, uses 1998 names, and has a platform bug.

**On Google Meet:** these steps are also pasted in the chat. When the instructor calls for status (every 10 minutes), reply in chat with ✅ done, 🟡 working, or 🔴 stuck. If you are 🔴, the instructor asks you to share your screen or join a breakout room.

Copy your `.claude/` and `docs/` from Build 2 into this folder first.

```powershell
cd build-3-extend          # from the Part 2 folder
build.bat          # 7 checks pass, also on Windows: the existing tests miss the bug
claude
```

## A. Bug tickets go through diagnosis first

The bug is [BUG-TICKET.md](BUG-TICKET.md) (AUD-877): late records in files above 2 GB are wrong on Windows, right on Linux.

1. **Extend the skill (10 min).** In stage 1 of `ticket-to-pr`, if the ticket is a bug, call the Skill tool with `pa-diagnosing-bugs` before the spec. It must save `.scratch/<ticket-id>/analysis.md` with: the one command that goes red, the ranked hypotheses, the one that held, and the regression test. The spec then describes the fix, and the PR body quotes the hypothesis that held.
2. **Run it (15 min).** `/ticket-to-pr BUG-TICKET.md`. Watch phase 1 of the diagnosis: no hypotheses before there is a red test. On Windows the red test is cheap; on Linux it stays green, and that is the finding.
3. **Check (5 min).** Did the loop go red on *your* compiler? Does the analysis name the platforms it ran on and the ones it did not?

Optional comparison: copy Superpowers' `systematic-debugging` skill from GitHub (MIT; drop `find-polluter.sh` and the `.ts` example) and run it on the same ticket.

## B. Build a documentation skill

The module has no documentation, and its names (`rf_off`, `rsz`, `fsz`) mean nothing to a new reader. You build a `document-module` skill that writes docs from the code and then checks them against the code, so they cannot quietly drift into fiction.

```text
research (cited "how it works today") → terms and decisions (glossary, ADRs) → fact-check in a fresh context
```

1. **Write the skill (10 min).** Copy the skeleton into place and fill it in:

   ```powershell
   Copy-Item -Recurse skeleton\document-module .claude\skills\
   ```

   - **Research:** read the module read-only and write `docs/modules/<module>.md`. Every section header states a fact ("Record offsets are header plus index times record size"), every claim cites `file:line`, and a tests section says what is and is not covered. No suggestions or critique: it describes what exists. (This pattern comes from HumanLayer's `rpi` research step, MIT.)
   - **Terms and decisions:** call the Skill tool with `mattpocock-skills:domain-modeling` to add the module's terms to `GLOSSARY.md` and to write an ADR under `docs/adr/` for any decision the code makes that a newcomer would question. (`grill-with-docs` is user-invoked only, so the skill calls `domain-modeling` directly.)
   - **Fact-check:** start a subagent with a fresh context that gets only the doc paths and the code. For each claim it answers *verified*, *wrong*, or *unsupported*, with the line that proves it. Fix or delete everything that is not verified, and keep the table at the end of the doc.
2. **Run it (10 min).**

   ```text
   /document-module src/record_file.cpp
   ```

   Answer the glossary questions it asks. Watch the fact-check: what did it remove?
3. **Check (5 min).** Pick three claims and verify them yourself. Does the doc say that `rf_off` multiplies in `long`, and that `long` is 32-bit on Windows? A doc that states the code's facts exactly is how a newcomer would spot AUD-877.
4. **Hook it into the pipeline (5 min).** Add a last stage to `ticket-to-pr`: when the change touched a module that has `docs/modules/<module>.md` or terms in `GLOSSARY.md`, run `document-module` on the changed files only, and list the doc changes under **Docs** in the PR body.

To reuse on your own code, point it at one legacy module of yours in Build 4, and add your build command and naming conventions to its Gotchas.

## Done when

- Your `ticket-to-pr` skill has one new branch and at least one new Gotcha.
- A: `.scratch/AUD-877/analysis.md` exists with a red-then-green test. B: `docs/modules/record_file.md` with a fact-check table, `GLOSSARY.md`, and an ADR if the code makes a decision worth recording, all checked against the code.

If a live step fails, the instructor has fallback outputs: an analysis, a module doc, a glossary, and an ADR.

---
name: document-module
description: Write or update documentation for one code module from the code itself, then fact-check it against the code. Use when the user runs /document-module with a file or directory, or when ticket-to-pr asks to refresh docs for changed files.
argument-hint: "<file or directory>"
---

# Document module

Goal: `docs/modules/<module>.md` explains how the module works today, every claim cites the code, and a fresh-context fact-check has verified each claim. `GLOSSARY.md` and `docs/adr/` hold the module's terms and decisions. This skill never edits source code, never suggests changes in the doc, and makes no network calls.

## 1. Research (how it works today)

- Read `CLAUDE.md`, `GLOSSARY.md`, and `docs/adr/` if they exist, then the module, its header, its callers, and its tests. For a module with several files, give each file to a read-only subagent (Explore) and ask for behaviour with `file:line` references; synthesise the answers yourself.
- Write `docs/modules/<module>.md`:
  - **Summary:** two or three paragraphs: what the module is for, its inputs and outputs, and who calls it.
  - **Findings:** one section per concept. Each header states a fact ("Record offsets are the 64-byte header plus index times record size"), not a topic ("Offsets"). Each claim cites `file:line`. Name units (bytes, records, ms), integer types and their widths, and platform differences.
  - **Tests:** which behaviours the tests cover, which they do not, and on which platform CI runs. Distinguish tests read from tests run; a run needs its command and result.
  - **Open questions:** what the code does not explain.
- Describe only what exists. No "should", no improvements, no critique: those belong in a ticket.

## 2. Terms and decisions

- Call the Skill tool with `mattpocock-skills:domain-modeling`. Add each module term to `GLOSSARY.md` with its abbreviation in the code (`rsz` → **Record size**). Ask the user to confirm any term whose meaning the code does not settle.
- Write an ADR under `docs/adr/` only for a decision a newcomer would question and the code or history makes visible (a format, a width, a deliberate limit). Do not invent the reason: if it is unknown, write "Reason not recorded" and add it to Open questions.

## 3. Fact-check (fresh context)

- Start a subagent with a fresh context (Agent tool). Give it only the paths of the new or changed docs and of the module. Never pass this conversation.
- For every claim it answers **verified** (with the proving line), **wrong** (with the line that contradicts it), or **unsupported** (nothing in the code proves it).
- Fix every wrong claim and delete or move every unsupported one to Open questions. Re-run the check once if more than a quarter of the claims changed.
- Append a **Fact-check** table to the module doc: claim, verdict, evidence, and the date.

## Update mode

When called with changed files only (for example by `ticket-to-pr`), update only the sections and glossary entries those files affect, re-run the fact-check on the changed claims, and report a short "Docs changed" list for the PR body.

## Final report

Paths written, number of claims and how many the fact-check verified, fixed, or removed, glossary terms added, ADRs written, and open questions for the user.

## Gotchas

- Read-only on code: this skill never edits source files.
- C++: name units and integer widths. `long` and `unsigned long` are 32-bit on Windows (x86 and x64) and 64-bit on Linux; a doc that says "64-bit" without naming the platform is wrong for half the team.
- Old abbreviations (`rf_`, `rsz`, `fsz`) go into the glossary verbatim next to the plain term, so search finds both.
- A tidy doc is not a true doc. The fact-check table is the evidence; never drop it to shorten the doc.

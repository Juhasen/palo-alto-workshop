---
name: ticket-to-pr
description: Take one ticket from Jira (through the Claude connector) or a pasted ticket to a validated change and a PR description. Use when the user runs /ticket-to-pr with a ticket id or a ticket file.
disable-model-invocation: true
argument-hint: "<JIRA-ID> | <path to ticket.md>"
---

# Ticket to PR

Goal: one ticket becomes a local branch with tested commits and `.scratch/<ticket-id>/pr.md`, a PR description a reviewer can audit in two minutes. This skill never pushes, never opens a PR, and never writes to Jira; a human does those.

Follow `docs/agents/issue-tracker.md` for where tickets and specs live. Make no network calls: Jira only through the Claude connector, anything else through the policy broker (TBD), otherwise ask the user.

## 1. Ticket

- If the argument looks like a Jira key and the Jira connector is available, read the ticket with it: summary, description, acceptance criteria, and comments. Read only.
- If the argument is a file, read it. If there is neither, ask the user to paste the ticket.
- Save it to `.scratch/<ticket-id>/ticket.md`. Restate the acceptance criteria as a numbered list and list anything ambiguous or contradictory.
- If the ticket is a bug report, say so; Build 3 adds the bug branch here.

## 2. Spec (stop: approval)

- If acceptance criteria are missing, vague, or an ambiguity would change the implementation, call the Skill tool with `mattpocock-skills:grilling` and resolve it with the user first.
- Call the Skill tool with `pa-to-spec`. It writes `.scratch/<ticket-id>/spec.md`.
- **Stop.** Show the spec path and the agreed test seams, and wait for the user to approve or edit. Do not continue on silence.

## 3. Implement

- Create a local branch `feature/<ticket-id>-<slug>` from the current branch. Refuse to work on `main` or `master`.
- Start a subagent with a fresh context (Agent tool, model Sonnet). Give it only pointers: the spec path, `CLAUDE.md`, and the instruction to run the `pa-implement` skill. Never pass this conversation's reasoning.
- It must report: files changed, commits, the `build.bat` output summary, the compiler and architecture used, and every target not run.

## 4. Validate (stop: red build or blocker)

- Run `build.bat` yourself and read the output. The implementer's report is a claim, not evidence.
- Call the Skill tool with `pa-code-review` with the branch start as the fixed point. Its reviewers run in fresh contexts and see the diff and spec, not the implementer's report.
- Walk each acceptance criterion and name the test or input that proves it.
- Fix every blocker and spec gap once, in a new fresh subagent with the same rules as step 3, then rebuild and review again.
- **Stop** if the build is red, a blocker remains, or a fix would break `CLAUDE.md` (for example C++20 on the MSVC 19.16 target). Report what failed; do not write a PR description that hides it.

## 5. PR body

- Call the Skill tool with `pa-pr`. It writes `.scratch/<ticket-id>/pr.md` with the evidence table and the title format; fill the table from the real output of stages 3 and 4, not from memory.
- Check the result yourself: every row filled or marked "not run", and no claim without a command behind it.

## 6. Docs (added in Build 3, option B)

- If the change touched a module that has `docs/modules/<module>.md` or terms in `GLOSSARY.md`, call the Skill tool with `document-module` in update mode on the changed files only.
- Add its "Docs changed" list under **Docs** in `pr.md`. If no docs exist for the module, write "No module docs" there; do not generate a full doc during a ticket.

## Final report

Branch name, commit list, build result with compiler and architecture, number of review findings and their decisions, anything deferred, and the path to `pr.md`. End with: "Open the PR yourself after reading the diff."

## Gotchas

- C++17 only; the legacy target is MSVC 19.16. Name the compiler and architecture behind every claim; a pass on x64 does not prove x86.
- `unsigned long` is 32-bit on Windows. A green run on 64-bit Linux or Clang can hide the overflow the ticket is about.
- Endpoint policy blocks reading `./build`, `.env`, and `secrets/`, and blocks `curl`, `wget`, and `WebFetch`. Read test results from console output; when something blocked is needed, stop and ask the user.
- A skill marked `disable-model-invocation: true` cannot be called from here. Call `pa-to-spec`, `pa-implement`, `mattpocock-skills:grilling`, never `to-spec` or `grill-me`.
- The second review only finds new things if it starts blind; never hand it the first review's findings.

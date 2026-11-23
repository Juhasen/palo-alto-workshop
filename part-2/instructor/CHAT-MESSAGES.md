# Meet chat messages

Paste-ready text for the Google Meet chat, one block per build. Meet chat messages are limited to 500 characters, so each build is split into two messages under that limit. Paste both right after you show the "Now you" slide, then stop sharing.

## Build 1 (0:15)

```text
Build 1 (0:15–0:45, 30 min): have Claude Code adapt the five skills
1. /plugin shows mattpocock-skills. Ask Claude to write docs/agents/issue-tracker.md (README step 1).
2. Copy ..\build-1-adapt\skeleton\adapt-skill into .claude\skills and fill it in: local source and license, audit list, route / replace / delete, stop for approval.
3. Run /adapt-skill <folder> in order: code-review, implement (--callable), to-spec (--callable), diagnosing-bugs, pr (add evidence rules). Approve each table.
```

```text
4. Review the diff with AUDIT-WORKSHEET.md. Fix adapt-skill for every miss and run it again.
5. /skills lists five pa- skills; each points at docs/agents/issue-tracker.md.
Done when: a search of the pa- skills finds no curl, gh, http, or .sh, and you fixed one thing adapt-skill missed.
Full steps: part-2/build-1-adapt/README.md
```

## Build 2 (0:45)

```text
Build 2 (0:45–1:20, 35 min): write ticket-to-pr and run it on NET-1502
1. In build-2-pipeline: build.bat (9 pass). Copy your pa- skills and docs\ in. Copy skeleton\ticket-to-pr into .claude\skills.
2. Fill in the five stages: ticket, spec (stop for approval), implement in a fresh subagent, validate (stop if red), PR body.
3. Run /ticket-to-pr TICKET.md. When a stage goes wrong, fix the skill and add a Gotcha.
```

```text
4. Check it yourself: run build.bat, open the diff, find the test behind two acceptance criteria.
5. Read .scratch/NET-1502/pr.md: is anything claimed that no output shows?
Done when: pr.md exists with a green build (compiler and architecture named), or the skill stopped with a clear reason. At least three Gotchas.
Full steps: part-2/build-2-pipeline/README.md
```

## Build 3 (1:30)

```text
Build 3 (1:30–2:00, 30 min): extend the pipeline, pick A or B
1. In build-3-extend: build.bat (7 pass). Copy your .claude and docs from Build 2.
A. Bug tickets: in stage 1 of ticket-to-pr, route bugs through pa-diagnosing-bugs first and save .scratch/<id>/analysis.md. Run /ticket-to-pr BUG-TICKET.md. No hypotheses before a red test.
```

```text
B. Docs: copy skeleton\document-module into .claude\skills, fill in research (file:line), terms (domain-modeling), fresh fact-check. Run /document-module src/record_file.cpp, then add a Docs stage to ticket-to-pr.
Done when: A, analysis.md with a test that goes red, then green. B, docs/modules/record_file.md with a fact-check table, plus GLOSSARY.md.
Full steps: part-2/build-3-extend/README.md
```

## Build 4 (2:00)

```text
Build 4 (2:00–2:45, 45 min): run your pipeline on a real ticket
1. Pick a small ticket: one component, a reproducible check, no schema or public API change.
2. Copy .claude/skills (pa-*, ticket-to-pr, document-module) and docs/agents into your repository.
3. Add your real build and test command to the Gotchas and to CLAUDE.md.
4. Run /ticket-to-pr <JIRA-KEY>. Approve the spec only if you would hand it to a colleague. Do not push.
```

```text
5. At 2:30 you go to a breakout room in pairs: review spec against ticket, diff against spec, evidence against real output.
Done when: .scratch/<id>/pr.md with a filled evidence table, and a list of skill fixes.
Full steps: part-2/build-4-real-ticket/README.md
```

At 2:30:

```text
Pair review: I am opening breakout rooms in pairs now. Share screens and review spec against ticket, diff against spec, evidence against real output. Back at 2:44.
```

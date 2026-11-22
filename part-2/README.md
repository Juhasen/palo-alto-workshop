# Claude Code Workshop, Part 2: Skills That Work Together

Start here. You will build your own `ticket-to-pr` workflow on top of Matt Pocock's skills, adapted to Palo Alto's rules, and run it on a real Jira ticket.

## Before the session

- Claude Code installed and signed in.
- `claude plugin install mattpocock-skills@claude-plugins-official`, then `/plugin` in Claude Code shows it enabled.
- The Jira connector enabled in Claude (pasting a ticket works as a fallback).
- A C++ compiler on `PATH`: MSVC (Developer Command Prompt), `clang++`, or `g++`.
- One small, real Jira ticket of yours for Build 4.

## The day

| Time | Block | Folder |
|---|---|---|
| 0:00–0:15 | Intro presentation | |
| 0:15–0:45 | Build 1: write an `adapt-skill` skill and have Claude Code adapt four public skills so they make no external calls | [build-1-adapt](build-1-adapt/README.md) |
| 0:45–1:20 | Build 2: write `ticket-to-pr` and run it on a sample ticket | [build-2-pipeline](build-2-pipeline/README.md) |
| 1:20–1:30 | Break | |
| 1:30–2:00 | Build 3: add a bug-analysis branch, or build a documentation skill that writes docs from code and fact-checks them | [build-3-extend](build-3-extend/README.md) |
| 2:00–2:45 | Build 4: your real ticket, then pair review | [build-4-real-ticket](build-4-real-ticket/README.md) |
| 2:45–3:00 | Share-out and `/retro` | |

Each build starts where the previous one ended: the skills you write in Build 1 are used in Build 2, and so on.

The workshop runs on Google Meet. Each build starts with a short screen-share demo, then the instructor pastes the steps in chat and stops sharing; the same steps are in each build README. If you get stuck, say so any time; you may be asked to share your screen or join a breakout room.

## Rules for every skill today

- Install nothing beyond Caveman, Ponytail, and `mattpocock-skills`.
- No network calls from the agent: no `curl`, `gh`, `npx`, or web fetches. Jira only through the Claude connector; other services through the policy broker (details from the instructor), or paste.
- Plain Markdown skills only: no scripts or hooks.
- Name the compiler and architecture behind every "it works", and list what you did not run.

Public skill sources we checked, with licenses: [SKILL-SOURCES.md](SKILL-SOURCES.md).

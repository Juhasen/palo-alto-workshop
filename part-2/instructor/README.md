# Instructor guide: running Part 2

Participants clone only `../participant/`. Everything in this folder is yours: the deck, answer keys, reference solutions, and fallbacks they get only when stuck.

## Folder map

| Here (instructor) | Participant counterpart | What it is |
|---|---|---|
| [intro-presentation.html](intro-presentation.html) | (none; you present it) | 23 slides: intro (1–17, with Part 1 questions on slide 2), one "Now you" slide per build (18, 19, 21, 22), break (20), wrap-up (23). Speaker notes inside the HTML |
| [build-1-adapt/](build-1-adapt/README.md) | `participant/build-1-adapt/` | Answer key: reference `adapt-skill`, findings table, adapted `skills/pa-*`, `docs/agents/` |
| [build-2-pipeline/](build-2-pipeline/README.md) | `participant/build-2-pipeline/` | Reference `ticket-to-pr` skill, reference solution and 35 tests, fallback spec |
| [build-3-extend/](build-3-extend/README.md) | `participant/build-3-extend/` | Root cause, fix, reference `document-module` skill, fallback analysis, module doc, glossary, ADR |
| (none) | `participant/build-4-real-ticket/` | Their own repository and Jira |
| [CHAT-MESSAGES.md](CHAT-MESSAGES.md) | (none; you paste them) | Paste-ready Google Meet chat text for each build, under the 500-character limit |
| [PLAN.md](PLAN.md) | | Design rationale and open questions |

## Run of show

The workshop runs on Google Meet. Participants cannot see your slide while they work in their own Claude Code, so every build follows the same rhythm:

1. **Demo (2 to 3 min, sharing).** Share the deck tab, show the step on screen.
2. **"Now you" slide (sharing).** Talk through the five steps and the timebox.
3. **Chat paste.** Paste the two messages for that build from [CHAT-MESSAGES.md](CHAT-MESSAGES.md). The same steps are in each participant README.
4. **Stop sharing.** Nothing on your screen matters during hands-on time, and the participants need their own screen.
5. **Check in by talking.** Stay on the call and ask people how far they are. Ask anyone stuck to share their screen, or take them into a breakout room so the others are not interrupted.
6. **Recap (2 min, sharing).** One finding most people missed, then the next "Now you" slide.

Open the deck in a browser tab (`F` for full screen, arrow keys, `G` for the slide grid) and share that tab, not your whole screen. Keep CHAT-MESSAGES.md and the instructor answer keys in a second window you never share. Set up breakout rooms in pairs before the session (Meet: Activities, Breakout rooms), so you can open them at 2:30 without delay.

| Time | You do | Slides | Participants open | Hand out if stuck |
|---|---|---|---|---|
| 0:00–0:15 | Present the intro; take Part 1 questions on slide 2 (2 to 3 min) | 1–17 | `participant/README.md` | |
| 0:15–0:45 | Demo the reference `adapt-skill` on `diagnosing-bugs` up to its findings table (3 min), after slides 10–12, show slide 18, paste Build 1 messages, stop sharing. Check in by voice; recap at 0:43 | 10–12, 18 | `participant/build-1-adapt/README.md` | `build-1-adapt/adapt-skill/`, then `build-1-adapt/skills/` and `docs/` |
| 0:45–1:20 | Demo copying the skeleton and the first `/ticket-to-pr TICKET.md` run (3 min), show slide 19, paste, stop sharing. Check in by voice; share again at 1:10 to show the reference skill; recap at 1:18 | 13, 15, 19 | `participant/build-2-pipeline/README.md` | `build-2-pipeline/fallback/spec.md`, then `ticket-to-pr/SKILL.md` |
| 1:20–1:30 | Break: leave slide 20 shared | 20 | | |
| 1:30–2:00 | Explain options A and B (2 min) with slide 14; show the Linux-green, Windows-red point. Show slide 21, paste, stop sharing. Check in by voice; recap at 1:58 | 14, 21 | `participant/build-3-extend/README.md` | `build-3-extend/fallback/*`, `build-3-extend/document-module/` |
| 2:00–2:45 | Show slide 22, paste, stop sharing. Help pick tickets in chat. Check in by voice. At 2:30 open breakout rooms in pairs for review; close them at 2:44 | 22 | `participant/build-4-real-ticket/README.md` | |
| 2:45–3:00 | Two or three people share their screen and show their pipeline; run `/retro`; agree an owner for publishing the skills | 23 | | |

Handing out reference material on Meet: paste the file into chat if it is short, or share your screen on it. Do not put answer files in the participant repository.

## Facilitation rules

- Demonstrate the first step of each build for 2 to 3 minutes, then stop sharing. Hand out reference material only after someone has tried.
- Silence on Meet usually means stuck, not done: ask people directly how far they are.
- Present Matt Pocock's skills as a third-party MIT project, not as built-in Claude features.
- If a skill tries `gh`, `curl`, or similar during the day, that is a finding for Build 1, not something to approve.
- Never accept "it works" without the compiler and architecture.
- If Build 2 overruns, shorten Build 3 to a show-only of option A. Protect Build 4.

## Before the session

- On a machine with Palo Alto's endpoint policies (see `../AGENTS.md`), check three things: Claude can read the installed `mattpocock-skills` folder (Build 1's `adapt-skill` depends on it), `build.bat` output reaches Claude through the console, and the Jira connector reads a ticket. Time one `/ticket-to-pr` run: always-on thinking makes runs slower.
- Run `build.bat` in `participant/build-2-pipeline` (expect `OK: 9 checks passed`) and in `participant/build-3-extend` (expect `OK: 7 checks passed`).
- Check the AUD-877 bug reproduces on a Windows compiler: add the regression check from `instructor/build-3-extend/README.md` to `participant/build-3-extend/tests/record_file_test.cpp` and expect `FAIL: record past 2 GB`. It does **not** reproduce on Linux or WSL.
- Have `instructor/build-1-adapt/skills` and `docs/` ready to hand out to anyone who falls behind.
- Pre-create breakout rooms in pairs in the Meet, and check participants can share their screen.
- Replace every "policy broker (TBD)" once you know how Claude reaches it. Search: `TBD`.

## Build 1 (0:15–0:45)

- Step 1 is `docs/agents/issue-tracker.md`; without it the adapted skills have nothing to point at and `adapt-skill` deletes the tracker lines instead (seen in the dry run).
- Participants write `adapt-skill` and let Claude Code do the edits; their job is the rules and the review. Demo the reference skill (`adapt-skill/SKILL.md`) on `diagnosing-bugs`, which has the most hits, and stop at the findings table.
- If someone's `adapt-skill` is not ready by 0:27, hand them the reference skill so they still get to the review.
- The phrase "publish to the issue tracker" is the finding an `adapt-skill` most often misses. Ask: "what would Claude run to publish?" A miss is fixed in `adapt-skill` (a Gotcha), not only in the output.
- Raise `disable-model-invocation` before Build 2: a user-invoked skill cannot be called by another skill. The answer key removes the flag from `pa-to-spec` and `pa-implement`.

## Build 2 (0:45–1:20)

- First run usually fails at stage 2 (wrong skill name, or a user-invoked skill). That failure is the lesson; have them add the Gotcha.
- When someone reports green, ask which compiler and architecture. On Clang or g++ under Windows, `unsigned long` is still 32-bit, so the legacy overflow test behaves like MSVC.
- Reference: `build-2-pipeline/ticket-to-pr/SKILL.md`; 35 reference checks in `build-2-pipeline/timeout_parser_test.cpp` (verified with GCC 13 and Clang on Linux x64; MSVC not run by the author).

## Build 3 (1:30–2:00)

- Root cause, fix, and fallbacks: `build-3-extend/`.
- Option A shows the best moment of the day: green CI on Linux, red on Windows. Anyone on Linux must report "could not reproduce", not "fixed".
- Option B: make them delete at least one glossary line the code does not support.

## Build 4 (2:00–2:45)

- Help pick tickets: one component, a reproducible check, no schema or API changes.
- Pairs review in breakout rooms, sharing screens, in this order: spec against the ticket, then the diff against the spec, then the evidence table against real output.
- Nobody pushes or opens a PR from the pipeline; they open it themselves after reading the diff.

## Wrap-up (2:45–3:00)

- `/retro` on the Build 4 session produces environment fixes; ask for two in chat.
- Ask who owns publishing the `pa-` skills and `ticket-to-pr` to the internal marketplace, and whether the other Palo Alto team's adapted set should be merged with this one.

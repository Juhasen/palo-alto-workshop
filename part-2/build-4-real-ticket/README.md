# Build 4 — Run your pipeline on a real ticket (45 min)

**Goal:** run the `ticket-to-pr` skill you built on a small, real ticket from your own Jira, in your own repository, and have a colleague review the result.

**On Google Meet:** these steps are also pasted in the chat. When the instructor calls for status (every 10 minutes), reply in chat with ✅ done, 🟡 working, or 🔴 stuck. If you are 🔴, the instructor asks you to share your screen or join a breakout room.

## Setup (5 min)

1. Pick a ticket: one component, a reproducible check, no schema or public API change. Ask the instructor if unsure.
2. In your repository, copy in your skills and config from Build 2 or 3:
   - `.claude/skills/pa-*` and `.claude/skills/ticket-to-pr/`
   - `docs/agents/issue-tracker.md`
3. Add your repository's real build and test command to the Gotchas of `ticket-to-pr`, and to `CLAUDE.md` if it is missing there.

## Run (25 min)

```text
/ticket-to-pr <JIRA-KEY>
```

The Jira connector reads the ticket. If it is not available, the skill asks you to paste it. Approve the spec only when you would hand it to a colleague. Every time the pipeline goes wrong, fix the skill and add a Gotcha.

## Pair review (15 min)

At 2:30 the instructor opens breakout rooms in pairs. Share your screen in turn and review in this order:

1. The spec against the ticket: is every acceptance criterion there, and nothing extra?
2. The diff against the spec: open the diff, not the summary.
3. The evidence table in `.scratch/<ticket-id>/pr.md` against real output: is anything claimed that no command shows? Which targets were not run?

Do not push or open the PR from the pipeline. Open it yourself after reading the diff, following your team's process.

## Bring to the wrap-up

- One Gotcha you added today that others should have.
- One stage where your marketplace tools would do better than the public skill.

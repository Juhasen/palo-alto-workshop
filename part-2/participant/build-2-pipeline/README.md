# Build 2 — Write `ticket-to-pr` and run it on a sample ticket (35 min)

**Goal:** write your own pipeline skill that takes a ticket to a validated change and a PR description, using the `pa-` skills from Build 1. Run it on the sample ticket here, where you know the code, before Build 4 runs it on a real Jira ticket.

```text
ticket (Jira connector or paste) → spec (stop: approval) → implement in a fresh subagent → validate (stop if red) → PR body
```

If you get stuck, the instructor has a reference skill, a reference solution, and a ready spec to continue from.

## Setup (3 min)

```powershell
cd build-2-pipeline        # from the Part 2 folder
build.bat          # baseline: 9 checks pass
claude
```

You need Build 1's `.claude/skills/pa-*` and `docs/agents/issue-tracker.md` in this folder. If you do not have them, ask the instructor for the reference set. Then copy `skeleton\ticket-to-pr` into `.claude\skills\`:

```powershell
mkdir .claude\skills -Force; Copy-Item -Recurse skeleton\ticket-to-pr .claude\skills\
```
 Run `/skills` and confirm `pa-to-spec`, `pa-implement`, `pa-code-review`, `pa-pr`, and `ticket-to-pr` are listed.

The sample is [TICKET.md](TICKET.md) (NET-1502): combined timeout units and an overflow that only shows on the Windows build.

## Steps

### 1. Write the skeleton (10 min)

Open `.claude/skills/ticket-to-pr/SKILL.md` (copied from `skeleton/`). Replace each `<...>` with goals and stop conditions, not keystrokes. Each section answers one question: where the ticket comes from and where it is saved; which skill runs, on which model, in which context; which command proves it and what blocks the PR; what evidence the PR body needs. Decide for each stage:

- which skill runs (`pa-to-spec`, `pa-implement`, `pa-code-review`, `pa-pr`, `mattpocock-skills:grilling`);
- whether it runs here or in a fresh subagent;
- what it must hand back, and what makes the pipeline stop.

### 2. Run it stage by stage (18 min)

```text
/ticket-to-pr TICKET.md
```

Watch each stage. When it goes wrong, stop it, fix the skill, and rerun from that stage. Every fix becomes one line under **Gotchas**. Typical first failures:

- The spec step calls `to-spec` instead of `pa-to-spec`, or fails because the skill is user-invoked only.
- The implementer reports "tests pass" without naming the compiler, or on x64 only.
- The review sees the implementer's summary and agrees with it.

### 3. Check the result (5 min)

- Run `build.bat` yourself.
- Open the diff, not the summary. Pick two acceptance criteria and find the test that proves each.
- Read `.scratch/NET-1502/pr.md`. Is anything claimed that no output supports?

Then compare with the reference skill the instructor shows, and keep what is better in yours.

## Your marketplace tools

If your team's internal marketplace already has a code-review or PR tool you trust, name it in the stage and keep the `pa-` skill as the fallback. A stage says *what* must happen; swapping the tool is a one-line change.

## Done when

- `/ticket-to-pr TICKET.md` reaches `.scratch/NET-1502/pr.md` with a green `build.bat`, or stops with a clear reason.
- Your skill has at least three Gotchas from today.

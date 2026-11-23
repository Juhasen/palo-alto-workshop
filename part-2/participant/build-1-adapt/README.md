# Build 1 — Have Claude Code adapt the skills you will use (30 min)

**Goal:** write an `adapt-skill` skill that holds Palo Alto's rules, run it on five of Matt Pocock's skills, and review what it changed. You leave with five `pa-*` project skills, one `docs/agents/issue-tracker.md`, and a tool you can run on the next public skill you want to use.

Claude Code does the editing. Your job is the rules and the review: you approve the findings before anything is written, and you check the result yourself.

## Setup (3 min)

In Claude Code, in the repository you will use for Build 2 (`../build-2-pipeline/` or your own):

```text
/plugin                              # mattpocock-skills is enabled?
/mattpocock-skills:to-spec           # user-invoked skills only appear when typed
```

If the plugin is missing, ask the instructor; do not install anything else.

Find the installed skill files: ask Claude *"Show me the path of the mattpocock-skills plugin's to-spec SKILL.md"*. You can also read the same files on GitHub in your browser at commit `49dd158` (plugin version 1.3.1).

## Steps

### 1. Write the tracker config (3 min)

Matt Pocock's skills expect a `/setup-matt-pocock-skills` run that tells them where tickets live. That setup skill runs `gh`/`glab` and creates labels, so we replace it with one file every `pa-` skill and `ticket-to-pr` will read. Ask Claude to write `docs/agents/issue-tracker.md` with exactly these rules, then read it:

- **Tickets** live in Jira. Read them through the Claude Jira connector (read only); if it is not available, the user pastes the ticket. Save it to `.scratch/<ticket-id>/ticket.md`.
- **"Publish to the issue tracker"** means writing a file: the spec to `.scratch/<ticket-id>/spec.md`, the PR body to `.scratch/<ticket-id>/pr.md`.
- **Never:** `gh`, `glab`, `curl`, or any web API; never create, update, label, or comment on a Jira issue; other services only through the policy broker (TBD).

### 2. Write `adapt-skill` (7 min)

```powershell
mkdir .claude\skills -Force; Copy-Item -Recurse ..\build-1-adapt\skeleton\adapt-skill .claude\skills\
```

Fill in each section of `.claude/skills/adapt-skill/SKILL.md`. Write goals and stops, not keystrokes. It must cover:

- **Source:** the upstream folder is local (the installed plugin, or a folder you copied from GitHub in the browser). Never a URL. Record the repository, path, commit, and license; stop if the license is missing or not MIT or Apache 2.0.
- **Audit, then stop:** search every file in the folder, not only `SKILL.md`, for commands *and* phrases:

  ```text
  curl  wget  http  WebFetch  WebSearch  gh  glab  npx  npm  pip  uv
  .sh  .py  .js  hooks  scripts/  Playwright
  "publish to the issue tracker"   "fetch the ticket"   "open a PR"
  ```

  Each hit gets one of three fixes. **Route** it through the Jira connector (reading tickets only, never creating or updating issues) or the policy broker (TBD). **Replace** it with a local file under `.scratch/` or a paste. **Delete** it when nothing approved can do it, keeping the idea in words. Write the findings to a table under `.scratch/` and stop for your approval.
- **What is not a finding:** files for other agents (`agents/openai.yaml`) are simply not copied, and words in sample code or design advice ("HTTP", `fetch()` in a TypeScript example) are not actions.
- **Tracker:** stop if `docs/agents/issue-tracker.md` is missing. Replace "run `/setup-matt-pocock-skills`", "fetch from the issue tracker", and "publish to the issue tracker" with "follow `docs/agents/issue-tracker.md`".
- **Calls to other skills:** point them at the `pa-` version where one exists. If there is none, read the called skill: a clean one is called as-is by its plugin name (`mattpocock-skills:tdd`); one with findings must be adapted first. Never replace a call with a written-out summary, and a `pa-` skill must never call an unadapted original that has findings.
- **`disable-model-invocation: true`:** with it, no other skill can call this one through the Skill tool. The pipeline in Build 2 calls `pa-to-spec` and `pa-implement`, so those two must lose the flag.
- **Write:** `.claude/skills/pa-<name>/` with `SKILL.md` (renamed, approved fixes only, a "Palo Alto rules" section), `SOURCE.md` (source, commit, list of changes), and the upstream `LICENSE` unchanged. No scripts.
- **Verify:** search the new folder again; any hit outside the rules section is a miss.

### 3. Run it on the five skills (10 min)

Adapt these five, in this order, because each later skill calls the earlier ones:

| Skill | Why the pipeline needs it |
|---|---|
| `code-review` | Stage 4: blind two-axis review in two sub-agents. Calls no skill, but tells the user to run `/setup-matt-pocock-skills` and fetches issue references (`#123`, GitLab `!67`) from the tracker |
| `implement` | Stage 3: spec → code. Calls `tdd` and `code-review` (pipeline calls it, so `--callable`) |
| `to-spec` | Stage 2: ticket → spec saved as a local file (pipeline calls it, so `--callable`) |
| `diagnosing-bugs` | Build 3: bug-ticket branch. Calls nothing |
| `pr` | Stage 5: PR body. No external calls, so this one is a customization: ask `adapt-skill` to **add** the Palo Alto evidence rules (save to `.scratch/<ticket-id>/pr.md`, never open a PR, command + compiler + architecture on every claim, targets not run, no screenshots) |

These are used as they are, by their plugin name. `adapt-skill` should find them clean and not copy them:

| Skill | Called by | Why no copy |
|---|---|---|
| `tdd` | `implement` | Calls only `codebase-design` and mentions `code-review`; no network, no tracker. Its examples are TypeScript, which is fine as reading |
| `codebase-design` | `tdd` | Reference only; "HTTP" appears in design advice, not as an action |
| `grilling`, `domain-modeling` | `ticket-to-pr` in Build 2 | No network, no tracker, callable. They only start local sub-agents or write `GLOSSARY.md` and ADRs |

```text
/adapt-skill <path to the plugin's to-spec folder> --callable
```

Read every findings table before you approve it. Wherever upstream says "run `/setup-matt-pocock-skills`" or "publish to the issue tracker", the fix should point at `docs/agents/issue-tracker.md`, not delete the line. Check that every `pa-` skill uses the same paths: `ticket-to-pr` in Build 2 looks for `.scratch/<ticket-id>/spec.md`, not `.scratch/spec-<slug>.md`.

### 4. Review what it did (7 min)

Use [AUDIT-WORKSHEET.md](AUDIT-WORKSHEET.md). For each skill, open the diff between upstream and `pa-` and check it against the findings table. The misses that matter are phrases, not commands: "publish to the issue tracker" makes an agent pick a CLI on its own. Every miss is a fix to `adapt-skill` (add it to its Gotchas), not only to the `pa-` skill. Run it again if you changed it.

Then run `/skills` and confirm the five `pa-` skills are listed. Ask Claude: *"Using only pa-to-spec, what would you do to publish a spec?"* The answer must be a local file path, not a CLI.

If you have time left, run `adapt-skill` on a fifth skill from [SKILL-SOURCES.md](../SKILL-SOURCES.md), copied from GitHub in the browser. That is how the team will bring in every public skill from now on.

## Policy broker

The broker is how other Palo Alto teams reach outside services. Until we know how Claude reaches it (MCP server, connector, or CLI), every adapted skill says **"policy broker (TBD)"** and falls back to the connector or a paste. Replace the TBD once the name is known.

## Done when

- `adapt-skill`, five `pa-` skills, and `docs/agents/issue-tracker.md` exist, each `pa-` skill with `SOURCE.md` and `LICENSE`.
- A search of `.claude/skills/pa-*` for `curl`, `gh `, `glab`, `http`, `Playwright`, and `.sh` finds nothing except the rules that forbid them.
- You found at least one thing `adapt-skill` got wrong or missed, and fixed the skill, not only its output.

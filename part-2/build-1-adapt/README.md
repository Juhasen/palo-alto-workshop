# Build 1 — Have Claude Code adapt the skills you will use (30 min)

**Goal:** write an `adapt-skill` skill that holds Palo Alto's rules, run it on four of Matt Pocock's skills, and review what it changed. You leave with four `pa-*` project skills, one `docs/agents/issue-tracker.md`, and a tool you can run on the next public skill you want to use.

**On Google Meet:** these steps are also pasted in the chat. If you get stuck, say so any time; you may be asked to share your screen.

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

### 1. Write `adapt-skill` (10 min)

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

  Each hit gets one of three fixes. **Route** it through the Jira connector or the policy broker (TBD). **Replace** it with a local file under `.scratch/` or a paste. **Delete** it when nothing approved can do it, keeping the idea in words. Write the findings to a table under `.scratch/` and stop for your approval.
- **Calls to other skills:** point them at the `pa-` version where one exists. A `pa-` skill that calls the unadapted original silently loses your changes.
- **`disable-model-invocation: true`:** with it, no other skill can call this one through the Skill tool. The pipeline in Build 2 calls `pa-to-spec` and `pa-implement`, so those two must lose the flag.
- **Write:** `.claude/skills/pa-<name>/` with `SKILL.md` (renamed, approved fixes only, a "Palo Alto rules" section), `SOURCE.md` (source, commit, list of changes), and the upstream `LICENSE` unchanged. No scripts.
- **Verify:** search the new folder again; any hit outside the rules section is a miss.

### 2. Run it on the four skills (10 min)

| Skill | Why the pipeline needs it |
|---|---|
| `to-spec` | Stage 2: ticket → spec (pipeline calls it) |
| `implement` | Stage 3: spec → code, drives `tdd` and `code-review` (pipeline calls it) |
| `code-review` | Stage 4: blind two-axis review |
| `diagnosing-bugs` | Build 3: bug-ticket branch |

```text
/adapt-skill <path to the plugin's to-spec folder> --callable
```

Read every findings table before you approve it. Run `code-review` before `implement`, so `implement` can point at `pa-code-review`. The first run that touches tickets should also write `docs/agents/issue-tracker.md`: tickets from the Jira connector, paste as fallback, specs under `.scratch/<ticket-id>/spec.md`, never `gh` or `curl`.

### 3. Review what it did (8 min)

Use [AUDIT-WORKSHEET.md](AUDIT-WORKSHEET.md). For each skill, open the diff between upstream and `pa-` and check it against the findings table. The misses that matter are phrases, not commands: "publish to the issue tracker" makes an agent pick a CLI on its own. Every miss is a fix to `adapt-skill` (add it to its Gotchas), not only to the `pa-` skill. Run it again if you changed it.

Then run `/skills` and confirm the four `pa-` skills are listed. Ask Claude: *"Using only pa-to-spec, what would you do to publish a spec?"* The answer must be a local file path, not a CLI.

If you have time left, run `adapt-skill` on a fifth skill from [SKILL-SOURCES.md](../SKILL-SOURCES.md), copied from GitHub in the browser. That is how the team will bring in every public skill from now on.

## Policy broker

The broker is how other Palo Alto teams reach outside services. Until we know how Claude reaches it (MCP server, connector, or CLI), every adapted skill says **"policy broker (TBD)"** and falls back to the connector or a paste. Replace the TBD once the name is known.

## Done when

- `adapt-skill`, four `pa-` skills, and `docs/agents/issue-tracker.md` exist, each `pa-` skill with `SOURCE.md` and `LICENSE`.
- A search of `.claude/skills/pa-*` for `curl`, `gh `, `glab`, `http`, `Playwright`, and `.sh` finds nothing except the rules that forbid them.
- You found at least one thing `adapt-skill` got wrong or missed, and fixed the skill, not only its output.

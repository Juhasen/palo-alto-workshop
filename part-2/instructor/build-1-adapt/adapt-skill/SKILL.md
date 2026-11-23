---
name: adapt-skill
description: Adapt a public skill to Palo Alto's rules (no network, no scripts, Jira only through the connector, licenses kept) and save it as a pa- project skill. Use when the user runs /adapt-skill with the path to an upstream skill folder.
disable-model-invocation: true
argument-hint: "<path to upstream skill folder> [--callable]"
---

# Adapt a skill

Goal: a `.claude/skills/pa-<name>/` folder with an adapted `SKILL.md`, `SOURCE.md`, and the upstream `LICENSE`, plus a findings table the user approved. This skill never edits the upstream files, never fetches anything from the web, and never copies a script.

## Palo Alto rules (what every adapted skill must obey)

- No network from the agent: no `curl`, `wget`, `gh`, `glab`, `npx`, `npm`, `pip`, `uv`, `WebFetch`, or `WebSearch`.
- Jira only through the Claude Jira connector, and **only to read** tickets. Never create, update, label, or comment on a Jira issue. Other outside services only through the policy broker (TBD). If neither is available, the user pastes the content.
- No scripts, hooks, or installers: plain Markdown only. Windows first: `build.bat` and PowerShell.
- Endpoint policy: never read `.env`, `./secrets/**`, `credentials.json`, `~/.ssh`, `~/.aws`, or `./build`. Take build and test results from the command's console output. Never suggest changing permissions or bypassing a block.
- C++17, legacy target MSVC 19.16. Name the compiler and architecture behind every verification claim.
- Nothing is published: specs, reviews, and reports are files under `.scratch/<ticket-id>/` (`spec.md`, `review.md`, `pr.md`), the paths in `docs/agents/issue-tracker.md`. "Publish to the issue tracker" always becomes "save the file", never "create a Jira issue". Never push, never open a PR.

## 1. Source

- Check that `docs/agents/issue-tracker.md` exists. If not, stop and ask the user to write it first (Build 1, step 1): every adapted skill points at it.

- The argument must be a local folder: the installed plugin (ask Claude Code for the plugin's install path) or a folder the user copied from GitHub in the browser. If the user gives a URL, stop and ask them to copy the folder instead.
- Record: upstream repository, path, version or commit (from the plugin's `plugin.json` or what the user tells you), and the license file. If there is no `LICENSE` in the folder or its repository root as the user provides it, or it is not MIT or Apache 2.0, stop: the skill cannot be vendored until legal says yes.
- List every file in the folder, not only `SKILL.md`. Scripts and reference files are where the network calls hide. Files for other agents (for example `agents/openai.yaml`) are not copied and are not findings; mention them once.

## 2. Audit (stop: user approves the findings)

Search every file for:

```text
curl  wget  http  WebFetch  WebSearch  gh  glab  npx  npm  pip  uv
.sh  .py  .js  .ts  hooks  scripts/  Playwright  Puppeteer
"issue tracker"  "publish"  "fetch the ticket"  "open a PR"  "push"  "label"  "setup-"
"Skill tool"  "invoke"  "/<other-skill-name>"
.env  secrets  credentials  ./build  "dangerously"  "bypass"  "permissions"
disable-model-invocation
```

Phrases matter as much as commands: "publish to the issue tracker" makes an agent pick a CLI on its own.

Write `.scratch/adapt/<name>/findings.md` with one row per hit:

| File:line | Quote | What it would do | Fix | New text |
|---|---|---|---|---|

Fix is one of **route** (Jira connector, policy broker), **replace** (a local file under `.scratch/`, or a paste), or **delete** (nothing approved can do it; keep the idea in words). If the user asks for Palo Alto additions (for example evidence rules in `pr`), list each as an **add** row. A finding is something the agent would *do*. Words in sample code or design advice (`fetch()` in a TypeScript example, "HTTP" in advice about the project's own code, "hooks" as a code smell) are not findings; list them under "Not a finding" so the user sees you checked.

Add a second table for calls to other skills ("call the Skill tool with ...", "see the X skill"). For each called skill:
- If `.claude/skills/pa-<it>` exists, point the call at it.
- Otherwise read the called skill. If it has no findings of its own (it only calls clean skills or none), keep the call and use its plugin name, for example `mattpocock-skills:tdd`. It needs no copy.
- If it has findings, stop and tell the user to adapt it first, then run this skill again.
- Never replace a skill call with a written-out summary of that skill: the call is how the upstream improvements keep reaching you.

Show the table and stop. Change it as the user says before writing anything.

## 3. Write the pa- skill

- Copy the upstream `SKILL.md` into `.claude/skills/pa-<name>/SKILL.md` and apply only the approved fixes. Keep everything else as upstream wrote it, so the next upstream diff stays readable.
- Rename `name:` to `pa-<name>` and adjust the description only where a fix requires it.
- Add a `## Palo Alto rules` section near the top, using the rules above that apply to this skill.
- `disable-model-invocation: true` stops other skills from calling this one through the Skill tool. Remove it only with `--callable` or when the user says a pipeline will call this skill; say what that changes.
- Copy reference Markdown files the skill needs, with the same fixes. Never copy scripts; describe the steps in Markdown instead if the skill relies on them.
- Every tracker line ("run `/setup-matt-pocock-skills`", "fetch from the issue tracker", "publish to the issue tracker") becomes "follow `docs/agents/issue-tracker.md`", not a deletion. The pa- skill stops if that file is missing.

## 4. SOURCE.md and LICENSE

- `LICENSE`: the upstream file, copied unchanged.
- `SOURCE.md`: upstream repository and path, commit or version, license, a bullet list of every change (one per approved finding), and an "Updating" note: when upstream changes, diff it against the recorded commit and port only what keeps these rules.

## 5. Verify

- Search `.claude/skills/pa-<name>/` for the patterns in step 2. Every hit must be inside the Palo Alto rules section that forbids it; anything else is a miss. Fix it or report it.
- Ask yourself, using only the adapted skill: "How would I publish the result?" The answer must be a local file path.

## Final report

Five lines at most: the new folder, the number of findings by fix type, the skill calls you redirected, whether `disable-model-invocation` was removed, and anything you could not fix.

## Gotchas

- Never edit files inside the plugin folder: the plugin updates itself and your changes would vanish.
- The setup skill of a plugin (for example `setup-matt-pocock-skills`) often runs `gh` or creates labels. Do not run it; read `docs/agents/issue-tracker.md` instead.
- Not every skill needs changes. If the audit finds nothing and the user asked for no additions, say so and do not create a copy.
- Adapt the leaves first: a skill that others call (`code-review`) before the skills that call it (`implement`).

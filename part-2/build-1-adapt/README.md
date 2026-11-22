# Build 1 — Adapt the skills you will use (30 min)

**Goal:** turn four of Matt Pocock's skills into Palo Alto versions that make no external calls, so the pipeline you build next can rely on them. You leave with four `pa-*` project skills and one `docs/agents/issue-tracker.md` you understand line by line.

**On Google Meet:** these steps are also pasted in the chat. When the instructor calls for status (every 10 minutes), reply in chat with ✅ done, 🟡 working, or 🔴 stuck. If you are 🔴, the instructor asks you to share your screen or join a breakout room.

The intro covered how to adapt a skill; the checklist is repeated below so you do not need the shared screen.

## Setup (3 min)

In Claude Code, in the repository you will use for Build 2 (`../build-2-pipeline/` or your own):

```text
/plugin                              # mattpocock-skills is enabled?
/mattpocock-skills:to-spec           # user-invoked skills only appear when typed
```

If the plugin is missing, ask the instructor; do not install anything else.

Find the installed skill files: ask Claude *"Show me the path of the mattpocock-skills plugin's to-spec SKILL.md"*. You can also read the same files on GitHub in your browser at commit `49dd158` (plugin version 1.3.1).

## Steps

### 1. Audit (10 min)

For each of these four skills, open `SKILL.md` and every file next to it:

| Skill | Why the pipeline needs it |
|---|---|
| `to-spec` | Stage 2: ticket → spec |
| `implement` | Stage 3: spec → code, drives `tdd` and `code-review` |
| `code-review` | Stage 4: blind two-axis review |
| `diagnosing-bugs` | Build 3: bug-ticket branch |

Search for these patterns and fill in [AUDIT-WORKSHEET.md](AUDIT-WORKSHEET.md): one row per hit, with the fix you choose.

```text
curl  wget  http  WebFetch  WebSearch
gh   glab   npx   npm   pip   uv
*.sh  *.py  *.js  hooks  scripts/
"publish to the issue tracker"   "fetch the ticket"   "open a PR"
```

Three fixes:

- **Route** it through an approved route: Jira through the Claude connector, other services through the policy broker (TBD).
- **Replace** it with a local file or a paste: "publish" becomes a file under `.scratch/`; no connector means the user pastes the ticket.
- **Delete** it when nothing approved can do it, and keep the idea (a failing test is the feedback loop). You can ask Claude to do the first pass: *"List every line in these four skills that could make a network call, run a script, or publish somewhere. Quote the line."* Then check its list yourself; it misses phrases like "publish to the issue tracker".

Also note every **call to another skill** ("Call the Skill tool with ..."). A `pa-` skill that calls the unadapted original silently loses your changes.

### 2. Adapt (12 min)

Create one folder per skill in your repository:

```text
.claude/skills/pa-to-spec/       SKILL.md  SOURCE.md  LICENSE
.claude/skills/pa-implement/     ...
.claude/skills/pa-code-review/   ...
.claude/skills/pa-diagnosing-bugs/ ...
docs/agents/issue-tracker.md
```

- Copy each upstream `SKILL.md`, rename `name:` to the `pa-` name, and apply your fixes.
- If the pipeline will call the skill (`pa-to-spec`, `pa-implement`), **remove `disable-model-invocation: true`**: with it, Claude cannot invoke the skill through the Skill tool, so a skill-calling-skill chain breaks. The same applies to upstream `grill-me`; call `mattpocock-skills:grilling` instead.
- Point skill-to-skill calls at `pa-` versions where one exists (`tdd` and `pr` need no changes; call them as `mattpocock-skills:tdd`).
- Add a short **Palo Alto rules** section: no network, Jira only through the connector, policy broker for anything else, C++17 and MSVC 19.16, name the architecture.
- `SOURCE.md`: upstream path, commit `49dd158`, license, and your list of changes. `LICENSE`: copy Matt Pocock's MIT license file.
- `docs/agents/issue-tracker.md`: where tickets come from (Jira connector, paste as fallback), where specs go (`.scratch/<ticket-id>/spec.md`), and what is never allowed.

### 3. Check (5 min)

Run `/skills` and confirm the four `pa-` skills are listed. Ask Claude: *"Using only pa-to-spec, what would you do to publish a spec?"* The answer must be a local file path, not a CLI.

When the instructor shows the reference adaptation, note any difference worth keeping.

## Policy broker

The broker is how other Palo Alto teams reach outside services. Until we know how Claude reaches it (MCP server, connector, or CLI), every adapted skill says **"policy broker (TBD)"** and falls back to the connector or a paste. Replace the TBD once the name is known.

## Done when

- Four `pa-` skills and `docs/agents/issue-tracker.md` exist, each skill with `SOURCE.md` and `LICENSE`.
- A search of `.claude/skills/pa-*` for `curl`, `gh `, `glab`, `http`, `Playwright`, and `.sh` finds nothing except the rules that forbid them.

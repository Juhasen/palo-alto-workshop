# Palo Alto Training v2 (Part 2: advanced skills)

Materials for Part 2 of the Palo Alto C++ team's Claude Code workshop: 3 hours on advanced skill use. Part 1 lives in `../palo-alto-training/` and is not edited from here. The team works in C++17 on Windows (MSVC 19.16 / Visual Studio 2017 targets), with legacy code up to 30 years old, plus some Go.

Layout: `participant/` is the only folder participants clone; it must never contain answers, reference solutions, or fallbacks. `instructor/` holds the deck, the run-of-show guide, and one answer-key folder per build, mirroring the participant folder names. Open: how Claude reaches the policy broker (marked TBD).

## Participant environment constraints

These apply to every demo, exercise, skill, and reference solution in this directory. Remove or replace anything that breaks them.

- **Install nothing that Palo Alto has not approved.** Approved plugins: Caveman, Ponytail, and (for Part 2) `mattpocock-skills`. RTK was not approved and is not part of this workshop; do not mention or depend on it. Do not assume any other plugin, marketplace, MCP server, package, CLI, or binary is available.
- **No network access from the agent.** Claude cannot run `curl`, `wget`, `gh`, `npx`, package managers, or anything else that fetches from the network, and cannot fetch URLs. No step may download at run time. External content (for example a Jira ticket) is pasted by the participant. A Jira connector in Claude is optional; always provide the paste-in path.
- **Plain Markdown only.** Skills, rules, prompts, templates, and fallbacks are plain Markdown (`SKILL.md`, `CLAUDE.md`, `AGENTS.md`, `.md`) and must work without scripts, installers, hooks, or extra runtimes. Matt Pocock's skills are installed with `claude plugin install mattpocock-skills@claude-plugins-official`. Other public skills are **copied from GitHub in the browser** into a project's `.claude/skills/`. Demos also ship a pre-copied fallback. Adapted versions live as project skills, never as edits inside a plugin's files.
- **Adapt every public skill before use.** Remove or rewrite anything that calls an external service, runs a script, or fetches from the web. Outside services (Jira, GitHub, and so on) are reached only through Palo Alto's internal **policy broker** or a connector, or replaced by a local file or a pasted text. Another Palo Alto team already runs Matt Pocock's skills adapted this way.
- **Keep everything non-invasive.** Do not change participants' global settings (`~/.claude`), system configuration, or the team's repositories. Project-local files inside a demo directory are fine.
- **Licenses travel with copied skills.** Every vendored skill keeps its upstream `LICENSE` file and a line in `SKILL-SOURCES.md` with the source repository and commit. Only use sources marked usable there; anything marked "ask legal" stays out of participant material until Palo Alto says yes.
- **Windows first.** Commands in demos are `build.bat` / PowerShell. Strip bash-only helper scripts from vendored skills.

## Palo Alto endpoint security policies (in force on participants' machines)

Every demo, exercise, and skill must work under these. Nothing may ask participants to work around them.

- **Restricted file access:** Claude Code cannot read `~/.ssh/*`, `~/.aws/*`, `.env` files, `./secrets/**`, `credentials.json`, or `./build` directories. Build output must not be read from `./build`; skills take results from the build command's console output. The demo folders build into the folder root, not `./build`.
- **Web and download tools blocked:** `curl`, `wget`, and `WebFetch` are blocked (consistent with "no network" above).
- **Managed hooks only:** no user or project hooks. Plugins that register hooks (for example Superpowers' SessionStart hook) cannot be installed; copy single skills instead.
- **No bypass:** participants cannot change permissions or security settings. No step may ask them to edit `settings.json` permissions or use a bypass mode.
- **Audit hooks:** `claude_audit` logs prompts and tool use. Nothing to do, but do not paste secrets into demos.
- **Always-on thinking:** `alwaysThinkingEnabled` is on. Runs are slower; keep timeboxes realistic.

## Writing conventions

- Name the compiler and architecture behind every verification claim; never claim x86 coverage from an x64 run.
- Present third-party skills as third-party (with author), not as built-in Claude features.
- Each demo has a paste-in fallback for any step that needs a live model or a connector.

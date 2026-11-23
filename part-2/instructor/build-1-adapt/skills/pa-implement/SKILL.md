---
name: pa-implement
description: "Implement a piece of work based on a local spec under .scratch/. Palo Alto adaptation of Matt Pocock's implement."
---

Implement the work described by the user in the spec or tickets.

If the user passes a ticket reference, read it from `.scratch/<ticket-id>/` as described in `docs/agents/issue-tracker.md` (Jira only through the Claude connector), and state its title before starting. If the reference is ambiguous, ask.

Call the Skill tool with "mattpocock-skills:tdd" where possible, at pre-agreed seams.

Compile regularly (the compiler is the typechecker), and run `build.bat` once at the end. Report the compiler and architecture it used.

Once done, call the Skill tool with "pa-code-review" to review the work.

Commit your work to the current branch. Never push, and never open a PR: a human does that.

## Palo Alto rules

- No network from the agent: never run `curl`, `wget`, `gh`, `glab`, `npx`, or a web fetch. Jira is reached only through the Claude Jira connector; other services only through the policy broker (TBD: name it once known). If neither is available, ask the user to paste the content.
- Install nothing. Use only the build and test command the repository documents (`build.bat`).
- Endpoint policy: never read `.env`, `./secrets/**`, `credentials.json`, `~/.ssh`, `~/.aws`, or `./build`; take results from the command's console output. If a blocked file or tool is needed, stop and tell the user; never suggest a workaround.
- C++17 only; the legacy target is MSVC 19.16 (Visual Studio 2017). Name the compiler and architecture behind every claim, and list the targets not run.

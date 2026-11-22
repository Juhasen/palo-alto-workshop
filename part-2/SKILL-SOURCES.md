# Public skill sources: license and constraint check

Checked on 2026-11-22 by reading each repository's `LICENSE` files and the file types inside each skill at the commit listed. This is a reading of the license texts, not legal advice: Palo Alto's legal or open-source office should confirm before material is handed to participants.

**Markdown-only** means the skill works from its `.md` files alone. Many repositories also ship a `plugin.json` or `agents/openai.yaml` (metadata for other agents); those are ignored when we copy the Markdown, so they do not count against a skill.

**How we use every source:** participants copy the skill's Markdown folder from GitHub in the browser into `.claude/skills/<name>/`, keep the upstream `LICENSE`, record the commit, then **adapt** it: strip or reroute every external call (through the policy broker, a connector, a local file, or a paste). The "Notes" columns below list what to strip per skill. No `/plugin install`, no marketplace add, no hooks.

## Summary

| Source (commit) | License | Fit | Use in Part 2 |
|---|---|---|---|
| [mattpocock/skills](https://github.com/mattpocock/skills) (`abeeaf9`, 2026-11-19) | MIT | Most engineering skills are Markdown-only | **Core.** Spec, TDD, review, bug diagnosis, docs |
| [obra/superpowers](https://github.com/obra/superpowers) (`22f0b46`, 2026-11-03) | MIT | Several skills Markdown-only; the plugin itself installs a SessionStart hook | Bug analysis, verification. Copy selected `SKILL.md` only |
| [anthropics/claude-plugins-official](https://github.com/anthropics/claude-plugins-official) `plugins/` (`73c8cf3`, 2026-11-20) | Apache 2.0 | `feature-dev`, `pr-review-toolkit`, `code-review`, `claude-md-management` are Markdown-only; `code-modernization` is not | Review agents, `CLAUDE.md` upkeep |
| [humanlayer/skills](https://github.com/humanlayer/skills) (`4d69d20`, 2026-11-01) | MIT | `rpi`, `show-me`, `improve-claude-md` Markdown-only | Documenting legacy code (research phase) |
| [anthropics/skills](https://github.com/anthropics/skills) (`e4bb5d9`, 2026-11-16) | Apache 2.0 per skill `LICENSE.txt`; `doc-coauthoring` has **no license file** | `skill-creator`, `docx`, `pdf` need Python; `doc-coauthoring`, `internal-comms` are Markdown-only | `doc-coauthoring` as a pattern only (ask legal before copying) |
| [trailofbits/skills](https://github.com/trailofbits/skills) (`149d7b2`, 2026-11-12) | **CC BY-SA 4.0** (share-alike) | `differential-review`, `sharp-edges`, `audit-context-building`, `spec-to-code-compliance`, `vulnerability-triage-brocards` Markdown-only; `c-review`, `patching-bugs`, `regression-hunt`, `variant-analysis` need Python/`uv` | Security-flavoured bug analysis. **Ask legal**: adaptations shared outside the team must stay CC BY-SA |

Matt Pocock's set is also listed in Anthropic's official marketplace as `mattpocock-skills@claude-plugins-official`. If Palo Alto's internal marketplace mirrors that one, the team could request approval for the plugin instead of vendoring. Worth asking before the workshop.

## mattpocock/skills (MIT)

Small, composable skills that call each other through the Skill tool. Most issue-tracker skills read a `docs/agents/issue-tracker.md` written by `/setup-matt-pocock-skills`; that file can describe **local Markdown files** (`.scratch/<feature>/spec.md`, `issues/NN-*.md`) or "other", for example "Jira via the Claude connector, else a pasted ticket". This is the hook for our ticket-to-PR pipeline.

| Skill | Markdown-only | Notes for this team |
|---|---|---|
| `grill-me` / `grilling` | Yes | Interview that sharpens a ticket or plan. Good front end for vague Jira tickets |
| `grill-with-docs` + `domain-modeling` | Yes | Interview that writes `GLOSSARY.md` and ADRs as it goes. **Documentation** |
| `to-spec` | Yes | Spec from the conversation (no interview), published to the tracker. Template is web-product flavoured (user stories); C++ teams will want to adapt |
| `to-tickets` | Yes | Splits a spec into vertical-slice tickets with blocking edges |
| `implement` | Yes | Drives `tdd` at agreed seams, then `code-review`, then commits |
| `implement-spec` | Yes | Parallel subagents in git worktrees per ticket. Advanced; probably a show-only |
| `tdd` (+ `tests.md`, `mocking.md`) | Yes | Red-green at pre-agreed seams. Mentions "typechecking": for C++ read "compile" |
| `code-review` | Yes | Two parallel subagents: Standards (repo rules + Fowler smells) and Spec |
| `diagnosing-bugs` | Mostly | Feedback loop, minimise, ranked falsifiable hypotheses, instrument, regression test. **Bug analysis.** Drop `scripts/hitl-loop.template.sh` (bash) and the curl/Playwright examples |
| `pr` | Yes | PR body: summary visual, before/after evidence, merge danger. Credits HumanLayer `show-me` |
| `codebase-design` | Yes | Vocabulary (seam, deep module) that `tdd` and `to-spec` rely on |
| `handoff` | Yes | Writes a handoff doc for a fresh session; Windows `%TEMP%` handled |
| `retro` | Yes | After-session suggestions to improve the agent's environment. Good wrap-up exercise |
| `setup-matt-pocock-skills` | Yes | Run once per repo. Choose "local" or "other"; the GitHub/GitLab paths call `gh`/`glab` and need network, so skip them |
| `triage`, `wayfinder`, `ask-matt` | Yes | Useful, but tracker-heavy; mention only |
| `research` | No (fetches web sources) | Exclude |
| `wizard`, `git-guardrails-claude-code`, `setup-pre-commit` | No (bash/scripts, hooks) | Exclude |
| `improve-codebase-architecture`, `prototype` | Yes, but produce HTML reports/prototypes | Optional |

Dependencies to copy together: `implement` → `tdd`, `code-review`; `tdd` → `codebase-design`; `grill-me` → `grilling`; `grill-with-docs` → `grilling`, `domain-modeling`.

## obra/superpowers (MIT)

Do not install the plugin: it registers a SessionStart hook (`hooks/hooks.json`). Copy single skills.

| Skill | Markdown-only | Notes |
|---|---|---|
| `systematic-debugging` (+ `root-cause-tracing.md`, `defense-in-depth.md`) | Yes once `find-polluter.sh` and the `.ts` example are removed | Root cause before fix; pairs with `diagnosing-bugs` for a compare-and-contrast exercise |
| `verification-before-completion` | Yes | "No claim without command output": matches our evidence rule |
| `receiving-code-review`, `requesting-code-review` | Yes | How to act on review findings |
| `writing-plans`, `test-driven-development`, `dispatching-parallel-agents` | Yes | Overlap with Matt's set; mention only |
| `brainstorming`, `executing-plans`, `subagent-driven-development`, `writing-skills` | No (scripts, local server) | Exclude |

## anthropics/claude-plugins-official, `plugins/` (Apache 2.0)

These are plugins (commands and agents), not only skills, but the ones below are pure Markdown and can be copied into `.claude/agents/` and `.claude/commands/`. Check `external_plugins/` entries individually; they are third-party.

| Plugin | Markdown-only | Notes |
|---|---|---|
| `pr-review-toolkit` | Yes | Six review agents. `silent-failure-hunter` (swallowed errors) and `pr-test-analyzer` suit legacy C++ |
| `feature-dev` | Yes | Explorer, architect, reviewer agents. Useful for "explain this legacy module" |
| `code-review` | Yes | Single review command |
| `claude-md-management` | Yes (two PNGs in README) | `claude-md-improver` skill and `/revise-claude-md`. **Documentation** of repo conventions |
| `code-modernization` | No (TypeScript, Python, hooks) | Exclude. Its `agents/legacy-analyst.md` and `business-rules-extractor.md` are good reading for documenting legacy code |

## humanlayer/skills (MIT)

| Skill | Markdown-only | Notes |
|---|---|---|
| `rpi` (research, design, plan, implement) | Yes | `create-research` writes a cited research doc of how existing code works: a good **legacy documentation** generator. Drop the `web-search-researcher` subagent |
| `show-me` | Yes | The PR-body pattern Matt's `pr` is based on |
| `improve-claude-md` | Yes | Alternative to `claude-md-improver` |

## anthropics/skills

| Skill | License | Markdown-only | Notes |
|---|---|---|---|
| `doc-coauthoring` | **No license file** in the folder or repository root | Yes | Three-stage doc workflow (context gathering, refinement, reader testing). Show as a pattern; do not copy until legal confirms |
| `internal-comms` | Apache 2.0 | Yes | Status reports, incident reports |
| `skill-creator` | Apache 2.0 | No (Python evals) | The authoring guidance is readable; the eval tooling is not usable here |
| `docx`, `pdf`, `pptx`, `xlsx` | Apache 2.0 | No (Python, Node) | Exclude |

## trailofbits/skills (CC BY-SA 4.0)

Security-focused, several aimed at C/C++. Share-alike means our adapted versions would have to be released under CC BY-SA if shared beyond the team, so get a legal answer first.

| Skill | Markdown-only | Notes |
|---|---|---|
| `differential-review` | Yes | Security review of a diff with blast radius and test coverage. Strong fit for the validation step |
| `sharp-edges` | Yes | Footgun APIs and configurations |
| `audit-context-building` | Yes (eval `.js` files are not part of the skill) | "Understand before hunting": what each function assumes and guarantees. Documentation plus bug analysis |
| `spec-to-code-compliance` | Yes | Code against its spec: which requirements hold, are contradicted, or absent |
| `vulnerability-triage-brocards` | Yes | Triage heuristics |
| `modern-cpp` | Yes | Targets C++20/23/26; conflicts with the C++17 / MSVC 19.16 rule. Exclude |
| `c-review`, `patching-bugs`, `regression-hunt`, `variant-analysis`, `post-patch-validation` | No (Python via `uv`) | Exclude |

## Excluded for these constraints

Anything that installs a plugin with hooks, starts a local server, runs Python/Node/bash helpers, or fetches from the web: Matt's `research`, `wizard`, `git-guardrails-claude-code`; Superpowers' `brainstorming`, `executing-plans`, `subagent-driven-development`; `code-modernization`; Anthropic's document skills; Trail of Bits' Python-backed skills.

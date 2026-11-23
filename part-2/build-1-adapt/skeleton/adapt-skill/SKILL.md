---
name: adapt-skill
description: Adapt a public skill to Palo Alto's rules (no network, no scripts, Jira only through the connector, licenses kept) and save it as a pa- project skill. Use when the user runs /adapt-skill with the path to an upstream skill folder.
disable-model-invocation: true
argument-hint: "<path to upstream skill folder> [--callable]"
---

# Adapt a skill

Goal: <one sentence: what exists at the end, and what this skill never does>

## Palo Alto rules (what every adapted skill must obey)

- No network from the agent: no curl, wget, gh, glab, npx, or web fetch.
- Jira only through the Claude Jira connector, and only to read tickets: never create or update a Jira issue. Other services only through the policy broker (TBD); otherwise the user pastes the content.
- Plain Markdown only: no scripts, hooks, or installers.
- Endpoint policy: never read `.env`, `./secrets/`, `credentials.json`, `~/.ssh`, `~/.aws`, or `./build`; never suggest changing permissions.
- C++17, legacy target MSVC 19.16. Name the compiler and architecture behind every claim.
- <anything else?>

## 1. Source

<Where may the upstream skill come from, and where not? What do you record about it? When do you stop because of the license? Which files do you look at?>

## 2. Audit (stop: user approves the findings)

<Which commands and which phrases do you search for? Where do you write the findings, in what table? Which three fixes are allowed? What counts as a finding, and what does not? What do you do with a call to a skill that has no pa- version?>

## 3. Write the pa- skill

<Where does the copy go? What do you change, and what do you leave as upstream wrote it? What about disable-model-invocation? What about scripts and reference files?>

## 4. SOURCE.md and LICENSE

<What goes in each?>

## 5. Verify

<How do you prove nothing slipped through?>

## Final report

<What does the user see in five lines?>

## Gotchas

- Never edit files inside the plugin folder: the plugin updates itself.

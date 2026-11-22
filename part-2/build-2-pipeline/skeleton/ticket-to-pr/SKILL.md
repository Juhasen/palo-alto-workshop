---
name: ticket-to-pr
description: Take one ticket from Jira (through the Claude connector) or a pasted ticket to a validated change and a PR description. Use when the user runs /ticket-to-pr with a ticket id or a ticket file.
disable-model-invocation: true
argument-hint: "<JIRA-ID> | <path to ticket.md>"
---

# Ticket to PR

Goal: <one sentence: what exists at the end, and what this skill never does>

## 1. Ticket

<Where does the ticket come from? Where is it saved? What do you restate before moving on?>

## 2. Spec (stop: approval)

<When do you grill? Which skill writes the spec, and where? What does the user approve?>

## 3. Implement

<Which skill, which model, which context? What must the implementer report back?>

## 4. Validate (stop: red build or blocker)

<Which command proves it? Which review runs, and does it see the implementer's reasoning? What blocks the PR?>

## 5. PR body

<Which skill writes it? Which evidence is mandatory? Where is it saved? Who opens the PR?>

## Final report

<What does the user see in two minutes?>

## Gotchas

- C++17 only; the legacy target is MSVC 19.16. Name the compiler and architecture behind every claim.

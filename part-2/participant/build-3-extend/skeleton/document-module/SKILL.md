---
name: document-module
description: Write or update documentation for one code module from the code itself, then fact-check it against the code. Use when the user runs /document-module with a file or directory, or when ticket-to-pr asks to refresh docs for changed files.
argument-hint: "<file or directory>"
---

# Document module

Goal: <what exists at the end, where it is saved, and what this skill never does>

## 1. Research (how it works today)

<What is read, by whom, in which context? Where is the doc saved? What must every header and every claim look like? What is forbidden in the doc?>

## 2. Terms and decisions

<Which skill updates GLOSSARY.md and docs/adr/? When is an ADR worth writing? What do you ask the user?>

## 3. Fact-check (fresh context)

<Who checks, with what input? What verdicts? What happens to a claim that is not verified? What is kept in the doc?>

## Update mode

<When called on changed files only: what changes, what stays?>

## Final report

<What does the user see?>

## Gotchas

- Read-only on code: this skill never edits source files.
- C++: name units (bytes, records, ms) and integer widths; `long` is 32-bit on Windows.

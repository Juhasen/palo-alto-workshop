# Issue tracker: Jira, read through the Claude connector

Tickets live in Jira. Specs and working notes live as local Markdown in this repository under `.scratch/`.

## When a skill says "fetch the ticket"

1. If the Claude Jira connector is available, read the ticket with it (summary, description, acceptance criteria, comments). Read only; never update Jira.
2. Otherwise, ask the user to paste the ticket text.
3. Either way, save it to `.scratch/<ticket-id>/ticket.md` and work from that file.

## When a skill says "publish to the issue tracker"

Write a file instead:

- Spec: `.scratch/<ticket-id>/spec.md`
- Sub-tickets: `.scratch/<ticket-id>/issues/<NN>-<slug>.md`, numbered from `01`, each with a `Blocked by:` line.
- PR description: `.scratch/<ticket-id>/pr.md`

## Never

- Call `gh`, `glab`, `curl`, `wget`, or any web API.
- Create labels, comments, or transitions in Jira.
- Reach another service except through the policy broker (TBD: how Claude reaches it).

# Repository Agent Rules

These rules capture the workflow for maintaining this LeetCode repository.

## Repository Layout

- Keep standalone solved problems in `problems/`.
- Group standalone problems by LeetCode contest rating bucket:
  - `0000-1199-newbie`
  - `1200-1399-pupil`
  - `1400-1599-specialist`
  - `1600-1899-expert`
  - `1900-2099-candidate-master`
  - `2100-2299-master`
  - `2300-2399-international-master`
  - `2400-2599-grandmaster`
  - `2600-2999-international-grandmaster`
  - `3000-3999-legendary-grandmaster`
  - `4000-plus-eponym`
  - `unrated`
- Keep contest submissions in `contests/<weekly|biweekly><number>/`.
- Do not recreate `goals/`; it was intentionally removed.
- Keep reusable snippets and notes in `codebook/`.

## README Rules

- README files must stay short.
- Do not use README files as storage for generated lists, summary tables, or problem tables.
- Generated lists, counts, and code previews belong in the `docs/` site.
- Curated external study links belong in root `resources.md`, not in folder READMEs.
- Folder READMEs may describe the folder and link to the site.
- Root `README.md` should only contain:
  - a short repo description,
  - links to the site, `resources.md`, and main folders,
  - commands.

## Maintenance Commands

Run commands from the repository root.

```bash
python -m scripts.cli update-problems
python -m scripts.cli update-contests
python -m scripts.cli update-codebook
python -m scripts.cli update-site
python -m scripts.cli all
```

- `update-problems` updates problem entry READMEs.
- `update-contests` updates contest entry READMEs.
- `update-codebook` updates the codebook entry README.
- `update-site` updates the generated GitHub Pages data in `docs/assets/data.js`.
- `all` runs problem, contest, codebook, and site updates.
- Rating data is fetched from `zerotrac/leetcode_problem_rating`.

## Website Rules

- The GitHub Pages app lives in `docs/`.
- Keep the site as a lightweight static table app; avoid adding frontend build tooling unless the user asks.
- For table UI-only site changes, edit `docs/index.html`, `docs/assets/app.js`, and `docs/assets/styles.css` directly.
- For full code view changes, keep `docs/code.html`, `docs/assets/code.js`, and `docs/assets/highlight.js` in sync with the table preview behavior.
- Put generated problem, contest, and codebook browsing views in the site rather than README tables.
- Regenerate site data with `python -m scripts.cli update-site` only when repository data changes.
- Preview locally with `python -m http.server 8000 -d docs`.

## Adding Problems

1. Add contest problems under the matching contest folder first.
2. Add standalone solved problems under `problems/<rating-bucket>/`.
3. If the correct rating bucket is unknown, run the scripts or check the rating source.
4. If the problem has no rating, place it under `problems/unrated/`.
5. Regenerate indexes with `python -m scripts.cli all`.

## Commit Rules

- Check `git status --short --branch` before staging.
- Keep commits separated by purpose:
  - script/tooling changes,
  - problem file moves or additions,
  - generated README/index changes,
  - site/docs changes.
- Split workflow documentation changes, such as `AGENTS.md`, from implementation commits unless the user explicitly wants a single housekeeping commit.
- Split generated outputs from the code changes that update the generator when that makes the review clearer.
- UI-only site changes in `docs/` may share one commit when they are part of the same visible polish pass.
- Do not use `git add -A` unless the whole worktree is intentionally in scope.
- Stage explicit paths when untracked or unrelated files exist.
- Do not commit local experiments, generated site files, or untracked work unless the user explicitly asks.
- Push only after confirming the commit split is clean.

## GitHub PR Flow

- Use the current work branch for follow-up fixes when a PR is already open for that branch.
- Check `git status --short --branch` and inspect the intended diff once before staging.
- Do not repeatedly run setup checks in the same publish workflow:
  - verify `gh --version` and `gh auth status` only once unless a command fails with an auth/tooling error,
  - verify the PR with `gh pr view` once after creating or updating it.
- Prefer explicit path staging; do not use `git add -A` unless the whole worktree is intentionally in scope.
- After committing, push the current branch with `git push -u origin <branch>` when tracking is missing, otherwise `git push` is enough.
- Always write a non-empty PR body with at least `Summary` and `Validation` sections.
- When using `gh pr create` or `gh pr edit` with a multiline body, write the body to a temporary Markdown file and pass `--body-file`; do not pass multiline Markdown as an inline PowerShell argument.
- If the GitHub connector returns `403 Resource not accessible by integration`, immediately use the authenticated `gh` fallback instead of retrying the connector.
- If a PR already exists, update that PR body instead of opening a duplicate PR.

## Branch Rules

- Keep `main` as the primary branch.
- Clean local and remote temporary branches when they are no longer needed.
- After a PR is closed by merging, whether with a merge commit or squash merge, immediately delete the PR branch locally and remotely.
- Do the cleanup in the same workflow after confirming `main` contains the merge result.
- Never delete `main` or `origin/main`.
- After remote branch cleanup, run `git fetch origin --prune`.

## Verification

Use the checks that fit the change:

```bash
python -m py_compile scripts/*.py
python -m scripts.cli all
node --check docs/assets/app.js
git diff --check
```

For rating bucket moves, verify every `.cpp` file is in the bucket implied by its rating.

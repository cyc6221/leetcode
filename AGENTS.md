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

- The root `README.md` must stay short.
- Do not put the full problem list on the homepage; it will eventually become too large.
- The full standalone problem list belongs in `problems/README.md`, so GitHub shows it when opening the `problems/` folder.
- Contest lists belong in `contests/README.md` and each contest folder README.
- Root `README.md` should only contain:
  - a short repo description,
  - links to `problems/` and `contests/`,
  - commands,
  - summary counts.

## Maintenance Commands

Run commands from the repository root.

```bash
python -m scripts.cli update-problems
python -m scripts.cli update-contests
python -m scripts.cli update-site
python -m scripts.cli all
```

- `update-problems` updates `problems/README.md` and the root `README.md`.
- `update-contests` updates contest READMEs and `contests/README.md`.
- `update-site` updates the generated GitHub Pages data in `docs/assets/data.js`.
- `all` runs problem, contest, and site updates.
- Rating data is fetched from `zerotrac/leetcode_problem_rating`.

## Website Rules

- The GitHub Pages app lives in `docs/`.
- Keep the site as a lightweight static table app; avoid adding frontend build tooling unless the user asks.
- For UI-only site changes, edit `docs/index.html`, `docs/assets/app.js`, and `docs/assets/styles.css` directly.
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
- Do not use `git add -A` unless the whole worktree is intentionally in scope.
- Stage explicit paths when untracked or unrelated files exist.
- Do not commit local experiments, generated site files, or untracked work unless the user explicitly asks.
- Push only after confirming the commit split is clean.

## Branch Rules

- Keep `main` as the primary branch.
- Clean local and remote temporary branches when they are no longer needed.
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

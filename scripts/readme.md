# CLI Usage

This project includes Python scripts to maintain short README entry points and generated site data.

## Commands

### Migrate legacy goals

Moves `goals/**/*.cpp` into `problems/<rating-range>/` and removes `goals/`.

```bash
python -m scripts.cli migrate-goals
```

### Update problem README entry points

Updates the root `README.md` and `problems/README.md` without embedding generated tables.

```bash
python -m scripts.cli update-problems
```

### Update contest README entry points

Updates every contest README and `contests/README.md` without embedding generated tables.

```bash
python -m scripts.cli update-contests
```

### Update codebook README entry point

Updates `codebook/README.md` without embedding a generated snippet list.

```bash
python -m scripts.cli update-codebook
```

### Update static site

Updates the generated data used by the GitHub Pages app in `docs/`.

```bash
python -m scripts.cli update-site
```

### Update all generated files

```bash
python -m scripts.cli all
```

## Notes

* Run commands from the repository root.
* Generated lists, counts, and code previews live in the GitHub Pages site under `docs/`.
* Rating data comes from `zerotrac/leetcode_problem_rating`.

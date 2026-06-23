# CLI Usage

This project includes Python scripts to maintain README indexes.

## Commands

### Migrate legacy goals

Moves `goals/**/*.cpp` into `problems/<rating-range>/` and removes `goals/`.

```bash
python -m scripts.cli migrate-goals
```

### Update problem indexes

Updates `problems/README.md` and the root `README.md`.

```bash
python -m scripts.cli update-problems
```

### Update contest indexes

Updates every contest README and `contests/README.md`.

```bash
python -m scripts.cli update-contests
```

### Update all indexes

```bash
python -m scripts.cli all
```

## Notes

* Run commands from the repository root.
* Rating data comes from `zerotrac/leetcode_problem_rating`.

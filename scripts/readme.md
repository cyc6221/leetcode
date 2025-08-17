# CLI Usage

This project includes Python scripts to maintain and update README files.

## Commands

### Update a single goal README
Updates the `goals/<goal>/README.md` blocks (Progress / Summary / Table).

```bash
python -m scripts.cli update goal-2
python -m scripts.cli update latest
```

### Sync to root README

Copies the specified goal (default: latest) README content to the root `README.md`.

```bash
python -m scripts.cli sync
python -m scripts.cli sync goal-1
```

### Update + Sync (most common)

Updates the latest goal README and syncs it to the root README.

```bash
python -m scripts.cli all
```

---

## Notes

* Run commands from the **repository root**.
* `latest` always points to the most recent goal folder.
* Recommended default: `python -m scripts.cli all`
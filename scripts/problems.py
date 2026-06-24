import filecmp
import shutil
from pathlib import Path

from .generator import extract_info
from .paths import PROBLEMS_DIR, ROOT_DIR
from .ratings import RATING_BUCKETS, UNRATED_BUCKET, rating_bucket_slug, ratings_map

REPO_ROOT = Path(ROOT_DIR)
PROBLEMS_ROOT = Path(PROBLEMS_DIR)
LEGACY_GOALS_ROOT = REPO_ROOT / "goals"

SITE_URL = "https://cyc6221.github.io/leetcode/"


def ensure_problem_dirs() -> None:
    PROBLEMS_ROOT.mkdir(exist_ok=True)
    for slug, *_ in [*RATING_BUCKETS, UNRATED_BUCKET]:
        (PROBLEMS_ROOT / slug).mkdir(exist_ok=True)


def migrate_goals_to_problems() -> int:
    if not LEGACY_GOALS_ROOT.exists():
        print("No legacy goals directory found.")
        ensure_problem_dirs()
        return 0

    ensure_problem_dirs()
    rating_by_id = ratings_map()
    moved = 0

    for source in sorted(LEGACY_GOALS_ROOT.rglob("*.cpp")):
        qid, _, _ = extract_info(source.name)
        if not qid:
            continue

        rating = rating_by_id.get(int(qid))
        bucket = rating_bucket_slug(rating)
        target = PROBLEMS_ROOT / bucket / source.name

        if target.exists():
            if not filecmp.cmp(source, target, shallow=False):
                raise FileExistsError(f"Refusing to overwrite different file: {target}")
            source.unlink()
        else:
            target.parent.mkdir(parents=True, exist_ok=True)
            shutil.move(str(source), str(target))
            moved += 1

    shutil.rmtree(LEGACY_GOALS_ROOT)
    print(f"Migrated {moved} files from goals/ to problems/.")
    return moved


def _problems_readme_template() -> str:
    return "\n".join(
        [
            "# LeetCode Problems",
            "",
            "Standalone solved problems are grouped by LeetCode contest rating buckets.",
            "",
            f"Browse, search, sort, and preview code on the site: {SITE_URL}#/problems",
            "",
            "The generated table that used to live here has moved to the site.",
            "",
        ]
    )


def update_problems_readme() -> None:
    ensure_problem_dirs()
    readme_path = PROBLEMS_ROOT / "README.md"
    readme_path.write_text(_problems_readme_template(), encoding="utf-8")
    print(f"Updated {readme_path}")


def sync_root_readme() -> None:
    content = "\n".join(
        [
            "# LeetCode Solutions in C++",
            "",
            "Personal LeetCode solutions written in C++.",
            "",
            "## Structure",
            "",
            "- `problems/`: standalone solutions grouped by rating range.",
            "- `contests/`: contest archive grouped by weekly or biweekly contest.",
            "- `codebook/`: reusable algorithm notes and snippets.",
            "",
            "## Browse",
            "",
            f"- [Interactive site]({SITE_URL})",
            "- [Problem folders](./problems/)",
            "- [Contest folders](./contests/)",
            "- [Codebook](./codebook/)",
            "- [Study resources](./resources.md)",
            "",
            "## Commands",
            "",
            "```bash",
            "python -m scripts.cli all",
            "python -m scripts.cli update-problems",
            "python -m scripts.cli update-contests",
            "python -m scripts.cli update-codebook",
            "python -m scripts.cli update-site",
            "```",
            "",
        ]
    )
    root_readme = REPO_ROOT / "README.md"
    root_readme.write_text(content, encoding="utf-8")
    print(f"Updated {root_readme}")


def update_problem_docs() -> None:
    update_problems_readme()
    sync_root_readme()

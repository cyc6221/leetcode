import re
from pathlib import Path

from .paths import CONTESTS_DIR

SITE_URL = "https://cyc6221.github.io/leetcode/"


def _is_contest_dir(name: str) -> bool:
    lowered = name.lower()
    return lowered.startswith("weekly") or lowered.startswith("biweekly")


def _count_cpp_files(contest_dir: Path) -> int:
    return sum(1 for path in contest_dir.glob("*.cpp") if path.is_file())


def _contest_url(dir_name: str) -> str | None:
    name = dir_name.lower()
    match = re.match(r"^(weekly|biweekly)\D*?(\d+)$", name)
    if not match:
        return None

    contest_type, number = match.group(1), match.group(2)
    if contest_type == "weekly":
        return f"https://leetcode.com/contest/weekly-contest-{number}/"
    return f"https://leetcode.com/contest/biweekly-contest-{number}/"


def update_index_readme(contest_root: Path) -> int:
    total_count = sum(
        _count_cpp_files(path)
        for path in contest_root.iterdir()
        if path.is_dir() and _is_contest_dir(path.name)
    )
    lines = [
        "# LeetCode Contests",
        "",
        "Contest submissions are grouped by weekly and biweekly contest folders.",
        "",
        f"Browse, search, sort, and preview contest code on the site: {SITE_URL}#/contests",
        "",
        f"Total C++ files tracked: {total_count}",
        "",
        "The generated contest tables that used to live here have moved to the site.",
        "",
    ]

    (contest_root / "README.md").write_text("\n".join(lines), encoding="utf-8")
    return total_count


def _contest_readme_content(contest: str) -> str:
    lines = [
        f"# {contest}",
        "",
        "Contest solution files live in this folder.",
        "",
        f"Browse this contest on the site: {SITE_URL}#/contests",
    ]
    leetcode_url = _contest_url(contest)
    if leetcode_url:
        lines.extend(["", f"LeetCode contest page: {leetcode_url}"])
    lines.extend(["", "The generated problem table that used to live here has moved to the site.", ""])
    return "\n".join(lines)


def update_all_contests() -> None:
    contest_root = Path(CONTESTS_DIR)
    if not contest_root.exists():
        print(f"{CONTESTS_DIR} does not exist.")
        return

    contest_dirs = sorted(
        [path for path in contest_root.iterdir() if path.is_dir() and _is_contest_dir(path.name)],
        key=lambda path: path.name.lower(),
    )

    for contest_dir in contest_dirs:
        contest = contest_dir.name
        readme_path = contest_dir / "README.md"
        readme_path.write_text(_contest_readme_content(contest), encoding="utf-8")
        print(f"Updated {readme_path}")

    update_index_readme(contest_root)
    print(f"Updated {contest_root / 'README.md'}")

import re
from pathlib import Path

from .blocks import replace_block
from .generator import generate_table_all_contest, generate_table_contest
from .paths import CONTESTS_DIR, GITHUB_CONTESTS_BASE


def _is_contest_dir(name: str) -> bool:
    lowered = name.lower()
    return lowered.startswith("weekly") or lowered.startswith("biweekly")


def _count_cpp_files(contest_dir: Path) -> int:
    return sum(1 for path in contest_dir.glob("*.cpp") if path.is_file())


def _list_contests(contest_root: Path) -> dict[str, list[Path]]:
    contests = {"weekly": [], "biweekly": []}
    if not contest_root.exists():
        return contests

    for directory in sorted(path for path in contest_root.iterdir() if path.is_dir()):
        name = directory.name.lower()
        if name.startswith("weekly"):
            contests["weekly"].append(directory)
        elif name.startswith("biweekly"):
            contests["biweekly"].append(directory)
    return contests


def _contest_link_pair(dir_name: str) -> tuple[str | None, str | None]:
    name = dir_name.lower()
    match = re.match(r"^(weekly|biweekly)\D*?(\d+)$", name)
    if not match:
        return None, None

    contest_type, number = match.group(1), match.group(2)
    if contest_type == "weekly":
        leetcode_url = f"https://leetcode.com/contest/weekly-contest-{number}/"
    else:
        leetcode_url = f"https://leetcode.com/contest/biweekly-contest-{number}/"
    github_url = f"{GITHUB_CONTESTS_BASE}/{dir_name}"
    return leetcode_url, github_url


def update_index_readme(contest_root: Path) -> int:
    groups = _list_contests(contest_root)
    lines = ["# LeetCode Contests (C++)", ""]
    total_count = 0

    for group_name in ("weekly", "biweekly"):
        contests = groups.get(group_name, [])
        if not contests:
            continue

        lines.extend(
            [
                f"## {group_name.capitalize()}",
                "",
                "| Contest | LeetCode | GitHub | C++ Files |",
                "|:-------:|:--------:|:------:|:---------:|",
            ]
        )
        for directory in contests:
            count = _count_cpp_files(directory)
            total_count += count
            leetcode_url, github_url = _contest_link_pair(directory.name)
            leetcode_link = f"[Link]({leetcode_url})" if leetcode_url else ""
            github_link = f"[Repo]({github_url})" if github_url else f"[Repo]({GITHUB_CONTESTS_BASE}/{directory.name})"
            lines.append(f"| {directory.name} | {leetcode_link} | {github_link} | {count} |")
        lines.append("")

    lines.extend(
        [
            "## Note",
            "",
            f"**Total C++ files tracked:** {total_count}",
            "",
            generate_table_all_contest(),
            "",
        ]
    )

    (contest_root / "README.md").write_text("\n".join(lines), encoding="utf-8")
    return total_count


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
        table = generate_table_contest(contest)
        readme_path = contest_dir / "README.md"

        if readme_path.exists():
            content = readme_path.read_text(encoding="utf-8")
            content = replace_block(content, "<!-- LEETCODE_TABLE_START -->", "<!-- LEETCODE_TABLE_END -->", table)
        else:
            content = "\n".join(
                [
                    f"# {contest}",
                    "",
                    "<!-- LEETCODE_TABLE_START -->",
                    table,
                    "<!-- LEETCODE_TABLE_END -->",
                    "",
                ]
            )
        readme_path.write_text(content, encoding="utf-8")
        print(f"Updated {readme_path}")

    update_index_readme(contest_root)
    print(f"Updated {contest_root / 'README.md'}")

import os
import re
from pathlib import Path

from .paths import CONTESTS_DIR, GITHUB_CONTESTS_BASE
from .generator import generate_table_contest
from .blocks import replace_block


def _is_contest_dir(name: str) -> bool:
    """只接受 weekly* / biweekly* 的直屬子資料夾名稱。"""
    n = name.lower()
    return n.startswith("weekly") or n.startswith("biweekly")


def _count_cpp_files(contest_dir: Path) -> int:
    """直接數 .cpp 檔數量"""
    return sum(1 for p in contest_dir.rglob("*.cpp") if p.is_file())


def _list_contests(contest_root: Path):
    """
    掃描 contest/ 下的直屬子資料夾，僅列出 weekly*/biweekly*。
    """
    contests = {"weekly": [], "biweekly": []}
    if not contest_root.exists():
        return contests

    for d in sorted(p for p in contest_root.iterdir() if p.is_dir()):
        name = d.name.lower()
        if name.startswith("weekly"):
            contests["weekly"].append(d)
        elif name.startswith("biweekly"):
            contests["biweekly"].append(d)
    return contests


def _contest_link_pair(dir_name: str):
    name = dir_name.lower()
    m = re.match(r'^(weekly|biweekly)\D*?(\d+)$', name)
    if not m:
        return None, None
    grp, num = m.group(1), m.group(2)
    if grp == "weekly":
        lc = f"https://leetcode.com/contest/weekly-contest-{num}/"
    else:
        lc = f"https://leetcode.com/contest/biweekly-contest-{num}/"
    gh = f"{GITHUB_CONTESTS_BASE}/{dir_name}"
    return lc, gh

def update_index_readme(contest_root: Path):
    groups = _list_contests(contest_root)
    md = ["# LeetCode Contests (C++)\n"]
    total_cnt = 0

    for grp in ("weekly", "biweekly"):
        contests = groups.get(grp, [])
        if not contests:
            continue
        md.append(f"## {grp.capitalize()}\n")
        md.append("| Contest | LeetCode | GitHub | C++ Files |")
        md.append("|:-------:|:--------:|:------:|:---------:|")
        for d in contests:
            cnt = _count_cpp_files(d)
            total_cnt += cnt

            # 相對於 contest/ 的資料夾連結（原本的本地連結）
            # rel = "./" + d.as_posix()

            # 產生 LeetCode & GitHub 連結
            lc_url, gh_url = _contest_link_pair(d.name)
            lc_link = f"[Link]({lc_url})" if lc_url else ""
            gh_link = f"[Repo]({gh_url})" if gh_url else f"[Repo]({GITHUB_CONTESTS_BASE}/{d.name})"

            # md.append(f"| [{d.name}]({rel}) | {lc_link} | {gh_link} | {cnt} |")
            md.append(f"| {d.name} | {lc_link} | {gh_link} | {cnt} |")
        md.append("")

    md.append(f"## Note\n")
    md.append(f"**Total C++ files tracked:** {total_cnt}\n")
    (contest_root / "README.md").write_text("\n".join(md), encoding="utf-8")
    return total_cnt


def update_all_contests():
    root = Path(CONTESTS_DIR)
    if not root.exists():
        print(f"⚠️ {CONTESTS_DIR} 不存在，略過。")
        return

    # 只處理第一層 weekly*/biweekly* 目錄
    contest_dirs = sorted(
        [p for p in root.iterdir() if p.is_dir() and _is_contest_dir(p.name)],
        key=lambda p: p.name.lower()
    )

    for contest_dir in contest_dirs:
        contest = contest_dir.name
        table = generate_table_contest(contest)

        contest_readme = contest_dir / "README.md"
        if contest_readme.exists():
            content = contest_readme.read_text(encoding="utf-8")
            content = replace_block(
                content,
                "<!-- LEETCODE_TABLE_START -->",
                "<!-- LEETCODE_TABLE_END -->",
                table
            )
            contest_readme.write_text(content, encoding="utf-8")
            print(f"✅ Updated {contest_readme}")
        else:
            # 沒有 README.md 直接新建
            skeleton = (
                f"# {contest}\n\n"
                f"<!-- LEETCODE_TABLE_START -->\n"
                f"{table}\n"
                f"<!-- LEETCODE_TABLE_END -->\n"
            )
            contest_readme.write_text(skeleton, encoding="utf-8")
            print(f"🆕 Created {contest_readme}")

    # 更新 contest/README.md 總索引
    update_index_readme(root)
    print(f"📚 Updated {root / 'README.md'}")

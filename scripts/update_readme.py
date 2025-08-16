import sys
import os
import re
import argparse
import pandas as pd
import csv
import io
import urllib.request

ROOT_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
GOALS_DIR = os.path.join(ROOT_DIR, "goals")
GOAL_PATTERN = re.compile(r"^goal(\d+)$")

LEVEL_MAP = {
    'EASY': 'Easy🟢',
    'MEDIUM': 'Med🟡',
    'HARD': 'Hard🔴'
}

# Extract ID and kebab-case title
def extract_info(filename):
    match = re.match(r"(\d+)\.([a-z0-9\-]+)\.cpp", filename)
    if match:
        qid = match.group(1)
        kebab_title = match.group(2)
        title_display = kebab_title.replace('-', ' ').title()
        return qid, title_display, kebab_title
    return None, None, None

##################################################################

RATINGS_URL = "https://raw.githubusercontent.com/zerotrac/leetcode_problem_rating/main/ratings.txt"

def get_ratings_map(url: str = RATINGS_URL) -> dict[int, float]:
    """抓取 ratings.txt，回傳 {problem_id: rating} 對照表（標準庫實作）。"""
    with urllib.request.urlopen(url) as resp:
        text = resp.read().decode("utf-8", errors="replace")

    reader = csv.DictReader(io.StringIO(text), delimiter="\t")
    if not reader.fieldnames:
        raise ValueError("ratings.txt 解析不到表頭欄位")

    lower = {c.lower(): c for c in reader.fieldnames}
    id_col = next((lower.get(k) for k in ("id", "problem id", "problem_id", "problemid")), None)
    rating_col = next((lower.get(k) for k in ("rating", "difficulty", "difficulty_rating")), None)
    if not id_col or not rating_col:
        raise ValueError(f"找不到 ID 或 Rating 欄位，表頭為：{reader.fieldnames}")

    out: dict[int, float] = {}
    for row in reader:
        id_raw = (row.get(id_col) or "").strip()
        rating_raw = (row.get(rating_col) or "").strip()
        try:
            pid = int(id_raw)
            r = float(rating_raw)
        except ValueError:
            continue
        # 若同一 ID 出現多筆，取較大的 rating（可依你需求改成首次或均值）
        out[pid] = max(out.get(pid, float("-inf")), r)
    return out

# 簡單快取，避免每次 generate_table 都去抓網路
_RATINGS_CACHE: dict[int, float] | None = None
def ratings_map() -> dict[int, float]:
    global _RATINGS_CACHE
    if _RATINGS_CACHE is None:
        _RATINGS_CACHE = get_ratings_map()
    return _RATINGS_CACHE

def rating_to_emoji(rating):
    if rating >= 4000:
        return "⚫🔴"
    elif rating >= 3000:
        return "🔴⚫"
    elif rating >= 2600:
        return "🔴🔴"
    elif rating >= 2400:
        return "🔴"
    elif rating >= 2300:
        return "🟠🟠"
    elif rating >= 2100:
        return "🟠"
    elif rating >= 1900:
        return "🟣"
    elif rating >= 1600:
        return "🔵"
    elif rating >= 1400:
        return "🔷" 
    elif rating >= 1200:
        return "🟢"
    else:
        return "⚪"

def _fmt_rating(x: float | None) -> str:
    if x is None:
        return "-"
    emoji = rating_to_emoji(x)
    if abs(x - int(x)) < 1e-9:
        return f"{int(x)}<br>{emoji}"
    else:
        return f"{x:.1f}<br>{emoji}"

##################################################################

from pathlib import Path
REPO_ROOT = Path(__file__).resolve().parents[1]  # repo 根目錄（scripts 的上一層）

# Generate the markdown table
def generate_table(goal: str) -> str:
    base_path = os.path.join(GOALS_DIR, goal)

    table = "## Completed Problem List\n\n"
    table += "| ID | Title | Diff | Rating | Link | Code |\n"
    table += "|:--:|-------|:----:|:------:|:----:|:----:|\n"

    entries = []
    rmap = ratings_map()

    for folder in ['EASY', 'MEDIUM', 'HARD']:
        folder_path = os.path.join(base_path, folder)
        if not os.path.exists(folder_path):
            continue
        for file in os.listdir(folder_path):
            if file.endswith(".cpp"):
                qid, title, kebab = extract_info(file)
                if qid:
                    pid = int(qid)
                    difficulty = LEVEL_MAP[folder]
                    # code_path = f"./{folder_path}/{file}"
                    p = Path(folder_path) / file
                    rel = Path(os.path.relpath(p.resolve(), REPO_ROOT))
                    code_path = "./" + rel.as_posix()   # 例如 ./goals/goal2/EASY/xxx.cpp
                    lc_url = f"https://leetcode.com/problems/{kebab}/"
                    rating_val = rmap.get(pid)
                    entries.append((pid, qid, title, difficulty, rating_val, lc_url, code_path))

    # Sort by numeric ID
    entries.sort()

    for _, qid, title, difficulty, rating_val, lc_url, code_path in entries:
        code_link = f"[View]({code_path})"
        lc_link = f"[Link]({lc_url})"
        table += f"| {qid} | {title} | {difficulty} | {_fmt_rating(rating_val)} | {lc_link} | {code_link} |\n"

    return table

def generate_summary_table(goal: str) -> str:
    base_path = os.path.join(GOALS_DIR, goal)
    summary = {"EASY": 0, "MEDIUM": 0, "HARD": 0}
    total = 0

    for folder in summary:
        folder_path = os.path.join(base_path, folder)
        if not os.path.exists(folder_path):
            continue
        for file in os.listdir(folder_path):
            if file.endswith(".cpp"):
                summary[folder] += 1
                total += 1

    table = "## Problem Count Summary\n\n"
    table += "| Difficulty | Count |\n"
    table += "|------------|-------|\n"
    for k in ["EASY", "MEDIUM", "HARD"]:
        table += f"| {LEVEL_MAP[k]} | {summary[k]} |\n"
    table += f"| **Total** | {total} |\n"
    return table

########################################################################

DIFFICULTY_TOTAL = {
    "EASY": 30,
    "MEDIUM": 20,
    "HARD": 10
}

def progress_bar(percentage, width=60):
    filled = int(percentage * width)
    return "[" + "█" * filled + "░" * (width - filled) + f"] {int(percentage * 100)}%"

def generate_progress_block(goal: str) -> str:
    base_path = os.path.join(GOALS_DIR, goal)
    counts = {"EASY": 0, "MEDIUM": 0, "HARD": 0}
    for level in counts:
        folder_path = os.path.join(base_path, level)
        if os.path.exists(folder_path):
            for file in os.listdir(folder_path):
                if file.endswith(".cpp"):
                    counts[level] += 1

    block = "## Difficulty Progress\n\n"
    for level in ["EASY", "MEDIUM", "HARD"]:
        done = counts[level]
        total = DIFFICULTY_TOTAL[level]
        pct = done / total if total else 0
        bar = progress_bar(pct)
        block += f"**{LEVEL_MAP[level]}**: {done} / {total}\n\n{bar}\n\n"
    return block.strip()

################################################################

# === 公用：替換 README 中標記區塊 ===
def replace_block(content: str, start_tag: str, end_tag: str, new_block: str) -> str:
    return re.sub(
        f"{re.escape(start_tag)}.*?{re.escape(end_tag)}",
        f"{start_tag}\n{new_block}\n{end_tag}",
        content,
        flags=re.DOTALL
    )

# === 自動找最新 goal-X ===
GOAL_DIR = "goals"
GOAL_PATTERN = re.compile(r"^goal(\d+)$")

def find_latest_goal(goals_dir: str = GOAL_DIR) -> str:
    if not os.path.isdir(goals_dir):
        raise FileNotFoundError(f"'{goals_dir}' 目錄不存在。")
    latest_num = -1
    latest_name = None
    for name in os.listdir(goals_dir):
        m = GOAL_PATTERN.match(name)
        if m and os.path.isdir(os.path.join(goals_dir, name)):
            num = int(m.group(1))
            if num > latest_num:
                latest_num = num
                latest_name = name
    if latest_name is None:
        raise RuntimeError(f"在 '{goals_dir}' 下找不到任何 goal-X 目錄。")
    return latest_name


# def resolve_goal(arg_goal: str) -> str:
#     if arg_goal.lower() == "latest":
#         return find_latest_goal()
#     path = os.path.join(GOAL_DIR, arg_goal)
#     if not os.path.isdir(path):
#         raise FileNotFoundError(f"找不到目標目錄：{path}")
#     return arg_goal

################################################################

# Replace the LEETCODE_TABLE block in README.md
# def update_readme():
#     start_table_tag = "<!-- LEETCODE_TABLE_START -->"
#     end_table_tag = "<!-- LEETCODE_TABLE_END -->"

#     start_summary_tag = "<!-- LEETCODE_SUMMARY_START -->"
#     end_summary_tag = "<!-- LEETCODE_SUMMARY_END -->"

#     progress_start = "<!-- LEETCODE_PROGRESS_START -->"
#     progress_end = "<!-- LEETCODE_PROGRESS_END -->"

#     with open("README.md", "r", encoding="utf-8") as f:
#         content = f.read()

#     table = generate_table()
#     summary = generate_summary_table()
#     progress_block = generate_progress_block()

#     content = re.sub(
#         f"{start_table_tag}.*?{end_table_tag}",
#         f"{start_table_tag}\n{table}\n{end_table_tag}",
#         content,
#         flags=re.DOTALL
#     )

#     content = re.sub(
#         f"{start_summary_tag}.*?{end_summary_tag}",
#         f"{start_summary_tag}\n{summary}\n{end_summary_tag}",
#         content,
#         flags=re.DOTALL
#     )

#     content = re.sub(
#         f"{progress_start}.*?{progress_end}",
#         f"{progress_start}\n{progress_block}\n{progress_end}",
#         content,
#         flags=re.DOTALL
#     )

#     with open("README.md", "w", encoding="utf-8") as f:
#         f.write(content)

#     print("README.md updated.")

################################################################

# === 替換區塊 ===
def replace_block(content: str, start_tag: str, end_tag: str, new_block: str) -> str:
    pattern = f"{re.escape(start_tag)}.*?{re.escape(end_tag)}"
    return re.sub(
        pattern,
        lambda m: f"{start_tag}\n{new_block}\n{end_tag}",
        content,
        flags=re.DOTALL
    )


# === 找最新 goal ===
def find_latest_goal() -> str:
    latest_num = -1
    latest_name = None
    for name in os.listdir(GOALS_DIR):
        m = GOAL_PATTERN.match(name)
        if m and os.path.isdir(os.path.join(GOALS_DIR, name)):
            num = int(m.group(1))
            if num > latest_num:
                latest_num = num
                latest_name = name
    if latest_name is None:
        raise RuntimeError("⚠️ 沒找到任何 goals/goal-X 目錄")
    return latest_name

# === 功能 1：更新單一 goal 的 README ===
def update_goal_readme(goal: str):
    table   = generate_table(goal)
    summary = generate_summary_table(goal)
    progress_block = generate_progress_block(goal)

    goal_readme = os.path.join(GOALS_DIR, goal, "README.md")
    if os.path.exists(goal_readme):
        with open(goal_readme, "r", encoding="utf-8") as f:
            content = f.read()
        content = replace_block(content, "<!-- LEETCODE_TABLE_START -->",   "<!-- LEETCODE_TABLE_END -->",   table)
        content = replace_block(content, "<!-- LEETCODE_SUMMARY_START -->", "<!-- LEETCODE_SUMMARY_END -->", summary)
        content = replace_block(content, "<!-- LEETCODE_PROGRESS_START -->","<!-- LEETCODE_PROGRESS_END -->",progress_block)
        with open(goal_readme, "w", encoding="utf-8") as f:
            f.write(content)
        print(f"✅ Updated {goal_readme}")
    else:
        print(f"⚠️ {goal_readme} 不存在，略過。")

# === 功能 2：同步到 root ===
def sync_root_readme(goal: str):
    src = os.path.join(GOALS_DIR, goal, "README.md")
    dst = os.path.join(ROOT_DIR, "README.md")
    if not os.path.exists(src):
        raise FileNotFoundError(f"{src} 不存在")
    with open(src, "r", encoding="utf-8") as f:
        content = f.read()
    with open(dst, "w", encoding="utf-8") as f:
        f.write(content)
    print(f"✅ Copied {src} → {dst}")

# === 功能 3：all (update + sync) ===
def update_and_sync_latest():
    latest = find_latest_goal()
    print(f"🌟 Latest goal: {latest}")
    update_goal_readme(latest)
    sync_root_readme(latest)

# === CLI ===
def main():
    parser = argparse.ArgumentParser(
        description="Update goal README and optionally sync latest goal README to root.",
        epilog=(
            "範例：\n"
            "  python scripts/update_readme.py update goal-2   # 更新 goals/goal-2/README.md\n"
            "  python scripts/update_readme.py sync            # 複製 latest goal 的 README 到 root\n"
            "  python scripts/update_readme.py sync goal-1     # 指定 goal-1 複製到 root\n"
            "  python scripts/update_readme.py all             # 更新 latest goal 並複製到 root\n"
        ),
        formatter_class=argparse.RawTextHelpFormatter
    )
    subparsers = parser.add_subparsers(dest="command", required=True)

    p1 = subparsers.add_parser("update", help="更新指定 goal 的 README")
    p1.add_argument("goal", help="要更新的 goal (例如 goal-1, goal-2, latest)")

    p2 = subparsers.add_parser("sync", help="把指定 goal 的 README 複製到 root")
    p2.add_argument("goal", nargs="?", default="latest", help="要同步的 goal (預設 latest)")

    subparsers.add_parser("all", help="更新 latest goal 的 README，並複製到 root")

    args = parser.parse_args()

    if args.command == "update":
        goal = args.goal if args.goal != "latest" else find_latest_goal()
        update_goal_readme(goal)
    elif args.command == "sync":
        goal = args.goal if args.goal != "latest" else find_latest_goal()
        sync_root_readme(goal)
    elif args.command == "all":
        update_and_sync_latest()

if __name__ == "__main__":
    main()


# # 更新單一 goal
# python scripts/update_readme.py update goal-2
# python scripts/update_readme.py update latest

# # 只複製到 root
# python scripts/update_readme.py sync
# python scripts/update_readme.py sync goal-1

# # 一次更新 + 複製（最常用）
# python scripts/update_readme.py all

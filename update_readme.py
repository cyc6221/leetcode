import os
import re
import pandas as pd
import csv
import io
import urllib.request

LEVEL_MAP = {
    'EASY': 'Easy 🟢',
    'MEDIUM': 'Med 🟡',
    'HARD': 'Hard 🔴'
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

# Generate the markdown table
def generate_table():
    table = "## Completed Problem List\n\n"
    table += "| ID | Title | Diff | Rating | Link | Code |\n"
    table += "|:--:|-------|:----:|:------:|:----:|:----:|\n"

    entries = []
    rmap = ratings_map()

    for folder in ['EASY', 'MEDIUM', 'HARD']:
        if not os.path.exists(folder):
            continue
        for file in os.listdir(folder):
            if file.endswith(".cpp"):
                qid, title, kebab = extract_info(file)
                if qid:
                    pid = int(qid)
                    difficulty = LEVEL_MAP[folder]
                    code_path = f"./{folder}/{file}"
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

def generate_summary_table():
    summary = {"EASY": 0, "MEDIUM": 0, "HARD": 0}
    total = 0

    for folder in summary:
        path = folder
        if not os.path.exists(path):
            continue
        for file in os.listdir(path):
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

def generate_progress_block():
    counts = {"EASY": 0, "MEDIUM": 0, "HARD": 0}
    for level in counts:
        path = level
        if os.path.exists(path):
            for file in os.listdir(path):
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

# Replace the LEETCODE_TABLE block in README.md
def update_readme():
    start_table_tag = "<!-- LEETCODE_TABLE_START -->"
    end_table_tag = "<!-- LEETCODE_TABLE_END -->"

    start_summary_tag = "<!-- LEETCODE_SUMMARY_START -->"
    end_summary_tag = "<!-- LEETCODE_SUMMARY_END -->"

    progress_start = "<!-- LEETCODE_PROGRESS_START -->"
    progress_end = "<!-- LEETCODE_PROGRESS_END -->"

    with open("README.md", "r", encoding="utf-8") as f:
        content = f.read()

    table = generate_table()
    summary = generate_summary_table()
    progress_block = generate_progress_block()

    content = re.sub(
        f"{start_table_tag}.*?{end_table_tag}",
        f"{start_table_tag}\n{table}\n{end_table_tag}",
        content,
        flags=re.DOTALL
    )

    content = re.sub(
        f"{start_summary_tag}.*?{end_summary_tag}",
        f"{start_summary_tag}\n{summary}\n{end_summary_tag}",
        content,
        flags=re.DOTALL
    )

    content = re.sub(
        f"{progress_start}.*?{progress_end}",
        f"{progress_start}\n{progress_block}\n{progress_end}",
        content,
        flags=re.DOTALL
    )

    with open("README.md", "w", encoding="utf-8") as f:
        f.write(content)

    print("README.md updated.")

if __name__ == "__main__":
    update_readme()

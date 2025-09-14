import os
import re
from pathlib import Path
from .paths import GOALS_DIR, CONTEST_DIR
from .ratings import ratings_map, _fmt_rating

REPO_ROOT = Path(__file__).resolve().parents[1]  # repo 根目錄（scripts 的上一層）

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

DIFFICULTY_TOTAL = {
    "EASY": 10,
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


### === CONTESTS === ###

def generate_table_contest(contest: str) -> str:
    contest_path = os.path.join(CONTEST_DIR, contest)

    table = "## Problem List\n\n"
    table += "| ID | Title | Rating | Link | Code |\n"
    table += "|:--:|-------|:------:|:----:|:----:|\n"

    entries = []
    rmap = ratings_map()

    for file in os.listdir(contest_path):
        if file.endswith(".cpp"):
            qid, title, kebab = extract_info(file)
            if qid:
                pid = int(qid)
                # code_path = f"./{folder_path}/{file}"
                p = Path(contest_path) / file
                rel = Path(os.path.relpath(p.resolve(), REPO_ROOT))
                code_path = "./" + rel.as_posix() 
                lc_url = f"https://leetcode.com/problems/{kebab}/"
                rating_val = rmap.get(pid)
                entries.append((pid, qid, title, rating_val, lc_url, code_path))

    # Sort by numeric ID
    entries.sort()

    for _, qid, title, rating_val, lc_url, code_path in entries:
        code_link = f"[View]({code_path})"
        lc_link = f"[Link]({lc_url})"
        table += f"| {qid} | {title} | {_fmt_rating(rating_val)} | {lc_link} | {code_link} |\n"

    return table

def generate_table_all_contest() -> str:
    table = "## Problem List\n\n"
    table += "| Contest | ID | Title | Rating | Link | Code |\n"
    table += "|:-------:|:--:|-------|:------:|:----:|:----:|\n"

    entries = []
    rmap = ratings_map()

    for folder in os.listdir(CONTEST_DIR):
        folder_path = os.path.join(CONTEST_DIR, folder)
        if not os.path.isdir(folder_path):
            continue
        for file in os.listdir(folder_path):
            if file.endswith(".cpp"):
                qid, title, kebab = extract_info(file)
                if qid:
                    pid = int(qid)
                    # code_path = f"./{folder_path}/{file}"
                    # p = Path(CONTEST_DIR) / file
                    p = Path(folder_path) / file
                    rel = Path(os.path.relpath(p.resolve(), CONTEST_DIR))
                    code_path = "./" + rel.as_posix() 
                    lc_url = f"https://leetcode.com/problems/{kebab}/"
                    rating_val = rmap.get(pid)

                    entries.append((pid, folder, qid, title, rating_val, lc_url, code_path))

    # Sort by numeric ID
    entries.sort()

    for _, contest, qid, title, rating_val, lc_url, code_path in entries:
        code_link = f"[View]({code_path})"
        lc_link = f"[Link]({lc_url})"
        table += f"| {contest} | {qid} | {title} | {_fmt_rating(rating_val)} | {lc_link} | {code_link} |\n"

    return table

import os
import re

LEVEL_MAP = {
    'EASY': 'Easy',
    'MEDIUM': 'Medium',
    'HARD': 'Hard'
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

# Generate the markdown table
def generate_table():
    table = "## Completed Problem List\n\n"
    table += "| ID | Title | Difficulty | LeetCode | Code |\n"
    table += "|----|-------|------------|----------|------|\n"

    entries = []

    for folder in ['EASY', 'MEDIUM', 'HARD']:
        if not os.path.exists(folder):
            continue
        for file in os.listdir(folder):
            if file.endswith(".cpp"):
                qid, title, kebab = extract_info(file)
                if qid:
                    difficulty = LEVEL_MAP[folder]
                    code_path = f"./{folder}/{file}"
                    lc_url = f"https://leetcode.com/problems/{kebab}/"
                    entries.append((int(qid), qid, title, difficulty, lc_url, code_path))

    # Sort by numeric ID
    entries.sort()

    for _, qid, title, difficulty, lc_url, code_path in entries:
        code_link = f"[View]({code_path})"
        lc_link = f"[Link]({lc_url})"
        table += f"| {qid} | {title} | {difficulty} | {lc_link} | {code_link} |\n"

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

def progress_bar(percentage, width=50):
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

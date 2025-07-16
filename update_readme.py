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
    table = "| ID | Title | Difficulty | LeetCode | Code |\n"
    table += "|----|-------|------------|----------|------|\n"

    for folder in ['EASY', 'MEDIUM', 'HARD']:
        if not os.path.exists(folder):
            continue
        for file in sorted(os.listdir(folder)):
            if file.endswith(".cpp"):
                qid, title, kebab = extract_info(file)
                if qid:
                    difficulty = LEVEL_MAP[folder]
                    code_path = f"./{folder}/{file}"
                    code_link = f"[View]({code_path})"
                    lc_url = f"https://leetcode.com/problems/{kebab}/"
                    lc_link = f"[Link]({lc_url})"
                    table += f"| {qid} | {title} | {difficulty} | {lc_link} | {code_link} |\n"
    return table

# Replace the LEETCODE_TABLE block in README.md
def update_readme():
    start_tag = "<!-- LEETCODE_TABLE_START -->"
    end_tag = "<!-- LEETCODE_TABLE_END -->"

    with open("README.md", "r", encoding="utf-8") as f:
        content = f.read()

    table = generate_table()
    new_content = re.sub(
        f"{start_tag}.*?{end_tag}",
        f"{start_tag}\n{table}\n{end_tag}",
        content,
        flags=re.DOTALL
    )

    with open("README.md", "w", encoding="utf-8") as f:
        f.write(new_content)

    print("✅ README.md updated!")

if __name__ == "__main__":
    update_readme()

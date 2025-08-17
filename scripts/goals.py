import os
from .paths import GOALS_DIR, GOAL_DIR, GOAL_PATTERN, ROOT_DIR
from .generator import generate_table, generate_summary_table, generate_progress_block
from .blocks import replace_block


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

# === function 1 ===
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

# === function 2 ===
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


# === function 3 ===
def update_and_sync_latest():
    latest = find_latest_goal()
    print(f"🌟 Latest goal: {latest}")
    update_goal_readme(latest)
    sync_root_readme(latest)

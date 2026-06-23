import os
import re

ROOT_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))

PROBLEM_DIR = "problems"
PROBLEMS_DIR = os.path.join(ROOT_DIR, PROBLEM_DIR)

CONTEST_DIR = "contests"
CONTESTS_DIR = os.path.join(ROOT_DIR, CONTEST_DIR)
CONTEST_PATTERN = re.compile(r"^(weekly|biweekly)\d+$")

GITHUB_PROBLEMS_BASE = "https://github.com/cyc6221/leetcode/tree/main/problems"
GITHUB_CONTESTS_BASE = "https://github.com/cyc6221/leetcode/tree/main/contests"

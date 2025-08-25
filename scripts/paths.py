import os
import re

ROOT_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))

GOAL_DIR = "goals"
GOALS_DIR = os.path.join(ROOT_DIR, "goals")
GOAL_PATTERN = re.compile(r"^goal(\d+)$")
# 
# GOAL_PATTERN = re.compile(r"^goal(\d+)$")

CONTEST_DIR = "contests"
CONTESTS_DIR = os.path.join(ROOT_DIR, "contests")
CONTEST_PATTERN = re.compile(r"^contest(\d+)$")
# 
# CONTEST_PATTERN = re.compile(r"^contest(\d+)$"


GITHUB_CONTESTS_BASE = "https://github.com/cyc6221/leetcode/tree/main/contests"

import os
import re

ROOT_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
GOALS_DIR = os.path.join(ROOT_DIR, "goals")
GOAL_PATTERN = re.compile(r"^goal(\d+)$")
GOAL_DIR = "goals"
GOAL_PATTERN = re.compile(r"^goal(\d+)$")

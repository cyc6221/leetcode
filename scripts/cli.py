import argparse
from .goals import find_latest_goal, update_goal_readme, sync_root_readme, update_and_sync_latest

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

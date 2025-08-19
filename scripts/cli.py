import argparse
from .goals import find_latest_goal, update_goal_readme, sync_root_readme, update_and_sync_latest


def main():
    parser = argparse.ArgumentParser(
        description="CLI to update goal READMEs and sync a goal README to the repository root.",
        epilog=(
            "Examples:\n"
            "  python -m scripts.cli update goal-2   # Update goals/goal-2/README.md\n"
            "  python -m scripts.cli update latest   # Update latest goal README\n"
            "  python -m scripts.cli sync            # Copy latest goal README to root README.md\n"
            "  python -m scripts.cli sync goal-1     # Copy goal-1 README to root README.md\n"
            "  python -m scripts.cli all             # Update latest goal and sync it to root\n"
        ),
        formatter_class=argparse.RawTextHelpFormatter,
    )
    subparsers = parser.add_subparsers(dest="command", required=True)

    # update
    p_update = subparsers.add_parser(
        "update",
        help="Update the README blocks (Progress/Summary/Table) for a specific goal.",
    )
    p_update.add_argument(
        "goal",
        help="Goal folder name (e.g., goal-1, goal-2) or 'latest'.",
    )

    # sync
    p_sync = subparsers.add_parser(
        "sync",
        help="Copy the specified goal (default: latest) README to the repository root README.md.",
    )
    p_sync.add_argument(
        "goal",
        nargs="?",
        default="latest",
        help="Goal folder name (e.g., goal-1, goal-2). Defaults to 'latest'.",
    )

    # all
    subparsers.add_parser(
        "all",
        help="Update the latest goal README and sync it to the root README.md.",
    )

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

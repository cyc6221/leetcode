import argparse

from .contests import update_all_contests
from .problems import migrate_goals_to_problems, update_problem_docs


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Maintain LeetCode solution indexes.",
        epilog=(
            "Examples:\n"
            "  python -m scripts.cli migrate-goals\n"
            "  python -m scripts.cli update-problems\n"
            "  python -m scripts.cli update-contests\n"
            "  python -m scripts.cli all\n"
        ),
        formatter_class=argparse.RawTextHelpFormatter,
    )
    subparsers = parser.add_subparsers(dest="command", required=True)

    subparsers.add_parser("migrate-goals", help="Move legacy goals/*.cpp files into problems/ rating buckets.")
    subparsers.add_parser("update-problems", help="Update problems/README.md and the root README.md.")
    subparsers.add_parser("update-contests", help="Update all contest README files and contests/README.md.")
    subparsers.add_parser("all", help="Update problem and contest README files.")

    args = parser.parse_args()

    if args.command == "migrate-goals":
        migrate_goals_to_problems()
        update_problem_docs()
    elif args.command == "update-problems":
        update_problem_docs()
    elif args.command == "update-contests":
        update_all_contests()
    elif args.command == "all":
        update_problem_docs()
        update_all_contests()


if __name__ == "__main__":
    main()

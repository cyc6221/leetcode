import argparse

from .codebook import update_codebook_readme
from .contests import update_all_contests
from .problems import migrate_goals_to_problems, update_problem_docs
from .site import update_site


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Maintain LeetCode solution entry points and site data.",
        epilog=(
            "Examples:\n"
            "  python -m scripts.cli migrate-goals\n"
            "  python -m scripts.cli update-problems\n"
            "  python -m scripts.cli update-contests\n"
            "  python -m scripts.cli update-codebook\n"
            "  python -m scripts.cli update-site\n"
            "  python -m scripts.cli all\n"
        ),
        formatter_class=argparse.RawTextHelpFormatter,
    )
    subparsers = parser.add_subparsers(dest="command", required=True)

    subparsers.add_parser("migrate-goals", help="Move legacy goals/*.cpp files into problems/ rating buckets.")
    subparsers.add_parser("update-problems", help="Update problem entry READMEs.")
    subparsers.add_parser("update-contests", help="Update contest entry READMEs.")
    subparsers.add_parser("update-codebook", help="Update codebook entry README.")
    subparsers.add_parser("update-site", help="Update the GitHub Pages static site data in docs/.")
    subparsers.add_parser("all", help="Update README entry points and static site files.")

    args = parser.parse_args()

    if args.command == "migrate-goals":
        migrate_goals_to_problems()
        update_problem_docs()
    elif args.command == "update-problems":
        update_problem_docs()
    elif args.command == "update-contests":
        update_all_contests()
    elif args.command == "update-codebook":
        update_codebook_readme()
    elif args.command == "update-site":
        update_site()
    elif args.command == "all":
        update_problem_docs()
        update_all_contests()
        update_codebook_readme()
        update_site()


if __name__ == "__main__":
    main()

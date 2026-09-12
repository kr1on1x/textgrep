import argparse
from pathlib import Path

def search(query, path, ignore_case=False, extension=None):
    matches = 0
    files_with_matches = 0

    if ignore_case:
        query = query.lower()

    for file in Path(path).rglob("*"):
        if not file.is_file():
            continue

        if extension and file.suffix != f".{extension}":
            continue

        try:
            text = file.read_text(errors="ignore")
        except OSError:
            continue

        found_in_file = False

        for line_number, line in enumerate(text.splitlines(), 1):
            search_line = line.lower() if ignore_case else line

            if query in search_line:
                print(f"{file}:{line_number}: {line}")
                matches += 1
                found_in_file = True

        if found_in_file:
            files_with_matches += 1

    return matches, files_with_matches


def main():
    parser = argparse = argparse.ArgumentParser(
        description="Search text recursively inside files."
    )

    parser.add_argument("query")
    parser.add_argument("path")

    parser.add_argument(
        "-i",
        "--ignore-case",
        action="store_true",
        help="ignore case when searching"
    )

    parser.add_argument(
        "--ext",
        help="search only files with this extension"
    )

    args = parser.parse_args()

    matches, files = search(
        args.query,
        args.path,
        args.ignore_case,
        args.ext
    )

    print()
    print(f"{matches} matches in {files} files")

if __name__ == "__main__":
    main()

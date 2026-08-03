import os

EXCLUDE_DIRS = {"build", ".git", "__pycache__", "node_modules"}
OUTPUT_FILE = "project_dump.txt"


def should_exclude(dirpath):
    parts = set(os.path.normpath(dirpath).split(os.sep))
    return bool(parts & EXCLUDE_DIRS)


def dump_project(root_dir, output_path):
    file_count = 0
    with open(output_path, "w", encoding="utf-8") as out:
        for dirpath, dirnames, filenames in os.walk(root_dir):
            # Prune excluded directories in-place so os.walk skips them
            dirnames[:] = [
                d for d in dirnames
                if d not in EXCLUDE_DIRS
            ]

            for filename in sorted(filenames):
                filepath = os.path.join(dirpath, filename)
                rel_path = os.path.relpath(filepath, root_dir)

                out.write(f"{'=' * 80}\n")
                out.write(f"FILE: {rel_path}\n")
                out.write(f"{'=' * 80}\n\n")

                try:
                    with open(filepath, "r", encoding="utf-8") as f:
                        content = f.read()
                    out.write(content)
                except UnicodeDecodeError:
                    out.write("[BINARY FILE - SKIPPED]\n")
                except Exception as e:
                    out.write(f"[ERROR READING FILE: {e}]\n")

                out.write("\n\n")
                file_count += 1

    print(f"Dumped {file_count} files to {output_path}")


if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.abspath(__file__))
    output = os.path.join(script_dir, OUTPUT_FILE)
    dump_project(script_dir, output)
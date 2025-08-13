#!/usr/bin/env python3
import os
import platform
import subprocess
import shutil

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
SYSTEM = platform.system()

def list_dependencies(file_path):
    try:
        if SYSTEM == "Darwin":
            if shutil.which("otool") is None:
                print("  (otool not found, skipping)")
                return
            output = subprocess.check_output(["otool", "-L", file_path], text=True)
        elif SYSTEM == "Linux":
            if shutil.which("ldd") is None:
                print("  (ldd not found, skipping)")
                return
            output = subprocess.check_output(["ldd", file_path], text=True)
        elif SYSTEM == "Windows":
            if shutil.which("dumpbin") is None:
                print("  (dumpbin not found, skipping)")
                return
            output = subprocess.check_output(["dumpbin", "/DEPENDENTS", file_path], text=True)
        else:
            print(f"Unsupported OS: {SYSTEM}")
            return
        print(output.strip())
    except Exception as e:
        print(f"  (Cannot analyze {file_path}: {e})")

def main():
    extensions = {
        "Darwin": ".dylib",
        "Linux": ".so",
        "Windows": ".dll"
    }

    ext = extensions.get(SYSTEM)
    if not ext:
        print(f"Unsupported OS: {SYSTEM}")
        return

    for root, dirs, files in os.walk(SCRIPT_DIR):
        for f in files:
            if f.lower().endswith(ext):
                full_path = os.path.join(root, f)
                print(f">>> {full_path}")
                list_dependencies(full_path)

if __name__ == "__main__":
    main()
    if SYSTEM == "Windows":
        try:
            input("Press Enter to exit...")
        except EOFError:
            pass

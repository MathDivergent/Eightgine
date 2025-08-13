#!/usr/bin/env python3
import os
import platform
import subprocess
import shutil

EXTENTIONS = {
    "Darwin": ".dylib",
    "Linux": ".so",
    "Windows": ".dll"
}

EXECUTABLES = {
    "Darwin": "EmptyProject",
    "Linux": "EmptyProject",
    "Windows": "EmptyProject.exe"
}

IGNORE_DIRS = [
    "Intermediate",
    ".idea"
]

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
SYSTEM = platform.system()

def list_dependencies(file_path):
    output = ""
    try:
        if SYSTEM == "Darwin":
            if shutil.which("otool") is None:
                output = "(otool not found, skipping)"
            else:
                output = subprocess.check_output(["otool", "-L", file_path], text=True)
        elif SYSTEM == "Linux":
            if shutil.which("ldd") is None:
                output = "(ldd not found, skipping)"
            else:
                output = subprocess.check_output(["ldd", file_path], text=True)
        elif SYSTEM == "Windows":
            try:
                import pefile
            except ImportError:
                output = "(pefile module not installed, skipping Windows DLL analysis)"
            else:
                pe = pefile.PE(file_path)
                lines = []
                if hasattr(pe, 'DIRECTORY_ENTRY_IMPORT'):
                    for entry in pe.DIRECTORY_ENTRY_IMPORT:
                        lines.append(entry.dll.decode('utf-8'))
                else:
                    lines.append("(No imports found)")
                lines.insert(0, os.path.basename(file_path))
                output = "\n".join(lines)
        else:
            output = f"Unsupported OS: {SYSTEM}"
    except Exception as e:
        output = f"(Cannot analyze {file_path}: {e})"

    print(output.strip())

def main():
    extention = EXTENTIONS.get(SYSTEM)
    executable = EXECUTABLES.get(SYSTEM)

    if not extention:
        print(f"Unsupported OS: {SYSTEM}")
        return

    executable_path = os.path.join(SCRIPT_DIR, executable)
    if os.path.isfile(executable_path):
        print(f">>> Executable: {executable_path}")
        list_dependencies(executable_path)
    else:
        print(f"(Executable {executable} not found)")

    for root, dirs, files in os.walk(SCRIPT_DIR):
        filtered_dirs = []
        for dir in dirs:
            if dir not in IGNORE_DIRS:
                filtered_dirs.append(dir)
        dirs[:] = filtered_dirs

        for file in files:
            if file.lower().endswith(extention):
                file_path = os.path.join(root, file)
                print(f">>> {file_path}")
                list_dependencies(file_path)

if __name__ == "__main__":
    main()
    if SYSTEM == "Windows":
        try:
            input("Press Enter to exit...")
        except EOFError:
            pass

#!/usr/bin/env python3
import os
import shutil
import platform

FILES = ["CMakeLists.txt.user"]
FOLDERS = ["Intermediate", ".idea"]

def remove_folders(folders):
    for folder in folders:
        if os.path.exists(folder) and os.path.isdir(folder):
            try:
                shutil.rmtree(folder)
                print(f"Folder '{folder}' deleted.")
            except Exception as e:
                print(f"Error deleting folder '{folder}': {e}")
        else:
            print(f"Folder '{folder}' not found.")

def remove_files(files):
    for file in files:
        if os.path.exists(file) and os.path.isfile(file):
            try:
                os.remove(file)
                print(f"File '{file}' deleted.")
            except Exception as e:
                print(f"Error deleting file '{file}': {e}")
        else:
            print(f"File '{file}' not found.")

def main():
    remove_folders(FOLDERS)
    remove_files(FILES)
    print("Remove succeeded!")

if __name__ == "__main__":
    main()
    if platform.system() == "Windows":
        try:
            input("Press Enter to exit...")
        except EOFError:
            pass

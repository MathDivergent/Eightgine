#!/usr/bin/env python3
import io
import fnmatch
import os
import platform
import shutil


EIGHTGINE_PLATFORM_WINDOWS : bool = platform.system() == "Windows"
EIGHTGINE_PLATFORM_LINUX : str = platform.system() == "Linux"
EIGHTGINE_PLATFORM_MACOS : str = platform.system() == "Darwin"

class DDevClear:
    def __init__(self):
        self.__cDirPatterns: list[str] = [
            "Intermediate",
            ".idea"
        ]

        self.__cFilePatterns: list[str] = [
            "CMakeLists.txt.user"
        ]

        self.__aRemoveStat: io.StringIO = io.StringIO()

    @staticmethod
    def __FileNameMatch(sFileName: str, cFilePatterns: list[str]):
        return any(fnmatch.fnmatch(sFileName, sFilePattern) for sFilePattern in cFilePatterns)

    def RemoveDirs(self):
        for aParentDir, cChildDirs, _ in os.walk('.', topdown=True):
            cMatchedDirs = [
                aChildDir for aChildDir in cChildDirs 
                if DDevClear.__FileNameMatch(aChildDir, self.__cDirPatterns)
            ]

            for aMatchedDir in cMatchedDirs:
                aMatchedDirPath = os.path.join(aParentDir, aMatchedDir)
                try:
                    shutil.rmtree(aMatchedDirPath)
                    cChildDirs.remove(aMatchedDir)
                    print(f"Directory '{aMatchedDirPath}' deleted.", file=self.__aRemoveStat)
                except Exception as aError:
                    print(f"Error deleting directory '{aMatchedDirPath}': '{aError}'!", file=self.__aRemoveStat)

    def RemoveFiles(self):
        for aParentDir, _, cChildFiles in os.walk('.'):
            cMatchedFiles = [
                aChildFile for aChildFile in cChildFiles 
                if DDevClear.__FileNameMatch(aChildFile, self.__cFilePatterns)
            ]

            for aMatchedFile in cMatchedFiles:
                aMatchedFilePath = os.path.join(aParentDir, aMatchedFile)
                try:
                    os.remove(aMatchedFilePath)
                    print(f"File '{aMatchedFilePath}' deleted.", file=self.__aRemoveStat)
                except Exception as aError:
                    print(f"Error deleting file '{aMatchedFilePath}': '{aError}'!", file=self.__aRemoveStat)

    def RemoveStat(self):
        sRemoveStat: str = self.__aRemoveStat.getvalue()
        self.__aRemoveStat.close()

        print(sRemoveStat, "Remove succeeded!")


def main():
    aDevClear: DDevClear = DDevClear()
    aDevClear.RemoveDirs()
    aDevClear.RemoveFiles()
    aDevClear.RemoveStat()

    if EIGHTGINE_PLATFORM_WINDOWS:
        try:
            input("Press Enter to exit...")
        except EOFError:
            pass


if __name__ == "__main__":
    if EIGHTGINE_PLATFORM_WINDOWS or EIGHTGINE_PLATFORM_LINUX or EIGHTGINE_PLATFORM_MACOS:
        main()
    else:
        print(f"Unsupported system: '{platform.system()}'!", file=self.aInfoStat)

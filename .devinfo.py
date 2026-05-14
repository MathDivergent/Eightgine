#!/usr/bin/env python3
import io
import fnmatch
import os
import platform
import subprocess
import shutil


EIGHTGINE_PLATFORM_WINDOWS : bool = platform.system() == "Windows"
EIGHTGINE_PLATFORM_LINUX : str = platform.system() == "Linux"
EIGHTGINE_PLATFORM_MACOS : str = platform.system() == "Darwin"

class DDevInfo:
    def __init__(self):
        if EIGHTGINE_PLATFORM_WINDOWS:
            self.__cModuleFilePatterns: list[str] = [
                "*.dll"
            ]

        elif EIGHTGINE_PLATFORM_LINUX:
            self.__cModuleFilePatterns: list[str] = [
                "*.so"
            ]

        elif EIGHTGINE_PLATFORM_MACOS:
            self.__cModuleFilePatterns: list[str] = {
                "*.dylib"
            }

        if EIGHTGINE_PLATFORM_WINDOWS:
            self.__cExecutableFilePatterns: list[str] = [
                "*/EmptyProject.exe",
                "*/EmptyProject-Debug.exe"
            ]

        elif EIGHTGINE_PLATFORM_LINUX or EIGHTGINE_PLATFORM_MACOS:
            self.__cExecutableFilePatterns: list[str] = [
                "*/EmptyProject",
                "*/EmptyProject-Debug"
            ]

        self.__cIngoreDirPatterns: list[str] = [
            "Intermediate",
            ".idea"
        ]

        self.__aInfoStat: io.StringIO = io.StringIO()

    if EIGHTGINE_PLATFORM_MACOS:
        def __ListDependencies(self, sFilePath: str):
            try:
                if shutil.which("otool") is None:
                    print("'otool' not found, skipping!", file=self.__aInfoStat)
                else:
                    print(subprocess.check_output(["otool", "-L", sFilePath], text=True), file=self.__aInfoStat)

            except Exception as aError:
                print(f"Cannot analyze '{sFilePath}': {aError}!", file=self.__aInfoStat)

    elif EIGHTGINE_PLATFORM_LINUX:
        def __ListDependencies(self, sFilePath: str):
            try:
                if shutil.which("ldd") is None:
                    print("'ldd' not found, skipping!", file=self.__aInfoStat)
                else:
                    print(subprocess.check_output(["ldd", sFilePath], text=True), file=self.__aInfoStat)

            except Exception as aError:
                print(f"Cannot analyze '{sFilePath}': '{aError}'!", file=self.__aInfoStat)

    elif EIGHTGINE_PLATFORM_WINDOWS:
        def __ListDependencies(self, sFilePath: str):
            try:
                import pefile

                aPE: pefile.PE = pefile.PE(sFilePath)
                cInfoLines: list[str] = []

                if hasattr(aPE, 'DIRECTORY_ENTRY_IMPORT'):
                    for aEntry in aPE.DIRECTORY_ENTRY_IMPORT:
                        cInfoLines.append(aEntry.dll.decode('utf-8'))
                else:
                    cInfoLines.append("No imports 'pefile' found!")

                cInfoLines.insert(0, os.path.basename(sFilePath))
                print("\n".join(cInfoLines), file=self.__aInfoStat)

            except ImportError:
                print("'pefile' module not installed, skipping Windows DLL analysis!", file=self.__aInfoStat)

            except Exception as aError:
                print(f"Cannot analyze '{sFilePath}': '{aError}'!", file=self.__aInfoStat)

    @staticmethod
    def __FileNameMatch(sFileName: str, cFilePatterns: list[str]):
        return any(fnmatch.fnmatch(sFileName, sFilePattern) for sFilePattern in cFilePatterns)

    def ListDependencies(self):
        sSourcePath: str = os.path.dirname(os.path.abspath(__file__))
        
        for aParentDir, cChildDirs, cChildFiles in os.walk(sSourcePath):
            cChildDirs[:] = [
                aChildDir for aChildDir in cChildDirs 
                if not DDevInfo.__FileNameMatch(aChildDir, self.__cIngoreDirPatterns)
            ]

            for aChildFile in cChildFiles:
                aChildFilePath = os.path.join(aParentDir, aChildFile)
                
                if DDevInfo.__FileNameMatch(aChildFile, self.__cModuleFilePatterns):
                    print(f">>>> Module: {aChildFilePath}", file=self.__aInfoStat)
                    self.__ListDependencies(aChildFilePath)

                if DDevInfo.__FileNameMatch(aChildFile, self.__cExecutableFilePatterns):
                    print(f">>>> Executable: {aChildFilePath}", file=self.__aInfoStat)
                    self.__ListDependencies(aChildFilePath)


    def InfoStat(self):
        sInfoStat: str = self.__aInfoStat.getvalue()
        self.__aInfoStat.close()

        print(sInfoStat)


def main():
    aDevInfo: DDevInfo = DDevInfo()
    aDevInfo.ListDependencies()
    aDevInfo.InfoStat()

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

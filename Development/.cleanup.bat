@echo off

REM List of files and folders (space-separated)
set "FILES=CMakeLists.txt.user"
set "FOLDERS=Intermediate"

REM Delete folders
for %%F in (%FOLDERS%) do (
    if exist "%%F\" (
        rmdir /s /q "%%F"
        echo Folder %%F deleted.
    ) else (
        echo Folder %%F not found.
    )
)

REM Delete files
for %%F in (%FILES%) do (
    if exist "%%F" (
        del /q "%%F"
        echo File %%F deleted.
    ) else (
        echo File %%F not found.
    )
)

echo Remove succesed!

pause
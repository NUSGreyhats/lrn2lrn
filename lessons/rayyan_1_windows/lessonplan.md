# Introduction to Windows

## Table of Contents
1. Windows Basics
2. Additional Windows Tools
3. Windows Command Prompt
4. Windows Powershell
5. Registry
6. Some Protection Mechanisms
	ASLR
7. Getting


### Introduction to Windows

### 3. Windows Command Prompt
The Windows command prompt is normally invoked with certain credentials, we can initialize it as a normal user first (that is ourselves). Simply hit <kbd>Windows + R</kbd> and type `cmd` and press Enter to launch the command prompt.

An equivalent to `man [command]` in Linux would be `[command] /?`, which will prove useful if you are stuck with any command. Note that `/?` is considered a "switch" (basically options).

Another note is the Absolute pathname difference:
```dos
Format: [Drive]:\[Path]\[File].[Extension]
Example: C:\Program Files\Java\jdk1.8.0_01\bin\javac.exe
```

Some useful commands for Windows Command Prompt are as follows:

Directory-related commands
```dos
dir /Q /P
- display contents of directory with file owner, paginated

cd [DIRECTORY]
- change to specified directory

xcopy D:\Data Z:\Backup /E /G /H
- Copies encrypted files, all subdirectories and hidden/system files from source to destination (basically backup)
```

Other Similar commands to Linux
```dos
whoami / echo %username%
- shows login name of currently logged in user

```

Runnning as another user (similar to sudo)
```dos
runas /user:administrator regedit (will ask for password)
- Run as administartor for a given program (e.g. regedit)
```

We can also write a basic batch files using the .bat extension:
```dos
SET name=Bob The Builder &:: This is an appended comment
SET /P filename=Enter a file name: &:: How to do input
IF EXIST %filename% (
	DEL /p %filename% &:: Deletes file after prompting user
) ELSE (
	ECHO %filename% does not exist!
)
GOTO loopyloop
:: Single-line comment, will be skipped! Note: GOTO can be used as loops!
:loopyloop
FOR %%F IN (*.txt) DO echo %%F &:: Display all .txt file names

CALL :add 10 11 &:: Perform a function call with param1=10 and param2=11
ECHO %RESULT% &:: should echo 21

:add
SETLOCAL # Ensure all set only applies for local context
set retval=0
set a=%1 # %1 stands for first argument, %2 for second ...
set b=%2
set /A "retval=a+b" &:: Use /A to perform arithmetic
ENDLOCAL & SET result=%retval% &:: Set result to return value
```




### 4. Windows Powershell

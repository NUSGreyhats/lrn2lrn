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
```bat
Format: [Drive]:\[Path]\[File].[Extension]
Example: C:\Program Files\Java\jdk1.8.0_01\bin\javac.exe
```

Some useful commands for Windows Command Prompt are as follows:

Directory/File-related commands
```bat
dir /Q /P
- display contents of directory with file owner, paginated

cd [DIRECTORY]
- change to specified directory

xcopy D:\Data Z:\Backup /E /G /H
- Copies encrypted files, all subdirectories and hidden/system files from source to destination (basically backup)

dir C:\ /s /b | find "SECRET"
- Search local hard drive C:\ for text "SECRET"

findstr /S /I confidential *.*
- Search for all files in subdirectories etc. for the word confidential, non-case sensitive
```

Windows Services / Tasks
```bat
sc start [SERVICE] - start a specific Windows Service
sc stop [SERVICE] - stop a specfic Windows Service
tasklist /svc - List all processes, their PIDs and corresponding Windows Services (if any)
taskkill /pid - Kill a process with a specific PID
```

net/netsh command
```bat
net accounts
- Display local user account policies for passwords (e.g. reset every 30 days etc.)

netsh firewall set opmode disable
- Quickly disable built-in Windows Firewall
```

reg command (For editing registry key/values)
```bat
reg add [\\TargetIPAddr\][RegDomain]\[Key]
- Add new [Key] to [RegDomain] at specified IP address. Assume local machine if no remote machine is specified

reg export [RegDomain]\[Key] [FILE]
- Export all keys in [RegDomain] to [File]

reg import [RegDomain]\[Key] [FILE]
- Import all keys from [FILE] to [RegDomain]

reg query [\\TargetIPAddr\][RegDomain]\[Key] /v [VALUENAME]
- Query a machine and get VALUENAME of a specific key
```

Windows Management Interface Command line (wmic)
```bat
FORMAT: wmic [alias] [where clause] [verb clause]

wmic process list full
- Displays all information about every single process, including the full path of the executable running. Switch 'full' to 'brief' for lesser details.

wmic startup where name='nc.exe'
- Displays a list of startup processes, useful for finding malware / programs that run on startup. In this case, we try to check if nc.exe is launched at startup.

wmic useraccount list full
- Displays a full list of accounts on the local machine, including whether they have passwords set or not etc. (Useful to determine what accounts we can try to compromise)

wmic qfe list full
- Displays a full list of patches and service packs installed on a service machine (Useful to determine if an exploit works) [qfe = Quick Fix Engineering]
```

Invoking Useful GUIs using command line:
```bat
lusrmgr.msc - Local User Manager
services.msc - Services Control Panel
secpol.msc - Security Policy Manager
eventvwr.msc - Event Viewer
regedit - Registry Editor
```

Other Similar commands to Linux
```bat
whoami / echo %username%
- shows login name of currently logged in user

netstat -a -n 2
- Displays all connections and listening ports (in decimal form), auto-refresh every 2 seconds
```

Runnning as another user (similar to sudo)
```bat
runas /user:administrator regedit (will ask for password)
- Run as administartor for a given program (e.g. regedit)
```

In Windows we follow the PATH environment variable in order to deduce where executables can be found. To view your PATH, simply type `path`. However, if you wish to insert your own malicious directory as the directory to be search first permanently, you may use:
```
setx path "C:\BAD_STUFF\;%path%"
```
This will lead to C:\BAD_STUFF being search for first instead of %path%. Note that it also works without `setx` but in that case it only works for the current session.




We can also write a basic batch files using the .bat extension:
```bat
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

Again, this is just a very small program and there are many other methods / functions out there. You may refer to [this link](https://en.wikibooks.org/wiki/Windows_Batch_Scripting) For more details


### 4. Windows Powershell

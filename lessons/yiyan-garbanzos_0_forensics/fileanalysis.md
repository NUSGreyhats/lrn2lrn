# File Analysis

## What is a File
We can view a file as a sequence of bytes used to store data. This data maybe a picture, video or a text document etc.

## File Format Identification
How does your computer know what is the format of a sequence of bytes? What is the sequence of bytes encoding for?

### Filename Extension
Most operating Systems usually figure it out by looking at the file extension. However, it is not reliable because you can easily change the extension by renaming the file.

### File Metadata
**File Format Magic Number** <br>
The first few bytes of of most files is the file format magic number, aka file signature.  Here are some examples of file signatures:

| File format | Signature in text | Hex signature |
| ------------- | ------------- | ----- |
| pdf | %PDF | 25 50 44 46 |
| png | .PNG.... | 89 50 4E 47 0D 0A 1A 0A |
| jpg<br>jpeg | ÿØÿÛ<br><br> ÿØÿà ..JF IF..<br><br> ÿØÿá ..Ex if.. | FF D8 FF DB<br><br>FF D8 FF E0 nn nn 4A 46 49 46 00 01<br><br>FF D8 FF E1 nn nn 45 78 69 66 00 00<br> |

Check out [this](https://www.filesignatures.net/) or [this](http://www.garykessler.net/library/file_sigs.html) or [this](https://en.wikipedia.org/wiki/List_of_file_signatures) for more file format magic numbers.

**File Header** <br>
This is *usually* found in the start of the file, but can be located elsewhere depending on the file format. It contains information on the file contents. For example, EXIF in JPEG, RAW and TIFF store information such as, camera used to capture the picture, and when and where the picture was taken.

## Tools
### file
```
file filename
```
To determine the file format, `file` performs the following 3 tests. The tests are performed in the order shown in the list and the *first* test that succeeds causes the file type to be printed.

|No.| Test | Description |
| -| - | - |
|1.| Filesystem tests | Checks if the file is empty or if it is some special file, e.g. symbolic links and named pipes. |
|2.|Magic tests| Check for files with data in particular fixed formats. Specifically, one thing it checks is whether the file has a file format magic number that matches one of the known file formats. |
|3.|Language tests| Checks to see if it seems to be a text file. When it is a text file, it reports the encoding. In addition, it also reports the language of the text file if it can be determined. |

To obtain results from all the tests, the `-k` can be used. Learn more about the other options [here](https://linux.die.net/man/1/file).

### TrID
```
.\trid filename
```
To use, download TrID and TRD definitions [here](http://mark0.net/soft-trid-e.html). According to the website it can identify up to 8408 file types. It identifies file types using the binary signatures of files.

### binwalk
```
binwalk filename
```
Binwalk is a tool for analyzing, reverse engineering, and extracting firmware images. Binwalk can scan a firmware image for many different embedded file types and file systems.

You can  find the installation instructions [here](https://github.com/devttys0/binwalk/wiki/Quick-Start-Guide) and learn more about the other functionalities of binwalk
[here](https://github.com/devttys0/binwalk/wiki/Usage).

#### Exercise
Let's try out file, TrID and binwalk on the following files.

| File | Description |
| - | - |
|[LegitPngFile](./exercise/LegitPngFile)| As in the filename |
|[DamagedPngFile](./exercise/DamagedPngFile)| The file signature part of the file is damaged |
|[NotReallyAPngFile](./exercise/NotReallyAPngFile)| A random file prepended with png file signature |
|[WhatIsThisFiles](exercise/W)| A jpg file + a png file |

### Online File Format Identifiers
Just some online alternatives:

1. [Toolsley File Identifier](https://www.toolsley.com/file.html)
2. [Falstaff](http://ec2-52-37-126-112.us-west-2.compute.amazonaws.com/falstaff/)

## File Formats
1. [png](./png.md)
2. TBC

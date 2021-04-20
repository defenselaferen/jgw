# JGW (Jonathan Generate Wave)

This is also a tool with which you can make songs. but like programming. And the way is the same as Java. compile the code first to binary. 
finished running with a different executable.

The Program:
Just like giving parameters to functions. the way is like giving a frequencyn in the first and second posts there is a delay (cs).
So it looks this way. In the middle of it must be put a comma.

Main:
```text
Frequency, Delay
```

And if there is another line put a comma at the last delay it will be like this.

Main:
```text
Frequency, Delay,
Frequency, Delay
```

If you are a beginner, you don't know how frequency works you can use a frequency substitute using a word.

This is Syntax.

Syntax Frequency:

- Do1, Re1, Mi1, Fa1, So1, La1, Si1
- Do2, Re2, Mi2, Fa2, So2, La2, Si2
- Do3, Re3, Mi3, Fa3, So3, La3, Si3
- Do4, Re4, Mi4, Fa4, So4, La4, Si4
- Do5, Re5, Mi5, Fa5, So5, La5, Si5

Keys Note:

- K1_1, K1_2, K1_3, K1_4, K1_5
- K2_1, K2_2, K2_3, K2_4, K2_5
- K3_1, K3_2, K3_3, K3_4, K3_5
- K4_1, K4_2, K4_3, K4_4, K4_5
- K5_1, K5_2, K5_3, K5_4, K5_5

If Delay You Must Know So To Seconds You Will Need (x100).

If keys is a black color on top of the white keys that are usually on the piano
So it can also be mathematically operational. In the frequency of reply in delay is not needed. 

Example:

```bash
Do4 * 2, 100
```

### compile And Installing Dependencis

compile:
```bash
$ bash build.sh
```

Install:
```bash
$ chmod +x INSTALL
$ ./INSTALL
```

How to compile music code
In the bin folder section there is the same executable jgw

for run compile:
So this is it.

Example:
```bash
$ ./jgw --compile <pathfile>
```

And if already compiled
Will release sourcecode.bnm there will be additional bnm format
That stands for binaru note music.

And how to play it with. 

```bash
$ ./jgw --play <pathfile>.bnm
```

Update Source Code And Compiling
If You Run `UPDATE`. Your Source Code From JGW Can Be Update.
And Compiling Automatically.

How to run:

```bash
$ chmod +x INSTALL
$ ./INSTALL
```

Compile To WAV:

```bash
$ ./jgw --compile-wav <pathfile>.bnm
```

It's Output:
- <pathfile>.bnm.wav


## Requirements
You must have this requirements:
- clang or g++
- libsdl2-dev

### Termux
If you using termux run this command:
```bash
$ apt update --fix-missing -y
$ apt upgrade --fix-missing -y
$ pkg update --fix-missing -y
$ pkg upgrade --fix-missing -y
$ pkg install x11-repo -y
$ pkg install clang sdl2-mixer -y
$ bash build_termux.sh
```

### Windows
If you using Windows. You just have to compiler C ++.
In Powershell
```powershell
$ .\build.bat
```
In Command Prompt
```bash
$ build.bat
```

### Linux
If you using Linux. You just have to using you're internet.
If you missing dependencis. This automatically install in you're computer.
```bash
$ bash build.sh
```

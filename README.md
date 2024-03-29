# Introduction
Hello everyone, this small project is supposed to be an attempt to learn 
Pybind11. Of course, like everything else I tried to learn, it's never
that easy. I ran into some problems so I decided to upload the repo on
github so others can look at it, and hopefully help me figure it out.

# Explanation
The pybind11 module I tried to make as simple. It was just a simple module
that includes a function that prints "Hello World!" when called. Y'know,
the bare minimum so I could get used to Pybind11.

I used CMake-Gui version: 3.29.0-rc2, and it generated the makefile
without any problems. The generated Makefile worked as well, and compiled
a .pyd module file. The problem is that whenever I tried to import the
module either through the Python Shell or regular file, I get this error:

```
ImportError: DLL load failed while importing test_module: The specified module could not be found.
```

To be honest, I was frustrated as I had to deal with another "black box"
situation again. I had no idea what the error meant, and I tried many
different things for no effect.

# What I tried.
After some angry searching one the internet I figured out one way I could
fix the issue. It was thanks to this thread in the pybind repo:
https://github.com/pybind/pybind11/issues/2010

Judging from the thread, apparently the error means that some DLLs which
my pybind module needs are missing, and the way I could fix it is add
the path to the DLLs that my module was missing.

```
>>> import os
>>> os.add_dll_directory("C:\\MinGW\\bin") # The path where DLLs the customized pybind module needs are locating.
<AddedDllDirectory('C:\\MinGW\\bin')>
>>> import example
>>> example.add(1, 2)
3
```

I tried doing this in the Python Shell, and it worked... I played around
for a bit by setting up a small package with a __init__.py file, and
created a stub file so my LSP and Typechecker would know the function
exists and not complain.

# The Main Issue.
While the solution does work, there's still one problem. It's not really
portable. While my DLL directory is located at: "C:/msys64/mingw64/bin",
not everyone is gonna have their's located at the same place. Yet alone
even have mingw64.

The module would only work for my computer. What if I want to distribute
what I'm making? If anyone else wants to use it, they would have to edit 
the code themselves for download something they wouldn't want to.

The only way I could see of fixing the issue is finding the DLLs the
module is missing, and statically link them to the module binary itself.
That way, no one has to deal with the add_dll_directory nonsense.

I tried tracking down what DLLs could be missing by using a dependency
walker, but the only clue I could find on what it could be is: 
"ext-ms-win-oobe-query-l1-1-0.dll". However I think that clue is 
irrelevant as the module imports just fine when I added the DLL directory
in test.py. So I could only deduce that whatever DLL the module was 
missing is in that directory.

Like I said, I'm frustrated that I seem to be the one of the only people
who seem to be having this issue. Hopefully uploading this project to 
github would help people get a better look and figure out a solution.
I hope you guys have a good day.

# The True Solution!!!
Ladies and Gentlemen, as of March 8th, 2024 at 10:21 PM EST, I've finally 
found the solution to the problem! I'm gonna document it here so others
could find the solution as well.

Apparently, the DLL file that the module needs was "libwinpthread-1.dll".
Once I knew that, all I had to do is statically link it in the cmake file.
Although, just to be safe, you may want to also link "static-libgcc" and
"static-libstdc++".

```
target_link_libraries("test_module" PRIVATE -static -lpthread -static-libgcc -static-libstdc++)
```

Once I did that, and compiled the module file, I was able to import the
module without needing to use "os.add_dll_directory"! Finally I could move
on to something else!



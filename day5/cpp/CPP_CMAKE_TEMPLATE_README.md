# Glossary (Explanation of terms/namings that occur):
## target (as in 'mytarget.cpp')
* Uses the same connotation as 'target' in cmake. It's some sourcecode that is built to result in a executable/binary or a library.
* When building a target into a library, make sure you use the scope rules PRIVATE, PUBLIC, INTERFACE correctly to decide which header files should be visible/accessable to the targets that link to that library.
* The file 'mytarget.cpp' is the entry point of the program, essentially it's the 'main.cpp' with the 'int main()' function. Try to have a appropriate name for this so that it's easy for the developer to find the entry point.

## module (Think of it as a 'block' in a 'block-diagram' describing a system.)
* Module is a isolated part of the sourcecode/codebase representing certain behaviour or functionality.
* Keeping each module well-defined in what purpose, behaviour and functionality it holds/represents makes it easier to avoid your codebase from having redundant code and becoming messy, complicated and hard to maintain. So it's a good idea to put a bit extra thought to what each module's purpose is before you just implement things hastily.
* It's common to revisit previously created modules and redefine them or break them apart (refactoring), since it's impossible to know ahead of time what the full resulting codebase will look like once your project is all complete.
    * It can be a good idea to write down in your todo list, whenever you notice things about your modules that can be improved in regards to keeping them confined, well-defined and easier to maintain.
* At the same time though, remember that there is no such thing as a perfectly defined, maintable source code. Aslong as you can keep modules and each .cpp/.h file from growing to out of control in size, you should be able to avoid any too big refactoring work down the line.

# Folders/Files (Explaining purpose/meaning of each file and folder in project structure)
The following shows the full filestructure from repository root:
```
build/
cmake/
    mytarget_rpi3.cmake
include/ <-- Holds all headerfiles 
    mytarget.h 
src/
    mymodule/
        mymodule_utils.cpp
        mymodule_utils.h
        mymodule.cpp
        mymodule.h
    CMakeLists.txt
    mytarget.cpp <-- essentially the 'main.cpp' (entry point of program)
test/ <-- 
thirdparty_lib/
thirdparty_src/
CMakeLists.txt
```
* build
    * This is the folder where all the built files goes, see more information below on steps on how to build.
    * Nothing with this folder should be commited/version handled.
    * To ensure a clean build, you can clear the 'build' folder from all files and folders before rebuilding.
* cmake
    * Holds .cmake config files, used to load a specific predefined configuration. So for example you can have a .cmake file that configures your build to cross-compile your target/project to run on a certain platform, like raspberry pi running raspbian.
    * They are used in the same step that configures and generates your build files. So instead of running 'cmake ..' you run 'cmake -C ../cmake/mytarget_rpi3.cmake ..' as an example.
* include
    * Only needed if target (the source code in 'src') outputs and library and not a executable
    * Holds the headers files that is exposed to other developers using this library, essentially 
    the API of what you have in 'src'.
* src
    * Holds your sourcecode. For this structure we assume everything in 'src' is to build a single target (either a library or executable). For a file structure that enables you to have multiple buildable targets in 'src', see this other template: URL TO MULTI TARGET TEMPLATE
* test
    * All automated testing: unittests, system/integration tests etc
* thirdparty_lib
    * Thirdparty libraries that are prebuilt libraries, either dynamic or static (.a, .so, .lib, .dll files)
    * Add information in this README file the version and a link or description where the library was taken from and how to get more information about it and how to get more recent versions of the library.
* thirdparty_src
    * Thirdparty libraries that we build from source, if possible keep it with the whole repository so we have version history and can easily update to newer versions, but updating to a more recent branch/revision.
    * If there is no repository for the thirdparty lib, or if it uses a different version handling system than git (mercurial, svn etc.), add information in this README file the version and a link or description where the sourcecode was taken from and how to get more information about it and how to get more recent versions of the source code.

# Adapting this template for your project:

* Change name of project in CMakeLists.
* Remove/Rename the files you need or don't need so it fits your project.
    * Remember to change CMakeLists.txt files aswell if you remove/rename files.
* Remove/Modify the example code inside the existing .cpp/.h files.

# How to build:

1. Create build folder from repo root (Can be called whatever you want, 
for example call it 'build')
2. 'cd' to your new build folder
3. 'cmake ..'
    * Configures and Generates build files
    * This will prepare for build everything in repo, if you want to for example only build 'src' (skipping 'test' and 'thirdparty_src') you can instead run 'cmake ../src'
4. 'cmake --build .'
    * Builds (e.g. compile, link etc.) based on the configuration and generation in previous step
5. Find you executable/binary in:
'<your build folder\>/'

# Side track points

## Why we add .cpp/.h files explicitly instead of using glob/wildcard patterns in CMakeLists.txt files

When we point out source and header files in CMakeLists.txt files for example with the call
target_sources, we can either use glob/wildcard patterns with the help of variables to get
all .cpp and .h file in current or even recursivley in all sub directories.

This initially seems like a good idea because it reduces the size of CMakeLists.txt and
you don't have to remember to adjust everytime you rename or add a new file.

Unfortunatley though, things are much more error-proned this way. First of all this way
cmake can't figure out the dependencies between the files, which means you build will
much more likely be broken when ever you rebuild without doing it from a clean build
directory.

This is just a simple/short explanation of the full argument which you can find in [this link](https://stackoverflow.com/questions/1027247/is-it-better-to-specify-source-files-with-glob-or-each-file-individually-in-cmak)

# Good links for inspiration on nice file/project structure with cmake:
* https://arne-mertz.de/2018/06/cmake-project-structure/

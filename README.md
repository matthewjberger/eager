# Eager
An ogre project template that uses premake to generate C++ project files for make or visual studio.

# Building your Project

Check the prerequisites section if anything fails here.

#### GNU Make (Linux)
```bash
git clone https://github.com/matthewjberger/eager your-project-name
cd your-project-name
./premake5 gmake
````

For a debug build:

```bash
make -C build
```

Your project can then be found in the `bin/debug` directory.

If you want a release build:
```bash
make -C build
```
# Prerequisites

####Note: If you're using NoMachine at the University of Nevada, Reno, the following steps are not required. The library has already been built from source and installed on NoMachine.

Ogre 3D must be installed. If it isn't installed you should build it from the source with the following commands.  Mercurial is required to clone the repo.

Clone the repo and grab version 1.9:
```bash
hg https://bitbucket.org/sinbad/ogre/src
cd ogre
hg pull
hg update v1-9
```

Use cmake to build the library:

```bash
mkdir build
cd build
cmake ..
```

Install the library:
```bash
sudo make install
```

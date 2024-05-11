# Needed

Cmake installed with:

```bash
sudo apt update
sudo apt install cmake
```

Qt5 installed with:

```bash
sudo apt install qtbase5-dev
```

## How to build?

Just run:

```bash
sh build.sh # in <project root>
```

or

```bash
./build.sh # if build.sh has permissions to run by user
```

## How to run?

to run program:

```bash
./files_compare
```

to run test:

```bash
./tests
```

## File structure

```txt
<project root>
├── CMakeLists.txt
├── README.md
├── build.sh
├── include
│   ├── CompareFiles
│   ├── TWidget.hpp
│   ├── button.hpp
│   ├── compare_files
│   │   ├── block.hpp
│   │   ├── file.hpp
│   │   ├── kmp.hpp
│   │   └── textdiff.hpp
│   └── mainwindow.hpp
├── install
├── src
│   ├── app
│   │   ├── CMakeLists.txt
│   │   ├── TWidget.cpp
│   │   ├── button.cpp
│   │   └── mainwindow.cpp
│   ├── compare_files
│   │   ├── CMakeLists.txt
│   │   ├── block.cpp
│   │   ├── file.cpp
│   │   ├── kmp.cpp
│   │   └── textdiff.cpp
│   └── main.cpp
└── test
    └── test.cpp
```

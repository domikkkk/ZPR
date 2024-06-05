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

to run tests:

```bash
./tests
```

## File structure

```txt
├── CMakeLists.txt
├── README.md
├── build.sh
├── include
│   ├── CompareFiles
│   ├── TWidget.hpp
│   ├── button.hpp
│   ├── compare_files
│   │   ├── app.hpp
│   │   ├── block.hpp
│   │   ├── change.hpp
│   │   ├── comparator.hpp
│   │   ├── file.hpp
│   │   ├── kmp.hpp
│   │   ├── nw.hpp
│   │   └── textdiff.hpp
│   ├── legend.hpp
│   ├── mainwindow.hpp
│   ├── mergedWindow.hpp
│   └── namespaces.hpp
├── src
│   ├── app
│   │   ├── CMakeLists.txt
│   │   ├── TWidget.cpp
│   │   ├── button.cpp
│   │   ├── legend.cpp
│   │   ├── mainwindow.cpp
│   │   └── mergedWindow.cpp
│   ├── compare_files
│   │   ├── CMakeLists.txt
│   │   ├── app.cpp
│   │   ├── block.cpp
│   │   ├── change.cpp
│   │   ├── comparator.cpp
│   │   ├── file.cpp
│   │   ├── kmp.cpp
│   │   ├── nw.cpp
│   │   └── textdiff.cpp
│   └── main.cpp
└── test
    ├── test.cpp
    └── text_files
        ├── letters.txt
        ├── letters_v2.txt
        ├── par.txt
        ├── paragraphs.txt
        ├── paragraphs_v2.txt
        └── test_file.txt
```

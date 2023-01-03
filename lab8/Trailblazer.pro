TEMPLATE = app

# Make sure we do not accidentally #include files placed in 'resources'
CONFIG += no_include_pwd

# Reduce compile times and avoid configuration confusion by excluding Qt libs
CONFIG -= qt

# Do not create an app bundle when running on OS X
CONFIG -= app_bundle

# Used to turn off warnings for qt headers.
QMAKE_CXXFLAGS += -isystem $$[QT_INSTALL_HEADERS]

QMAKE_CXXFLAGS += -std=c++11 -m64 -pipe -fstack-clash-protection -fstack-protector-strong

# Warnings
QMAKE_CXXFLAGS += -Wall -Wextra -Wshadow -Wunused -Wold-style-cast -Woverloaded-virtual -Wnull-dereference
QMAKE_CXXFLAGS += -Wconversion -Wdouble-promotion
# GCC specific
QMAKE_CXXFLAGS += -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast -Wunsafe-loop-optimizations

# Errors
QMAKE_CXXFLAGS += -Wimplicit-fallthrough -Werror=return-type -Werror=narrowing -Wuninitialized

QMAKE_CXXFLAGS_DEBUG += -Og -g -ggdb -D_FORTIFY_SOURCE=2 -D_GLIBCXX_ASSERTIONS -fasynchronous-unwind-tables
QMAKE_CXXFLAGS_RELEASE += -D NDEBUG -O3 -march=native -flto

QMAKE_LFLAGS += -m64

# These flags increase the recursion stack size so that recursive DFS doesn't
# exhaust all available stack space on large graphs
QMAKE_CXXFLAGS += -fno-stack-limit -fstack-check

INCLUDEPATH += $$PWD/lib/StanfordCPPLib/

SOURCES = $$PWD/src/*.cpp
SOURCES += $$PWD/lib/StanfordCPPLib/*.cpp

HEADERS = $$PWD/src/*.h
HEADERS += $$PWD/lib/StanfordCPPLib/*.h
# HEADERS += $$PWD/lib/StanfordCPPLib/private/*.h


# Copies the given files to the destination directory
# The rest of this file defines how to copy the resources folder
defineTest(copyToDestdir) {
    files = $$1

    for(FILE, files) {
        DDIR = $$OUT_PWD

        # Replace slashes in paths with backslashes for Windows
        win32:FILE ~= s,/,\\,g
        win32:DDIR ~= s,/,\\,g

        !win32 {
            copyResources.commands += cp -r '"'$$FILE'"' '"'$$DDIR'"' $$escape_expand(\\n\\t)
        }
        win32 {
            copyResources.commands += xcopy '"'$$FILE'"' '"'$$DDIR'"' /e /y $$escape_expand(\\n\\t)
        }
    }
    export(copyResources.commands)
}

!win32 {
    copyToDestdir($$files($$PWD/res/*))
    copyToDestdir($$files($$PWD/lib/*.jar))
}
win32 {
    QMAKE_LFLAGS += -Wl,--stack,100000000   # stop stack from overflowing
    copyToDestdir($$PWD/res)
    copyToDestdir($$PWD/lib/*.jar)
}

copyResources.input = $$files($$PWD/res/*)
OTHER_FILES = $$files(res/*)
QMAKE_EXTRA_TARGETS += copyResources
POST_TARGETDEPS += copyResources

macx {
    cache()
}

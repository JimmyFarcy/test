import os
from os.path import join
def doWalk():
    exludedirs=["Debug","Debug Win32","DebugUnix","LibDebugging","python_bindings"]
    headers=""
    sources=""
    template="""
    # -------------------------------------------------
    # Project created by QtCreator 2010-05-03T09:58:56
    # -------------------------------------------------
    QT -= core \
        gui
    TARGET = lib_interface
    TEMPLATE = lib
    DEFINES += LIB_INTERFACE_LIBRARY
    SOURCES += %(sources)s
    HEADERS += %(headers)s
    INCLUDEPATH = ./
    """
    for root, dirs, files in os.walk('./'):
        for excldir in exludedirs:
            if excldir in dirs:
                dirs.remove(excldir)  # don't visit excldir directories
        for filename in files:
            ext=filename[filename.rfind(".")+1:]
            filepath=join(root,filename)
            filepath=filepath.replace("\\","/")[2:]
            if ext in ["h","hpp"]:
                headers+=filepath+"\\\n"
            elif ext in ["c","cpp"]:
                sources+=filepath+"\\\n"
    sources=sources[:-2]
    headers=headers[:-2]
    print template % {"headers" : headers, "sources": sources}
doWalk()
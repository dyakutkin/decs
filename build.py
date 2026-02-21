import subprocess, pathlib, sys

SRC_DIR = pathlib.Path("./src")
OUT_DIR = pathlib.Path("./out")
OUT_DIR.mkdir(exist_ok=True)

MODES = {
    "--run": ("release.exe", ["-O3", "-DNDEBUG"], True),
    "--debug": ("debug.exe", ["-g3", "-O0", "-fno-omit-frame-pointer", "-fno-inline"], False,),
}

LIBS = ["src/lib/win/libraylib.a", "-lm", "-lwinmm", "-lgdi32"]

# TODO: consider "embedding" assets into the binary, e.g.
# xxd -i .\assets\apple.png > apple.h

if __name__ == "__main__":
    sources = list(SRC_DIR.rglob("*.c"))

    mode = sys.argv[1]
    exe, flags, should_run = MODES[mode]
    output = OUT_DIR / exe

    cmd = ["gcc", "-o", str(output), *flags] + [str(f) for f in sources] + LIBS 
    subprocess.run(cmd, check=True)

    if should_run:
        subprocess.run([str(output)], creationflags=subprocess.CREATE_NEW_CONSOLE)


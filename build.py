import subprocess, pathlib, sys

SRC_DIR = pathlib.Path("./src")
OUT_DIR = pathlib.Path("./out")
OUT_DIR.mkdir(exist_ok=True)

FLAGS_DEBUG = ["-g3 ", "-O0", "-fno-omit-frame-pointer", "-fno-inline", "-fsanitize=address,undefined"]
FLAGS_RELEASE = ["-O3", "-DNDEBUG"]

LIBS = ["src/lib/win/libraylib.a", "-lm", "-lwinmm", "-lgdi32"]

if __name__ == "__main__":
    sources = list(SRC_DIR.rglob("*.c"))
    output = OUT_DIR / "release.exe"
    cmd = ["gcc", "-o", str(output), *FLAGS_RELEASE] + [str(f) for f in sources] + LIBS 
    subprocess.run(cmd, check=True)

    if "--run" in sys.argv:
        subprocess.run([str(output)], creationflags=subprocess.CREATE_NEW_CONSOLE)


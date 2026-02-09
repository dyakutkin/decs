import subprocess, os, pathlib

SRC_DIR = pathlib.Path("./src")
BUILD_DIR = pathlib.Path("./out")
BUILD_DIR.mkdir(exist_ok=True)

_debug_flags = ["-g3 ", "-O0", "-fno-omit-frame-pointer", "-fno-inline", "-fsanitize=address,undefined"]

if __name__ == "__main__":
    sources = list(SRC_DIR.rglob("*.c"))
    output = BUILD_DIR / "release.exe"
    cmd = ["gcc", "-O3", "-DNDEBUG", "-o", str(output)] + [str(f) for f in sources] + ["src/lib/win/libraylib.a", "-lm", "-lwinmm", "-lgdi32"]
    subprocess.run(cmd, check=True)


"""Rebuild only proven native outputs; never discard packaged siblings."""

import argparse
from pathlib import Path, PurePosixPath
import re
import shutil
import stat

from repository import is_link


PRODUCT = "System Colors"
BASE = Path("test/Plugins")
BUNDLE = BASE / (PRODUCT + ".bundle")
FILES = tuple(BUNDLE / relative for relative in (
    f"Contents/MacOS/{PRODUCT}", "Contents/Info.plist",
    "Contents/Resources/English.lproj/InfoPlist.strings",
    "Contents/Resources/constants.xlf", "Contents/Resources/manifest.json",
    "Contents/_CodeSignature/CodeResources",
))
XCODE_DATA = Path("build/XCBuildData")
DIRECTORIES = (
    Path("build") / (PRODUCT + ".build"),
    Path("build/Default") / (PRODUCT + ".build"),
    BASE / (PRODUCT + ".build"),
    BASE / "Default" / (PRODUCT + ".build"),
)


def generated(path):
    if "\\" in path or PurePosixPath(path).as_posix() != path \
            or PurePosixPath(path).is_absolute() or ".." in PurePosixPath(path).parts:
        return False
    return (path in set(map(str, FILES))
            or bool(re.fullmatch(
                r"build/XCBuildData/(?:build\.db(?:-wal|-shm)?|"
                r"[0-9a-f]{32}\.xcbuilddata/.+)", path))
            or any(path.startswith(str(directory) + "/") for directory in DIRECTORIES))


def validate_paths(paths):
    root = Path.cwd().resolve()
    for path in paths:
        for parent in (path, *path.parents):
            if parent == Path("."):
                break
            if is_link(parent):
                raise ValueError(f"Refusing symlink output: {parent}")
        if not path.resolve().is_relative_to(root):
            raise ValueError(f"Output escapes checkout: {path}")
        if path.is_dir():
            for descendant in path.rglob("*"):
                if is_link(descendant):
                    raise ValueError(f"Refusing symlink output: {descendant}")


def prepare():
    validate_paths((*FILES, *DIRECTORIES, XCODE_DATA))
    for path in FILES:
        if path.exists() and not stat.S_ISREG(path.lstat().st_mode):
            raise ValueError(f"Expected regular generated leaf before cleanup: {path}")
    for path in (*DIRECTORIES, XCODE_DATA):
        if path.exists() and not path.is_dir():
            raise ValueError(f"Expected generated directory before cleanup: {path}")
    for path in FILES:
        path.unlink(missing_ok=True)
    for path in DIRECTORIES:
        if path.exists():
            shutil.rmtree(path)


def require_file(path):
    validate_paths((path,))
    try:
        status = path.lstat()
    except FileNotFoundError as error:
        raise ValueError(f"Missing native output: {path}") from error
    if not stat.S_ISREG(status.st_mode) or status.st_size == 0:
        raise ValueError(f"Missing or empty regular native output: {path}")


def verify_resources():
    for name in ("manifest.json", "constants.xlf"):
        copied = BUNDLE / "Contents/Resources" / name
        require_file(copied)
        if copied.read_bytes() != Path(name).read_bytes():
            raise ValueError(f"Copied resource differs from source: {copied}")


def verify_unsigned():
    for path in FILES:
        if path != BUNDLE / "Contents/_CodeSignature/CodeResources":
            require_file(path)
    verify_resources()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("phase", choices=("clean-macos", "verify-resources", "verify-unsigned"))
    phase = parser.parse_args().phase
    if phase == "clean-macos":
        prepare()
    elif phase == "verify-unsigned":
        verify_unsigned()
    else:
        verify_resources()

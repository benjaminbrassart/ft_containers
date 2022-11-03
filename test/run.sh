#!/bin/bash

DIR_LOGS='logs'
DIR_DIFF='diff'
DIR_TITLES='titles'

FILE_INCLUDE_PATH=".include_path"

is_abs() {
    case "$1" in
    /*) return 0;;
    *)  return 1;;
    esac
}

if is_abs "$0"; then
    REAL_WD="$(dirname "$0")"
else
    SCRIPT_WD="$(dirname "$0")"
    REAL_WD="$(realpath "${PWD}/${SCRIPT_WD}")"
fi

cd "${REAL_WD}" || exit 1

set -e

. script/func.sh

make -q

pushd src &>/dev/null || exit 1

declare -a TEST_FILES

for arg in $*; do
    arg="./${arg}"
    if [[ -d "${arg}" ]]; then
        files="$(find "./${arg}" -type f -iname '*.cpp' -exec realpath --relative-to=. {} \;)"
        readarray -t read_files <<< "${files}"
    elif [[ -f "${arg}.cpp" ]]; then
        read_files=("$(realpath --relative-to=. "${arg}.cpp")")
    else
        abort "'${arg}' not found"
    fi
    TEST_FILES+=("${read_files[@]}")
done

popd &>/dev/null

for f in "${TEST_FILES[@]}"; do
    bin="${f%.cpp}.out"
    ft="bin/ft/${bin}"
    std="bin/std/${bin}"
    echo "${ft}"
    echo "${std}"
done

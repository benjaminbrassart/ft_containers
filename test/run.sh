#!/bin/sh

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

. script/func.sh

make -q

SOURCES="$(make dump)"

echo "${SOURCES}"

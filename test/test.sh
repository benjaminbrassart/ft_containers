#!/bin/sh

set -e

CXX="c++"
CXXFLAGS="-Wall -Werror -Wextra"

INCLUDE_PATH_FILE=".include_path"

DIR_SRC="src"
DIR_BIN="bin"
DIR_LOGS="logs"
DIR_DIFF="diff"

RESET="$(tput sgr0)"
RED="$(tput setaf 1)"
GREEN="$(tput setaf 2)"
YELLOW="$(tput setaf 11)"
BLUE="$(tput setaf 12)"

is_absolute() {
    case "$1" in
    /*) return 0 ;;
    *) return 1 ;;
    esac
}

if is_absolute "$0"; then
    REAL_WD="$(dirname "$0")"
else
    SCRIPT_WD="$(dirname "$0")"
    REAL_WD="$(realpath "${PWD}/${SCRIPT_WD}")"
fi

cd "${REAL_WD}" || abort "Failed to compute working directory"

case "$1" in
    clean|fclean)
        rm -rf "${DIR_BIN}" "${DIR_LOGS}" "${DIR_DIFF}";
        exit 0;;
    *) ;;
esac

abort() {
    printf -- "%s\n${RED}Aborted${RESET}\n" "$1" >&2
    exit 1
}

compile() {
    cc="${CXX}"
    cflags="${CXXFLAGS}"

    CONTAINER="$1"
    TEST="$2"
    NAMESPACE="$3"

    INPUT="${DIR_SRC}/${CONTAINER}/${TEST}.cpp"
    OUTPUT="${DIR_BIN}/${CONTAINER}/${TEST}.${NAMESPACE}.out"

    mkdir -p "${DIR_BIN}/${CONTAINER}"

    if [ "${NAMESPACE}" = "std" ]; then
        cflags="${cflags} -D STD"
    fi

    ${cc} ${cflags} "${INPUT}" -o "${OUTPUT}"
}

run() {
    CONTAINER="$1"
    TEST="$2"
    NAMESPACE="$3"

    mkdir -p "${DIR_LOGS}/${CONTAINER}"

    "${DIR_BIN}/${CONTAINER}/${TEST}.${NAMESPACE}.out" \
        1> "${DIR_LOGS}/${CONTAINER}/${TEST}.${NAMESPACE}.stdout.log" \
        2> "${DIR_LOGS}/${CONTAINER}/${TEST}.${NAMESPACE}.stderr.log"
}

check_diff() {
    CONTAINER="$1"
    TEST="$2"

    mkdir -p "${DIR_DIFF}/${CONTAINER}"

    diff \
        "${DIR_LOGS}/${CONTAINER}/${TEST}.ft.stdout.log" \
        "${DIR_LOGS}/${CONTAINER}/${TEST}.std.stdout.log" \
        1> "${DIR_DIFF}/${CONTAINER}/${TEST}.diff" \
        2> /dev/null
}

get_containers() {
    find "${DIR_SRC}" \
        -maxdepth 1 \
        -mindepth 1 \
        -type d \
        -exec basename {} .cpp \; \
    | paste -sd " "
}

now() {
    date +%s%N | cut -b1-16
}

setup() {
    if [ ! -f "${INCLUDE_PATH_FILE}" ]; then
        {
            printf -- 'Please enter your include path, separated by spaces\n'
            printf -- 'Include path: '
        } >&2
        read -r include_path

        for path in ${include_path}; do
            printf -- '-I %s\n' "${path}" >> "${INCLUDE_PATH_FILE}"
        done
    fi
    CXXFLAGS="${CXXFLAGS} $(paste -sd " " < "${INCLUDE_PATH_FILE}")"

    if [ -n "${SEED}" ]; then
        case "${SEED}" in
            *[!0-9]*) abort "Seed must be an unsigned int" ;;
            *) ;;
        esac

        if [ "${#SEED}" -gt 10 ] || [ "${SEED}" -gt 4294967295 ]; then
            abort "Seed is too big"
        fi

        CXXFLAGS="${CXXFLAGS} -D SEED=${SEED}"
    fi
}

setup

CONTAINERS="$(get_containers)"

if [ $# -eq 0 ]; then
    abort "You must supply a container of [${CONTAINERS}]."
elif [ $# -gt 1 ]; then
    abort "You may only supply one container."
fi

for c in ${CONTAINERS}; do
    if [ "${c}" = "$1" ]; then
        container="${c}"
        break
    fi
done

if [ -z "${container}" ]; then
    abort "'$1' is an invalid container."
fi

TESTS="$(find "${DIR_SRC}/${container}" -mindepth 1 -maxdepth 1 -name '*.cpp' -exec basename {} .cpp \;)"

DIFF_OK=0
DIFF_KO=0

for test in ${TESTS}; do
    printf -- "${BLUE}-------------------- %s${RESET}\n" "${test}"
    printf -- "  ${YELLOW}Compilation${RESET}\n"

    printf -- '     ft: '
    if compile "${container}" "${test}" ft; then
        printf -- "${GREEN}[OK]"
    else
        printf -- "${RED}[KO]"
    fi

     printf -- "${RESET}\n"

    printf -- '    std: '
    if compile "${container}" "${test}" std; then
        printf -- "${GREEN}[OK]"
    else
        printf -- "${RED}[KO]"
    fi

    printf -- "${RESET}\n"

    NOW="$(now)"
    run "${container}" "${test}" ft
    TIME_FT="$(now)"
    TIME_FT="$(echo "${TIME_FT} - ${NOW}" | bc)"
    NOW="$(now)"
    run "${container}" "${test}" std
    TIME_STD="$(now)"
    TIME_STD="$(echo "${TIME_STD} - ${NOW}" | bc)"

    printf -- "  ${YELLOW}Diff check: "
    if check_diff "${container}" "${test}"; then
        printf -- "${GREEN}[OK]"
        DIFF_OK="$(echo "${DIFF_OK}" + 1 | bc)"
    else
        printf -- "${RED}[KO]"
        DIFF_OK="$(echo "${DIFF_KO}" + 1 | bc)"
    fi

    printf -- "${RESET}\n"
    printf -- "  ${YELLOW}Time diff: ${RESET}\n"
    printf -- '     ft: %d ns' "${TIME_FT}"
    printf -- '\n'
    printf -- '    std: %d ns' "${TIME_STD}"
    printf -- "${RESET}\n\n"
done

DIFF_TOTAL="$(echo "${DIFF_OK} + ${DIFF_KO}" | bc)"

if [ "${DIFF_KO}" -eq 0 ]; then
    DIFF_RATIO=100
else
    DIFF_RATIO="$(echo "${DIFF_OK} * 100 / ${DIFF_KO}" | bc)"
fi

if [ "${DIFF_RATIO}" -lt 33 ]; then
    RATIO_COLOR="${RED}"
elif [ "${DIFF_RATIO}" -lt 66 ]; then
    RATIO_COLOR="${YELLOW}"
else
    RATIO_COLOR="${GREEN}"
fi

printf -- "${YELLOW}Result: ${GREEN}%d ${YELLOW}/ ${RED}%d ${YELLOW}/ ${BLUE}%d ${YELLOW}| ${RATIO_COLOR}%d%% \n${RESET}" \
    "${DIFF_OK}" \
    "${DIFF_KO}" \
    "${DIFF_TOTAL}" \
    "${DIFF_RATIO}"

#!/bin/sh

abort() {
    printf -- "Aborted: %sAborted\n" "$1" >&2
    exit 1
}

upper() {
    echo "$1" | awk '{ print toupper($0) }'
}

now() {
    date +%s%N | cut -b1-16
}

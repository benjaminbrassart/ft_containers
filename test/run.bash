#!/bin/bash

RESET="$(tput sgr0)"
RED="$(tput setaf 1)"
GREEN="$(tput setaf 2)"

set -e

make -q all

dump="$(make dump)"
test_files="${dump// /$'\n'}"

readarray -t test_files <<< "${dump// /$'\n'}"

set +e

for test in "${test_files[@]}"; do
  test_name="${test%.cpp}"
  bin_ft="bin/ft/${test_name}.out"
  bin_std="bin/std/${test_name}.out"

  echo -n "${test_name}: "

  res_ft="$(${bin_ft})"
  res_std="$(${bin_std})"

  echo -n "DIFF "

  if diff -q <(echo "${res_ft}") <(echo "${res_std}"); then
    echo -n "${GREEN}[OK]"
  else
    echo -n "${RED}[KO]"
  fi
  echo "${RESET}"
done

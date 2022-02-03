#!/bin/bash

# to get csvcut
# shellcheck source=../venv/bin/activate
source ../venv/bin/activate


# get final instance, score and solution from given file
old_ifs=$IFS
IFS=,
read -r instance score solution < <(csvcut -c instance,score,solution "$1" | tail -n 1)
IFS=$old_ifs

cd ../instances || exit

if ! python3 check_solution.py "$instance" "$score" "$solution";
then
    echo "Error : $1"
fi

#!/bin/bash

if [ $# -lt 1 ]; then
    echo "Usage: $0 [OPTIONS] file1 file2 ..."
    echo ""
    echo "Options:"
    echo "  -c      will run \"make clean && make\" before running the assembler program"
    echo "  -m      will run \"make\" before running the assembler program"
    echo "  -t      will run \"make tests\" before running the assembler program"
    exit 1
fi

for arg in ${@};
do
    if [[ "${arg}" =~ "-" ]]; then
        if [[ "${arg}" =~ "c" ]]; then
            make clean
        fi
        if [[ "${arg}" =~ "m" ]]; then
            make
        fi
        if [[ "${arg}" =~ "t" ]]; then
            make tests
        fi
    else 
        if [[ ! -f ./assembler ]]; then
            make
        fi

        ./assembler "${arg}"
        exit 0
    fi

    shift 
done

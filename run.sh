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
        if [[ "${arg}" =~ "tr" ]]; then
            make tests
            tests=$(find . -name "*test")
            mkdir -p ./test_logs
            for test in ${tests}; do
                if [[ ! -x ${test} ]]; then
                    continue
                fi
                log_file="./test_logs/${test}.log"
                echo "Running test: ${test}..." > ${log_file}
                echo "" >> ${log_file}
                eval "./${test} &>> ${log_file}"
                echo "" >> ${log_file}
                echo "" >> ${log_file}
                if [[ $? -eq 0 ]]; then
                    echo '------------' >> ${log_file}
                    echo 'Test passed!' >> ${log_file}
                    echo '------------' >> ${log_file}
                else
                    echo '------------' >> ${log_file}
                    echo 'Test failed!' >> ${log_file}
                    echo '------------' >> ${log_file}
                fi
            done
            exit
        elif [[ "${arg}" =~ "t" ]]; then
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

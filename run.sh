#!/bin/bash

assembler_executable=assembler

# Utility Variables
now=$(date +%H_%M)
today=$(date +%Y-%m-%d)

# Path Variables
build_dir="./build"
source_dir="./src"
example_dir="./examples"
logging_directory="./logs/${today}/${now}"


# =============================================================================
# Functions
# =============================================================================

function invoke_action_by_option {
    if [[ $1 =~ "c" ]]; then
        clean_previous_build
    fi
    if [[ $1 =~ "m" ]]; then
        build_executable
    fi
    if [[ $1 =~ "t" ]]; then
        build_tests
    fi
    if [[ $1 =~ "tr" ]]; then
        run_tests
    fi
}

function run_assembler {
    if [[ ! -f "./${assembler_executable}" ]]; then
        clean_previous_build
        build_executable
    fi

    eval "./${assembler_executable} $1"
}

# --------------
# Option Actions
# --------------

function clean_previous_build {
    make clean
}

function build_executable {
    make
}

function build_tests {
    make tests
}

function run_tests {
    init_logging_prerequisites

    tests=(./*test)
    for test in ${tests[@]}; do
        test_log="${logging_directory}/$(basename test).log"
        log_pre_run_info ${test} ${test_log}
        run_test ${test} ${test_log}
        log_post_run_info ${test} ${test_log}
    done
}

function init_logging_prerequisites {
    eval "mkdir -p ${logging_directory}"
}

function get_test_list {
    return ./*test
}

function log_pre_run_info {
    echo -e "Running test: ${1}...\n\n" &> ${2}
}

function run_test {
    eval "${1} &>> ${2}"
}

function log_post_run_info {
    sep=$(printf '=%.0s' {1..79})

    echo -e "\n\n${sep}" &>> ${2}
    if ${1}; then
        echo -e "Test ${1} passed!" &>> ${2}
    else
        echo -e "Test failed!" &>> ${2}
    fi
    echo -e "${sep}\n\n" &>> ${2}

}

# -----------------
# Boolean Functions
# -----------------

function is_option {
    if [[ "$1" =~ "-" ]]; then
        return 0
    else
        return 1
    fi
}

function is_script_missing_args {
    if [[ $# -lt 1 ]]; then
        return 0
    else
        return 1
    fi
}

# ---------------
# Print Functions
# ---------------

function print_usage {
    echo "Usage: $0 [OPTIONS] file1 file2 ..."
    echo ""
    echo "Options:"
    echo "-c      will run \"make clean && make\" before running the assembler program"
    echo "-m      will run \"make\" before running the assembler program"
    echo "-t      will run \"make tests\" before running the assembler program"
    echo "-tr     will build and run all available tests, results are saved under test_results/<test_name>.log"
    echo ""
}

# =============================================================================
# Main
# =============================================================================

if is_script_missing_args $@; then
    print_usage
    exit 1
fi

for arg in ${@}; do
    if is_option ${arg}; then
        invoke_action_by_option ${arg}
    else
        run_assembler ${arg}
    fi
    shift
done


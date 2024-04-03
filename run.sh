#!/bin/bash

assembler_executable=assembler

# Utility Variables
# now=$(date +%H)
# today=$(date +%Y-%m-%d)

# Path Variables
output_directory="outputs"
logging_directory=$(printf "%s/logs" ${output_directory})


# =============================================================================
# Functions
# =============================================================================

function invoke_action_by_option {
    if [[ $1 =~ "c" ]]; then
        echo
        clean_previous_build
    fi
    if [[ $1 =~ "m" ]]; then
        echo
        build_executable
    fi
    if [[ $1 =~ "t" ]]; then
        echo
        build_tests
    fi
    if [[ $1 =~ "tr" ]]; then
        echo
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
    setup_prerequisites

    tests=$(find . -type f -executable -name "*test*" -print0 | xargs -0 basename -a)
    for test in ${tests}; do
        test_log=$(printf "%s/%s.log" "${logging_directory}" "${test}")
        run_test "${test}" "${test_log}"
    done
}

function setup_prerequisites {
    eval "mkdir -p ${logging_directory}"
}

function run_test {
    report_pre_run_info "${test}"
    eval "./${test}"
    report_run_result
    report_post_run_info "${test}" "${test_log}"
}

function report_pre_run_info {
    info "Test Started." "${test}"
}

function report_post_run_info {
    info "Log saved to \"${test_log}\"" "${test}"
    info "Test Ended.\n" "${test}"
}

function report_run_result {
    if [ $? -eq 0 ]; then
        print_header "Test passed!"
    else
        print_header "Test failed!"
    fi
}

function print_header {
    header="${1}"
    sep=$(printf "=%.0s" {1..80})
    text=$(printf "%s\n%s\n%s" "${sep}" "${header}" "${sep}")
    echo "${text}"
}

function info {
    if [ $# -ge 1 ]; then
        info=${1:-""}
        reporter=${2:-"General"}
        echo -e "[INFO] (${reporter}): ${info}"
    fi
}

function error {
    if [ $# -ge 1 ]; then
        error=${1:-""}
        reporter=${2:-"General"}
        echo -e "[ERROR] (${reporter}): ${error}"
    fi
    return 1
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

function main {
    if is_script_missing_args "${@}"; then
        print_usage
        exit 1
    fi

    for arg in "${@}"; do
        if is_option "${arg}"; then
            invoke_action_by_option "${arg}"
        else
            run_assembler "${arg}"
        fi
        shift
    done
    exit 0
}

log=$(printf "%s/run.log" "${logging_directory}")
main "${@}"

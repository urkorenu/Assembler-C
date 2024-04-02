#!/bin/bash

assembler_executable=assembler

# Utility Variables
now=$(date +%H)
today=$(date +%Y-%m-%d)

# Path Variables
logging_directory=$(printf "./logs/%.s/%.s" ${today} ${now})


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

    tests=$(find . -type f -executable -name "*test" -print)
    for test in ${tests}; do
        test_log=$(printf "./%.s/%.s.log" ${logging_directory} $(basename ${test}))
        log_pre_run_info ${test} ${test_log}
        run_test ${test} ${test_log}
        log_post_run_info ${test} ${test_log}
    done
}

function init_logging_prerequisites {
    eval "mkdir -p ${logging_directory}"
}

function log_pre_run_info {
    echo -e "Running test: ${test}...\n\n" > ${test_log}
}

function run_test {
    eval "${test}" >> ${test_log}
}

function log_post_run_info {
    sep=$(printf '=%.0s' {1..79})

    echo -e "\n\n${sep}" >> ${test_log}
    if ${1}; then
        echo -e "Test ${test} passed!" >> ${test_log}
    else
        echo -e "Test ${test} failed!" >> ${test_log}
    fi
    echo -e "\n\n${sep}" >> ${test_log}

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


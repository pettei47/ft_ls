#!bin/bash

TESTS_DIR="tests/unit_tests"

bash ${TESTS_DIR}/no_args.sh
bash ${TESTS_DIR}/option_a.sh
bash ${TESTS_DIR}/option_l.sh
bash ${TESTS_DIR}/option_LargeR.sh
bash ${TESTS_DIR}/option_r.sh
bash ${TESTS_DIR}/option_s.sh
bash ${TESTS_DIR}/option_t.sh
bash ${TESTS_DIR}/all_options.sh
bash ${TESTS_DIR}/invalid_option.sh
bash ${TESTS_DIR}/invalid_args_order.sh
bash ${TESTS_DIR}/multiple_dirs.sh
bash ${TESTS_DIR}/multiple_dirs_with_r.sh
bash ${TESTS_DIR}/give_file.sh

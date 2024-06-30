#!/bin/bash

TEST_DIR="tests"
TEST_DATA_DIR="${TEST_DIR}/test_data"
OUTPUTS_DIR="../outputs"
EXPECTS_DIR="../expects"
LOGS_DIR="../logs"

cd ${TEST_DATA_DIR}
../../ft_ls > ${OUTPUTS_DIR}/no_args_output
diff ${OUTPUTS_DIR}/no_args_output ${EXPECTS_DIR}/no_args > ${LOGS_DIR}/no_args.log
if [ $? -eq 0 ]; then
  echo -n "[PASS]"
else
  echo -n "[FAIL]"
fi
echo ": test 'no_args'"
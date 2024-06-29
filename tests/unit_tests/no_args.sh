#!/bin/bash

TEST_DIR="tests"
TEST_DATA_DIR="${TEST_DIR}/test_data"
OUTPUTS_DIR="../outputs"
EXPECTS_DIR="../expects"
LOGS_DIR="../logs"

echo -n "test 'no_args': "
cd ${TEST_DATA_DIR}
../../ft_ls > ${OUTPUTS_DIR}/no_args_output
diff ${OUTPUTS_DIR}/no_args_output ${EXPECTS_DIR}/no_args > ${LOGS_DIR}/no_args.log
if [ $? -eq 0 ]; then
  echo "[PASS]"
else
  echo "[FAIL]"
fi

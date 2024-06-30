#!/bin/bash

TEST_DIR="tests"
TEST_DATA_DIR="${TEST_DIR}/test_data"
OUTPUTS_DIR="../outputs"
EXPECTS_DIR="../expects"
LOGS_DIR="../logs"

cd ${TEST_DATA_DIR}
../../ft_ls -a > ${OUTPUTS_DIR}/option_a_output
diff ${OUTPUTS_DIR}/option_a_output ${EXPECTS_DIR}/option_a > ${LOGS_DIR}/option_a.log
if [ $? -eq 0 ]; then
  echo -n "[PASS]"
else
  echo -n "[FAIL]"
fi
echo ": test 'option_a'"

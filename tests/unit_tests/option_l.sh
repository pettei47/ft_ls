#!/bin/bash

TEST_DIR="tests"
TEST_DATA_DIR="${TEST_DIR}/test_data"
OUTPUTS_DIR="../outputs"
EXPECTS_DIR="../expects"
LOGS_DIR="../logs"

cd ${TEST_DATA_DIR}
../../ft_ls -l > ${OUTPUTS_DIR}/option_l_output
diff ${OUTPUTS_DIR}/option_l_output ${EXPECTS_DIR}/option_l > ${LOGS_DIR}/option_l.log
if [ $? -eq 0 ]; then
  echo -n "[PASS]"
else
  echo -n "[FAIL]"
fi
echo ": test 'option_l'"

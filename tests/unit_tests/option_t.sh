#!/bin/bash

TEST_NAME="option_t"
TEST_DIR="tests"
TEST_DATA_DIR="${TEST_DIR}/test_data"
OUTPUTS_DIR="../outputs"
EXPECTS_DIR="../expects"
LOGS_DIR="../logs"

OPTION="-t"

cd ${TEST_DATA_DIR}
../../ft_ls ${OPTION} &> ${OUTPUTS_DIR}/${TEST_NAME}_output
diff ${OUTPUTS_DIR}/${TEST_NAME}_output ${EXPECTS_DIR}/${TEST_NAME} > ${LOGS_DIR}/${TEST_NAME}.log
if [ $? -eq 0 ]; then
  echo -n "[PASS]"
else
  echo -n "-FAIL-"
fi
echo " test: ${TEST_NAME}"

if [ ${SKIP_LEAK_CHECK} ]; then
  exit 0
fi

leaks -q -atExit -- ../../ft_ls ${OPTION} &> ${LOGS_DIR}/${TEST_NAME}_leaks.log
if [ $? -eq 0 ]; then
  echo -n "[PASS]"
else
  echo -n "-FAIL-"
fi
echo " test: ${TEST_NAME} leak check"

#!/bin/bash

TEST_NAME="option_r"
TEST_DIR="tests"
TEST_DATA_DIR="${TEST_DIR}/test_data"
OUTPUTS_DIR="../outputs"
EXPECTS_DIR="../expects"
LOGS_DIR="../logs"

OPTION="-r"

cd ${TEST_DATA_DIR}
../../ft_ls ${OPTION} &> ${OUTPUTS_DIR}/${TEST_NAME}_output
diff ${OUTPUTS_DIR}/${TEST_NAME}_output ${EXPECTS_DIR}/${TEST_NAME} > ${LOGS_DIR}/${TEST_NAME}.log
if [ $? -eq 0 ]; then
  echo -n "[PASS]"
else
  echo -n "[FAIL]"
fi
echo " test: ${TEST_NAME}"

leaks -q -atExit -- ../../ft_ls ${OPTION} &> ${LOGS_DIR}/${TEST_NAME}_leaks.log
if [ $? -eq 0 ]; then
  echo -n "[PASS]"
else
  echo -n "[FAIL]"
fi
echo " test: ${TEST_NAME} leak check"

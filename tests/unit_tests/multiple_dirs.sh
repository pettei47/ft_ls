#!/bin/bash

TEST_NAME="multiple_dirs"
TEST_DIR="tests"
TEST_DATA_DIR="${TEST_DIR}/test_data"
OUTPUTS_DIR="../outputs"
EXPECTS_DIR="../expects"
LOGS_DIR="../logs"

FAILED=0

cd ${TEST_DATA_DIR}
ls testdir . z x y &> ${EXPECTS_DIR}/${TEST_NAME}
../../ft_ls testdir . z x y &> ${OUTPUTS_DIR}/${TEST_NAME}_output
diff ${OUTPUTS_DIR}/${TEST_NAME}_output ${EXPECTS_DIR}/${TEST_NAME} > ${LOGS_DIR}/${TEST_NAME}.log
if [ $? -eq 0 ]; then
  echo -n "[PASS]"
else
  echo -n "-FAIL-"
  FAILED=1
fi
echo " test: ${TEST_NAME}"

if [ ${SKIP_LEAK_CHECK} ]; then
  exit ${FAILED}
fi

leaks -q -atExit -- ../../ft_ls testdir . z x y &> ${LOGS_DIR}/${TEST_NAME}_leaks.log
if [ $? -eq 0 ]; then
  echo -n "[PASS]"
else
  echo -n "-FAIL-"
  FAILED=1
fi
echo " test: ${TEST_NAME} leak check"

exit ${FAILED}

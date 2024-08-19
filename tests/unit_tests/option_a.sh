#!/bin/bash

TEST_NAME="option_a"
TEST_DIR="tests"
TEST_DATA_DIR="${TEST_DIR}/test_data"
OUTPUTS_DIR="../outputs"
EXPECTS_DIR="../expects"
LOGS_DIR="../logs"

OPTION="-a"

FAILED=0

cd ${TEST_DATA_DIR}

if [ ${LEAK_CHECK_ONLY} ]; then
  SKIP_LEAK_CHECK=
else
  ls ${OPTION} &> ${EXPECTS_DIR}/${TEST_NAME}
  ../../ft_ls ${OPTION} &> ${OUTPUTS_DIR}/${TEST_NAME}_output
  diff ${OUTPUTS_DIR}/${TEST_NAME}_output ${EXPECTS_DIR}/${TEST_NAME} > ${LOGS_DIR}/${TEST_NAME}.log
  if [ $? -eq 0 ]; then
    rm ${LOGS_DIR}/${TEST_NAME}.log
    echo -n "[PASS]"
  else
    echo -n "-FAIL-"
    FAILED=1
  fi
  echo " test: ${TEST_NAME}"

  if [ ${SKIP_LEAK_CHECK} ]; then
    exit ${FAILED}
  fi
fi

valgrind --log-file="${LOGS_DIR}/${TEST_NAME}_leaks.log" --leak-check=full --error-exitcode=1 ../../ft_ls ${OPTION} &> /dev/null
if [ $? -eq 0 ]; then
  rm ${LOGS_DIR}/${TEST_NAME}_leaks.log
  echo -n "[PASS]"
else
  echo -n "-FAIL-"
  FAILED=1
fi
echo " test: ${TEST_NAME} leak check"

exit ${FAILED}

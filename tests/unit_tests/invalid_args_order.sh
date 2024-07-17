#!/bin/bash

TEST_NAME="invalid_args_order"
TEST_DIR="tests"
TEST_DATA_DIR="${TEST_DIR}/test_data"
OUTPUTS_DIR="../outputs"
EXPECTS_DIR="../expects"
LOGS_DIR="../logs"

OPTION="-l"

FAILED=0

cd ${TEST_DATA_DIR}
ls ${OPTION} testdir &> ${EXPECTS_DIR}/${TEST_NAME}
../../ft_ls testdir ${OPTION} &> ${OUTPUTS_DIR}/${TEST_NAME}_output
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

valgrind --log-file="${LOGS_DIR}/${TEST_NAME}_leaks.log" --leak-check=full --error-exitcode=2 ../../ft_ls testdir ${OPTION} &> /dev/null
if [ $? -eq 0 ]; then
  echo -n "[PASS]"
else
  echo -n "-FAIL-"
  FAILED=1
fi
echo " test: ${TEST_NAME} leak check"

exit ${FAILED}

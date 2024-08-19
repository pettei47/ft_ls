#!/bin/bash

TEST_NAME="option_LargeR_with_no_permission_dir"
TEST_DIR="tests"
TEST_DATA_DIR="${TEST_DIR}/test_data"
OUTPUTS_DIR="../outputs"
EXPECTS_DIR="../expects"
LOGS_DIR="../logs"

OPTION="-R"

FAILED=0

cd ${TEST_DATA_DIR}
mkdir no_permission_dir
chmod 000 no_permission_dir

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
    chmod 644 no_permission_dir
    rm -rf no_permission_dir
    touch -t 204201011200.00 .
    touch -t 204201021200.00 ..
    exit ${FAILED}
  fi
fi

valgrind --log-file="${LOGS_DIR}/${TEST_NAME}_leaks.log" --leak-check=full --error-exitcode=2 ../../ft_ls ${OPTION} &> /dev/null
if [ $? -eq 1 ]; then
  rm ${LOGS_DIR}/${TEST_NAME}_leaks.log
  echo -n "[PASS]"
else
  echo -n "-FAIL-"
  FAILED=1
fi
chmod 644 no_permission_dir
rm -rf no_permission_dir
touch -t 204201011200.00 .
touch -t 204201021200.00 ..
echo " test: ${TEST_NAME} leak check"

exit ${FAILED}

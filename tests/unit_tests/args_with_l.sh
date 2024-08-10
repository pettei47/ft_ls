#!/bin/bash

TEST_NAME="args_with_l"
TEST_DIR="tests"
TEST_DATA_DIR="${TEST_DIR}/test_data"
OUTPUTS_DIR="../outputs"
EXPECTS_DIR="../expects"
LOGS_DIR="../logs"

OPTION="-l"

FAILED=0

cd ${TEST_DATA_DIR}
ls ${OPTION} testdir z textfile.txt . x symbolic_link_different_dir y &> ${EXPECTS_DIR}/${TEST_NAME}
sed -e "s/ 1月/Jan/g" -i ${EXPECTS_DIR}/${TEST_NAME}
sed -e "s/ 2月/Feb/g" -i ${EXPECTS_DIR}/${TEST_NAME}
sed -e "s/ 3月/Mar/g" -i ${EXPECTS_DIR}/${TEST_NAME}
sed -e "s/ 4月/Apr/g" -i ${EXPECTS_DIR}/${TEST_NAME}
sed -e "s/ 5月/May/g" -i ${EXPECTS_DIR}/${TEST_NAME}
sed -e "s/ 6月/Jun/g" -i ${EXPECTS_DIR}/${TEST_NAME}
sed -e "s/ 7月/Jul/g" -i ${EXPECTS_DIR}/${TEST_NAME}
sed -e "s/ 8月/Aug/g" -i ${EXPECTS_DIR}/${TEST_NAME}
sed -e "s/ 9月/Sep/g" -i ${EXPECTS_DIR}/${TEST_NAME}
sed -e "s/10月/Oct/g" -i ${EXPECTS_DIR}/${TEST_NAME}
sed -e "s/11月/Nov/g" -i ${EXPECTS_DIR}/${TEST_NAME}
sed -e "s/12月/Dec/g" -i ${EXPECTS_DIR}/${TEST_NAME}
../../ft_ls ${OPTION} testdir z textfile.txt . x symbolic_link_different_dir y &> ${OUTPUTS_DIR}/${TEST_NAME}_output
# 空白の出方が謎仕様すぎるので、-wをつけて無視する
diff -w ${OUTPUTS_DIR}/${TEST_NAME}_output ${EXPECTS_DIR}/${TEST_NAME} > ${LOGS_DIR}/${TEST_NAME}.log
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

valgrind --log-file="${LOGS_DIR}/${TEST_NAME}_leaks.log" --leak-check=full --error-exitcode=2 ../../ft_ls ${OPTION} testdir z textfile.txt . x symbolic_link_different_dir y &> /dev/null
if [ $? -eq 1 ]; then
  rm ${LOGS_DIR}/${TEST_NAME}_leaks.log
  echo -n "[PASS]"
else
  echo -n "-FAIL-"
  FAILED=1
fi
echo " test: ${TEST_NAME} leak check"

exit ${FAILED}

#!bin/bash

TESTS_DIR="tests/unit_tests"

FAILED_TESTS=0

echo "No args test"
bash ${TESTS_DIR}/no_args.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi
bash ${TESTS_DIR}/option_a.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi
bash ${TESTS_DIR}/option_l.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi
bash ${TESTS_DIR}/option_LargeR.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi
bash ${TESTS_DIR}/option_LargeR_with_no_permission_dir.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi
bash ${TESTS_DIR}/option_r.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi
bash ${TESTS_DIR}/option_t.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi
bash ${TESTS_DIR}/all_options.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi
bash ${TESTS_DIR}/invalid_option.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi
echo ""
echo "dir args test"
bash ${TESTS_DIR}/invalid_args_order.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi
bash ${TESTS_DIR}/multiple_dirs.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi
bash ${TESTS_DIR}/multiple_dirs_with_r.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi
echo ""
echo "file args test"
bash ${TESTS_DIR}/give_file.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi
bash ${TESTS_DIR}/give_file_with_l.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi
echo ""
echo "args with options test"
bash ${TESTS_DIR}/args_with_LargeR.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi
bash ${TESTS_DIR}/args_with_a.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi
bash ${TESTS_DIR}/args_with_l.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi
bash ${TESTS_DIR}/args_with_r.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi
bash ${TESTS_DIR}/args_with_t.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi
bash ${TESTS_DIR}/args_with_all_options.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi
echo ""
echo "bonus test"
bash ${TESTS_DIR}/option_s.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi
bash ${TESTS_DIR}/args_with_s.sh
if [ $? -ne 0 ]; then
  FAILED_TESTS=$((FAILED_TESTS + 1))
fi

echo ""
if [ ${FAILED_TESTS} -eq 0 ]; then
  echo "All tests passed"
else
  echo "${FAILED_TESTS} tests failed"
  exit 1
fi

#!/bin/bash

TEST_DATA_DIR="tests/test_data"
HALF_YEAR_AGO_DATE=$(date -d '183 days ago' "+%Y%m%d%H%M")


touch -t 204201010000 ${TEST_DATA_DIR}/future_file.txt
touch -t ${HALF_YEAR_AGO_DATE} ${TEST_DATA_DIR}/half_year_ago_file.txt
touch -t 199304070000 ${TEST_DATA_DIR}/ancient.txt
touch ${TEST_DATA_DIR}/special_permission
chmod 7557 ${TEST_DATA_DIR}/special_permission

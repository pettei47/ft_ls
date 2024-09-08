#!/bin/bash

TEST_DATA_DIR="tests/test_data"
HALF_YEAR_AGO=$(date -d '183 days ago' "+%Y%m%d%H%M")

cd ${TEST_DATA_DIR}
touch -t 204201010000 future_file.txt
touch -t ${HALF_YEAR_AGO} half_year_ago_file.txt
touch -t 199304070000 ancient.txt
touch special_permission
chmod 7557 special_permission
mkdir ascii_dir
cd ascii_dir
touch a b c d e f g h i j k l m n o p q r s t u v w x y z \
      A B C D E F G H I J K L M N O P Q R S T U V W X Y Z \
      0 1 2 3 4 5 6 7 8 9

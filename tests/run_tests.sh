#!/usr/bin/env bash

echo -e "\n[SERVER OUTPUT]\n"
./unit_tests 6969 . debug & pid=$!;
echo -e "SERVER PID: $pid\n"
python -B tests/test.py | sed  's/^/[CLIENT OUTPUT] /'
echo -e "\n"
kill -SIGINT $pid
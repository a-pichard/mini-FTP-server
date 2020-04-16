#!/usr/bin/env bash
./unit_tests 6969 . debug & pid=$!
python -B tests/test.py
kill -SIGINT $pid
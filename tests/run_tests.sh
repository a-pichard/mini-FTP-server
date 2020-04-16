#!/usr/bin/env bash
./unit_tests 6969 . debug & pid=$!
tests/test.py
kill -SIGINT $pid
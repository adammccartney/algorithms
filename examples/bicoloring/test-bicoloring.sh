#!/usr/bin/sh

if ! [[ -x bicoloring ]]; then
    echo "bicoloring executable does not exist"
    exit 1
fi

../tester/run-tests.sh $*

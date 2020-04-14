#!/bin/bash

strace -o firstStats ./first
strace -o secondStats ./second

READ_FIRST=$(grep -w 'read' firstStats | wc -l)
WRITE_FIRST=$(grep -w 'write' firstStats | wc -l)

READ_SECOND=$(grep -w 'read' secondStats | wc -l)
WRITE_SECOND=$(grep -w 'write' secondStats | wc -l)

echo -e "Program\t#reads\t#writes"
echo -e "---------------------------------"
echo -e "first\t$READ_FIRST\t$WRITE_FIRST"
echo -e "second\t$READ_SECOND\t$WRITE_SECOND"

rm firstStats secondStats

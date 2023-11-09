#!/bin/bash
#File: codeTester1
#Author: Eric Anson
#Purpose: A very simple file to test assignments

testFiles=$(ls testcases/test*)
for file in $testFiles
do
  mymake <$file >myOut 2>myErr
  echo $? >>myOut
  exMymake <$file >exOut 2>exErr
  echo $? >>exOut
  echo Test File $file
  echo stdout diffs:
  diff myOut exOut
  echo stderr diffs:
  diff myErr exErr
done

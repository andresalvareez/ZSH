#!/bin/bash

function compile()
{
  local dir="$1"
  echo "Compiling $dir"
  gcc $dir -o $dir.out
  echo "Running $dir"
  ./$dir.out
  echo "Removing $dir.out"
  rm $dir.out
  
}

compile $1

#!/bin/bash


while [ 1 == 1 ] ; do
  ./camerastatus $*
  if [ $? == 0 ] ; then
    break;
  fi

done

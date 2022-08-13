#!/bin/bash
DIR=$(dirname $0)
CPP=$1
EXE=${1%.*}
case "$(uname -s)" in
Darwin)
  PARUNNER=parunner.macos
;;
Linux)
  PARUNNER=parunner.linux
;;
CYGWIN*|MINGW32*|MSYS*)
  PARUNNER=parunner.exe
;;
*)
  echo 'Unsupported OS'
  exit 1
;;
esac

g++ -O2 -std=gnu++17 -lm -static \
  -I${DIR}/lib -I${DIR} \
  ${DIR}/lib/zeus_local.o \
  ${DIR}/lib/message_internal.o \
  $CPP -o $EXE

${DIR}/${PARUNNER} --n 2 --stdout tagged --stderr tagged ${EXE}


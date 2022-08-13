#!/bin/bash

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
PARUNNER_DIR=parunner.build

function die() {
  echo $@
  exit 1
}

set +x
git clone https://github.com/robryk/parunner.git ${PARUNNER_DIR} || die "git clone failed"
g++ -c -O2 -g ${PARUNNER_DIR}/zeus/zeus_local.c -o lib/zeus_local.o || die "zeus buld failed"
g++ -c -O2 -I${PARUNNER_DIR}/zeus -g ${PARUNNER_DIR}/message/message_internal.c -o lib/message_internal.o || "message build failed"
cp ${PARUNNER_DIR}/message/message.h lib/ || die "message.h copy failed"
pushd ${PARUNNER_DIR}
go build -o ../${PARUNNER} || die "build parunner failed"
popd
rm -rf ${PARUNNER_DIR}

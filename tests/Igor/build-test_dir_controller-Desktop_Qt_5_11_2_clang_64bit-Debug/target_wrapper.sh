#!/bin/sh
DYLD_FRAMEWORK_PATH=/Volumes/Macintosh_Hard/Qt/5.11.2/clang_64/lib${DYLD_FRAMEWORK_PATH:+:$DYLD_FRAMEWORK_PATH}
export DYLD_FRAMEWORK_PATH
QT_PLUGIN_PATH=/Volumes/Macintosh_Hard/Qt/5.11.2/clang_64/plugins${QT_PLUGIN_PATH:+:$QT_PLUGIN_PATH}
export QT_PLUGIN_PATH
exec "$@"

#!/usr/bin/env bash
set -eo pipefail
VERSION=2.1
##########################################################################
# This is the MOS automated install script for Linux and Mac OS.
# This file was downloaded from https://github.com/mos/mos
#
# Copyright (c) 2017, Respective Authors all rights reserved.
#
# After June 1, 2018 this software is available under the following terms:
#
# The MIT License
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
# https://github.com/mos/mos/blob/master/LICENSE.txt
##########################################################################

# Ensure we're in the repo root and not inside of scripts
cd $( dirname "${BASH_SOURCE[0]}" )/..

# Load mos specific helper functions
. ./scripts/helpers/mos.sh

[[ ! $NAME == "Ubuntu" ]] && set -i # Ubuntu doesn't support interactive mode since it uses dash

[[ ! -f ${BUILD_DIR}/CMakeCache.txt ]] && printf "${COLOR_RED}Please run ${SCRIPT_DIR}/mos_build.sh first!${COLOR_NC}" && exit 1
echo "${COLOR_CYAN}====================================================================================="
echo "========================== ${COLOR_WHITE}Starting MOS Installation${COLOR_CYAN} ==============================${COLOR_NC}"
execute cd $BUILD_DIR
execute make install
execute cd ..

printf "\n${COLOR_RED}"
printf "       ___           ___           ___     \n"
printf "      /__/\         /  /\         /  /\    \n"
printf "     |  |::\       /  /::\       /  /:/_   \n"
printf "     |  |:|:\     /  /:/\:\     /  /:/ /\  \n"
printf "   __|__|:|\:\   /  /:/  \:\   /  /:/ /::\ \n"
printf "  /__/::::| \:\ /__/:/ \__\:\ /__/:/ /:/\:\\n"
printf "  \  \:\~~\__\/ \  \:\ /  /:/ \  \:\/:/~/:/\n"
printf "   \  \:\        \  \:\  /:/   \  \::/ /:/ \n"
printf "    \  \:\        \  \:\/:/     \__\/ /:/  \n"
printf "     \  \:\        \  \::/        /__/:/   \n"
printf "      \__\/         \__\/         \__\/    \n"
printf "${COLOR_NC}"



printf "==============================================================================================\\n"
printf "${COLOR_GREEN}MOS has been installed into ${CACHED_INSTALL_PATH}/bin${COLOR_NC}"
printf "\\n${COLOR_YELLOW}Uninstall with: ${SCRIPT_DIR}/mos_uninstall.sh${COLOR_NC}\\n"
printf "==============================================================================================\\n\\n"
resources

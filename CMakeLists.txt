# This file is part of Telegram Desktop,
# the official desktop application for the Telegram messaging service.
#
# For license and copyright information please follow this link:
# https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL

cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0076 NEW)
cmake_policy(SET CMP0091 NEW)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(DESKTOP_APP_DISABLE_CRASH_REPORTS TRUE)

include(cmake/validate_special_target.cmake)
include(cmake/version.cmake)
desktop_app_parse_version(Telegram/build/version)

project(Telegram
    LANGUAGES C CXX
    VERSION ${desktop_app_version_cmake}
    DESCRIPTION "Official Telegram Desktop messenger"
    HOMEPAGE_URL "https://desktop.telegram.org"
)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Telegram)

get_filename_component(third_party_loc "Telegram/ThirdParty" REALPATH)
get_filename_component(submodules_loc "Telegram" REALPATH)

set(DESKTOP_APP_DISABLE_SPELLCHECK TRUE)
include(cmake/variables.cmake)

set(TDESKTOP_API_TEST TRUE)
set(DESKTOP_APP_DISABLE_AUTOUPDATE TRUE)
set(DESKTOP_APP_DISABLE_CRASH_REPORTS TRUE)
set(DESKTOP_APP_DISABLE_DBUS_INTEGRATION TRUE)
set(DESKTOP_APP_USE_PACKAGED_EXPECTED FALSE)
set(DESKTOP_APP_USE_PACKAGED_GSL FALSE)
set(DESKTOP_APP_USE_PACKAGED_RLOTTIE FALSE)
set(DESKTOP_APP_USE_PACKAGED_VARIANT FALSE)
set(TDESKTOP_USE_PACKAGED_TGVOIP FALSE)

include(cmake/nice_target_sources.cmake)
include(cmake/target_link_static_libraries.cmake)
include(cmake/target_link_frameworks.cmake)
include(cmake/init_target.cmake)
include(cmake/generate_target.cmake)

include(cmake/options.cmake)

include(cmake/external/qt/package.cmake)

add_subdirectory(cmake)
add_subdirectory(Telegram)

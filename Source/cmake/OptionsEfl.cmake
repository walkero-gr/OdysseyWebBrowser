set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 18)
set(PROJECT_VERSION_MICRO 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_MICRO})

set(ENABLE_WEBKIT OFF)
set(ENABLE_WEBKIT2 ON)

# FIXME: Disable WERROR in clang build because of many warnings.
if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(ADDITIONAL_COMPILER_FLAGS ENABLE_WERROR)
endif ()

set(USE_SOUP 1)

set(WTF_LIBRARY_TYPE STATIC)
set(WTF_OUTPUT_NAME wtf_efl)
set(JavaScriptCore_OUTPUT_NAME javascriptcore_efl)
set(WebCore_OUTPUT_NAME webcore_efl)
set(WebKit2_OUTPUT_NAME ewebkit2)
set(WebKit2_WebProcess_OUTPUT_NAME WebKitWebProcess)
set(WebKit2_NetworkProcess_OUTPUT_NAME WebKitNetworkProcess)
set(WebKit2_PluginProcess_OUTPUT_NAME WebKitPluginProcess)
set(WebKit2_DatabaseProcess_OUTPUT_NAME WebKitDatabaseProcess)

set(CPACK_SOURCE_GENERATOR TBZ2)
set(GLIB_COMPONENTS gio gobject gthread)
set(DATA_INSTALL_DIR "share/${WebKit2_OUTPUT_NAME}-${PROJECT_VERSION_MAJOR}" CACHE PATH "Installation path for theme data")
set(HEADER_INSTALL_DIR "include/${WebKit2_OUTPUT_NAME}-${PROJECT_VERSION_MAJOR}" CACHE PATH "Installation path for header files")
set(THEME_BINARY_DIR ${CMAKE_BINARY_DIR}/WebCore/platform/efl/DefaultTheme)
set(WEB_INSPECTOR_DIR "${DATA_INSTALL_DIR}/inspector")
set(WEBINSPECTORUI_DIR "${CMAKE_SOURCE_DIR}/Source/WebInspectorUI")

# Optimize binary size for release builds by removing dead sections on unix/gcc.
if (CMAKE_COMPILER_IS_GNUCC AND UNIX AND NOT APPLE)
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffunction-sections -fdata-sections")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -ffunction-sections -fdata-sections -fno-rtti")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} -Wl,--gc-sections")
endif ()

add_definitions(-DBUILDING_EFL__=1)
add_definitions(-DUSER_AGENT_EFL_MAJOR_VERSION="602")
add_definitions(-DUSER_AGENT_EFL_MINOR_VERSION="1")
add_definitions(-DDATA_DIR="${CMAKE_INSTALL_PREFIX}/${DATA_INSTALL_DIR}"
                -DDEFAULT_THEME_DIR="${THEME_BINARY_DIR}")

# EWebKit2 tests need a hint to find out where processes such as WebProcess are located at.
add_definitions(-DWEBKIT_EXEC_PATH=\"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}\")

file(MAKE_DIRECTORY ${THEME_BINARY_DIR})

WEBKIT_OPTION_BEGIN()

WEBKIT_OPTION_DEFINE(USE_LIBHYPHEN "Whether to enable the default automatic hyphenation implementation." PUBLIC ON)

SET_AND_EXPOSE_TO_BUILD(ENABLE_DEVELOPER_MODE ${DEVELOPER_MODE})
if (DEVELOPER_MODE)
    set(ENABLE_TOOLS ON)

    add_definitions(-DWEB_INSPECTOR_DIR=\"${CMAKE_BINARY_DIR}/${WEB_INSPECTOR_DIR}\")

    WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_API_TESTS PUBLIC ON)
    WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_MINIBROWSER PUBLIC ON)
else ()
    set(ENABLE_TOOLS OFF)

    add_definitions(-DWEB_INSPECTOR_DIR=\"${CMAKE_INSTALL_PREFIX}/${WEB_INSPECTOR_DIR}\")

    WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_API_TESTS PUBLIC OFF)
    WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_MINIBROWSER PUBLIC OFF)
    set(WebKit2_VERSION_SCRIPT "-Wl,--version-script,${CMAKE_MODULE_PATH}/eflsymbols.filter")
endif ()

if (WTF_CPU_X86_64)
    set(ENABLE_FTL_DEFAULT ON)
else ()
    set(ENABLE_FTL_DEFAULT OFF)
endif ()

WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_3D_TRANSFORMS PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_ACCESSIBILITY PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_ALLINONE_BUILD PUBLIC OFF)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_ATTACHMENT_ELEMENT PUBLIC OFF)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_BATTERY_STATUS PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CSS3_TEXT PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CSS_DEVICE_ADAPTATION PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CSS_GRID_LAYOUT PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CSS_REGIONS PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CSS_SCROLL_SNAP PUBLIC OFF)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CSS_SELECTORS_LEVEL4 PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CUSTOM_ELEMENTS PRIVATE OFF)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_CUSTOM_SCHEME_HANDLER PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_DATABASE_PROCESS PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_DATALIST_ELEMENT PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_DOM4_EVENTS_CONSTRUCTOR PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_DOWNLOAD_ATTRIBUTE PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_DRAG_SUPPORT PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_ENCRYPTED_MEDIA PUBLIC OFF)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_ENCRYPTED_MEDIA_V2 PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_FILTERS_LEVEL_2 PUBLIC OFF)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_FTL_JIT PUBLIC ${ENABLE_FTL_DEFAULT})
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_FULLSCREEN_API PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_GAMEPAD PUBLIC OFF)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_GAMEPAD_DEPRECATED PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_GEOLOCATION PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_INDEXED_DATABASE_IN_WORKERS PUBLIC OFF)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_INDEXED_DATABASE PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_INPUT_TYPE_COLOR PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_LINK_PREFETCH PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_MEDIA_CAPTURE PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_MEDIA_CONTROLS_SCRIPT PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_MEDIA_SOURCE PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_MEDIA_STREAM PUBLIC OFF)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_MEMORY_SAMPLER PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_MHTML PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_MOUSE_CURSOR_SCALE PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_NAVIGATOR_CONTENT_UTILS PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_NAVIGATOR_HWCONCURRENCY PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_NETSCAPE_PLUGIN_API PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_NOSNIFF PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_POINTER_LOCK PRIVATE OFF)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_PUBLIC_SUFFIX_LIST PRIVATE ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_RESOLUTION_MEDIA_QUERY PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_REQUEST_ANIMATION_FRAME PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_SAMPLING_PROFILER PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_SPEECH_SYNTHESIS PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_SPELLCHECK PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_SUBTLE_CRYPTO PUBLIC OFF)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_TOUCH_EVENTS PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_TOUCH_SLIDER PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_USERSELECT_ALL PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_VIBRATION PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_VIDEO PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_VIDEO_TRACK PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_VIEW_MODE_CSS_MEDIA PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_WEB_AUDIO PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_WEB_RTC PUBLIC OFF)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_WEB_TIMING PUBLIC ON)
WEBKIT_OPTION_DEFAULT_PORT_VALUE(ENABLE_WEBGL PUBLIC ON)

WEBKIT_OPTION_END()

# Begin to find necessary packages for EFL port.
find_package(Cairo 1.10.2 REQUIRED)
find_package(Fontconfig 2.8.0 REQUIRED)
find_package(GnuTLS 3.0.0 REQUIRED)
find_package(LibXml2 2.8.0 REQUIRED)
find_package(LibXslt 1.1.7 REQUIRED)
find_package(ICU REQUIRED)
find_package(JPEG REQUIRED)
find_package(PNG REQUIRED)
find_package(Sqlite REQUIRED)
find_package(Threads REQUIRED)
find_package(WebP REQUIRED)
find_package(ZLIB REQUIRED)

option(ENABLE_ECORE_X "Enable Ecore_X specific usage (cursor, bell)" ON)
if (ENABLE_ECORE_X)
    # We need Xext.h to disable Xlib error messages  when running WTR on Xvfb.
    # These errors are dumped on stderr and makes the test driver thinks that
    # the test case has failed.
    find_package(X11 REQUIRED)

    list(APPEND ECORE_ADDITIONAL_COMPONENTS X)
    SET_AND_EXPOSE_TO_BUILD(HAVE_ECORE_X 1)
    SET_AND_EXPOSE_TO_BUILD(WTF_PLATFORM_X11 1)
    SET_AND_EXPOSE_TO_BUILD(MOZ_X11 1)
endif ()

if (ENABLE_ACCESSIBILITY)
    find_package(ATK 2.10.0 REQUIRED)
    set(EFL_REQUIRED_VERSION 1.9)
else ()
    add_definitions(-DHAVE_ACCESSIBILITY=0)
    set(EFL_REQUIRED_VERSION 1.8)
endif ()

find_package(Ecore ${EFL_REQUIRED_VERSION} COMPONENTS Evas File Input Imf Imf_Evas ${ECORE_ADDITIONAL_COMPONENTS} CONFIG)
find_package(Edje ${EFL_REQUIRED_VERSION} REQUIRED CONFIG)
find_package(Eet ${EFL_REQUIRED_VERSION} REQUIRED CONFIG)
find_package(Eeze ${EFL_REQUIRED_VERSION} REQUIRED CONFIG)
find_package(Efreet ${EFL_REQUIRED_VERSION} REQUIRED CONFIG)
find_package(Eina ${EFL_REQUIRED_VERSION} REQUIRED CONFIG)
find_package(Eo ${EFL_REQUIRED_VERSION} REQUIRED CONFIG)
find_package(Evas ${EFL_REQUIRED_VERSION} REQUIRED CONFIG)

if (ENABLE_GEOLOCATION)
    list(APPEND GLIB_COMPONENTS gio-unix)
    find_package(GeoClue2 2.1.5)
    if (GEOCLUE2_FOUND)
      set(USE_GEOCLUE2 1)
    else ()
      find_package(GeoClue)
      set(USE_GEOCLUE2 0)
    endif ()
endif ()

find_package(Freetype2 2.4.2 REQUIRED)
find_package(GLIB 2.38.0 REQUIRED COMPONENTS ${GLIB_COMPONENTS})
find_package(HarfBuzz 0.9.2 REQUIRED)
find_package(LibSoup 2.42.0 REQUIRED)

if (ENABLE_BATTERY_STATUS)
    find_package(Eldbus ${EFL_REQUIRED_VERSION} CONFIG)
endif ()

if (ENABLE_MEDIA_STREAM OR ENABLE_WEB_RTC)
    find_package(OpenWebRTC REQUIRED)
    SET_AND_EXPOSE_TO_BUILD(USE_OPENWEBRTC TRUE)
endif ()

if (ENABLE_NETSCAPE_PLUGIN_API)
    set(ENABLE_PLUGIN_PROCESS 1)
endif ()

if (WTF_OS_UNIX)
    set(ENABLE_X11_TARGET ON)
    SET_AND_EXPOSE_TO_BUILD(XP_UNIX 1)
endif (WTF_OS_UNIX)

if (ENABLE_VIDEO OR ENABLE_WEB_AUDIO)
    set(GSTREAMER_COMPONENTS app mpegts pbutils)
    SET_AND_EXPOSE_TO_BUILD(USE_GSTREAMER TRUE)

    if (ENABLE_VIDEO)
        list(APPEND GSTREAMER_COMPONENTS video tag)
    endif ()

    if (ENABLE_WEB_AUDIO)
        list(APPEND GSTREAMER_COMPONENTS audio fft)
        add_definitions(-DUSE_WEBAUDIO_GSTREAMER=1)
    endif ()

    find_package(GStreamer 1.0.5 REQUIRED COMPONENTS ${GSTREAMER_COMPONENTS})

    if (PC_GSTREAMER_MPEGTS_FOUND)
        add_definitions(-DUSE_GSTREAMER_MPEGTS)
        set(USE_GSTREAMER_MPEGTS TRUE)
    endif ()
endif ()

SET_AND_EXPOSE_TO_BUILD(ENABLE_GRAPHICS_CONTEXT_3D TRUE)
SET_AND_EXPOSE_TO_BUILD(USE_COORDINATED_GRAPHICS TRUE)
SET_AND_EXPOSE_TO_BUILD(USE_COORDINATED_GRAPHICS_MULTIPROCESS TRUE)
SET_AND_EXPOSE_TO_BUILD(USE_GRAPHICS_SURFACE TRUE)
SET_AND_EXPOSE_TO_BUILD(USE_TEXTURE_MAPPER TRUE)
SET_AND_EXPOSE_TO_BUILD(USE_TEXTURE_MAPPER_GL TRUE)

option(ENABLE_GLES2 "Enable GLES Support")
if (ENABLE_GLES2)
    find_package(OpenGLES2 REQUIRED)
    SET_AND_EXPOSE_TO_BUILD(USE_OPENGL_ES_2 TRUE)
else ()
    find_package(OpenGL REQUIRED)
    SET_AND_EXPOSE_TO_BUILD(USE_OPENGL TRUE)
endif ()

option(ENABLE_EGL "Enable EGL Support")
if (ENABLE_EGL)
    find_package(EGL REQUIRED)
    SET_AND_EXPOSE_TO_BUILD(USE_EGL TRUE)
else ()
    include(CheckIncludeFiles)
    CHECK_INCLUDE_FILES("GL/glx.h" OPENGLX_FOUND)
    SET_AND_EXPOSE_TO_BUILD(USE_GLX TRUE)
endif ()

if (ENABLE_WEBGL AND OPENGLX_FOUND)
    if (NOT X11_Xcomposite_FOUND OR NOT X11_Xrender_FOUND)
        # FIXME: Add support for NOT X11_Xcomposite for GLX
        message(FATAL_ERROR "To use WebGL with GLX support requires X11_Xcomposite.")
    endif ()
endif ()

if (ENABLE_SPELLCHECK)
    find_package(Enchant REQUIRED)
endif ()

if (ENABLE_SPEECH_SYNTHESIS)
    find_package(Espeak REQUIRED)
endif ()

if (ENABLE_FTL_JIT AND NOT WTF_CPU_X86_64 AND NOT DEVELOPER_MODE)
    message(FATAL_ERROR "FTL JIT is only available on X86_64 architecture.")
endif ()

if (USE_LIBHYPHEN)
    find_package(Hyphen)
    if (NOT HYPHEN_FOUND)
       message(FATAL_ERROR "libhyphen is needed for USE_LIBHYPHEN.")
    endif ()
endif ()

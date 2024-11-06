SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_SYSTEM_PROCESSOR ppc)
SET(CMAKE_C_COMPILER /opt/ppc-amigaos/bin/ppc-amigaos-gcc)
SET(CMAKE_CXX_COMPILER /opt/ppc-amigaos/bin/ppc-amigaos-g++)
SET(CXX_STANDARD_REQUIRED ON)
SET(CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "-mcrt=clib4 -std=c++17 -O3 -DNDEBUG -DCAIRO_HAS_FC_FONT -D_GNU_SOURCE -D__USE_INLINE__ -g0 -gstabs1 -feliminate-unused-debug-symbols -mlongcall -mno-sched-prolog -Wno-ignored-attributes -Wno-unused-but-set-parameter -Wno-unused-parameter -I/opt/ppc-amigaos/ppc-amigaos/SDK/MUI_5.0/C/include/")
SET(CMAKE_CXX_FLAGS_RELEASE "")
SET(CMAKE_CXX_FLAGS_DEBUG "-mlongcall -mno-sched-prolog -Wno-ignored-attributes -Wno-unused-but-set-parameter")
SET(CMAKE_CXX_FLAGS_RELEASE_INIT "")
SET(CMAKE_C_FLAGS "-mcrt=clib4 -O3 -DCAIRO_HAS_FC_FONT -D_GNU_SOURCE -D__USE_INLINE__ -mlongcall -mno-sched-prolog -Wno-ignored-attributes -I/opt/ppc-amigaos/ppc-amigaos/SDK/MUI_5.0/C/include/")
SET(CMAKE_C_FLAGS_DEBUG "-mlongcall -mno-sched-prolog -Wno-ignored-attributes")
SET(CMAKE_MODULE_LINKER_FLAGS "-lpthread -athread=native")
SET(CMAKE_FIND_LIBRARY_SUFFIXES .a)
SET(CMAKE_FIND_ROOT_PATH /opt/ppc-amigaos/ppc-amigaos/SDK/local/clib4)
SET(CMAKE_LIBRARY_PATH /opt/ppc-amigaos/ppc-amigaos/SDK/local/clib4/lib)
SET(CMAKE_INCLUDE_PATH /opt/ppc-amigaos/ppc-amigaos/SDK/local/clib4/include)
SET(SQLite3_LIBRARY /opt/ppc-amigaos/ppc-amigaos/SDK/local/clib4/lib/sqlite/instdir/include)
SET(SQLite3_INCLUDE_DIR /opt/ppc-amigaos/ppc-amigaos/SDK/local/common/include)
SET(NGHTTP2_INCLUDE_DIRS /opt/ppc-amigaos/ppc-amigaos/SDK/local/common/include)
SET(HYPHEN_INCLUDE_DIR /opt/ppc-amigaos/ppc-amigaos/SDK/local/common/include/hyphen)
SET(CURL_INCLUDE_DIR /opt/ppc-amigaos/ppc-amigaos/SDK/local/common/include/curl)
SET(OpenJPEG_INCLUDE_DIR /opt/ppc-amigaos/ppc-amigaos/SDK/local/clib4/include/openjpeg-2.5)
SET(WebP_DEMUX_LIBRARY /opt/ppc-amigaos/ppc-amigaos/SDK/local/clib4/lib/libwebpdemux.a)
SET(HarfBuzz_ICU_LIBRARY /opt/ppc-amigaos/ppc-amigaos/SDK/local/clib4/lib/libharfbuzz-icu.a)
SET(Fontconfig_INCLUDE_DIR /opt/ppc-amigaos/ppc-amigaos/SDK/local/common/include)
SET(ICU_I18N_LIBRARY_RELEASE /opt/ppc-amigaos/ppc-amigaos/SDK/local/clib4/lib/libicui18n.a)
SET(ICU_UC_LIBRARY_RELEASE /opt/ppc-amigaos/ppc-amigaos/SDK/local/clib4/lib/libicuuc.a)
SET(JPEG_LIBRARY_RELEASE /opt/ppc-amigaos/ppc-amigaos/SDK/local/clib4/lib/libjpeg.a)
SET(LIBXML2_INCLUDE_DIR /opt/ppc-amigaos/ppc-amigaos/SDK/local/common/include/libxml2)
SET(LIBXML2_LIBRARY /opt/ppc-amigaos/ppc-amigaos/SDK/local/clib4/lib/libxml2.a)
SET(NGHTTP2_LIBRARIES /opt/ppc-amigaos/ppc-amigaos/SDK/local/clib4/lib/libnghttp2.a)
SET(OPENSSL_CRYPTO_LIBRARY /opt/ppc-amigaos/ppc-amigaos/SDK/local/clib4/lib/libcrypto.a)
SET(OPENSSL_SSL_LIBRARY /opt/ppc-amigaos/ppc-amigaos/SDK/local/clib4/lib/libssl.a)
SET(ZLIB_LIBRARY_RELEASE /opt/ppc-amigaos/ppc-amigaos/SDK/local/clib4/lib/libz.a)
SET(CAIRO_INCLUDE_DIRS /opt/ppc-amigaos/ppc-amigaos/SDK/local/clib4/include/cairo)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

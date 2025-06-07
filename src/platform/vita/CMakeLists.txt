cmake_minimum_required(VERSION 3.16)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(sm)
include("${VITASDK}/share/vita.cmake" REQUIRED)

find_package(SDL2 REQUIRED)

set(VITA_APP_NAME "Super Metroid")
set(VITA_TITLEID  "SPMETROID")
set(VITA_VERSION  "00.11")
set(VITA_VPKNAME  "sm")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-q,--wrap,fopen,--wrap,mkdir -Ofast -fomit-frame-pointer -ffast-math \
 -mfloat-abi=hard -ffast-math -fsingle-precision-constant -fno-tree-vectorize -mtune=cortex-a9 -mfpu=neon -DNDEBUG -D__VITA__")

add_executable(${PROJECT_NAME}
        ../../main.c
        ../../sm_80.c
        ../../sm_81.c
        ../../sm_82.c
        ../../sm_84.c
        ../../sm_85.c
        ../../sm_86.c
        ../../sm_87.c
        ../../sm_88.c
        ../../sm_89.c
        ../../sm_8b.c
        ../../sm_8d.c
        ../../sm_8f.c
        ../../sm_90.c
        ../../sm_91.c
        ../../sm_92.c
        ../../sm_93.c
        ../../sm_94.c
        ../../sm_9b.c
        ../../sm_a0.c
        ../../sm_a2.c
        ../../sm_a3.c
        ../../sm_a4.c
        ../../sm_a5.c
        ../../sm_a6.c
        ../../sm_a7.c
        ../../sm_a8.c
        ../../sm_a9.c
        ../../sm_aa.c
        ../../sm_ad.c
        ../../sm_b2.c
        ../../sm_b3.c
        ../../sm_b4.c
        ../../sm_cpu_infra.c
        ../../sm_rtl.c
        ../../snes/apu.c
        ../../snes/cart.c
        ../../snes/cpu.c
        ../../snes/dma.c
        ../../snes/dsp.c
        ../../snes/input.c
        ../../snes/ppu.c
        ../../snes/snes.c
        ../../snes/snes_other.c
        ../../snes/spc.c
        ../../spc_player.c
        ../../util.c
        ../../config.c
        ../../tracing.c
        src/vita_impl.c
)

target_link_libraries(${PROJECT_NAME}
  SDL2::SDL2
)

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE sm.ini sm.ini
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
)

set(PSVITAIP "192.168.178.32" CACHE STRING "PSVita IP (for FTP access)")

add_custom_target(send
        COMMAND echo Sending to ${PSVITAIP}...
        COMMAND echo destroy | nc ${PSVITAIP} 1338
        COMMAND cp sm.self eboot.bin
        COMMAND curl -T ftp://${PSVITAIP}:1337/ux0:/app/${VITA_TITLEID}/
        COMMAND echo launch ${VITA_TITLEID} | nc ${PSVITAIP} 1338
        DEPENDS ${VITA_VPKNAME}.vpk-vpk
)

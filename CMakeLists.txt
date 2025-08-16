cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 8.1 CACHE STRING "" FORCE)

project(fbneo_vs2015 C CXX)

################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "Win32")
endif()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

if(NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64"
     OR "${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32"))
    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
endif()

################################################################################
# Global configuration types
################################################################################
set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    CACHE STRING "" FORCE
)

################################################################################
# Global compiler options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_C_FLAGS "")
    set(CMAKE_C_FLAGS_DEBUG "")
    set(CMAKE_C_FLAGS_RELEASE "")
    set(CMAKE_CXX_FLAGS "")
    set(CMAKE_CXX_FLAGS_DEBUG "")
    set(CMAKE_CXX_FLAGS_RELEASE "")
endif()

################################################################################
# Global linker options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_EXE_LINKER_FLAGS "")
    set(CMAKE_MODULE_LINKER_FLAGS "")
    set(CMAKE_SHARED_LINKER_FLAGS "")
    set(CMAKE_STATIC_LINKER_FLAGS "")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
endif()

################################################################################
# Nuget packages function stub.
################################################################################
function(use_package TARGET PACKAGE VERSION)
    message(WARNING "No implementation of use_package. Create yours. "
                    "Package \"${PACKAGE}\" with version \"${VERSION}\" "
                    "for target \"${TARGET}\" is ignored!")
endfunction()

################################################################################
# Common utils
################################################################################
include(CMake/Utils.cmake)

################################################################################
# Additional Global Settings(add specific info there)
################################################################################
include(CMake/GlobalSettingsInclude.cmake OPTIONAL)

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################################################################################
# Sub-projects
################################################################################



























set(PROJECT_NAME fcadefbneo)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
    "src/burner/win32/resource.rc"
    "src/dep/scripts/build_details.cpp"
)
source_group("" FILES ${no_group_source_files})

set(Burn
    "src/burn/bitswap.h"
    "src/burn/burn.cpp"
    "src/burn/burn.h"
    "src/burn/burn_bitmap.cpp"
    "src/burn/burn_bitmap.h"
    "src/burn/burn_gun.cpp"
    "src/burn/burn_gun.h"
    "src/burn/burn_led.cpp"
    "src/burn/burn_led.h"
    "src/burn/burn_memory.cpp"
    "src/burn/burn_pal.cpp"
    "src/burn/burn_pal.h"
    "src/burn/burn_shift.cpp"
    "src/burn/burn_shift.h"
    "src/burn/burn_sound.cpp"
    "src/burn/burn_sound.h"
    "src/burn/burn_sound_a.asm"
    "src/burn/burn_sound_c.cpp"
    "src/burn/burnint.h"
    "src/burn/cheat.cpp"
    "src/burn/cheat.h"
    "src/burn/debug_track.cpp"
    "src/burn/driver.h"
    "src/burn/hiscore.cpp"
    "src/burn/hiscore.h"
    "src/burn/load.cpp"
    "src/burn/state.h"
    "src/burn/stdfunc.h"
    "src/burn/tilemap_generic.cpp"
    "src/burn/tilemap_generic.h"
    "src/burn/tiles_generic.cpp"
    "src/burn/tiles_generic.h"
    "src/burn/timer.cpp"
    "src/burn/timer.h"
    "src/burn/vector.cpp"
    "src/burn/vector.h"
    "src/burn/version.h"
)
source_group("Burn" FILES ${Burn})

set(Burn__devices
    "src/burn/devices/6821pia.cpp"
    "src/burn/devices/6821pia.h"
    "src/burn/devices/8255ppi.cpp"
    "src/burn/devices/8255ppi.h"
    "src/burn/devices/8257dma.cpp"
    "src/burn/devices/8257dma.h"
    "src/burn/devices/atariic.cpp"
    "src/burn/devices/atariic.h"
    "src/burn/devices/atarijsa.cpp"
    "src/burn/devices/atarijsa.h"
    "src/burn/devices/atarimo.cpp"
    "src/burn/devices/atarimo.h"
    "src/burn/devices/atarirle.cpp"
    "src/burn/devices/atarirle.h"
    "src/burn/devices/atarivad.cpp"
    "src/burn/devices/atarivad.h"
    "src/burn/devices/avgdvg.cpp"
    "src/burn/devices/avgdvg.h"
    "src/burn/devices/bsmt2000.cpp"
    "src/burn/devices/bsmt2000.h"
    "src/burn/devices/c169.cpp"
    "src/burn/devices/c169.h"
    "src/burn/devices/decobsmt.cpp"
    "src/burn/devices/decobsmt.h"
    "src/burn/devices/earom.cpp"
    "src/burn/devices/earom.h"
    "src/burn/devices/eeprom.cpp"
    "src/burn/devices/eeprom.h"
    "src/burn/devices/gaelco_crypt.cpp"
    "src/burn/devices/gaelco_crypt.h"
    "src/burn/devices/i4x00.cpp"
    "src/burn/devices/i4x00.h"
    "src/burn/devices/joyprocess.cpp"
    "src/burn/devices/joyprocess.h"
    "src/burn/devices/kaneko_tmap.cpp"
    "src/burn/devices/kaneko_tmap.h"
    "src/burn/devices/mathbox.cpp"
    "src/burn/devices/mathbox.h"
    "src/burn/devices/mb87078.cpp"
    "src/burn/devices/mb87078.h"
    "src/burn/devices/mermaid.cpp"
    "src/burn/devices/mermaid.h"
    "src/burn/devices/midcsd.cpp"
    "src/burn/devices/midcsd.h"
    "src/burn/devices/midsat.cpp"
    "src/burn/devices/midsat.h"
    "src/burn/devices/midsg.cpp"
    "src/burn/devices/midsg.h"
    "src/burn/devices/midssio.cpp"
    "src/burn/devices/midssio.h"
    "src/burn/devices/midtcs.cpp"
    "src/burn/devices/midtcs.h"
    "src/burn/devices/namco_c45.cpp"
    "src/burn/devices/namco_c45.h"
    "src/burn/devices/namcoio.cpp"
    "src/burn/devices/namcoio.h"
    "src/burn/devices/nb1414m4.cpp"
    "src/burn/devices/nb1414m4.h"
    "src/burn/devices/nb1414m4_8bit.cpp"
    "src/burn/devices/nb1414m4_8bit.h"
    "src/burn/devices/nmk004.cpp"
    "src/burn/devices/nmk004.h"
    "src/burn/devices/nmk112.cpp"
    "src/burn/devices/nmk112.h"
    "src/burn/devices/pandora.cpp"
    "src/burn/devices/pandora.h"
    "src/burn/devices/qs1000.cpp"
    "src/burn/devices/qs1000.h"
    "src/burn/devices/resnet.cpp"
    "src/burn/devices/resnet.h"
    "src/burn/devices/seibucop.cpp"
    "src/burn/devices/seibucop.h"
    "src/burn/devices/seibusnd.cpp"
    "src/burn/devices/seibusnd.h"
    "src/burn/devices/sknsspr.cpp"
    "src/burn/devices/sknsspr.h"
    "src/burn/devices/slapstic.cpp"
    "src/burn/devices/slapstic.h"
    "src/burn/devices/st0020.cpp"
    "src/burn/devices/st0020.h"
    "src/burn/devices/t5182.cpp"
    "src/burn/devices/t5182.h"
    "src/burn/devices/timekpr.cpp"
    "src/burn/devices/timekpr.h"
    "src/burn/devices/tms34061.cpp"
    "src/burn/devices/tms34061.h"
    "src/burn/devices/tms9928a.cpp"
    "src/burn/devices/tms9928a.h"
    "src/burn/devices/v3021.cpp"
    "src/burn/devices/v3021.h"
    "src/burn/devices/vdc.cpp"
    "src/burn/devices/vdc.h"
    "src/burn/devices/watchdog.cpp"
    "src/burn/devices/watchdog.h"
    "src/burn/devices/x2212.cpp"
    "src/burn/devices/x2212.h"
)
source_group("Burn\\devices" FILES ${Burn__devices})

set(Burn__drv__atari
    "src/burn/drv/atari/d_akkaarrh.cpp"
    "src/burn/drv/atari/d_arcadecl.cpp"
    "src/burn/drv/atari/d_atarig1.cpp"
    "src/burn/drv/atari/d_badlands.cpp"
    "src/burn/drv/atari/d_batman.cpp"
    "src/burn/drv/atari/d_blstroid.cpp"
    "src/burn/drv/atari/d_eprom.cpp"
    "src/burn/drv/atari/d_gauntlet.cpp"
    "src/burn/drv/atari/d_klax.cpp"
    "src/burn/drv/atari/d_offtwall.cpp"
    "src/burn/drv/atari/d_rampart.cpp"
    "src/burn/drv/atari/d_relief.cpp"
    "src/burn/drv/atari/d_shuuz.cpp"
    "src/burn/drv/atari/d_skullxbo.cpp"
    "src/burn/drv/atari/d_thunderj.cpp"
    "src/burn/drv/atari/d_toobin.cpp"
    "src/burn/drv/atari/d_vindictr.cpp"
    "src/burn/drv/atari/d_xybots.cpp"
)
source_group("Burn\\drv\\atari" FILES ${Burn__drv__atari})

set(Burn__drv__capcom
    "src/burn/drv/capcom/cps.cpp"
    "src/burn/drv/capcom/cps.h"
    "src/burn/drv/capcom/cps2_crpt.cpp"
    "src/burn/drv/capcom/cps_config.cpp"
    "src/burn/drv/capcom/cps_draw.cpp"
    "src/burn/drv/capcom/cps_mem.cpp"
    "src/burn/drv/capcom/cps_obj.cpp"
    "src/burn/drv/capcom/cps_pal.cpp"
    "src/burn/drv/capcom/cps_run.cpp"
    "src/burn/drv/capcom/cps_rw.cpp"
    "src/burn/drv/capcom/cps_scr.cpp"
    "src/burn/drv/capcom/cpsr.cpp"
    "src/burn/drv/capcom/cpsrd.cpp"
    "src/burn/drv/capcom/cpst.cpp"
    "src/burn/drv/capcom/ctv.cpp"
    "src/burn/drv/capcom/ctv_do.h"
    # "src/burn/drv/capcom/ctv_make.cpp"
    "src/burn/drv/capcom/d_cps1.cpp"
    "src/burn/drv/capcom/d_cps2.cpp"
    "src/burn/drv/capcom/d_kenseim.h"
    "src/burn/drv/capcom/fcrash_snd.cpp"
    "src/burn/drv/capcom/kabuki.cpp"
    "src/burn/drv/capcom/ps.cpp"
    "src/burn/drv/capcom/ps_m.cpp"
    "src/burn/drv/capcom/ps_z.cpp"
    "src/burn/drv/capcom/qs.cpp"
    "src/burn/drv/capcom/qs_c.cpp"
    "src/burn/drv/capcom/qs_z.cpp"
    "src/burn/drv/capcom/sf2mdt_snd.cpp"
)
source_group("Burn\\drv\\capcom" FILES ${Burn__drv__capcom})

set(Burn__drv__cave
    "src/burn/drv/cave/cave.cpp"
    "src/burn/drv/cave/cave_palette.cpp"
    "src/burn/drv/cave/cave_sprite.cpp"
    "src/burn/drv/cave/cave_tile.cpp"
    "src/burn/drv/cave/d_dodonpachi.cpp"
    "src/burn/drv/cave/d_donpachi.cpp"
    "src/burn/drv/cave/d_esprade.cpp"
    "src/burn/drv/cave/d_feversos.cpp"
    "src/burn/drv/cave/d_gaia.cpp"
    "src/burn/drv/cave/d_guwange.cpp"
    "src/burn/drv/cave/d_hotdogst.cpp"
    "src/burn/drv/cave/d_korokoro.cpp"
    "src/burn/drv/cave/d_mazinger.cpp"
    "src/burn/drv/cave/d_metmqstr.cpp"
    "src/burn/drv/cave/d_pwrinst2.cpp"
    "src/burn/drv/cave/d_sailormn.cpp"
    "src/burn/drv/cave/d_tjumpman.cpp"
    "src/burn/drv/cave/d_uopoko.cpp"
)
source_group("Burn\\drv\\cave" FILES ${Burn__drv__cave})

set(Burn__drv__coleco
    "src/burn/drv/coleco/d_coleco.cpp"
)
source_group("Burn\\drv\\coleco" FILES ${Burn__drv__coleco})

set(Burn__drv__cps3
    "src/burn/drv/cps3/cps3run.cpp"
    "src/burn/drv/cps3/cps3snd.cpp"
    "src/burn/drv/cps3/d_cps3.cpp"
)
source_group("Burn\\drv\\cps3" FILES ${Burn__drv__cps3})

set(Burn__drv__dataeast
    "src/burn/drv/dataeast/d_actfancr.cpp"
    "src/burn/drv/dataeast/d_backfire.cpp"
    "src/burn/drv/dataeast/d_boogwing.cpp"
    "src/burn/drv/dataeast/d_brkthru.cpp"
    "src/burn/drv/dataeast/d_bwing.cpp"
    "src/burn/drv/dataeast/d_cbuster.cpp"
    "src/burn/drv/dataeast/d_chanbara.cpp"
    "src/burn/drv/dataeast/d_cninja.cpp"
    "src/burn/drv/dataeast/d_darkseal.cpp"
    "src/burn/drv/dataeast/d_dassault.cpp"
    "src/burn/drv/dataeast/d_dblewing.cpp"
    "src/burn/drv/dataeast/d_dec0.cpp"
    "src/burn/drv/dataeast/d_dec8.cpp"
    "src/burn/drv/dataeast/d_deco156.cpp"
    "src/burn/drv/dataeast/d_deco32.cpp"
    "src/burn/drv/dataeast/d_decocass.cpp"
    "src/burn/drv/dataeast/d_decomlc.cpp"
    "src/burn/drv/dataeast/d_dietgogo.cpp"
    "src/burn/drv/dataeast/d_dreambal.cpp"
    "src/burn/drv/dataeast/d_funkyjet.cpp"
    "src/burn/drv/dataeast/d_karnov.cpp"
    "src/burn/drv/dataeast/d_kchamp.cpp"
    "src/burn/drv/dataeast/d_lemmings.cpp"
    "src/burn/drv/dataeast/d_liberate.cpp"
    "src/burn/drv/dataeast/d_metlclsh.cpp"
    "src/burn/drv/dataeast/d_pktgaldx.cpp"
    "src/burn/drv/dataeast/d_progolf.cpp"
    "src/burn/drv/dataeast/d_rohga.cpp"
    "src/burn/drv/dataeast/d_shootout.cpp"
    "src/burn/drv/dataeast/d_sidepckt.cpp"
    "src/burn/drv/dataeast/d_simpl156.cpp"
    "src/burn/drv/dataeast/d_sshangha.cpp"
    "src/burn/drv/dataeast/d_stadhero.cpp"
    "src/burn/drv/dataeast/d_supbtime.cpp"
    "src/burn/drv/dataeast/d_tumblep.cpp"
    "src/burn/drv/dataeast/d_vaportra.cpp"
    "src/burn/drv/dataeast/deco146.cpp"
    "src/burn/drv/dataeast/deco16ic.cpp"
    "src/burn/drv/dataeast/decobac06.cpp"
)
source_group("Burn\\drv\\dataeast" FILES ${Burn__drv__dataeast})

set(Burn__drv__galaxian
    "src/burn/drv/galaxian/d_galaxian.cpp"
    "src/burn/drv/galaxian/gal_gfx.cpp"
    "src/burn/drv/galaxian/gal_run.cpp"
    "src/burn/drv/galaxian/gal_sound.cpp"
    "src/burn/drv/galaxian/gal_stars.cpp"
)
source_group("Burn\\drv\\galaxian" FILES ${Burn__drv__galaxian})

set(Burn__drv__irem
    "src/burn/drv/irem/d_m107.cpp"
    "src/burn/drv/irem/d_m52.cpp"
    "src/burn/drv/irem/d_m57.cpp"
    "src/burn/drv/irem/d_m58.cpp"
    "src/burn/drv/irem/d_m62.cpp"
    "src/burn/drv/irem/d_m63.cpp"
    "src/burn/drv/irem/d_m72.cpp"
    "src/burn/drv/irem/d_m90.cpp"
    "src/burn/drv/irem/d_m92.cpp"
    "src/burn/drv/irem/d_vigilant.cpp"
    "src/burn/drv/irem/irem_cpu.cpp"
    "src/burn/drv/irem/irem_cpu.h"
    "src/burn/drv/irem/irem_sound.cpp"
    "src/burn/drv/irem/irem_sound.h"
)
source_group("Burn\\drv\\irem" FILES ${Burn__drv__irem})

set(Burn__drv__konami
    "src/burn/drv/konami/d_88games.cpp"
    "src/burn/drv/konami/d_ajax.cpp"
    "src/burn/drv/konami/d_aliens.cpp"
    "src/burn/drv/konami/d_asterix.cpp"
    "src/burn/drv/konami/d_battlnts.cpp"
    "src/burn/drv/konami/d_bishi.cpp"
    "src/burn/drv/konami/d_bladestl.cpp"
    "src/burn/drv/konami/d_blockhl.cpp"
    "src/burn/drv/konami/d_bottom9.cpp"
    "src/burn/drv/konami/d_chqflag.cpp"
    "src/burn/drv/konami/d_circusc.cpp"
    "src/burn/drv/konami/d_combatsc.cpp"
    "src/burn/drv/konami/d_contra.cpp"
    "src/burn/drv/konami/d_crimfght.cpp"
    "src/burn/drv/konami/d_dbz.cpp"
    "src/burn/drv/konami/d_ddribble.cpp"
    "src/burn/drv/konami/d_divebomb.cpp"
    "src/burn/drv/konami/d_fastlane.cpp"
    "src/burn/drv/konami/d_finalzr.cpp"
    "src/burn/drv/konami/d_flkatck.cpp"
    "src/burn/drv/konami/d_gberet.cpp"
    "src/burn/drv/konami/d_gbusters.cpp"
    "src/burn/drv/konami/d_gijoe.cpp"
    "src/burn/drv/konami/d_gradius3.cpp"
    "src/burn/drv/konami/d_gyruss.cpp"
    "src/burn/drv/konami/d_hcastle.cpp"
    "src/burn/drv/konami/d_hexion.cpp"
    "src/burn/drv/konami/d_hyperspt.cpp"
    "src/burn/drv/konami/d_ironhors.cpp"
    "src/burn/drv/konami/d_jackal.cpp"
    "src/burn/drv/konami/d_jailbrek.cpp"
    "src/burn/drv/konami/d_junofrst.cpp"
    "src/burn/drv/konami/d_kontest.cpp"
    "src/burn/drv/konami/d_labyrunr.cpp"
    "src/burn/drv/konami/d_lethal.cpp"
    "src/burn/drv/konami/d_mainevt.cpp"
    "src/burn/drv/konami/d_megazone.cpp"
    "src/burn/drv/konami/d_mikie.cpp"
    "src/burn/drv/konami/d_mogura.cpp"
    "src/burn/drv/konami/d_moo.cpp"
    "src/burn/drv/konami/d_mystwarr.cpp"
    "src/burn/drv/konami/d_nemesis.cpp"
    "src/burn/drv/konami/d_pandoras.cpp"
    "src/burn/drv/konami/d_parodius.cpp"
    "src/burn/drv/konami/d_pingpong.cpp"
    "src/burn/drv/konami/d_pooyan.cpp"
    "src/burn/drv/konami/d_rockrage.cpp"
    "src/burn/drv/konami/d_rocnrope.cpp"
    "src/burn/drv/konami/d_rollerg.cpp"
    "src/burn/drv/konami/d_sbasketb.cpp"
    "src/burn/drv/konami/d_scotrsht.cpp"
    "src/burn/drv/konami/d_shaolins.cpp"
    "src/burn/drv/konami/d_simpsons.cpp"
    "src/burn/drv/konami/d_spy.cpp"
    "src/burn/drv/konami/d_surpratk.cpp"
    "src/burn/drv/konami/d_thunderx.cpp"
    "src/burn/drv/konami/d_timeplt.cpp"
    "src/burn/drv/konami/d_tmnt.cpp"
    "src/burn/drv/konami/d_tp84.cpp"
    "src/burn/drv/konami/d_trackfld.cpp"
    "src/burn/drv/konami/d_tutankhm.cpp"
    "src/burn/drv/konami/d_twin16.cpp"
    "src/burn/drv/konami/d_ultraman.cpp"
    "src/burn/drv/konami/d_vendetta.cpp"
    "src/burn/drv/konami/d_xexex.cpp"
    "src/burn/drv/konami/d_xmen.cpp"
    "src/burn/drv/konami/d_yiear.cpp"
    "src/burn/drv/konami/k007121.cpp"
    "src/burn/drv/konami/k007342_k007420.cpp"
    "src/burn/drv/konami/k051316.cpp"
    "src/burn/drv/konami/k051733.cpp"
    "src/burn/drv/konami/k051960.cpp"
    "src/burn/drv/konami/k052109.cpp"
    "src/burn/drv/konami/k053245.cpp"
    "src/burn/drv/konami/k053247.cpp"
    "src/burn/drv/konami/k053250.cpp"
    "src/burn/drv/konami/k053251.cpp"
    "src/burn/drv/konami/k053936.cpp"
    "src/burn/drv/konami/k054000.cpp"
    "src/burn/drv/konami/k054338.cpp"
    "src/burn/drv/konami/k055555.cpp"
    "src/burn/drv/konami/k056832.cpp"
    "src/burn/drv/konami/konamigx.cpp"
    "src/burn/drv/konami/konamiic.cpp"
    "src/burn/drv/konami/timeplt_snd.cpp"
)
source_group("Burn\\drv\\konami" FILES ${Burn__drv__konami})

set(Burn__drv__megadrive
    "src/burn/drv/megadrive/d_megadrive.cpp"
    "src/burn/drv/megadrive/mdeeprom.cpp"
    "src/burn/drv/megadrive/megadrive.cpp"
    "src/burn/drv/megadrive/stm95.cpp"
)
source_group("Burn\\drv\\megadrive" FILES ${Burn__drv__megadrive})

set(Burn__drv__midway
    "src/burn/drv/midway/d_kinst.cpp"
    "src/burn/drv/midway/d_tunit.cpp"
    "src/burn/drv/midway/d_wunit.cpp"
    "src/burn/drv/midway/dcs2k.cpp"
    "src/burn/drv/midway/ide.cpp"
    "src/burn/drv/midway/midtunit.cpp"
    "src/burn/drv/midway/midwayic.cpp"
    "src/burn/drv/midway/midwunit.cpp"
)
source_group("Burn\\drv\\midway" FILES ${Burn__drv__midway})

set(Burn__drv__msx
    "src/burn/drv/msx/d_msx.cpp"
)
source_group("Burn\\drv\\msx" FILES ${Burn__drv__msx})

set(Burn__drv__neogeo
    "src/burn/drv/neogeo/d_neogeo.cpp"
    "src/burn/drv/neogeo/neo_decrypt.cpp"
    "src/burn/drv/neogeo/neo_palette.cpp"
    "src/burn/drv/neogeo/neo_run.cpp"
    "src/burn/drv/neogeo/neo_sprite.cpp"
    "src/burn/drv/neogeo/neo_sprite_render.h"
    "src/burn/drv/neogeo/neo_text.cpp"
    "src/burn/drv/neogeo/neo_text_render.h"
    "src/burn/drv/neogeo/neo_upd4990a.cpp"
    "src/burn/drv/neogeo/neogeo.cpp"
    "src/burn/drv/neogeo/neogeo.h"
)
source_group("Burn\\drv\\neogeo" FILES ${Burn__drv__neogeo})

set(Burn__drv__nes
    "src/burn/drv/nes/d_nes.cpp"
)
source_group("Burn\\drv\\nes" FILES ${Burn__drv__nes})

set(Burn__drv__pce
    "src/burn/drv/pce/d_pce.cpp"
    "src/burn/drv/pce/pce.cpp"
)
source_group("Burn\\drv\\pce" FILES ${Burn__drv__pce})

set(Burn__drv__pgm
    "src/burn/drv/pgm/d_pgm.cpp"
    "src/burn/drv/pgm/pgm_asic25.cpp"
    "src/burn/drv/pgm/pgm_asic27a_type1.cpp"
    "src/burn/drv/pgm/pgm_asic27a_type2.cpp"
    "src/burn/drv/pgm/pgm_asic27a_type3.cpp"
    "src/burn/drv/pgm/pgm_asic3.cpp"
    "src/burn/drv/pgm/pgm_crypt.cpp"
    "src/burn/drv/pgm/pgm_draw.cpp"
    "src/burn/drv/pgm/pgm_run.cpp"
    # "src/burn/drv/pgm/pgm_sprite_create.cpp"
)
source_group("Burn\\drv\\pgm" FILES ${Burn__drv__pgm})

set(Burn__drv__pre90s
    "src/burn/drv/d_parent.cpp"
    "src/burn/drv/pre90s/d_1942.cpp"
    "src/burn/drv/pre90s/d_1943.cpp"
    "src/burn/drv/pre90s/d_4enraya.cpp"
    "src/burn/drv/pre90s/d_aeroboto.cpp"
    "src/burn/drv/pre90s/d_alinvade.cpp"
    "src/burn/drv/pre90s/d_alpha68k.cpp"
    "src/burn/drv/pre90s/d_alpha68k1.cpp"
    "src/burn/drv/pre90s/d_alpha68k2.cpp"
    "src/burn/drv/pre90s/d_ambush.cpp"
    "src/burn/drv/pre90s/d_amspdwy.cpp"
    "src/burn/drv/pre90s/d_arabian.cpp"
    "src/burn/drv/pre90s/d_argus.cpp"
    "src/burn/drv/pre90s/d_armedf.cpp"
    "src/burn/drv/pre90s/d_asteroids.cpp"
    "src/burn/drv/pre90s/d_atetris.cpp"
    "src/burn/drv/pre90s/d_aztarac.cpp"
    "src/burn/drv/pre90s/d_bagman.cpp"
    "src/burn/drv/pre90s/d_baraduke.cpp"
    "src/burn/drv/pre90s/d_battlane.cpp"
    "src/burn/drv/pre90s/d_battlex.cpp"
    "src/burn/drv/pre90s/d_bbusters.cpp"
    "src/burn/drv/pre90s/d_beaminv.cpp"
    "src/burn/drv/pre90s/d_berzerk.cpp"
    "src/burn/drv/pre90s/d_bionicc.cpp"
    "src/burn/drv/pre90s/d_blktiger.cpp"
    "src/burn/drv/pre90s/d_blockade.cpp"
    "src/burn/drv/pre90s/d_blockout.cpp"
    "src/burn/drv/pre90s/d_blueprnt.cpp"
    "src/burn/drv/pre90s/d_bogeyman.cpp"
    "src/burn/drv/pre90s/d_bombjack.cpp"
    "src/burn/drv/pre90s/d_btime.cpp"
    "src/burn/drv/pre90s/d_bwidow.cpp"
    "src/burn/drv/pre90s/d_bzone.cpp"
    "src/burn/drv/pre90s/d_cabal.cpp"
    "src/burn/drv/pre90s/d_calorie.cpp"
    "src/burn/drv/pre90s/d_canyon.cpp"
    "src/burn/drv/pre90s/d_capbowl.cpp"
    "src/burn/drv/pre90s/d_carjmbre.cpp"
    "src/burn/drv/pre90s/d_ccastles.cpp"
    "src/burn/drv/pre90s/d_cclimber.cpp"
    "src/burn/drv/pre90s/d_cheekyms.cpp"
    "src/burn/drv/pre90s/d_chinagat.cpp"
    "src/burn/drv/pre90s/d_citycon.cpp"
    "src/burn/drv/pre90s/d_cloak.cpp"
    "src/burn/drv/pre90s/d_cloud9.cpp"
    "src/burn/drv/pre90s/d_clshroad.cpp"
    "src/burn/drv/pre90s/d_commando.cpp"
    "src/burn/drv/pre90s/d_cop01.cpp"
    "src/burn/drv/pre90s/d_copsnrob.cpp"
    "src/burn/drv/pre90s/d_cybertnk.cpp"
    "src/burn/drv/pre90s/d_dacholer.cpp"
    "src/burn/drv/pre90s/d_dday.cpp"
    "src/burn/drv/pre90s/d_ddayjlc.cpp"
    "src/burn/drv/pre90s/d_ddragon.cpp"
    "src/burn/drv/pre90s/d_deadang.cpp"
    "src/burn/drv/pre90s/d_djboy.cpp"
    "src/burn/drv/pre90s/d_dkong.cpp"
    "src/burn/drv/pre90s/d_docastle.cpp"
    "src/burn/drv/pre90s/d_dogfgt.cpp"
    "src/burn/drv/pre90s/d_dorachan.cpp"
    "src/burn/drv/pre90s/d_dribling.cpp"
    "src/burn/drv/pre90s/d_drmicro.cpp"
    "src/burn/drv/pre90s/d_dynduke.cpp"
    "src/burn/drv/pre90s/d_efdt.cpp"
    "src/burn/drv/pre90s/d_epos.cpp"
    "src/burn/drv/pre90s/d_espial.cpp"
    "src/burn/drv/pre90s/d_ettrivia.cpp"
    "src/burn/drv/pre90s/d_exedexes.cpp"
    "src/burn/drv/pre90s/d_exprraid.cpp"
    "src/burn/drv/pre90s/d_fantland.cpp"
    "src/burn/drv/pre90s/d_fastfred.cpp"
    "src/burn/drv/pre90s/d_firetrap.cpp"
    "src/burn/drv/pre90s/d_flipjack.cpp"
    "src/burn/drv/pre90s/d_flower.cpp"
    "src/burn/drv/pre90s/d_foodf.cpp"
    "src/burn/drv/pre90s/d_freekick.cpp"
    "src/burn/drv/pre90s/d_funkybee.cpp"
    "src/burn/drv/pre90s/d_galaga.cpp"
    "src/burn/drv/pre90s/d_galivan.cpp"
    "src/burn/drv/pre90s/d_gaplus.cpp"
    "src/burn/drv/pre90s/d_ginganin.cpp"
    "src/burn/drv/pre90s/d_gng.cpp"
    "src/burn/drv/pre90s/d_goindol.cpp"
    "src/burn/drv/pre90s/d_gunsmoke.cpp"
    "src/burn/drv/pre90s/d_headonb.cpp"
    "src/burn/drv/pre90s/d_higemaru.cpp"
    "src/burn/drv/pre90s/d_himesiki.cpp"
    "src/burn/drv/pre90s/d_holeland.cpp"
    "src/burn/drv/pre90s/d_hvyunit.cpp"
    "src/burn/drv/pre90s/d_invaders.cpp"
    "src/burn/drv/pre90s/d_iqblock.cpp"
    "src/burn/drv/pre90s/d_jack.cpp"
    "src/burn/drv/pre90s/d_jedi.cpp"
    "src/burn/drv/pre90s/d_jrpacman.cpp"
    "src/burn/drv/pre90s/d_kangaroo.cpp"
    "src/burn/drv/pre90s/d_kingofbox.cpp"
    "src/burn/drv/pre90s/d_kncljoe.cpp"
    "src/burn/drv/pre90s/d_kyugo.cpp"
    "src/burn/drv/pre90s/d_ladybug.cpp"
    "src/burn/drv/pre90s/d_lasso.cpp"
    "src/burn/drv/pre90s/d_lastduel.cpp"
    "src/burn/drv/pre90s/d_lwings.cpp"
    "src/burn/drv/pre90s/d_madmotor.cpp"
    "src/burn/drv/pre90s/d_mainsnk.cpp"
    "src/burn/drv/pre90s/d_mappy.cpp"
    "src/burn/drv/pre90s/d_marineb.cpp"
    "src/burn/drv/pre90s/d_mario.cpp"
    "src/burn/drv/pre90s/d_markham.cpp"
    "src/burn/drv/pre90s/d_mastboyo.cpp"
    "src/burn/drv/pre90s/d_matmania.cpp"
    "src/burn/drv/pre90s/d_mcr.cpp"
    "src/burn/drv/pre90s/d_mcr3.cpp"
    "src/burn/drv/pre90s/d_megasys1.cpp"
    "src/burn/drv/pre90s/d_meijinsn.cpp"
    "src/burn/drv/pre90s/d_metlfrzr.cpp"
    "src/burn/drv/pre90s/d_mhavoc.cpp"
    "src/burn/drv/pre90s/d_millipede.cpp"
    "src/burn/drv/pre90s/d_mirax.cpp"
    "src/burn/drv/pre90s/d_mitchell.cpp"
    "src/burn/drv/pre90s/d_mmagic.cpp"
    "src/burn/drv/pre90s/d_mole.cpp"
    "src/burn/drv/pre90s/d_momoko.cpp"
    "src/burn/drv/pre90s/d_mouser.cpp"
    "src/burn/drv/pre90s/d_mrdo.cpp"
    "src/burn/drv/pre90s/d_mrflea.cpp"
    "src/burn/drv/pre90s/d_mrjong.cpp"
    "src/burn/drv/pre90s/d_munchmo.cpp"
    "src/burn/drv/pre90s/d_mustache.cpp"
    "src/burn/drv/pre90s/d_mystston.cpp"
    "src/burn/drv/pre90s/d_namcos1.cpp"
    "src/burn/drv/pre90s/d_namcos86.cpp"
    "src/burn/drv/pre90s/d_naughtyb.cpp"
    "src/burn/drv/pre90s/d_ninjakd2.cpp"
    "src/burn/drv/pre90s/d_nitedrvr.cpp"
    "src/burn/drv/pre90s/d_olibochu.cpp"
    "src/burn/drv/pre90s/d_omegrace.cpp"
    "src/burn/drv/pre90s/d_pac2650.cpp"
    "src/burn/drv/pre90s/d_pacland.cpp"
    "src/burn/drv/pre90s/d_pacman.cpp"
    "src/burn/drv/pre90s/d_pbaction.cpp"
    "src/burn/drv/pre90s/d_pengadvb.cpp"
    "src/burn/drv/pre90s/d_phoenix.cpp"
    "src/burn/drv/pre90s/d_pitnrun.cpp"
    "src/burn/drv/pre90s/d_pkunwar.cpp"
    "src/burn/drv/pre90s/d_popeye.cpp"
    "src/burn/drv/pre90s/d_popper.cpp"
    "src/burn/drv/pre90s/d_prehisle.cpp"
    "src/burn/drv/pre90s/d_psychic5.cpp"
    "src/burn/drv/pre90s/d_pturn.cpp"
    "src/burn/drv/pre90s/d_punchout.cpp"
    "src/burn/drv/pre90s/d_qbert.cpp"
    "src/burn/drv/pre90s/d_quantum.cpp"
    "src/burn/drv/pre90s/d_quizo.cpp"
    "src/burn/drv/pre90s/d_rallyx.cpp"
    "src/burn/drv/pre90s/d_renegade.cpp"
    "src/burn/drv/pre90s/d_route16.cpp"
    "src/burn/drv/pre90s/d_rpunch.cpp"
    "src/burn/drv/pre90s/d_safarir.cpp"
    "src/burn/drv/pre90s/d_sauro.cpp"
    "src/burn/drv/pre90s/d_scregg.cpp"
    "src/burn/drv/pre90s/d_seicross.cpp"
    "src/burn/drv/pre90s/d_senjyo.cpp"
    "src/burn/drv/pre90s/d_sf.cpp"
    "src/burn/drv/pre90s/d_shisen.cpp"
    "src/burn/drv/pre90s/d_sidearms.cpp"
    "src/burn/drv/pre90s/d_skyarmy.cpp"
    "src/burn/drv/pre90s/d_skyfox.cpp"
    "src/burn/drv/pre90s/d_skykid.cpp"
    "src/burn/drv/pre90s/d_snk.cpp"
    "src/burn/drv/pre90s/d_snk6502.cpp"
    "src/burn/drv/pre90s/d_snk68.cpp"
    "src/burn/drv/pre90s/d_solomon.cpp"
    "src/burn/drv/pre90s/d_sonson.cpp"
    "src/burn/drv/pre90s/d_spacefb.cpp"
    "src/burn/drv/pre90s/d_speedbal.cpp"
    "src/burn/drv/pre90s/d_sprcros2.cpp"
    "src/burn/drv/pre90s/d_srumbler.cpp"
    "src/burn/drv/pre90s/d_ssozumo.cpp"
    "src/burn/drv/pre90s/d_sstrangr.cpp"
    "src/burn/drv/pre90s/d_starwars.cpp"
    "src/burn/drv/pre90s/d_stfight.cpp"
    "src/burn/drv/pre90s/d_sub.cpp"
    "src/burn/drv/pre90s/d_suna8.cpp"
    "src/burn/drv/pre90s/d_tagteam.cpp"
    "src/burn/drv/pre90s/d_tail2nose.cpp"
    "src/burn/drv/pre90s/d_tankbust.cpp"
    "src/burn/drv/pre90s/d_tbowl.cpp"
    "src/burn/drv/pre90s/d_tceptor.cpp"
    "src/burn/drv/pre90s/d_tecmo.cpp"
    "src/burn/drv/pre90s/d_tempest.cpp"
    "src/burn/drv/pre90s/d_terracre.cpp"
    "src/burn/drv/pre90s/d_thedeep.cpp"
    "src/burn/drv/pre90s/d_thepit.cpp"
    "src/burn/drv/pre90s/d_thief.cpp"
    "src/burn/drv/pre90s/d_tigeroad.cpp"
    "src/burn/drv/pre90s/d_timelimt.cpp"
    "src/burn/drv/pre90s/d_toki.cpp"
    "src/burn/drv/pre90s/d_toypop.cpp"
    "src/burn/drv/pre90s/d_travrusa.cpp"
    "src/burn/drv/pre90s/d_tsamurai.cpp"
    "src/burn/drv/pre90s/d_usgames.cpp"
    "src/burn/drv/pre90s/d_vastar.cpp"
    "src/burn/drv/pre90s/d_vball.cpp"
    "src/burn/drv/pre90s/d_vicdual.cpp"
    "src/burn/drv/pre90s/d_vulgus.cpp"
    "src/burn/drv/pre90s/d_wallc.cpp"
    "src/burn/drv/pre90s/d_warpsped.cpp"
    "src/burn/drv/pre90s/d_warpwarp.cpp"
    "src/burn/drv/pre90s/d_wc90.cpp"
    "src/burn/drv/pre90s/d_wc90b.cpp"
    "src/burn/drv/pre90s/d_williams.cpp"
    "src/burn/drv/pre90s/d_wiping.cpp"
    "src/burn/drv/pre90s/d_wiz.cpp"
    "src/burn/drv/pre90s/d_wwfsstar.cpp"
    "src/burn/drv/pre90s/d_xain.cpp"
    "src/burn/drv/pre90s/d_xxmissio.cpp"
    "src/burn/drv/pre90s/d_xyonix.cpp"
    "src/burn/drv/pre90s/d_zodiack.cpp"
)
source_group("Burn\\drv\\pre90s" FILES ${Burn__drv__pre90s})

set(Burn__drv__psikyo
    "src/burn/drv/psikyo/d_psikyo.cpp"
    "src/burn/drv/psikyo/d_psikyo4.cpp"
    "src/burn/drv/psikyo/d_psikyosh.cpp"
    "src/burn/drv/psikyo/psikyo_palette.cpp"
    "src/burn/drv/psikyo/psikyo_sprite.cpp"
    "src/burn/drv/psikyo/psikyo_tile.cpp"
    "src/burn/drv/psikyo/psikyosh_render.cpp"
)
source_group("Burn\\drv\\psikyo" FILES ${Burn__drv__psikyo})

set(Burn__drv__pst90s
    "src/burn/drv/pre90s/d_mjkjidai.cpp"
    "src/burn/drv/pre90s/d_spdodgeb.cpp"
    "src/burn/drv/pre90s/d_stuntair.cpp"
    "src/burn/drv/pre90s/d_tubep.cpp"
    "src/burn/drv/pst90s/d_1945kiii.cpp"
    "src/burn/drv/pst90s/d_20pacgal.cpp"
    "src/burn/drv/pst90s/d_3x3puzzl.cpp"
    "src/burn/drv/pst90s/d_aerofgt.cpp"
    "src/burn/drv/pst90s/d_airbustr.cpp"
    "src/burn/drv/pst90s/d_aquarium.cpp"
    "src/burn/drv/pst90s/d_bestleag.cpp"
    "src/burn/drv/pst90s/d_bigstrkb.cpp"
    "src/burn/drv/pst90s/d_blackt96.cpp"
    "src/burn/drv/pst90s/d_blmbycar.cpp"
    "src/burn/drv/pst90s/d_bloodbro.cpp"
    "src/burn/drv/pst90s/d_crospang.cpp"
    "src/burn/drv/pst90s/d_crshrace.cpp"
    "src/burn/drv/pst90s/d_cultures.cpp"
    "src/burn/drv/pst90s/d_dcon.cpp"
    "src/burn/drv/pst90s/d_ddragon3.cpp"
    "src/burn/drv/pst90s/d_deniam.cpp"
    "src/burn/drv/pst90s/d_diverboy.cpp"
    "src/burn/drv/pst90s/d_dooyong.cpp"
    "src/burn/drv/pst90s/d_dreamwld.cpp"
    "src/burn/drv/pst90s/d_drgnmst.cpp"
    "src/burn/drv/pst90s/d_drtomy.cpp"
    "src/burn/drv/pst90s/d_egghunt.cpp"
    "src/burn/drv/pst90s/d_esd16.cpp"
    "src/burn/drv/pst90s/d_f1gp.cpp"
    "src/burn/drv/pst90s/d_funybubl.cpp"
    "src/burn/drv/pst90s/d_fuukifg2.cpp"
    "src/burn/drv/pst90s/d_fuukifg3.cpp"
    "src/burn/drv/pst90s/d_gaelco.cpp"
    "src/burn/drv/pst90s/d_gaelco2.cpp"
    "src/burn/drv/pst90s/d_gaiden.cpp"
    "src/burn/drv/pst90s/d_galpani3.cpp"
    "src/burn/drv/pst90s/d_galpanic.cpp"
    "src/burn/drv/pst90s/d_galspnbl.cpp"
    "src/burn/drv/pst90s/d_glass.cpp"
    "src/burn/drv/pst90s/d_go2000.cpp"
    "src/burn/drv/pst90s/d_gotcha.cpp"
    "src/burn/drv/pst90s/d_gstream.cpp"
    "src/burn/drv/pst90s/d_gumbo.cpp"
    "src/burn/drv/pst90s/d_hyperpac.cpp"
    "src/burn/drv/pst90s/d_hyprduel.cpp"
    "src/burn/drv/pst90s/d_inufuku.cpp"
    "src/burn/drv/pst90s/d_itech32.cpp"
    "src/burn/drv/pst90s/d_jchan.cpp"
    "src/burn/drv/pst90s/d_kaneko16.cpp"
    "src/burn/drv/pst90s/d_kickgoal.cpp"
    "src/burn/drv/pst90s/d_legionna.cpp"
    "src/burn/drv/pst90s/d_limenko.cpp"
    "src/burn/drv/pst90s/d_lordgun.cpp"
    "src/burn/drv/pst90s/d_macrossp.cpp"
    "src/burn/drv/pst90s/d_mcatadv.cpp"
    "src/burn/drv/pst90s/d_metro.cpp"
    "src/burn/drv/pst90s/d_midas.cpp"
    "src/burn/drv/pst90s/d_mirage.cpp"
    "src/burn/drv/pst90s/d_missb2.cpp"
    "src/burn/drv/pst90s/d_mosaic.cpp"
    "src/burn/drv/pst90s/d_mugsmash.cpp"
    "src/burn/drv/pst90s/d_mwarr.cpp"
    "src/burn/drv/pst90s/d_namcos2.cpp"
    "src/burn/drv/pst90s/d_news.cpp"
    "src/burn/drv/pst90s/d_nmg5.cpp"
    "src/burn/drv/pst90s/d_nmk16.cpp"
    "src/burn/drv/pst90s/d_ohmygod.cpp"
    "src/burn/drv/pst90s/d_oneshot.cpp"
    "src/burn/drv/pst90s/d_onetwo.cpp"
    "src/burn/drv/pst90s/d_pass.cpp"
    "src/burn/drv/pst90s/d_patapata.cpp"
    "src/burn/drv/pst90s/d_pipedrm.cpp"
    "src/burn/drv/pst90s/d_pirates.cpp"
    "src/burn/drv/pst90s/d_pkscram.cpp"
    "src/burn/drv/pst90s/d_playmark.cpp"
    "src/burn/drv/pst90s/d_powerins.cpp"
    "src/burn/drv/pst90s/d_ppmast93.cpp"
    "src/burn/drv/pst90s/d_pushman.cpp"
    "src/burn/drv/pst90s/d_rabbit.cpp"
    "src/burn/drv/pst90s/d_raiden.cpp"
    "src/burn/drv/pst90s/d_raiden2.cpp"
    "src/burn/drv/pst90s/d_sandscrp.cpp"
    "src/burn/drv/pst90s/d_seta.cpp"
    "src/burn/drv/pst90s/d_seta2.cpp"
    "src/burn/drv/pst90s/d_shadfrce.cpp"
    "src/burn/drv/pst90s/d_silkroad.cpp"
    "src/burn/drv/pst90s/d_silvmil.cpp"
    "src/burn/drv/pst90s/d_speedspn.cpp"
    "src/burn/drv/pst90s/d_ssv.cpp"
    "src/burn/drv/pst90s/d_suna16.cpp"
    "src/burn/drv/pst90s/d_supduck.cpp"
    "src/burn/drv/pst90s/d_suprnova.cpp"
    "src/burn/drv/pst90s/d_taotaido.cpp"
    "src/burn/drv/pst90s/d_targeth.cpp"
    "src/burn/drv/pst90s/d_tecmo16.cpp"
    "src/burn/drv/pst90s/d_tecmosys.cpp"
    "src/burn/drv/pst90s/d_tetrisp2.cpp"
    "src/burn/drv/pst90s/d_thoop2.cpp"
    "src/burn/drv/pst90s/d_tumbleb.cpp"
    "src/burn/drv/pst90s/d_unico.cpp"
    "src/burn/drv/pst90s/d_vamphalf.cpp"
    "src/burn/drv/pst90s/d_vegaeo.cpp"
    "src/burn/drv/pst90s/d_vmetal.cpp"
    "src/burn/drv/pst90s/d_welltris.cpp"
    "src/burn/drv/pst90s/d_wrally.cpp"
    "src/burn/drv/pst90s/d_wwfwfest.cpp"
    "src/burn/drv/pst90s/d_xorworld.cpp"
    "src/burn/drv/pst90s/d_yunsun16.cpp"
    "src/burn/drv/pst90s/d_yunsung8.cpp"
    "src/burn/drv/pst90s/d_zerozone.cpp"
)
source_group("Burn\\drv\\pst90s" FILES ${Burn__drv__pst90s})

set(Burn__drv__sega
    "src/burn/drv/sega/d_angelkds.cpp"
    "src/burn/drv/sega/d_appoooh.cpp"
    "src/burn/drv/sega/d_bankp.cpp"
    "src/burn/drv/sega/d_dotrikun.cpp"
    "src/burn/drv/sega/d_hangon.cpp"
    "src/burn/drv/sega/d_outrun.cpp"
    "src/burn/drv/sega/d_segac2.cpp"
    "src/burn/drv/sega/d_segae.cpp"
    "src/burn/drv/sega/d_segag80v.cpp"
    "src/burn/drv/sega/d_suprloco.cpp"
    "src/burn/drv/sega/d_sys1.cpp"
    "src/burn/drv/sega/d_sys16a.cpp"
    "src/burn/drv/sega/d_sys16b.cpp"
    "src/burn/drv/sega/d_sys18.cpp"
    "src/burn/drv/sega/d_sys24.cpp"
    "src/burn/drv/sega/d_turbo.cpp"
    "src/burn/drv/sega/d_xbrd.cpp"
    "src/burn/drv/sega/d_ybrd.cpp"
    "src/burn/drv/sega/d_zaxxon.cpp"
    "src/burn/drv/sega/fd1089.cpp"
    "src/burn/drv/sega/fd1094.cpp"
    "src/burn/drv/sega/fd1094_intf.cpp"
    "src/burn/drv/sega/genesis_vid.cpp"
    "src/burn/drv/sega/mc8123.cpp"
    "src/burn/drv/sega/sega_315_5195.cpp"
    "src/burn/drv/sega/sys16_fd1094.cpp"
    "src/burn/drv/sega/sys16_gfx.cpp"
    "src/burn/drv/sega/sys16_run.cpp"
    "src/burn/drv/sega/usb_snd.cpp"
)
source_group("Burn\\drv\\sega" FILES ${Burn__drv__sega})

set(Burn__drv__sg1000
    "src/burn/drv/sg1000/d_sg1000.cpp"
)
source_group("Burn\\drv\\sg1000" FILES ${Burn__drv__sg1000})

set(Burn__drv__sms
    "src/burn/drv/sms/d_sms.cpp"
    "src/burn/drv/sms/sms.cpp"
    "src/burn/drv/sms/smsfmintf.cpp"
    "src/burn/drv/sms/smspio.cpp"
    "src/burn/drv/sms/smsrender.cpp"
    "src/burn/drv/sms/smssound.cpp"
    "src/burn/drv/sms/smssystem.cpp"
    "src/burn/drv/sms/smstms.cpp"
    "src/burn/drv/sms/smsvdp.cpp"
)
source_group("Burn\\drv\\sms" FILES ${Burn__drv__sms})

set(Burn__drv__spectrum
    "src/burn/drv/spectrum/d_spectrum.cpp"
    "src/burn/drv/spectrum/spectrum_states.cpp"
)
source_group("Burn\\drv\\spectrum" FILES ${Burn__drv__spectrum})

set(Burn__drv__taito
    "src/burn/drv/taito/cchip.cpp"
    "src/burn/drv/taito/d_arkanoid.cpp"
    "src/burn/drv/taito/d_ashnojoe.cpp"
    "src/burn/drv/taito/d_asuka.cpp"
    "src/burn/drv/taito/d_bublbobl.cpp"
    "src/burn/drv/taito/d_buggychl.cpp"
    "src/burn/drv/taito/d_chaknpop.cpp"
    "src/burn/drv/taito/d_crbaloon.cpp"
    "src/burn/drv/taito/d_darius2.cpp"
    "src/burn/drv/taito/d_darkmist.cpp"
    "src/burn/drv/taito/d_exzisus.cpp"
    "src/burn/drv/taito/d_flstory.cpp"
    "src/burn/drv/taito/d_groundfx.cpp"
    "src/burn/drv/taito/d_gunbuster.cpp"
    "src/burn/drv/taito/d_jollyjgr.cpp"
    "src/burn/drv/taito/d_ksayakyu.cpp"
    "src/burn/drv/taito/d_lkage.cpp"
    "src/burn/drv/taito/d_mexico86.cpp"
    "src/burn/drv/taito/d_minivdr.cpp"
    "src/burn/drv/taito/d_msisaac.cpp"
    "src/burn/drv/taito/d_othunder.cpp"
    "src/burn/drv/taito/d_qix.cpp"
    "src/burn/drv/taito/d_retofinv.cpp"
    "src/burn/drv/taito/d_rollrace.cpp"
    "src/burn/drv/taito/d_slapshot.cpp"
    "src/burn/drv/taito/d_ssrj.cpp"
    "src/burn/drv/taito/d_superchs.cpp"
    "src/burn/drv/taito/d_supridr.cpp"
    "src/burn/drv/taito/d_taitob.cpp"
    "src/burn/drv/taito/d_taitof2.cpp"
    "src/burn/drv/taito/d_taitof3.cpp"
    "src/burn/drv/taito/d_taitoh.cpp"
    "src/burn/drv/taito/d_taitol.cpp"
    "src/burn/drv/taito/d_taitomisc.cpp"
    "src/burn/drv/taito/d_taitosj.cpp"
    "src/burn/drv/taito/d_taitox.cpp"
    "src/burn/drv/taito/d_taitoz.cpp"
    "src/burn/drv/taito/d_tnzs.cpp"
    "src/burn/drv/taito/d_undrfire.cpp"
    "src/burn/drv/taito/d_wyvernf0.cpp"
    "src/burn/drv/taito/pc080sn.cpp"
    "src/burn/drv/taito/pc090oj.cpp"
    "src/burn/drv/taito/taito.cpp"
    "src/burn/drv/taito/taito_ic.cpp"
    "src/burn/drv/taito/taito_m68705.cpp"
    "src/burn/drv/taito/taitof3_snd.cpp"
    "src/burn/drv/taito/taitof3_video.cpp"
    "src/burn/drv/taito/tc0100scn.cpp"
    "src/burn/drv/taito/tc0110pcr.cpp"
    "src/burn/drv/taito/tc0140syt.cpp"
    "src/burn/drv/taito/tc0150rod.cpp"
    "src/burn/drv/taito/tc0180vcu.cpp"
    "src/burn/drv/taito/tc0220ioc.cpp"
    "src/burn/drv/taito/tc0280grd.cpp"
    "src/burn/drv/taito/tc0360pri.cpp"
    "src/burn/drv/taito/tc0480scp.cpp"
    "src/burn/drv/taito/tc0510nio.cpp"
    "src/burn/drv/taito/tc0640fio.cpp"
    "src/burn/drv/taito/tnzs_prot.cpp"
)
source_group("Burn\\drv\\taito" FILES ${Burn__drv__taito})

set(Burn__drv__toaplan
    "src/burn/drv/toaplan/d_batrider.cpp"
    "src/burn/drv/toaplan/d_batsugun.cpp"
    "src/burn/drv/toaplan/d_battleg.cpp"
    "src/burn/drv/toaplan/d_bbakraid.cpp"
    "src/burn/drv/toaplan/d_dogyuun.cpp"
    "src/burn/drv/toaplan/d_enmadaio.cpp"
    "src/burn/drv/toaplan/d_fixeight.cpp"
    "src/burn/drv/toaplan/d_ghox.cpp"
    "src/burn/drv/toaplan/d_kbash.cpp"
    "src/burn/drv/toaplan/d_kbash2.cpp"
    "src/burn/drv/toaplan/d_mahoudai.cpp"
    "src/burn/drv/toaplan/d_pipibibs.cpp"
    "src/burn/drv/toaplan/d_shippumd.cpp"
    "src/burn/drv/toaplan/d_slapfght.cpp"
    "src/burn/drv/toaplan/d_snowbro2.cpp"
    "src/burn/drv/toaplan/d_tekipaki.cpp"
    "src/burn/drv/toaplan/d_toaplan1.cpp"
    "src/burn/drv/toaplan/d_truxton2.cpp"
    "src/burn/drv/toaplan/d_twincobr.cpp"
    "src/burn/drv/toaplan/d_vfive.cpp"
    "src/burn/drv/toaplan/d_wardner.cpp"
    "src/burn/drv/toaplan/toa_bcu2.cpp"
    "src/burn/drv/toaplan/toa_extratext.cpp"
    "src/burn/drv/toaplan/toa_gp9001.cpp"
    "src/burn/drv/toaplan/toa_palette.cpp"
    "src/burn/drv/toaplan/toaplan.cpp"
    "src/burn/drv/toaplan/toaplan1.cpp"
)
source_group("Burn\\drv\\toaplan" FILES ${Burn__drv__toaplan})

set(Burn__snd
    "src/burn/snd/asteroids.cpp"
    "src/burn/snd/asteroids.h"
    "src/burn/snd/ay8910.c"
    "src/burn/snd/ay8910.h"
    "src/burn/snd/burn_md2612.cpp"
    "src/burn/snd/burn_md2612.h"
    "src/burn/snd/burn_y8950.cpp"
    "src/burn/snd/burn_y8950.h"
    "src/burn/snd/burn_ym2151.cpp"
    "src/burn/snd/burn_ym2151.h"
    "src/burn/snd/burn_ym2203.cpp"
    "src/burn/snd/burn_ym2203.h"
    "src/burn/snd/burn_ym2413.cpp"
    "src/burn/snd/burn_ym2413.h"
    "src/burn/snd/burn_ym2608.cpp"
    "src/burn/snd/burn_ym2608.h"
    "src/burn/snd/burn_ym2610.cpp"
    "src/burn/snd/burn_ym2610.h"
    "src/burn/snd/burn_ym2612.cpp"
    "src/burn/snd/burn_ym2612.h"
    "src/burn/snd/burn_ym3526.cpp"
    "src/burn/snd/burn_ym3526.h"
    "src/burn/snd/burn_ym3812.cpp"
    "src/burn/snd/burn_ym3812.h"
    "src/burn/snd/burn_ymf262.cpp"
    "src/burn/snd/burn_ymf262.h"
    "src/burn/snd/burn_ymf278b.cpp"
    "src/burn/snd/burn_ymf278b.h"
    "src/burn/snd/bzone.cpp"
    "src/burn/snd/bzone.h"
    "src/burn/snd/c140.cpp"
    "src/burn/snd/c140.h"
    "src/burn/snd/c6280.cpp"
    "src/burn/snd/c6280.h"
    "src/burn/snd/dac.cpp"
    "src/burn/snd/dac.h"
    "src/burn/snd/es5506.cpp"
    "src/burn/snd/es5506.h"
    "src/burn/snd/es8712.cpp"
    "src/burn/snd/es8712.h"
    "src/burn/snd/flower.cpp"
    "src/burn/snd/flower.h"
    "src/burn/snd/flt_rc.cpp"
    "src/burn/snd/flt_rc.h"
    "src/burn/snd/fm.c"
    "src/burn/snd/fm.h"
    "src/burn/snd/fmopl.c"
    "src/burn/snd/fmopl.h"
    "src/burn/snd/gaelco.cpp"
    "src/burn/snd/gaelco.h"
    "src/burn/snd/hc55516.cpp"
    "src/burn/snd/hc55516.h"
    "src/burn/snd/i5000.cpp"
    "src/burn/snd/i5000.h"
    "src/burn/snd/ics2115.cpp"
    "src/burn/snd/ics2115.h"
    "src/burn/snd/iremga20.cpp"
    "src/burn/snd/iremga20.h"
    "src/burn/snd/k005289.cpp"
    "src/burn/snd/k005289.h"
    "src/burn/snd/k007232.cpp"
    "src/burn/snd/k007232.h"
    "src/burn/snd/k051649.cpp"
    "src/burn/snd/k051649.h"
    "src/burn/snd/k053260.cpp"
    "src/burn/snd/k053260.h"
    "src/burn/snd/k054539.cpp"
    "src/burn/snd/k054539.h"
    "src/burn/snd/llander.cpp"
    "src/burn/snd/llander.h"
    "src/burn/snd/msm5205.cpp"
    "src/burn/snd/msm5205.h"
    "src/burn/snd/msm5232.cpp"
    "src/burn/snd/msm5232.h"
    "src/burn/snd/msm6295.cpp"
    "src/burn/snd/msm6295.h"
    "src/burn/snd/namco_snd.cpp"
    "src/burn/snd/namco_snd.h"
    "src/burn/snd/nes_apu.cpp"
    "src/burn/snd/nes_apu.h"
    "src/burn/snd/nes_defs.h"
    "src/burn/snd/phoenixsound.cpp"
    "src/burn/snd/phoenixsound.h"
    "src/burn/snd/pleiadssound.cpp"
    "src/burn/snd/pleiadssound.h"
    "src/burn/snd/pokey.cpp"
    "src/burn/snd/pokey.h"
    "src/burn/snd/redbaron.cpp"
    "src/burn/snd/redbaron.h"
    "src/burn/snd/rescap.h"
    "src/burn/snd/rf5c68.cpp"
    "src/burn/snd/rf5c68.h"
    "src/burn/snd/s14001a.cpp"
    "src/burn/snd/s14001a.h"
    "src/burn/snd/saa1099.cpp"
    "src/burn/snd/saa1099.h"
    "src/burn/snd/samples.cpp"
    "src/burn/snd/samples.h"
    "src/burn/snd/segapcm.cpp"
    "src/burn/snd/segapcm.h"
    "src/burn/snd/sn76477.cpp"
    "src/burn/snd/sn76477.h"
    "src/burn/snd/sn76496.cpp"
    "src/burn/snd/sn76496.h"
    "src/burn/snd/snk6502_sound.cpp"
    "src/burn/snd/snk6502_sound.h"
    "src/burn/snd/sp0250.cpp"
    "src/burn/snd/sp0250.h"
    "src/burn/snd/sp0256.cpp"
    "src/burn/snd/sp0256.h"
    "src/burn/snd/tms36xx.cpp"
    "src/burn/snd/tms36xx.h"
    "src/burn/snd/tms5110.cpp"
    "src/burn/snd/tms5110.h"
    "src/burn/snd/tms5110_tables.h"
    "src/burn/snd/tms5220.cpp"
    "src/burn/snd/tms5220.h"
    "src/burn/snd/tms5220_tables.h"
    "src/burn/snd/upd7759.cpp"
    "src/burn/snd/upd7759.h"
    "src/burn/snd/vlm5030.cpp"
    "src/burn/snd/vlm5030.h"
    "src/burn/snd/wiping.cpp"
    "src/burn/snd/wiping.h"
    "src/burn/snd/x1010.cpp"
    "src/burn/snd/x1010.h"
    "src/burn/snd/ym2151.c"
    "src/burn/snd/ym2151.h"
    "src/burn/snd/ym2413.c"
    "src/burn/snd/ym2413.h"
    "src/burn/snd/ym2612.c"
    "src/burn/snd/ym2612.h"
    "src/burn/snd/ymdeltat.c"
    "src/burn/snd/ymdeltat.h"
    "src/burn/snd/ymf262.cpp"
    "src/burn/snd/ymf262.h"
    "src/burn/snd/ymf278b.c"
    "src/burn/snd/ymf278b.h"
    "src/burn/snd/ymz280b.cpp"
    "src/burn/snd/ymz280b.h"
)
source_group("Burn\\snd" FILES ${Burn__snd})

set(burner
    "src/burner/burner.h"
    "src/burner/conc.cpp"
    "src/burner/cong.cpp"
    "src/burner/dat.cpp"
    "src/burner/dynhuff.cpp"
    "src/burner/dynhuff.h"
    "src/burner/gamc.cpp"
    "src/burner/gameinp.h"
    "src/burner/gami.cpp"
    "src/burner/image.cpp"
    "src/burner/ioapi.c"
    "src/burner/ioapi.h"
    "src/burner/luaengine.cpp"
    "src/burner/luaengine.h"
    "src/burner/luasav.cpp"
    "src/burner/luasav.h"
    "src/burner/misc.cpp"
    "src/burner/neocdlist.h"
    "src/burner/sshot.cpp"
    "src/burner/state.cpp"
    "src/burner/statec.cpp"
    "src/burner/title.h"
    "src/burner/un7z.cpp"
    "src/burner/un7z.h"
    "src/burner/unzip.c"
    "src/burner/unzip.h"
    "src/burner/zipfn.cpp"
)
source_group("burner" FILES ${burner})

set(burner__win32
    "src/burner/win32/about.cpp"
    "src/burner/win32/avi.cpp"
    "src/burner/win32/burner_win32.h"
    "src/burner/win32/bzip.cpp"
    "src/burner/win32/choose_monitor.cpp"
    "src/burner/win32/cona.cpp"
    "src/burner/win32/d3dkmt_sync.cpp"
    "src/burner/win32/d3dkmt_sync.h"
    "src/burner/win32/debugger.cpp"
    "src/burner/win32/drv.cpp"
    "src/burner/win32/fbn_ggpo.cpp"
    "src/burner/win32/fbn_ggpo_perfmon.cpp"
    "src/burner/win32/fbn_network.cpp"
    "src/burner/win32/gameinfo.cpp"
    "src/burner/win32/image_win32.cpp"
    "src/burner/win32/inpc.cpp"
    "src/burner/win32/inpcheat.cpp"
    "src/burner/win32/inpd.cpp"
    "src/burner/win32/inpdipsw.cpp"
    "src/burner/win32/inps.cpp"
    "src/burner/win32/ips_manager.cpp"
    "src/burner/win32/localise.cpp"
    "src/burner/win32/localise_download.cpp"
    "src/burner/win32/localise_gamelist.cpp"
    "src/burner/win32/luaconsole.cpp"
    "src/burner/win32/main.cpp"
    "src/burner/win32/media.cpp"
    "src/burner/win32/memcard.cpp"
    "src/burner/win32/menu.cpp"
    "src/burner/win32/misc_win32.cpp"
    "src/burner/win32/neocdlist.cpp"
    "src/burner/win32/neocdsel.cpp"
    "src/burner/win32/numdial.cpp"
    "src/burner/win32/paletteviewer.cpp"
    "src/burner/win32/placeholder.cpp"
    "src/burner/win32/popup_win32.cpp"
    "src/burner/win32/progress.cpp"
    "src/burner/win32/replay.cpp"
    "src/burner/win32/res.cpp"
    "src/burner/win32/resource.h"
    "src/burner/win32/resource_string.h"
    "src/burner/win32/roms.cpp"
    "src/burner/win32/run.cpp"
    "src/burner/win32/scrn.cpp"
    "src/burner/win32/sel.cpp"
    "src/burner/win32/sfactd.cpp"
    "src/burner/win32/splash.cpp"
    "src/burner/win32/stated.cpp"
    "src/burner/win32/support_paths.cpp"
    "src/burner/win32/systeminfo.cpp"
    "src/burner/win32/wave.cpp"
)
source_group("burner\\win32" FILES ${burner__win32})

set(cpus
    "src/cpu/adsp2100_intf.cpp"
    "src/cpu/adsp2100_intf.h"
    "src/cpu/arm7_intf.cpp"
    "src/cpu/arm7_intf.h"
    "src/cpu/arm_intf.cpp"
    "src/cpu/arm_intf.h"
    "src/cpu/h6280_intf.cpp"
    "src/cpu/h6280_intf.h"
    "src/cpu/hd6309_intf.cpp"
    "src/cpu/hd6309_intf.h"
    "src/cpu/konami_intf.cpp"
    "src/cpu/konami_intf.h"
    "src/cpu/m6502_intf.cpp"
    "src/cpu/m6502_intf.h"
    "src/cpu/m68000_debug.h"
    "src/cpu/m68000_intf.cpp"
    "src/cpu/m68000_intf.h"
    "src/cpu/m6800_intf.cpp"
    "src/cpu/m6800_intf.h"
    "src/cpu/m6805_intf.cpp"
    "src/cpu/m6805_intf.h"
    "src/cpu/m6809/m6809.h"
    "src/cpu/m6809_intf.cpp"
    "src/cpu/m6809_intf.h"
    "src/cpu/mips3_intf.cpp"
    "src/cpu/mips3_intf.h"
    "src/cpu/nec_intf.cpp"
    "src/cpu/nec_intf.h"
    "src/cpu/pic16c5x_intf.cpp"
    "src/cpu/pic16c5x_intf.h"
    "src/cpu/s2650_intf.cpp"
    "src/cpu/s2650_intf.h"
    "src/cpu/sh2_intf.h"
    "src/cpu/tlcs90_intf.cpp"
    "src/cpu/tlcs90_intf.h"
    "src/cpu/tms34_intf.cpp"
    "src/cpu/tms34_intf.h"
    "src/cpu/upd7810_intf.h"
    "src/cpu/v60_intf.h"
    "src/cpu/z180_intf.cpp"
    "src/cpu/z180_intf.h"
    "src/cpu/z80_intf.cpp"
    "src/cpu/z80_intf.h"
)
source_group("cpus" FILES ${cpus})

set(cpus__adsp2100
    "src/cpu/adsp2100/adsp2100.cpp"
)
source_group("cpus\\adsp2100" FILES ${cpus__adsp2100})

set(cpus__arm
    "src/cpu/arm/arm.cpp"
)
source_group("cpus\\arm" FILES ${cpus__arm})

set(cpus__arm7
    "src/cpu/arm7/arm7.cpp"
    "src/cpu/arm7/arm7core.h"
)
source_group("cpus\\arm7" FILES ${cpus__arm7})

set(cpus__e132xs
    "src/cpu/e132xs/e132xs.cpp"
    "src/cpu/e132xs/e132xs.h"
    "src/cpu/e132xs/e132xsop.inc"
)
source_group("cpus\\e132xs" FILES ${cpus__e132xs})

set(cpus__h6280
    "src/cpu/h6280/h6280.cpp"
    "src/cpu/h6280/h6280.h"
    "src/cpu/h6280/h6280ops.h"
)
source_group("cpus\\h6280" FILES ${cpus__h6280})

set(cpus__hd6309
    "src/cpu/hd6309/hd6309.cpp"
    "src/cpu/hd6309/hd6309.h"
)
source_group("cpus\\hd6309" FILES ${cpus__hd6309})

set(cpus__i8039
    "src/cpu/i8039/i8039.cpp"
    "src/cpu/i8039/i8039.h"
)
source_group("cpus\\i8039" FILES ${cpus__i8039})

set(cpus__i8051
    "src/cpu/i8051/mcs51.cpp"
)
source_group("cpus\\i8051" FILES ${cpus__i8051})

set(cpus__i8x41
    "src/cpu/i8x41/i8x41.cpp"
)
source_group("cpus\\i8x41" FILES ${cpus__i8x41})

set(cpus__konami
    "src/cpu/konami/konami.cpp"
    "src/cpu/konami/konami.h"
)
source_group("cpus\\konami" FILES ${cpus__konami})

set(cpus__m6502
    "src/cpu/m6502/ill02.h"
    "src/cpu/m6502/m6502.cpp"
    "src/cpu/m6502/m6502.h"
    "src/cpu/m6502/ops02.h"
    "src/cpu/m6502/opsc02.h"
    "src/cpu/m6502/opsn2a03.h"
)
source_group("cpus\\m6502" FILES ${cpus__m6502})

set(cpus__m6800
    "src/cpu/m6800/m6800.cpp"
    "src/cpu/m6800/m6800.h"
)
source_group("cpus\\m6800" FILES ${cpus__m6800})

set(cpus__m6805
    "src/cpu/m6805/m6805.cpp"
    "src/cpu/m6805/m6805.h"
)
source_group("cpus\\m6805" FILES ${cpus__m6805})

set(cpus__m6809
    "src/cpu/m6809/m6809.cpp"
)
source_group("cpus\\m6809" FILES ${cpus__m6809})

set(cpus__m68k
    "src/cpu/m68k/m68kcpu.c"
    "src/cpu/m68k/m68kdasm.c"
    # "src/cpu/m68k/m68kmake.c"
)
source_group("cpus\\m68k" FILES ${cpus__m68k})

set(cpus__mips
    "src/cpu/mips3/cop0.cpp"
    "src/cpu/mips3/cop1.cpp"
    "src/cpu/mips3/mips3.cpp"
)
source_group("cpus\\mips" FILES ${cpus__mips})

set(cpus__nec
    "src/cpu/nec/nec.cpp"
    "src/cpu/nec/nec.h"
    "src/cpu/nec/necea.h"
    "src/cpu/nec/necinstr.h"
    "src/cpu/nec/necmacro.h"
    "src/cpu/nec/necmodrm.h"
    "src/cpu/nec/necpriv.h"
    "src/cpu/nec/v25.cpp"
    "src/cpu/nec/v25instr.h"
    "src/cpu/nec/v25priv.h"
)
source_group("cpus\\nec" FILES ${cpus__nec})

set(cpus__pic16c5x
    "src/cpu/pic16c5x/pic16c5x.cpp"
)
source_group("cpus\\pic16c5x" FILES ${cpus__pic16c5x})

set(cpus__s2650
    "src/cpu/s2650/s2650.cpp"
    "src/cpu/s2650/s2650.h"
)
source_group("cpus\\s2650" FILES ${cpus__s2650})

set(cpus__sh2
    "src/cpu/sh2/sh2.cpp"
)
source_group("cpus\\sh2" FILES ${cpus__sh2})

set(cpus__tlcs90
    "src/cpu/tlcs90/tlcs90.cpp"
)
source_group("cpus\\tlcs90" FILES ${cpus__tlcs90})

set(cpus__tms32010
    "src/cpu/tms32010/tms32010.cpp"
)
source_group("cpus\\tms32010" FILES ${cpus__tms32010})

set(cpus__tms34
    "src/cpu/tms34/tms34010.cpp"
    "src/cpu/tms34/tms34010.h"
)
source_group("cpus\\tms34" FILES ${cpus__tms34})

set(cpus__upd7725
    "src/cpu/upd7725/upd7725.cpp"
)
source_group("cpus\\upd7725" FILES ${cpus__upd7725})

set(cpus__upd7810
    "src/cpu/upd7810/upd7810.cpp"
)
source_group("cpus\\upd7810" FILES ${cpus__upd7810})

set(cpus__v60
    "src/cpu/v60/v60.cpp"
)
source_group("cpus\\v60" FILES ${cpus__v60})

set(cpus__z180
    "src/cpu/z180/z180.cpp"
)
source_group("cpus\\z180" FILES ${cpus__z180})

set(cpus__z80
    "src/cpu/z80/z80.cpp"
    "src/cpu/z80/z80.h"
    "src/cpu/z80/z80ctc.cpp"
    "src/cpu/z80/z80daisy.cpp"
    "src/cpu/z80/z80daisy.h"
    "src/cpu/z80/z80pio.cpp"
)
source_group("cpus\\z80" FILES ${cpus__z80})

set(generated
    "generated/m68kops.c"
)
source_group("generated" FILES ${generated})

set(ggpo
    "src/dep/ggpo/include/ggpo_perfmon.h"
    "src/dep/ggpo/include/ggponet.h"
)
source_group("ggpo" FILES ${ggpo})

set(mister
        "src/dep/mister/lz4/lz4.h"
        "src/dep/mister/lz4/lz4.c"
        "src/dep/mister/lz4/lz4hc.h"
        "src/dep/mister/lz4/lz4hc.c"
        "src/dep/mister/groovymister.h"
        "src/dep/mister/groovymister.cpp"
)
source_group("mister" FILES ${mister})

set(switchres
        "src/dep/switchres/switchres.h"
        "src/dep/switchres/switchres.cpp"
        "src/dep/switchres/display.h"
        "src/dep/switchres/display.cpp"
        "src/dep/switchres/modeline.h"
        "src/dep/switchres/modeline.cpp"
        "src/dep/switchres/monitor.h"
        "src/dep/switchres/monitor.cpp"
        "src/dep/switchres/log.h"
        "src/dep/switchres/log.cpp"
)
source_group("switchres" FILES ${switchres})

set(interfaces
    "src/intf/interface.cpp"
    "src/intf/interface.h"
    "src/intf/mister.cpp"
    "src/intf/mister.h"
)
source_group("interfaces" FILES ${interfaces})

set(interfaces__audio
    "src/intf/audio/aud_dsp.cpp"
    "src/intf/audio/aud_dsp.h"
    "src/intf/audio/aud_interface.cpp"
    "src/intf/audio/lowpass2.cpp"
    "src/intf/audio/lowpass2.h"
)
source_group("interfaces\\audio" FILES ${interfaces__audio})

set(interfaces__audio__win32
    "src/intf/audio/win32/aud_dsound3.cpp"
    "src/intf/audio/win32/aud_mister.cpp"
    "src/intf/audio/win32/aud_wasapi.cpp"
    "src/intf/audio/win32/aud_xaudio2.cpp"
    "src/intf/audio/win32/dsound_core.cpp"
    "src/intf/audio/win32/dsound_core.h"
)
source_group("interfaces\\audio\\win32" FILES ${interfaces__audio__win32})

set(interfaces__cd
    "src/intf/cd/cd_interface.cpp"
    "src/intf/cd/cd_interface.h"
)
source_group("interfaces\\cd" FILES ${interfaces__cd})

set(interfaces__cd__win32
    "src/intf/cd/win32/cd_img.cpp"
)
source_group("interfaces\\cd\\win32" FILES ${interfaces__cd__win32})

set(interfaces__input
    "src/intf/input/inp_interface.cpp"
    "src/intf/input/inp_keys.h"
)
source_group("interfaces\\input" FILES ${interfaces__input})

set(interfaces__input__win32
    "src/intf/input/win32/dinput_core.cpp"
    "src/intf/input/win32/dinput_core.h"
    "src/intf/input/win32/inp_dinput.cpp"
    "src/intf/input/win32/inp_mister.cpp"
)
source_group("interfaces\\input\\win32" FILES ${interfaces__input__win32})

set(interfaces__perf
    "src/intf/perfcount/prf_interface.cpp"
)
source_group("interfaces\\perf" FILES ${interfaces__perf})

set(interfaces__perf__win32
    "src/intf/perfcount/win32/prf_performance_counter.cpp"
)
source_group("interfaces\\perf\\win32" FILES ${interfaces__perf__win32})

set(interfaces__video
    "src/intf/video/vid_interface.cpp"
    "src/intf/video/vid_softfx.cpp"
    "src/intf/video/vid_softfx.h"
    "src/intf/video/vid_support.cpp"
    "src/intf/video/vid_support.h"
)
source_group("interfaces\\video" FILES ${interfaces__video})

set(interfaces__video__scalers
    "src/intf/video/scalers/2xpm.cpp"
    "src/intf/video/scalers/2xsai.cpp"
    "src/intf/video/scalers/2xsaimmx.asm"
    "src/intf/video/scalers/ddt3x.cpp"
    "src/intf/video/scalers/eagle_fm.asm"
    "src/intf/video/scalers/epx.cpp"
    "src/intf/video/scalers/hq2x32.asm"
    "src/intf/video/scalers/hq2xs.cpp"
    "src/intf/video/scalers/hq2xs.h"
    "src/intf/video/scalers/hq2xs_16.cpp"
    "src/intf/video/scalers/hq3x32.asm"
    "src/intf/video/scalers/hq3xs.cpp"
    "src/intf/video/scalers/hq3xs.h"
    "src/intf/video/scalers/hq4x32.asm"
    "src/intf/video/scalers/hq_shared32.cpp"
    "src/intf/video/scalers/hq_shared32.h"
    "src/intf/video/scalers/interp.h"
    "src/intf/video/scalers/scale2x.h"
    "src/intf/video/scalers/scale2x_vc.h"
    "src/intf/video/scalers/scale3x.h"
    "src/intf/video/scalers/superscale.asm"
    "src/intf/video/scalers/xbr.cpp"
    "src/intf/video/scalers/xbr.h"
)
source_group("interfaces\\video\\scalers" FILES ${interfaces__video__scalers})

set(interfaces__video__win32
    "src/intf/video/win32/ddraw_core.cpp"
    "src/intf/video/win32/ddraw_core.h"
    "src/intf/video/win32/rgb_pattern.h"
    "src/intf/video/win32/stb_image.h"
    "src/intf/video/win32/vid_d3d.cpp"
    "src/intf/video/win32/vid_ddraw.cpp"
    "src/intf/video/win32/vid_ddrawfx.cpp"
    "src/intf/video/win32/vid_detector.cpp"
    "src/intf/video/win32/vid_detector.h"
    "src/intf/video/win32/vid_directx9.cpp"
    "src/intf/video/win32/vid_directx_support.cpp"
    "src/intf/video/win32/vid_directx_support.h"
    "src/intf/video/win32/vid_dynrender.cpp"
    "src/intf/video/win32/vid_dynrender.h"
    "src/intf/video/win32/vid_effect.cpp"
    "src/intf/video/win32/vid_effect.h"
    "src/intf/video/win32/vid_font.cpp"
    "src/intf/video/win32/vid_font.h"
    "src/intf/video/win32/vid_memorybuffer.cpp"
    "src/intf/video/win32/vid_memorybuffer.h"
    "src/intf/video/win32/vid_mister.cpp"
    "src/intf/video/win32/vid_overlay.cpp"
    "src/intf/video/win32/vid_overlay.h"
)
source_group("interfaces\\video\\win32" FILES ${interfaces__video__win32})

set(interfaces__video__win32__resource
    "src/intf/video/win32/resource/bicubic.fx"
)
source_group("interfaces\\video\\win32\\resource" FILES ${interfaces__video__win32__resource})

set(libs__7z
    "src/dep/libs/lib7z/7z.h"
    "src/dep/libs/lib7z/7zAlloc.c"
    "src/dep/libs/lib7z/7zAlloc.h"
    "src/dep/libs/lib7z/7zArcIn.c"
    "src/dep/libs/lib7z/7zBuf.c"
    "src/dep/libs/lib7z/7zBuf.h"
    "src/dep/libs/lib7z/7zBuf2.c"
    "src/dep/libs/lib7z/7zCrc.c"
    "src/dep/libs/lib7z/7zCrc.h"
    "src/dep/libs/lib7z/7zCrcOpt.c"
    "src/dep/libs/lib7z/7zDec.c"
    "src/dep/libs/lib7z/7zFile.c"
    "src/dep/libs/lib7z/7zFile.h"
    "src/dep/libs/lib7z/7zStream.c"
    "src/dep/libs/lib7z/7zTypes.h"
    "src/dep/libs/lib7z/7zVersion.h"
    "src/dep/libs/lib7z/Aes.c"
    "src/dep/libs/lib7z/Aes.h"
    "src/dep/libs/lib7z/AesOpt.c"
    "src/dep/libs/lib7z/Alloc.c"
    "src/dep/libs/lib7z/Alloc.h"
    "src/dep/libs/lib7z/Bcj2.c"
    "src/dep/libs/lib7z/Bcj2.h"
    "src/dep/libs/lib7z/Bcj2Enc.c"
    "src/dep/libs/lib7z/Bra.c"
    "src/dep/libs/lib7z/Bra.h"
    "src/dep/libs/lib7z/Bra86.c"
    "src/dep/libs/lib7z/BraIA64.c"
    "src/dep/libs/lib7z/Compiler.h"
    "src/dep/libs/lib7z/CpuArch.c"
    "src/dep/libs/lib7z/CpuArch.h"
    "src/dep/libs/lib7z/Delta.c"
    "src/dep/libs/lib7z/Delta.h"
    "src/dep/libs/lib7z/LzFind.c"
    "src/dep/libs/lib7z/LzFind.h"
    "src/dep/libs/lib7z/LzFindMt.c"
    "src/dep/libs/lib7z/LzFindMt.h"
    "src/dep/libs/lib7z/LzHash.h"
    "src/dep/libs/lib7z/Lzma2Dec.c"
    "src/dep/libs/lib7z/Lzma2Dec.h"
    "src/dep/libs/lib7z/Lzma2Enc.c"
    "src/dep/libs/lib7z/Lzma2Enc.h"
    "src/dep/libs/lib7z/Lzma86.h"
    "src/dep/libs/lib7z/Lzma86Dec.c"
    "src/dep/libs/lib7z/Lzma86Enc.c"
    "src/dep/libs/lib7z/LzmaDec.c"
    "src/dep/libs/lib7z/LzmaDec.h"
    "src/dep/libs/lib7z/LzmaEnc.c"
    "src/dep/libs/lib7z/LzmaEnc.h"
    "src/dep/libs/lib7z/LzmaLib.c"
    "src/dep/libs/lib7z/LzmaLib.h"
    "src/dep/libs/lib7z/MtCoder.c"
    "src/dep/libs/lib7z/MtCoder.h"
    "src/dep/libs/lib7z/Ppmd.h"
    "src/dep/libs/lib7z/Ppmd7.c"
    "src/dep/libs/lib7z/Ppmd7.h"
    "src/dep/libs/lib7z/Ppmd7Dec.c"
    "src/dep/libs/lib7z/Ppmd7Enc.c"
    "src/dep/libs/lib7z/Precomp.h"
    "src/dep/libs/lib7z/RotateDefs.h"
    "src/dep/libs/lib7z/Sha256.c"
    "src/dep/libs/lib7z/Sha256.h"
    "src/dep/libs/lib7z/Sort.c"
    "src/dep/libs/lib7z/Sort.h"
    "src/dep/libs/lib7z/Threads.c"
    "src/dep/libs/lib7z/Threads.h"
    "src/dep/libs/lib7z/Xz.c"
    "src/dep/libs/lib7z/Xz.h"
    "src/dep/libs/lib7z/XzCrc64.c"
    "src/dep/libs/lib7z/XzCrc64.h"
    "src/dep/libs/lib7z/XzCrc64Opt.c"
    "src/dep/libs/lib7z/XzDec.c"
    "src/dep/libs/lib7z/XzEnc.c"
    "src/dep/libs/lib7z/XzEnc.h"
    "src/dep/libs/lib7z/XzIn.c"
)
source_group("libs\\7z" FILES ${libs__7z})

set(libs__libpng
    "src/dep/libs/libpng/png.c"
    "src/dep/libs/libpng/png.h"
    "src/dep/libs/libpng/pngconf.h"
    "src/dep/libs/libpng/pngdebug.h"
    "src/dep/libs/libpng/pngerror.c"
    "src/dep/libs/libpng/pngget.c"
    "src/dep/libs/libpng/pnginfo.h"
    "src/dep/libs/libpng/pnglibconf.h"
    "src/dep/libs/libpng/pngmem.c"
    "src/dep/libs/libpng/pngpread.c"
    "src/dep/libs/libpng/pngpriv.h"
    "src/dep/libs/libpng/pngread.c"
    "src/dep/libs/libpng/pngrio.c"
    "src/dep/libs/libpng/pngrtran.c"
    "src/dep/libs/libpng/pngrutil.c"
    "src/dep/libs/libpng/pngset.c"
    "src/dep/libs/libpng/pngstruct.h"
    "src/dep/libs/libpng/pngtrans.c"
    "src/dep/libs/libpng/pngwio.c"
    "src/dep/libs/libpng/pngwrite.c"
    "src/dep/libs/libpng/pngwtran.c"
    "src/dep/libs/libpng/pngwutil.c"
)
source_group("libs\\libpng" FILES ${libs__libpng})

set(libs__lua
    "src/dep/libs/lua/lapi.c"
    "src/dep/libs/lua/lapi.h"
    "src/dep/libs/lua/lauxlib.c"
    "src/dep/libs/lua/lauxlib.h"
    "src/dep/libs/lua/lbaselib.c"
    "src/dep/libs/lua/lcode.c"
    "src/dep/libs/lua/lcode.h"
    "src/dep/libs/lua/ldblib.c"
    "src/dep/libs/lua/ldebug.c"
    "src/dep/libs/lua/ldebug.h"
    "src/dep/libs/lua/ldo.c"
    "src/dep/libs/lua/ldo.h"
    "src/dep/libs/lua/ldump.c"
    "src/dep/libs/lua/lfunc.c"
    "src/dep/libs/lua/lfunc.h"
    "src/dep/libs/lua/lgc.c"
    "src/dep/libs/lua/lgc.h"
    "src/dep/libs/lua/linit.c"
    "src/dep/libs/lua/liolib.c"
    "src/dep/libs/lua/llex.c"
    "src/dep/libs/lua/llex.h"
    "src/dep/libs/lua/llimits.h"
    "src/dep/libs/lua/lmathlib.c"
    "src/dep/libs/lua/lmem.c"
    "src/dep/libs/lua/lmem.h"
    "src/dep/libs/lua/loadlib.c"
    "src/dep/libs/lua/lobject.c"
    "src/dep/libs/lua/lobject.h"
    "src/dep/libs/lua/lopcodes.c"
    "src/dep/libs/lua/lopcodes.h"
    "src/dep/libs/lua/loslib.c"
    "src/dep/libs/lua/lparser.c"
    "src/dep/libs/lua/lparser.h"
    "src/dep/libs/lua/lstate.c"
    "src/dep/libs/lua/lstate.h"
    "src/dep/libs/lua/lstring.c"
    "src/dep/libs/lua/lstring.h"
    "src/dep/libs/lua/lstrlib.c"
    "src/dep/libs/lua/ltable.c"
    "src/dep/libs/lua/ltable.h"
    "src/dep/libs/lua/ltablib.c"
    "src/dep/libs/lua/ltm.c"
    "src/dep/libs/lua/ltm.h"
    "src/dep/libs/lua/lua.h"
    "src/dep/libs/lua/luaconf.h"
    "src/dep/libs/lua/lualib.h"
    "src/dep/libs/lua/lundump.c"
    "src/dep/libs/lua/lundump.h"
    "src/dep/libs/lua/lvm.c"
    "src/dep/libs/lua/lvm.h"
    "src/dep/libs/lua/lzio.c"
    "src/dep/libs/lua/lzio.h"
    "src/dep/libs/lua/print.c"
)
source_group("libs\\lua" FILES ${libs__lua})

set(libs__zlib
    "src/dep/libs/zlib/adler32.c"
    "src/dep/libs/zlib/compress.c"
    "src/dep/libs/zlib/crc32.c"
    "src/dep/libs/zlib/crc32.h"
    "src/dep/libs/zlib/deflate.c"
    "src/dep/libs/zlib/deflate.h"
    "src/dep/libs/zlib/gzclose.c"
    "src/dep/libs/zlib/gzguts.h"
    "src/dep/libs/zlib/gzlib.c"
    "src/dep/libs/zlib/gzread.c"
    "src/dep/libs/zlib/gzwrite.c"
    "src/dep/libs/zlib/infback.c"
    "src/dep/libs/zlib/inffast.c"
    "src/dep/libs/zlib/inffast.h"
    "src/dep/libs/zlib/inffixed.h"
    "src/dep/libs/zlib/inflate.c"
    "src/dep/libs/zlib/inflate.h"
    "src/dep/libs/zlib/inftrees.c"
    "src/dep/libs/zlib/inftrees.h"
    "src/dep/libs/zlib/trees.c"
    "src/dep/libs/zlib/trees.h"
    "src/dep/libs/zlib/uncompr.c"
    "src/dep/libs/zlib/zconf.h"
    "src/dep/libs/zlib/zconf.h.in"
    "src/dep/libs/zlib/zlib.h"
    "src/dep/libs/zlib/zutil.c"
    "src/dep/libs/zlib/zutil.h"
)
source_group("libs\\zlib" FILES ${libs__zlib})

set(ALL_FILES
    ${no_group_source_files}
    ${Burn}
    ${Burn__devices}
    ${Burn__drv__atari}
    ${Burn__drv__capcom}
    ${Burn__drv__cave}
    ${Burn__drv__coleco}
    ${Burn__drv__cps3}
    ${Burn__drv__dataeast}
    ${Burn__drv__galaxian}
    ${Burn__drv__irem}
    ${Burn__drv__konami}
    ${Burn__drv__megadrive}
    ${Burn__drv__midway}
    ${Burn__drv__msx}
    ${Burn__drv__neogeo}
    ${Burn__drv__nes}
    ${Burn__drv__pce}
    ${Burn__drv__pgm}
    ${Burn__drv__pre90s}
    ${Burn__drv__psikyo}
    ${Burn__drv__pst90s}
    ${Burn__drv__sega}
    ${Burn__drv__sg1000}
    ${Burn__drv__sms}
    ${Burn__drv__spectrum}
    ${Burn__drv__taito}
    ${Burn__drv__toaplan}
    ${Burn__snd}
    ${burner}
    ${burner__win32}
    ${cpus}
    ${cpus__adsp2100}
    ${cpus__arm}
    ${cpus__arm7}
    ${cpus__e132xs}
    ${cpus__h6280}
    ${cpus__hd6309}
    ${cpus__i8039}
    ${cpus__i8051}
    ${cpus__i8x41}
    ${cpus__konami}
    ${cpus__m6502}
    ${cpus__m6800}
    ${cpus__m6805}
    ${cpus__m6809}
    ${cpus__m68k}
    ${cpus__mips}
    ${cpus__nec}
    ${cpus__pic16c5x}
    ${cpus__s2650}
    ${cpus__sh2}
    ${cpus__tlcs90}
    ${cpus__tms32010}
    ${cpus__tms34}
    ${cpus__upd7725}
    ${cpus__upd7810}
    ${cpus__v60}
    ${cpus__z180}
    ${cpus__z80}
    ${generated}
    ${ggpo}
    ${mister}
    ${switchres}
    ${interfaces}
    ${interfaces__audio}
    ${interfaces__audio__win32}
    ${interfaces__cd}
    ${interfaces__cd__win32}
    ${interfaces__input}
    ${interfaces__input__win32}
    ${interfaces__perf}
    ${interfaces__perf__win32}
    ${interfaces__video}
    ${interfaces__video__scalers}
    ${interfaces__video__win32}
    ${interfaces__video__win32__resource}
    ${libs__7z}
    ${libs__libpng}
    ${libs__lua}
    ${libs__zlib}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE fbneo_vs2015)

################################################################################
# Target name
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG   "fcadefbneod64$ENV{TargetExt}"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG   "fcadefbneod$ENV{TargetExt}"
        TARGET_NAME_RELEASE "fcadefbneo$ENV{TargetExt}"
    )
endif()
################################################################################
# Output directory
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_CURRENT_SOURCE_DIR}/build"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}//build"
        OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}//build"
    )
endif()
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
endif()
################################################################################
# Include directories
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "$<$<CONFIG:Debug>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/generated;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/dep/libs/zlib;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/dep/libs/lib7z;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/dep/libs/libpng;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/dep/generated;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/dep/ggpo/include;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/dep/mister;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/dep/mister/lz4;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/dep/switchres;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/burner/win32/resource;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/burn/drv/taito;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/burn/drv/misc_post90s;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/burn/devices;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/audio/win32;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/audio;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/intf;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/video/scalers;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/video/win32;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/video;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/perfcount/win32;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/perfcount;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/input/win32;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/input;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/cd/win32;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/cd;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/intf;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/burner/win32;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/burn/snd;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/burner;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/burn;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/z80;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/sh2;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/s2650;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/nec;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/m6809;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/m6805;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/m6800;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/m6502;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/m68k;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/i8039;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/konami;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/hd6309;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/h6280;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/arm7;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/arm;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/g65816;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/spc700;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/i8051;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/tms32010;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/tms34010;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/i8x41;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/burn/drv/sega;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/burn/drv/dataeast;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/burn/drv/konami;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/z180;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/burn/drv/irem;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/upd7810;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/v60;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/upd7725"
        ">"
        "$<$<CONFIG:Release>:"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/burn/drivers/taito;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/burn/drivers/misc_post90s;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/burn/devices;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/depend/generated;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/interface/scalers;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/interface/win32/resource;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/interface/win32;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/interface;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/burner/win32/resource;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/burner/win32;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/depend/libs/zlib;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/depend/libs/libpng;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/depend/libs;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/depend/kaillera/client;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/depend/kaillera;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/burn/sound;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/burner;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/burn;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/z80;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/sh2;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/s2650;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/nec;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/m6809;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/m6805;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/m6800;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/m6502;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/m68k;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/i8039;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/konami;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/hd6309;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/h6280;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/arm7;"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/arm"
        ">"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/generated;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/dep/libs/zlib;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/dep/libs/lib7z;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/dep/libs/libpng;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/dep/libs/lua;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/dep/generated;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/dep/ggpo/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/dep/mister;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/dep/mister/lz4;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/dep/switchres;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/burner/win32/resource;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/burn/drv/taito;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/burn/drv/misc_post90s;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/burn/devices;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/audio/win32;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/audio;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/intf;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/video/scalers;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/video/win32;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/video;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/perfcount/win32;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/perfcount;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/input/win32;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/input;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/cd/win32;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/intf/cd;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/burner/win32;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/burn/snd;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/burner;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/burn;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/z80;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/sh2;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/s2650;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/nec;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/m6809;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/m6805;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/m6800;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/m6502;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/m68k;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/i8039;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/konami;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/hd6309;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/h6280;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/arm7;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/arm;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/g65816;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/spc700;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/i8051;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/tms32010;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/tms34;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/i8x41;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/burn/drv/sega;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/burn/drv/dataeast;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/burn/drv/konami;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/z180;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/burn/drv/irem;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/upd7810;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/v60;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cpu/upd7725"
        
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include"
    )
endif()

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG;"
            "FBNEO_DEBUG;"
            "LSB_FIRST;"
            "INLINE=__inline static;"
            "INCLUDE_LIB_PNGH;"
            "C_INLINE=__inline;"
            "MAME_INLINE=__inline static;"
            "_CRT_SECURE_NO_WARNINGS;"
            "WINAPI_FAMILY=WINAPI_FAMILY_DESKTOP_APP;"
            "UNICODE;"
            "_UNICODE"
        ">"
        "$<$<CONFIG:Release>:"
            "_MBCS;"
            "_MBCS"
        ">"
        "BUILD_WIN32;"
        "FASTCALL"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG;"
            "_DEBUG;"
            "FBNEO_DEBUG"
        ">"
        "BUILD_WIN32;"
        "FASTCALL;"
        "LSB_FIRST;"
        "INLINE=__inline static;"
        "INCLUDE_LIB_PNGH;"
        "INCLUDE_AVI_RECORDING;"
        "C_INLINE=__inline;"
        "MAME_INLINE=__inline static;"
        "_CRT_SECURE_NO_WARNINGS;"
        "WINAPI_FAMILY=WINAPI_FAMILY_DESKTOP_APP;"
        "UNICODE;"
        "_UNICODE"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od;
                /Oy-;
                /TP
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy
            >
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od
            >
            $<$<CONFIG:Release>:
                /O2;
                /Ob2;
                /Oi;
                /Gy
            >
            /W3;
            /Zi;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /DEBUG
            >
            $<$<CONFIG:Release>:
                /MANIFEST;
                /DEBUG:FASTLINK;
                /OPT:REF;
                /OPT:ICF
            >
            /NODEFAULTLIB:winspool.lib;
            /NODEFAULTLIB:oleaut32.lib;
            /NODEFAULTLIB:uuid.lib;
            /NODEFAULTLIB:odbc32.lib;
            /NODEFAULTLIB:odbccp32.lib;
            /SUBSYSTEM:WINDOWS
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "user32;"
        "gdi32;"
        "comdlg32;"
        "comctl32;"
        "shell32;"
        "winmm;"
        "ole32;"
        "shlwapi;"
        "advapi32;"
        "setupapi;"
        "d3d9;"
        "d3dx9;"
        "dsound;"
        "dinput8"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "user32;"
        "gdi32;"
        "comdlg32;"
        "comctl32;"
        "shell32;"
        "winmm;"
        "advapi32;"
        "setupapi;"
        "vfw32;"
        "wininet;"
        "ggponet;"
        "ws2_32"
    )
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x64"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
    target_link_directories(${PROJECT_NAME} PRIVATE
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86;"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/dep/ggpo/lib"
    )
endif()


# --------------------------------------------------------- #
# PDCurses                                                  #
# --------------------------------------------------------- #
set(PDCURSES_DIR lib/PDCurses)
set(PDCURSES_LIB pdcurses)
set(PDCURSES_INCLUDE_DIR ${PDCURSES_DIR})

set(PDCURSES_SRCS
    ${PDCURSES_DIR}/pdcurses/addch.c
    ${PDCURSES_DIR}/pdcurses/addchstr.c
    ${PDCURSES_DIR}/pdcurses/addstr.c
    ${PDCURSES_DIR}/pdcurses/attr.c
    ${PDCURSES_DIR}/pdcurses/beep.c
    ${PDCURSES_DIR}/pdcurses/bkgd.c
    ${PDCURSES_DIR}/pdcurses/border.c
    ${PDCURSES_DIR}/pdcurses/clear.c
    ${PDCURSES_DIR}/pdcurses/color.c
    ${PDCURSES_DIR}/pdcurses/debug.c
    ${PDCURSES_DIR}/pdcurses/delch.c
    ${PDCURSES_DIR}/pdcurses/deleteln.c
    ${PDCURSES_DIR}/pdcurses/getch.c
    ${PDCURSES_DIR}/pdcurses/getstr.c
    ${PDCURSES_DIR}/pdcurses/getyx.c
    ${PDCURSES_DIR}/pdcurses/inch.c
    ${PDCURSES_DIR}/pdcurses/inchstr.c
    ${PDCURSES_DIR}/pdcurses/initscr.c
    ${PDCURSES_DIR}/pdcurses/inopts.c
    ${PDCURSES_DIR}/pdcurses/insch.c
    ${PDCURSES_DIR}/pdcurses/insstr.c
    ${PDCURSES_DIR}/pdcurses/instr.c
    ${PDCURSES_DIR}/pdcurses/kernel.c
    ${PDCURSES_DIR}/pdcurses/keyname.c
    ${PDCURSES_DIR}/pdcurses/mouse.c
    ${PDCURSES_DIR}/pdcurses/move.c
    ${PDCURSES_DIR}/pdcurses/outopts.c
    ${PDCURSES_DIR}/pdcurses/overlay.c
    ${PDCURSES_DIR}/pdcurses/pad.c
    ${PDCURSES_DIR}/pdcurses/panel.c
    ${PDCURSES_DIR}/pdcurses/printw.c
    ${PDCURSES_DIR}/pdcurses/refresh.c
    ${PDCURSES_DIR}/pdcurses/scanw.c
    ${PDCURSES_DIR}/pdcurses/scr_dump.c
    ${PDCURSES_DIR}/pdcurses/scroll.c
    ${PDCURSES_DIR}/pdcurses/slk.c
    ${PDCURSES_DIR}/pdcurses/termattr.c
    ${PDCURSES_DIR}/pdcurses/touch.c
    ${PDCURSES_DIR}/pdcurses/util.c
    ${PDCURSES_DIR}/pdcurses/window.c
)

if(MSVC)
    list(APPEND PDCURSES_SRCS
        ${PDCURSES_DIR}/wincon/pdcclip.c
        ${PDCURSES_DIR}/wincon/pdcdisp.c
        ${PDCURSES_DIR}/wincon/pdcgetsc.c
        ${PDCURSES_DIR}/wincon/pdckbd.c
        ${PDCURSES_DIR}/wincon/pdcscrn.c
        ${PDCURSES_DIR}/wincon/pdcsetsc.c
        ${PDCURSES_DIR}/wincon/pdcutil.c
    )
endif()

add_library(${PDCURSES_LIB} ${PDCURSES_SRCS})
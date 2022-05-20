if(APPLE)
  configure_file(package/osx/Info.plist.in package/osx/Info.plist)
  configure_file(package/osx.sh.in package/osx.sh)

add_custom_command(
    OUTPUT Falltergeist.dmg
    COMMAND sh ./package/osx.sh
  )
  add_custom_target(dmg DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Falltergeist.dmg)
endif()

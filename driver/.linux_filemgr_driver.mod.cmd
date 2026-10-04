savedcmd_linux_filemgr_driver.mod := printf '%s\n'   linux_filemgr_driver.o | awk '!x[$$0]++ { print("./"$$0) }' > linux_filemgr_driver.mod

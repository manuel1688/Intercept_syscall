.. code-block:: console
    cmake syscall_intercept -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang
    make
    sudo make install

    cc xpn_syscall_intercept.c -lsyscall_intercept -fpic -shared -o xpn_syscall_intercept.so

    INTERCEPT_LOG=logs/intercept.log- LD_LIBRARY_PATH=. LD_PRELOAD=xpn_syscall_intercept.so ./prueba_write

    

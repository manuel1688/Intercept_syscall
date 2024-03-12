.. code-block:: console
    
    git clone https://github.com/pmem/syscall_intercept.git

    sudo apt install clang

    sudo apt-get install pkg-config libcapstone-dev
    
    cmake syscall_intercept -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang
    make
    sudo make install


    ## Compilar el programa de prueba
    mkdir logs
    cc xpn_syscall_intercept.c -lsyscall_intercept -fpic -shared -o xpn_syscall_intercept.so

    ## compilar un interceptor para creat
    cc xpn_syscall_intercept_create.c -lsyscall_intercept -fpic -shared -o xpn_syscall_intercept_create.so

    INTERCEPT_LOG=logs/intercept.log- LD_LIBRARY_PATH=. LD_PRELOAD=xpn_syscall_intercept_create.so ./prueba_write
    

    ## comando para probar ByPass
    LD_PRELOAD=../../../src/bypass/xpn_bypass.so:$LD_PRELOAD  XPN_CONF=./xpn.conf  ./open-write-close /tmp/expand/P1/demo.txt  8

    ## comando para probar intercept xpn lib
    LD_PRELOAD=xpn_syscall_intercept.so:$LD_PRELOAD  XPN_CONF=./xpn.conf  ./prueba_creat /tmp/expand/P1/demo.txt  8

    ## comando para probar intercept xpn lib creat
    LD_PRELOAD=xpn_syscall_intercept_create.so:$LD_PRELOAD XPN_CONF=./xpn.conf ./prueba_create /tmp/expand/P1/demo.txt 8

    LD_PRELOAD=xpn_syscall_intercept_create.so XPN_CONF=./xpn.conf ./prueba_creat /tmp/expand/P1/demo.txt 8
    

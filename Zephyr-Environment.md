## Assignment - Zephyr Environment \& Hello World




<div style="text-align: justify">
  
The main goal of this document is to explain what is done during this practical Lab with the [QEMU Emulation for RISCV32E](https://docs.zephyrproject.org/latest/boards/qemu/riscv32e/doc/index.html). My environment is Windows 11 host, hence, I couldn't use the [Native simulator - native\_sim](https://docs.zephyrproject.org/latest/boards/native/native\_sim/doc/index.html) because Windows isn't POSIX architecture based board.

</div>

<br>


````cmd

(.venv) C:\\Users\\WinIAM\\zephyrproject\\zephyr>west build -p always -b qemu\_xtensa/dc233c samples/synchronization

\-- west build: making build dir C:\\Users\\WinIAM\\zephyrproject\\zephyr\\build pristine

\-- west build: generating a build system

Loading Zephyr default modules (Zephyr base).

\-- Application: C:/Users/WinIAM/zephyrproject/zephyr/samples/synchronization

\-- CMake version: 4.4.3

\-- Found Python3: C:/Users/WinIAM/zephyrproject/.venv/Scripts/python.exe (found suitable version "3.12.10", minimum required is "3.12") found components: Interpreter

\-- Cache files will be written to: C:/Users/WinIAM/zephyrproject/zephyr/.cache

\-- Zephyr version: 4.4.99 (C:/Users/WinIAM/zephyrproject/zephyr)

\-- Found west (found suitable version "1.5.0", minimum required is "0.14.0")

\-- Board: qemu\_xtensa, qualifiers: dc233c

\-- ZEPHYR\_TOOLCHAIN\_VARIANT not set, trying to locate Zephyr SDK

\-- Found host-tools: zephyr 1.0.1 (C:/Users/WinIAM/zephyr-sdk-1.0.1)

\-- Found toolchain: zephyr 1.0.1 (C:/Users/WinIAM/zephyr-sdk-1.0.1)

\-- Found Dtc: C:/msys64/mingw64/bin/dtc.exe (found suitable version "1.7.2", minimum required is "1.4.6")

\-- Found BOARD.dts: C:/Users/WinIAM/zephyrproject/zephyr/boards/qemu/xtensa/qemu\_xtensa\_dc233c.dts

\-- Generated zephyr.dts: C:/Users/WinIAM/zephyrproject/zephyr/build/zephyr/zephyr.dts

\-- Generated pickled edt: C:/Users/WinIAM/zephyrproject/zephyr/build/zephyr/edt.pickle

\-- Generated devicetree\_generated.h: C:/Users/WinIAM/zephyrproject/zephyr/build/zephyr/include/generated/zephyr/devicetree\_generated.h

Parsing C:/Users/WinIAM/zephyrproject/zephyr/Kconfig

Loaded configuration 'C:/Users/WinIAM/zephyrproject/zephyr/boards/qemu/xtensa/qemu\_xtensa\_dc233c\_defconfig'

Merged configuration 'C:/Users/WinIAM/zephyrproject/zephyr/samples/synchronization/prj.conf'

Configuration saved to 'C:/Users/WinIAM/zephyrproject/zephyr/build/zephyr/.config'

Kconfig header saved to 'C:/Users/WinIAM/zephyrproject/zephyr/build/zephyr/include/generated/zephyr/autoconf.h'

\-- Could NOT find Ccache (missing: CCACHE) (Required is at least version "4.12")

Hint: The project() command has not yet been called.  It sets up system-specific search paths.

\-- Found GnuLd: C:/Users/WinIAM/zephyr-sdk-1.0.1/gnu/xtensa-dc233c\_zephyr-elf/xtensa-dc233c\_zephyr-elf/bin/ld.bfd.exe (found version "2.43.1")

\-- The C compiler identification is GNU 14.3.0

\-- The CXX compiler identification is GNU 14.3.0

\-- The ASM compiler identification is GNU

\-- Found assembler: C:/Users/WinIAM/zephyr-sdk-1.0.1/gnu/xtensa-dc233c\_zephyr-elf/bin/xtensa-dc233c\_zephyr-elf-gcc.exe

\-- Found gen\_kobject\_list: C:/Users/WinIAM/zephyrproject/zephyr/scripts/build/gen\_kobject\_list.py

\-- Configuring done (100.6s)

\-- Generating done (0.9s)

\-- Build files have been written to: C:/Users/WinIAM/zephyrproject/zephyr/build

\-- west build: building application

\[4/145] Generating include/generated/zephyr/version.h

\-- Zephyr version: 4.4.99 (C:/Users/WinIAM/zephyrproject/zephyr), build: v4.4.0-14135-gb904e0ca7d57

\[145/145] Linking C executable zephyr\\zephyr.elf

Memory region         Used Size  Region Size  %age Used

&#x20;        vectors:         970 B         9 KB     10.53%

&#x20;            RAM:       21232 B     16375 KB      0.13%

&#x20;       rom0\_seg:         296 B        16 KB      1.81%

&#x20;       IDT\_LIST:           0 B         8 KB      0.00%

Generating files from C:/Users/WinIAM/zephyrproject/zephyr/build/zephyr/zephyr.elf for board: qemu\_xtensa/dc233c



(.venv) C:\\Users\\WinIAM\\zephyrproject\\zephyr>west build -t run

\-- west build: running target run

\[0/1] To exit from QEMU enter: 'CTRL+a, x'\[QEMU] CPU: dc233c\*\*\* Booting Zephyr OS build v4.4.0-14135-gb904e0ca7d57 \*\*\*

thread\_a: Hello World from cpu 0 on qemu\_xtensa!

thread\_b: Hello World from cpu 0 on qemu\_xtensa!

thread\_a: Hello World from cpu 0 on qemu\_xtensa!

thread\_b: Hello World from cpu 0 on qemu\_xtensa!

thread\_a: Hello World from cpu 0 on qemu\_xtensa!

thread\_b: Hello World from cpu 0 on qemu\_xtensa!

thread\_a: Hello World from cpu 0 on qemu\_xtensa!

thread\_b: Hello World from cpu 0 on qemu\_xtensa!

thread\_a: Hello World from cpu 0 on qemu\_xtensa!

thread\_b: Hello World from cpu 0 on qemu\_xtensa!

thread\_a: Hello World from cpu 0 on qemu\_xtensa!

thread\_b: Hello World from cpu 0 on qemu\_xtensa!

thread\_a: Hello World from cpu 0 on qemu\_xtensa!

thread\_b: Hello World from cpu 0 on qemu\_xtensa!

^C

(.venv) C:\\Users\\WinIAM\\zephyrproject\\zephyr>west build -p always -b qemu\_xtensa/dc233c samples/hello\_world

\-- west build: making build dir C:\\Users\\WinIAM\\zephyrproject\\zephyr\\build pristine

\-- west build: generating a build system

Loading Zephyr default modules (Zephyr base).

\-- Application: C:/Users/WinIAM/zephyrproject/zephyr/samples/hello\_world

\-- CMake version: 4.4.3

\-- Found Python3: C:/Users/WinIAM/zephyrproject/.venv/Scripts/python.exe (found suitable version "3.12.10", minimum required is "3.12") found components: Interpreter

\-- Cache files will be written to: C:/Users/WinIAM/zephyrproject/zephyr/.cache

\-- Zephyr version: 4.4.99 (C:/Users/WinIAM/zephyrproject/zephyr)

\-- Found west (found suitable version "1.5.0", minimum required is "0.14.0")

\-- Board: qemu\_xtensa, qualifiers: dc233c

\-- ZEPHYR\_TOOLCHAIN\_VARIANT not set, trying to locate Zephyr SDK

\-- Found host-tools: zephyr 1.0.1 (C:/Users/WinIAM/zephyr-sdk-1.0.1)

\-- Found toolchain: zephyr 1.0.1 (C:/Users/WinIAM/zephyr-sdk-1.0.1)

\-- Found Dtc: C:/msys64/mingw64/bin/dtc.exe (found suitable version "1.7.2", minimum required is "1.4.6")

\-- Found BOARD.dts: C:/Users/WinIAM/zephyrproject/zephyr/boards/qemu/xtensa/qemu\_xtensa\_dc233c.dts

\-- Generated zephyr.dts: C:/Users/WinIAM/zephyrproject/zephyr/build/zephyr/zephyr.dts

\-- Generated pickled edt: C:/Users/WinIAM/zephyrproject/zephyr/build/zephyr/edt.pickle

\-- Generated devicetree\_generated.h: C:/Users/WinIAM/zephyrproject/zephyr/build/zephyr/include/generated/zephyr/devicetree\_generated.h

Parsing C:/Users/WinIAM/zephyrproject/zephyr/Kconfig

Loaded configuration 'C:/Users/WinIAM/zephyrproject/zephyr/boards/qemu/xtensa/qemu\_xtensa\_dc233c\_defconfig'

Merged configuration 'C:/Users/WinIAM/zephyrproject/zephyr/samples/hello\_world/prj.conf'

Configuration saved to 'C:/Users/WinIAM/zephyrproject/zephyr/build/zephyr/.config'

Kconfig header saved to 'C:/Users/WinIAM/zephyrproject/zephyr/build/zephyr/include/generated/zephyr/autoconf.h'

\-- Could NOT find Ccache (missing: CCACHE) (Required is at least version "4.12")

Hint: The project() command has not yet been called.  It sets up system-specific search paths.

\-- Found GnuLd: C:/Users/WinIAM/zephyr-sdk-1.0.1/gnu/xtensa-dc233c\_zephyr-elf/xtensa-dc233c\_zephyr-elf/bin/ld.bfd.exe (found version "2.43.1")

\-- The C compiler identification is GNU 14.3.0

\-- The CXX compiler identification is GNU 14.3.0

\-- The ASM compiler identification is GNU

\-- Found assembler: C:/Users/WinIAM/zephyr-sdk-1.0.1/gnu/xtensa-dc233c\_zephyr-elf/bin/xtensa-dc233c\_zephyr-elf-gcc.exe

\-- Found gen\_kobject\_list: C:/Users/WinIAM/zephyrproject/zephyr/scripts/build/gen\_kobject\_list.py

\-- Configuring done (17.2s)

\-- Generating done (0.9s)

\-- Build files have been written to: C:/Users/WinIAM/zephyrproject/zephyr/build

\-- west build: building application

\[4/145] Generating include/generated/zephyr/version.h

\-- Zephyr version: 4.4.99 (C:/Users/WinIAM/zephyrproject/zephyr), build: v4.4.0-14135-gb904e0ca7d57

\[145/145] Linking C executable zephyr\\zephyr.elf

Memory region         Used Size  Region Size  %age Used

&#x20;        vectors:         970 B         9 KB     10.53%

&#x20;            RAM:       17200 B     16375 KB      0.10%

&#x20;       rom0\_seg:         296 B        16 KB      1.81%

&#x20;       IDT\_LIST:           0 B         8 KB      0.00%

Generating files from C:/Users/WinIAM/zephyrproject/zephyr/build/zephyr/zephyr.elf for board: qemu\_xtensa/dc233c



(.venv) C:\\Users\\WinIAM\\zephyrproject\\zephyr>west build -t run

\-- west build: running target run

\[0/1] To exit from QEMU enter: 'CTRL+a, x'\[QEMU] CPU: dc233c\*\*\* Booting Zephyr OS build v4.4.0-14135-gb904e0ca7d57 \*\*\*

Hello World! qemu\_xtensa/dc233c

^C

(.venv) C:\\Users\\WinIAM\\zephyrproject\\zephyr>west build -t run

````




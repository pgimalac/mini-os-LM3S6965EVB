# mini-os LM3S6965EVB
## Informations
This project was realised as a two week long end of the (first) year project at Telecom Paris.

It was supervised by Guillaume Duc.

## Project
The objective of the project was to write a minimalistic OS on a Luminary Micro Stellaris LM3S6965EVB equipped with a ARM Cortex-M3 processor.

There wasn't a list of things to do and it was the first year such a project was attempted so it was a little bit improvised over the two weeks.

## Dependencies
The project uses Qemu (as it occurred during a lock-down and the chip wasn't available for testing) to launch.

At first the official QEMU System ARM version was used, but to implement a small file system some RAM was added between the addresses `0xF0000000` and `0xF0A00000`. To do so you must modify the file [`hw/arm/stellaris.c`](https://github.com/qemu/qemu/blob/master/hw/arm/stellaris.c) in the [QEMU repository](https://github.com/qemu/qemu), then compile and install.

The GCC arm-none-eabi tool chain was used to compile and debug the project.

## Final state
By the end of the project the processus handling and sequencing were working fine.

System calls work rather fine but no intensive test was made. `fork` doesn't work.

The file system was almost not tested and thus may be filled with bugs but it seemed to work fine in the few tests realised.

Processes are constantly with high priviledges.

Nothing was optimised, as speed was not the objective of the project.

## Significant issue
A small part of memory seemed to take longer to access, causing one process (the one that had its RAM in this region) to be slower. No explanation was found.

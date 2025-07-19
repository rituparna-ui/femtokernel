.section ".text.boot"
.global _start

_start:
  ldr x0, =_stack_top
  mov sp, x0
  b kernel_main
# bl kernel_main
# b panic

.section ".bss"
  .space 4096
_stack_top:

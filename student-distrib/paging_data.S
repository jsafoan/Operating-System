/*cr3:


  .align 0x8000
paging_direct:
  .rept 1024
  .long 0
  .endr

  .align 0x8000
page_table:
  .rept 1024
  .align 0x8000
  .rept 1024
  .long 0
  .endr
  .endr
*/

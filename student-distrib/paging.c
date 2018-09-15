
#include "paging.h"
//
// direct_desc_t paging_direct[1024] __attribute__((aligned (4096)));
// table_desc_t page_tables[1024] __attribute__((aligned (4096)));

//static uint32_t paging_direct[SIZE_OF_PAGE] __attribute__((aligned (SIZE_OF_PAGE_ALIGN)));
//static uint32_t page_tables[SIZE_OF_PAGE] __attribute__((aligned (SIZE_OF_PAGE_ALIGN)));

/*
 * paging_init
 *   DESCRIPTION: initializes paging
 *
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 *
 */
void paging_init()
  { 
    int i, j;
    //void* cast;
    //int bytes = 4;
    for (j = 0; j < SIZE_OF_PAGE; j++)
      {
        switch (j)
        {
          case 0:   // this set up the first entry of paging directory which maps to a paging table
          {

            paging_direct[j].offset_20_0 = ((uint32_t)page_tables)>>SHIFT_TWELVE;
            paging_direct[j].avail = 0;
            paging_direct[j].G = 0;  //this bit is ignored
            paging_direct[j].D = 0;
            paging_direct[j].W = 0;
            paging_direct[j].U = 0;
            paging_direct[j].S = 0;
            paging_direct[j].R = 1;
            paging_direct[j].P = 1;
            paging_direct[j].O = 0;
            paging_direct[j].A = 0;

			for (i = 0; i < SIZE_OF_PAGE; i++) { // this set up the paging table entries
              page_tables[i].offset_20_0 = i;
              page_tables[i].avail = 0;
              page_tables[i].G = 0;
              page_tables[i].O = 0;
              page_tables[i].D = 0;
              page_tables[i].A = 0;
              page_tables[i].C = 0;
              page_tables[i].W = 0;
              page_tables[i].U = 0;
              page_tables[i].R = 1;
              page_tables[i].P = 0;
            }
			
		    //B8000 , last 12 unused // set the specific address for video memory
            page_tables[VIDEO].offset_20_0 = VIDEO;
            page_tables[VIDEO].P = 1;
            page_tables[VIDEO].R = 1;
            page_tables[VIDEO].U = 0;
		        break;
				
          }
          case 1:   // this is a 4 mb paging directory for kernel
          {
            //offset 10 doest fit 12 bits
            paging_direct[j].offset10_0 = KERNEL_ADDRESS;
            paging_direct[j].reserved = 0;
            paging_direct[j].PAT = 0;  //this bit is ignored
            paging_direct[j].avail_M = 0;
            paging_direct[j].G_M = 0;
            paging_direct[j].PS = 1;
            paging_direct[j].D_M = 0;
            paging_direct[j].A_M = 0;
            paging_direct[j].PCD = 0;
            paging_direct[j].PWT = 0;
            paging_direct[j].U_S = 0;
            paging_direct[j].R_W = 1;
            paging_direct[j].P_M = 1;

            break;

          }
          default: // this is default construct for paging directory
          {
            //cast = &page_tables + 0x1024 * bytes * j;
            paging_direct[j].offset_20_0 = 0;
            paging_direct[j].G = 0;  //this bit is ignored
            paging_direct[j].D = 0;
            paging_direct[j].W = 0;
            paging_direct[j].U = 0;
            paging_direct[j].S = 0;
            paging_direct[j].R = 1;
            paging_direct[j].P = 0;
            paging_direct[j].O = 0;
            paging_direct[j].A = 0;
            //temp = page_table + 0x1024 * bytes * j;
            //paging_direct = temp << 12;
          }
        }
      }
	  
	  
	  	  
	  
      // call the two enable paging functions written in Assembly
      loadPageDirectory((void*) paging_direct);
      enablePaging();

	  //Test for bad page pointers 

	  //Greater than 8MB
	  /*int c; int* a;
	  a =(int*)0xB8002;//0x400000;
	  c = *a;*/
	  

	  //table_desc_t* page_test = (page_tables[2].offset_20_0);
	  //table_desc_t page_test2 = *page_test;
	  return;

}

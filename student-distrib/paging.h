#ifndef _PAGING_H
#define _PAGING_H

#include "types.h"
#define VIDEO       0xB8
#define SIZE_OF_PAGE 1024
#define SIZE_OF_PAGE_ALIGN 4096
#define KERNEL_ADDRESS 0x1
#define SHIFT_TWELVE  12
/* We constructs two seperate structs here
 * One is direct struct and another is table struct
 *
 */

typedef union direct_desc_t {
    uint32_t val;
    struct {                       // this is 4 kb mapping
        uint32_t P            : 1; // Present
        uint32_t R            : 1; // Read/Write
        uint32_t U            : 1; // User/Supervisor
        uint32_t W            : 1; // Write Through
        uint32_t D            : 1; // Cache disabled
        uint32_t A            : 1; // Accessed
        uint32_t O            : 1; // Reserved (set to 0)
        uint32_t S            : 1; // Page size (0 indicates 4 KBytes)
        uint32_t G            : 1; // Global page (Ignored)
        uint8_t  avail        : 3; // Available for system programmer’s use
        uint32_t offset_20_0  : 20;// Page-Table Base Address
    } __attribute__ ((packed));
    struct {                        //  this is 4 mb mapping
      uint8_t P_M             :  1; //  Present
      uint8_t R_W             :  1; //  Read/Write
      uint8_t U_S             :  1; //  User/Supervisor
      uint8_t PWT             :  1; //  Write Through
      uint8_t PCD             :  1; //  Cache disabled
      uint8_t A_M             :  1; //  Accessed
      uint8_t D_M             :  1; //  Dirty
      uint8_t PS              :  1; //  Page size (1 indicates 4 MBytes)
      uint8_t G_M             :  1; //  Global Page
      uint8_t avail_M         :  3; //  Available for system programmer’s use
      uint8_t PAT             :  1; //  Page Table Attribute Index
      uint32_t reserved       :  9; //  Reserved
      uint32_t offset10_0     : 10; //  Page Base Address
    } __attribute__ ((packed));

} direct_desc_t;

typedef union table_desc_t {
    uint32_t val;
    struct {
        uint32_t P            : 1; // this is 4 mb mapping
        uint32_t R            : 1; // Present
        uint32_t U            : 1; // Read/Write
        uint32_t W            : 1; // User/Supervisor
        uint32_t C            : 1; // Write Through
        uint32_t A            : 1; // Cache disabled
        uint32_t D            : 1; // Accessed
        uint32_t O            : 1; // Dirty
        uint32_t G            : 1; // Page Table Attribute Index
        uint8_t  avail        : 3; // Global Page
        uint32_t offset_20_0  : 20; // Available for system programmer’s use
    } __attribute__ ((packed));
} table_desc_t;

// construct a paging directory of size 1024
direct_desc_t paging_direct[SIZE_OF_PAGE] __attribute__((aligned (SIZE_OF_PAGE_ALIGN)));

// construct a paging table of size 1024 for the entry 0 of paging directory
table_desc_t page_tables[SIZE_OF_PAGE] __attribute__((aligned (SIZE_OF_PAGE_ALIGN)));

/* initializes paging */
void paging_init();

/* paging enable functions */
extern void enablePaging();
extern void loadPageDirectory(unsigned int*);


#endif

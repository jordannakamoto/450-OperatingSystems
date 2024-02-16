# Virtual Memory Paging and Address Translation

This project implements address translation between logical and physical addresses for a simple paged virtual memory system.

## Key Concepts

- **Page**: A fixed-length contiguous block of virtual memory.
- **Frame**: A fixed-length contiguous block of physical memory.
- **Page Size (P)**: The size of a page or frame, typically a power of 2 (e.g., 4KB).
- **Virtual Address Space (N)**: The maximum size of virtual memory, which is \(2^n\).
- **Physical Memory Size (M)**: The maximum size of physical memory, which is \(2^m\).
- **Page Offset**: The part of the address that determines the byte offset within a page.

## Address Translation

To translate between virtual and physical addresses, a page table is used. The page table contains the base physical address of each virtual page.

### Calculations

#### Logical to Physical

To find the physical address from a logical address:

1. Divide the logical address by the page size to get the page number.
2. Look up the page number in the page table to find the corresponding frame number.
3. Multiply the frame number by the page size.
4. Add the page offset (remainder from step 1) to get the physical address.

   **Physical Address = (Frame Number x Page Size) + Page Offset**

#### Physical to Logical

To find the logical address from a physical address:

1. Divide the physical address by the page size to get the frame number.
2. Find which page number maps to this frame in the page table.
3. Multiply the page number by the page size.
4. Add the offset within the frame to get the logical address.

   **Logical Address = (Page Number x Page Size) + Offset within Frame**

### Example Calculations

- If the logical address is 3567 and the page size is 4KB (4096 bytes):
  
  - Page number is 3567 / 4096 = 0
  - Page 0 maps to frame 2
  - Physical address is (2 x 4096) + 3567 = 11759

- If the physical address is 17900 and the page size is 4KB:
  
  - Frame number is 17900 / 4096 = 4
  - Frame 4 maps to page 2
  - Logical address is (2 x 4096) + 1516 = 9708

--- 
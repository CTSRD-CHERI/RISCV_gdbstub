// Copyright (c) 2020 Bluespec, Inc. All Rights Reserved
// Author: Rishiyur Nikhil
//
// ================================================================

#pragma once

// ================================================================
// All functions return the following status

#define   status_err      0
#define   status_ok       1

// ================================================================
// Public globals

// ================================================================
// Word bitwidth (32 for RV32, 64 for RV64)
// (Important: affects format of data strings in RSP communication with GDB)
// This defaults to 64 (for RV64), but can be set to 32.
// If gdbstub_be_elf_load() is invoked, it'll be picked up from the ELF file.

extern
int gdbstub_be_xlen;

// ================================================================
// Help
// Return a help string for GDB to print out,
// listing which 'monitor' commands are available

extern
const char *gdbstub_be_help (void);

// ================================================================
// Initialize gdbstub_be

extern
uint32_t  gdbstub_be_init (FILE *logfile);

// ================================================================
// Final actions for gdbstub_be

extern
uint32_t  gdbstub_be_final (const int xlen);

// ================================================================
// Reset the Debug Module

extern
uint32_t  gdbstub_be_dm_reset (const int xlen);

// ================================================================
// Reset the NDM (non-debug module, i.e., everything but the debug module)
// The argument indicates whether the hart is running/halted after reset

extern
uint32_t  gdbstub_be_ndm_reset (const int xlen, bool haltreq);

// ================================================================
// Reset the HART 
// The argument indicates whether the hart is running/halted after reset

extern
uint32_t  gdbstub_be_hart_reset (const int xlen, bool haltreq);

// ================================================================
// Set verbosity to n in RISC-V system

extern
uint32_t gdbstub_be_verbosity (int n);

// ================================================================
// Load ELF file into RISC-V memory

extern
uint32_t gdbstub_be_elf_load (const char *elf_filename);

// ================================================================
// Continue the HW execution at given PC

extern
uint32_t gdbstub_be_continue (const int xlen);

// ================================================================
// Step the HW execution at given PC

extern
uint32_t  gdbstub_be_step (const int xlen);

// ================================================================
// Stop the HW execution

extern
uint32_t  gdbstub_be_stop (const int xlen);

// ================================================================
// Get stop-reason from HW
// (HW normally stops due to GDB ^C, after a 'step', or at a breakpoint)

extern
uint32_t  gdbstub_be_get_stop_reason (const int xlen, uint8_t *p_stop_reason);

// ================================================================
// This is not a debugger function at all, just an aid for humans
// perusing the logfile.  A GDB command can result in several DMI
// commands. This function writes a separation marker into the log
// file, so that it is easy to group sets of DMIs command and
// responses corresponding to a single GDB command.

extern
uint32_t  gdbstub_be_start_command (const int xlen);

// ================================================================
// Read a value from the PC

extern
uint32_t  gdbstub_be_PC_read (const int xlen, uint64_t *p_PC);

// ================================================================
// Read a value from a GPR register in SoC

extern
uint32_t  gdbstub_be_GPR_read (const int xlen, uint32_t regnum, uint64_t *p_regval);

// ================================================================
// Read a value from a FPR register in SoC

extern
uint32_t  gdbstub_be_FPR_read (const int xlen, uint32_t regnum, uint64_t *p_regval);

// ================================================================
// Read a value from a CSR in SoC

extern
uint32_t  gdbstub_be_CSR_read (const int xlen, uint32_t regnum, uint64_t *p_regval);

// ================================================================
// Read 1, 2 or 4 bytes from SoC memory at address 'addr' into 'data'

extern
uint32_t  gdbstub_be_mem_read_subword (const int       xlen,
				       const uint64_t  addr,
				       uint64_t       *data,
				       const uint32_t  len);

// ================================================================
// Read 'len' bytes from SoC memory starting at address 'addr' into 'data'.
// No alignment restriction on 'addr'; no restriction on 'len'.

extern
uint32_t  gdbstub_be_mem_read (const int       xlen,
			       const uint64_t  addr,
			       uint8_t        *data,
			       const uint32_t  len);

// ================================================================
// Write a value into the RISC-V PC

extern
uint32_t  gdbstub_be_PC_write (const int xlen, uint64_t regval);

// ================================================================
// Write a value into a RISC-V GPR register

extern
uint32_t  gdbstub_be_GPR_write (const int xlen, uint32_t regnum, uint64_t regval);

// ================================================================
// Write a value into a RISC-V FPR register

extern
uint32_t  gdbstub_be_FPR_write (const int xlen, uint32_t regnum, uint64_t regval);

// ================================================================
// Write a value into a RISC-V CSR register

extern
uint32_t  gdbstub_be_CSR_write (const int xlen, uint32_t regnum, uint64_t regval);

// ================================================================
// Write 'len' bytes of 'data' into RISC-V system memory, starting at address 'addr'
// where 'len' is 1, 2 or 4 only, and addr is aligned.

extern
uint32_t  gdbstub_be_mem_write_subword (const int       xlen,
					const uint64_t  addr,
					const uint64_t  data,
					const uint32_t  len);

// ================================================================
// Write 'len' bytes of 'data' into RISC-V system memory, starting at address 'addr'

extern
uint32_t  gdbstub_be_mem_write (const int xlen, const uint64_t addr, const uint8_t *data, const uint32_t len);

// ****************************************************************
// ****************************************************************
// ****************************************************************
// Raw reads and writes of the DMI interface (for debugging)

// ================================================================
// Raw DMI read

extern
uint32_t  gdbstub_be_dmi_read (uint32_t dmi_addr, uint64_t *p_data);

// ================================================================
// Raw DMI write

extern
uint32_t  gdbstub_be_dmi_write (uint32_t dmi_addr, uint64_t dmi_data);

// ================================================================

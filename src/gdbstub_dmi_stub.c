// Copyright (c) 2016-2020 Bluespec, Inc. All Rights Reserved
// Author: Rishiyur Nikhil

// ================================================================
// Stub implementation of DMI read/write functions

// ================================================================
// C lib includes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include <sys/mman.h>
#include <sys/types.h>

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

// ----------------
// Project includes

#include  "RVDM.h"

// ================================================================
// DMI interface (gdbstub invokes these functions)
// These should be filled in with the appropriate mechanisms that
// perform the actual DMI read/write on the RISC-V Debug module.

#include <sys/types.h>
#include <sys/ioctl.h>

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

struct fmem_request {
	uint32_t offset;
	uint32_t data;
	uint32_t access_width;
};

#define	FMEM_READ	_IOWR('X', 1, struct fmem_request)
#define	FMEM_WRITE	_IOWR('X', 2, struct fmem_request)

static int fd;

static int fmem_read(uint32_t offset)
{
        struct fmem_request req;
        int error;

	req.offset = offset;
	req.access_width = 4;

        error = ioctl(fd, FMEM_READ, &req);

        if (error == 0)
		return (req.data);

        return (0);
}

static int fmem_write(uint32_t offset, uint32_t data)
{
	struct fmem_request req;
	int error;

	req.offset = offset;
	req.data = data;
	req.access_width = 4;

	error = ioctl(fd, FMEM_WRITE, &req);

	return (error);
}

static int fmem_open ()
{
	char* fmemdev = getenv("RISCV_GDB_STUB_FMEM_DEV");
	char filename[256] = "/dev/fmem_sys0_debug_unit";
	if (fmemdev) {
		strncpy(filename, fmemdev, 255);
		filename[255] = '\0';
	}
	fd = open(filename, O_RDWR);
        return fd;
}

int dmi_init () {
  return fmem_open ();
}

void dmi_write (uint16_t addr, uint32_t data)
{
	//printf("%s: addr %x: data %x\n", __func__, addr, data);
	//fflush(stdout);
	fmem_write(addr * 4, data);
}

uint32_t dmi_read (uint16_t addr)
{
	//printf("%s: addr %x", __func__, addr);
	uint32_t reg;
	reg = fmem_read(addr * 4);
	//printf(", val %x\n", reg);
	//fflush(stdout);
	return (reg);
}

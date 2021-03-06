/*
 * Copyright (C) 2008 The Android Open Source Project
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#pragma once

#include <inttypes.h>
#include <stdlib.h>

#include <string>

#include <bootimg.h>
#include "fastboot_driver.h"
#include "util.h"

#include "constants.h"

class Transport;
struct sparse_file;

const std::string fb_get_error();

//#define FB_COMMAND_SZ (fastboot::FB_COMMAND_SZ)
//#define FB_RESPONSE_SZ (fastboot::FB_RESPONSE_SZ)

/* engine.c - high level command queue engine */

void fb_init(fastboot::FastBootDriver& fbi);

bool fb_getvar(const std::string& key, std::string* value);
void fb_queue_flash(const std::string& partition, void* data, uint32_t sz);
void fb_queue_flash_fd(const std::string& partition, int fd, uint32_t sz);
void fb_queue_flash_sparse(const std::string& partition, struct sparse_file* s, uint32_t sz,
                           size_t current, size_t total);
void fb_queue_erase(const std::string& partition);
void fb_queue_format(const std::string& partition, int skip_if_not_supported, int32_t max_chunk_sz);
void fb_queue_require(const std::string& prod, const std::string& var, bool invert, size_t nvalues,
                      const char** values);
void fb_queue_display(const std::string& label, const std::string& var);
void fb_queue_query_save(const std::string& var, char* dest, uint32_t dest_size);
void fb_queue_reboot(void);
void fb_queue_command(const std::string& cmd, const std::string& msg);
void fb_queue_download(const std::string& name, void* data, uint32_t size);
void fb_queue_download_fd(const std::string& name, int fd, uint32_t sz);
void fb_queue_upload(const std::string& outfile);
void fb_queue_notice(const std::string& notice);
void fb_queue_wait_for_disconnect(void);
void fb_queue_create_partition(const std::string& partition, const std::string& size);
void fb_queue_delete_partition(const std::string& partition);
void fb_queue_resize_partition(const std::string& partition, const std::string& size);
int64_t fb_execute_queue();
void fb_set_active(const std::string& slot);

/* Current product */
extern char cur_product[FB_RESPONSE_SZ + 1];

class FastBootTool {
  public:
    int Main(int argc, char* argv[]);

    void ParseOsPatchLevel(boot_img_hdr_v1*, const char*);
    void ParseOsVersion(boot_img_hdr_v1*, const char*);
};

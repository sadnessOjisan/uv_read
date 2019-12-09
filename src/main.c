
/*
 * Copyright (c) 2016, Saúl Ibarra Corretgé <saghul@gmail.com>
 * Copyright (c) 2012, Ben Noordhuis <info@bnoordhuis.nl>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <uv.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

static QUEUE users;

static void on_read(uv_stream_t *handle, ssize_t nread, const uv_buf_t *buf);
static void on_write(uv_write_t *req, int status);
static void on_close(uv_handle_t *handle);

int main(int argc, char **argv)
{
    uv_fs_open(uv_default_loop(), &open_req, argv[1], O_RDONLY, 0, on_open);
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    uv_fs_req_cleanup(&open_req);
    uv_fs_req_cleanup(&read_req);
    uv_fs_req_cleanup(&write_req);
    return 0;
}

void on_open(uv_fs_t *req)
{
    // The request passed to the callback is the same as the one the call setup
    // function was passed.
    assert(req == &open_req);
    if (req->result >= 0)
    {
        iov = uv_buf_init(buffer, sizeof(buffer));
        uv_fs_read(uv_default_loop(), &read_req, req->result,
                   &iov, 1, -1, on_read);
    }
    else
    {
        fprintf(stderr, "error opening file: %s\n", uv_strerror((int)req->result));
    }
}

void on_read(uv_fs_t *req)
{
    if (req->result < 0)
    {
        fprintf(stderr, "Read error: %s\n", uv_strerror(req->result));
    }
    else if (req->result == 0)
    {
        uv_fs_t close_req;
        // synchronous
        uv_fs_close(uv_default_loop(), &close_req, open_req.result, NULL);
    }
    else if (req->result > 0)
    {
        iov.len = req->result;
        uv_fs_write(uv_default_loop(), &write_req, 1, &iov, 1, -1, on_write);
    }
}

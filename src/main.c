#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <uv.h>

static uv_fs_t openReq;
static uv_fs_t readReq;
static uv_fs_t closeReq;
static uv_buf_t uvBuf;
static char strBuf[65];
static char dataBuf[64];

static void onRead(uv_fs_t *req);

static void readData(void)
{
    memset(strBuf, 0, sizeof(strBuf));
    memcpy(strBuf, dataBuf, sizeof(dataBuf));
    fprintf(stdout, "%s\n", strBuf);
}

static void onRead(uv_fs_t *req)
{
    if (req->result == 0)
    {
        uv_fs_close(uv_default_loop(), &closeReq, openReq.result, NULL);
    }
    else
    {
        readData();
    }
}

static void onOpen(uv_fs_t *req)
{
    if (req->result < 0)
    {
        fprintf(stderr, "error: %s\n", uv_strerror(req->result));
    }
    else
    {
        uvBuf = uv_buf_init(dataBuf, sizeof(dataBuf));
        uv_fs_read(uv_default_loop(), &readReq, req->result, &uvBuf, 1, -1, onRead);
    }
}

int main(int argc, char *argv[])
{
    uv_fs_open(uv_default_loop(), &openReq, argv[1], O_RDONLY, 0, onOpen);
    return uv_run(uv_default_loop(), UV_RUN_DEFAULT);
}
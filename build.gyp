# Copyright (c) 2016, Saúl Ibarra Corretgé <saghul@gmail.com>
# Copyright (c) 2012, Ben Noordhuis <info@bnoordhuis.nl>
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

# gyp -Duv_library=static_library --depth=$PWD --generator-output=$PWD/out -Goutput_dir=$PWD/out -f make build.gyp

{
  'targets': [
    {
      'target_name': 'chat-server',
      'type': 'executable',
      'dependencies': ['deps/libuv/uv.gyp:libuv'],
      'sources': ['src/main.c', 'src/queue.h', 'src/pokemon_names.h'],
    }
  ]
}
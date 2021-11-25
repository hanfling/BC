//
// Generic stuff.
//
// Copyright (c) 2016 Intel Corporation
// Copyright (c) 2020 Sebastian Kaufel
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this 
// software and associated documentation files (the "Software"), to deal in the Software 
// without restriction, including without limitation the rights to use, copy, modify, 
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
// permit persons to whom the Software is furnished to do so, subject to the following 
// conditions: 
//
// The above copyright notice and this permission notice shall be included in all copies 
// or substantial portions of the Software.  
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
// CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
// OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#include "BC.h"
#include "memory.h" // memcpy

void ReplicateBorders(rgba_surface* dst_slice, const rgba_surface* src_tex, int start_x, int start_y, int bpp)
{
	int bytes_per_pixel = bpp >> 3;

	bool aliasing = false;
	if (&src_tex->ptr[src_tex->stride * start_y + bytes_per_pixel * start_x] == dst_slice->ptr)
		aliasing = true;

	for (int y = 0; y < dst_slice->height; y++)
	{
		for (int x = 0; x < dst_slice->width; x++)
		{
			int xx = start_x + x;
			int yy = start_y + y;

			if (aliasing && xx < src_tex->width && yy < src_tex->height) continue;

			if (xx >= src_tex->width) xx = src_tex->width - 1;
			if (yy >= src_tex->height) yy = src_tex->height - 1;

			void* dst = &dst_slice->ptr[dst_slice->stride * y + bytes_per_pixel * x];
			void* src = &src_tex->ptr[src_tex->stride * yy + bytes_per_pixel * xx];

			memcpy(dst, src, bytes_per_pixel);
		}
	}
}

//
// The End.
//

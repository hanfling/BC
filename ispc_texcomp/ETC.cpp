//
// ETC, ETC2 and EAC support.
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
#include "kernel_etc_ispc.h"

//
// ETC1 Encode Settings.
//

struct KETC1EncodeSettings
{
	int fastSkipTreshold;
};

void GetProfile_etc_slow(KETC1EncodeSettings* settings)
{
	settings->fastSkipTreshold = 6;
}

// ETC1.
void ETC1EncodeRGBA8( const ISPCTC_Surface_RGBA8* InputSurface, uint8_t* OutputBlocks, KETC1EncodeSettings* Settings )
{
	ispc::ETC1_Compress_RGBA8( (ispc::Surface_RGBA8*)InputSurface, OutputBlocks, (ispc::etc_enc_settings*)Settings );
}
void ETC1EncodeRGBA16( const ISPCTC_Surface_RGBA16* InputSurface, uint8_t* OutputBlocks, KETC1EncodeSettings* Settings )
{
	ispc::ETC1_Compress_RGBA16( (ispc::Surface_RGBA16*)InputSurface, OutputBlocks, (ispc::etc_enc_settings*)Settings );
}
//void pETC1EncodeRGBA32F( const ISPCTC_Surface_RGBA32F* InputSurface, uint8_t* OutputBlocks, KETC1EncodeSettings* Settings );
//{
//	ispc::ETC1_Compress_RGBA32F( (ispc::Surface_RGBA32F*)InputSurface, OutputBlocks, (ispc::etc_enc_settings*)Settings );
//}

//
// The End.
//

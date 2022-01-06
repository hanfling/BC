//
// BC1-BC5 support.
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
#include "kernel_ispc.h"

// BC1.
void BC1EncodeRGBA8( const ISPCTC_Surface_RGBA8* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC1CompressRGBA8( (ispc::Surface_RGBA8*)InputSurface, OutputBlocks );
}
void BC1EncodeRGBA16( const ISPCTC_Surface_RGBA16* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC1CompressRGBA16( (ispc::Surface_RGBA16*)InputSurface, OutputBlocks );
}
//void KTexCompBC1EncodeRGBA32F( const ISPCTC_Surface_RGBA32F* InputSurface, uint8_t* OutputBlocks );
//{
//	ispc::BC1CompressRGBA32F( (ispc::Surface_RGBA32F*)InputSurface, OutputBlocks );
//}

// BC1 Punchthrough Alpha.
void BC1PAEncodeRGBA8( const ISPCTC_Surface_RGBA8* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC1PACompressRGBA8( (ispc::Surface_RGBA8*)InputSurface, OutputBlocks );
}
void BC1PAEncodeRGBA16( const ISPCTC_Surface_RGBA16* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC1PACompressRGBA16( (ispc::Surface_RGBA16*)InputSurface, OutputBlocks );
}
//void BC1PAEncodeRGBA32F( const ISPCTC_Surface_RGBA32F* InputSurface, uint8_t* OutputBlocks );
//{
//	ispc::BC1PACompressRGBA32F( (ispc::Surface_RGBA32F*)InputSurface, OutputBlocks );
//}

// BC2.
void BC2EncodeRGBA8( const ISPCTC_Surface_RGBA8* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC2CompressRGBA8( (ispc::Surface_RGBA8*)InputSurface, OutputBlocks );
}
void BC2EncodeRGBA16( const ISPCTC_Surface_RGBA16* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC2CompressRGBA16( (ispc::Surface_RGBA16*)InputSurface, OutputBlocks );
}
//void BC2EncodeRGBA32F( const ISPCTC_Surface_RGBA32F* InputSurface, uint8_t* OutputBlocks );
//{
//	ispc::BC2CompressRGBA32F( (ispc::Surface_RGBA32F*)InputSurface, OutputBlocks );
//}

// BC3.
void BC3EncodeRGBA8( const ISPCTC_Surface_RGBA8* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC3CompressRGBA8( (ispc::Surface_RGBA8*)InputSurface, OutputBlocks );
}
void BC3EncodeRGBA16( const ISPCTC_Surface_RGBA16* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC3CompressRGBA16( (ispc::Surface_RGBA16*)InputSurface, OutputBlocks );
}
//void BC3EncodeRGBA32F( const ISPCTC_Surface_RGBA32F* InputSurface, uint8_t* OutputBlocks )
//{
//	ispc::BC3CompressRGBA32F( (ispc::Surface_RGBA32F*)InputSurface, OutputBlocks );
//}

// BC4.
void BC4EncodeR8( const ISPCTC_Surface_R8* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC4CompressR8( (ispc::Surface_R8*)InputSurface, OutputBlocks );
}
void BC4EncodeR16( const ISPCTC_Surface_R16* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC4CompressR16( (ispc::Surface_R16*)InputSurface, OutputBlocks );
}
//void BC4EncodeR32F( const ISPCTC_Surface_R32F* InputSurface, uint8_t* OutputBlocks )
//{
//	ispc::BC4CompressR32F( (ispc::Surface_R32F*)InputSurface, OutputBlocks );
//}
//void BC4SEncodeR8S( const ISPCTC_Surface_R8S* InputSurface, uint8_t* OutputBlocks );
//void BC4SEncodeR16S( const ISPCTC_Surface_R16S* InputSurface, uint8_t* OutputBlocks );
//void BC4SEncodeSR32F( const ISPCTC_Surface_R32F* InputSurface, uint8_t* OutputBlocks );

// BC5.
void BC5EncodeRG8( const ISPCTC_Surface_RG8* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC5CompressRG8( (ispc::Surface_RG8*)InputSurface, OutputBlocks );
}
void BC5EncodeRG16( const ISPCTC_Surface_RG16* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC5CompressRG16( (ispc::Surface_RG16*)InputSurface, OutputBlocks );
}
//void BC5EncodeRG32F( const ISPCTC_Surface_RG32F* InputSurface, uint8_t* OutputBlocks )
//{
//	ispc::BC5CompressRG32F( (ispc::Surface_RG32F*)InputSurface, OutputBlocks );
//}
//void BC5SEncodeRG8S( const ISPCTC_Surface_RG8S* InputSurface, uint8_t* OutputBlocks );
//void BC5SEncodeRG16S( const ISPCTC_Surface_RG16S* InputSurface, uint8_t* OutputBlocks );
//void BC5SEncodeRG32F( const ISPCTC_Surface_RG32F* InputSurface, uint8_t* OutputBlocks );

//
// The End.
//

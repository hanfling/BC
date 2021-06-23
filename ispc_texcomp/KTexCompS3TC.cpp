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

#include "ispc_texcomp.h"
#include "kernel_ispc.h"

// BC1.
void CompressBlocksBC1( const rgba_surface* InputSurface, uint8_t* OutputBlocks )
{
	KTexCompBC1CompressRGBA8( (const ISPCTC_Surface_RGBA8*)InputSurface, OutputBlocks );
}
void KTexCompBC1CompressRGBA8( const ISPCTC_Surface_RGBA8* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC1CompressRGBA8( (ispc::Surface_RGBA8*)InputSurface, OutputBlocks );
}
void KTexCompBC1CompressRGBA16( const ISPCTC_Surface_RGBA16* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC1CompressRGBA16( (ispc::Surface_RGBA16*)InputSurface, OutputBlocks );
}
//void KTexCompBC1CompressRGBA32F( const ISPCTC_Surface_RGBA32F* InputSurface, uint8_t* OutputBlocks );
//{
//	ispc::BC1CompressRGBA32F( (ispc::Surface_RGBA32F*)InputSurface, OutputBlocks );
//}

// BC1 Punchthrough Alpha.
void CompressBlocksBC1Alpha( const rgba_surface* InputSurface, uint8_t* OutputBlocks )
{
	KTexCompBC1PACompressRGBA8( (const ISPCTC_Surface_RGBA8*)InputSurface, OutputBlocks );
}
void KTexCompBC1PACompressRGBA8( const ISPCTC_Surface_RGBA8* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC1PACompressRGBA8( (ispc::Surface_RGBA8*)InputSurface, OutputBlocks );
}
void KTexCompBC1PACompressRGBA16( const ISPCTC_Surface_RGBA16* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC1PACompressRGBA16( (ispc::Surface_RGBA16*)InputSurface, OutputBlocks );
}
//void KTexCompBC1PACompressRGBA32F( const ISPCTC_Surface_RGBA32F* InputSurface, uint8_t* OutputBlocks );
//{
//	ispc::BC1PACompressRGBA32F( (ispc::Surface_RGBA32F*)InputSurface, OutputBlocks );
//}

// BC2.
void CompressBlocksBC2( const rgba_surface* InputSurface, uint8_t* OutputBlocks )
{
	KTexCompBC2CompressRGBA8( (const ISPCTC_Surface_RGBA8*)InputSurface, OutputBlocks );
}
void KTexCompBC2CompressRGBA8( const ISPCTC_Surface_RGBA8* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC2CompressRGBA8( (ispc::Surface_RGBA8*)InputSurface, OutputBlocks );
}
void KTexCompBC2CompressRGBA16( const ISPCTC_Surface_RGBA16* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC2CompressRGBA16( (ispc::Surface_RGBA16*)InputSurface, OutputBlocks );
}
//void KTexCompBC2CompressRGBA32F( const ISPCTC_Surface_RGBA32F* InputSurface, uint8_t* OutputBlocks );
//{
//	ispc::BC2CompressRGBA32F( (ispc::Surface_RGBA32F*)InputSurface, OutputBlocks );
//}

// BC3.
void CompressBlocksBC3( const rgba_surface* InputSurface, uint8_t* OutputBlocks )
{
	KTexCompBC3CompressRGBA8( (const ISPCTC_Surface_RGBA8*)InputSurface, OutputBlocks );
}
void KTexCompBC3CompressRGBA8( const ISPCTC_Surface_RGBA8* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC3CompressRGBA8( (ispc::Surface_RGBA8*)InputSurface, OutputBlocks );
}
void KTexCompBC3CompressRGBA16( const ISPCTC_Surface_RGBA16* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC3CompressRGBA16( (ispc::Surface_RGBA16*)InputSurface, OutputBlocks );
}
//void KTexCompBC3CompressRGBA32F( const ISPCTC_Surface_RGBA32F* InputSurface, uint8_t* OutputBlocks )
//{
//	ispc::BC3CompressRGBA32F( (ispc::Surface_RGBA32F*)InputSurface, OutputBlocks );
//}

// BC4.
void CompressBlocksBC4( const red_surface* InputSurface, uint8_t* OutputBlocks )
{
	KTexCompBC4CompressR8( (const ISPCTC_Surface_R8*)InputSurface, OutputBlocks );
}
void KTexCompBC4CompressR8( const ISPCTC_Surface_R8* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC4CompressR8( (ispc::Surface_R8*)InputSurface, OutputBlocks );
}
void KTexCompBC4CompressR16( const ISPCTC_Surface_R16* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC4CompressR16( (ispc::Surface_R16*)InputSurface, OutputBlocks );
}
//void KTexCompBC4CompressR32F( const ISPCTC_Surface_R32F* InputSurface, uint8_t* OutputBlocks )
//{
//	ispc::BC4CompressR32F( (ispc::Surface_R32F*)InputSurface, OutputBlocks );
//}
//void KTexCompBC4SCompressR8S( const ISPCTC_Surface_R8S* InputSurface, uint8_t* OutputBlocks );
//void KTexCompBC4SCompressR16S( const ISPCTC_Surface_R16S* InputSurface, uint8_t* OutputBlocks );
//void KTexCompBC4SCompressSR32F( const ISPCTC_Surface_R32F* InputSurface, uint8_t* OutputBlocks );

// BC5.
void CompressBlocksBC5( const rg_surface* InputSurface, uint8_t* OutputBlocks )
{
	KTexCompBC5CompressRG8( (const ISPCTC_Surface_RG8*)InputSurface, OutputBlocks );
}
void KTexCompBC5CompressRG8( const ISPCTC_Surface_RG8* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC5CompressRG8( (ispc::Surface_RG8*)InputSurface, OutputBlocks );
}
void KTexCompBC5CompressRG16( const ISPCTC_Surface_RG16* InputSurface, uint8_t* OutputBlocks )
{
	ispc::BC5CompressRG16( (ispc::Surface_RG16*)InputSurface, OutputBlocks );
}
//void KTexCompBC5CompressRG32F( const ISPCTC_Surface_RG32F* InputSurface, uint8_t* OutputBlocks )
//{
//	ispc::BC5CompressRG32F( (ispc::Surface_RG32F*)InputSurface, OutputBlocks );
//}
//void KTexCompBC5SCompressRG8S( const ISPCTC_Surface_RG8S* InputSurface, uint8_t* OutputBlocks );
//void KTexCompBC5SCompressRG16S( const ISPCTC_Surface_RG16S* InputSurface, uint8_t* OutputBlocks );
//void KTexCompBC5SCompressRG32F( const ISPCTC_Surface_RG32F* InputSurface, uint8_t* OutputBlocks );

//
// The End.
//

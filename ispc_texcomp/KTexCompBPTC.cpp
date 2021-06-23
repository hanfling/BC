//
// BC6H and BC7 support.
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
#include "kernel_bptc_ispc.h"

//
// BC6H Profiles.
//
void GetProfile_bc6h_veryfast(bc6h_enc_settings* settings)
{
	settings->slow_mode = false;
	settings->fast_mode = true;
	settings->fastSkipTreshold = 0;
	settings->refineIterations_1p = 0;
	settings->refineIterations_2p = 0;
}

void GetProfile_bc6h_fast(bc6h_enc_settings* settings)
{
	settings->slow_mode = false;
	settings->fast_mode = true;
	settings->fastSkipTreshold = 2;
	settings->refineIterations_1p = 0;
	settings->refineIterations_2p = 1;
}

void GetProfile_bc6h_basic(bc6h_enc_settings* settings)
{
	settings->slow_mode = false;
	settings->fast_mode = false;
	settings->fastSkipTreshold = 4;
	settings->refineIterations_1p = 2;
	settings->refineIterations_2p = 2;
}

void GetProfile_bc6h_slow(bc6h_enc_settings* settings)
{
	settings->slow_mode = true;
	settings->fast_mode = false;
	settings->fastSkipTreshold = 10;
	settings->refineIterations_1p = 2;
	settings->refineIterations_2p = 2;
}

void GetProfile_bc6h_veryslow(bc6h_enc_settings* settings)
{
	settings->slow_mode = true;
	settings->fast_mode = false;
	settings->fastSkipTreshold = 32;
	settings->refineIterations_1p = 2;
	settings->refineIterations_2p = 2;
}

//
// BC7 Development Profile -- For library internal development use only.
//
void GetProfile_bc6h_development( bc6h_enc_settings* Settings )
{
	Settings->slow_mode = true;
	Settings->fast_mode = false;
	Settings->fastSkipTreshold = 32;
	Settings->refineIterations_1p = 2;
	Settings->refineIterations_2p = 2;
}

//
// BC7 Profiles (w/o alpha).
//
void GetProfile_ultrafast( bc7_enc_settings* Settings )
{
	Settings->IgnoreAlphaError = false;
	Settings->channels = 3;

	// Modes 0 and 2.
	Settings->ModeEnabled[0] = false;
	Settings->ModeEnabled[2] = false;
	Settings->RefineIterations[0] = 2;
	Settings->RefineIterations[2] = 2;

	// Modes 1, 3 and 7.
	Settings->ModeEnabled[1] = false;
	Settings->ModeEnabled[3] = false;
	Settings->ModeEnabled[7] = false;
	Settings->fastSkipTreshold_mode1 = 3;
	Settings->fastSkipTreshold_mode3 = 1;
	Settings->fastSkipTreshold_mode7 = 0;
	Settings->RefineIterations[1] = 2;
	Settings->RefineIterations[3] = 1;
	Settings->RefineIterations[7] = 2;

	// Modes 4 and 5.
	Settings->ModeEnabled[4] = false;
	Settings->ModeEnabled[5] = false;
	Settings->mode45_channel0 = 0;
	Settings->refineIterations_channel = 0;
	Settings->RefineIterations[4] = 2;
	Settings->RefineIterations[5] = 2;

	// Mode 6.
	Settings->ModeEnabled[6] = true;
	Settings->RefineIterations[6] = 1;
}

void GetProfile_veryfast(bc7_enc_settings* Settings)
{
	Settings->IgnoreAlphaError = false;
	Settings->channels = 3;

	// Modes 0 and 2.
	Settings->ModeEnabled[0] = false;
	Settings->ModeEnabled[2] = false;
	Settings->RefineIterations[0] = 2;
	Settings->RefineIterations[2] = 2;

	// Modes 1, 3 and 7.
	Settings->ModeEnabled[1] = true;
	Settings->ModeEnabled[3] = true;
	Settings->ModeEnabled[7] = true; // !! Disabled by fastSkipTreshold_mode7==0.
	Settings->fastSkipTreshold_mode1 = 3;
	Settings->fastSkipTreshold_mode3 = 1;
	Settings->fastSkipTreshold_mode7 = 0;
	Settings->RefineIterations[1] = 2;
	Settings->RefineIterations[3] = 1;
	Settings->RefineIterations[7] = 2;

	// Modes 4 and 5.
	Settings->ModeEnabled[4] = false;
	Settings->ModeEnabled[5] = false;
	Settings->mode45_channel0 = 0;
	Settings->refineIterations_channel = 0;
	Settings->RefineIterations[4] = 2;
	Settings->RefineIterations[5] = 2;

	// Mode 6.
	Settings->ModeEnabled[6] = true;
	Settings->RefineIterations[6] = 1;
}

void GetProfile_fast( bc7_enc_settings* Settings )
{
	Settings->IgnoreAlphaError = false;
	Settings->channels = 3;

	// Modes 0 and 2.
	Settings->ModeEnabled[0] = false;
	Settings->ModeEnabled[2] = false;
	Settings->RefineIterations[0] = 2;
	Settings->RefineIterations[2] = 2;

	// Modes 1, 3 and 7.
	Settings->ModeEnabled[1] = true;
	Settings->ModeEnabled[3] = true;
	Settings->ModeEnabled[7] = true; // !! Disabled by fastSkipTreshold_mode7==0.
	Settings->fastSkipTreshold_mode1 = 12;
	Settings->fastSkipTreshold_mode3 = 4;
	Settings->fastSkipTreshold_mode7 = 0;
	Settings->RefineIterations[1] = 2;
	Settings->RefineIterations[3] = 1;
	Settings->RefineIterations[7] = 2;

	// Modes 4 and 5.
	Settings->ModeEnabled[4] = false;
	Settings->ModeEnabled[5] = false;
	Settings->mode45_channel0 = 0;
	Settings->refineIterations_channel = 0;
	Settings->RefineIterations[4] = 2;
	Settings->RefineIterations[5] = 2;

	// Mode 6.
	Settings->ModeEnabled[6] = true;
	Settings->RefineIterations[6] = 2;
}

void GetProfile_basic( bc7_enc_settings* Settings )
{
	Settings->IgnoreAlphaError = false;
	Settings->channels = 3;

	// Modes 0 and 2.
	Settings->ModeEnabled[0] = true;
	Settings->ModeEnabled[2] = false;
	Settings->RefineIterations[0] = 2;
	Settings->RefineIterations[2] = 2;

	// Modes 1, 3 and 7.
	Settings->ModeEnabled[1] = true;
	Settings->ModeEnabled[3] = true;
	Settings->ModeEnabled[7] = true; // !! Disabled by fastSkipTreshold_mode7==0.
	Settings->fastSkipTreshold_mode1 = 8+4;
	Settings->fastSkipTreshold_mode3 = 8;
	Settings->fastSkipTreshold_mode7 = 0;
	Settings->RefineIterations[1] = 2;
	Settings->RefineIterations[3] = 2;
	Settings->RefineIterations[7] = 2;

	// Modes 4 and 5.
	Settings->ModeEnabled[4] = true;
	Settings->ModeEnabled[5] = true;
	Settings->mode45_channel0 = 0;
	Settings->refineIterations_channel = 2;
	Settings->RefineIterations[4] = 2;
	Settings->RefineIterations[5] = 2;

	// Mode 6.
	Settings->ModeEnabled[6] = true;

	Settings->RefineIterations[6] = 2;
}

void GetProfile_slow( bc7_enc_settings* Settings )
{
	Settings->IgnoreAlphaError = false;
	Settings->channels = 3;

	const int MoreRefineIterations = 2;

	// Modes 0 and 2.
	Settings->ModeEnabled[0] = true;
	Settings->ModeEnabled[2] = true;
	Settings->RefineIterations[0] = 2+MoreRefineIterations;
	Settings->RefineIterations[2] = 2+MoreRefineIterations;

	// Modes 1, 3 and 7.
	Settings->ModeEnabled[1] = true;
	Settings->ModeEnabled[3] = true;
	Settings->ModeEnabled[7] = true;
	Settings->fastSkipTreshold_mode1 = 64;
	Settings->fastSkipTreshold_mode3 = 64;
	Settings->fastSkipTreshold_mode7 = 0; // !! Disabled by fastSkipTreshold_mode7==0.
	Settings->RefineIterations[1] = 2+MoreRefineIterations;
	Settings->RefineIterations[3] = 2+MoreRefineIterations;
	Settings->RefineIterations[7] = 2+MoreRefineIterations;

	// Modes 4 and 5.
	Settings->ModeEnabled[4] = true;
	Settings->ModeEnabled[5] = true;
	Settings->mode45_channel0 = 0;
	Settings->refineIterations_channel = 2+MoreRefineIterations;
	Settings->RefineIterations[4] = 2+MoreRefineIterations;
	Settings->RefineIterations[5] = 2+MoreRefineIterations;

	// Mode 6.
	Settings->ModeEnabled[6] = true;
	Settings->RefineIterations[6] = 2+MoreRefineIterations;
}

void GetProfile_veryslow( bc7_enc_settings* Settings )
{
	Settings->IgnoreAlphaError = false;
#if 1
	// Currently vslow profile seems to be only slower, but won't yield a lower psnr.
	GetProfile_slow( Settings );
	return;
#endif

	Settings->channels = 3;

	const int MoreRefineIterations = 8; // Was 2 in GetProfile_slow, but even 16 doesn't seem to make any difference at all.

	// Modes 0 and 2.
	Settings->ModeEnabled[0] = true;
	Settings->ModeEnabled[2] = true;
	Settings->RefineIterations[0] = 2+MoreRefineIterations;
	Settings->RefineIterations[2] = 2+MoreRefineIterations;

	// Modes 1, 3 and 7.
	Settings->ModeEnabled[1] = true;
	Settings->ModeEnabled[3] = true;
	Settings->ModeEnabled[7] = true;
	Settings->fastSkipTreshold_mode1 = 64;
	Settings->fastSkipTreshold_mode3 = 64;
	Settings->fastSkipTreshold_mode7 = 64; // Was 0 in GetProfile_slow, but doesn't seem to make any difference in psnr.
	Settings->RefineIterations[1] = 2+MoreRefineIterations;
	Settings->RefineIterations[3] = 2+MoreRefineIterations;
	Settings->RefineIterations[7] = 2+MoreRefineIterations;

	// Modes 4 and 5.
	Settings->ModeEnabled[4] = true;
	Settings->ModeEnabled[5] = true;
	Settings->mode45_channel0 = 0;
	Settings->refineIterations_channel = 2+MoreRefineIterations;
	Settings->RefineIterations[4] = 2+MoreRefineIterations;
	Settings->RefineIterations[5] = 2+MoreRefineIterations;

	// Mode 6.
	Settings->ModeEnabled[6] = true;
	Settings->RefineIterations[6] = 2+MoreRefineIterations;
}

//
// BC7 Profiles (with alpha).
//
void GetProfile_alpha_ultrafast( bc7_enc_settings* Settings )
{
	Settings->IgnoreAlphaError = false;
	Settings->channels = 4;

	// Modes 0 and 2.
	Settings->ModeEnabled[0] = false;
	Settings->ModeEnabled[2] = false;
	Settings->RefineIterations[0] = 2;
	Settings->RefineIterations[2] = 2;

	// Modes 1, 3 and 7.
	Settings->ModeEnabled[1] = false;
	Settings->ModeEnabled[3] = false;
	Settings->ModeEnabled[7] = false;
	Settings->fastSkipTreshold_mode1 = 0;
	Settings->fastSkipTreshold_mode3 = 0;
	Settings->fastSkipTreshold_mode7 = 4;
	Settings->RefineIterations[1] = 1;
	Settings->RefineIterations[3] = 1;
	Settings->RefineIterations[7] = 2;

	// Modes 4 and 5.
	Settings->ModeEnabled[4] = true;
	Settings->ModeEnabled[5] = true;
	Settings->mode45_channel0 = 3;
	Settings->refineIterations_channel = 1;
	Settings->RefineIterations[4] = 1;
	Settings->RefineIterations[5] = 1;

	// Mode 6.
	Settings->ModeEnabled[6] = true;
	Settings->RefineIterations[6] = 2;
}

void GetProfile_alpha_veryfast( bc7_enc_settings* Settings )
{
	Settings->IgnoreAlphaError = false;
	Settings->channels = 4;

	// Modes 0 and 2.
	Settings->ModeEnabled[0] = false;
	Settings->ModeEnabled[2] = false;
	Settings->RefineIterations[0] = 2;
	Settings->RefineIterations[2] = 2;

	// Modes 1, 3 and 7.
	Settings->ModeEnabled[1] = true; // !! Disabled by fastSkipTreshold_mode7==0.
	Settings->ModeEnabled[3] = true; // !! Disabled by fastSkipTreshold_mode7==0.
	Settings->ModeEnabled[7] = true;
	Settings->fastSkipTreshold_mode1 = 0;
	Settings->fastSkipTreshold_mode3 = 0;
	Settings->fastSkipTreshold_mode7 = 4;
	Settings->RefineIterations[1] = 1;
	Settings->RefineIterations[3] = 1;
	Settings->RefineIterations[7] = 2;

	// Modes 4 and 5.
	Settings->ModeEnabled[4] = true;
	Settings->ModeEnabled[5] =true ;
	Settings->mode45_channel0 = 3;
	Settings->refineIterations_channel = 2;
	Settings->RefineIterations[4] = 2;
	Settings->RefineIterations[5] = 2;

	// Mode 6.
	Settings->ModeEnabled[6] = true;
	Settings->RefineIterations[6] = 2;
}

void GetProfile_alpha_fast( bc7_enc_settings* Settings )
{
	Settings->IgnoreAlphaError = false;
	Settings->channels = 4;

	// Modes 0 and 2.
	Settings->ModeEnabled[0] = false;
	Settings->ModeEnabled[2] = false;
	Settings->RefineIterations[0] = 2;
	Settings->RefineIterations[2] = 2;

	// Modes 1, 3 and 7.
	Settings->ModeEnabled[1] = true;
	Settings->ModeEnabled[3] = true;
	Settings->ModeEnabled[7] = true;
	Settings->fastSkipTreshold_mode1 = 4;
	Settings->fastSkipTreshold_mode3 = 4;
	Settings->fastSkipTreshold_mode7 = 8;
	Settings->RefineIterations[1] = 1;
	Settings->RefineIterations[3] = 1;
	Settings->RefineIterations[7] = 2;

	// Modes 4 and 5.
	Settings->ModeEnabled[4] = true;
	Settings->ModeEnabled[5] = true;
	Settings->mode45_channel0 = 3;
	Settings->refineIterations_channel = 2;
	Settings->RefineIterations[4] = 2;
	Settings->RefineIterations[5] = 2;

	// Mode 6.
	Settings->ModeEnabled[6] = true;
	Settings->RefineIterations[6] = 2;
}

void GetProfile_alpha_basic( bc7_enc_settings* Settings )
{
	Settings->IgnoreAlphaError = false;
	Settings->channels = 4;

	// Modes 0 and 2.
	Settings->ModeEnabled[0] = true;
	Settings->ModeEnabled[2] = true;
	Settings->RefineIterations[0] = 2;
	Settings->RefineIterations[2] = 2;

	// Modes 1, 3 and 7.
	Settings->ModeEnabled[1] = true;
	Settings->ModeEnabled[3] = true;
	Settings->ModeEnabled[7] = true;
	Settings->fastSkipTreshold_mode1 = 8+4;
	Settings->fastSkipTreshold_mode3 = 8;
	Settings->fastSkipTreshold_mode7 = 8;
	Settings->RefineIterations[1] = 2;
	Settings->RefineIterations[3] = 2;
	Settings->RefineIterations[7] = 2;

	// Modes 4 and 5.
	Settings->ModeEnabled[4] = true;
	Settings->ModeEnabled[5] = true;
	Settings->mode45_channel0 = 0;
	Settings->refineIterations_channel = 2;
	Settings->RefineIterations[4] = 2;
	Settings->RefineIterations[5] = 2;

	// Mode 6.
	Settings->ModeEnabled[6] = true;
	Settings->RefineIterations[6] = 2;
}

void GetProfile_alpha_slow( bc7_enc_settings* Settings )
{
	Settings->IgnoreAlphaError = false;
	Settings->channels = 4;

	const int MoreRefineIterations = 2;

	// Modes 0 and 2.
	Settings->ModeEnabled[0] = true;
	Settings->ModeEnabled[2] = true;
	Settings->RefineIterations[0] = 2+MoreRefineIterations;
	Settings->RefineIterations[2] = 2+MoreRefineIterations;

	// Modes 1, 3 and 7.
	Settings->ModeEnabled[1] = true;
	Settings->ModeEnabled[3] = true;
	Settings->ModeEnabled[7] = true;
	Settings->fastSkipTreshold_mode1 = 64;
	Settings->fastSkipTreshold_mode3 = 64;
	Settings->fastSkipTreshold_mode7 = 64;
	Settings->RefineIterations[1] = 2+MoreRefineIterations;
	Settings->RefineIterations[3] = 2+MoreRefineIterations;
	Settings->RefineIterations[7] = 2+MoreRefineIterations;

	// Modes 4 and 5.
	Settings->ModeEnabled[4] = true;
	Settings->ModeEnabled[5] = true;
	Settings->mode45_channel0 = 0;
	Settings->refineIterations_channel = 2+MoreRefineIterations;
	Settings->RefineIterations[4] = 2+MoreRefineIterations;
	Settings->RefineIterations[5] = 2+MoreRefineIterations;

	// Mode 6.
	Settings->ModeEnabled[6] = true;
	Settings->RefineIterations[6] = 2+MoreRefineIterations;
}

void GetProfile_alpha_veryslow( bc7_enc_settings* Settings )
{
#if 1
	// Currently vslow profile seems to be only slower, but won't yield a lower psnr.
	GetProfile_alpha_slow( Settings );
	return;
#endif

	Settings->IgnoreAlphaError = false;
	Settings->channels = 4;

	const int MoreRefineIterations = 8; // Was 2 in GetProfile_alpha_slow, but even 16 doesn't seem to make any difference at all.

	// Modes 0 and 2.
	Settings->ModeEnabled[0] = true;
	Settings->ModeEnabled[2] = true;
	Settings->RefineIterations[0] = 2+MoreRefineIterations;
	Settings->RefineIterations[2] = 2+MoreRefineIterations;

	// Modes 1, 3 and 7.
	Settings->ModeEnabled[1] = true;
	Settings->ModeEnabled[3] = true;
	Settings->ModeEnabled[7] = true;
	Settings->fastSkipTreshold_mode1 = 64;
	Settings->fastSkipTreshold_mode3 = 64;
	Settings->fastSkipTreshold_mode7 = 64;
	Settings->RefineIterations[1] = 2+MoreRefineIterations;
	Settings->RefineIterations[3] = 2+MoreRefineIterations;
	Settings->RefineIterations[7] = 2+MoreRefineIterations;

	// Modes 4 and 5.
	Settings->ModeEnabled[4] = true;
	Settings->ModeEnabled[5] = true;
	Settings->mode45_channel0 = 0;
	Settings->refineIterations_channel = 2+MoreRefineIterations;
	Settings->RefineIterations[4] = 2+MoreRefineIterations;
	Settings->RefineIterations[5] = 2+MoreRefineIterations;

	// Mode 6.
	Settings->ModeEnabled[6] = true;
	Settings->RefineIterations[6] = 2+MoreRefineIterations;
}

//
// BC7 Development Profile -- For library internal development use only.
//
void GetProfile_development( bc7_enc_settings* Settings )
{	
	GetProfile_slow( Settings );

	Settings->IgnoreAlphaError = true;
	Settings->channels = 3;
}

//
// BC6H entry points into ispc  code.
//
void CompressBlocksBC6H( const rgba_surface* InputSurface, uint8_t* OutputBlocks, bc6h_enc_settings* EncSettings )
{
	KTexCompBC6HCompressRGBA16F( (const ISPCTC_Surface_RGBA16F*)InputSurface, OutputBlocks, EncSettings );
}
void KTexCompBC6HCompressRGBA16F( const ISPCTC_Surface_RGBA16F* InputSurface, uint8_t* OutputBlocks, bc6h_enc_settings* EncSettings )
{
	ispc::CompressBlocksBC6H_ispc( (ispc::rgba_surface*)InputSurface, OutputBlocks, (ispc::bc6h_enc_settings*)EncSettings );
}
//void KTexCompBC6HCompressRGBA32F( const ISPCTC_Surface_RGBA32F* InputSurface, uint8_t* OutputBlocks, bc6h_enc_settings* EncSettings );
//void KTexCompBC6HSCompressRGBA16F( const ISPCTC_Surface_RGBA16F* InputSurface, uint8_t* OutputBlocks, bc6h_enc_settings* EncSettings );
//void KTexCompBC6HSCompressRGBA32F( const ISPCTC_Surface_RGBA32F* InputSurface, uint8_t* OutputBlocks, bc6h_enc_settings* EncSettings );

//
// BC7 entry points into ispc  code.
//
void CompressBlocksBC7( const rgba_surface* InputSurface, uint8_t* OutputBlocks, bc7_enc_settings* EncSettings )
{
	KTexCompBC7CompressRGBA8( (const ISPCTC_Surface_RGBA8*)InputSurface, OutputBlocks, EncSettings);
}
void KTexCompBC7CompressRGBA8( const ISPCTC_Surface_RGBA8* InputSurface, uint8_t* OutputBlocks, bc7_enc_settings* EncSettings )
{
	ispc::BC7_Compress_RGBA8( (ispc::Surface_RGBA8*)InputSurface, OutputBlocks, (ispc::bc7_enc_settings*)EncSettings );
}
void KTexCompBC7CompressRGBA16( const ISPCTC_Surface_RGBA16* InputSurface, uint8_t* OutputBlocks, bc7_enc_settings* EncSettings )
{
	ispc::BC7_Compress_RGBA16( (ispc::Surface_RGBA16*)InputSurface, OutputBlocks, (ispc::bc7_enc_settings*)EncSettings );
}
//void KTexCompBC7CompressRGBA32F( const ISPCTC_Surface_RGBA32F* InputSurface, uint8_t* OutputBlocks, bc7_enc_settings* EncSettings );
//{
//	ispc::BC7_Compress_RGBA32F( (ispc::Surface_RGBA32F*)InputSurface, OutputBlocks, (ispc::bc7_enc_settings*)EncSettings );
//}

//
// The End.
//

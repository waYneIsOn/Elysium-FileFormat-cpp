/*
===========================================================================

Copyright (C) 2020 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_FILEFORMAT_IMAGING_JPG_JPGMARKER
#define ELYSIUM_FILEFORMAT_IMAGING_JPG_JPGMARKER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_SYSTEM
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/System.hpp"
#endif

namespace Elysium::FileFormat::Imaging::Jpg
{
#if defined(ELYSIUM_CORE_OS_WINDOWS)
	enum class JpgMarker : Elysium::Core::uint8_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class JpgMarker
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// Start of image
		/// </summary>
		SOI = 0xD8,

		/// <summary>
		/// End of image
		/// </summary>
		EOI = 0xD9,

		/// <summary>
		/// Start of frame (baseline DCT)
		/// </summary>
		SOF0 = 0xC0,

		/// <summary>
		/// Start of frame (progressive DCT)
		/// </summary>
		SOF2 = 0xC2,

		/// <summary>
		/// Define huffman table(s)
		/// </summary>
		DHT = 0xC4,

		/// <summary>
		/// Define quantization table(s)
		/// </summary>
		DQT = 0xDB,

		/// <summary>
		/// Define restart interval
		/// </summary>
		DRI = 0xDD,

		/// <summary>
		/// Start of scan
		/// </summary>
		SOS = 0xDA,

		/// <summary>
		/// Restart 0
		/// </summary>
		RST0 = 0xD0,
		
		/// <summary>
		/// Restart 1
		/// </summary>
		RST1 = 0xD1,

		/// <summary>
		/// Restart 2
		/// </summary>
		RST2 = 0xD2,

		/// <summary>
		/// Restart 3
		/// </summary>
		RST3 = 0xD3,

		/// <summary>
		/// Restart 4
		/// </summary>
		RST4 = 0xD4,

		/// <summary>
		/// Restart 5
		/// </summary>
		RST5 = 0xD5,

		/// <summary>
		/// Restart 6
		/// </summary>
		RST6 = 0xD6,

		/// <summary>
		/// Restart 7
		/// </summary>
		RST7 = 0xD7,
		
		/// <summary>
		/// Application specific 0
		/// </summary>
		APP0 = 0xE0,
		
		/// <summary>
		/// Application specific 1
		/// </summary>
		APP1 = 0xE1,

		/// <summary>
		/// Application specific 2
		/// </summary>
		APP2 = 0xE2,

		/// <summary>
		/// Application specific 3
		/// </summary>
		APP3 = 0xE3,

		/// <summary>
		/// Application specific 4
		/// </summary>
		APP4 = 0xE4,

		/// <summary>
		/// Application specific 5
		/// </summary>
		APP5 = 0xE5,

		/// <summary>
		/// Application specific 6
		/// </summary>
		APP6 = 0xE6,

		/// <summary>
		/// Application specific 7
		/// </summary>
		APP7 = 0xE7,

		/// <summary>
		/// Application specific 8
		/// </summary>
		APP8 = 0xE8,

		/// <summary>
		/// Application specific 9
		/// </summary>
		APP9 = 0xE9,

		/// <summary>
		/// Application specific 10
		/// </summary>
		APP10 = 0xEA,

		/// <summary>
		/// Application specific 11
		/// </summary>
		APP11 = 0xEB,

		/// <summary>
		/// Application specific 12
		/// </summary>
		APP12 = 0xEC,

		/// <summary>
		/// Application specific 13
		/// </summary>
		APP13 = 0xED,

		/// <summary>
		/// Application specific 14
		/// </summary>
		APP14 = 0xEE,

		/// <summary>
		/// Application specific 15
		/// </summary>
		APP15 = 0xEF,
		
		/// <summary>
		/// Comment
		/// </summary>
		COM = 0xFE,
	};
}
#endif

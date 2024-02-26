/*
===========================================================================

Copyright (C) 2020 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_FILEFORMAT_IMAGING_JPG_JPGHUFFMANTABLETYPE
#define ELYSIUM_FILEFORMAT_IMAGING_JPG_JPGHUFFMANTABLETYPE

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
	enum class JpgHuffmanTableType : Elysium::Core::uint8_t
#elif defined(ELYSIUM_CORE_OS_ANDROID)
	enum class JpgHuffmanTableType
#else
#error "undefined os"
#endif
	{
		/// <summary>
		/// 
		/// </summary>
		DC = 0,

		/// <summary>
		/// 
		/// </summary>
		AC = 1
	};
}
#endif

/*
===========================================================================

Copyright (C) 2020 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_FILEFORMAT_PDF_PDFROTATION
#define ELYSIUM_FILEFORMAT_PDF_PDFROTATION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::FileFormat::PDF
{
#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
	enum class PdfPageRotation : Elysium::Core::uint32_t
#elif defined(__ANDROID__)
	enum class PdfPageRotation
#else
#error "undefined os"
#endif
	{
		Normal = 0,

		Rotate90 = 1,

		Rotate180 = 2,

		Rotate270 = 3
	};
}
#endif

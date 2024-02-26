/*
===========================================================================

Copyright (C) 2020 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_FILEFORMAT_IMAGING_JPG_JPGSEGMENT
#define ELYSIUM_FILEFORMAT_IMAGING_JPG_JPGSEGMENT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_FILEFORMAT_IMAGING_API
#include "../Elysium.FileFormat.Imaging/API.hpp"
#endif

#ifndef ELYSIUM_FILEFORMAT_IMAGING_JPG_JPGMARKER
#include "JpgMarker.hpp"
#endif

namespace Elysium::FileFormat::Imaging::Jpg
{
	class ELYSIUM_FILEFORMAT_IMAGING_API JpgSegment
	{
	public:
		JpgSegment() = delete;
		JpgSegment(const JpgSegment& Source) = delete;
		JpgSegment(JpgSegment&& Right) noexcept = delete;
		virtual ~JpgSegment() { };

		JpgSegment& operator=(const JpgSegment& Source) = delete;
		JpgSegment& operator=(JpgSegment&& Right) noexcept = delete;

		virtual const JpgMarker GetMarker() const = 0;
	};
}
#endif

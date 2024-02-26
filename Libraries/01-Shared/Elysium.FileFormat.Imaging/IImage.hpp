/*
===========================================================================

Copyright (C) 2020 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_FILEFORMAT_IMAGING_IIMAGE
#define ELYSIUM_FILEFORMAT_IMAGING_IIMAGE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_FILEFORMAT_IMAGING_API
#include "API.hpp"
#endif

namespace Elysium::FileFormat::Imaging
{
	class ELYSIUM_FILEFORMAT_IMAGING_API IImage
	{
	public:
		virtual ~IImage() { };
		
		virtual const Elysium::Core::uint8_t GetDimensions() const = 0;

		virtual const Elysium::Core::uint16_t GetSize(const Elysium::Core::uint8_t Axis) const = 0;

		virtual const Elysium::Core::uint16_t GetWidth() const = 0;
		virtual const Elysium::Core::uint16_t GetHeight() const = 0;
	};
}
#endif

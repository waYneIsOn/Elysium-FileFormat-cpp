/*
===========================================================================

Copyright (C) 2020 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_FILEFORMAT_IMAGING_JPG_JPGREADER
#define ELYSIUM_FILEFORMAT_IMAGING_JPG_JPGREADER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAYOFBYTE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/ArrayOfByte.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.IO/Stream.hpp"
#endif

#ifndef ELYSIUM_FILEFORMAT_IMAGING_API
#include "../Elysium.FileFormat.Imaging/API.hpp"
#endif

#ifndef ELYSIUM_FILEFORMAT_IMAGING_JPG_JPGMARKER
#include "JpgMarker.hpp"
#endif

namespace Elysium::FileFormat::Imaging::Jpg
{
	class ELYSIUM_FILEFORMAT_IMAGING_API JpgReader final
	{
	public:
		JpgReader(Elysium::Core::IO::Stream& InputStream);
		JpgReader(const JpgReader& Source) = delete;
		JpgReader(JpgReader&& Right) noexcept = delete;
		~JpgReader();

		JpgReader& operator=(const JpgReader& Source) = delete;
		JpgReader& operator=(JpgReader&& Right) noexcept = delete;

		const bool ReadSegment();
	private:
		static const size_t DefaultBufferSize = 4096;

		Elysium::Core::IO::Stream& _InputStream;
		Elysium::Core::Collections::Template::Array<Elysium::Core::byte> _Buffer;

		const JpgMarker ReadJpgMarker();
		const Elysium::Core::uint16_t ReadUInt16();

		void PopulateBuffer(const size_t Count);

		const bool ReadSegmentAPP0();
		const bool ReadSegmentDQT();
		const bool ReadSegmentSOF0();
		const bool ReadSegmentDHT();
		const bool ReadSegmentSOS();
	};
}
#endif

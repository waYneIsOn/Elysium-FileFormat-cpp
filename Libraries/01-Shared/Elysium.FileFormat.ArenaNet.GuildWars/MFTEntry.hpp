/*
===========================================================================

Copyright (C) 2020 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_DAT_MFTENTRY
#define ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_DAT_MFTENTRY

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

namespace Elysium::FileFormat::ArenaNet::GuildWars::DAT
{
	class ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_API MFTEntry
	{
	public:
		const bool Validate() const noexcept;
	public:
		Elysium::Core::uint64_t _Offset;
		Elysium::Core::uint32_t _Size;
		Elysium::Core::uint16_t _Compression;
		Elysium::Core::uint8_t _Unknown1;	// content?
		Elysium::Core::uint8_t _Unknown2;	// content type?

		Elysium::Core::uint32_t _Unknown3;
		Elysium::Core::uint32_t _CRCChecksum;
	public:
		const bool GetIsCompressed() const;

		const bool GetHasContent() const;
	};
}
#endif

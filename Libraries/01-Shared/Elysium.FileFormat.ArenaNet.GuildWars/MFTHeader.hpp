/*
===========================================================================

Copyright (C) 2020 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_DAT_MFTHEADER
#define ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_DAT_MFTHEADER

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
	class ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_API MFTHeader
	{
	public:
		const bool Validate() const noexcept;
	public:
		unsigned char _Magic[3];
		Elysium::Core::uint8_t _Type;

		// Mustn't use Elysium::Core::uint64_t as this will pad MFTHeader to 32 byte in size!
		Elysium::Core::uint32_t _Unknown1;
		Elysium::Core::uint32_t _Unknown2;

		Elysium::Core::uint32_t _EntryCount;
		Elysium::Core::uint32_t _Unknown3;
		Elysium::Core::uint32_t _UnusedCRCChecksum;
	private:
		inline const static char _ExpectedMagic[3] = { 'M', 'f', 't' };
		inline const static Elysium::Core::uint8_t _ExpectedType = 0x1A;
		inline const static Elysium::Core::uint8_t _ExpectedUnknown3 = 0x00;
		inline const static Elysium::Core::uint8_t _ExpectedCRCChecksum = 0x00;
	};
}
#endif

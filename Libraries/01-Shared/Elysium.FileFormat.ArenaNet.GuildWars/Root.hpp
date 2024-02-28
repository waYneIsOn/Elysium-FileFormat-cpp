/*
===========================================================================

Copyright (C) 2020 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_DAT_ROOT
#define ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_DAT_ROOT

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
	class ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_API Root
	{
	public:
		const bool Validate() const noexcept;
	public:
		Elysium::Core::uint8_t _Type;
		unsigned char _Magic[2];
		Elysium::Core::uint8_t _Version;

		Elysium::Core::uint32_t _HeaderSize;
		Elysium::Core::uint32_t _BlockSize;
		Elysium::Core::uint32_t _CRCChecksum;

		Elysium::Core::uint64_t _MftOffset;
		Elysium::Core::uint32_t _MftSize;
		Elysium::Core::uint32_t _Unknown3;
	private:
		inline const static Elysium::Core::uint8_t _ExpectedType = 0x33;
		inline const static char _ExpectedMagic[2] = { 'A', 'N' };
		inline const static Elysium::Core::uint8_t _ExpectedVersion = 0x1A;
		inline const static Elysium::Core::uint32_t _ExpectedHeaderSize = 0x20;
		inline const static Elysium::Core::uint32_t _ExpectedBlockSize = 0x200;
		inline const static Elysium::Core::uint32_t _ExpectedUnknown = 0x00;
	};
}
#endif

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
	private:
		Elysium::Core::uint32_t _FileTypeAndVersion;
		Elysium::Core::uint32_t _HeaderSize;
		Elysium::Core::uint32_t _BlockSize;
		Elysium::Core::uint32_t _CRC;
		Elysium::Core::uint64_t _MftOffset;
		Elysium::Core::uint64_t _MftSize;
		Elysium::Core::uint64_t _Unknown;
	};
}
#endif

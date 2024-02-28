/*
===========================================================================

Copyright (C) 2020 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_DAT_ENTRYCONTENT
#define ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_DAT_ENTRYCONTENT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_BYTE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Byte.hpp"
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Vector.hpp"
#endif

#ifndef ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_DAT_FILETYPE
#include "FileType.hpp"
#endif

namespace Elysium::FileFormat::ArenaNet::GuildWars::DAT
{
	class ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_API EntryContent
	{
	public:
		FileType _Type = FileType::Unknown;
		Elysium::Core::uint32_t _UncompressedSize = 0;
		Elysium::Core::uint32_t _Hash = 0;

		Elysium::Core::Template::Container::Vector<Elysium::Core::byte> _Data = Elysium::Core::Template::Container::Vector<Elysium::Core::byte>();
	};
}
#endif

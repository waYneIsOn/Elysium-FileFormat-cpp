/*
===========================================================================

Copyright (C) 2020 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_DAT_DATSTREAM
#define ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_DAT_DATSTREAM

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILESTREAM
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Vector.hpp"
#endif

#ifndef ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_DAT_MFTHEADER
#include "MFTHeader.hpp"
#endif

#ifndef ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_DAT_MFTENTRY
#include "MFTEntry.hpp"
#endif

#ifndef ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_DAT_ROOT
#include "Root.hpp"
#endif

namespace Elysium::FileFormat::ArenaNet::GuildWars::DAT
{
	class ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_API DATStream
	{
	public:
		DATStream(const Elysium::Core::Utf8String& Path);

		DATStream(const DATStream& Source) = delete;

		DATStream(DATStream&& Right) noexcept = delete;

		~DATStream();
	public:
		DATStream& operator=(const DATStream& Source) = delete;

		DATStream& operator=(DATStream&& Right) noexcept = delete;
	public:
		const Elysium::Core::Template::Container::Vector<MFTEntry>& GetEntries() const;
	public:
		const bool ReadRootBlock();

		const bool ReadMainFileTableHeader();

		const bool ReadMainFileTableEntries();
	public:
		const bool ReadEntryContent(const MFTEntry& Entry, const Elysium::Core::uint32_t Index);
	private:
		void Read(Elysium::Core::byte* Buffer, const Elysium::Core::size BufferSize);
	private:
		Elysium::Core::IO::FileStream _SourceStream;

		Root _RootBlock;
		MFTHeader _MainFileTableHeader;
		Elysium::Core::Template::Container::Vector<MFTEntry> _Entries;
	};
}
#endif

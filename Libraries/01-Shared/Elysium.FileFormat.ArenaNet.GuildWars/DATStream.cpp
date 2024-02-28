#include "DATStream.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Move.hpp"
#endif

#ifndef ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_DAT_FILETYPE
#include "FileType.hpp"
#endif

Elysium::FileFormat::ArenaNet::GuildWars::DAT::DATStream::DATStream(const Elysium::Core::Utf8String& Path)
	: _SourceStream(Path, Elysium::Core::IO::FileMode::Open, Elysium::Core::IO::FileAccess::Read, Elysium::Core::IO::FileShare::None, 4096,
		Elysium::Core::IO::FileOptions::None),
	_RootBlock(), _MainFileTableHeader(), _Entries()
{ }

Elysium::FileFormat::ArenaNet::GuildWars::DAT::DATStream::~DATStream()
{ }

const Elysium::Core::Template::Container::Vector<Elysium::FileFormat::ArenaNet::GuildWars::DAT::MFTEntry>& Elysium::FileFormat::ArenaNet::GuildWars::DAT::DATStream::GetEntries() const
{
	return _Entries;
}

const bool Elysium::FileFormat::ArenaNet::GuildWars::DAT::DATStream::ReadRootBlock()
{	
	Elysium::Core::byte* Buffer = reinterpret_cast<Elysium::Core::byte*>(reinterpret_cast<void*>(&_RootBlock));
	const Elysium::Core::size BufferSize = sizeof(_RootBlock);

	Read(Buffer, BufferSize);

	return _RootBlock.Validate();
}

const bool Elysium::FileFormat::ArenaNet::GuildWars::DAT::DATStream::ReadMainFileTableHeader()
{
	// 00 - Main File Table Header
	_SourceStream.SetPosition(_RootBlock._MftOffset);

	Elysium::Core::byte* Buffer = reinterpret_cast<Elysium::Core::byte*>(reinterpret_cast<void*>(&_MainFileTableHeader));
	const Elysium::Core::size BufferSize = sizeof(_MainFileTableHeader);

	Read(Buffer, BufferSize);

	return _MainFileTableHeader.Validate();
}

const bool Elysium::FileFormat::ArenaNet::GuildWars::DAT::DATStream::ReadMainFileTableEntries()
{
	_SourceStream.SetPosition(_RootBlock._MftOffset + sizeof(MFTHeader));

	MFTEntry Entry = MFTEntry();
	Elysium::Core::byte* Buffer = reinterpret_cast<Elysium::Core::byte*>(reinterpret_cast<void*>(&Entry));
	const Elysium::Core::size BufferSize = sizeof(Entry);

	// 01 - reference to root table
	Read(Buffer, BufferSize);

	Entry.Validate(); 

	if (Entry._Offset != 0x00)
	{
		return false;
	}

	if (Entry._Size != sizeof(Root))
	{
		return false;
	}

	if (Entry._Compression != 0x00)
	{	// is compressed
		return false;
	}

	if (Entry._Unknown1 != 0x03)
	{	// has content
		return false;
	}

	if (Entry._Unknown2 != 0x00)
	{	// ?
		return false;
	}

	_Entries.PushBack(Elysium::Core::Template::Functional::Move(Entry));

	// 02 - unknown
	Read(Buffer, BufferSize);

	Entry.Validate();

	if (Entry._Compression != 0x00)
	{	
		return false;
	}

	if (Entry._Unknown1 != 0x03)
	{
		return false;
	}

	if (Entry._Unknown2 != 0x00)
	{
		return false;
	}

	_Entries.PushBack(Elysium::Core::Template::Functional::Move(Entry));

	// 03 - reference to main file table information (before MFTHeader -> stored in _RootBlock)
	Read(Buffer, BufferSize);

	Entry.Validate();

	if (Entry._Offset != _RootBlock._MftOffset)
	{
		return false;
	}

	if (Entry._Size != _RootBlock._MftSize)
	{
		return false;
	}

	if (Entry._Compression != 0x00)
	{
		return false;
	}

	if (Entry._Unknown1 != 0x03)
	{
		return false;
	}

	if (Entry._Unknown2 != 0x00)
	{
		return false;
	}

	_Entries.PushBack(Elysium::Core::Template::Functional::Move(Entry));

	// 04 - 15 - empty blocks (placeholder for something that wasn't used?)
	for (Elysium::Core::uint8_t i = 0; i < 12; ++i)
	{
		Read(Buffer, BufferSize);

		Entry.Validate();

		if (Entry._Offset != 0x00)
		{
			return false;
		}

		if (Entry._Size != 0x00)
		{
			return false;
		}

		if (Entry._Compression != 0x00)
		{
			return false;
		}

		if (Entry._Unknown1 != 0x00)
		{
			return false;
		}

		if (Entry._Unknown2 != 0x00)
		{
			return false;
		}

		_Entries.PushBack(Elysium::Core::Template::Functional::Move(Entry));
	}

	// 16 - looks like EULA (have to check whether it's always at #16)
	// ...

	// 16 - start of "actual" blocks
	for (Elysium::Core::uint32_t i = 0; i < _MainFileTableHeader._EntryCount - 15; ++i)
	{
		Read(Buffer, BufferSize);

		Entry.Validate();
		
		_Entries.PushBack(Elysium::Core::Template::Functional::Move(Entry));
	}

	// just to make sure for now
	if (_Entries.GetLength() != _MainFileTableHeader._EntryCount)
	{
		return false;
	}

	return true;
}

const Elysium::FileFormat::ArenaNet::GuildWars::DAT::EntryContent Elysium::FileFormat::ArenaNet::GuildWars::DAT::DATStream::GetEntryContent(const MFTEntry& Entry)
{
	EntryContent Content = EntryContent();

	// handle root block reference specifically [entry 0]
	if (Entry._Size != 0x00 && Entry._Offset == 0x00)
	{
		Content._Type = Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::RootBlockReference;
		Content._UncompressedSize = Entry._Size;

		return Content;
	}

	// handle hashlist specifically [entry 1]
	{
		// @ToDo
	}

	// handle main file table header reference specifically [entry 2]
	if(Entry._Offset == _RootBlock._MftOffset)
	{
		if (Entry._Size != _RootBlock._MftSize)
		{	// @ToDo: throw specific exception (this should never happen if the file isn't corrupted!)
			throw 1;
		}

		Content._Type = Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::MainFileTableHeaderReference;
		Content._UncompressedSize = Entry._Size;

		return Content;
	}

	// handle entries without content specifically [entries 3 - 14] (seems like only reserved entries have no content)
	if (Entry._Size == 0x00)
	{
		if (Entry._Compression || Entry._Unknown1 || Entry._Unknown2)
		{	// @ToDo: throw specific exception (this should never happen if the file isn't corrupted!)
			throw 1;
		}

		Content._Type = Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::ReservedEntry;

		return Content;
	}

	// handle all remaining cases
	Elysium::Core::byte* UncompressedData = nullptr;

	if (Entry.GetIsCompressed())
	{
		Elysium::Core::byte* CompressedData = new Elysium::Core::byte[Entry._Size];

		_SourceStream.SetPosition(Entry._Offset);
		_SourceStream.Read(CompressedData, Entry._Size);

		// @ToDo: uncompress into UncompressedData

		delete[] CompressedData;



		Content._Type = Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::CompressedValueToBeDeleted;

		return Content;
	}
	else
	{
		UncompressedData = new Elysium::Core::byte[Entry._Size];

		_SourceStream.SetPosition(Entry._Offset);
		_SourceStream.Read(UncompressedData, Entry._Size);

		Content._UncompressedSize = Entry._Size;
	}

	if (UncompressedData == nullptr)
	{	// @ToDo: throw specific exception (this should never happen if the file isn't corrupted!)
		throw 1;
	}

	const Elysium::Core::uint32_t* UnderlyingFileType = reinterpret_cast<Elysium::Core::uint32_t*>(&UncompressedData[0]);
	Content._Type = static_cast<Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType>(*UnderlyingFileType);
	Content._Data.Reserve(Entry._Size);
	Content._Data.PushBackRange(UncompressedData, Entry._Size);

	delete[] UncompressedData;

	return Content;
}

const bool Elysium::FileFormat::ArenaNet::GuildWars::DAT::DATStream::PerformTypeTests(const MFTEntry& Entry, const Elysium::Core::uint32_t Index)
{
	// skip entry referencing root block
	if (Entry._Size != 0x00 && Entry._Offset == 0x00)
	{
		return true;
	}

	// skip any entries without content
	if (Entry._Size == 0x00)
	{
		return true;
	}
	
	Elysium::Core::byte* UncompressedData = nullptr;

	// read uncompressed data
	if (Entry.GetIsCompressed())
	{
		Elysium::Core::byte* CompressedData = new Elysium::Core::byte[Entry._Size];

		_SourceStream.SetPosition(Entry._Offset);
		_SourceStream.Read(CompressedData, Entry._Size);

		// @ToDo: uncompress into UncompressedData

		delete[] CompressedData;
	}
	else
	{
		UncompressedData = new Elysium::Core::byte[Entry._Size];

		_SourceStream.SetPosition(Entry._Offset);
		_SourceStream.Read(UncompressedData, Entry._Size);
	}

	// process uncompressed data
	if (UncompressedData == nullptr)
	{
		return false;
	}

	const Elysium::Core::uint32_t* UnderlyingFileType = reinterpret_cast<Elysium::Core::uint32_t*>(&UncompressedData[0]);

	const Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType FileType =
		static_cast<Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType>(*UnderlyingFileType);

	if (FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::RootBlockReference &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::ArenaNetTexture &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::ArenaNetFileFormat &&

		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Entry2Hashlist &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::MainFileTableHeaderReference &&

		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown1 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown2 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown3 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown4 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown5 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown6 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown7 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown8 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown9 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown10 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown11 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown12 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown13 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown14 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown15 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown16 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown17 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown18 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown19 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown20 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown21 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown22 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown23 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown24 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown25 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown26 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown27 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown28 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown29 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown30 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown31 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown32 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown33 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown34 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown35 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown36 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown37 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown38 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown39 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown40 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown41 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown42 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown43 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown44 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown45 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown46 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown47 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown48 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown49 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown50 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown51 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown52 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown53 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown54 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown55 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown56 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown57 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown58 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown59 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown60 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown61 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown62 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown63 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown64 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown65 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown66 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown67 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown68 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown69 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown70 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown71 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown72 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown73 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown74 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown75 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown76 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown77 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown78 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown79 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown80 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown81 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown82 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown83 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown84 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown85 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown86 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown87 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown88 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown89 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown90 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown91 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown92 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown93 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown94 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown95 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown96 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown97 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown98 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown99 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown100 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown101 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown102 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown103 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown104 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown105 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown106 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown107 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown108 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown109 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown110 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown111 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown112 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown113 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown114 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown115 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown116 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown117 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown118 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown119 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown120 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown121 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown122 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown123 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown124 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown125 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown126 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown127 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown128 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown129 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown130 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown131 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown132 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown133 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown134 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown135 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown136 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown137 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown138 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown139 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown140 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown141 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown142 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown143 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown144 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown145 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown146 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown147 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown148 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown149 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown150 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown151 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown152 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown153 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown154 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown155 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown156 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown157 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown158 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown159 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown160 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown161 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown162 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown163 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown164 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown165 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown166 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown167 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown168 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown169 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown170 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown171 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown172 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown173 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown174 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown175 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown176 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown177 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown178 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown179 &&
		FileType != Elysium::FileFormat::ArenaNet::GuildWars::DAT::FileType::Unknown180
		)
	{
		bool bla = false;
	}
	
	delete[] UncompressedData;
	
	return true;
}

void Elysium::FileFormat::ArenaNet::GuildWars::DAT::DATStream::Read(Elysium::Core::byte* Buffer, const Elysium::Core::size BufferSize)
{
	Elysium::Core::size TotalBytesRead = 0;

	do
	{
		const Elysium::Core::size BytesRead = _SourceStream.Read(&Buffer[TotalBytesRead], BufferSize - TotalBytesRead);
		TotalBytesRead += BytesRead;
	} while (TotalBytesRead != BufferSize);
}

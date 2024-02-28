#include "DATStream.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Move.hpp"
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

	if (Entry._Content != 0x03)
	{	// has content
		return false;
	}

	if (Entry._ContentType != 0x00)
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

	if (Entry._Content != 0x03)
	{
		return false;
	}

	if (Entry._ContentType != 0x00)
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

	if (Entry._Content != 0x03)
	{
		return false;
	}

	if (Entry._ContentType != 0x00)
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

		if (Entry._Content != 0x00)
		{
			return false;
		}

		if (Entry._ContentType != 0x00)
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

const bool Elysium::FileFormat::ArenaNet::GuildWars::DAT::DATStream::ReadEntryContent(const MFTEntry& Entry)
{
	/*
	// ...
	if (Entry.GetIsCompressed())
	{
		Elysium::Core::byte* Data = new Elysium::Core::byte[Entry._Size];

		_SourceStream.SetPosition(Entry._Offset);
		_SourceStream.Read(Data, Entry._Size);

		Elysium::Core::uint32_t* i = (Elysium::Core::uint32_t*)&Data[0];
		Elysium::Core::uint32_t* k = (Elysium::Core::uint32_t*)&Data[1];

		delete[] Data;
	}
	else
	{
		Elysium::Core::byte* Data = new Elysium::Core::byte[Entry._Size];

		_SourceStream.SetPosition(Entry._Offset);
		_SourceStream.Read(Data, Entry._Size);

		Elysium::Core::uint32_t* i = (Elysium::Core::uint32_t*)&Data[0];
		Elysium::Core::uint32_t* k = (Elysium::Core::uint32_t*)&Data[1];

		delete[] Data;
	}
	*/
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

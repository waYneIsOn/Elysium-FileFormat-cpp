#include "MFTEntry.hpp"

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CHECKSUM_CRC32
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Security/Crc32.hpp"
#endif

const bool Elysium::FileFormat::ArenaNet::GuildWars::DAT::MFTEntry::Validate() const noexcept
{
	if (_Offset != 0x00)
	{

	}

	if (_Size != 0x00)
	{

	}

	if (_Compression != 0x00)
	{

	}
	
	if (_CRCChecksum != 0x00)
	{
	}
	
	if (_Content != 0x00)
	{

	}

	if (_ContentType != 0x00)
	{

	}

	if (_Unknown != 0x00)
	{

	}

	// some entries have unused checksums
	if (_CRCChecksum != 0x00)
	{
		// this doesn't work here!
		// maybe the checksum applies to the actual bytes stored at _Offset and their _Size
		/*
		const Elysium::Core::byte* Data = reinterpret_cast<const Elysium::Core::byte*>(reinterpret_cast<const void*>(this));
		const Elysium::Core::uint32_t CalculatedCRCChecksum = Elysium::Core::Security::Cryptography::Checksum::Crc32::CalculateBytewise(Data,
			0x18);
		if (_CRCChecksum != CalculatedCRCChecksum)
		{
			return false;
		}
		*/
	}

    return true;
}

const bool Elysium::FileFormat::ArenaNet::GuildWars::DAT::MFTEntry::GetIsCompressed() const
{
	if (_Compression != 0x00 && _Compression != 0x08)
	{	// @ToDo: not encountered any other values in dat-file so far. this might be something "new"
		throw 1;
	}

	return _Compression != 0x00;
}

const bool Elysium::FileFormat::ArenaNet::GuildWars::DAT::MFTEntry::GetHasContent() const
{
	if (_Content != 0x00 && _Content != 0x01 && _Content != 0x03)
	{	// @ToDo: not encountered any other values in dat-file so far. this might be something "new"
		throw 1;
	}

	return _Content != 0x00;
}


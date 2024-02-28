#include "Root.hpp"

#ifndef ELYSIUM_CORE_SECURITY_CRYPTOGRAPHY_CHECKSUM_CRC32
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Security/Crc32.hpp"
#endif

const bool Elysium::FileFormat::ArenaNet::GuildWars::DAT::Root::Validate() const noexcept
{
	if (_Type != _ExpectedType)
	{
		return false;
	}

	if (_Magic[0] != _ExpectedMagic[0] || _Magic[1] != _ExpectedMagic[1])
	{
		return false;
	}

	if (_Version != _ExpectedVersion)
	{
		return false;
	}
	
	if (_HeaderSize != _ExpectedHeaderSize)
	{
		return false;
	}

	if (_BlockSize != _ExpectedBlockSize)
	{
		return false;
	}

	const Elysium::Core::byte* Data = reinterpret_cast<const Elysium::Core::byte*>(reinterpret_cast<const void*>(this));
	const Elysium::Core::uint32_t CalculatedCRCChecksum = Elysium::Core::Security::Cryptography::Checksum::Crc32::CalculateBytewise(Data, 
		12);	// sizeof(_Type) + sizeof(_Magic) + sizeof(_Version) + sizeof(_HeaderSize) + sizeof(_BlockSize)
	if (_CRCChecksum != CalculatedCRCChecksum)
	{
		return false;
	}

	if (_Unknown != 0x00)
	{
		return false;
	}

	return true;
}

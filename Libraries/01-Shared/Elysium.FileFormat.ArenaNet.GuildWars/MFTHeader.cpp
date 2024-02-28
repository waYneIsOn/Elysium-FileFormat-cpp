#include "MFTHeader.hpp"

const bool Elysium::FileFormat::ArenaNet::GuildWars::DAT::MFTHeader::Validate() const noexcept
{
	if (_Magic[0] != _ExpectedMagic[0] || _Magic[1] != _ExpectedMagic[1] || _Magic[2] != _ExpectedMagic[2])
	{
		return false;
	}

	if (_Type != _ExpectedType)
	{
		return false;
	}

#if DEBUG
	if (_Unknown1 != 0x00)
	{ }

	if(_EntryCount != 0x00)
	{ }
#endif
	if (_Unknown3 != _ExpectedUnknown3)
	{
		return false;
	}

	if (_UnusedCRCChecksum != _ExpectedCRCChecksum)
	{
		return false;
	}

	return true;
}

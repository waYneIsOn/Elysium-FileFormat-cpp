#include "DATStream.hpp"

Elysium::FileFormat::ArenaNet::GuildWars::DAT::DATStream::DATStream(const Elysium::Core::Utf8String& Path)
	: _Stream(Path, Elysium::Core::IO::FileMode::Open, Elysium::Core::IO::FileAccess::Read, Elysium::Core::IO::FileShare::None, 4096,
		Elysium::Core::IO::FileOptions::Asynchronous)
{ }

Elysium::FileFormat::ArenaNet::GuildWars::DAT::DATStream::~DATStream()
{ }

void Elysium::FileFormat::ArenaNet::GuildWars::DAT::DATStream::ReadRoot()
{
}

#include "JpgReader.hpp"

#ifndef ELYSIUM_CORE_ARGUMENTOUTOFRANGEEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/ArgumentOutOfRangeException.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_NOTIMPLEMENTEDEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/NotImplementedException.hpp"
#endif

#ifndef ELYSIUM_FILEFORMAT_IMAGING_JPG_JPGHUFFMANTABLETYPE
#include "JpgHuffmanTableType.hpp"
#endif

Elysium::FileFormat::Imaging::Jpg::JpgReader::JpgReader(Elysium::Core::IO::Stream& InputStream)
	: _InputStream(InputStream), _Buffer(DefaultBufferSize)
{ }
Elysium::FileFormat::Imaging::Jpg::JpgReader::~JpgReader()
{ }

const bool Elysium::FileFormat::Imaging::Jpg::JpgReader::ReadSegment()
{
	JpgMarker Marker = ReadJpgMarker();
	switch (Marker)
	{
	case JpgMarker::SOI:
		return true;	// SOI-segments contain no further data
	case JpgMarker::APP0:
		return ReadSegmentAPP0();
	case JpgMarker::DQT:
		return ReadSegmentDQT();
	case JpgMarker::SOF0:
		return ReadSegmentSOF0();
	case JpgMarker::DHT:
		return ReadSegmentDHT();
	case JpgMarker::SOS:
		return ReadSegmentSOS();
	case JpgMarker::EOI:	// EOI-segments contain no further data. since we're at the end of the image (and possibly stream) we can stop reading.
		return false;
	default:
		throw Elysium::Core::NotImplementedException(u8"Unhandled JpgMarker.");
	}
}

const Elysium::FileFormat::Imaging::Jpg::JpgMarker Elysium::FileFormat::Imaging::Jpg::JpgReader::ReadJpgMarker()
{
	PopulateBuffer(2);

	// each segment starts with 0xFF, 0x??
	if (_Buffer[0] != 0xFF)
	{	// ToDo: throw specific exception
		throw 1;
	}

	return static_cast<JpgMarker>(_Buffer[1]);
}

const Elysium::Core::uint16_t Elysium::FileFormat::Imaging::Jpg::JpgReader::ReadUInt16()
{
	PopulateBuffer(2);
	return Elysium::Core::uint16_t(_Buffer[1] | _Buffer[0] << 8);
}

void Elysium::FileFormat::Imaging::Jpg::JpgReader::PopulateBuffer(const size_t Count)
{
	if (Count > _Buffer.GetLength())
	{
		throw Elysium::Core::ArgumentOutOfRangeException(u8"Count");
	}

	if (Count == 1)
	{	// circumvent the more complex code down below
		Elysium::Core::byte Byte = _InputStream.ReadByte();
		_Buffer[0] = Byte;
		return;
	}

	size_t TotalBytesRead = 0;
	do
	{
		const size_t BytesRead = _InputStream.Read(&_Buffer[TotalBytesRead], Count - TotalBytesRead);
		if (BytesRead == 0)
		{
			break;
		}
		TotalBytesRead += BytesRead;
	} while (TotalBytesRead < Count);
}

const bool Elysium::FileFormat::Imaging::Jpg::JpgReader::ReadSegmentAPP0()
{
	const Elysium::Core::uint16_t SegmentLength = ReadUInt16() - 2;
	if (SegmentLength < 14)
	{	// ToDo: throw specific exception
		throw 1;
	}
	PopulateBuffer(SegmentLength);

	// JFIF (ToDo: could also be "JFXX\x00" for JFIF)
	if (_Buffer[0] != 0x4A || _Buffer[1] != 0x46 || _Buffer[2] != 0x49 || _Buffer[3] != 0x46 || _Buffer[4] != 0x00)
	{	// ToDo: throw specific exception
		throw 1;
	}

	// version (major and minor)
	if (_Buffer[5] != 0x01)
	{	// ToDo: throw specific exception
		throw 1;
	}
	if (_Buffer[6] > 2)
	{	// ToDo: throw specific exception
		throw 1;
	}

	// densities
	switch (_Buffer[7])
	{
	case 0:	// no density but aspect ratio
		break;
	case 1:	// dots/inch 
		break;
	case 2:	// dots/cm 
		break;
	default:// ToDo: throw specific exception
		throw 1;
	}
	const Elysium::Core::uint16_t DensityX = Elysium::Core::uint16_t(_Buffer[9] | _Buffer[8] << 8);
	if (DensityX == 0)
	{	// ToDo: throw specific exception
		throw 1;
	}
	const Elysium::Core::uint16_t DensityY = Elysium::Core::uint16_t(_Buffer[11] | _Buffer[10] << 8);
	if (DensityY == 0)
	{	// ToDo: throw specific exception
		throw 1;
	}

	// thumbnail
	const Elysium::Core::uint8_t ThumbnailWidth = _Buffer[12];
	const Elysium::Core::uint8_t ThumbnailHeight = _Buffer[13];
	if (ThumbnailWidth != 0 && ThumbnailHeight != 0)
	{
		const size_t ThumbnailBytes = static_cast<size_t>(ThumbnailWidth) * ThumbnailHeight * 3;
		if (ThumbnailBytes != SegmentLength - 14)
		{	// ToDo: throw specific exception
			throw 1;
		}
		// ToDo: read thumbnail bitmap from buffer
	}

	return true;
}

const bool Elysium::FileFormat::Imaging::Jpg::JpgReader::ReadSegmentDQT()
{
	const Elysium::Core::uint16_t SegmentLength = ReadUInt16() - 2;
	PopulateBuffer(SegmentLength);

	// QT info
	const Elysium::Core::uint8_t NumberOfQT = _Buffer[0] >> 5;
	if (NumberOfQT > 3)
	{	// ToDo: throw specific exception
		throw 1;
	}
	const Elysium::Core::uint8_t PrecisionOfQT = (_Buffer[0] >> 1) & 0x0F;
	const Elysium::Core::uint8_t Bitness = (_Buffer[0] & 0x03) == 0 ? 8 : 16;

	// bytes
	const Elysium::Core::uint32_t DataLength = 64 * (PrecisionOfQT + 1);
	if (DataLength != SegmentLength - 1)
	{	// ToDo: throw specific exception
		throw 1;
	}

	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Data = Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(DataLength);
	std::memcpy(&Data[0], &_Buffer[1], DataLength);

	return true;
}

const bool Elysium::FileFormat::Imaging::Jpg::JpgReader::ReadSegmentSOF0()
{
	const Elysium::Core::uint16_t SegmentLength = ReadUInt16() - 2;
	PopulateBuffer(SegmentLength);

	const Elysium::Core::uint8_t DataPrecision = _Buffer[0];
	const Elysium::Core::uint16_t ImageWidth = Elysium::Core::uint16_t(_Buffer[2] | _Buffer[1] << 8);
	const Elysium::Core::uint16_t ImageHeight = Elysium::Core::uint16_t(_Buffer[4] | _Buffer[3] << 8);
	const Elysium::Core::uint8_t NumberOfComponents = _Buffer[5];

	for (Elysium::Core::uint8_t i = 0; i < NumberOfComponents; i++)
	{
		Elysium::Core::uint8_t ComponentId = _Buffer[6ui8 + (i * 3ui8)];
		Elysium::Core::uint8_t SamplingFactors = _Buffer[7ui8 + (i * 3ui8)];
		Elysium::Core::uint8_t QuantizationTableNumber = _Buffer[8ui8 + (i * 3ui8)];
	}

	return true;
}

const bool Elysium::FileFormat::Imaging::Jpg::JpgReader::ReadSegmentDHT()
{
	const Elysium::Core::uint16_t SegmentLength = ReadUInt16() - 2;
	PopulateBuffer(SegmentLength);

	const Elysium::Core::uint8_t HTInfo = _Buffer[0] >> 5;
	const JpgHuffmanTableType HTType = static_cast<JpgHuffmanTableType>((_Buffer[0] >> 4) & 0x01);
	const Elysium::Core::uint8_t Unused = _Buffer[0] & 0x07;
	if (Unused != 0)
	{	// apparently this is ok as other values appear in jpgs created with mspaint?
		
		// ToDo: throw specific exception
		//throw 1;
	}

	Elysium::Core::uint8_t NumberOfSymbolsPerLevel[16];
	Elysium::Core::UInt8 SumOfNumberOfSymbolsPerLevel = 0;
	for (Elysium::Core::uint8_t i = 0; i < 16; i++)
	{
		NumberOfSymbolsPerLevel[i] = _Buffer[1ui8 + i];
		SumOfNumberOfSymbolsPerLevel += NumberOfSymbolsPerLevel[i];
	}

	if (SumOfNumberOfSymbolsPerLevel != SegmentLength - 17)
	{	// ToDo: throw specific exception
		throw 1;
	}
	/*
	// not necessary as long as I use Elysium::Core::UInt8 and OverflowException will be thrown.
	if (SumOfNumberOfSymbolsPerLevel > 255ui8)
	{	// ToDo: throw specific exception
		throw 1;
	}
	*/

	Elysium::Core::uint8_t CastSumOfNumberOfSymbolsPerLevel = static_cast<Elysium::Core::uint8_t>(SumOfNumberOfSymbolsPerLevel);
	for (Elysium::Core::uint8_t i = 0; i < CastSumOfNumberOfSymbolsPerLevel; i++)
	{
		Elysium::Core::uint8_t Symbol = _Buffer[17ui8 + i];
	}

	return true;
}

const bool Elysium::FileFormat::Imaging::Jpg::JpgReader::ReadSegmentSOS()
{
	const Elysium::Core::uint16_t SegmentLength = ReadUInt16() - 2;
	PopulateBuffer(SegmentLength);

	const Elysium::Core::uint8_t NumberOfComponents = _Buffer[0];
	if (NumberOfComponents < 1 || NumberOfComponents > 4)
	{	// ToDo: throw specific exception
		throw 1;
	}

	if (SegmentLength != 2 * NumberOfComponents + 4)
	{	// ToDo: throw specific exception
		throw 1;
	}

	for (Elysium::Core::uint8_t i = 0; i < NumberOfComponents; i++)
	{
		Elysium::Core::byte ComponentId = _Buffer[1ui8 + (i * 2ui8)];
		Elysium::Core::byte HuffmanTableIndex = _Buffer[2ui8 + (i * 2ui8)];
	}

	// these bytes are ignorable and can be skipped
	PopulateBuffer(3);

	// image data





	// read line by line
	const Elysium::Core::uint16_t WIDTH = 128;
	const Elysium::Core::uint16_t HEIGHT = 128;
	const Elysium::Core::uint16_t COMPONENTS = 3;	// rgb
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> ScanlineBuffer = 
		Elysium::Core::Collections::Template::Array<Elysium::Core::byte>(COMPONENTS * WIDTH);
	for (Elysium::Core::uint16_t i = 0; i < HEIGHT; i++)
	{

	}





	PopulateBuffer(255);
	/*
	const size_t Pos1 = _InputStream.GetPosition();

	_InputStream.SetPosition(_InputStream.GetLength() - 2);
	const size_t Pos2 = _InputStream.GetPosition();

	const size_t DataLength = Pos2 - Pos1;
	*/

	return true;
}

/*
===========================================================================

Copyright (C) 2020 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_DAT_FILETYPE
#define ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_DAT_FILETYPE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_FILEFORMAT_ARENANET_GUILDWARS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_SYSTEM_OPERATINGSYSTEM
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/OperatingSystem.hpp"
#endif

namespace Elysium::FileFormat::ArenaNet::GuildWars::DAT
{
#if defined ELYSIUM_CORE_OS_WINDOWS
	enum class FileType : Elysium::Core::Template::System::uint32_t
#elif defined ELYSIUM_CORE_OS_ANDROID
	enum class FileType
#else
#error "undefined os"
#endif
	{
		Unknown = 0,

		RootBlockReference = 441336115,

		Entry2Hashlist = 381384,

		MainFileTableHeaderReference = 443835981,

		ReservedEntry = 1,




		ArenaNetTexture = 1480938561,

		ArenaNetFileFormat = 1634625126,







		Unknown31 = 6029055,

		Unknown49 = 307237804,
		Unknown80 = 307237805,
		Unknown81 = 307237797,
		Unknown127 = 307237800,
		Unknown128 = 307237795,
		
		Unknown1 = 3078714045,
		Unknown53 = 3759603714,


		Unknown2 = 33627558,
		Unknown3 = 33627506,
		Unknown4 = 33626880,
		Unknown5 = 33624320,
		Unknown6 = 33627392,
		Unknown7 = 33623338,
		Unknown8 = 33623906,
		Unknown9 = 33622825,
		Unknown10 = 33623143,
		Unknown11 = 33623141,
		Unknown12 = 33622828,
		Unknown13 = 33627420,
		Unknown14 = 33627488,
		Unknown15 = 33622556,
		Unknown16 = 33623324,
		Unknown17 = 33621510,
		Unknown18 = 33624928,
		Unknown19 = 33624944,
		Unknown20 = 33624672,
		Unknown21 = 33626370,
		Unknown22 = 33627489,
		Unknown23 = 33627507,
		Unknown24 = 33622305,
		Unknown25 = 33623670,
		Unknown26 = 33623837,
		Unknown27 = 33622898,
		Unknown28 = 33625346,
		Unknown29 = 33627421,
		Unknown30 = 33624092,
		Unknown32 = 33626652,
		Unknown33 = 33626626,
		Unknown34 = 33627497,
		Unknown35 = 33626908,
		Unknown36 = 33627584,
		Unknown37 = 33627570,
		Unknown38 = 33626480,
		Unknown39 = 33627552,
		Unknown40 = 33627513,
		Unknown41 = 33627520,
		Unknown42 = 33627628,
		Unknown43 = 33624366,
		Unknown44 = 33625722,
		Unknown45 = 33624250,
		Unknown46 = 33625961,
		Unknown47 = 33624578,
		Unknown48 = 33625128,
		Unknown50 = 33625858,
		Unknown51 = 33626112,
		Unknown52 = 33624694,
		Unknown54 = 33626396,
		Unknown55 = 33626471,
		Unknown56 = 33623325,
		Unknown57 = 33622451,
		Unknown58 = 33622650,
		Unknown59 = 33622278,
		Unknown60 = 33622569,
		Unknown61 = 33623068,
		Unknown62 = 33622812,
		Unknown63 = 33624832,
		Unknown64 = 33622786,
		Unknown65 = 33623808,
		Unknown66 = 33623069,
		Unknown67 = 33623145,
		Unknown68 = 33622059,
		Unknown69 = 33622633,
		Unknown70 = 33622313,
		Unknown71 = 33625856,
		Unknown72 = 33622813,
		Unknown73 = 33622534,
		Unknown74 = 33622557,
		Unknown75 = 33622889,
		Unknown76 = 33622375,
		Unknown77 = 33622119,
		Unknown78 = 33622784,
		Unknown79 = 33623042,
		Unknown82 = 33621746,
		Unknown83 = 33624070,
		Unknown84 = 33621844,
		Unknown85 = 33621087,
		Unknown86 = 33621702,
		Unknown87 = 33621129,
		Unknown88 = 33621014,
		Unknown89 = 33622356,
		Unknown90 = 33621134,
		Unknown91 = 33621232,
		Unknown92 = 33622227,
		Unknown93 = 33621443,
		Unknown94 = 33623204,
		Unknown95 = 33621646,
		Unknown96 = 33621525,
		Unknown97 = 33621483,
		Unknown98 = 33621513,
		Unknown99 = 33623931,
		Unknown100 = 33623602,
		Unknown101 = 33621958,
		Unknown102 = 33621753,
		Unknown103 = 33622246,
		Unknown104 = 33622470,
		Unknown105 = 33620867,
		Unknown106 = 33621690,
		Unknown107 = 33622436,
		Unknown108 = 33621268,
		Unknown109 = 33621212,
		Unknown110 = 33621491,
		Unknown111 = 33621522,
		Unknown112 = 33624006,
		Unknown113 = 33626030,
		Unknown114 = 33622230,
		Unknown115 = 33622482,
		Unknown116 = 33621700,
		Unknown117 = 33627504,
		Unknown118 = 33625443,
		Unknown119 = 33625714,
		Unknown120 = 33627235,
		Unknown121 = 33622377,
		Unknown122 = 33622528,
		Unknown123 = 33624106,
		Unknown124 = 33623693,
		Unknown125 = 33622724,
		Unknown126 = 33621332,
		Unknown129 = 33624499,
		Unknown130 = 33624156,
		Unknown131 = 33621264,
		Unknown132 = 33627398,
		Unknown133 = 33624435,
		Unknown134 = 33623854,
		Unknown135 = 33623695,
		Unknown136 = 33621926,
		Unknown137 = 33625540,
		Unknown138 = 33621609,
		Unknown139 = 33627602,
		Unknown140 = 33627585,
		Unknown141 = 33627394,
		Unknown142 = 33621849,
		Unknown143 = 33626368,
		Unknown144 = 33626468,
		Unknown145 = 33621816,
		Unknown146 = 33620997,
		Unknown147 = 33624201,
		Unknown148 = 33622833,
		Unknown149 = 33621489,
		Unknown150 = 33623745,
		Unknown151 = 33621457,
		Unknown152 = 33620939,
		Unknown153 = 33621538,
		Unknown154 = 33621583,
		Unknown155 = 33621298,
		Unknown156 = 33621715,
		Unknown157 = 33621682,
		Unknown158 = 33622195,
		Unknown159 = 33621971,
		Unknown160 = 33621727,
		Unknown161 = 33621202,
		Unknown162 = 33621074,
		Unknown163 = 33622468,
		Unknown164 = 33621970,
		Unknown165 = 33621446,
		Unknown166 = 33624064,
		Unknown167 = 33623296,
		Unknown168 = 33623749,
		Unknown169 = 33625465,
		Unknown170 = 33624707,
		Unknown171 = 33624935,
		Unknown172 = 33623314,
		Unknown173 = 33623761,
		Unknown174 = 33621747,
		Unknown175 = 33621234,
		Unknown176 = 33625088,
		Unknown177 = 33626739,
		Unknown178 = 33627437,
		Unknown179 = 33624425,
		Unknown180 = 33624531,
	};
}
#endif

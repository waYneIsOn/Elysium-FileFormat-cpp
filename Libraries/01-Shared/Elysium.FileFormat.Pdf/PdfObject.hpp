/*
===========================================================================

Copyright (C) 2020 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_FILEFORMAT_PDF_PDFOBJECT
#define ELYSIUM_FILEFORMAT_PDF_PDFOBJECT

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_FILEFORMAT_PDF_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Integer.hpp"
#endif

namespace Elysium::FileFormat::PDF
{
	class ELYSIUM_FILEFORMAT_PDF_API PdfObject
	{
	public:
		PdfObject(const PdfObject& Source) = delete;
		PdfObject(PdfObject&& Right) noexcept = delete;
		virtual ~PdfObject();

		PdfObject& operator=(const PdfObject& Source) = delete;
		PdfObject& operator=(PdfObject&& Right) noexcept = delete;
	protected:
		PdfObject();
	};
}
#endif

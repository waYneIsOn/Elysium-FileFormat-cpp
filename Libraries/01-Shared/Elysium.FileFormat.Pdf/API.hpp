/*
===========================================================================

Copyright (C) 2020 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_FILEFORMAT_PDF_API

#ifdef _MSC_VER
#pragma once
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(_WINDOWS)
#ifdef ELYSIUMFILEFORMATPDF_EXPORTS
#define ELYSIUM_FILEFORMAT_PDF_API __declspec(dllexport)
#else
#define ELYSIUM_FILEFORMAT_PDF_API __declspec(dllimport)
#endif
#elif defined(__ANDROID__)
#define EXPORT
#else
#error "undefined os"
#endif

#endif

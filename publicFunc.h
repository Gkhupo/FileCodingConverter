#ifndef _PUBLIC_FUNC_
#define _PUBLIC_FUNC_

#include <QString>
#include <QTime>
#include "public.h"

#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
#include <QDebug>
#endif

#ifndef _NOW_TIME
#define _NOW_TIME	(QTime::currentTime().toString("hh:mm:ss.zzz"))
#endif // !_NOW_TIME

#ifndef _FILE_NAME
#define _FILE_NAME	(QString(__FILE__).split('\\').last())
#endif // !_FILE_NAME

#ifndef _LINE_FIX
#define _LINE_FIX	(QString::number(__LINE__).rightJustified(4, '0'))
#endif // !_LINE_FIX

#ifndef _PREFIX
#ifdef _DEBUG
#define _PREFIX	(QString("[%1][%2 %3]").arg(_NOW_TIME).arg(_FILE_NAME).arg(_LINE_FIX))
#else
#define _PREFIX	(QString("[%1]").arg(_NOW_TIME))
#endif
#endif

//#define _NO_COLOR

#ifndef _DEBUG_DEFINE
#define _DEBUG_DEFINE

#ifdef _NO_COLOR

#define _INFO		(qDebug().noquote() << (QString("%1 [INFO]").arg(_PREFIX)))
#define _ERROR		(qDebug().noquote() << (QString("%1 [ERROR]").arg(_PREFIX)))
#define _SUCCESS	(qDebug().noquote() << (QString("%1 [SUCCESS]").arg(_PREFIX)))
#define _WARRING	(qDebug().noquote() << (QString("%1 [WARRING]").arg(_PREFIX)))
#define _SIGN(x)	(qDebug().noquote() << (QString("%1 [%2]").arg(_PREFIX).arg(x)))

#else

#define _INFO		(qDebug().noquote() << (QString("%1 [INFO]").arg(_PREFIX)))
#define _ERROR		(qDebug().noquote() << (QString("%1\033[31m [ERROR]\033[0m").arg(_PREFIX)))
#define _SUCCESS	(qDebug().noquote() << (QString("%1\033[32m [SUCCESS]\033[0m").arg(_PREFIX)))
#define _WARRING	(qDebug().noquote() << (QString("%1\033[33m [WARRING]\033[0m").arg(_PREFIX)))
#define _SIGN(x)	(qDebug().noquote() << (QString("%1\033[36m [%2]\033[0m").arg(_PREFIX).arg(x)))

#endif // _NO_COLOR

#endif // !_DEBUG_DEFINE


namespace pubc
{
	template <typename T>
	constexpr static bool isDiget()
	{
		return std::is_integral_v<std::remove_reference_t<std::remove_pointer_t<T>>> ||
			std::is_floating_point_v<std::remove_reference_t<std::remove_pointer_t<T>>>;
	}

	template <typename T>
	constexpr static bool isDiget([[maybe_unused]] T value)
	{
		return isDiget<T>();
	}

	template <typename T>
	static inline QString numToHexStr(const T& num)
	{
		Q_ASSERT(isDiget(num));
		return QString::number(num, 16).rightJustified(sizeof(num) * 2, '0').toUpper();
	}

	static inline QString byteArrayToHexStr(const QByteArray& byteArray, quint64 size = 0)
	{
		QStringList hexCharList;
		if (!byteArray.isEmpty())
		{
			size = (size && (size <= byteArray.size())) ? size : byteArray.size();
			for (uint i = 0; i < size; i++)
			{
				hexCharList << QString::number(static_cast<uchar>(byteArray[i]), 16).toUpper().rightJustified(2, '0');
			}
		}
		return hexCharList.join(" ");
	}

	template <typename T>
	static inline QString numListToHexStr(const QVector<T> numList, quint64 size = 0)
	{
		Q_ASSERT(isDiget(T));
		QStringList hexCharList;
		if (!numList.isEmpty())
		{
			size = (size && (size <= numList.size())) ? size : numList.size();
			for (uint i = 0; i < size; i++)
			{
				hexCharList << pubc::numToHexStr(numList[i]);
			}
		}
		return hexCharList.join(" ");
	}

	//交换字节序
	template <typename T>
	[[nodiscard]] static T bitConversion(const T& num)
	{
		assert(pubc::isDiget(num));
		T value = 0x00;
		if (num != 0)
		{
			uint8_t tmp = 0x00;
			T mov = 0xFF;
			const uint8_t bitWidth = 8;
			for (int i = 0; i < sizeof(T); ++i)
			{
				value <<= bitWidth;
				tmp = (num & mov) >> (i * bitWidth);
				mov <<= bitWidth;
				value |= tmp;
			}
		}
		return value;
	}
};

#endif // !_PUBLIC_FUNC_

#pragma once

#include <QDateTime>

namespace pub
{
	const QString date_time_format = "yyyy/MM/dd HH:mm:ss";


	/**
	 * @brief 文件保存属性
	 */
	typedef enum _FILE_SAVE_STATUS
	{
		//未编辑
		UNEDITED = 0x00,
		//已编辑未保存
		EDITED_UNSAVED,
		//已保存
		SAVED,
	}FileSaveStatus;

	/**
	 * @brief 文件状态
	 */
	typedef struct _FILE_STATUS
	{
		//是否选择
		bool checked = false;
		//文件名
		QString fileName;
		//当前编码
		QString currentCoding;
		//目标编码
		QString targetCoding;
		//文件保存状态
		FileSaveStatus fileSaveStatus = FileSaveStatus::UNEDITED;
	}FileStatus;

	/**
	 * @brief 文件信息
	 */
	struct _FILE_INFO
	{
		//文件名
		QString fileName;
		//文件路径
		QString path;
		//文件大小
		uint size = 0;
		//最后更改日期
		QDateTime lastUpdatedDate;
	};

};
/*
* Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/


#include <string.h>
#include <sys/stat.h>
#include <media_util_private.h>
#include <media_info_private.h>
#include <media_content_type.h>


int _media_util_get_store_type_by_path(const char *path, int *storage_type)
{
	if(STRING_VALID(path))
	{
		if(strncmp(path, MEDIA_CONTENT_PATH_PHONE, strlen(MEDIA_CONTENT_PATH_PHONE)) == 0)
		{
			*storage_type = MEDIA_CONTENT_STORAGE_INTERNAL;
		}
		else if(strncmp (path, MEDIA_CONTENT_PATH_MMC, strlen(MEDIA_CONTENT_PATH_MMC)) == 0)
		{
			*storage_type = MEDIA_CONTENT_STORAGE_EXTERNAL;
		}
	}
	else
	{
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	return MEDIA_CONTENT_ERROR_NONE;
}

int _media_util_get_file_dir_modified_time(const char *path)
{
	struct stat statbuf;
	int fd = 0;
	int err = 0;

	if(!STRING_VALID(path))
	{
		media_content_error("INVALID_PARAMETER(0x%08x)", MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}

	memset(&statbuf, 0, sizeof(struct stat));
	fd = stat(path, &statbuf);
	if(fd == -1) {
		err = errno;
		media_content_error("stat(%s) fails. err[%d]", path, err);
		return -1;
	}

	return statbuf.st_mtime;
}

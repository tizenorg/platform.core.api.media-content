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


#include <tet_api.h>
#include <media_content.h>
#include <stdlib.h>

static void startup(void);
static void cleanup(void);

void (*tet_startup)(void) = startup;
void (*tet_cleanup)(void) = cleanup;

static void utc_media_content_connect_p(void);
static void utc_media_content_disconnect_p(void);



struct tet_testlist tet_testlist[] = {
	{ utc_media_content_connect_p, 1 },
	{ utc_media_content_disconnect_p, 1 },
	{ NULL, 0 },
};


static void startup(void)
{
	/* start of TC */
	tet_printf("\n TC start");
	
}


static void cleanup(void)
{
	/* end of TC */
	tet_printf("\n TC end");
}


/**
 * @brief Positive test case of utc_media_content_connect_p()
 */
static void utc_media_content_connect_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_content_connect();

	dts_check_eq("utc_media_content_connect_p", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to connect database");
}


/**
 * @brief Positive test case of utc_media_content_disconnect_p()
 */
static void utc_media_content_disconnect_p(void)
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	ret = media_content_disconnect();

	dts_check_eq("utc_content_imageinfo_destroy", ret, MEDIA_CONTENT_ERROR_NONE, "Failed to disconnect database");
}

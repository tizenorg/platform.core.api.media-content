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

#ifndef __TIZEN_MEDIA_CONTENT_H__
#define __TIZEN_MEDIA_CONTENT_H__

#include <media_audio.h>
#include <media_content_type.h>
#include <media_filter.h>
#include <media_folder.h>
#include <media_image.h>
#include <media_info.h>
#include <media_tag.h>
#include <media_video.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup CAPI_MEDIA_CONTENT_MODULE
 * @{
 */


/**
 * @brief Connects to the media content service.
 * @details Any media content related function call should be invoked after this function call.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_DB_FAILED DB operation failed 
 * @post media_content_disconnect()
 * @see media_content_disconnect()
 *
 */
int media_content_connect(void);

/**
 * @brief Disconnects from the media content service.
 * @details This function closes connection to the media content service. Any further media content related operation
 * cannot be performed after this function is called.
 *
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_DB_FAILED DB operation failed 
 * @pre media_content_connect()
 * @see media_content_connect()
 *
 */
int media_content_disconnect(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TIZEN_MEDIA_CONTENT_H__ */



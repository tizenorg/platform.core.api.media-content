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



#ifndef __TIZEN_MEDIA_CONTENT_INTERNAL_H__
#define __TIZEN_MEDIA_CONTENT_INTERNAL_H__

#include <media_content_type.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @internal
 * @file media_content_internal.h
 * @brief This file contains API on main functional operations with storage that are related to media resources in the media database. \n
 *        Operations include: inserting a new storage in media to the media database, removing storage from database, \n
 */

/**
* @internal
* @brief Insert media storage to database.
* @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
*
* @remarks You must release @a storage using media_storage_destroy().
*
* @privlevel platform
* @privilege %http://tizen.org/privilege/content.write
*
* @param[in] storage_name The storage name to insert to database
* @param[in] storage_path The storage path to insert to database
* @param[in] storage_account The storage account to insert to database
* @param[in] storage_type The storage type to insert to database
* @param[out] storage The media storage handle
*
* @return @c 0 on success,
*           otherwise a negative error value
*
* @retval #MEDIA_CONTENT_ERROR_NONE Successful
* @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
* @retval #MEDIA_CONTENT_ERROR_DB_FAILED		 DB operation failed
* @retval #MEDIA_CONTENT_ERROR_PERMISSION_DENIED Permission denied
*
* @see media_storage_delete_from_db()
*/
int media_storage_insert_to_db(const char *storage_name, const char *storage_path, const char *storage_account, media_content_storage_e storage_type, media_storage_h *storage);

/**
* @internal
* @brief Deletes the database for media storage.
* @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
*
* @privlevel platform
* @privilege %http://tizen.org/privilege/content.write
*
* @param[in] storage_id The storage ID to delete from database
*
* @return @c 0 on success,
*           otherwise a negative error value
*
* @retval #MEDIA_CONTENT_ERROR_NONE Successful
* @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
* @retval #MEDIA_CONTENT_ERROR_DB_FAILED		 DB operation failed
* @retval #MEDIA_CONTENT_ERROR_PERMISSION_DENIED Permission denied
*
* @see media_storage_insert_to_db()
*/
int media_storage_delete_from_db(const char *storage_id);

/**
 * @brief Gets the storage account of media storage.
 * @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
 *
 * @remarks You must release @a storage_account using free().
 *
 * @param[in]  storage The media storage handle
 * @param[out] storage_account  The storage account of the media storage
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 *
 * @retval #MEDIA_CONTENT_ERROR_NONE              Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY     Out of memory
 */
int media_storage_get_storage_account(media_storage_h storage, char **storage_account);

/**
* @internal
* @brief Sets the MIME type of media info handle.
* @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
*
* @param[in] media The media info handle
* @param[in] mime_type The MIME type of the media info
*
* @return @c 0 on success,
*           otherwise a negative error value
*
* @retval #MEDIA_CONTENT_ERROR_NONE Successful
* @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
* @retval #MEDIA_CONTENT_ERROR_DB_FAILED		 DB operation failed
* @retval #MEDIA_CONTENT_ERROR_PERMISSION_DENIED Permission denied
*
* @post media_info_insert_to_db_with_data()
*/
int media_info_set_mime_type(media_info_h media, const char *mime_type);

/**
* @internal
* @brief Sets the thumbnail path of media info handle.
* @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
*
* @param[in] media The media info handle
* @param[in] thumbnail_path The thumbnail path of media info handle
*
* @return @c 0 on success,
*           otherwise a negative error value
*
* @retval #MEDIA_CONTENT_ERROR_NONE Successful
* @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
* @retval #MEDIA_CONTENT_ERROR_DB_FAILED		 DB operation failed
* @retval #MEDIA_CONTENT_ERROR_PERMISSION_DENIED Permission denied
*
* @post media_info_insert_to_db_with_data()
*/
int media_info_set_thumbnail_path(media_info_h media, const char *thumbnail_path);

/**
* @internal
* @brief Sets the size of media info handle.
* @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
*
* @param[in] media The media info handle
* @param[in] size The size of media info handle
*
* @return @c 0 on success,
*           otherwise a negative error value
*
* @retval #MEDIA_CONTENT_ERROR_NONE Successful
* @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
* @retval #MEDIA_CONTENT_ERROR_DB_FAILED		 DB operation failed
* @retval #MEDIA_CONTENT_ERROR_PERMISSION_DENIED Permission denied
*
* @post media_info_insert_to_db_with_data()
*/
int media_info_set_size(media_info_h media, unsigned long long size);

/**
* @internal
* @brief Sets the modified time of media info handle.
* @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
*
* @param[in] media The media info handle
* @param[in] modified_time The modified time of media info handle
*
* @return @c 0 on success,
*           otherwise a negative error value
*
* @retval #MEDIA_CONTENT_ERROR_NONE Successful
* @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
* @retval #MEDIA_CONTENT_ERROR_DB_FAILED		 DB operation failed
* @retval #MEDIA_CONTENT_ERROR_PERMISSION_DENIED Permission denied
*
* @post media_info_insert_to_db_with_data()
*/
int media_info_set_modified_time(media_info_h media, time_t modified_time);

/**
* @internal
* @brief Sets the media type of media info handle.
* @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
*
* @param[in] media The media info handle
* @param[in] type The media type of media info handle
*
* @return @c 0 on success,
*           otherwise a negative error value
*
* @retval #MEDIA_CONTENT_ERROR_NONE Successful
* @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
* @retval #MEDIA_CONTENT_ERROR_DB_FAILED		 DB operation failed
* @retval #MEDIA_CONTENT_ERROR_PERMISSION_DENIED Permission denied
*
* @post media_info_insert_to_db_with_data()
*/
int media_info_set_media_type(media_info_h media, media_content_type_e type);

/**
* @internal
* @brief Sets the duration of media info handle.
* @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
*
* @param[in] media The media info handle
* @param[in] duration The duration of media info handle
*
* @return @c 0 on success,
*           otherwise a negative error value
*
* @retval #MEDIA_CONTENT_ERROR_NONE Successful
* @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
* @retval #MEDIA_CONTENT_ERROR_DB_FAILED		 DB operation failed
* @retval #MEDIA_CONTENT_ERROR_PERMISSION_DENIED Permission denied
*
* @post media_info_insert_to_db_with_data()
*/
int media_info_set_duration(media_info_h media, int duration);

/**
* @internal
* @brief Sets the width of media info handle.
* @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
*
* @param[in] media The media info handle
* @param[in] width The width of media info handle
*
* @return @c 0 on success,
*           otherwise a negative error value
*
* @retval #MEDIA_CONTENT_ERROR_NONE Successful
* @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
* @retval #MEDIA_CONTENT_ERROR_DB_FAILED		 DB operation failed
* @retval #MEDIA_CONTENT_ERROR_PERMISSION_DENIED Permission denied
*
* @post media_info_insert_to_db_with_data()
*/
int media_info_set_width(media_info_h media, int width);

/**
* @internal
* @brief Sets the height of media info handle.
* @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
*
* @param[in] media The media info handle
* @param[in] height The height of media info handle
*
* @return @c 0 on success,
*           otherwise a negative error value
*
* @retval #MEDIA_CONTENT_ERROR_NONE Successful
* @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
* @retval #MEDIA_CONTENT_ERROR_DB_FAILED		 DB operation failed
* @retval #MEDIA_CONTENT_ERROR_PERMISSION_DENIED Permission denied
*
* @post media_info_insert_to_db_with_data()
*/
int media_info_set_height(media_info_h media, int height);

/**
* @internal
* @brief Sets the storage type of media info handle.
* @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
*
* @param[in] media The media info handle
* @param[in] storage_type The storage type of media info handle
*
* @return @c 0 on success,
*           otherwise a negative error value
*
* @retval #MEDIA_CONTENT_ERROR_NONE Successful
* @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
* @retval #MEDIA_CONTENT_ERROR_DB_FAILED		 DB operation failed
* @retval #MEDIA_CONTENT_ERROR_PERMISSION_DENIED Permission denied
*
* @post media_info_insert_to_db_with_data()
*/
int media_info_set_storage_type(media_info_h media, media_content_storage_e storage_type);

/**
* @internal
* @brief Sets the storage type of media info handle.
* @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
*
* @param[in] media The media info handle
* @param[in] storage_id The storage id of media info handle
*
* @return @c 0 on success,
*           otherwise a negative error value
*
* @retval #MEDIA_CONTENT_ERROR_NONE Successful
* @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
* @retval #MEDIA_CONTENT_ERROR_DB_FAILED		 DB operation failed
* @retval #MEDIA_CONTENT_ERROR_PERMISSION_DENIED Permission denied
*
* @post media_info_insert_to_db_with_data()
*/
int media_info_set_storage_id(media_info_h media, const char *storage_id);

/**
 * @brief Gets the storage scan status of media storage.
 * @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
 *
 * @param[in]  storage The media storage handle
 * @param[out] scan_status  The storage type of the media storage
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 *
 * @retval #MEDIA_CONTENT_ERROR_NONE              Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 */
int media_storage_get_scan_status(const char *storage_uuid, media_storage_scan_status_e *scan_status);

/**
 * @brief Subscribes notifications of the media DB change.
 * @details This function subscribes notifications of the media DB change which are published by the media server or other apps.
 *          media_content_db_update_cb() function will be called when notification of the media DB change is subscribed.
 *
 * @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
 *
 * @param[in] callback  The callback to be invoked when the scanning is finished
 * @param[in] user_data The user data to be passed to the callback function
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 *
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_INVALID_OPERATION Invalid operation
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY     Out of memory
 * @retval #MEDIA_CONTENT_ERROR_PERMISSION_DENIED Permission denied
 *
 * @see media_content_db_update_cb()
 * @see media_content_unset_db_updated_cb_v2()
 */
int media_content_set_db_updated_cb_v2(media_content_noti_h *noti_handle, media_content_db_update_cb callback, void *user_data);


/**
 * @brief Unsubscribes notifications of the media DB change.
 * @details This function unsubscribes notifications of the media DB change which are published by the media server or other apps.
 *
 * @since_tizen @if MOBILE 2.4 @elseif WEARABLE 3.0 @endif
 *
 * @return @c 0 on success,
 *         otherwise a negative error value
 *
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_PERMISSION_DENIED Permission denied
 *
 * @pre media_content_set_db_updated_cb_v2()
 *
 * @see media_content_set_db_updated_cb_v2()
 */
int media_content_unset_db_updated_cb_v2(media_content_noti_h noti_handle);

typedef enum {
	MEDIA_CONTENT_SCAN_PARTIAL_COMPLETE		= 2,
	MEDIA_CONTENT_SCAN_COMPLETE			= 3,
	MEDIA_CONTENT_EXTRACT_COMPLETE		= 4,
} media_content_complete_phase_e;

typedef void (*media_scan_completed_cb_v2)(media_content_error_e error, media_content_complete_phase_e complete_phase, void * user_data);

typedef struct _media_content_scan_cb_data_v2 {
	media_scan_completed_cb_v2 callback;
	void *user_data;
} media_content_scan_cb_data_v2;

int media_content_scan_folder_v2(const char *path, bool is_recursive, media_scan_completed_cb_v2 callback, void *user_data);

#ifdef _USE_SENIOR_MODE
int media_info_insert_to_db_with_contact_data(const char *path, const char* contact, const char* app_data, media_info_h *info);
int media_info_delete_contact_from_db(const char* contact, const char* storage_id);
int media_info_get_media_info_by_path_from_db(const char* path, media_info_h* media);
int media_info_delete_item(const char *media_id);
int media_info_get_contact(media_info_h media, char **contact);
int media_info_get_app_data(media_info_h media, char **app_data);
int media_info_set_contact(media_info_h media, const char *contact);
int media_info_set_app_data(media_info_h media, const char *app_data);
#endif

#define PVR_DURATION				"PVR_DURATION"
#define PVR_TIME_ZONE				"PVR_TIME_ZONE"
#define PVR_PTC						"PVR_PTC"
#define PVR_MAJOR					"PVR_MAJOR"
#define PVR_MINOR					"PVR_MINOR"
#define PVR_CHANNEL_TYPE			"PVR_CHANNEL_TYPE"
#define PVR_CHANNEL_NAME			"PVR_CHANNEL_NAME"
#define PVR_CHANNEL_NUM				"PVR_CHANNEL_NUM"
#define PVR_PROGRAM_TITLE			"PVR_PROGRAM_TITLE"
#define PVR_PROGRAM_NUM			"PVR_PROGRAM_NUM"
#define PVR_PROGRAM_CRID			"PVR_PROGRAM_CRID"
#define PVR_GUIDANCE				"PVR_GUIDANCE"
#define PVR_SYNOPSIS				"PVR_SYNOPSIS"
#define PVR_GENRE					"PVR_GENRE"
#define PVR_LANGUAGE				"PVR_LANGUAGE"
#define PVR_EMBARGO_TIME			"PVR_EMBARGO_TIME"
#define PVR_EXPIRY_TIME				"PVR_EXPIRY_TIME"
#define PVR_START_TIME				"PVR_START_TIME"
#define PVR_PROGRAM_START_TIME	"PVR_PROGRAM_START_TIME"
#define PVR_PROGRAM_END_TIME		"PVR_PROGRAM_END_TIME"
#define PVR_PROGRAM_DATE			"PVR_PROGRAM_DATE"
#define PVR_PARENTAL_RATING		"PVR_PARENTAL_RATING"
#define PVR_TIMER_RECORD			"PVR_TIMER_RECORD"
#define PVR_SERIES_RECORD			"PVR_SERIES_RECORD"
#define PVR_HD						"PVR_HD"
#define PVR_SUBTITLE				"PVR_SUBTITLE"
#define PVR_TTX						"PVR_TTX"
#define PVR_AD						"PVR_AD"
#define PVR_HARDOF_HEARINGRADIO	"PVR_HARDOF_HEARINGRADIO"
#define PVR_DATA_SERVICE			"PVR_DATA_SERVICE"
#define PVR_CONTENT_LOCK			"PVR_CONTENT_LOCK"
#define PVR_CONTENT_WATCH		"PVR_CONTENT_WATCH"
#define PVR_CONTENT_HAS_AUDIO_ONLY	"PVR_CONTENT_HAS_AUDIO_ONLY"
#define PVR_CONTENT_IS_LOCAL_RECORD	"PVR_CONTENT_IS_LOCAL_RECORD"
#define PVR_CONTENT_RESOLUTION		"PVR_CONTENT_RESOLUTION"
#define PVR_CONTENT_ASPECTRATIO		"PVR_CONTENT_ASPECTRATIO"
#define PVR_MODIFIED_MONTH		"PVR_MODIFIED_MONTH"
#define PVR_MODIFIED_DATE		"PVR_MODIFIED_DATE"
#define PVR_SPORTS_TYPE			"PVR_SPORTS_TYPE"
#define PVR_GUIDANCE_LENGTH		"PVR_GUIDANCE_LENGTH"
#define PVR_TVMODE					"PVR_TVMODE"
#define PVR_PLAY_COUNT				"PVR_PLAY_COUNT"
#define PVR_PRIVATE_DATA			"PVR_PRIVATE_DATA"
#define UHD_CONTENT_TITLE		"UHD_CONTENT_TITLE"
#define UHD_RELEASE_DATE		"UHD_RELEASE_DATE"
#define UHD_SUB_TYPE			"UHD_SUB_TYPE"
#define UHD_FILE_NAME			"UHD_FILE_NAME"
#define UHD_FOLDER_ID			"UHD_FOLDER_ID"
#define UHD_PLAYED_COUNT		"UHD_PLAYED_COUNT"

typedef void *media_pvr_h;
typedef void *media_uhd_h;
typedef bool (*media_pvr_cb)(media_pvr_h pvr, void *user_data);
typedef bool (*media_uhd_cb)(media_uhd_h uhd, void *user_data);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /*__TIZEN_MEDIA_CONTENT_INTERNAL_H__*/

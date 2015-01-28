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


#ifndef __TIZEN_MEDIA_CONTENT_TYPE_H__
#define __TIZEN_MEDIA_CONTENT_TYPE_H__

#include <time.h>
#include <tizen.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#ifndef DEPRECATED_API
#define DEPRECATED_API __attribute__ ((deprecated))
#endif

/**
 * @file media_content_type.h
 * @brief This file contains API related to media-content enumerations for media data types, groups, orientations, \n
 *        classes of errors and definitions of media-data. \n
 *        Listed APIs are called when iterating over lists of album, group, bookmark and other media,  \n
 *        when media items and burst shot are inserted completely and when notification of media DB change is subscribed.
 */

/**
* @addtogroup CAPI_MEDIA_CONTENT_MODULE
 * @{
 */

/**
 * @ingroup CAPI_MEDIA_CONTENT_MODULE
 * @brief Enumeration for the media file format.
 */
typedef enum
{
    MEDIA_CONTENT_TYPE_IMAGE   = 0,  /**<The type of an image */
    MEDIA_CONTENT_TYPE_VIDEO   = 1,  /**<The type of a video */
    MEDIA_CONTENT_TYPE_SOUND   = 2,  /**<The type of sound */
    MEDIA_CONTENT_TYPE_MUSIC   = 3,  /**<The type of music */
    MEDIA_CONTENT_TYPE_OTHERS  = 4,  /**<The type of other */
} media_content_type_e;

/**
 * @ingroup CAPI_CONTENT_MEDIA_FOLDER_MODULE
 * @brief Enumeration for the storage type.
 * @details This information is used to establish where the folder is.
 */
typedef enum
{
    MEDIA_CONTENT_STORAGE_INTERNAL  = 0,  /**< The device's internal storage */
    MEDIA_CONTENT_STORAGE_EXTERNAL  = 1,  /**< The device's external storage */
} media_content_storage_e;

/**
 * @ingroup CAPI_MEDIA_CONTENT_MODULE
 * @brief Enumeration for media content DB update items.
 */
typedef enum {
    MEDIA_ITEM_FILE       = 0,              /**< File type, an item updated to DB */
    MEDIA_ITEM_DIRECTORY  = 1,              /**< Directory type, an item updated to DB */
} media_content_db_update_item_type_e;

/**
 * @ingroup CAPI_MEDIA_CONTENT_MODULE
 * @brief Enumeration for media content DB update types.
 */
typedef enum {
    MEDIA_CONTENT_INSERT  = 0,              /**< Insert, the type of DB update */
    MEDIA_CONTENT_DELETE  = 1,              /**< Delete, The type of DB update */
    MEDIA_CONTENT_UPDATE  = 2,              /**< Update, The type of DB update */
} media_content_db_update_type_e;

/**
 * @ingroup CAPI_CONTENT_MEDIA_INFO_MODULE
 * @brief Enumeration for orientation types.
 */
typedef enum {
    MEDIA_CONTENT_ORIENTATION_NOT_AVAILABLE  = 0,       /**< Not available*/
    MEDIA_CONTENT_ORIENTATION_NORMAL         = 1,       /**< Normal*/
    MEDIA_CONTENT_ORIENTATION_HFLIP          = 2,       /**< Flip horizontal*/
    MEDIA_CONTENT_ORIENTATION_ROT_180        = 3,       /**< Rotate 180 degrees*/
    MEDIA_CONTENT_ORIENTATION_VFLIP          = 4,       /**< Flip vertical*/
    MEDIA_CONTENT_ORIENTATION_TRANSPOSE      = 5,       /**< Transpose*/
    MEDIA_CONTENT_ORIENTATION_ROT_90         = 6,       /**< Rotate 90 degrees*/
    MEDIA_CONTENT_ORIENTATION_TRANSVERSE     = 7,       /**< Transverse*/
    MEDIA_CONTENT_ORIENTATION_ROT_270        = 8,       /**< Rotate 270 degrees*/
} media_content_orientation_e;

/**
 * @ingroup CAPI_MEDIA_CONTENT_MODULE
 * @brief Enumeration for ordering.
 */
typedef enum
{
    MEDIA_CONTENT_ORDER_ASC   = 0,      /**< Ascending order*/
    MEDIA_CONTENT_ORDER_DESC  = 1,      /**< Descending order*/
} media_content_order_e;

/**
 * @ingroup CAPI_MEDIA_CONTENT_MODULE
 * @brief Enumeration for collations.
 */
typedef enum
{
    MEDIA_CONTENT_COLLATE_DEFAULT   = 0,        /**< Default collation BINARY */
    MEDIA_CONTENT_COLLATE_NOCASE    = 1,        /**< Collation NOCASE, not case sensitive */
    MEDIA_CONTENT_COLLATE_RTRIM     = 2,        /**< Collation RTRIM, trailing space characters are ignored */
    MEDIA_CONTENT_COLLATE_LOCALIZED = 3,        /**< Collation LOCALIZATION, NOCASE also applied */
} media_content_collation_e;

#define MEDIA_CONTENT_ERROR_CLASS				TIZEN_ERROR_MEDIA_CONTENT

/**
 * @ingroup CAPI_MEDIA_CONTENT_MODULE
 * @brief Enumeration for a media content error.
 */
 typedef enum
{
    MEDIA_CONTENT_ERROR_NONE                    = TIZEN_ERROR_NONE,                    /**< Successful */
    MEDIA_CONTENT_ERROR_INVALID_PARAMETER       = TIZEN_ERROR_INVALID_PARAMETER,       /**< Invalid parameter */
    MEDIA_CONTENT_ERROR_OUT_OF_MEMORY           = TIZEN_ERROR_OUT_OF_MEMORY,           /**< Out of memory */
    MEDIA_CONTENT_ERROR_INVALID_OPERATION       = TIZEN_ERROR_INVALID_OPERATION,       /**< Invalid Operation */
    MEDIA_CONTENT_FILE_NO_SPACE_ON_DEVICE       = TIZEN_ERROR_FILE_NO_SPACE_ON_DEVICE, /**< No space left on device */
    MEDIA_CONTENT_ERROR_PERMISSION_DENIED		  = TIZEN_ERROR_PERMISSION_DENIED,		  /**< Permission denied */
    MEDIA_CONTENT_ERROR_DB_FAILED               = MEDIA_CONTENT_ERROR_CLASS | 0x01,    /**< DB operation failed */
    MEDIA_CONTENT_ERROR_DB_BUSY                 = MEDIA_CONTENT_ERROR_CLASS | 0x02,    /**< DB operation BUSY */
    MEDIA_CONTENT_ERROR_NETWORK                 = MEDIA_CONTENT_ERROR_CLASS | 0x03,    /**< Network Fail */
    MEDIA_CONTENT_ERROR_UNSUPPORTED_CONTENT     = MEDIA_CONTENT_ERROR_CLASS | 0x04,    /**< Unsupported Content */
} media_content_error_e;

/**
 * @ingroup CAPI_MEDIA_CONTENT_MODULE
 * @brief Enumeration for a media group.
 */
typedef enum {
    MEDIA_CONTENT_GROUP_DISPLAY_NAME = 0,    /**< Media group ID for display name */
    MEDIA_CONTENT_GROUP_TYPE,                /**< Media group ID for a media type */
    MEDIA_CONTENT_GROUP_MIME_TYPE,           /**< Media group ID for a mime type */
    MEDIA_CONTENT_GROUP_SIZE,                /**< Media group ID for content size */
    MEDIA_CONTENT_GROUP_ADDED_TIME,          /**< Media group ID for the added time */
    MEDIA_CONTENT_GROUP_MODIFIED_TIME,       /**< Media group ID for the modified time */
    MEDIA_CONTENT_GROUP_TITLE,               /**< Media group ID for a content title */
    MEDIA_CONTENT_GROUP_ARTIST,              /**< Media group ID for an artist*/
    MEDIA_CONTENT_GROUP_ALBUM_ARTIST,        /**< Media group ID for an album artist */
    MEDIA_CONTENT_GROUP_GENRE,               /**< Media group ID for a genre*/
    MEDIA_CONTENT_GROUP_COMPOSER,            /**< Media group ID for a composer*/
    MEDIA_CONTENT_GROUP_YEAR,                /**< Media group ID for a year*/
    MEDIA_CONTENT_GROUP_RECORDED_DATE,       /**< Media group ID for the recorded date*/
    MEDIA_CONTENT_GROUP_COPYRIGHT,           /**< Media group ID for the copyright*/
    MEDIA_CONTENT_GROUP_TRACK_NUM,           /**< Media group ID for a track number*/
    MEDIA_CONTENT_GROUP_DESCRIPTION,         /**< Media group ID for a description */
    MEDIA_CONTENT_GROUP_LONGITUDE,           /**< Media group ID for the longitude*/
    MEDIA_CONTENT_GROUP_LATITUDE,            /**< Media group ID for the latitude*/
    MEDIA_CONTENT_GROUP_ALTITUDE,            /**< Media group ID for the altitude*/
    MEDIA_CONTENT_GROUP_BURST_IMAGE,         /**< Media group ID for the burst shot*/
    MEDIA_CONTENT_GROUP_RATING,              /**< Media group ID for a rating*/
    MEDIA_CONTENT_GROUP_AUTHOR,              /**< Media group ID for an author*/
    MEDIA_CONTENT_GROUP_PROVIDER,            /**< Media group ID for a provider*/
    MEDIA_CONTENT_GROUP_CONTENT_NAME,        /**< Media group ID for the content name*/
    MEDIA_CONTENT_GROUP_CATEGORY,            /**< Media group ID for a category*/
    MEDIA_CONTENT_GROUP_LOCATION_TAG,        /**< Media group ID for a location tag*/
    MEDIA_CONTENT_GROUP_AGE_RATING,          /**< Media group ID for an age rating*/
    MEDIA_CONTENT_GROUP_KEYWORD,             /**< Media group ID for a keyword*/
    MEDIA_CONTENT_GROUP_WEATHER,             /**< Media group ID for the weather*/
    MEDIA_CONTENT_GROUP_MAX                  /**< Max count of the media group ID */
} media_group_e;

/**
 * @ingroup CAPI_CONTENT_MEDIA_INFO_MODULE
 * @brief The structure type for the Media info handle.
 */
typedef struct media_info_s *media_info_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_FOLDER_MODULE
 * @brief The structure type for the Media folder handle.
 */
typedef struct media_folder_s *media_folder_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_PLAYLIST_MODULE
 * @brief The structure type for the Media playlist handle.
 */
typedef struct media_playlist_s *media_playlist_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_TAG_MODULE
 * @brief The structure type for the Media tag handle.
 */
typedef struct media_tag_s *media_tag_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_BOOKMARK_MODULE
 * @brief The structure type for the Media bookmark handle.
 */
typedef struct media_bookmark_s *media_bookmark_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_ALBUM_MODULE
 * @brief The structure type for the Media album handle.
 */
typedef struct media_album_s *media_album_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_IMAGE_MODULE
 * @brief The structure type for the Image metadata handle.
 */
typedef struct image_meta_s *image_meta_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_VIDEO_META_MODULE
 * @brief The structure type for the Video metadata handle.
 */
typedef struct video_meta_s *video_meta_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_AUDIO_META_MODULE
 * @brief The structure type for the Audio metadata handle.
 */
typedef struct audio_meta_s *audio_meta_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_FILTER_MODULE
 * @brief The structure type for the Media filter handle.
 */
typedef struct filter_s *filter_h;

/**
 * @ingroup CAPI_MEDIA_CONTENT_MODULE
 * @brief Called when the media scanning is finished.
 *
 * @param[in] error     The error code
 * @param[in] user_data The user data passed from the foreach function
 *
 * @pre media_content_scan().
 *
 * @see media_content_scan()
 *
 */
typedef void (*media_scan_completed_cb)(media_content_error_e error, void * user_data);

/**
 * @ingroup CAPI_MEDIA_CONTENT_MODULE
 * @brief Called when the notification of the media DB change is subscribed.
 *
 * @param[in] error       The error code
 * @param[in] pid         The PID which publishes notification
 * @param[in] update_item The update item of notification
 * @param[in] update_type The update type of notification
 * @param[in] media_type  The type of the media content (#media_content_type_e)
 * @param[in] uuid        The UUID of media or directory, which is updated
 * @param[in] path        The path of the media or directory
 * @param[in] mime_type   The mime type of the media info
 * @param[in] user_data   The user data passed from the foreach function
 *
 * @pre media_content_db_update_subscribe().
 * @see media_content_db_update_subscribe()
 */
typedef void (*media_content_db_update_cb)(
                                    media_content_error_e error,
                                    int pid,
                                    media_content_db_update_item_type_e update_item,
                                    media_content_db_update_type_e update_type,
                                    media_content_type_e media_type,
                                    char *uuid,
                                    char *path,
                                    char *mime_type,
                                    void *user_data);


/**
 * @ingroup CAPI_CONTENT_MEDIA_INFO_MODULE
 * @brief Called for every available media info.
 *
 * @details Iterates over a list of media info.
 *
 * @remarks To use the @a media outside this function, copy the handle with media_info_clone() function.
 *
 * @param[in] media     The handle to the media info
 * @param[in] user_data The user data passed from the foreach function
 *
 * @return @c true to continue with the next iteration of the loop,
 *         otherwise @c false to break out of the loop
 *
 * @pre media_tag_foreach_media_from_db(), media_playlist_foreach_media_from_db(), media_genre_foreach_media_from_db(),
 *      media_info_foreach_media_from_db(), media_folder_foreach_media_from_db() will invoke this function.
 *
 * @see media_info_clone()
 * @see media_album_foreach_media_from_db()
 * @see media_playlist_foreach_media_from_db()
 * @see media_tag_foreach_media_from_db()
 * @see media_info_foreach_media_from_db()
 * @see media_folder_foreach_media_from_db()
 */
typedef bool (*media_info_cb)(media_info_h media, void *user_data);


/**
 * @ingroup CAPI_CONTENT_MEDIA_INFO_MODULE
 * @brief Called when media items are inserted completely.
 *
 * @param[in] media     The handle to the media info
 * @param[in] user_data The user data passed from the foreach function
 *
 * @pre media_info_insert_batch_to_db()
 *
 * @see media_info_insert_batch_to_db()
 */
typedef void (*media_insert_completed_cb)(media_content_error_e error, void * user_data);


/**
 * @ingroup CAPI_CONTENT_MEDIA_INFO_MODULE
 * @brief Called when the burst shot is inserted completely.
 *
 * @param[in] media     The handle to the media info
 * @param[in] user_data The user data passed from the foreach function
 *
 * @pre media_info_insert_burst_shot_to_db()
 *
 * @see media_info_insert_burst_shot_to_db()
 *
 */
typedef void (*media_insert_burst_shot_completed_cb)(media_content_error_e error, void * user_data);


/**
 * @ingroup CAPI_CONTENT_MEDIA_INFO_MODULE
 * @brief Called when creating a thumbnail image.
 *
 * @details This callback is called for completion of generating the thumbnail image.
 *
 * @param[in] error     The error code
 * @param[in] path      The path of the thumbnail which is generated
 * @param[in] user_data The user data passed from the foreach function
 *
 * @pre media_info_create_thumbnail()
 *
 * @see media_info_create_thumbnail()
 */
typedef void (*media_thumbnail_completed_cb)(media_content_error_e error, const char *path, void *user_data);


/**
 * @ingroup CAPI_CONTENT_MEDIA_FOLDER_MODULE
 * @brief Called for every available media folder.
 *
 * @details Iterates over a list of folders.
 *
 * @remarks To use the @a folder outside this function, copy the handle with the media_folder_clone() function.
 *
 * @param[in] folder    The handle to the media folder
 * @param[in] user_data The user data passed from the foreach function
 *
 * @return @c true to continue with the next iteration of the loop,
 *         otherwise @c false to break out of the loop
 *
 * @pre media_folder_foreach_folder_from_db() will invoke this function.
 * @see media_folder_clone()
 * @see media_folder_foreach_folder_from_db()
 */
typedef bool (*media_folder_cb)(media_folder_h folder, void *user_data);

/**
 * @ingroup CAPI_CONTENT_MEDIA_PLAYLIST_MODULE
 * @brief Called for every playlist in the obtained list of playlists.
 *
 * @details Iterates over a playlist list.
 *
 * @remarks To use the @a playlist outside this function, copy the handle with the media_playlist_clone() function.
 *
 * @param[in] playlist  The handle to the media playlist
 * @param[in] user_data The user data passed from the foreach function
 *
 * @return @c true to continue with the next iteration of the loop,
 *         otherwise @c false to break out of the loop
 *
 * @pre media_playlist_foreach_playlist_from_db() will invoke this function.
 *
 * @see media_playlist_clone()
 * @see media_playlist_foreach_playlist_from_db()
 */
typedef bool (*media_playlist_cb)(media_playlist_h playlist, void *user_data);

/**
 * @ingroup CAPI_CONTENT_MEDIA_PLAYLIST_MODULE
 * @brief Called for every media info with playlist member ID in the obtained list of media info.
 *
 * @details Iterates over playlist members.
 *
 * @remarks To use the @a media outside this function, copy the handle with the media_info_clone() function.
 *
 * @param[in] playlist_member_id The ID to member of the playlist
 * @param[in] media              The handle to the media info
 * @param[in] user_data          The user data passed from the foreach function
 *
 * @return @c true to continue with the next iteration of the loop,
 *         otherwise @c false to break out of the loop
 *
 * @pre media_playlist_foreach_media_from_db() will invoke this function.
 *
 * @see media_info_clone()
 * @see media_playlist_foreach_media_from_db()
 */
typedef bool(* playlist_member_cb)(int playlist_member_id, media_info_h media, void *user_data);

/**
 * @ingroup CAPI_CONTENT_MEDIA_TAG_MODULE
 * @brief Called for every tag in the obtained list of tags.
 *
 * @details Iterates over a list of tags.
 *
 * @remarks To use the @a tag outside this function, copy the handle with the media_tag_clone() function.
 *
 * @param[in] tag       The handle to the media tag
 * @param[in] user_data The user data passed from the foreach function
 *
 * @return @c true to continue with the next iteration of the loop,
 *         otherwise @c false to break out of the loop
 *
 * @pre media_tag_foreach_tag_from_db(), media_info_foreach_tag_from_db() will invoke this function.
 *
 * @see media_tag_clone()
 * @see media_tag_foreach_tag_from_db()
 * @see media_info_foreach_tag_from_db()
 */
typedef bool (*media_tag_cb)(media_tag_h tag, void *user_data);

/**
 * @ingroup CAPI_CONTENT_MEDIA_BOOKMARK_MODULE
 * @brief Called for every bookmark in the obtained list of bookmarks.
 *
 * @details Iterates over a bookmark list.
 *
 * @remarks To use the @a bookmark outside this function, copy the handle with the media_bookmark_clone() function.
 *
 * @param[in] bookmark  The handle to the video bookmark
 * @param[in] user_data The user data passed from the foreach function
 *
 * @return @c true to continue with the next iteration of the loop,
 *         otherwise @c false to break out of the loop
 *
 * @pre media_info_foreach_bookmark_from_db() will invoke this function.
 *
 * @see media_info_foreach_bookmark_from_db()
 */
typedef bool (*media_bookmark_cb)(media_bookmark_h bookmark, void *user_data);

/**
 * @ingroup CAPI_CONTENT_MEDIA_ALBUM_MODULE
 * @brief Called for every album in the obtained list of groups.
 *
 * @details Iterates over an album list.
 *
 * @remarks To use the @a album outside this function, copy the handle with the media_album_clone() function.
 *
 * @param[in] album     The handle to the media album
 * @param[in] user_data The user data passed from the foreach function
 *
 * @return @c true to continue with the next iteration of the loop,
 *         otherwise @c false to break out of the loop
 *
 * @pre media_album_foreach_album_from_db() will invoke this function.
 *
 * @see media_album_clone()
 * @see media_album_foreach_album_from_db()
 */
typedef bool (*media_album_cb)(media_album_h album, void *user_data);

/**
 * @ingroup CAPI_CONTENT_MEDIA_GROUP_MODULE
 * @brief Called for every group in the obtained list of groups.
 *
 * @details Iterates over a media group list.
 *
 * @remarks You should not free @a group_name returned by this function.
 *
 * @param[in] group_name The name of the media group
 * @param[in] user_data  The user data passed from the foreach function
 *
 * @return @c true to continue with the next iteration of the loop,
 *         otherwise @c false to break out of the loop
 *
 * @pre media_group_foreach_group_from_db() will invoke this function.
 *
 * @see media_group_foreach_group_from_db()
 */
typedef bool (*media_group_cb)(const char *group_name, void *user_data);

/**
 * @}
 */

/**
 * @addtogroup CAPI_CONTENT_MEDIA_FILTER_MODULE
 * @{
 * @brief You can use above defines to set the condition of media filter and order keyword.
 *
 */
#define MEDIA_ID "MEDIA_ID" /**< Media ID */
#define MEDIA_PATH "MEDIA_PATH"  /**< Media full path */
#define MEDIA_DISPLAY_NAME "MEDIA_DISPLAY_NAME"  /**< Media base name */
#define MEDIA_TYPE "MEDIA_TYPE"  /**< Media type: 0-image, 1-video, 2-sound, 3-music, 4-other*/
#define MEDIA_MIME_TYPE "MEDIA_MIME_TYPE"  /**< Media MIME type */
#define MEDIA_SIZE "MEDIA_SIZE"  /**< Media MIME size */
#define MEDIA_ADDED_TIME "MEDIA_ADDED_TIME"  /**< Media added time */
#define MEDIA_MODIFIED_TIME "MEDIA_MODIFIED_TIME"  /**< Media modified time */
#define MEDIA_THUMBNAIL_PATH "MEDIA_THUMBNAIL_PATH"  /**< Media thumbnail path */
#define MEDIA_TITLE "MEDIA_TITLE"  /**< Media title get from tag or file name */
#define MEDIA_ALBUM "MEDIA_ALBUM"  /**< Media album name*/
#define MEDIA_ARTIST "MEDIA_ARTIST"  /**< Media artist*/
#define MEDIA_GENRE "MEDIA_GENRE"  /**< Media genre*/
#define MEDIA_COMPOSER "MEDIA_COMPOSER"  /**< Media composer*/
#define MEDIA_YEAR "MEDIA_YEAR"  /**< Media year*/
#define MEDIA_RECORDED_DATE "MEDIA_RECORDED_DATE"  /**< Media recorded date*/
#define MEDIA_COPYRIGHT "MEDIA_COPYRIGHT"  /**< Media copyright*/
#define MEDIA_TRACK_NUM "MEDIA_TRACK_NUM"  /**< Media track number*/
#define MEDIA_DESCRIPTION "MEDIA_DESCRIPTION"  /**< Media description*/
#define MEDIA_BITRATE "MEDIA_BITRATE"  /**< Media bitrate*/
#define MEDIA_SAMPLERATE "MEDIA_SAMPLERATE"  /**< Media sample rate*/
#define MEDIA_CHANNEL "MEDIA_CHANNEL"  /**< Media channel*/
#define MEDIA_DURATION "MEDIA_DURATION"  /**< Media duration */
#define MEDIA_LONGITUDE "MEDIA_LONGITUDE"  /**< Media longitude */
#define MEDIA_LATITUDE "MEDIA_LATITUDE"  /**< Media latitude */
#define MEDIA_ALTITUDE "MEDIA_ALTITUDE"  /**< Media altitude */
#define MEDIA_WIDTH "MEDIA_WIDTH"  /**< Media width*/
#define MEDIA_HEIGHT "MEDIA_HEIGHT"  /**< Media height*/
#define MEDIA_DATETAKEN "MEDIA_DATETAKEN"  /**< Media datetaken*/
#define MEDIA_ORIENTATION "MEDIA_ORIENTATION"  /**< Media orientation*/
#define MEDIA_BURST_ID "BURST_ID"  /**< Media burst ID*/
#define MEDIA_PLAYED_COUNT "MEDIA_PLAYED_COUNT"  /**< Media playedcount*/
#define MEDIA_LAST_PLAYED_TIME "MEDIA_LAST_PLAYED_TIME"  /**< Media last played time*/
#define MEDIA_LAST_PLAYED_POSITION "MEDIA_LAST_PLAYED_POSITION"  /**< Media last played position of file*/
#define MEDIA_RATING "MEDIA_RATING"  /**< Media rating*/
#define MEDIA_FAVOURITE "MEDIA_FAVOURITE"  /**< 0-not favourite, 1-favourite*/
#define MEDIA_AUTHOR "MEDIA_AUTHOR"  /**< Media authore*/
#define MEDIA_PROVIDER "MEDIA_PROVIDER"  /**< Media provider*/
#define MEDIA_CONTENT_NAME "MEDIA_CONTENT_NAME"  /**< Media content name*/
#define MEDIA_CATEGORY "MEDIA_CATEGORY"  /**< Media category*/
#define MEDIA_LOCATION_TAG "MEDIA_LOCATION_TAG"  /**< Media location tag*/
#define MEDIA_AGE_RATING "MEDIA_AGE_RATING"  /**< Media age rating*/
#define MEDIA_KEYWORD "MEDIA_KEYWORD"  /**< Media keyword*/
#define MEDIA_IS_DRM "MEDIA_IS_DRM"  /**< Is DRM. 0-not drm, 1-drm*/
#define MEDIA_STORAGE_TYPE "MEDIA_STORAGE_TYPE"  /**< Media storage. 0-internal storage, 1-external storage*/

/**
 * @}
 */


/**

 * @addtogroup CAPI_CONTENT_MEDIA_FOLDER_MODULE
 * @{
 */
#define FOLDER_ID "FOLDER_ID"  /**< Folder ID */
#define FOLDER_PATH "FOLDER_PATH"  /**< Folder full path */
#define FOLDER_NAME "FOLDER_NAME"  /**< Folder base name */
#define FOLDER_MODIFIED_TIME "FOLDER_MODIFIED_TIME"  /**< Folder modified time */
#define FOLDER_STORAGE_TYPE "FOLDER_STORAGE_TYPE"  /**< Folder storage. 0-internal storage, 1-external storage*/

/**
 * @}
 */

/**
 * @addtogroup CAPI_CONTENT_MEDIA_PLAYLIST_MODULE
 * @{
 */
#define PLAYLIST_NAME "PLAYLIST_NAME"  /**< Playlist name */
#define PLAYLIST_MEMBER_ORDER "PLAYLIST_MEMBER_ORDER"  /**< Playlist name */
#define PLAYLIST_MEDIA_COUNT "PLAYLIST_MEDIA_COUNT"  /**< Media count in playlist view */

/**
 * @}
 */

/**
 * @addtogroup CAPI_CONTENT_MEDIA_TAG_MODULE
 * @{
 */
#define TAG_NAME "TAG_NAME"  /**< Tag name */
#define TAG_MEDIA_COUNT "TAG_MEDIA_COUNT"  /**< Media count in tag view */

/**
 * @}
 */

/**
 * @addtogroup CAPI_CONTENT_MEDIA_BOOKMARK_MODULE
 * @{
 */
#define BOOKMARK_MARKED_TIME "BOOKMARK_MARKED_TIME"  /**< Bookmark marked time */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /*__TIZEN_MEDIA_CONTENT_TYPE_H__*/

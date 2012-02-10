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

#define ERROR_MASKL16       0xFFFF
#define ERROR_SET(X)        ((X) & ERROR_MASKL16)


/**
* @addtogroup CAPI_MEDIA_CONTENT_MODULE
* @{
*/

/**
 * @ingroup CAPI_MEDIA_CONTENT_MODULE
 * @brief The enumerations of the media file format.
 */
typedef enum
{
    MEDIA_CONTENT_TYPE_IMAGE = 0x01 << 0,     /**<The type of image */
    MEDIA_CONTENT_TYPE_VIDEO = 0x01 << 1,     /**<The type of video */
    MEDIA_CONTENT_TYPE_AUDIO = 0x01 << 2,     /**<The type of audio */
    MEDIA_CONTENT_TYPE_ALL = MEDIA_CONTENT_TYPE_IMAGE|MEDIA_CONTENT_TYPE_VIDEO|MEDIA_CONTENT_TYPE_AUDIO,        /**< The type of all media content */

} media_content_type_e;

/**
 * @ingroup CAPI_CONTENT_MEDIA_FOLDER_MODULE
 * @brief The enumerations of the storage type.
 * @detail This information is used to establish where the folder is.
 */
typedef enum
{
    MEDIA_CONTENT_STORAGE_INTERNAL,    /**< The device's internal storage */		
    MEDIA_CONTENT_STORAGE_EXTERNAL,   /**< The device's external storage */   
    //MEDIA_CONTENT_STORAGE_WEB = 0x01<< 2,
} media_content_storage_e;

/**
 * @ingroup CAPI_CONTENT_MEDIA_INFO_MODULE
 * @brief The type of orientation.
 */
typedef enum {
    MEDIA_CONTENT_ORIENTATION_NOT_AVAILABLE=0,    /**< Not available*/
    MEDIA_CONTENT_ORIENTATION_NORMAL  =1,         /**< Normal*/
    MEDIA_CONTENT_ORIENTATION_HFLIP   =2,         /**< Flip horizontal*/
    MEDIA_CONTENT_ORIENTATION_ROT_180 =3,         /**< Rotate 180 degrees*/
    MEDIA_CONTENT_ORIENTATION_VFLIP   =4,         /**< Flip vertical*/
    MEDIA_CONTENT_ORIENTATION_TRANSPOSE   =5,     /**< Transpose*/
    MEDIA_CONTENT_ORIENTATION_ROT_90  =6,         /**< Rotate 90 degrees*/
    MEDIA_CONTENT_ORIENTATION_TRANSVERSE  =7,     /**< Transverse*/
    MEDIA_CONTENT_ORIENTATION_ROT_270 =8,         /**< Rotate 270 degrees*/
} media_content_orientation_e;

/**
 * @ingroup CAPI_MEDIA_CONTENT_MODULE
 * @brief The enumerations of ordering.
 */
typedef enum
{
    MEDIA_CONTENT_SORT_NONE,          /**< None order of sort*/
    MEDIA_CONTENT_SORT_BY_NAME_ASC,   /**< The sort by name in ascending order*/
    MEDIA_CONTENT_SORT_BY_NAME_DESC,  /**< The sort by name in descending order*/
    MEDIA_CONTENT_SORT_BY_DATE_ASC,	/**< The sort by date in ascending order*/
    MEDIA_CONTENT_SORT_BY_DATE_DESC,  /**< The sort by date in descending order*/    
} media_content_order_e;

/**
 * @ingroup CAPI_CONTENT_MEDIA_AUDIO_META_MODULE
 * @brief The category of audio.
 */
typedef enum{
    CONTENT_AUDIO_MUSIC,    /**< Music Category*/
    CONTENT_AUDIO_SOUND     /**< Sound Category*/
} audio_category_e;

/**
 * @ingroup CAPI_MEDIA_CONTENT_MODULE
 * @brief   The enumerations of media content error
 */
typedef enum
{
    MEDIA_CONTENT_ERROR_NONE					= TIZEN_ERROR_NONE,                   /**< Successful */
    MEDIA_CONTENT_ERROR_INVALID_PARAMETER		= TIZEN_ERROR_INVALID_PARAMETER,  /**< Invalid parameter */
    MEDIA_CONTENT_ERROR_OUT_OF_MEMORY 			= TIZEN_ERROR_OUT_OF_MEMORY,      /**< Out of memory */
    MEDIA_CONTENT_ERROR_DB_FAILED 				= TIZEN_ERROR_CONTENT_CLASS | 0x01,   /**< DB operation failed  */
    MEDIA_CONTENT_ERROR_NOT_SUPPORTED_AUDIO		= TIZEN_ERROR_CONTENT_CLASS | 0x02, /**< Only video and image info can be added to Tag */
} media_content_error_e;



/**
 * @ingroup CAPI_CONTENT_MEDIA_FILTER_INFO_MODULE
 * @brief  The type of searchable media info 
 */
typedef enum
{
	MEDIA_INFO_SEARCH_NONE = 0x00,				/**< No Search */
	MEDIA_INFO_SEARCH_BY_DISPLAY_NAME = 0x01 << 0,		/**< The search by display name */
		
}media_info_search_type_e;


/**
 * @ingroup CAPI_CONTENT_MEDIA_FILTER_FOLDER_MODULE
 * @brief  The type of searchable media folder 
 */
typedef enum
{
	MEDIA_FOLDER_SEARCH_NONE = 0x00,				/**< No Search */
	MEDIA_FOLDER_SEARCH_BY_FOLDER_NAME = 0x01 << 0,		/**< The searchable type folder name */
}media_folder_search_type_e;

/**
 * @ingroup CAPI_CONTENT_MEDIA_FILTER_AUDIO_MODULE
 * @brief  The type of searchable media audio 
 */
typedef enum
{
	MEDIA_AUDIO_SEARCH_NONE = 0x00,				/**< No Search */
	MEDIA_AUDIO_SEARCH_BY_PLAYLIST = 0x01 << 0,		/**< The searchable type of playlist */
	MEDIA_AUDIO_SEARCH_BY_ARTIST = 0x01 << 1,		/**< The searchable type of  artist */
	MEDIA_AUDIO_SEARCH_BY_ALBUM = 0x01 << 2,		/**< The searchable type of  album */
	MEDIA_AUDIO_SEARCH_BY_AUTHOR = 0x01 << 3,		/**< The searchable type of  author */
	MEDIA_AUDIO_SEARCH_BY_GENRE = 0x01 << 4,		/**< The searchable type of  genre */
}media_audio_search_type_e;

/**
 * @ingroup CAPI_CONTENT_MEDIA_FILTER_TAG_MODULE
 * @brief  The type of searchable media tag 
 */
typedef enum
{
	MEDIA_TAG_SEARCH_NONE = 0x00,				/**< No Search */
	MEDIA_TAG_SEARCH_BY_TAG_NAME = 0x01 << 0,		/**< The searchable type folder name */
}media_tag_search_type_e;





/**
 * @ingroup CAPI_CONTENT_MEDIA_FILTER_INFO_MODULE
 * @brief  The handle to media info filter.
 */
typedef struct media_info_filter_s* media_info_filter_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_FILTER_FOLDER_MODULE
 * @brief The handle to media folder filter.
 */
typedef struct media_folder_filter_s* media_folder_filter_h;

/** 
 * @ingroup CAPI_CONTENT_MEDIA_FILTER_TAG_MODULE
 * @brief The handle to media tag filter.
 */
typedef struct media_tag_filter_s* media_tag_filter_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_FILTER_AUDIO_MODULE
 * @brief The handle to media audio filter.
 */
typedef struct media_audio_filter_s* media_audio_filter_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_FILTER_BOOKMARK_MODULE
 * @brief The handle to video bookmark filter.
 */
typedef struct video_bookmark_filter_s* video_bookmark_filter_h;


/**
 * @ingroup CAPI_CONTENT_MEDIA_INFO_MODULE
 * @brief The handle to media info.
 */
typedef struct media_info_s* media_info_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_FOLDER_MODULE
 * @brief The handle to media folder.
 */
typedef struct media_folder_s* media_folder_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_TAG_MODULE
 * @brief The handle to media tag.
 */
typedef struct media_tag_s* media_tag_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_IMAGE_MODULE
 * @brief The handle to image metadata.
 */
typedef struct image_meta_s* image_meta_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_VIDEO_META_MODULE
 * @brief The handle to video metadata.
 */
typedef struct video_meta_s* video_meta_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_VIDEO_BOOKMARK_MODULE
 * @brief The handle to video bookmark.
 */
typedef struct video_bookmark_s* video_bookmark_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_AUDIO_META_MODULE
 * @brief The handle to audio metadata.
 */
typedef struct audio_meta_s* audio_meta_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_AUDIO_PLAYLIST_MODULE
 * @brief The handle to audio playlist.
 */
typedef struct audio_playlist_s* audio_playlist_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_AUDIO_ALBUM_MODULE
 * @brief The handle to audio album.
 */
typedef struct audio_album_s* audio_album_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_AUDIO_AUTHOR_MODULE
 * @brief The handle to audio author.
 */
typedef struct audio_author_s* audio_author_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_AUDIO_GENRE_MODULE
 * @brief The handle to audio genre.
 */
typedef struct audio_genre_s* audio_genre_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_AUDIO_ARTIST_MODULE
 * @brief The handle to audio artist.
 */
typedef struct audio_artist_s* audio_artist_h;

/**
 * @ingroup CAPI_CONTENT_MEDIA_FOLDER_MODULE
 * @brief Iterates over a list of folders.
 *
 * @details This callback is called for every available media folder.\n
 *
 * @remarks To use the @a folder outside this function, copy the handle with #media_folder_clone() function. 
 *
 * @param[in] folder The handle to media folder
 * @param[in] user_data The user data passed from the foreach function
 
 * @return true to continue with the next iteration of the loop, 
 * @return false to break out of the loop.
 * @pre media_folder_foreach_folder_from_db() will invoke this function.
 * @see media_folder_clone()
 * @see media_folder_foreach_folder_from_db()
 */
typedef bool (*media_folder_cb)(media_folder_h folder, void *user_data);


/**
 * @ingroup CAPI_CONTENT_MEDIA_INFO_MODULE
 * @brief Iterates over a list of media info.
 *
 * @details This callback is called for every available media info.\n
 *
 * @remarks To use the @a media outside this function, copy the handle with #media_info_clone() function. 
 *
 * @param[in] media  The handle to media info
 * @param[in] user_data The user data passed from the foreach function 
 * @return true to continue with the next iteration of the loop, 
 * @return false to break out of the loop.
 * @pre media_tag_foreach_media_from_db(), audio_playlist_foreach_media_from_db(), audio_genre_foreach_media_from_db(),
 *	audio_album_foreach_media_from_db(), audio_artist_foreach_media_from_db(), audio_author_foreach_media_from_db(), 
 * 	media_info_foreach_media_from_db(), media_folder_foreach_media_from_db() will invoke this function.
 * @see media_info_clone()
 * @see audio_album_foreach_media_from_db()
 * @see audio_playlist_foreach_media_from_db()
 * @see audio_artist_foreach_media_from_db()
 * @see audio_author_foreach_media_from_db()
 * @see audio_genre_get_media_count_from_db()
 * @see media_tag_foreach_media_from_db()
 * @see media_info_foreach_media_from_db()
 * @see  media_folder_foreach_media_from_db()
 */
typedef bool (*media_info_cb)(media_info_h media, void *user_data);

/**
 * @ingroup CAPI_CONTENT_MEDIA_TAG_MODULE
 * @brief Iterates over a list of tags
 *
 * @details This callback is called for every tag in the obtained list of tags.\n
 *
 * @remarks To use the @a tag outside this function, copy the handle with #media_tag_clone() function. 
 *
 * @param[in] tag The handle to media tag
 * @param[in] user_data  The user data passed from the foreach function
 * @return true to continue with the next iteration of the loop, 
 * @return false to break out of the loop.
 * @pre media_tag_foreach_tag_from_db(), media_info_foreach_tag_from_db() will invoke this function.
 * @see media_tag_clone()
 * @see media_tag_foreach_tag_from_db()
 * @see media_info_foreach_tag_from_db()
 */
typedef bool (*media_tag_cb)(media_tag_h tag, void *user_data);

/**
 * @ingroup CAPI_CONTENT_MEDIA_VIDEO_BOOKMARK_MODULE
 * @brief Iterates over bookmark list
 *
 * @details This callback is called for every bookmark in obtained list of bookmarks.\n
 *
 * @remarks To use the @a bookmark outside this function, copy the handle with #video_bookmark_clone() function. 
 *
 * @param[in] bookmark The handle to video bookmark
 * @param[in] user_data  The user data passed from the foreach function
 * @return true to continue with the next iteration of the loop, 
 * @return false to break out of the loop.
 * @pre video_bookmark_foreach_bookmark_from_db() will invoke this function.
 * @see video_bookmark_clone()
 * @see video_bookmark_foreach_bookmark_from_db()
 */
typedef bool (*video_bookmark_cb)(video_bookmark_h bookmark, void *user_data);

/**
 * @ingroup CAPI_CONTENT_MEDIA_AUDIO_PLAYLIST_MODULE
 * @brief Iterates over playlist list
 *
 * @details This callback is called for every playlist in obtained list of playlists.\n
 *
 * @remarks To use the @a playlist outside this function, copy the handle with #audio_playlist_clone() function. 

 *
 * @param[in] playlist The handle to audio playlist
 * @param[in] user_data  The user data passed from the foreach function
 * @return true to continue with the next iteration of the loop, 
 * @return false to break out of the loop.
 * @pre audio_playlist_foreach_playlist_from_db() will invoke this function.
 * @see audio_playlist_clone()
 * @see audio_playlist_foreach_playlist_from_db()
 */
typedef bool (*audio_playlist_cb)(audio_playlist_h playlist, void *user_data);

/**
 * @ingroup CAPI_CONTENT_MEDIA_AUDIO_GENRE_MODULE
 * @brief Iterates over genre list
 *
 * @details This callback is called for every genre in obtained list of groups.\n
 *
 * @remarks To use the @a genre outside this function, copy the handle with #audio_genre_clone() function. 
 *
 * @param[in] genre  The handle to audio genre
 * @param[in] user_data  The user data passed from the foreach function
 * @return true to continue with the next iteration of the loop, 
 * @return false to break out of the loop.
 * @pre audio_genre_foreach_genre_from_db() will invoke this function.
 * @see audio_genre_clone()
 * @see audio_genre_foreach_genre_from_db()
 */
typedef bool (*audio_genre_cb)(audio_genre_h genre, void *user_data);

/**
 * @ingroup CAPI_CONTENT_MEDIA_AUDIO_ARTIST_MODULE
 * @brief Iterates over artist list
 *
 * @details This callback is called for every artist in obtained list of groups.\n
 *
 * @remarks To use the @a artist outside this function, copy the handle with #audio_artist_clone() function. 
 *
 * @param[in] artist The handle to audio artist
 * @param[in] user_data  The user data passed from the foreach function
 * @return true to continue with the next iteration of the loop, 
 * @return false to break out of the loop.
 * @pre audio_artist_foreach_artist_from_db() will invoke this function.
 * @see audio_artist_clone()
 * @see audio_artist_foreach_artist_from_db()
 */
typedef bool (*audio_artist_cb)(audio_artist_h artist, void *user_data);

/**
 * @ingroup CAPI_CONTENT_MEDIA_AUDIO_AUTHOR_MODULE
 * @brief Iterates over author list
 *
 * @details This callback is called for every author in obtained list of groups.\n
 *
 * @remarks To use the @a author outside this function, copy the handle with #audio_author_clone() function. 
 *
 * @param[in] author  The handle to audio author
 * @param[in] user_data  The user data passed from the foreach function
 * @return true to continue with the next iteration of the loop, 
 * @return false to break out of the loop.
 * @pre audio_author_foreach_author_from_db() will invoke this function.
 * @see audio_author_clone()
 * @see audio_author_foreach_author_from_db()
 */
typedef bool (*audio_author_cb)(audio_author_h author, void *user_data);

/**
 * @ingroup CAPI_CONTENT_MEDIA_AUDIO_ALBUM_MODULE
 * @brief Iterates over album list
 *
 * @details This callback is called for every album in obtained list of groups.\n
 *
 * @remarks To use the @a album outside this function, copy the handle with #audio_album_clone() function. 
 *
 * @param[in] album  The handle to audio album
 * @param[in] user_data  The user data passed from the foreach function
 * @return true to continue with the next iteration of the loop, 
 * @return false to break out of the loop.
 * @pre audio_album_foreach_album_from_db() will invoke this function.
 * @see audio_album_clone()
 * @see audio_album_foreach_album_from_db()
 */

typedef bool (*audio_album_cb)(audio_album_h album, void *user_data);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /*__TIZEN_MEDIA_CONTENT_TYPE_H__*/

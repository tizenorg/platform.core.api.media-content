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


#ifndef __TIZEN_AUDIO_META_H__
#define __TIZEN_AUDIO_META_H__

#include <media_content_type.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup CAPI_CONTENT_MEDIA_AUDIO_META_MODULE
 * @{
 *
 * @file audio_meta.h
 * @brief This file contains the audio metadata API and related structure and enumeration. \n
 *        Description of the audio content involves: album, artist, author, genre and description tags. \n
 *        Parameters of the recording are also supported, as: format, bitrate, duration, size etc.
 */


/**
 * @brief Destroys audio metadata.
 *
 * @param [in] audio The handle to audio metadata.
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre Get copy of audio metadata handle handle by calling audio_meta_clone()
 * @see audio_meta_clone()
 * @see media_info_get_audio_from_db()
 */
int audio_meta_destroy(audio_meta_h audio);


/**
 * @brief Clones audio metadata.
 * @details Function copies the audio metadata handle handle from source to destination.
 *
 * @remark The destination handle must be released with audio_meta_destroy() by you.
 *
 * @param [out] dst A destination handle to audio metadata
 * @param [in] src The source handle to audio metadata
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 * @see audio_meta_destroy()
 */
int audio_meta_clone(audio_meta_h* dst, audio_meta_h src);


/**
 * @brief Gets name of genre of given audio metadata.
 *
 * @remarks  @a genre_name must be released with free() by you.
 *
 * @param [in] audio The handle to audio metadata
 * @param [out] genre_name The name of the genre
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 */
int audio_meta_get_genre(audio_meta_h audio, char **genre_name);


/**
 * @brief Gets name of album of given audio metadata.
 *
 * @remarks @a album_name must be released with free() by you.
 *
 * @param [in] audio The handle to audio metadata
 * @param [out] album_name The name of the album
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 */
int audio_meta_get_album(audio_meta_h audio, char **album_name);


/**
 * @brief Gets name of artist of given audio metadata.
 *
 * @remarks @a artist_name must be released with free() by you.
 *
 * @param [in] audio The handle to audio metadata
 * @param [out] artist_name The name of the artist
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 */
int audio_meta_get_artist(audio_meta_h audio, char **artist_name);


/**
 * @brief Gets name of author of given audio metadata.
 *
 * @remarks @a author_name must be released with free() by you.
 *
 * @param [in] audio The handle to audio metadata
 * @param [out] author_name The name of the author of audio
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 */
int audio_meta_get_author(audio_meta_h audio, char **author_name);


/**
 * @brief Gets year of given audio metadata.
 *
 * @remarks @a year must be released with free() by you.
 *
 * @param [in] audio The handle to audio metadata
 * @param [out] year The year of the audio file
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 */
int audio_meta_get_year(audio_meta_h audio, char** year);


/**
 * @brief Gets copyright notice of given audio metadata.
 *
 * @remarks @a copyright must be released with free() by you.
 *
 * @param [in] audio The handle to audio metadata
 * @param [out] copyright The audio copyright notice
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 */
int audio_meta_get_copyright(audio_meta_h audio, char **copyright);


/**
 * @brief Gets description of given audio metadata.
 *
 * @remarks @a description must be released with free() by you.
 *
 * @param [in] audio The handle to audio metadata
 * @param [out] description The audio description
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 */
int audio_meta_get_description(audio_meta_h audio, char **description);


/**
 * @brief Gets format of given audio metadata.
 *
 * @remarks @a format must be released with free() by you.
 *
 * @param [in] audio The handle to audio metadata
 * @param [out] format The audio format
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 */
int audio_meta_get_format(audio_meta_h audio, char **format);


/**
 * @brief Gets bitrate of given audio metadata in bitrate per second.
 *
 * @param [in] audio The handle to audio metadata
 * @param [out] bitrate The audio bitrate in bit per second [bps].
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 */
int audio_meta_get_bitrate(audio_meta_h audio, int *bitrate);


/**
 * @brief Gets track number of given audio metadata.
 *
 * @param [in] audio The handle to audio metadata
 * @param [out] track_num The audio track number
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 */
int audio_meta_get_track_num(audio_meta_h audio, int *track_num);


/**
 * @brief Gets track duration of given audio metadata.
 *
 * @param [in] audio The handle to audio metadata
 * @param [out] duration The audio file duration
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 */
int audio_meta_get_duration(audio_meta_h audio, int *duration);


/**
 * @brief Gets track rating of given audio metadata.
 *
 * @param [in] audio The handle to audio metadata
 * @param [out] rating The rating of audio
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 */
int audio_meta_get_rating(audio_meta_h audio, int *rating);


/**
 * @brief Gets number which represents how many times given audio has been played.
 *
 * @param [in] audio The handle to audio metadata
 * @param [out] count_played The counter of audio played
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 */
int audio_meta_get_count_played(audio_meta_h audio, int *count_played);


/**
 * @brief Gets the audio's played time parameter.
 * @details Function returns audio's elapsed playback time parameter as period
 * starting from the beginning of the track.
 *
 * @param [in] audio The handle to audio metadata
 * @param [out] time_played The elapsed time of the audio
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 */
int audio_meta_get_time_played(audio_meta_h audio, int *time_played);


/**
 * @brief Gets the time when audio file was added.
 *
 * @param [in] audio The handle to audio metadata
 * @param [out]  time_added The time when  audio file added
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 */
int audio_meta_get_time_added(audio_meta_h audio, time_t *time_added);

/**
 * @brief Gets audio's file size in bytes.
 *
 * @param [in] audio The handle to audio metadata
 * @param [out] size The size of audio file in bytes.
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 */
int audio_meta_get_size(audio_meta_h audio, int *size);


/**
 * @brief Gets audio's category from desired audio metadata.
 *
 * @param [in] audio The handle to audio metadata
 * @param [out] category The audio category
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 */
int audio_meta_get_category(audio_meta_h audio, audio_category_e *category);


/**
 * @brief Updates audio's played counter to the media database.
 *
 * @param [in] audio The handle to audio metadata
 * @param [in] count The new counter of audio played
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see media_content_connect()
 */
int audio_meta_update_count_played_to_db(audio_meta_h audio, int count);

/**
 * @brief Updates audio's played time parameter to the media database.
 *
 * @param [in] audio The handle to audio metadata
 * @param [in] time The time from the beginning of audio
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see media_content_connect()
 */
int audio_meta_update_time_played_to_db(audio_meta_h audio, time_t time);


/**
 * @}
 */


/**
 * @addtogroup CAPI_CONTENT_MEDIA_AUDIO_PLAYLIST_MODULE
 * @{
 */


/**
 * @brief Iterates through the audio playlist with optional @a filter from the media database.
 * @details This function gets all audio playlist handles meeting the given filter. 
 * The callback function will be invoked for every retrieved audio playlist.
 * If NULL is passed to the filter, no filtering is applied.

 *
 * @param [in] filter The handle to audio filter
 * @param [in] callback The callback function to invoke.
 * @param [in] user_data User data to be passed to the callback function.
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 * @pre This function requires opened connection to content service by media_content_connect().
 * @post This function invokes audio_playlist_cb().
 * @see #audio_playlist_cb
 * @see media_content_connect()
 * @see media_audio_filter_create()
 *
 */
int audio_playlist_foreach_playlist_from_db(media_audio_filter_h filter, audio_playlist_cb callback, void *user_data);


/**
 * @brief Iterates through the media files with optional @a filter in the given @a audio @a playlist from the media database.
 * @details This function gets all media files associated with the given audio playlist and
 * meeting desired filter option and calls registered callback function for
 * every retrieved media info. If NULL is passed to the @a filter, no filtering is applied. 
 *
 * @param [in] playlist The handle to audio playlist
 * @param [in] filter The handle to audio filter
 * @param [in] callback The callback function to invoke
 * @param [in] user_data The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 * @pre This function requires opened connection to content service by media_content_connect().
 * @post This function invokes media_info_cb().
 * @see #media_info_cb
 * @see media_content_connect()
 * @see media_audio_filter_create()
 *
 */
int audio_playlist_foreach_media_from_db(audio_playlist_h playlist, media_audio_filter_h filter, media_info_cb callback, void *user_data);


/**
 * @brief Inserts a new playlist with given name in the media database. 
 *
 * @remark The created handle must be released with audio_playlist_destroy() by you. 
 * @param [in] name The name of the inserted playlist.
 * @param [out] playlist A created handle to audio playlist
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see media_content_connect()
 * @see audio_playlist_delete_from_db()
 *
 */
int audio_playlist_insert_to_db(const char *name, audio_playlist_h *playlist);


/**
 * @brief Deletesthe given playlist from the media database.
 *
 * @param [in] playlist The handle to audio playlist
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see media_content_connect()
 * @see audio_playlist_insert_to_db()
 *
 */
int audio_playlist_delete_from_db(audio_playlist_h playlist);

/**
 * @brief Gets number of media info for the given playlist present in the media database.

 *
 * @param [in] playlist The handle to audio playlist
 * @param [out] count The number of playlist items
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see media_content_connect()
 *
 */
int audio_playlist_get_media_count_from_db(audio_playlist_h playlist, int *count);


/**
 * @brief Destroys a playlist handle.
 * @details Function frees all resources related to playlist handle. This
 * handle no longer can be used to perform any operation. New handle has to
 * be created before next usage.
 *
 * @param [in] playlist The handle to audio playlist
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see audio_playlist_clone()
 * @pre Get copy of playlist handle by calling audio_playlist_clone() or audio_playlist_insert_to_db()
 * @see audio_playlist_clone()
 *
 */
int audio_playlist_destroy(audio_playlist_h playlist);


/**
 * @brief Clones playlist handle.
 * @details This function copies the audio playlist handle from a source to
 * destination. There is no audio_playlist_create() function. The audio_playlist_h is created internally and available through 
 * audio playlist foreach function such as audio_playlist_foreach_playlist_from_db(). To  use this handle outside of these foreach functions, 
 * use this function. 
 * 
 * @remark The destination handle must be released with audio_playlist_destroy() by you.  
 *
 * @param [in] src The source handle to  audio playlist
 * @param [out] dst A destination handle to audio playlist
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 * @see audio_playlist_destroy()
 * @see audio_playlist_foreach_playlist_from_db()
 */
int audio_playlist_clone(audio_playlist_h *dst, audio_playlist_h src);

/**
 * @brief Gets a name of the playlist.
 *
 * @remarks @a playlist_name must be released with free() by you.
 *
 * @param [in] playlist The handle to audio playlist
 * @param [out] playlist_name The playlist name
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 *
 */
int audio_playlist_get_name(audio_playlist_h playlist, char **playlist_name);


/**
 * @brief Updates the name of the given playlist in the media database.
 *
 * @param [in] playlist The handle to audio playlist
 * @param [in] playlist_name The playlist name to set
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see media_content_connect()
 */
int audio_playlist_update_name_to_db(audio_playlist_h playlist, const char *playlist_name);

/**
 * @brief Adds a new media info to the playlist present in the media database.
 *
 * @param [in] playlist The handle to audio playlist
 * @param [in] media The newly added media info handle
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see media_content_connect()
 * @see audio_playlist_remove_media_from_db()
 */
int audio_playlist_add_media_to_db(audio_playlist_h playlist, media_info_h media);

/**
 * @brief Removes the given @a media from the playlist present in the media database.
 *
 * @param [in] playlist The handle to audio playlist
 * @param [in] media The handle to media info to be removed
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see media_content_connect()
 * @see audio_playlist_add_media_to_db()
 */
int audio_playlist_remove_media_from_db(audio_playlist_h playlist, media_info_h media);

/**
 * @}
 */


/**
 * @addtogroup CAPI_CONTENT_MEDIA_AUDIO_GENRE_MODULE
 * @{
 */

/**
 * @brief Iterates through the audio genre with optional @a filter from the media database.
 * @details This function gets all audio genre handles meeting the given filter. 
 * The callback function will be invoked for every retrieved audio genre.
 * If NULL is passed to the filter, no filtering is applied.

 *
 * @param [in] filter The handle to audio filter
 * @param [in] callback The callback function to invoke
 * @param [in] user_data The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @post This function invokes audio_genre_cb().
 * @see #audio_genre_cb
 * @see media_content_connect()
 * @see media_audio_filter_create()
 *
 */
int audio_genre_foreach_genre_from_db(media_audio_filter_h filter, audio_genre_cb callback, void *user_data);


/**
 * @brief Iterates through the media files with optional @a filter in the given @a audio @a genre from the media database.
 * @details This function gets all media files associated with the given audio genre and
 * meeting desired filter option and calls registered callback function for
 * every retrieved media info. If NULL is passed to the @a filter, no filtering is applied. 
 *
 * @param [in] genre The handle to audio genre
 * @param [in] filter The filter handle.
 * @param [in] callback The callback function to invoke
 * @param [in] user_data The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @post This function invokes media_info_cb().
 * @see #media_info_cb
 * @see media_content_connect()
 * @see media_audio_filter_create()
 */
int audio_genre_foreach_media_from_db(audio_genre_h genre, media_audio_filter_h filter, media_info_cb callback, void *user_data);


/**
 * @brief Gets number of media info for the given genre present in the media database.
 *
 * @param [in] genre The handle to audio genre
 * @param [out] count The count of "genre group" media information.
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see media_content_connect()
 */
int audio_genre_get_media_count_from_db(audio_genre_h genre, int *count);



/**
 * @brief Destroys genre handle.
 * @details Function frees all resources related to genre handle. This handle
 * no longer can be used to perform any operation. A new handle has to
 * be created before the next use.
 *
 * @param [in] genre The handle to audio genre
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre Get copy of genre handle by calling audio_genre_clone()
 * @see audio_genre_clone()
 */
int audio_genre_destroy(audio_genre_h genre);

/**
 * @brief Clones genre handle.
 * @details This function copies the audio genre handle from a source to
 * destination. There is no audio_genre_create() function. The media_genre_h is created internally and available through 
 * audio genre foreach function such as audio_genre_foreach_genre_from_db(). To  use this handle outside of these foreach functions, 
 * use this function. 
 *
 * @remark The destination handle must be released with audio_genre_destroy() by you. 
 *
 * @param [in] src The source handle to audio genre
 * @param [out] dst A destination handle to audio genre
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 * @see audio_genre_destroy()
 * @see audio_genre_foreach_genre_from_db()
 */
int audio_genre_clone(audio_genre_h *dst,audio_genre_h src);


/**
 * @brief Gets a name of the genre.
 *
 * @remarks @a genre_name must be released with free() by you.
 *
 * @param [in] genre The handle to audio genre
 * @param [out] genre_name The name of the audio genre
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 */
int audio_genre_get_name(audio_genre_h genre, char **genre_name);

/**
 * @}
 */


/**
 * @addtogroup CAPI_CONTENT_MEDIA_AUDIO_ALBUM_MODULE
 * @{
 */

/**
 * @brief Iterates through the audio album with optional @a filter from the media database.
 * @details This function gets all audio album handles meeting the given filter. 
 * The callback function will be invoked for every retrieved audio album.
 * If NULL is passed to the filter, no filtering is applied.
 *
 * @param [in] filter The handle to audio filter
 * @param [in] callback The callback function to invoke
 * @param [in] user_data The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available 
 * @pre This function requires opened connection to content service by media_content_connect().
 * @post This function invokes audio_album_cb().
 * @see #audio_album_cb
 * @see media_content_connect()
 * @see media_audio_filter_create()
 *
 */
int audio_album_foreach_album_from_db(media_audio_filter_h filter, audio_album_cb callback, void *user_data);


/**
 * @brief Iterates through the media files with optional @a filter in the given @a audio @a album from the media database.
 * @details This function gets all media files associated with the given audio album and
 * meeting desired filter option and calls registered callback function for
 * every retrieved media info. If NULL is passed to the @a filter, no filtering is applied. 
 *
 * @param [in] album The handle to audio album
 * @param [in] filter The handle to audio filter
 * @param [in] callback The callback function to invoke
 * @param [in] user_data The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @post This function invokes media_info_cb().
 * @see #media_info_cb
 * @see media_content_connect()
 * @see media_audio_filter_create()
 */
int audio_album_foreach_media_from_db(audio_album_h album, media_audio_filter_h filter, media_info_cb callback, void *user_data);


/**
 * @brief Gets number of media info for the given album present in the media database.
 *
 * @param [in] album  The handle to audio album
 * @param [out] count A count of album
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see media_content_connect()
 */
int audio_album_get_media_count_from_db(audio_album_h album, int *count);




/**
 * @brief Destroys album handle.
 * @details Function frees all resources related to album handle. This handle
 * no longer can be used to perform any operation. A new handle has to
 * be created before the next use.
 *
 * @param [in] album  The handle to audio album
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre Get copy of album handle by calling audio_album_clone()
 * @see audio_album_clone()
 */
int audio_album_destroy(audio_album_h album);

/**
 * @brief Clones audio album.
 * @details This function copies the audio album handle from a source to
 * destination. There is no audio_album_create() function. The audio_album_h is created internally and available through 
 * audio album foreach function such as audio_album_foreach_album_from_db(). To  use this handle outside of these foreach functions, 
 * use this function. 
 *
 * @remark The destination handle must be released with audio_album_destroy() by you. 
 *
 * @param [in] src The source handle to audio album
 * @param [out] dst A destination handle to audio album
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available  
 * @see audio_album_destroy()
 * @see audio_album_foreach_album_from_db()
 */
int audio_album_clone(audio_album_h *dst,audio_album_h src);


/**
 * @brief Gets a name of the album.
 *
 * @remarks @a album_name must be released with free() by you.
 *
 * @param [in] album  The handle to audio album
 * @param [out] album_name A name of audio album handle
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 *
 */
int audio_album_get_name(audio_album_h album, char **album_name);

/**
 * @}
 */


/**
 * @addtogroup CAPI_CONTENT_MEDIA_AUDIO_ARTIST_MODULE
 * @{
 */

/**
 * @brief Iterates through the media files with optional @a filter from the media database.
 * @details This function gets all audio artist handles meeting the given filter. 
 * The callback function will be invoked for every retrieved audio artist.
 * If NULL is passed to the filter, no filtering is applied.
 *
 * @param [in] filter The handle to audio filter
 * @param [in] callback The callback function to invoke
 * @param [in] user_data The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 * @pre This function requires opened connection to content service by media_content_connect().
 * @post This function invokes audio_artist_cb().
 * @see #audio_artist_cb
 * @see media_content_connect()
 * @see media_audio_filter_create()
 */
int audio_artist_foreach_artist_from_db(media_audio_filter_h filter, audio_artist_cb callback, void *user_data);


/**
 * @brief Iterates through the media files with optional @a filter in the given @a audio @artist from the media database.
 * @details This function gets all media files associated with the given audio artist and
 * meeting desired filter option and calls registered callback function for
 * every retrieved media info. If NULL is passed to the @a filter, no filtering is applied. 

 *
 * @param [in] artist The handle to audio artist
 * @param [in] filter The handle to audio filter
 * @param [in] callback The callback function to invoke
 * @param [in] user_data The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 * @pre This function requires opened connection to content service by media_content_connect().
 * @post This function invokes media_info_cb().
 * @see #media_info_cb
 * @see media_content_connect()
 * @see media_audio_filter_create()
 */
int audio_artist_foreach_media_from_db(audio_artist_h artist, media_audio_filter_h filter, media_info_cb callback, void *user_data);


/**
 * @brief Gets number of media info for the given artist present in the media database.
 *
 * @param [in] artist The handle to audio artist
 * @param [out] count The count of artist
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see media_content_connect()
 */
int audio_artist_get_media_count_from_db(audio_artist_h artist, int *count);

/**
 * @brief Destroys artist handle.
 * @details Function frees all resources related to artist handle. This handle
 * no longer can be used to perform any operation. A new handle has to
 * be created before the next use.
 *
 * @param [in] artist The handle to audio artist
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre Get copy of artist handle by calling audio_artist_clone()
 * @see audio_artist_clone()
 */
int audio_artist_destroy(audio_artist_h artist);

/**
 * @brief Clones audio artist.
 * @details This function copies the audio artist handle from a source to
 * destination. There is no audio_artist_create() function. The audio_artist_h is created internally and available through 
 * audio artist foreach function such as audio_artist_foreach_artist_from_db(). To  use this handle outside of these foreach functions, 
 * use this function. 

 *
 * @remark The destination handle must be released with audio_artist_destroy() by you. 
 *
 * @param [in] src The source handle to audio artist
 * @param [out] dst A destination handle to audio artist
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available 
 * @see audio_artist_destroy()
 * @see audio_artist_foreach_artist_from_db() 
 */
int audio_artist_clone(audio_artist_h *dst,audio_artist_h src);

/**
 * @brief Gets a name of the artist.
 *
 * @remarks @a artist_name must be released with free() by you.
 *
 * @param [in] artist The handle to audio artist
 * @param [out] artist_name A name of the audio artist handle
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 */
int audio_artist_get_name(audio_artist_h artist, char **artist_name);


/**
 * @}
 */


/**
 * @addtogroup CAPI_CONTENT_MEDIA_AUDIO_AUTHOR_MODULE
 * @{
 */

/**
 *
 * @brief Iterates through the audio author with optional @a filter from the media database.
 * @details This function gets all audio author handles meeting the given filter. 
 * The callback function will be invoked for every retrieved audio playlist.
 * If NULL is passed to the filter, no filtering is applied.
 *
 * @param [in] filter The handle to audio filter
 * @param [in] callback The callback function to invoke
 * @param [in] user_data The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @post This function invokes audio_author_cb().
 * @see #audio_author_cb
 * @see media_content_connect()
 * @see media_audio_filter_create()
 */
int audio_author_foreach_author_from_db(media_audio_filter_h filter, audio_author_cb callback, void *user_data);


/**
 * @brief Iterates through the media files with optional @a filter in the given @a audio @a author from the media database.
 * @details This function gets all media files associated with the given audio author and
 * meeting desired filter option and calls registered callback function for
 * every retrieved media info. If NULL is passed to the @a filter, no filtering is applied. 
 *
 *
 * @param [in] author The handle to audio author
 * @param [in] filter The handle to audio filter
 * @param [in] callback The callback function to invoke
 * @param [in] user_data The user data to be passed to the callback function
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @post This function invokes media_info_cb().
 * @see #media_info_cb
 * @see media_content_connect()
 * @see media_audio_filter_create()
 */
int audio_author_foreach_media_from_db(audio_author_h author, media_audio_filter_h filter, media_info_cb callback, void *user_data);


/**
 * @brief Gets number of media info for the given author present in the media database.
 *
 * @param [in] author The handle to audio author
 * @param [out] count The count of author
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre This function requires opened connection to content service by media_content_connect().
 * @see media_content_connect()
 */
int audio_author_get_media_count_from_db(audio_author_h author, int *count);


/**
 * @brief Destroys author handle.
 * @details Function frees all resources related to author handle. This handle
 * no longer can be used to perform any operation. A new handle has to
 * be created before the next use.
 *
 * @param [in] author The handle to audio author
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @pre Get copy of author handle by calling audio_author_clone()
 * @see audio_author_clone()
 */
int audio_author_destroy(audio_author_h author);


/**
 * @brief Clones audio author.
 * @details This function copies the audio author handle from a source to
 * destination. There is no audio_author_create() function. The audio_author_h is created internally and available through 
 * audio author foreach function such as audio_author_foreach_author_from_db(). To  use this handle outside of these foreach functions, 
 * use this function. 
 *
 *
 * @param [in] src The source handle to audio author
 * @param [out] dst A destination handle to audio author
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 * @post The destination handle should be deallocated by audio_author_destroy()      
 * @see audio_author_destroy()
 * @see audio_author_foreach_author_from_db()  
 */
int audio_author_clone(audio_author_h *dst,audio_author_h src);

/**
 * @brief Gets a name of the author.
 *
 * @remarks @a author_name must be released with free() by you.
 *
 * @param [in] author The handle to audio author
 * @param [out] author_name The name of the "author group" handle
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Not enough memory is available
 */
int audio_author_get_name(audio_author_h author, char **author_name);


/**
 * @}
 */


#ifdef __cplusplus
}
#endif


#endif /*__TIZEN_AUDIO_META_H__*/

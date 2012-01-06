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



#ifndef __TIZEN_MEDIA_FILTER_H__
#define __TIZEN_MEDIA_FILTER_H__

#include <media_content_type.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup CAPI_CONTENT_MEDIA_FILTER_INFO_MODULE
 * @{
 */

/**
 * @brief Creates a media info filter handle.
 * @details This function creates a media info filter handle. The handle can be
 * used to get filtered information based on filter properties i.e. offset, count,search type, search keyword, 
 * media type and order.
 *@remarks The @a filter handle must be released with media_info_filter_destroy() by you. 
 * @param[out] filter A handle to media info filter
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @see media_info_filter_destroy()
 *
 */
int media_info_filter_create(media_info_filter_h* filter);

/**
 * @brief Destroys a media info filter handle.
 * @details The function frees all resources related to the media info filter handle. The filter
 * handle no longer can be used to perform any operation. A new filter handle
 * has to be created before the next usage.
 *
 * @param[in] filter The handle to media info filter
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_info_filter_create()
 *
 */
int media_info_filter_destroy(media_info_filter_h filter);


/**
 * @brief Set the media info filter's offset and count.
 * @details This function set the @a offset and @a count for the given filter used to limit number of items returned.
 *  For example, if you set the @a offset as 10 and @a count as 5, then only searched data from 10 to 14 will be returned when the filter is used with foreach functions. 
 *
 * @param[in] filter The handle to media info filter
 * @param[in] offset The start position of the given filter(Starting from zero).
 * @param[in] count The number of items to be searched with respect to offset
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_info_filter_create()
 * @see media_info_filter_destroy() 
 */
int media_info_filter_set_offset(media_info_filter_h filter, int offset, int count);


/**
 * @brief Set the @a search @a keyword and @a search @a type for given @a filter.
 *
 * @param[in] filter The handle to media info filter
 * @param[in] search_type The type which user want to search. e.g. display name
 * @param[in] search_keyword The keyword which user want to search.
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_info_filter_create()
 * @see media_info_filter_destroy()  
 */
int media_info_filter_set_search_keyword(media_info_filter_h filter, media_info_search_type_e search_type, const char *search_keyword);


/**
 * @brief Set the media info filter's content order either descending or ascending.
 *
 * @param[in] filter The media info filter handle
 * @param[in] order The search order type
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_info_filter_create()
 * @see media_info_filter_destroy()  
 */
int media_info_filter_set_order(media_info_filter_h filter, media_content_order_e order);


/**
 * @brief Set the media info filter's content type.
 *

 *
 * @param[in] filter The handle to Media Info filter.
 * @param[in] media_type The type of the content(#media_content_type_e) \n
 * To allow searching over different content types, you should use bitwise 'OR' operator to compose 'type' parameter. 
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_info_filter_create()
 * @see media_info_filter_destroy()  
 */
int media_info_filter_set_media_type(media_info_filter_h filter,int media_type);


/**
 * @brief Gets the @a offset and @a count for the given @a filter used to limit number of items returned.
 *
 * @param[in] filter The handle to Media Info filter
 * @param[out] offset The start position of the given filter(Starting from zero).
 * @param[out] count The number of items to be searched with respect to offset.
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_info_filter_create()
 * @see media_info_filter_destroy()  
 */
int media_info_filter_get_offset(media_info_filter_h filter, int* offset, int* count);


/**
 * @brief Gets the @a search @a keyword and @a search @a type for given @a filter.
 *
 * @remarks @a search_keyword must be released with free() by you. 
 * @param[in] filter The handle to media info filter
 * @param[out] search_type The type of search
 * @param[out] search_keyword The keyword which user want to search
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_info_filter_create()
 * @see media_info_filter_destroy()  
 */
int media_info_filter_get_search_keyword(media_info_filter_h filter,media_info_search_type_e* search_type, char **search_keyword);


/**
 * @brief Gets the media info filter's content order.
 * @details This function gets the @a order for given @a filter.
 *
 * @param[in] filter The handle to media info filter
 * @param[out] order The search order type
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_info_filter_create()
 * @see media_info_filter_destroy()  
 */
int media_info_filter_get_order(media_info_filter_h filter, media_content_order_e* order);


/**
 * @brief Gets the media info filter's content type.
 * @details This function gets the content type (#media_content_type_e) for given filter
 *
 *
 * @param[in] filter The handle to media info filter
 * @param[out] type The type of the media content(#media_content_type_e) \n
 * To allow searching over different content types, you should use bitwise 'OR' operator to compose 'type' parameter. 
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_info_filter_create()
 * @see media_info_filter_destroy()  
 */
int media_info_filter_get_media_type(media_info_filter_h filter,int* type);

/**
 * @}
 */



/**
 * @addtogroup CAPI_CONTENT_MEDIA_FILTER_FOLDER_MODULE
 * @{
 */


/**
 * @brief Creates a media folder filter handle.
 * @details This function creates a media folder filter handle. The handle can be
 * used to get filtered information based on filter properties i.e. offset, count, search type, search keyword
 * and order.
 *
 * @remarks The @a filter handle must be released with media_info_filter_destroy() by you. 
 * @param[out] filter  A handle to media folder filter
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @see media_folder_filter_destroy(),
 *
 */
int media_folder_filter_create(media_folder_filter_h* filter);

/**
 * @brief Destroys a media media folder filter
 * @details The function frees all resources related to the media folder filter handle. The filter
 * handle no longer can be used to perform any operation. A new filter handle
 * has to be created before the next usage.
 *
 * @param[in] filter The handle to media folder filter
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_folder_filter_create()
 *
 */

int media_folder_filter_destroy(media_folder_filter_h filter);


/**
 * @brief Set the media folder filter's offset and count.
 * @details This function set the @a offset and @a count for the given filter used to limit number of items returned.
 *  For example, if you set the @a offset as 10 and @a count as 5, then only searched data from 10 to 14 will be returned when the filter is used with foreach functions. 
 *
 * @param[in] filter The handle to media folder filter
 * @param[in] offset The start position of the given filter(Starting from zero).
 * @param[in] count The number of items to be searched with respect to offset.
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_folder_filter_create()
 * @see media_folder_filter_destroy() 
 */
int media_folder_filter_set_offset(media_folder_filter_h filter, int offset, int count);


/**
 * @brief Set the @a search @a keyword and @a search @a type for given @a filter.
 *
 * @param[in] filter The handle to media folder filter
 * @param[in] search_type The type which user want to search.
 * @param[in] search_keyword The keyword which user want to search
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_folder_filter_create()
 * @see media_folder_filter_destroy() 
 */
int media_folder_filter_set_search_keyword(media_folder_filter_h filter,media_folder_search_type_e search_type,const char *search_keyword);


/**
 * @brief Set the media folder filter's content order either descending or ascending.
 *
 * @param[in] filter the handle to media folder filter
 * @param[in] order The search order type
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_folder_filter_create()
 * @see media_folder_filter_destroy() 
 */
int media_folder_filter_set_order(media_folder_filter_h filter, media_content_order_e order);



/**
 * @brief Gets the @a offset and @a count for the given @a filter used to limit number of items returned.
 *
 * @param[in] filter The handle to media folder filter
 * @param[out] offset The start position of the given filter(Starting from zero).
 * @param[out] count The number of items to be searched with respect to offset.
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_folder_filter_create()
 * @see media_folder_filter_destroy()
 */
int media_folder_filter_get_offset(media_folder_filter_h filter, int* offset, int* count);


/**
 * @brief Gets the @a search @a keyword and @a search @a type for given @a filter.
 *
 * @remarks search_keyword must be released with free() by you. 
 * @param[in] filter The handle to media folder filter
 * @param[out] search_type The type of search
 * @param[out] search_keyword The keyword which user want to search
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_folder_filter_create()
 * @see media_folder_filter_destroy()
 */
int media_folder_filter_get_search_keyword(media_folder_filter_h filter,media_folder_search_type_e* search_type, char **search_keyword);


/**
 * @brief Gets the media folder filter's content order.
 * @details This function gets the @a order for given @a filter.
 *
 * @param[in] filter The handle to media folder filter
 * @param[out] order The search order type
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_folder_filter_create()
 * @see media_folder_filter_destroy() 
 */
int media_folder_filter_get_order(media_folder_filter_h filter, media_content_order_e* order);



/**
 * @}
 */




/**
 * @addtogroup CAPI_CONTENT_MEDIA_FILTER_AUDIO_MODULE
 * @{
 */
 


/**
 * @brief Creates a audio filter handle.
 * @details This function creates a #media_audio_filter_h filter handle. The handle can be
 * used to get filtered information based on filter properties i.e. offset, count, search keyword
 * and order.
 *
 * @param[out] filter A handle to media audio filter
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @see media_audio_filter_destroy(),
 *
 */
int media_audio_filter_create(media_audio_filter_h* filter);

/**
 * @brief Destroys a media audio filter handle.
 * @details The function frees all resources related to the media audio filter handle. The filter
 * handle no longer can be used to perform any operation. A new filter handle
 * has to be created before the next usage.
 *
 * @param[in] filter The handle to media audio filter
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_audio_filter_create()
 *
 */

int media_audio_filter_destroy(media_audio_filter_h filter);


/**
 * @brief Set the media audio filter's offset and count.
 * @details This function set the @a offset and @a count for the given filter used to limit number of items returned.
 *  For example, if you set the @a offset as 10 and @a count as 5, then only searched data from 10 to 14 will be returned when the filter is used with foreach functions. 
 *
 * @param[in] filter The handle to media audio filter
 * @param[in] offset The start position of the given filter (Starting from zero).
 * @param[in] count The number of items to be searched with respect to offset.
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_audio_filter_create()
 * @see media_audio_filter_destroy() 
 */
int media_audio_filter_set_offset(media_audio_filter_h filter, int offset, int count);


/**
 * @brief Set the @a search @a keyword and @a search @a type for given @a filter.
 *
 * @param[in] filter The handle to media audio filter
 * @param[in] search_keyword The keyword which user want to search
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_audio_filter_create()
 * @see media_audio_filter_destroy() 
 */
int media_audio_filter_set_search_keyword(media_audio_filter_h filter,media_audio_search_type_e search_type,const char *search_keyword);


/**
 * @brief Set the media audio filter's content order either descending or ascending.
 *
 * @param[in] filter The handle to media audio filter
 * @param[in] order The search order type
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_audio_filter_create()
 * @see media_audio_filter_destroy() 
 */
int media_audio_filter_set_order(media_audio_filter_h filter, media_content_order_e order);




/**
 * @brief Gets the @a offset and @a count for the given @a filter used to limit number of items returned.
 *
 * @param[in] filter The handle to media audio filter
 * @param[out] offset The start position of the given filter (Starting from zero).
 * @param[out] count The number of items to be searched with respect to offset.
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_audio_filter_create()
 * @see media_audio_filter_destroy()  
 */
int media_audio_filter_get_offset(media_audio_filter_h filter, int* offset, int* count);


/**
 * @brief Gets the @a search @a keyword and @a search @a type for given @a filter.
 *
 * @remarks search_keyword must be released with free() by you. 
 * @param[in] filter The handle to media audio filter
 * @param[out] search_type The type of search
 * @param[out] search_keyword  The keyword which user want to search
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_audio_filter_create()
 * @see media_audio_filter_destroy()  
 */
int media_audio_filter_get_search_keyword(media_audio_filter_h filter,media_audio_search_type_e* search_type,char **search_keyword);


/**
 * @brief Gets the media audio filter's content order.
 * @details This function gets the @a order for given @a filter.
 *
 * @param[in] filter The handle to media audio filter
 * @param[out] order The search order type
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_audio_filter_create()
 * @see media_audio_filter_destroy()  
 */
int media_audio_filter_get_order(media_audio_filter_h filter, media_content_order_e* order);


/**
 * @}
 */



/**
 * @addtogroup CAPI_CONTENT_MEDIA_FILTER_TAG_MODULE
 * @{
 */


/**
 * @brief Creates a media tag filter handle.
 * @details This function creates a #media_tag_filter_h filter handle. The handle can be
 * used to get filtered information based on filter properties i.e. offset, count, search keyword
 * and order.
 *
 * @param[out] filter A handle to media tag filter
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @see media_tag_filter_destroy(),
 *
 */
int media_tag_filter_create(media_tag_filter_h* filter);

/**
 * @brief Destroys a media tag filter handle.
 * @details The function frees all resources related to the tag filter handle. The filter
 * handle no longer can be used to perform any operation. A new filter handle
 * has to be created before the next usage.
 *
 * @param[in]  The handle to media tag filter
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_tag_filter_create()
 *
 */

int media_tag_filter_destroy(media_tag_filter_h filter);

/**
 * @brief Set the media tag filter's offset and count.
 * @details This function set the @a offset and @a count for the given filter used to limit number of items returned.
 *  For example, if you set the @a offset as 10 and @a count as 5, then only searched data from 10 to 14 will be returned when the filter is used with foreach functions. 
 *
 *
 * @param[in] filter  The handle to media tag filter
 * @param[in] offset The start position of the given filter(Starting from zero).
 * @param[in] count The number of items to be searched with respect to offset.
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_tag_filter_create()
 * @see media_tag_filter_destroy() 
 */
int media_tag_filter_set_offset(media_tag_filter_h filter, int offset, int count);


/**
 * @brief Set the @a search @a keyword and @a search @a type for given @a filter.
 *
 * @param[in] filter  The handle to media tag filter
 * @param[in] search_type The type which user want to search. 
 * @param[in] search_keyword The keyword which user want to search.
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_tag_filter_create()
 * @see media_tag_filter_destroy() 
 */
int media_tag_filter_set_search_keyword(media_tag_filter_h filter,media_tag_search_type_e search_type,const char *search_keyword);


/**
 * @brief Set the media tag filter's content order either descending or ascending.
 *
 * @param[in] filter  The handle to media tag filter
 * @param[in] order The search order type
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_tag_filter_create()
 * @see media_tag_filter_destroy() 
 */
int media_tag_filter_set_order(media_tag_filter_h filter, media_content_order_e order);



/**
 * @brief Gets the @a offset and @a count for the given @a filter used to limit number of items returned.
 *
 * @param[in] filter The handle to media tag filter
 * @param[out] offset The start position of the given filter(Starting from zero).
 * @param[out] count The number of items to be searched with respect to offset.
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_tag_filter_create()
 * @see media_tag_filter_destroy() 
 */
int media_tag_filter_get_offset(media_tag_filter_h filter, int* offset, int* count);


/**
 * @brief Gets the @a search @a keyword and @a search @a type for given @a filter.
 *
 * @remarks search_keyword must be released with free() by you.
 * @param[in] filter  The handle to media tag filter
 * @param[out] search_type The type of search
 * @param[out] search_keyword  The keyword which user want to search
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_tag_filter_create()
 * @see media_tag_filter_destroy() 
 */
int media_tag_filter_get_search_keyword(media_tag_filter_h filter, media_tag_search_type_e *search_type,char **search_keyword);


/**
 * @brief Gets the media tag filter's content order.
 * @details This function gets the @a order for given @a filter.
 *
 * @param[in] filter  The handle to media tag filter
 * @param[out] order The search order type
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see media_tag_filter_create()
 * @see media_tag_filter_destroy() 
 */
int media_tag_filter_get_order(media_tag_filter_h filter, media_content_order_e* order);

/**
 * @}
 */
 


/**
 * @addtogroup CAPI_CONTENT_MEDIA_FILTER_BOOKMARK_MODULE
 * @{
 */
 


/**
 * @brief Creates a video bookmark filter handle.
 * @details This function creates a #video_bookmark_filter_h filter handle. The handle can be
 * used to get filtered information based on filter properties i.e. offset, count and order.
 *
 * @param[out] filter A handle to video bookmark filter
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval #MEDIA_CONTENT_ERROR_OUT_OF_MEMORY Out of memory
 * @see video_bookmark_filter_destroy(),
 *
 */
int video_bookmark_filter_create(video_bookmark_filter_h* filter);

/**
 * @brief Destroys a video bookmark filter handle.
 * @details The function frees all resources related to the bookmark filter handle. The filter
 * handle no longer can be used to perform any operation. A new filter handle
 * has to be created before the next usage.
 *
 * @param[in] filter The handle to video bookmark filter
 * @return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see video_bookmark_filter_create()
 *
 */

int video_bookmark_filter_destroy(video_bookmark_filter_h filter);

/**
 * @brief Set the video bookmark filter's offset.
 * @details This function set the offset and count for the given bookmark filter used to limit number of items returned.
 *
 * @param[in] filter The handle to video bookmark filter
 * @param[in] offset The start position of the given filter (Starting from zero).
 * @param[in] count The number of items to be searched with respect to offset.
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see video_bookmark_filter_create()
 * @see video_bookmark_filter_destroy() 
 */
int video_bookmark_filter_set_offset(video_bookmark_filter_h filter, int offset, int count);


/**
 * @brief Set the video bookmark filter's content order either descending or ascending.
 *
 * @param[in] filter The handle to video bookmark filter
 * @param[in] order The search order type
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see video_bookmark_filter_create()
 * @see video_bookmark_filter_destroy() 
 */
int video_bookmark_filter_set_order(video_bookmark_filter_h filter, media_content_order_e order);


/**
 * @brief Gets the @a offset and @a count for the given @a filter used to limit number of items returned.
 *
 * @param[in] filter  The handle to video bookmark filter
 * @param[out] offset The start position of the given filter (Starting from zero).
 * @param[out] count The number of items to be searched with respect to offset.
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see video_bookmark_filter_create()
 * @see video_bookmark_filter_destroy() 
 */
int video_bookmark_filter_get_offset(video_bookmark_filter_h filter, int* offset, int* count);


/**
 * @brief Gets the video bookmark filter's content order.
 * @details This function gets the @a order for given @a filter.
 *
 * @param[in] filter  The handle to video bookmark filter
 * @param[out] order The search order type
 * @return return 0 on success, otherwise a negative error value.
 * @retval #MEDIA_CONTENT_ERROR_NONE Successful
 * @retval #MEDIA_CONTENT_ERROR_INVALID_PARAMETER Invalid parameter
 * @see video_bookmark_filter_create()
 * @see video_bookmark_filter_destroy()
 */
int video_bookmark_filter_get_order(video_bookmark_filter_h filter, media_content_order_e* order);

/**
 * @}
 */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TIZEN_MEDIA_FILTER_H__ */


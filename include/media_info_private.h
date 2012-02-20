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


#ifndef __TIZEN_MEDIA_INFO_PRIVATE_H__
#define __TIZEN_MEDIA_INFO_PRIVATE_H__


#include <media_content_type.h>
#include <string.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <stdio.h>
#include <media-svc.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define MEDIA_CONTENT_TYPE 5

#define MEDIA_CONTENT_PATH_PHONE 	"/opt/media" 	/**< File path prefix of files stored in phone */
#define MEDIA_CONTENT_PATH_MMC 		"/mnt/mmc"		/**< File path prefix of files stored in mmc card */

#define MAX_QUERY_SIZE 4096
#define MIN_QUERY_SIZE 256
#define DEFAULT_QUERY_SIZE 1024
#define MAX_KEYWORD_SIZE 2048



typedef struct
{
	media_content_type_e media_type;		// image, audio, video, all
	int offset;			// position of start
	int count;			// offset
	media_info_search_type_e search_type;
	char* keyword;		// search condition  like a sql "like"
	media_content_order_e order;		//The sort order

}media_info_filter_s;


typedef struct
{
	int offset;			// position of start
	int count;			// offset
	media_folder_search_type_e search_type;
	char* keyword;		// search condition  like a sql "like"
	media_content_order_e order;		//The sort order	

}media_folder_filter_s;


typedef struct
{
	int offset;			// position of start
	int count;			// offset
	media_tag_search_type_e search_type;
	char* keyword;		// search condition  like a sql "like"
	media_content_order_e order;		//The sort order		

}media_tag_filter_s;


typedef struct
{
	int offset;			// position of start
	int count;			// offset
	media_audio_search_type_e search_type;
	char* keyword;		// search condition  like a sql "like"
	media_content_order_e order;		//The sort order		

}media_audio_filter_s;

typedef struct
{
	int offset;			// position of start
	int count;			// offset
	media_content_order_e order;		//The sort order		

}video_bookmark_filter_s;


typedef struct
{
	char* folder_uid;				//image id , audio id, video id
	char* path;
	char* name;
	time_t date_modified;
	media_content_storage_e storage_type;
}media_folder_s;

typedef struct
{
	char* item_id;				//image id , audio id, video id
	char* file_path;
	char* display_name;
	char* thumbnail;
	time_t date_modified;
	int favorite;
	media_content_type_e media_type;
}media_info_s;


typedef struct
{
	int tag_id;
	//int content_id;  //replace to glist of item_h
	char* name;
	
}media_tag_s;


typedef struct 
{
	char* image_id;
	int longitude;
	int latitude;
	char* thumbnail;
	char* description;
	int width;
	int height;
	int favorite;
	media_content_orientation_e orientation;
	time_t date_taken;
}image_meta_s;


typedef struct 
{
	char* video_id;
	int longitude;
	int latitude;
	char* album;
	char* artist;
	char* title;
	char* description;
	char* thumbnail;
	int time_played;
	int duration;
	int width;
	int height;
	int favorite;	
	media_content_orientation_e orientation;
	time_t date_taken;
}video_meta_s;


typedef struct 
{
	int bookmark_id;
	char* video_id;
	time_t time_marked;
	char* thumbnail;
	
}video_bookmark_s;


typedef struct 
{
	char* audio_id;
	char* genre;
	char* author;
	char* album;
	char* artist;
	char* year;
	char* copyright;
	char* description;
	char* format;
	int bitrate;
	int track_num;
	int duration;
	int rating;
	int count_played;
	int time_played;
	time_t time_added;
	int size;
	int category;
	
}audio_meta_s;

typedef struct
{
	int playlist_id;		//playlist id
	char* name;			// playlist name
	
}audio_playlist_s;


typedef struct
{
	char* name;
}audio_artist_s;

typedef struct
{
	char* name;
}audio_genre_s;


typedef struct
{
	char* name;
}audio_author_s;

typedef struct
{
	char* name;
}audio_album_s;





#define CONDITION_TYPE_IMAGE "content_type=1"
#define CONDITION_TYPE_VIDEO "content_type=2"
#define CONDITION_TYPE_AUDIO "content_type=3"
#define QUERY_KEYWORD_AND "and"
#define QUERY_KEYWORD_OR "or"
#define QUERY_KEYWORD_ORDER_BY "order by"
#define QUERY_KEYWORD_LIMIT "limit"
#define QUERY_KEYWORD_DESC "desc"
#define QUERY_KEYWORD_SPACE " "
#define DB_FIELD_FOLDER_UID "folder_uuid"
#define DB_FILED_DISPLAY_NAME "display_name"
#define DB_FILED_DATE_MODIFIED "date_modified"
#define DB_FILED_MODIFIED_DATE "modified_date"
#define DB_FILED_NAME "name"
#define DB_FIELD_THUMBNAIL_PATH "thumbnail_path"
#define DB_FIELD_MARKED_TIME "marked_time"
#define DB_FIELD_TAG_NAME "tag_name"
#define DB_FIELD_ID "_id"
#define DB_FIELD_ADDED_TIME "added_time"

#define SELECT_MEDIA_ITEM "select item_id, file_path, display_name, thumbnail, date_modified,content_type, favourite from item_view where 1"
#define SELECT_ALL_FOLDER "select folder_uuid, path, name, storage_type,modified_date from (select folder_uuid, path, folder_name as name, storage_type,modified_date from visual_folder where valid=1 union select folder_uuid, path, folder_name as name, storage_type,modified_date from audio_folder) where 1"
#define SELECT_COUNT_ITEM "select count(*) from item_view where 1"
#define SELECT_TAG_LIST "select _id, tag_name from visual_tag where 1"
#define SELECT_MEDIA_FROM_TAG "SELECT t._id, tm.visual_uuid, m.display_name as display_name, modified_date  from ( select _id, tag_name from visual_tag WHERE tag_name='%s' ORDER BY tag_name ASC  ) t, ( select visual_uuid, tag_id from visual_tag_map ) tm, ( select visual_uuid, folder_uuid, display_name, modified_date from visual_media) m, ( select folder_uuid, lock_status from visual_folder where valid=1 ) f where tm.tag_id = t._id and m.visual_uuid = tm.visual_uuid and m.folder_uuid = f.folder_uuid and f.lock_status=0 "
#define SELECT_PLAYLIST "select _id,name from audio_playlists where 1"
#define SELECT_MEDIA_FROM_PLAYLIST "select item_id, file_path, display_name, thumbnail, date_modified,content_type, favourite from item_view where 1 and content_type=3 and item_id IN (select audio_uuid from audio_playlists_map where playlist_id=%d)"
#define SELECT_GENRE_LIST "select distinct genre as name from audio_media where valid=1"
#define SELECT_MEDIA_FROM_GENRE "select audio_uuid ,path ,title as display_name,thumbnail_path,modified_date, content_type, favourite,valid,folder_uuid from audio_media where valid=1 and  genre='%s'"
#define SELECT_MEDIA_COUNT_FROM_GENRE "select count(*) from audio_media where valid=1 and genre='%s'"
#define SELECT_ALBUM_LIST "select distinct album as name from audio_media where valid=1 "
#define SELECT_MEDIA_FROM_ALBUM "select audio_uuid ,path ,title as display_name,thumbnail_path,modified_date, content_type, favourite,valid,folder_uuid from audio_media where valid=1 and album='%s'"
#define SELECT_MEDIA_COUNT_FROM_ALBUM "select count(*) from audio_media where valid=1 and album='%s'"
#define SELECT_AUTHOR_LIST "select distinct author as name from audio_media where valid=1 "
#define SELECT_MEDIA_FROM_AUTHOR "select audio_uuid ,path ,title as display_name,thumbnail_path,modified_date, content_type, favourite,valid,folder_uuid from audio_media where valid=1 and  author='%s'"
#define SELECT_MEDIA_COUNT_FROM_AUTHOR "select count(*) from audio_media where valid=1 and author='%s'"
#define SELECT_MEDIA_ARTIST_LIST "select distinct artist as name from audio_media where valid=1"
#define SELECT_MEDIA_FROM_ARTIST "select audio_uuid ,path ,title as display_name,thumbnail_path,modified_date, content_type, favourite,valid,folder_uuid from audio_media where valid=1 and artist='%s'"
#define SELECT_MEDIA_COUNT_FROM_ARTIST "select count(*) from audio_media where valid=1 and artist='%s'"
#define SELECT_BOOKMARK_FROM_VIDEO "select _id,visual_uuid,marked_time,thumbnail_path from video_bookmark where visual_uuid='%s' "


/**
 *@internal
 */
void _content_folder_get_detail(sqlite3_stmt *stmt, media_folder_h folder);

/**
 *@internal
 */
int _content_query_prepare(sqlite3_stmt **stmt, char *select_query,char *condition_query, char *search_query, char *limit_query,char *order );


/**
 *@internal
 */
void _content_item_get_detail(sqlite3_stmt *stmt, media_info_h item);

/**
 *@internal
 */
int _content_error_capi(media_content_type_e type, int cotent_error);

/**
 *@internal
 */
int _content_get_storage_type(const char* full_path);

/**
 *@internal
 */
int _content_get_audio_category(const char* file_full_path,int* category);

/**
 *@internal
 */
int _content_query_sql(char *query_str);

/**
 *@internal
 */
MediaSvcHandle* _content_get_db_handle();


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /*__TIZEN_MEDIA_INFO_PRIVATE_H__*/




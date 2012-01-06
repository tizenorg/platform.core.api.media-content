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


#include <stdio.h>
#include <stdlib.h>
#include <media_content.h>
#include <dlog.h>
#include <pthread.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "TIZEN_N_MEDIACONTENT"


int test_content_connect_database()
{
	int ret;

	LOGI("\n============DB Connection Test============\n\n");

	ret = media_content_connect();

	if(ret == MEDIA_CONTENT_ERROR_NONE)
	{
		LOGI("connection is success\n\n");
	}
	else
		LOGE("connection is failed\n\n");

	return ret;
}

void test_content_disconnect_database()
{

	int ret;
	LOGI("\n============DB Disconnection Test============\n\n");

	ret = media_content_disconnect();

	if(ret == MEDIA_CONTENT_ERROR_NONE)
		LOGI("disconnection is success\n\n");
	else
		LOGE("disconnection is failed\n\n");

}

bool capi_media_list_cb(media_info_h item, void *user_data)
{
	int ret = true; 

	char* file_path = NULL;

	char* name = NULL;
	char* thumbnail_path = NULL;
	time_t date_modified;
	int type;
	
	if(item != NULL)
	{
		if(media_info_get_file_path(item,&file_path) != MEDIA_CONTENT_ERROR_NONE)
		{
			LOGE("[ERROR] media_info_get_file_path is failed\n");
			ret = false;
		}
		
		if(media_info_get_display_name(item,&name) != MEDIA_CONTENT_ERROR_NONE)
		{
			LOGE("[ERROR] media_info_get_display_name is failed\n");
			ret = false;
		}
		if(media_info_get_thumbnail_path(item,&thumbnail_path) != MEDIA_CONTENT_ERROR_NONE)
		{
			LOGE("[ERROR] media_info_get_thumbnail_path is failed\n");
			ret = false;
		}
		if(media_info_get_date_modified(item,&date_modified) != MEDIA_CONTENT_ERROR_NONE)
		{
			LOGE("[ERROR] media_info_get_date_modified is failed\n");
			ret = false;
		}
		if(media_info_get_media_type(item,&type) != MEDIA_CONTENT_ERROR_NONE)
		{
			LOGE("[ERROR] media_info_get_content_type is failed\n");
			ret = false;
		}		
		LOGI("[%d] name : %s , file path : %s , date : %s , thumbnail path : %s \n"
			,type,name,file_path,ctime(&date_modified),thumbnail_path);




		if(type == MEDIA_CONTENT_TYPE_IMAGE)
		{
			image_meta_h image;

			double lati;
			double longi;
			
			if(media_info_get_image_from_db(item,&image) == MEDIA_CONTENT_ERROR_NONE)
			{
				image_meta_get_latitude(image,&lati);
				image_meta_get_longitude(image,&longi);
				//printf("[image] latitude : %f , longitude : %f \n",lati, longi);				

				image_meta_destroy(image);
			}
			else
				LOGE("[image_error] \n");

		}
		if(type == MEDIA_CONTENT_TYPE_VIDEO)
		{
			video_meta_h video;
			double lati;
			double longi;

			if(media_info_get_video_from_db(item,&video) == MEDIA_CONTENT_ERROR_NONE)
			{
				video_meta_get_latitude(video,&lati);
				video_meta_get_longitude(video,&longi);			
				video_meta_destroy(video);
			}
			else
				LOGE("[video_error] \n");

		}		
		if(type == MEDIA_CONTENT_TYPE_AUDIO)
		{
			audio_meta_h audio;

			if(media_info_get_audio_from_db(item,&audio) == MEDIA_CONTENT_ERROR_NONE)
			{
	
				audio_meta_destroy(audio);
			}
			else
				LOGE("[audio_error] \n");

		}	


		if(file_path != NULL)
			free(file_path);
		if(name != NULL)
			free(name);
		if(thumbnail_path != NULL)
			free(thumbnail_path);
			
	}

	return ret;
}

bool capi_folder_list_cb(media_folder_h folder, void* user_data)
{
	int item_count;
	char* folder_path;
	char* folder_name;
	media_content_storage_e storage_type;
	bool ret;
	media_folder_h* _folder = (media_folder_h*)user_data;
	
	if(folder != NULL)
	{
		media_folder_clone(_folder,folder);
		
		if(media_folder_get_path(folder,&folder_path) != MEDIA_CONTENT_ERROR_NONE)
		{
			LOGE("[ERROR] media_folder_get_path is failed\n");
			ret = false;
		}		
		if(media_folder_get_name(folder,&folder_name) != MEDIA_CONTENT_ERROR_NONE)
		{
			LOGE("[ERROR] media_folder_get_name is failed\n");
			ret = false;
		}		
		if(media_folder_get_storage_type(folder,&storage_type) != MEDIA_CONTENT_ERROR_NONE)
		{
			LOGE("[ERROR] media_folder_get_storage_type is failed\n");
			ret = false;
		}	
		if(media_folder_get_media_count_from_db(folder,MEDIA_CONTENT_TYPE_IMAGE|MEDIA_CONTENT_TYPE_VIDEO|MEDIA_CONTENT_TYPE_AUDIO,&item_count) != MEDIA_CONTENT_ERROR_NONE)
		{
			LOGE("[ERROR] media_folder_get_media_count_from_db is failed\n");
			ret = false;
		}			
		LOGI("[name : %s] media count : %d , storage type : %d, path : %s \n",
			folder_name,item_count,storage_type,folder_path);

		if(folder_path != NULL)
		{
			free(folder_path);
		}
		if(folder_name != NULL)
		{
			free(folder_name);
		}

		//media_folder_destroy(_folder);
		ret = true;
	}
	else
	{
		ret = false;
	}

	return ret;
}


bool capi_audio_list_cb(audio_album_h album,void* user_data)
{
	int ret;
	char* name = NULL;
	
	if(album != NULL)
	{
		if(audio_album_get_name(album,&name) != MEDIA_CONTENT_ERROR_NONE)
		{
			LOGE("[ERROR] audio_album_get_name is failed\n");
			ret = false;
		}	

		if(name != NULL)
		{
			LOGE("album is found : %s \n",name);
			free(name);
		}

				
	}
	else
		ret = false;

	return ret;
}
	


void test_folder_foreach_from_db()
{
	int ret;
	media_folder_h folder;


	//test.1 set the filter
	media_folder_filter_h filter;		// handle of filter
	
	if(media_folder_filter_create(&filter) != MEDIA_CONTENT_ERROR_NONE)
	{
		LOGE("[ERROR] media_folder_filter_create is failed\n");
		return ;
	}
	//test.2 get the folder
	ret = media_folder_foreach_folder_from_db(filter, capi_folder_list_cb,&folder);

	//test.3 get the media list in first folder
	media_info_filter_h m_filter = NULL;
	if(media_info_filter_create(&m_filter) != MEDIA_CONTENT_ERROR_NONE)
	{
		LOGE("[ERROR] media_info_filter_create is failed\n");
		return ;
		
	}
	media_info_filter_set_media_type(m_filter,MEDIA_CONTENT_TYPE_IMAGE);
	media_info_filter_set_offset(m_filter,1,5);
	media_info_filter_set_search_keyword(m_filter,MEDIA_INFO_SEARCH_BY_DISPLAY_NAME,"ph");
	media_info_filter_set_order(m_filter,MEDIA_CONTENT_SORT_BY_NAME_DESC);

	ret = media_folder_foreach_media_from_db(folder,m_filter, capi_media_list_cb,NULL);

	if(ret != MEDIA_CONTENT_ERROR_NONE)
	{
		LOGE("[ERROR] media_folder_foreach_media_from_db is failed, error code : %d\n",ret);
	}

	media_folder_filter_destroy(filter);
	media_info_filter_destroy(m_filter);
	
}


void test_media_info_foreach_from_db()
{
	int ret;
	LOGI("\n============Content get Media Test============\n\n");

	//test4-1. get all items
	media_info_filter_h filter;

	
	media_info_filter_create(&filter);

	ret = media_info_foreach_media_from_db(filter, capi_media_list_cb,NULL);

	if(ret == MEDIA_CONTENT_ERROR_NONE)
		LOGI("media_info_foreach_media_from_db is success\n\n");
	else
		LOGE("media_info_foreach_media_from_db is failed\n\n");
	
	
	media_info_filter_destroy(filter);
}


void test_audio_album_foreach_from_db()
{
	int ret;
	media_audio_filter_h filter = NULL;
	
	media_audio_filter_create(&filter);

	ret = audio_album_foreach_album_from_db(filter,capi_audio_list_cb,NULL);

	if(ret == MEDIA_CONTENT_ERROR_NONE)
		LOGI("audio_album_foreach_album_from_db is success\n\n");
	else
		LOGE("audio_album_foreach_album_from_db is failed\n\n");	


	if(filter != NULL)
		media_audio_filter_destroy(filter);
	
	
}


bool capi_find_media_cb(media_info_h item,void* user_data)
{
	media_info_h* _item = (media_info_h*)user_data;
	if(item != NULL)
	{
		char* name = NULL;
		media_info_get_display_name(item,&name);

		LOGI("[media]display name : %s \n",name);

		if(name != NULL)
			free(name);
		media_info_clone(_item,item);
	}
	return false;
}

bool capi_taginfo_cb(media_tag_h tag, void* user_data)
{
	char* tag_name;
	media_tag_h* _tag = (media_tag_h*)user_data;
	if(tag != NULL)
	{
		media_tag_get_name(tag,&tag_name);
		LOGI("[tag name] : %s \n",tag_name);
		media_tag_clone(_tag,tag);

		if(tag_name != NULL)
			free(tag_name);
	}
	return false;
}


void test_tag_operation()
{

	//test . insert tag information
	//condition : item is needed to insert the tag, tag is not support for audio
	media_tag_h tag = NULL;
	media_info_h item = NULL;
	media_info_filter_h media_filter = NULL;
	media_info_filter_create(&media_filter);

	//find the item which display_name is "1_photo.jpg"
	media_info_foreach_media_from_db(media_filter,capi_find_media_cb,(void *)&item);
	if(media_filter != NULL)
		media_info_filter_destroy(media_filter);

	if(item != NULL)
	{
		//insert tag 
		media_tag_insert_to_db("test_tag",&tag);
		


		//add the media to tag.
		media_tag_add_media_to_db(tag,item);
		

		//delete the tag
		if(tag != NULL)
		{	
			media_tag_delete_from_db(tag);
			media_tag_destroy(tag);

		}

		media_info_destroy(item);
	}
		
	
}



bool capi_get_video_cb(media_info_h item, void* user_data)
{
	video_meta_h* _video = (video_meta_h*)user_data;
	char* name = NULL;
	if(item != NULL)
	{
		media_info_get_display_name(item,&name);
		LOGI(" video name : %s \n" , 	name);
		
		media_info_get_video_from_db(item,_video);
	

		if(name != NULL)
			free(name);

	}
	return false;
}

bool capi_get_bookmarks_cb(video_bookmark_h bookmark,void* user_data)
{
	//get the first bookmark.
	// it is needed array of bookmark, if user wan to get list of bookmarks.
	video_bookmark_h* _bookmark = (video_bookmark_h*)user_data;
	if(bookmark != NULL)
	{	
		char* name = NULL;
		video_bookmark_get_thumbnail_path(bookmark,&name);
		
		video_bookmark_clone(_bookmark,bookmark);

		if(name != NULL)
		{
			LOGI("deleted the bookmark path : %s \n",name);

			free(name);
		}
	}
	return false;	
}

void test_video_bookmark_operation()
{
	//bookmark is only supported for video information.
	video_meta_h video = NULL;
	media_info_filter_h media_filter = NULL;

	
	media_info_filter_create(&media_filter);
	media_info_filter_set_media_type(media_filter,MEDIA_CONTENT_TYPE_VIDEO);

	//get the media_info which is returned first , and get the video's instance from media_info.
	media_info_foreach_media_from_db(media_filter,capi_get_video_cb,(void *)&video);	

	media_info_filter_destroy(media_filter);
	

	if(video != NULL)
	{	

		video_bookmark_h bookmark = NULL;
		
		//insert bookmark to video 
		char* thumbnail_path1 = "/opt/media/Images and videos/My video clips/teat11.jpg";
		video_bookmark_insert_to_db(video, 200,thumbnail_path1);

		//get the bookmark
		video_bookmark_filter_h bookmark_filter = NULL;
		video_bookmark_filter_create(&bookmark_filter);
	
		video_bookmark_foreach_bookmark_from_db(video,bookmark_filter,capi_get_bookmarks_cb,(void*)&bookmark);

		video_bookmark_filter_destroy(bookmark_filter);
		
		if(bookmark != NULL)
		{
			video_bookmark_delete_from_db(bookmark);
		}

		video_bookmark_destroy(bookmark);



	}

	video_meta_destroy(video);

}


#include <time.h>
#include <memory.h>
void test_insert_item(int count)
{
	int i =0,ret;
	char img_path[1024];

	clock_t start, end;

	start = clock();
	for(i =0 ; i< count; i++)
	{	
		memset(img_path, 0x00, sizeof(img_path));
		snprintf(img_path,sizeof(img_path),"%s%d.jpg","/opt/media/Images and videos/My photo clips/a",i+0);

		ret = media_info_insert_to_db(MEDIA_CONTENT_TYPE_IMAGE,img_path);
		if(ret != MEDIA_CONTENT_ERROR_NONE)
		{
			LOGE(" image insert error \n");
		}
	}
	end = clock();
	LOGI(" time : %f \n",(double)(end-start)/CLOCKS_PER_SEC);

	
}

void test_filter_operation()
{
	int ret;
	int media_type;
	int offset;
	int count;
	char *keyword= NULL;
	media_info_search_type_e search_type;
	
	
	media_info_filter_h filter;
	media_info_filter_create(&filter);

	media_info_filter_get_offset( filter,&offset,&count);
	media_info_filter_get_media_type( filter, &media_type);
	media_info_filter_get_search_keyword( filter,&search_type,&keyword);
	
	LOGI("1. media : %d , offset : %d / %d , search : %d / %s \n",media_type, offset,count,search_type,keyword);

	ret = media_info_filter_set_search_keyword(filter,MEDIA_INFO_SEARCH_BY_DISPLAY_NAME,"test");
	media_info_filter_get_search_keyword( filter,&search_type,&keyword);	
	LOGI("2. media : %d , offset : %d / %d , search : %d / %s ret : %d\n",media_type, offset,count,search_type,keyword, ret);

	ret = media_info_filter_set_search_keyword(filter,MEDIA_INFO_SEARCH_NONE,NULL);
	media_info_filter_get_search_keyword( filter,&search_type,&keyword);
	LOGI("3. media : %d , offset : %d / %d , search : %d /%s ret : %d\n",media_type, offset,count,search_type,keyword, ret);
	
}

bool capi_audio_playlist_cb(audio_playlist_h playlist, void *user_data)
{
	char* playlist_name = NULL;
	if(playlist != NULL)
	{
		audio_playlist_get_name(playlist,&playlist_name);

		if(playlist_name != NULL)
		{
			LOGI(" Playlist Name : %s \n", playlist_name);
			free(playlist_name);
		}
		
	}
	return true;
}

bool capi_audio_info_cb(media_info_h media,void* user_data)
{

	media_info_h* add_media = (media_info_h*)user_data;
	if(media != NULL)
	{
		media_info_clone(add_media,media);
	}
	
	return false;
}

bool capi_media_info_in_playlist_cb(media_info_h media,void* user_data)
{

	char* media_name = NULL;

	if(media != NULL)
	{
		media_info_get_display_name(media,&media_name);

		if(media_name != NULL)
		{
			LOGI("[Playlist] Media Name : %s \n",media_name);
			free(media_name);
		}
	}
	return true;
}

void test_playlist_operation()
{
	//1. insert the playlist
	audio_playlist_h playlist;
	char *playlist_name = "myPlaylist";
	int ret = audio_playlist_insert_to_db(playlist_name, &playlist);

	if(ret != MEDIA_CONTENT_ERROR_NONE)
	{
		LOGE("[ERROR] Insert operation is failed\n");
	}

	//2. get the playlist using foreach function.
	//   if filter is NULL, all item will be retrieved.
	audio_playlist_foreach_playlist_from_db(NULL,capi_audio_playlist_cb,NULL);


	//3. add the audio to playlist
	media_info_h audio_info = NULL;
	media_info_filter_h media_filter;
	media_info_filter_create(&media_filter);
	media_info_filter_set_media_type(media_filter,MEDIA_CONTENT_TYPE_AUDIO);
	media_info_foreach_media_from_db(media_filter,capi_audio_info_cb,&audio_info);

	ret = audio_playlist_add_media_to_db(playlist,audio_info);

	media_info_destroy(audio_info);

	//4. get the media from playlist
	audio_playlist_foreach_media_from_db(playlist,NULL,capi_media_info_in_playlist_cb,NULL);
	
	//5. deletes the playlist
	ret = audio_playlist_delete_from_db(playlist);

	if(ret != MEDIA_CONTENT_ERROR_NONE)
	{
		LOGE("[ERROR] Delete operation is failed\n");
	}
	
}

int main(int argc, char *argv[])
{

	LOGI("--- content manager test start ---\n\n");

	//scenario 1. DB connection
	if(test_content_connect_database() != MEDIA_CONTENT_ERROR_NONE)
		return MEDIA_CONTENT_ERROR_NONE;
	
	
	//scenario 2-1  .1 set the filter
	//	         .2 gets the folders
	test_folder_foreach_from_db();
	
	//test_insert_item(1000);
	//scenario 2-2.  gets the media
	test_media_info_foreach_from_db();
	
	//scenario 2-3. searching the data by filter.
	test_audio_album_foreach_from_db();

	//scenario 3. operation of tag information
	//	1. insert the tag
	//	2. get the tag list
	// 	3. delete the tag
	test_tag_operation();
	

	//scenario 4. the operation of bookmark 
	//	1. insert the bookmark
	//	2. get the bookmark list
	// 	3. delete the bookmark	
	test_video_bookmark_operation();

	//scenario 5. the operation of playlist  
	test_playlist_operation();
		

	//scenario 6. DB disconnection
	test_content_disconnect_database();	
	return 0;
	
}




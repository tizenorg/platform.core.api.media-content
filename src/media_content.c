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



#include <media_content.h>
#include <media_info_private.h>
#include <audio-svc.h>
#include <audio-svc-error.h>
#include <audio-svc-types.h>
#include <visual-svc-types.h>
#include <visual-svc.h>


#include <dlog.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "TIZEN_N_MEDIACONTENT"

static MediaSvcHandle* db_handle = NULL;
static int ref_count = 0;

int media_content_connect()
{
	int ret = MEDIA_CONTENT_ERROR_NONE;

	if(ref_count == 0)
	{
		if(db_handle == NULL)
	{
			ret = media_svc_connect(&db_handle);
	}

		ret = _content_error_capi(MEDIA_CONTENT_TYPE,ret);
	}

	ref_count++;
	
	return ret;
}


int media_content_disconnect()
{
	int ret = MEDIA_CONTENT_ERROR_NONE;
	
	if(ref_count > 0)
	{
		ref_count--;
	}
	else
	{
		LOGE("[%s]DB_FAILED(0x%08x) database is not connected", __FUNCTION__, MEDIA_CONTENT_ERROR_DB_FAILED);
		return MEDIA_CONTENT_ERROR_DB_FAILED;
	}

	if(ref_count == 0)
	{
	if(db_handle != NULL)
	{
			ret = media_svc_disconnect(db_handle);
			ret =  _content_error_capi(MEDIA_CONTENT_TYPE,ret);
		if( ret == MEDIA_CONTENT_ERROR_NONE)
		{		
			db_handle = NULL;
		}
	}
	
	}
	
	return ret;
}

MediaSvcHandle* _content_get_db_handle()
{
	return db_handle;
}


int _content_query_prepare(sqlite3_stmt** stmt,char* select_query,char* condition_query, char* search_query,char* limit_query,char* order)
{
	char* query = NULL;
	int len_query;
	
	if(db_handle == NULL)
	{
		LOGE("[%s]DB_FAILED(0x%08x) database is not connected", __FUNCTION__, MEDIA_CONTENT_ERROR_DB_FAILED);
		return MEDIA_CONTENT_ERROR_DB_FAILED;	
	}
	
	if((select_query != NULL) && (select_query[0] != 0x00))
	{
		if((search_query == NULL) || search_query[0] == 0x00)
		{
			search_query = " ";
		}
		if((limit_query == NULL) || limit_query[0] == 0x00)
		{
			limit_query = " ";
		}		
		if((order == NULL) || order[0] == 0x00)
		{
			order = " ";
		}
		if((condition_query == NULL) ||condition_query[0] == 0x00)
		{
			condition_query = " ";
		}

		len_query= strlen(select_query) + 1 + strlen(search_query)+ 1 + strlen(condition_query)+ 1 + strlen(limit_query)+ 1 + strlen(order)+1;

		query = (char*)calloc(len_query,sizeof(char));

		if(query == NULL)
		{
			LOGE("[%s]OUT_OF_MEMORY(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_OUT_OF_MEMORY);
			return MEDIA_CONTENT_ERROR_OUT_OF_MEMORY;
		}
		
		snprintf(query,len_query,"%s %s %s %s %s",select_query,condition_query,search_query,order,limit_query );

		LOGV("[%s]Query : %s",__func__,query); 
		if( sqlite3_prepare((sqlite3*)db_handle, query, strlen(query),stmt, NULL) != SQLITE_OK )
		{
			LOGE("[%s]DB_FAILED(0x%08x) fail to sqlite3_prepare(), %s", __FUNCTION__, MEDIA_CONTENT_ERROR_DB_FAILED,sqlite3_errmsg((sqlite3*)db_handle));
			exit(1);
		}	
		free(query);
	}
	else
	{
		LOGE("[%s]INVALID_PARAMETER(0x%08x)", __FUNCTION__, MEDIA_CONTENT_ERROR_INVALID_PARAMETER);
		return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
	}
	return MEDIA_CONTENT_ERROR_NONE;

}



int _content_error_capi(media_content_type_e type, int content_error)
{
	if(type == MEDIA_CONTENT_TYPE)
	{
		if(content_error == MB_SVC_ERROR_NONE)
			return MEDIA_CONTENT_ERROR_NONE;
		else if(content_error == MB_SVC_ERROR_INVALID_PARAMETER || content_error == AUDIO_SVC_ERROR_INVALID_PARAMETER)
			return MEDIA_CONTENT_ERROR_INVALID_PARAMETER;
		else if(content_error == MB_SVC_ERROR_DB_INTERNAL || content_error == AUDIO_SVC_ERROR_DB_INTERNAL)
			return MEDIA_CONTENT_ERROR_DB_FAILED;
		else if(content_error == MEDIA_INFO_ERROR_DATABASE_CONNECT || content_error == AUDIO_SVC_ERROR_DB_CONNECT)
			return MEDIA_CONTENT_ERROR_DB_FAILED;
		else if(content_error == MEDIA_INFO_ERROR_DATABASE_DISCONNECT)
			return MEDIA_CONTENT_ERROR_DB_FAILED;				
			
	}
	return MEDIA_CONTENT_ERROR_NONE;
	
}


int _content_query_sql(char *query_str)
{
	int err = MEDIA_CONTENT_ERROR_NONE;
	char *err_msg;

	if(db_handle == NULL)
	{
		LOGE("[%s]DB_FAILED(0x%08x) database is not connected",__FUNCTION__, MEDIA_CONTENT_ERROR_DB_FAILED);
		return MEDIA_CONTENT_ERROR_DB_FAILED;	
	}


	err = sqlite3_exec(db_handle, query_str, NULL, NULL, &err_msg);
	if (SQLITE_OK != err) 
	{
		if (err_msg) 
		{
			sqlite3_free(err_msg);
		}
		LOGE("[%s]DB_FAILED(0x%08x) database operation is failed",__FUNCTION__, MEDIA_CONTENT_ERROR_DB_FAILED);
		return MEDIA_CONTENT_ERROR_DB_FAILED;
	}

	if (err_msg)
		sqlite3_free(err_msg);
	
	return err;
}



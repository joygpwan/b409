#include"global.h"
#include"utility.h"
#include"list_head.h"
#include"name_buf.h"
#include"nss_api.h"
#define _XML
#ifdef _XML
#include<libxml/parser.h>
#include<libxml/tree.h>
static char * buf = "test";
int list_all_buckets_and_objects(user_dir_t * user,char * xml_file)
{
	struct list_head * l,*x;
	bucket_t * bucket;
	object_t * object;
	xmlDocPtr doc = NULL;
	xmlNodePtr root_node = NULL,bnode;
	doc = xmlNewDoc(BAD_CAST "1.0");
	root_node = xmlNewNode(NULL,BAD_CAST *(user->user_name));
	xmlDocSetRootElement(doc,root_node);
	if(list_empty(&user->buckets)){
		goto ret;
	}
	for_each_bucket(l,user){
		bucket = container_of(l,bucket_t,b_list);
		bnode = xmlNewChild(root_node,NULL,BAD_CAST *(bucket->bucket_name),BAD_CAST buf);
		if(list_empty(&bucket->objects)){
			continue;
		}
		for_each_object(x,bucket){
			object = container_of(x,object_t,o_list);
			xmlNewChild(bnode,NULL,BAD_CAST *(object->object_name),BAD_CAST buf);
		}
	}
ret:
	xmlSaveFormatFileEnc(xml_file,doc,"UTF-8",1);
//	xmlSaveFormatFileEnc("-",doc,"UTF-8",1);
	xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlMemoryDump();
	return 0;
}
#endif
#define U1	"u1"
#define U2	"u2"
#define U3	"u3"
#define U4	"u4"
#define U5	"u5"
#define U6	"u6"
#define U7	"u7"
#define U8	"u8"
#define U9	"u9"
#define U10	"u10"
#define U11	"u11"
#define U12	"u12"
#define B1	"b1"
#define B2	"b2"
#define B3	"b3"
#define B4	"b4"
#define B5	"b5"
#define B6	"b6"
#define B7	"b7"
#define B8	"b8"
#define O1	"o1"
#define O2	"o2"
#define O3	"o3"
#define O4	"o4"
#define O5	"o5"
#define O6	"o6"
#define O7	"o7"
#define O8	"o8"
#define O9	"o9"
#define O10	"o10"
#define O11	"o11"
#define O12	"o12"
#define O13	"o13"
int main()
{
	int i;
	user_dir_t * u;
	bucket_t * b;
	object_t * o;
	init_name_space();
	put_user(U1);
	put_user(U2);
	put_user(U3);
	put_user(U4);
	put_user(U5);
	put_user(U6);
	put_user(U7);
	put_user(U8);
	put_user(U9);
	put_user(U10);
	put_user(U11);
	put_user(U12);
	prt_ulist();
	prt_uhash();
	printf("----------------------\n");
	put_bucket(B1,U5);
	put_bucket(B2,U5);
	put_bucket(B3,U5);
	put_bucket(B4,U5);
	put_bucket(B5,U5);
	get_user_dir_by_name(U5,(void**)&u,OP_WITH_LOCK);
	prt_blist(u);
	prt_bhash();
	printf("----------------------\n");
	if(put_object(O1,B3,U5) == 0){
		printf("put o1 ok\n");
	}
	if(put_object(O2,B3,U5) == 0){
		printf("put o2 ok\n");
	}
	if(put_object(O3,B3,U5) == 0){
		printf("put o3 ok\n");
	}
	if(put_object(O4,B3,U5) == 0){
		printf("put o4 ok\n");
	}
	if(put_object(O5,B3,U5) == 0){
		printf("put o5 ok\n");
	}
	if(put_object(O6,B3,U5) == 0){
		printf("put o6 ok\n");
	}
	if(put_object(O7,B3,U5) == 0){
		printf("put o7 ok\n");
	}
	get_bucket_by_name(B3,u,(void**)&b,OP_WITH_LOCK);
	prt_olist(b);
	prt_ohash();
	if(list_all_buckets_and_objects(u,"zz.xml") != 0){
		fprintf(stderr,"xml fail!\n");
	}
	return 0;
}

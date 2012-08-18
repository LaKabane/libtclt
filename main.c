#include <stdio.h>
#include "json_parse.h"

/* debug */
static void
show_chain(elements *e)
{
	while (e != NULL && e->type != NOTHING)
	{
		printf("new component :");
		switch (e->type)
		{
		case NULL_ELE:
			printf("null\n");
			break;
		case BOOL:
			printf("boolean : %d\n", e->u_value.boolean);
			break;
		case INT:
			printf("integer : %lld\n", e->u_value.integer);
			break;
		case DOUBLE:
			printf("double : %f\n", e->u_value.floating);
			break;
		case NUMBER:
			printf("number : \"%s\"\n", e->u_value.buf);
			break;
		case STRING:
			printf("string : \"%s\"\n", e->u_value.buf);
			break;
		case MAP_KEY:
			printf("map key : \"%s\"\n", e->u_value.buf);
			break;
		case START_MAP:
			printf("start map\n");
			break;
		case END_MAP:
			printf("end map\n");
			break;
		case START_ARRAY:
			printf("start array\n");
			break;
		case END_ARRAY:
			printf("end array\n");
			break;
		}
		e = e->next;
	}
}

/* debug */
static void
restore_chain(elements *e)
{
	while (e != NULL && e->type != NOTHING)
	{
		switch (e->type)
		{
		case NULL_ELE:
			printf("null");
			break;
		case BOOL:
			printf("%d", e->u_value.boolean);
			break;
		case INT:
			printf("%lld", e->u_value.integer);
			break;
		case DOUBLE:
			printf("%f", e->u_value.floating);
			break;
		case NUMBER:
			printf("\"%s\"", e->u_value.buf);
			break;
		case STRING:
			printf("\"%s\"", e->u_value.buf);
			break;
		case MAP_KEY:
			printf("\"%s\": ", e->u_value.buf);
			break;
		case START_MAP:
			printf("{");
			break;
		case END_MAP:
			printf("}");
			break;
		case START_ARRAY:
			printf("[");
			break;
		case END_ARRAY:
			printf("]");
			break;
		}
		e = e->next;
	}
}

#include <QVariant>
#include <QDebug>
int main()
{
	const char * buf = "[{\"AddContact\": {\"Name\": \"name1\", \"Key\":\"key1\"}}]";
	size_t len = 49;
	//const unsigned char * buf = "[{\"lol\":false},{\"lol2\":false}]";
	//size_t len = 30;
	elements *e;

	printf("len=%d\n", strlen((const char*)buf));
	printf("====start test====\n");
	printf("try with : '%s'\n\n", buf);
	//e = parse(buf, len);
	QVariant *var = getVariant(buf, len);
	if (var == 0)
	{
		printf("faileddddd\n");
		return 1;
	}
	printf("\n\n");
	printf("=====Result==\n");
	//show_chain(e);
	//restore_chain(e);
	qDebug() << *var;
	printf("\n\n");
	printf("====end   test====\n");
	return 0;
}

/* 0[                  start_array */
/* 1	{               start_map */
/* 2	   "lol"        map_key */
/* 3	   0            boolean */
/* 4	}               end_map */
/* 5	{               start_map */
/* 6	   "lol2"       map_key */
/* 7	   0            boolean */
/* 8	}               end_map */
/* 9]                  end_array */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 			500
#define MAX_DATA			250
#define HEX_MARK_BASE 		0
#define HEX_RECLEN_BASE 	1
#define HEX_OFFSET_BASE 	3
#define HEX_RECTYPE_BASE 	7
#define HEX_DATABYTE_BASE	9



int main(int argc,char **argv)
{
	int count;
	int count1;
	int buff;	
	int data_sum;
	int cd_1;
	int cd_2;
	
	FILE *fp;
	
	char str_data[MAX_CHAR];
	char data_type[10];
	char data_length[10];
	char data_offset[10];
	char hex_data_buff[10];
	int data_byte[250];
	
	
	fp = fopen(argv[1],"r");
	if(fp == NULL)
	{
		printf("ERROR \n");
		return 0;
	}
	
		for(count1 = 0;fgets(str_data, MAX_CHAR, fp) != NULL;count1++)
		{
			printf("\n");
			printf("data --> %d\n", count1);
			printf("%s\n",str_data);
			printf("mark ---> %c \n",str_data[0]);
			
			for(count = HEX_RECLEN_BASE; count <= (HEX_RECLEN_BASE + 1); count++)
			{
				data_length[(count - HEX_RECLEN_BASE)] = str_data[count];
			}
			data_sum = strtoul(data_length,NULL,16);
			printf("data length %x \n",data_sum);
			
			for(count = HEX_OFFSET_BASE; count <= (HEX_OFFSET_BASE + 3); count++)
			{
				data_offset[(count - HEX_OFFSET_BASE)] = str_data[count];
			}
			buff = strtoul(data_offset,NULL,16);
			printf("data offset %x \n",buff);
			
			for(count = HEX_RECTYPE_BASE; count <= (HEX_RECTYPE_BASE + 1);count++)
			{
				data_type[count - HEX_RECTYPE_BASE] = str_data[count];
			}
			buff = strtoul(data_type,NULL,16);
			printf("data type %x \n",buff);
			
			/* HEX DATA EXTRACTING */
			for(cd_1 = 0;cd_1 < data_sum;cd_1++)
			{
				for(cd_2 = (HEX_DATABYTE_BASE + (cd_1*2));cd_2 <= ((HEX_DATABYTE_BASE + (cd_1*2)) + 1);cd_2++)
				{
					hex_data_buff[cd_2 - (HEX_DATABYTE_BASE + (cd_1*2))] = str_data[cd_2];
				}
				printf("HEX DATA BYTE %d --> %X \n",cd_1,strtoul(hex_data_buff,NULL,16));
			}
			
			/* CHECKSUM DATA */
			for(cd_1 = (HEX_DATABYTE_BASE + (data_sum*2));cd_1 <= ((HEX_DATABYTE_BASE + (data_sum*2))+1);cd_1++)
			{
				hex_data_buff[cd_1 - (HEX_DATABYTE_BASE + (data_sum*2))] = str_data[cd_1];
			}
			printf("CHECKSUM --> %X \n", strtoul(hex_data_buff,NULL,16));
			
		}
		
	fclose(fp);
	return 0;
}

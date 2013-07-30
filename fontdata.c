#include "stdio.h"
#include "fontdata.h"
#include "stdlib.h"

U8 buffer[50]={0};

U16 get_unicode_pos(U16 code);
U16 get_unicode_offset(U16 code);
U16 get_unicode_realpos(U16 code);
U16 get_unicode_width(U16 code);
void get_unicode_dataoffset(U16 code, U16* start, U16* end);
void get_unicode_data(U16 code,U8* buf);
void writefile(U16 code);
void main()
{
	U16 code=0;
	U16 start=0,end=0;
	U16 width=0;
	U16 i=0,k=0,j=0;
	//U8 buffer1[]={0xfe,0x09,0x98,0xcf,0x00,0x0f,0x30,0x80,0x01,0x0c,0x60,0x00,0x03,0x0c,0xc0,0x00,0x06,0x00,0x00,0x00,0x00,0x00,};
	while(1)
	{
	i=0,k=0,j=0;
	width=0;
	printf("Please input unicode:");
	scanf("%x",&code);
#if 1
	get_unicode_dataoffset(code,&start,&end);
	printf("\n");
	printf("start:0x%x,end=0x%x\n",start,end);

	width = get_unicode_width(code);
	printf("\n");
	printf("width=%d",width);

	get_unicode_data(code,buffer);
	
	printf("\n");
	for(i=0;i<2*width;i++)
	{
		for(j=0;j<8;j++)
		{
			if(buffer[i]&(1<<j))
				printf("*");
			else
				printf("0"); 
			k++;
			if(k%width == 0)
				printf("\n");
		}
		
	}
	printf("\n\r");
#endif
	}


	//writefile(code);
};

U16 get_unicode_pos(U16 code)
{
	U16 i=0;
	#if 0
	while(Bengali_20x20p_v24b_RangeData[i].min!=0xffff)
	{
		if(code >= Bengali_20x20p_v24b_RangeData[i].min && code <= Bengali_20x20p_v24b_RangeData[i].max)
		{
			break;
		}
		i++;
	}
	if(Bengali_20x20p_v24b_RangeData[i].min==0xffff)
		i=0xffff;
	#else
	while(Bengali_16_RangeData[i].min!=0xffff)
	{
		if(code >= Bengali_16_RangeData[i].min && code <= Bengali_16_RangeData[i].max)
		{
			break;
		}
		i++;
	}
	if(Bengali_16_RangeData[i].min==0xffff)
		i=0xffff;
	#endif
	return i;
}

U16 get_unicode_offset(U16 code)
{
	U16 pos=0;
	
	pos = get_unicode_pos(code);
	#if 0
	if(pos!=0xffff)
		return Bengali_20x20p_v24b_RangeOffset[pos];
	else
		return 0xffff;
	#else
	if(pos!=0xffff)
		return Bengali_RangeOffset[pos];
	else
		return 0xffff;
	#endif
}

U16 get_unicode_realpos(U16 code)
{
	U16 pos=0,realpos=0,offset=0;
	pos = get_unicode_pos(code);
	if(pos != 0xffff)
	{
		offset = get_unicode_offset(code);
		#if 0
		realpos = (code - Bengali_20x20p_v24b_RangeData[pos].min) + offset;
		#else
		realpos = (code - Bengali_16_RangeData[pos].min) + offset;
		#endif
		return realpos;
	}
	else
		return 0xffff;

}

U16 get_unicode_width(U16 code)
{
	U16 realpos=0;
	realpos = get_unicode_realpos(code);
	#if 0
	if(realpos !=0xffff)
		return Bengali_20x20p_v24b_Width[realpos];
	#else
	if(realpos !=0xffff)
		return Bengali_Width[realpos];
	#endif
}

void get_unicode_dataoffset(U16 code, U16* start, U16* end)
{
	U16 realpos=0;
	realpos = get_unicode_realpos(code);
	#if 0
	*start = Bengali_20x20p_v24b_Offset[realpos];
	*end = Bengali_20x20p_v24b_Offset[realpos + 1];
	#else
	*start = Bengali_Offset[realpos];
	*end = Bengali_Offset[realpos + 1];
	#endif
}

void get_unicode_data(U16 code,U8* buf)
{
	U16 start=0,end=0;
	U16 len =0 ,i=0;
	get_unicode_dataoffset(code,&start,&end);
	len = end - start;
	memset(buf,0,sizeof(buffer));
	#if 0
	memcpy(buf,&Bengali_20x20p_v24b_Data[start],len);
	#else
	memcpy(buf,&Bengali_Data[start],len);
	#endif
	printf("\nbuffer[%d]={",len);
	for(i=0;i<len;i++)
	{
		printf("%x,",buf[i]);
	}
	printf("}\n");
}


void writefile(U16 code)
{
	FILE *fphzk;
	U16 realpos=0,end=0;	
	U16 i=0;
	U8 str[8]={0};
	fphzk=fopen("f:\\offset.txt","wt+");

	realpos = get_unicode_realpos(code);
	for(i=0;i<398;i++)
	{
		#if 0
		if(i>=realpos+1)
			sprintf(str,"0x%04x,",(Bengali_20x20p_v24b_Offset[i]-2));
		else
			sprintf(str,"0x%04x,",Bengali_20x20p_v24b_Offset[i]);
		fputs(str,fphzk);
		if((i+1)%16 ==0)
			fputs("\r\n",fphzk);
		#else
		if(i>=realpos+1)
			sprintf(str,"0x%04x,",(Bengali_Offset[i]-2));
		else
			sprintf(str,"0x%04x,",Bengali_Offset[i]);
		fputs(str,fphzk);
		if((i+1)%16 ==0)
			fputs("\r\n",fphzk);
		#endif
	}

}
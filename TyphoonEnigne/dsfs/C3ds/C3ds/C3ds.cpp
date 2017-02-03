#include "C3ds.h"

#define PRIMARY_ID   0x4D4D
	

// Main Chunks
#define OBJECTINFO    0x3D3D	
#define OBJECTNAME	  0x4000

#define TRIANGULAR_MESH  0x4100  


#define OBJECT_VERTICES     0x4110	
#define OBJECT_FACES        0x4120 
#define OBJECT_MATERIAL     0x4130 
#define OBJECT_UV			0x4140			


#define MATERIAL_BLOCK 0xAFFF

#define MATNAME       0xA000				
#define MATDIFFUSE    0xA020				
#define MATMAP        0xA200				
#define MATMAPFILE    0xA300

C3ds::C3ds(TCHAR *path)
{
	n_uv = 0;
	bytesRead = 0;
	bytesRead2 = 0;
	index = 0;
	vert = 0;
	face = 0;
	m_Mesh = new Mesh();
	n_uv = 0;

	
	m_file = _wfopen(path,TEXT("rb"));

	ReadChunk(&m_MainChunk);

	if(m_MainChunk.ID != PRIMARY_ID)
	{
		printf("no");
	}
	else
	{
		printf("yes 3ds file! Start reading \n");
		Read3ds();
	}
	printf("File size : %d\n", m_MainChunk.lenght); //lenght of file

	fclose(m_file);


}
int C3ds::GetString(char *pBuffer)
{
	int index = 0;
	
	fread(pBuffer, 1, 1, m_file);
	
	while (*(pBuffer + index++) != 0) 
	{
		fread(pBuffer + index, 1, 1, m_file);
	}
	
	return strlen(pBuffer) + 1;
}

bool C3ds::Read3ds()
{
	int buffer[50000] = {0};
	bytesRead += 6;
	m_Current = new Chunk();
	char mat[32] = {0};
char tex3[32]= {0};
	int s = 0;
	while(bytesRead < m_MainChunk.lenght)
	{
		ReadChunk(m_Current);
		

		printf("current chunk size : %d \n", m_Current->lenght);
		switch(m_Current->ID)
		{
			
				
	
			
			
		
		

		
			case OBJECTINFO :
				printf("Yeah! object info1 \n");
				break;
	
			case OBJECTNAME :
				bytesRead += 6;
				bytesRead += GetString(m_Mesh->name);
				printf("name is %s \n",m_Mesh->name);
				break;
			case TRIANGULAR_MESH:
				break;
			case OBJECT_VERTICES :
			
					bytesRead += 6;
					bytesRead += fread(&vert, 1, 2, m_file); 
					printf("Yeah! msh info \n");
					printf("number of vertices %d \n", vert);

					m_Mesh->m_vertex = new v3[vert];
								
					bytesRead += fread(m_Mesh->m_vertex, 1, vert * 12 ,m_file);
				
				
					break;
			case OBJECT_FACES :
				
				    bytesRead += 6;
				   	bytesRead += fread(&face, 1, 2, m_file); 
					printf("Number of faces %d \n", face);

					m_Mesh->indices = new tFace [face];

					for(int i = 0; i < face; i++)
					{
						
							bytesRead += fread(&m_Mesh->indices[i].f1, 1,2, m_file);
							bytesRead += fread(&m_Mesh->indices[i].f2, 1,2, m_file);
							bytesRead += fread(&m_Mesh->indices[i].f3, 1,2, m_file);
							bytesRead += fread(&index, 1,2, m_file);
							
			
							
								printf("%d \n", m_Mesh->indices[i].f1);
								
						
					}			


					break;
			case OBJECT_MATERIAL :
				
			//	 bytesRead += 6;
				 bytesRead += GetString(mat); 
				 printf("%s \n", mat);
				break;
		
		
					case OBJECT_UV :
						   bytesRead += 6;
				  bytesRead += 6;
	 bytesRead += fread(&n_uv,1,2,m_file);
	 m_Mesh->coord = new uv[n_uv];
	 bytesRead+= fread(m_Mesh->coord, 1, n_uv *8,m_file);
 
				 printf("skip uv \n");
				break;
				
					
				case MATERIAL_BLOCK:
							
					break;
				case MATNAME :
					char matt[32];
					  bytesRead += 6;
				    bytesRead += fread(buffer, 1, m_Current->lenght - 6, m_file); 
					break;
				case MATMAP :
				break;
			
					break;
				case MATMAPFILE :
						
					 bytesRead += 6;
				     bytesRead += GetString(tex3);
					 printf("grrrrrrrrr %s\n", tex3);
					break;
			
		
		

			default :
			        bytesRead += 6;
				    bytesRead += fread(buffer, 1, m_Current->lenght - 6, m_file); 
					break;
		}
	}


	return true;
}
bool C3ds::ReadObjectChunk(Chunk *src)
{
	int buffer[50000] = {0};
	
	m_Current2 = new Chunk();


	while(bytesRead2 < src->lenght)
	{
		ReadChunk(m_Current2);
		

		
		switch(m_Current2->ID)
		{
			case OBJECT_VERTICES :
					printf("Yeah! vecrtex chunk");
					bytesRead2 += 6;
				    bytesRead2 += fread(buffer, 1, m_Current2->lenght - 6, m_file); 
					break;
			default :
			        bytesRead2 += 6;
				    bytesRead2 += fread(buffer, 1, m_Current2->lenght - 6, m_file); 
					break;
		}
	}


	return TRUE;


}
bool C3ds::ReadChunk(Chunk *src)
{
	fread(&src->ID, 1, 2, m_file); // read id of chunk
	fread(&src->lenght, 1, 4, m_file); // read lenght of chunk

	return true;
}
bool C3ds::ReadVertex(CVector *vertex)
{



	return TRUE;
}

C3ds::~C3ds()
{


}